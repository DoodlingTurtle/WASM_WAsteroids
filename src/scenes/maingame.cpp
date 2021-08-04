#include "maingame.h"
#include <vector>
#include "../config.h"
#include "../global.h"

#include "../gameobjects/scorepopup.h"

static std::vector<SpaceObj*>   gameObjList[3];
static std::vector<SpaceObj*>*  gameObjects         = &gameObjList[0];
static std::vector<SpaceObj*>*  prevGameObjects     = &gameObjList[1];
static std::vector<SpaceObj*>*  newGameObjects      = &gameObjList[2];

static unsigned char tick = 0;

MainGameScreen::MainGameScreen() 
{ 
// setup the scoreboard
    scorelocation.pos.x = 5;
    scorelocation.pos.y = 5;
    scorelocation.scale = 2;
    shipexp = nullptr;
    reset();
}

void MainGameScreen::reset() {
    state = MainGameScreen::STATE_LOST;
    game_difficulty = 1.0f;
    shipSurvived = true;
    scoreTimer = 0.0f;

    onEnd();
}

void MainGameScreen::onStart() {
    if(state != MainGameScreen::STATE_RUNNING) {
        if(game_difficulty>8.0f)
            game_difficulty = 8.0f;

    // Initialize the Ship
        ship = new Ship();
        shipSurvived = true;
        newGameObjects->push_back(ship);

    // Initialize the asteroids
        std::vector<Asteroids::Asteroid*>* spawnedAsteroids = Global::asteroids->spawnAsteroids(
               (int)game_difficulty, Asteroids::SIZE_LARGE);

        ship->scale = 2.0f;
        RGNDS::Collision::Circle sc = ship->getCollider();
        ship->scale = 1.0f;

        for(auto ast : *spawnedAsteroids) {
            while(RGNDS::Collision::checkCircleOnCircle(sc, ast->getColliders())) {
                Debug("ship hit before game started " << ast->pos.x << " " << ast->pos.y);
                ast->moveInDirection(32);
            }

            newGameObjects->push_back(ast);
        }
        delete spawnedAsteroids;
    }
    state = MainGameScreen::STATE_RUNNING;
}

void MainGameScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {

// Check for Pause Key
    if(pge->GetKey(GameKeyMap[KEYPAD_SELECT]).bPressed) {
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

// switch Spaceobject lists
    tick++;
    tick = (tick&1);

    gameObjects         = &gameObjList[0 + tick];
    prevGameObjects     = &gameObjList[1 - tick];

// Process SpaceObjects
    gameObjects->clear();
    bool asteroidFound = false;
    bool hasAsteroids = false;
    Asteroids::Asteroid* ast;

    // Check and remove all dead SpaceObjects
    for(SpaceObj* go : *prevGameObjects) {
        // Check and get Pointer for potential asteroid
        ast = Global::asteroids->isAsteroid((void*)go);

        if(go->isAlive()) {
            gameObjects->push_back(go);
            hasAsteroids |= (ast != nullptr);
        }
        else if(go == (SpaceObj*)ship) {
            shipSurvived = false;
            shipexp = new ShipExplosion(ship);
            newGameObjects->push_back(shipexp);
        }
        else {
            Debug("Delete dead SO: " << go << ": " << go->allowDeleteAfterDeath());
            if(go->allowDeleteAfterDeath())
                delete go;
        }
    } 

// Add new SpaceObjects to the cycle 
    for(SpaceObj* go : *newGameObjects)
        if(go != nullptr && go->isAlive()) {
            Debug("add new SO " << go);
            if(Global::asteroids->isAsteroid(go) != nullptr)
                hasAsteroids = true;
            gameObjects->push_back(go);
        } else Debug("WARNING: dead SO added " << go);
    
    newGameObjects->clear();

// Check win condition
    if(!hasAsteroids || (!shipSurvived && !shipexp->isAlive())) {
        state = (shipSurvived) 
            ? (MainGameScreen::STATE_WON) 
            : (MainGameScreen::STATE_LOST); 
        exit();
        return;
    }

    ScorePopup::refreshInstanceList();

// Send out an update heartbeat to all attached objects
    std::vector<SpaceObj*>* so;
    for(SpaceObj* go : *gameObjects) {
        so = go->onUpdate(deltaTime);
        if(so != nullptr) {
            for(auto s : *so)
                newGameObjects->push_back(s);
        
            delete so;
        }
    }
}

void MainGameScreen::onDraw(olc::PixelGameEngine* pge) {

    for(SpaceObj* go : *gameObjects)
        go->onDraw(pge);

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

        Debug("remove ship exp");
        if(shipexp != nullptr)
            delete shipexp;
        shipexp = nullptr;

        Debug("clear score popup");
        ScorePopup::cleanup();
        Debug("clear Asteroids");
        Global::asteroids->killall();

        Debug("delete ship");
        if(ship != nullptr)
            delete ship;
        ship = nullptr;

        Debug("clear gameobjects");
        gameObjects->clear();
        prevGameObjects->clear();
        newGameObjects->clear();

        Debug("MainGameScreen::onEnd finished");
    }
}

MainGameScreen::GAME_STATE MainGameScreen::getState() { return state; }
