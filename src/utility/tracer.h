#pragma once

class Tracer {
public:
	class Timer {
	public:
		using clock = std::chrono::high_resolution_clock;

		Timer(const char *location);
		~Timer();

		Timer(const Timer &)			= delete;
		Timer(Timer &&)					= delete;
		Timer &operator=(const Timer &) = delete;
		Timer &operator=(Timer &&)		= delete;

	private:
		const char *location_;
		clock::time_point startTime_;
	};

	static void begin(const std::string &filepath);
	static void end();

	[[nodiscard]] static Timer
	trace(std::source_location location = std::source_location::current());
	[[nodiscard]] static Timer trace(const char *location);

private:
	static std::ofstream file;
	static std::mutex fileMutex;
};