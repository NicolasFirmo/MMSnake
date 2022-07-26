#include "app.h"

#include "utility/tracer.h"

int main(int /*argc*/, char * /*argv*/[]) {
	Tracer::begin("profile.json");

	if (const auto exitCode = App::init(); exitCode != App::ExitCode::success)
		return static_cast<int>(exitCode);

	const auto exitCode = App::run();

	Tracer::end();

	return static_cast<int>(exitCode);
}