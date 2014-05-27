#include "stdafx.h"
#include "InputManager.h"


KeyboardState InputManager::m_antKeyboardState = { 0 };
KeyboardState InputManager::m_keyboardState = { 0 };
MouseState InputManager::m_antMouseState = { 0 };
MouseState InputManager::m_mouseState = { 0 };
Vector3 InputManager::m_delta_mouse;

LPDIRECTINPUT8 InputManager::m_dinput = NULL;
LPDIRECTINPUTDEVICE8 InputManager::m_pKeyboard = NULL;
LPDIRECTINPUTDEVICE8 InputManager::m_pMouse = NULL;


bool InputManager::Init(void)
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_dinput, NULL);
	m_dinput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	m_dinput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);

	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	//m_pKeyboard->SetCooperativeLevel(hWnd, dwCoopFlags);
	//m_pMouse->SetCooperativeLevel(hWnd, dwCoopFlags);

	m_pKeyboard->Acquire();
	m_pMouse->Acquire();
	return true;
}

void InputManager::Shutdown(void)
{
	m_pKeyboard->Release();
	m_pMouse->Release();
}

void InputManager::Update()
{
	m_antKeyboardState = m_keyboardState;
	m_antMouseState = m_mouseState;

	m_pKeyboard->GetDeviceState(sizeof(m_keyboardState), m_keyboardState);
	m_pMouse->GetDeviceState(sizeof(m_mouseState), m_mouseState);

	m_delta_mouse.X = m_mouseState.X; -m_antMouseState.X;
	m_delta_mouse.Y = m_mouseState.Y; -m_antMouseState.Y;
	m_delta_mouse.Z = m_mouseState.Z; -m_antMouseState.Z;
}
