struct TimingData {
	// The current render frame. this simply increments.
	unsigned frameNumber;

	// The timestamp when the last frame ended.
	unsigned lastFrameTimestamp;

	// The duration of the last frame in ms.
	unsigned lastFrameDuration;

	// The clockstamp of the end of the last frame.
	unsigned long lastFrameClockstamp;

	// The duration of the last frame in clock ticks.
	unsigned long lastFrameClockTicks;

	bool isPaused;

	double averageFrameDuration;

	float fps;

	// Gets the global timing data object.
	static TimingData& get();

	// Updates the timing system, should be called once per frame.
	static void update();

	// Initialises the frame informtaion system. Use the overall init function to set up all modules.
	static void init();
	static void deinit();

	// Gets the global system time in ms, in the best resolution possible.
	static unsigned getTime();

	// Gets the clock ticks since process start.
	static unsigned long getClock();

private:
	TimingData() {}
	TimingData(const TimingData&) {}
	TimingData& operator=(const TimingData&) {}
};