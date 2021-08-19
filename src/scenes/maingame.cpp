#include "maingame.h"
#include <vector>
#include <unordered_set>

#include "config.h"
#include "global.h"
#include "assets.h"

static std::vector<SpaceObj*>   gameObjList[3];
static std::vector<SpaceObj*>*  gameObjects         = &gameObjList[0];
static std::vector<SpaceObj*>*  prevGameObjects     = &gameObjList[1];
static std::vector<SpaceObj*>*  newGameObjects      = &gameObjList[2];

static std::unordered_set<SpaceObj*> worldObjects;

static unsigned char tick = 0;

MainGameScreen::MainGameScreen() 
:shipexp(nullptr), ship(nullptr)
{ 
// setup the scoreboard
    scorelocation.pos = { 5.0f, 5.0f };
    scorelocation.scale = 2;
    reset();
}

void MainGameScreen::reset() {
    state = MainGameScreen::STATE_LOST;
    game_difficulty = 1.0f;
    shipSurvived = true;
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

    // Initialize the Ship
        ship = new Ship();
        shipSurvived = true;
        newGameObjects->push_back(ship);

    // Initialize the asteroids
        Global::asteroids->killall();
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
    if(Global::gameInput->pressed&KEYPAD_SELECT){
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

        Debug("delete ship");
        if(shipexp) delete shipexp; 
        shipexp = nullptr;

        if(ship) delete ship; 
        ship = nullptr;

        Debug("clear gameobjects");
        auto _clearGameObjects = [this](std::vector<SpaceObj*>* gameObjects) {
            for(auto go : *gameObjects)
                if(go->allowDeleteAfterDeath())
                    delete go;

            gameObjects->clear();
        };
        
        _clearGameObjects(gameObjects);
        _clearGameObjects(newGameObjects);
        prevGameObjects->clear();

        Debug("MainGameScreen::onEnd finished");
    }
}

MainGameScreen::GAME_STATE MainGameScreen::getState() { return state; }
