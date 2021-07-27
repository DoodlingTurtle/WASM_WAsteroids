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
    scoreTimer = 0.0f;
    game_difficulty = 1.0f;
    shipSurvived = true;
}

void MainGameScreen::onStart() {

    if(game_difficulty>8.0f)
        game_difficulty = 8.0f;

// Initialize the Ship
    ship = new Ship();
    shipSurvived = true;
    newGameObjects->push_back(ship);

// Initialize the asteroids
    std::vector<Asteroids::Asteroid*>* spawnedAsteroids = Global::asteroids->spawnAsteroids(
           (int)game_difficulty, Asteroids::SIZE_LARGE);

    for(auto ast : *spawnedAsteroids) {
        ast->moveInDirection(64);
        newGameObjects->push_back(ast);
    }
    delete spawnedAsteroids;
}

void MainGameScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    
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
        else if(go == (SpaceObj*)ship)
            shipSurvived = false;
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
    if(!hasAsteroids || !shipSurvived) {
        exit();
        return;
    }

//TODO: Rewrite Update all GameObject-Managers/Factorys
//TODO: Move into score spawn logic into asteroid update onUpdate
    //ScorePopup::refreshInstanceList();

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
    

// TODO: If Ship is dead, exit game 
/*
    if(!ship.isAlive() and shipexp == nullptr) {
        Asteroid::ship = nullptr;

        shipexp = new ShipExplosion(&ship);
        newGameObjects->push_back(shipexp);
    }
    else if(shipexp != nullptr and !shipexp->isAlive()) {
        exit();
    }
*/
}

void MainGameScreen::onDraw(olc::PixelGameEngine* pge) {

    for(SpaceObj* go : *gameObjects)
        go->onDraw(pge);

// Rendering Score
    char buffer[18];
    //printf(buffer, "Score: % 8d", *score);
    std::string s(buffer);
    
    pge->DrawString(
            scorelocation.pos.x, scorelocation.pos.y, 
            s, olc::Pixel(8, 0, 80, 255), 
            scorelocation.scale
    ); 
}

void MainGameScreen::onEnd() {
    /*if(shipexp != nullptr)
        delete shipexp;
    
    shipexp = nullptr;
    */
    ScorePopup::cleanup();
    
    Global::asteroids->killall();
    delete ship;

    gameObjects->clear();
    prevGameObjects->clear();
    newGameObjects->clear();
}

bool MainGameScreen::gameWasWon() { return shipSurvived; }
