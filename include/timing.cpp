#include "timing.h"

// Includes the high performance timer (c. 4ms).
#include <chrono>
#ifdef __aarch64__
#else
#include <windows.h>
#endif

// Hold internal timing data for the perfomrance counter.
static bool qpcFlag;
static double qpcFrequency;

// Internal time and clock access functions
unsigned systemTime() {
#ifdef __aarch64__
    // Don't know how to do the same for this architecture
    return (unsigned)(std::chrono::high_resolution::clock::now().time_since_epoch().count() * qpcFrequency);
#else
    static long long qpcMillisPerTick;
    if (qpcFlag) {
        QueryPerformanceCounter((LARGE_INTEGER*)&qpcMillisPerTick);

        return (unsigned)(qpcMillisPerTick * qpcFrequency);
    } else {
        return unsigned(timeGetTime());
    }
#endif
}

unsigned TimingData::getTime() { return systemTime(); }

unsigned long systemClock() {
    unsigned val;
#ifdef __aarch64__
    asm volatile("mrs %0, cntvct_el0" : "=r"(val));
#else
    val = __rdtsc();
#endif
    return val;
}

unsigned long TimingData::getClock() { return systemClock(); }

// Sets up the timing system and registers the performance timer.
void initTime() {
#ifdef __aarch64__
    // Don't know how to do the same for this architecture.
    qpcFrequency = 0.0000011;
#else
    long long time;

    qpcFlag = (QueryPerformanceFrequency((LARGE_INTEGER*)&time) > 0);

    // Check if we have access to the performance counter at this resolution.

    if (qpcFlag) qpcFrequency = 0.0001;//1000.0 / time;
#endif
}

// Holds the global frame time that is passed around
static TimingData* timingData = nullptr;

// Retrieves the global frame info instance
TimingData& TimingData::get() { return (TimingData&)*timingData; }

// Updates the global frame information. Should be called once per frame.
void TimingData::update() {
    if (!timingData) return;

    // Advance the frame number.
    if (!timingData->isPaused) {
        timingData->frameNumber++;
    }

    // Update the timing information.
    unsigned thisTime = systemTime();
    timingData->lastFrameDuration = thisTime - timingData->lastFrameTimestamp;
    timingData->lastFrameTimestamp = thisTime;

    // Update the tick information.
    unsigned long thisClock = systemClock();
    timingData->lastFrameClockTicks = thisClock - timingData->lastFrameClockstamp;
    timingData->lastFrameClockstamp = thisClock;

    // Update the RWA frame rate if we are able to.
    if (timingData->frameNumber > 1) {
        if (timingData->averageFrameDuration <= 0) {
            timingData->averageFrameDuration = (double)timingData->lastFrameDuration;
        } else {
            // RWA over 100 frames.
            timingData->averageFrameDuration *= 0.99;
            timingData->averageFrameDuration += 0.01 * (double)timingData->lastFrameDuration;

            // Invert to get FPS
            timingData->fps = (float)(1000.0 / timingData->averageFrameDuration);
        }
    }
}

void TimingData::init() {
    // Set up the timing system.
    initTime();

    // Create the frame info object
    if (!timingData) timingData = new TimingData();

    // Set up the frame info structure.
    timingData->frameNumber = 0;

    timingData->lastFrameTimestamp = systemTime();
    timingData->lastFrameDuration = 0;

    timingData->lastFrameClockstamp = systemClock();
    timingData->lastFrameClockTicks = 0;

    timingData->isPaused = false;

    timingData->averageFrameDuration = 0;
    timingData->fps = 0;
}

void TimingData::deinit() {
    delete timingData;
    timingData = NULL;
}