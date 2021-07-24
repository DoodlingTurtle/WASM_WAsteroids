#include "maingame.h"
#include <vector>

#include "../gameobjects/shipexplosion.h"

static std::vector<SpaceObj*>   gameObjList[3];
static std::vector<SpaceObj*>*  gameObjects         = &gameObjList[0];
static std::vector<SpaceObj*>*  prevGameObjects     = &gameObjList[1];
static std::vector<SpaceObj*>*  newGameObjects      = &gameObjList[2];

static unsigned char tick = 0;
static ShipExplosion* shipexp = nullptr;

MainGameScreen::MainGameScreen(Asteroids* asteroids, int* score) 
: asteroids(asteroids), score(score)
{ }

void MainGameScreen::onStart() {
    
    int a;
    
//    ship.controlls = keys;

    // setup the scoreboard
    scorelocation.pos.x = 5;
    scorelocation.pos.y = 5;
    scorelocation.scale = 2;
    scoreTimer = 0.0f;

//    ship.reset();
//   newGameObjects->push_back(&ship);

// Initialize the asteroids
    std::vector<Asteroids::Asteroid*>* spawnedAsteroids = asteroids->spawnAsteroids(
           (int)game_difficulty, Asteroids::SIZE_LARGE);

    for(auto ast : *spawnedAsteroids) {
        ast->moveInDirection(64);
        newGameObjects->push_back(ast);
    }
    delete spawnedAsteroids;
}

void MainGameScreen::onUpdate(olc::PixelGameEngine* pge, float deltaTime) {
    asteroids->update(deltaTime);

// score countdown
    if(*score > 0) {
        scoreTimer += 1000.0f * deltaTime;
        if(scoreTimer > 1000) {
            (*score)--;
            
            scoreTimer = 0;
        }
    }

// switch gameobject lists
    tick++;
    tick = (tick&1);

    gameObjects         = &gameObjList[0 + tick];
    prevGameObjects     = &gameObjList[1 - tick];

// Process SpaceObjects
    gameObjects->clear();
    bool asteroidFound = false;
    bool hasAsteroids = false;
    Asteroids::Asteroid* ast;
    

    printf("sort dead SO\n");

    // Check and remove all dead SpaceObjects
    for(SpaceObj* go : *prevGameObjects) {
        // Check and get Pointer for potential asteroid
        ast = asteroids->isAsteroid((void*)go);

        if(go->isAlive()) {
            gameObjects->push_back(go);
            hasAsteroids |= (ast != nullptr);
        }
        else {
            short addScore = go->getScoreValue();
            if(addScore > 0) *score += addScore;    
            
            // Check if killed object is part of the Asteroids List
            if(asteroidFound) {
                // If yes, Spawn ScorePopups TODO: reactivate
                //newGameObjects->push_back(ScorePopup::spawn(addScore, go->pos.x, go->pos.y));
                
                Asteroids::SIZES astSize = ast->getSize();
                
                //TODO: Spawn AsteroidExplosion at go->pos
                //(once particle system is reintroduced)

                // If the destroyed asteroid is bigger then the min. size, span 2
                // smaller asteroids at the same position
                if(astSize > Asteroids::SIZE_SMALL){
                    std::vector<Asteroids::Asteroid*>* spawned = asteroids->spawnAsteroids(
                           2,  
                           static_cast<Asteroids::SIZES>(
                               static_cast<int>(astSize)-1
                            ), ast->pos.x, ast->pos.y);

                    for(auto ast : *spawned) {
                        ast->moveInDirection(64);
                        newGameObjects->push_back(ast);
                    }
                    delete spawned;

                }
            }
        }
    } 

// Add new SpaceObjects to the cycle
    for(SpaceObj* go : *newGameObjects)
        if(go->isAlive()) {
            printf("add new SO: %d \n", go);
            if(asteroids->isAsteroid(go) != nullptr)
                hasAsteroids = true;
            gameObjects->push_back(go);
        }
    
    newGameObjects->clear();

// Check win condition
    if(!hasAsteroids) {
        printf("no asteroids found\n");
        this->exit();
        return;
    }

//TODO: Rewrite Update all GameObject-Managers/Factorys
    //ScorePopup::refreshInstanceList();

// Send out an update heartbeat to all attached objects
    for(SpaceObj* go : *gameObjects) {
        printf("update new SO: %d \n", go);
        go->onUpdate(deltaTime);
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
    sprintf(buffer, "Score: % 8d", *score);
    std::string s(buffer);
    
    pge->DrawString(
            scorelocation.pos.x, scorelocation.pos.y, 
            s, olc::Pixel(8, 0, 80, 255), 
            scorelocation.scale
    ); 
}

void MainGameScreen::onEnd() {
    if(shipexp != nullptr)
        delete shipexp;
    
    shipexp = nullptr;

    //ScorePopup::cleanup();
    
    //Shot::cleanup();

    gameObjects->clear();
    prevGameObjects->clear();
    newGameObjects->clear();

    asteroids->killall();
}


