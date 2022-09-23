#pragma once

#include "geometric/point.hpp"

static constexpr auto pi = std::numbers::pi_v<GLfloat>;

class StickFigure {
public:
	struct Joints {
		GLfloat torsoHip{pi / 2};
		GLfloat torsoSpine{0};

		GLfloat leftArmShoulder{pi / 2};
		GLfloat leftArmElbow{0};
		GLfloat rightArmShoulder{-pi / 2};
		GLfloat rightArmElbow{0};

		GLfloat leftLegHip{pi * 3 / 4};
		GLfloat leftLegKnee{0};
		GLfloat rightLegHip{-pi * 3 / 4};
		GLfloat rightLegKnee{0};
	};

	struct Lenghts {
		GLfloat torsoLower{0.1F};
		GLfloat torsoUpper{0.2F};

		GLfloat armUpper{0.1F};
		GLfloat armLower{0.1F};

		GLfloat legUpper{0.15F};
		GLfloat legLower{0.15F};
	};

	//[[nodiscard]] const Joints &getJoints() const { return joints_; }
	//[[nodiscard]] const Lenghts &getLenghts() const { return lenghts_; }

	Point2<GLfloat> position;
	Joints joints;
	Lenghts lenghts;
};
