#include <cstdlib>
#include <cyclone/pworld.h>

using namespace cyclone;

void ParticleWorld::startFrame() {
    for (Particles::iterator p = particles.begin(); p != particles.end(); p++) {
        // Remove all forces from the accumulator
        (*p)->clearAccumulator();
    }
}

void ParticleWorld::integrate(real duration) {
    for (Particles::iterator p = particles.begin(); p != particles.end(); p++) {
        // Integrate the particle by the given duration.
        (*p)->integrate(duration);
    }
}

void ParticleWorld::runPhysics(real duration) {
    integrate(duration);
}

ParticleWorld::Particles& ParticleWorld::getParticles() { return particles; }