#ifndef __PARTICLES_H__
#define __PARTICLES_H__ 

#include "olcPixelGameEngine.h"
#include "config.h"
#include <vector>

template <typename Em, typename Pa>
class ParticleSystem {
public:
    class Particle {
    public:
        virtual ~Particle(){};
        virtual Pa* spawnNewParticle(Em* e) = 0;
        virtual bool onParticleUpdate(float deltaTime) = 0;
        virtual void onParticleDraw(olc::PixelGameEngine*) = 0;
    };

    class Emitter {
    public:
        virtual ~Emitter(){
            Debug("ParticleSystem::Emitter::~Emitter");
            for(auto p : particles)
                delete p;

            particles.clear();
        }

        virtual void onParticleDeath(Pa* particle){}; // Called, when one of the particles has reached its max lifetime
        virtual void onNoParticlesLeft()                 = 0; // Called, once all particles in the list have reached its max lifetime

        virtual void updateParticles(float deltaTime) final {
            Pa* p;
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
        };
        virtual void drawParticles(olc::PixelGameEngine* pge) final{
            for(auto p : particles)
                p->onParticleDraw(pge);
        }

    private:
        std::vector<Pa*> particles;
        friend class ParticleSystem<Em, Pa>;
    };

    ParticleSystem(Em* e, Pa* p) {
        if(!std::is_base_of<ParticleSystem::Particle, Pa>())
            throw "given Particle is not instanceOf ParticleSystem::Particle";

        if(!std::is_base_of<ParticleSystem::Emitter, Em>())
            throw "given Emitter is not instanceOf ParticleSystem::Emitter";
       
        this->emitter = e;
        this->particle = p;
    }
    ~ParticleSystem() {
        delete this->emitter;
        delete this->particle;
    }

    virtual int spawnNewParticles(int cnt=1) final {

        Debug("Spawn Particles " << cnt);

        int attempts = 1000;
        int spawned = 0;
        for(int a = 0; a < cnt && attempts > 0; a++) {
            auto p = particle->spawnNewParticle(emitter);
            if(p != nullptr) {
                emitter->particles.push_back(p);
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

protected:
    Em* emitter;
    Pa* particle;

};


#endif
