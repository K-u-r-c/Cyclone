#include <cyclone/pfgen.h>

using namespace cyclone;

void ParticleForceRegistry::updateForces(real duration) {
	for (auto i = registrations.begin(); i != registrations.end(); i++) {
		i->fg->updateForce(i->particle, duration);
	}
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg) {
	ParticleForceRegistry::ParticleForceRegistration registration;
	registration.particle = particle;
	registration.fg = fg;
	
	registrations.push_back(registration);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg) {
	// !! Empty implementation !!
}

void ParticleForceRegistry::clear() {
	// !! Empty implementation !!
}

ParticleGravity::ParticleGravity(const Vector3& gravity) : gravity(gravity) {}

void ParticleGravity::updateForce(Particle* particle, real duration) {
	// Check that we do not have infinite mass.
	if (!particle->hasFiniteMass()) return;

	// Apply the mass-scaled force to the particle.
	particle->addForce(gravity * particle->getMass());
}