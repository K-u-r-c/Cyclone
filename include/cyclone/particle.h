#pragma once

#include <cyclone/core.h>

namespace cyclone {

// A particle is a simplest object that can be simulated in the physics system.
class Particle {
protected:
	// Holds the linear position of the particle in world space.
	Vector3 position;

	// Holds the linear velocity of the particle in world space.
	Vector3 velocity;

	// Holds the acceleration of the particle. This value can be used to set
	// acceleration due to gravity (it's primary use), or any other constatnt acceleration.
	Vector3 acceleration;

	// Holds the amount of damping applied to linear motion. Damping is required
	// to remove energy added through numerical instability in the integrator.
	real damping;

	// Holds the inverse of the mass of the particle. It is more useful to hold
	// the inverse mass because integration is ismpler, and because in real-time
	// simulation it is more useful to have objects with infinite mass(immovable)
	// than zero mass (completely unstable in numerical simulation).
	real inverseMass;

	// Holds the accumulated force to be applied at the next simulation iteration only.
	// This value is zeroed at each integration step.
	Vector3 forceAccum;

public:
	// Integrates the particle forward in time by the given amount. This function
	// uses a Newton-euler integration method, which is a linear approximation to
	// the correct integral. For this reason it may be inaccurate in some cases.
	void integrate(real duration);

	// Clears the forces applied to the particle.This will be
	// called automatically after each integration step.
	void clearAccumulator();

	// Sets the mass of the particle.
	//
	// The new mass of the body.This may not be zero. Small masses can produce unstable 
	// rigid bodies under simulation.
	//
	// This invalidates internal data for the particle. Either an integration 
	// function, or the calculateInternals function should be called before trying to 
	// get any settings from the particle.
	void setMass(const real mass);

	// Gets the current mass of the particle.
	real getMass() const;

	// Fills the given vector with the position of the particle.
	void getPosition(Vector3* position) const;

	// Gets the position of the particle.
	Vector3 getPosition() const;

	// Sets the position of the particle.
	void setPosition(const Vector3& position);
	
	// Sets the position of the particle by component.
	void setPosition(const real x, const real y, const real z);

	// Sets the velocity of the particle.
	void setVelocity(const Vector3& velocity);

	// Sets the velocity of the particle by component
	void setVelocity(const real x, const real y, const real z);

	// Fills the given vector with the velocity of the particle.
	void getVelocity(Vector3* velocity) const;

	// Gets the velocity of the particle.
	Vector3 getVelocity() const;

	// Sets both the damping of the particle.
	void setDamping(const real damping);
	
	// Sets the constant acceleration of the particle.
	void setAcceleration(const Vector3& acceleration);
	
	// Sets the constant acceleration of the particle by component.
	void setAcceleration(const real x, const real y, const real z);
};

}