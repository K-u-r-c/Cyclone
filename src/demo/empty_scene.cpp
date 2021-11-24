#include <cyclone/cyclone.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <app.h>
#include <timing.h>

class Empty : public Application {
    struct Sphere {
        double velX = 0;
        cyclone::Particle particle;
        unsigned startTime;

        // Draws the sphere.
        void render() {
            cyclone::Vector3 position;
            particle.getPosition(&position);

            glColor3f(0, 0, 0);
            glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glutSolidSphere(0.5f, 50, 50);
            glPopMatrix();
        }
    };

    Sphere sphere;

public:
    //Creates a new demo object.
    Empty();

    // Returns the window title for the demo.
    virtual const char* getTitle();

    // Update the particle positions.
    virtual void update();

    // Display the particle positions.
    virtual void display();

    // Handle a mouse click.
    virtual void mouse(int button, int state, int x, int y);

    // Handle a keypress.
    virtual void key(unsigned char key);
};

// ---------------- Method definitions ---------------- //

Empty::Empty() {
    sphere.particle.setMass(0.1f);
    sphere.particle.setVelocity(0.0f, 0.0f, 0.0f);
    sphere.particle.setAcceleration(0.0f, 0.0f, 0.0f);
    sphere.particle.setDamping(0.59f);
}

const char* Empty::getTitle() { return "Cyclone > Empty Demo"; }

void Empty::update() {
    // Find the duration of the last frame in seconds
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

    // Integrate physical objects
    sphere.particle.integrate(duration);

    Application::update();
}

void Empty::display() {
    // Clear the viewport and set the camera direction
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    sphere.render();

    glEnd();
}

void Empty::mouse(int button, int state, int x, int y) {}

void Empty::key(unsigned char key) {
    switch (key) {
    case '1':
        sphere.velX = 0;
        sphere.velX += 2;
        break;

    case '2':
        sphere.velX = 0;
        sphere.velX -= 2;
    }

    sphere.particle.setVelocity(sphere.velX, 0.0f, 0.0f);
}

// Called by the common demo framework to create an application
// object (with new) and return a pointer.
Application* getApplication() { return new Empty(); }