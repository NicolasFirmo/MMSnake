#include "game.h"

#include "stick_figure.h"

#include "window.h"

#include "events/mouse_event.h"

#include "renderer/renderer.h"

#include "utility/log.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

#include "geometric/point.hpp"

#include "core/sleeper.h"

bool Game::running = false;

static Point2<double> mouseWorldPosition;

static StickFigure testStickFigure;

void Game::init() {
	profileTraceFunc();

	running = true;
	std::thread gameLoop{run};
	gameLoop.detach();
}

void Game::run() {
	profileTraceFunc();

	Timer timer;
	Sleeper sleeper;
	while (running) {
		profileTraceScope("game run loop");

		// const auto deltaT = timer.getSecondsElapsed();
		timer.startCounting();
		// fmt::print("Game loop period: {}\n", deltaT);

		sleeper.preciseSync(2500, timer);
	}
}

void Game::shutdown() {
	profileTraceFunc();

	running = false;
}

void Game::onEvent(Event& evt) {
	auto type = evt.getType();

	switch (type) {
	case Event::Type::mouseMove: {
		const auto& mouseMoveEvt	  = static_cast<MouseMoveEvent&>(evt);
		const auto [screenX, screenY] = mouseMoveEvt.pos;
		mouseWorldPosition			  = {.x = Window::aspectRatio() *
											  (screenX / double(Window::width()) * 2.0 - 1.0),
										 .y = -(screenY / double(Window::height()) * 2.0 - 1.0)};
		break;
	}
	case Event::Type::mouseButton: {
		const auto& mouseButtonEvt = static_cast<MouseButtonEvent&>(evt);
		if (mouseButtonEvt.action == MouseAction::pressed)
			testStickFigure.position = mouseWorldPosition;
	}
	default: break;
	}
}

void Game::onImGui() {
	ImGui::Begin("Stick figure body");

	ImGui::SliderFloat2("Torso", &testStickFigure.joints.torsoHip, -pi, pi);

	ImGui::SliderFloat2("Left arm", &testStickFigure.joints.leftArmShoulder, -pi, pi);
	ImGui::SliderFloat2("Right arm", &testStickFigure.joints.rightArmShoulder, -pi, pi);

	ImGui::SliderFloat2("Left leg", &testStickFigure.joints.leftLegHip, -pi, pi);
	ImGui::SliderFloat2("Right leg", &testStickFigure.joints.rightLegHip, -pi, pi);

	ImGui::End();
}

void Game::render() {
	profileTraceFunc();

	Renderer::beginScene();

	drawStickFigure(testStickFigure);

	Renderer::endScene();
}

void Game::drawStickFigure(const StickFigure& stickFigure) {
	profileTraceFunc();

	// torso
	const auto& hip				= stickFigure.position;
	const auto& lowerTorsoAngle = stickFigure.joints.torsoHip;
	const auto spine		   = hip + Point2Polar{stickFigure.lenghts.torsoLower, lowerTorsoAngle};
	const auto upperTorsoAngle = lowerTorsoAngle + stickFigure.joints.torsoSpine;
	const auto shoulders = spine + Point2Polar{stickFigure.lenghts.torsoUpper, upperTorsoAngle};

	// arms
	const auto leftUpperArmAngle = upperTorsoAngle + stickFigure.joints.leftArmShoulder;
	const auto leftElbow = shoulders + Point2Polar{stickFigure.lenghts.armUpper, leftUpperArmAngle};
	const auto leftLowerArmAngle = leftUpperArmAngle + stickFigure.joints.leftArmElbow;
	const auto leftHand = leftElbow + Point2Polar{stickFigure.lenghts.armLower, leftLowerArmAngle};

	const auto rightUpperArmAngle = upperTorsoAngle + stickFigure.joints.rightArmShoulder;
	const auto rightElbow =
		shoulders + Point2Polar{stickFigure.lenghts.armUpper, rightUpperArmAngle};
	const auto rightLowerArmAngle = rightUpperArmAngle + stickFigure.joints.rightArmElbow;
	const auto rightHand =
		rightElbow + Point2Polar{stickFigure.lenghts.armLower, rightLowerArmAngle};

	// legs
	const auto leftUpperLegAngle = lowerTorsoAngle + stickFigure.joints.leftLegHip;
	const auto leftKnee = hip + Point2Polar{stickFigure.lenghts.legUpper, leftUpperLegAngle};
	const auto leftLowerLegAngle = leftUpperLegAngle + stickFigure.joints.leftLegKnee;
	const auto leftFoot = leftKnee + Point2Polar{stickFigure.lenghts.legLower, leftLowerLegAngle};

	const auto rightUpperLegAngle = lowerTorsoAngle + stickFigure.joints.rightLegHip;
	const auto rightKnee = hip + Point2Polar{stickFigure.lenghts.legUpper, rightUpperLegAngle};
	const auto rightLowerLegAngle = rightUpperLegAngle + stickFigure.joints.rightLegKnee;
	const auto rightFoot =
		rightKnee + Point2Polar{stickFigure.lenghts.legLower, rightLowerLegAngle};

	static constexpr GLfloat thickness = 0.01F;
	Renderer::drawLine(hip, spine, thickness);
	Renderer::drawLine(spine, shoulders, thickness);

	Renderer::drawLine(shoulders, leftElbow, thickness);
	Renderer::drawLine(leftElbow, leftHand, thickness);
	Renderer::drawLine(shoulders, rightElbow, thickness);
	Renderer::drawLine(rightElbow, rightHand, thickness);

	Renderer::drawLine(hip, leftKnee, thickness);
	Renderer::drawLine(leftKnee, leftFoot, thickness);
	Renderer::drawLine(hip, rightKnee, thickness);
	Renderer::drawLine(rightKnee, rightFoot, thickness);
}