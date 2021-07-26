#include "maingame.h"
#include <vector>
#include "../config.h"
#include "../global.h"

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
}

void MainGameScreen::onStart() {

// Initialize the Ship
    ship = new Ship();
    newGameObjects->push_back(ship);

// Initialize the asteroids
    std::vector<Asteroids::Asteroid*>* spawnedAsteroids = Global::asteroids->spawnAsteroids(
           (int)game_difficulty, Asteroids::SIZE_LARGE);

    for(auto ast : *spawnedAsteroids) {
        Debug("Add Asteroid " << ast);
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
        Debug("is asteroid " << ast);

        if(go->isAlive()) {
            Debug("live SO " << go);
            gameObjects->push_back(go);
            hasAsteroids |= (ast != nullptr);
        }
        else {
            short addScore = go->getScoreValue();
            if(addScore > 0) Global::score += addScore;    
           
            Debug("dead SO " << go);

            // Check if killed object is part of the Asteroids List
            if(asteroidFound) {
                // If yes, Spawn ScorePopups TODO: reactivate
                //newGameObjects->push_back(ScorePopup::spawn(addScore, go->pos.x, go->pos.y));
                
                Asteroids::SIZES astSize = ast->getSize();
                
                //TODO: Spawn AsteroidExplosion at go->pos
                //TODO: Move logic into Asteroids onUpdate
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
        
        if(go != nullptr && go->isAlive()) {
            Debug("add new SO " << go);
            if(Global::asteroids->isAsteroid(go) != nullptr)
                hasAsteroids = true;
            gameObjects->push_back(go);
        } else Debug("WARNING: dead SO added " << go);
    
    newGameObjects->clear();

// Check win condition
    if(!hasAsteroids) {
        Debug("no asteroids found");
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
            Debug("SO " << go << " spawned " << so->size() << " new SO");
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
    //ScorePopup::cleanup();
    
    //Shot::cleanup();

    delete ship;

    gameObjects->clear();
    prevGameObjects->clear();
    newGameObjects->clear();

    asteroids->killall();
}


