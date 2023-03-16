#include "tracer.h"

#include "core/assert.h"

std::ofstream Tracer::file;
std::mutex Tracer::fileMutex;

std::atomic<Tracer::Timer::clock::time_point> s_last_timer_start_time = Tracer::Timer::clock::now();

Tracer::Timer::Timer(const char* location) : location_(location), startTime_(clock::now()) {
	if (startTime_ >= s_last_timer_start_time.load(std::memory_order_acquire))
		s_last_timer_start_time.store(startTime_, std::memory_order_release);

	while (!s_last_timer_start_time.compare_exchange_weak(
		startTime_, startTime_ + std::chrono::microseconds(1), std::memory_order_release,
		std::memory_order_acquire))
		;
}

Tracer::Timer::~Timer() {
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(
						   (clock::now() - startTime_))
						   .count();
	auto startTime = std::chrono::duration_cast<std::chrono::microseconds>(
						 startTime_.time_since_epoch())
						 .count();

	std::lock_guard lock{fileMutex};

	file << ",{";
	file << "\"cat\":\"function\",";
	file << "\"dur\":" << elapsedTime << ',';
	file << "\"name\":\"" << location_ << "\",";
	file << "\"ph\":\"X\",";
	file << "\"pid\":0,";
	file << "\"tid\":" << std::this_thread::get_id() << ",";
	file << "\"ts\":" << startTime;
	file << "}";

	file.flush();
}

void Tracer::begin(const std::string& filepath) {
	std::lock_guard lock{fileMutex};

	debugAssert(!file.is_open(),
				"Tracer::begin was called a second time before a call to Tracer::end!");

	file.open(filepath);

	debugAssert(file.is_open(), fmt::format("Could not open {} tracing file!", filepath));

	file << "{\"otherData\": {},\"traceEvents\":[{}";
	file.flush();
}

void Tracer::end() {
	std::lock_guard lock{fileMutex};

	file << "]}";
	file.flush();
	file.close();
}

Tracer::Timer Tracer::trace(const char* location) {
	return location;
}
