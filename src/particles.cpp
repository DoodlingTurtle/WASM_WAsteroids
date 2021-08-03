#include "particles.h"












/*#############################################################################
 * ParticleSystem::Emitter
namespace ParticleSystem {
    ParticleSystem::Emitter::Emitter()
    {
        _proto = new P();
        Particle* p = dynamic_cast<Particle*>(_proto);
        if(p == nullptr) {
            Debug("WARNING: given Templaten class is not a ChildOf 'ParticleSystem::Particle'");
            delete _proto;
            _proto = nullptr;
        }
    }

    ParticleSystem::Emitter::~Emitter() {
        Debug("ParticleSystem::Emitter::~Emitter");
        for(auto p : particles)
            delete p;

        particles.clear();
        if(_proto != nullptr)
            delete _proto;
    }

    int ParticleSystem::Emitter::spawnNewParticles(int cnt) {

        Debug("Spawn Particles " << cnt);

        int attempts = 1000;
        int spawned = 0;
        for(int a = 0; a < cnt && attempts > 0; a++) {
            Particle* p = _proto->spawnNewParticle(this);
            if(p != nullptr) {
                particles.push_back(p);
                spawned++;
            }
            else {
                delete p;
                a--;
                attempts--;
            }
        }

        return spawned;
    }

    void ParticleSystem::Emitter::updateParticles(float deltaTime) {
        Particle* p;
        int a;
        
        for(a = particles.size()-1; a >= 0; a--) {
            
            p = particles.at(a);    

            if(!p->onParticleUpdate(deltaTime)) {
                onParticleDeath(p);
                delete p;
                particles.erase(particles.begin() + a);
            }
        }

        if(particles.size() == 0)
            onNoParticlesLeft();
    }

    void ParticleSystem::Emitter::drawParticles(olc::PixelGameEngine* pge) {
        for(auto p : particles)
            p->onParticleDraw(pge);
    }

    int ParticleSystem::Emitter::cntActiveParticles() { return particles.size(); }
}
*/
