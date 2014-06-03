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
	float m_rotationSpeed = 0.5f;
	float m_wheelSpeed = 1.0f;
	float m_panSpeed = 1.0;
	float m_moveSpeed = 1000.0f;
	float m_jumpSpeed = 500.0f;

	float m_animTime = 1;
	float m_deltaAnimTime = 0;
	Vector3 m_endPos;
	Vector3 m_endTarget;
	Vector3 m_startPos;
	Vector3 m_startTarget;
	bool m_animate = false;
	bool m_cameraBlocked = false;
	bool m_captureMouse = false;

	CFpsCamera();

	~CFpsCamera();

	virtual Vector3 GetViewDir();
	virtual Vector3 GetLeft();
	virtual Vector3 GetUp();
	virtual void UpdateCamera();
	virtual void AnimateTo(Vector3 newLookFrom, Vector3 newLookAt);
};



