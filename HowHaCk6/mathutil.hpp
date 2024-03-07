#pragma once
#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "sourcesdk/sdk.h"

namespace HowHack {
	float AngleNormalize(float angle)
	{
		angle = fmodf(angle, 360.0f);
		if (angle > 180)
		{
			angle -= 360;
		}
		if (angle < -180)
		{
			angle += 360;
		}
		return angle;
	}
	float AngleNormalizePositive(float angle)
	{
		angle = fmodf(angle, 360.0f);

		if (angle < 0.0f)
		{
			angle += 360.0f;
		}

		return angle;
	}
	float AngleDifference(float destAngle, float srcAngle)
	{
		float delta;

		delta = fmodf(destAngle - srcAngle, 360.0f);
		if (destAngle > srcAngle)
		{
			if (delta >= 180)
				delta -= 360;
		}
		else
		{
			if (delta <= -180)
				delta += 360;
		}
		return delta;
	}
	QAngle FixAngles(QAngle angles) {
		angles.x = AngleNormalize(angles.x);
		angles.y = AngleNormalize(angles.y);
		if (angles.x > 89.f)
			angles.x = 89.f;
		else if (angles.x < -89.f)
			angles.x = -89.f;
		return angles;
	}
	QAngle FixAnglePositive(QAngle angles) {
		angles.x = AngleNormalizePositive(angles.x);
		angles.y = AngleNormalizePositive(angles.y);
		angles.z = AngleNormalizePositive(angles.z);
		return angles;
	}
	QAngle GetAngle(Vector source, Vector target) {
		QAngle OutputAngle;
		VectorAngles(target - source, OutputAngle);
		return OutputAngle;
	}

	Vector Forward(QAngle ang) {
		ang = FixAngles(ang);
		float radx = DEG2RAD(ang.x);
		float rady = DEG2RAD(ang.y);

		return Vector(cos(radx) * cos(rady), cos(radx) * sin(rady), sin(radx));
	}

	void CorrectMovement(CUserCmd* pCmd, QAngle oOldAngle) {
		float deltaView;
		float yaw[2];

		float pitch = fmodf(AngleNormalizePositive(pCmd->viewangles.x), 360);

		yaw[0] = AngleNormalizePositive(oOldAngle.y);
		yaw[1] = AngleNormalizePositive(pCmd->viewangles.y);

		if (yaw[1] < yaw[0])
			deltaView = abs(yaw[1] - yaw[0]);
		else
			deltaView = 360.0f - abs(yaw[0] - yaw[1]);

		deltaView = 360.0f - deltaView;

		float fwdmov, sdmov; fwdmov = pCmd->forwardmove; sdmov = pCmd->sidemove;

		pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fwdmov + cos(DEG2RAD(deltaView + 90.f)) * sdmov;
		pCmd->sidemove = sin(DEG2RAD(deltaView)) * fwdmov + sin(DEG2RAD(deltaView + 90.f)) * sdmov;
	}
}

#endif