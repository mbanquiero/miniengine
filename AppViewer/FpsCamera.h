#pragma once

#include "math\Vector3.h"
#include "math\Matrix.h"
#include "math\FastMath.h"
#include "InputManager.h"


class CFpsCamera
{
public:

	static Vector3 UP_VECTOR;
	Vector3 m_lookFrom;
	Vector3 m_lookAt;
	Matrix m_viewMatrix;
	float m_rotationSpeed;
	float m_wheelSpeed;
	float m_panSpeed;
	float m_moveSpeed;
	float m_jumpSpeed;

	float m_animTime;
	float m_deltaAnimTime;
	Vector3 m_endPos;
	Vector3 m_endTarget;
	Vector3 m_startPos;
	Vector3 m_startTarget;
	bool m_animate;
	bool m_cameraBlocked;
	bool m_captureMouse;

	CFpsCamera();

	~CFpsCamera();

	virtual Vector3 GetViewDir();
	virtual Vector3 GetLeft();
	virtual Vector3 GetUp();
	virtual void UpdateCamera();
	virtual void AnimateTo(Vector3 newLookFrom, Vector3 newLookAt);
};



