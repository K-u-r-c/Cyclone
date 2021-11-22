#pragma once

#include <cyclone/cyclone.h>

#include <cstdlib>

class Application {
protected:
	int width;
	int height;

public:
	virtual const char* getTitle();
	virtual void initGraphics();

	// Called to set the projection characteristics of the camera.
	virtual void setView();

	//Called just before the application is destroyed. Clear up can
    // be performed here or in the application destructor.
    // The default implementation does nothing.
	virtual void deinit();

	// Called each frame to display the current scene.
	virtual void display();

	// Called each frame to update the current state of the scene.
	virtual void update();

	// Called when a keypress is detected.
	virtual void key(unsigned char key);

	// Notifies the application that the window has changed size.
	virtual void resize(int width, int height);

	// Called when GLUT detects a mouse button press.
	virtual void mouse(int button, int state, int x, int y);

	// Called when GLUT detects a mouse drag.
	virtual void mouseDrag(int x, int y);

	// Renders the given text to the given x,y locations (in screen space) on the window.
	// This is used to pass status information to the application.
	void renderText(float x, float y, const char* text, void* font = NULL);
};

class MassAggregateApplication : public Application {
protected:
	cyclone::ParticleWorld world;
	cyclone::Particle* particleArray;

public:
	MassAggregateApplication(unsigned int particleCount);
	virtual ~MassAggregateApplication();

	// Update the particle positions.
	virtual void update();

	// Sets up the graphics rendering.
	virtual void initGraphics();

	// Display the particles.
	virtual void display();
};