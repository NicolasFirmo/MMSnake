#include "game.h"

#include "stick_figure.h"

#include "window.h"

#include "events/mouse_event.h"

#include "renderer/renderer.h"

#include "utility/log.hpp"
#include "utility/point.hpp"
#include "utility/timer.h"
#include "utility/tracer.h"

bool Game::running = false;
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
	while (running) {
		profileTraceScope("game run loop");
		const auto deltaT = timer.getSecondsElapsed();
		timer.startCounting();
		debugLog("Game loop period: {}\n", deltaT);
		timer.syncThread(gameLoopPeriod);
	}
}

void Game::shutdown() {
	profileTraceFunc();

	running = false;
}

void Game::onEvent(Event &evt) {
	auto type = evt.getType();

	switch (type) {
	case Event::Type::mouseMove: {
		const auto [screenX, screenY] = static_cast<MouseMoveEvent &>(evt).pos;
		break;
	}
	default:
		break;
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

	Renderer::beginBatch();

	drawStickFigure(testStickFigure);

	Renderer::endBatch();
}

void Game::drawStickFigure(const StickFigure &stickFigure) {
	profileTraceFunc();

	// torso
	const auto &hip				= stickFigure.position;
	const auto &lowerTorsoAngle = stickFigure.joints.torsoHip;
	const auto spine =
		hip + Point2<GLfloat>::fromPolar(stickFigure.lenghts.torsoLower, lowerTorsoAngle);
	const auto upperTorsoAngle = lowerTorsoAngle + stickFigure.joints.torsoSpine;
	const auto shoulders =
		spine + Point2<GLfloat>::fromPolar(stickFigure.lenghts.torsoUpper, upperTorsoAngle);

	// arms
	const auto leftUpperArmAngle = upperTorsoAngle + stickFigure.joints.leftArmShoulder;
	const auto leftElbow =
		shoulders + Point2<GLfloat>::fromPolar(stickFigure.lenghts.armUpper, leftUpperArmAngle);
	const auto leftLowerArmAngle = leftUpperArmAngle + stickFigure.joints.leftArmElbow;
	const auto leftHand =
		leftElbow + Point2<GLfloat>::fromPolar(stickFigure.lenghts.armLower, leftLowerArmAngle);

	const auto rightUpperArmAngle = upperTorsoAngle + stickFigure.joints.rightArmShoulder;
	const auto rightElbow =
		shoulders + Point2<GLfloat>::fromPolar(stickFigure.lenghts.armUpper, rightUpperArmAngle);
	const auto rightLowerArmAngle = rightUpperArmAngle + stickFigure.joints.rightArmElbow;
	const auto rightHand =
		rightElbow + Point2<GLfloat>::fromPolar(stickFigure.lenghts.armLower, rightLowerArmAngle);

	// legs
	const auto leftUpperLegAngle = lowerTorsoAngle + stickFigure.joints.leftLegHip;
	const auto leftKnee =
		hip + Point2<GLfloat>::fromPolar(stickFigure.lenghts.legUpper, leftUpperLegAngle);
	const auto leftLowerLegAngle = leftUpperLegAngle + stickFigure.joints.leftLegKnee;
	const auto leftFoot =
		leftKnee + Point2<GLfloat>::fromPolar(stickFigure.lenghts.legLower, leftLowerLegAngle);

	const auto rightUpperLegAngle = lowerTorsoAngle + stickFigure.joints.rightLegHip;
	const auto rightKnee =
		hip + Point2<GLfloat>::fromPolar(stickFigure.lenghts.legUpper, rightUpperLegAngle);
	const auto rightLowerLegAngle = rightUpperLegAngle + stickFigure.joints.rightLegKnee;
	const auto rightFoot =
		rightKnee + Point2<GLfloat>::fromPolar(stickFigure.lenghts.legLower, rightLowerLegAngle);

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
