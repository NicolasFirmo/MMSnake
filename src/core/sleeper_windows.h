#pragma once

class Sleeper {
public:
	static void init();

	Sleeper();
	~Sleeper();
	Sleeper(const Sleeper &) = delete;
	Sleeper(Sleeper &&);
	Sleeper &operator=(const Sleeper &) = delete;
	Sleeper &operator=(Sleeper &&);

	void sleep(int64_t microseconds);

private:
	HANDLE timer_;
};