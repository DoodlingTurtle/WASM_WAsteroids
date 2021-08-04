#include "sprite_dissolve.h"

/*#############################################################################
 * SpriteDissovlve
 *###########################################################################*/
SpriteDissolve::SpriteDissolve( 
        olc::Sprite* spr, RGNDS::Transform* tr,
        float mpd, float mpl
) 
: t_SpriteDissolve(
    new SpriteDissolve_Emitter(spr, tr, this, mpd, mpl),
    new SpriteDissolve_Particle({0, 0}, 0, 0, 0, nullptr)
) {}

void SpriteDissolve::onUpdate(float deltaTime) 
{ emitter->updateEmitter(deltaTime); }
void SpriteDissolve::onDraw(olc::PixelGameEngine* pge) 
{ emitter->drawParticles(pge); }

/*#############################################################################
 * SpriteDissolve_Emitter
 *###########################################################################*/
SpriteDissolve_Emitter::SpriteDissolve_Emitter(
        olc::Sprite* spr, RGNDS::Transform* tr,
        SpriteDissolve* sys, float mpmd, float mplt
){
    this->system = sys;
    this->decal = new olc::Decal(spr);
    int offx = spr->width / 2;
    int offy = spr->height / 2;

    pos = tr->pos;
    setAngle(tr->ang);

    olc::vf2d initialCoords;
    olc::vf2d finalCoords;

    //Debug("SDE: " << tr->dir.x << " " << cos(tr->ang));

    olc::vf2d pos = tr->pos;
    tr->pos.x = 0;
    tr->pos.y = 0;

    for(int y = 0; y < spr->height; y++) {
        for(int x = 0; x < spr->width; x++) {
            olc::Pixel p = spr->GetPixel(x, y); 
            if(p.a > 3) {
                initialCoords.x = (x - offx);
                initialCoords.y = (y - offy);

                tr->translate(&initialCoords, &finalCoords);

                SpriteDissolve_Particle* pa = new SpriteDissolve_Particle(
                        finalCoords, x, y, p.a, 
                        this, RandF() * mpmd, RandF() + mplt);
                particles.push_back(pa);
            }
        }
    }

    tr->pos = pos;
}

SpriteDissolve_Emitter::~SpriteDissolve_Emitter() { delete decal; }

void SpriteDissolve_Emitter::onNoParticlesLeft() { system->onEmitterFinished(); }

/*#############################################################################
 * SpriteDissolve_Particle
 *###########################################################################*/
SpriteDissolve_Particle::SpriteDissolve_Particle(
        olc::vf2d s, 
        int x, int y, float a, 
        SpriteDissolve_Emitter* em,
        float speed, float maxLifetime
) {
    pos = s;
    directionFromPositionVector();
    pos += em->pos;

    px.x = x;
    px.y = y;
    lifetime = (1.0f / 255.0f) * a;

    this->em = em;
    this->speed = speed;
    this->maxLifetime = maxLifetime;
}

SpriteDissolve_Particle* SpriteDissolve_Particle::spawnNewParticle(SpriteDissolve_Emitter* e) { return 0; }

bool SpriteDissolve_Particle::onParticleUpdate(float deltaTime) {
    lifetime -= deltaTime*maxLifetime;
    if(lifetime < 0.0f) lifetime = 0.0f;
    moveInDirection(deltaTime * speed);

    return lifetime > 0;
}

void SpriteDissolve_Particle::onParticleDraw(olc::PixelGameEngine* pge){
    pge->DrawPartialDecal(pos, em->decal, px, {1.0f, 1.0f});
};

