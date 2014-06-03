#include "stdafx.h"
#include "FpsCamera.h"

Vector3 CFpsCamera::UP_VECTOR(0, 1, 0);


CFpsCamera::CFpsCamera()
{
	m_lookFrom.Set(0, 0, -100);
	m_lookAt.Set(0, 0, 0);
}

CFpsCamera::~CFpsCamera()
{

}

Vector3 CFpsCamera::GetViewDir()
{
	Vector3 viewDir = m_lookAt - m_lookFrom;
	viewDir.Normalize();
	return viewDir;
}

Vector3 CFpsCamera::GetLeft()
{
	//lo saco de la matriz del frame anterior
	Vector3 left(m_viewMatrix.M11, m_viewMatrix.M21, m_viewMatrix.M31);
	left.Normalize();
	return left;
}

Vector3 CFpsCamera::GetUp()
{
	Vector3 up(m_viewMatrix.M12, m_viewMatrix.M22, m_viewMatrix.M32);
	up.Normalize();
	return up;
}

void CFpsCamera::UpdateCamera()
{
	float elapsed_time = _engine.elapsed_time;
	if (m_animate)
	{
		//Muevo El ojo de la camara hacia el punto destino
		m_deltaAnimTime += elapsed_time;

		float deltaMove = saturate(m_deltaAnimTime / m_animTime);
		m_lookFrom = m_startPos*(1 - deltaMove) + m_endPos*deltaMove;
		m_lookAt = m_startTarget*(1 - deltaMove) + m_endTarget*deltaMove;

		if (m_deltaAnimTime >= m_animTime)
		{
			m_animate = false;
			m_lookFrom = m_endPos;
			m_lookAt = m_endTarget;
			m_deltaAnimTime = 0;
		}
	}

	//Obtener variacion XY del mouse
	Vector3 dir = GetViewDir();
	Vector3 ndir = dir*-1;

	float beta = atan2(ndir.Y, sqrt(ndir.X*ndir.X + ndir.Z*ndir.Z))*FastMath::RADIANS_TO_DEGREES;
	float rotX = 0;
	float rotY = 0;
	if (!m_cameraBlocked)
	{
		Vector3 dm = InputManager::m_delta_mouse;

		if (InputManager::IsLButtonDown() || m_captureMouse)
		{
			//roto solo si el boton del mouse esta apretado
			rotX = dm.X * m_rotationSpeed;
			rotY = dm.Y * m_rotationSpeed;

			if (rotY + beta > 90 - 1)
			{
				rotY = 90 - beta - 1;
			}
			if (rotY + beta < -90 + 1)
			{
				rotY = -90 - beta + 1;
			}

		}

		if (dm.Z != 0)
		{
			//avanzo y retrocedo con la rueda del mouse
			float distancia = (m_lookAt - m_lookFrom).Length();
			float deltamove = dm.Z * m_wheelSpeed;

			if (distancia - deltamove < 1)
				deltamove = distancia - 1;

			m_lookFrom += dir*deltamove;
		}

		if (InputManager::IsPressed(DInputKey::Key_C))
		{
			m_endPos = m_lookFrom;
			m_endTarget = m_lookAt;
		}

		if (InputManager::IsPressed(DInputKey::Key_P))
		{
			AnimateTo(m_endPos, m_endTarget);
		}

		if (InputManager::IsPressed(DInputKey::Key_M))
		{
			m_captureMouse = !m_captureMouse;
		}

		if (m_captureMouse)
		{
			//TODO: Falta convertir el la posicion en absoluta, ahora esta relativa a la camara y no queda centrada
			SetCursorPos(_engine.screenWidth / 2, _engine.screenHeight / 2);
		}


		if (InputManager::IsWheelButtonDown())
		{
			//Hace el pan del mouse
			Vector3 delta_pan = GetLeft() * (dm.X * m_panSpeed);
			delta_pan += GetUp() * (dm.Y * m_panSpeed);
			m_lookAt += delta_pan;
			m_lookFrom += delta_pan;
		}

		if (InputManager::IsDown(DInputKey::Key_W))
		{
			Vector3 move = dir*m_moveSpeed*elapsed_time;
			//anulo el movimiento en Y
			move.Y = 0;
			m_lookAt += move;
			m_lookFrom += move;
		}

		if (InputManager::IsDown(DInputKey::Key_S))
		{
			Vector3 move = dir*-m_moveSpeed*elapsed_time;
			//anulo el movimiento en Y
			move.Y = 0;
			m_lookAt += move;
			m_lookFrom += move;
		}

		if (InputManager::IsDown(DInputKey::Key_A))
		{
			Vector3 move = GetLeft()*m_moveSpeed*elapsed_time;
			//anulo el movimiento en Y
			move.Y = 0;
			m_lookAt += move;
			m_lookFrom += move;
		}

		if (InputManager::IsDown(DInputKey::Key_D))
		{
			Vector3 move = GetLeft()*-m_moveSpeed*elapsed_time;
			//anulo el movimiento en Y
			move.Y = 0;
			m_lookAt += move;
			m_lookFrom += move;
		}

		if (InputManager::IsDown(DInputKey::Key_Space))
		{
			Vector3 move = UP_VECTOR*m_jumpSpeed*elapsed_time;
			m_lookAt += move;
			m_lookFrom += move;
		}

		if (InputManager::IsDown(DInputKey::Key_LeftControl) || InputManager::IsDown(DInputKey::Key_RightControl))
		{
			Vector3 move = UP_VECTOR*-m_jumpSpeed*elapsed_time;
			m_lookAt += move;
			m_lookFrom += move;
		}

	}

	//creo un vector perpendicular a la direccion de la camara y la direccion arriba para rotar sonbre ese eje.
	if (rotX != 0 || rotY != 0)
	{
		Matrix rotMat = Matrix::SRotationAxis(GetLeft(), rotY*FastMath::DEGREES_TO_RADIANS) *
			Matrix::SRotationAxis(UP_VECTOR, -rotX*FastMath::DEGREES_TO_RADIANS);

		Vector3 dif = m_lookFrom - m_lookAt;

		m_lookFrom = m_lookAt + Vector3::TransformCoordinate(dif, rotMat).XYZ();
	}

	m_viewMatrix.LookAtLH(m_lookAt, m_lookFrom, UP_VECTOR);
}

void CFpsCamera::AnimateTo(Vector3 newLookFrom, Vector3 newLookAt)
{
	m_startPos = m_lookFrom;
	m_endPos = newLookFrom;
	m_startTarget = m_lookAt;
	m_endTarget = newLookAt;
	m_animate = true;
	m_deltaAnimTime = 0.0;
}