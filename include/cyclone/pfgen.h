#pragma once

#include <vector>

#include "core.h"
#include "particle.h"

namespace cyclone {

// A force generator can be asked to add a force to one or more particles.
class ParticleForceGenerator {
public:
	// Overload this in implementations of the interface to calculate and updae
	// the force applied to the given particle.
	virtual void updateForce(Particle* particle, real duration) = 0;
};

// A force generator that applies a gravitational force. One instance can be used
// for multilple particles.
class ParticleGravity : public ParticleForceGenerator {
	// Holds the acceleation due to gravity.
	Vector3 gravity;

public:
	// Creates the geneator with the given acceleration.
	ParticleGravity(const Vector3& gravity);

	// Applies the gravitational force to the given particle.
	virtual void updateForce(Particle* particle, real duration);
};

// A formce generator that applies a drag force. One instance can be used
// for multiple particles.
class ParticleDrag : public ParticleForceGenerator {
	// Holds the velocity drag coefficient.
	real k1;

	// Holds the velocity squared drag coefficient.
	real k2;

public:
	// Creates the generator with the given coefficients.
	ParticleDrag(real k1, real k2);

	// Applies the drag force to the given particle.
	virtual void updateForce(Particle* particle, real duration);
};

// Holds all the force generators and the particles that they pply to.
class ParticleForceRegistry {
protected:
	// Keeps track of one force generator and the particle it applies to.
	struct ParticleForceRegistration {
		Particle* particle;
		ParticleForceGenerator* fg;
	};

	// Holds the lsit of registrations.
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

public:
	// Registers the given force generator to apply to the given particle.
	void add(Particle* particle, ParticleForceGenerator* fg);

	// !! Empty implementation !!
	// Removes the given registered pair from the registry. If the pair is not
	// registered, this method will have no effect.
	void remove(Particle* particle, ParticleForceGenerator* fg);

	// !! Empty implementation !!
	// Clears all registrations from the registry. This will not delete the particles
	// or the force generators themselves, just the records of their connection.
	void clear();

	//Calls all the force generators to update the forces of their corresponding particles.
	void updateForces(real duration);
};

} // namespace cyclone