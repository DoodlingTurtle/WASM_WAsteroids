#include <vector>
#include <unordered_set>

#include "./maingame.h"

#include "../config.h"
#include "../engine/Global.h"
#include "../engine/Assets.h"

#include "./pausescreen.h"
#include "./gameoverscreen.h"
#include "./upgradescreen.h"

#include "../gameobjects/player_ship.h"

using namespace RGNDS;

Mix_Music** MainGameScreen::bgMusic[BGM_TRACKS] = {
    &Assets::bgmLV01,
    &Assets::bgmLV02,
    &Assets::bgmLV03,
    &Assets::bgmLV04,
    &Assets::bgmLV05
};

MainGameScreen::MainGameScreen() 
    : state(GAME_STATE::STATE_LOST), game_difficulty(0.0f), scoreTimer(0.0f)
{ 
// setup the scoreboard
    scorelocation.pos = { 5.0f, 5.0f };
    scorelocation.scale = 2;
    switchBGMusic(nullptr);

    Global::shipStats->resetToLV1();
    UpgradeScreen::resetPool();
    
    Global::level = 0;
    Global::score = 0;
}

void MainGameScreen::onStart(olc::PixelGameEngine* pge) {
    if(state != GAME_STATE::STATE_RUNNING) {
        game_difficulty += 1.0f;
        Global::level++;

        if(game_difficulty>16.0f)
            game_difficulty = 16.0f;

        Global::world->removeWithAttribute(GameObject::ALL);

    // Initialize the Ship
        auto ship = new PlayerShip();
        Global::world->addGameObject(ship);

    // Initialize the asteroids
        Asteroid::spawn( (int)game_difficulty, Asteroid::SIZE_LARGE, ship);
    }
    state = GAME_STATE::STATE_RUNNING;
}

void MainGameScreen::updateBGM() {
    if (!Mix_PlayingMusic()) {
        int track = std::min(4, (int)floor(this->game_difficulty / 1.2f));
        Mix_PlayMusic(*bgMusic[track], 0);
    }
}

bool MainGameScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

// Check Music Loop
    updateBGM();

// Check for Pause Key
    if(Global::input->pressed&KEYPAD_SELECT){ 
        return false; }

// Check Win loos state
    // If no asteroids = game won
    if(Global::world->countWithAttribute(GameObject::ASTEROID) == 0) {
        state = GAME_STATE::STATE_WON; 
        return false;
    }

    // If no ship or ship explosition = game lost 
    if(Global::world->countWithAttribute(GameObject::MAINGAME_COMPONENT) == 0) {
        state = GAME_STATE::STATE_LOST; 
        return false;
    }

// score countdown
    if(Global::score > 0) {
        scoreTimer += 1000.0f * deltaTime;
        if(scoreTimer > 1000) {
            Global::score--;
            scoreTimer = 0;
        }
    }

    return true;
}

void MainGameScreen::onDraw(olc::PixelGameEngine* pge) {

// Rendering Score
    char buffer[18];
    sprintf(buffer, "Score: % 8d", Global::score);
    std::string s(buffer);
    
    pge->DrawString(
        scorelocation.pos.x, scorelocation.pos.y, 
        s, olc::Pixel(32, 32, 196), 
        scorelocation.scale
    ); 
}

void MainGameScreen::onEnd() {
    if(state != GAME_STATE::STATE_RUNNING)
        Global::world->removeWithAttribute(GameObject::ALL);
}

Scene* MainGameScreen::nextScene() {
    switch(state){
    case GAME_STATE::STATE_RUNNING: 
        this->persistent = true;
        return new PauseScreen(this);

    case GAME_STATE::STATE_LOST:
        this->persistent = false;
        return new GameOverScreen();

    case GAME_STATE::STATE_WON: 
        this->persistent = true;
        return new UpgradeScreen (this);
    }

    return nullptr;
}
