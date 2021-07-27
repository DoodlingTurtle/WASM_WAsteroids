#ifndef __PARTICLES_H__
#define __PARTICLES_H__ 

#include "olcPixelGameEngine.h"
#include <vector>

class ParticleSystem {

public:
    class Particle {
    public:
        virtual ~Particle(){};
        virtual Particle* spawnNewParticle() = 0;
        virtual bool onParticleUpdate(float deltaTime) = 0;
        virtual void onParticleDraw(olc::PixelGameEngine*) = 0;
    };

    class Emitter {
    public:
        Emitter();
        virtual ~Emitter();

        virtual void onParticleAssign(Particle*) {}
        virtual void onParticleDeath(Particle* particle){}; // Called, when one of the particles has reached its max lifetime
        virtual void onNoParticlesLeft()                 = 0; // Called, once all particles in the list have reached its max lifetime

        virtual int  spawnNewParticles(int cnt=1) final;
        virtual void updateParticles(float deltaTime) final;
        virtual void drawParticles(olc::PixelGameEngine*) final;

        virtual int cntActiveParticles() final;

    private:
        Particle* _proto;

        std::vector<Particle*> particles;

        friend class ParticleSystem;
    };

    ParticleSystem();
    ~ParticleSystem();

    template <typename E, typename P>
    bool assign(E* em, P* pa){
        Particle* particle = dynamic_cast<Particle*>(pa);
        if(particle == nullptr)
            return false;
        
        Emitter* emitter = dynamic_cast<Emitter*>(em);
        if(emitter == nullptr)
            return false;

        if(emitter->_proto == nullptr)
            emitters->push_back(emitter);

        emitter->_proto = particle;

        em->onParticleAssign(particle);

        return true; 
    }

    void destroyFinished();


protected:

    
private:
    std::vector<Emitter*>* emitters;

};


#endif
