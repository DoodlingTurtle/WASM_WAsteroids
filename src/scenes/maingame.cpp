#include "maingame.h"
#include <vector>
#include <unordered_set>

#include "config.h"
#include "global.h"
#include "assets.h"

MainGameScreen::MainGameScreen() 
{ 
// setup the scoreboard
    scorelocation.pos = { 5.0f, 5.0f };
    scorelocation.scale = 2;
    reset();
}

void MainGameScreen::reset() {
    state = MainGameScreen::STATE_LOST;
    game_difficulty = 1.0f;
    scoreTimer = 0.0f;

    onEnd();
    Global::switchBGMusic(Assets::bgmGame);
}

#ifdef DEBUG_BUILD
void MainGameScreen::endLevel() { 
    state = MainGameScreen::STATE_WON;
    exit(); 
}
#endif

void MainGameScreen::onStart() {
    if(state != MainGameScreen::STATE_RUNNING) {
        if(game_difficulty>8.0f)
            game_difficulty = 8.0f;

        Global::world->removeWithAttribute(GameObject::ALL);

    // Initialize the Ship
        Ship* ship = new Ship();
        Global::world->addGameObject(ship);

    // Initialize the asteroids
        Asteroid::spawn( (int)game_difficulty, Asteroid::SIZE_LARGE, ship);
    }
    state = MainGameScreen::STATE_RUNNING;
}

void MainGameScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

// Check for Pause Key
    if(Global::gameInput->pressed&KEYPAD_SELECT){
        exit();
        return;
    }

// Check Win loos state
    // If no asteroids = game won
    if(Global::world->countWithAttribute(GameObject::ASTEROID) == 0) {
        state = MainGameScreen::STATE_WON; 
        exit();
        return;
    }

    // If no ship or ship explosition = game lost 
    if(Global::world->countWithAttribute(GameObject::MAINGAME_COMPONENT) == 0) {
        state = MainGameScreen::STATE_LOST; 
        exit();
        return;
    }

// score countdown
    if(Global::score > 0) {
        scoreTimer += 1000.0f * deltaTime;
        if(scoreTimer > 1000) {
            Global::score--;
            scoreTimer = 0;
        }
    }
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
    if(state != MainGameScreen::STATE_RUNNING) {
        Debug("MainGameScreen::onEnd finished");
    }
}

MainGameScreen::GAME_STATE MainGameScreen::getState() { return state; }
