#pragma once

// @change later to get them from pfgen.h
#include "core.h"
#include "particle.h"
#include <vector>

namespace cyclone {

class ParticleWorld {
public:
	typedef std::vector<Particle*> Particles;

protected:
	Particles particles;

public:
	// Integrates all the particles in this world forward in time by the given duration.
	void integrate(real duration);

	// Processes all the physics for the particle world.
	void runPhysics(real duration);

	// Initializes the world for a simulation frame. This clears the force accumulators for particles
	// in the world. After calling this, the particles can have their forces for this frame added.
	void startFrame();

	// Returns the list of particles.
	Particles& getParticles();
};

}