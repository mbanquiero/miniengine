#pragma once

#include <../Include/dinput.h>
#include <math/vector3.h>

enum DInputKey
{
	Key_Escape = 1,
	Key_D1 = 2,
	Key_D2 = 3,
	Key_D3 = 4,
	Key_D4 = 5,
	Key_D5 = 6,
	Key_D6 = 7,
	Key_D7 = 8,
	Key_D8 = 9,
	Key_D9 = 10,
	Key_D0 = 11,
	Key_Minus = 12,
	Key_Equals = 13,
	Key_Back = 14,
	Key_BackSpace = 14,
	Key_Tab = 15,
	Key_Q = 16,
	Key_W = 17,
	Key_E = 18,
	Key_R = 19,
	Key_T = 20,
	Key_Y = 21,
	Key_U = 22,
	Key_I = 23,
	Key_O = 24,
	Key_P = 25,
	Key_LeftBracket = 26,
	Key_RightBracket = 27,
	Key_Return = 28,
	Key_LeftControl = 29,
	Key_A = 30,
	Key_S = 31,
	Key_D = 32,
	Key_F = 33,
	Key_G = 34,
	Key_H = 35,
	Key_J = 36,
	Key_K = 37,
	Key_L = 38,
	Key_SemiColon = 39,
	Key_Apostrophe = 40,
	Key_Grave = 41,
	Key_LeftShift = 42,
	Key_BackSlash = 43,
	Key_Z = 44,
	Key_X = 45,
	Key_C = 46,
	Key_V = 47,
	Key_B = 48,
	Key_N = 49,
	Key_M = 50,
	Key_Comma = 51,
	Key_Period = 52,
	Key_Slash = 53,
	Key_RightShift = 54,
	Key_Multiply = 55,
	Key_NumPadStar = 55,
	Key_LeftAlt = 56,
	Key_LeftMenu = 56,
	Key_Space = 57,
	Key_Capital = 58,
	Key_CapsLock = 58,
	Key_F1 = 59,
	Key_F2 = 60,
	Key_F3 = 61,
	Key_F4 = 62,
	Key_F5 = 63,
	Key_F6 = 64,
	Key_F7 = 65,
	Key_F8 = 66,
	Key_F9 = 67,
	Key_F10 = 68,
	Key_Numlock = 69,
	Key_Scroll = 70,
	Key_NumPad7 = 71,
	Key_NumPad8 = 72,
	Key_NumPad9 = 73,
	Key_NumPadMinus = 74,
	Key_Subtract = 74,
	Key_NumPad4 = 75,
	Key_NumPad5 = 76,
	Key_NumPad6 = 77,
	Key_Add = 78,
	Key_NumPadPlus = 78,
	Key_NumPad1 = 79,
	Key_NumPad2 = 80,
	Key_NumPad3 = 81,
	Key_NumPad0 = 82,
	Key_Decimal = 83,
	Key_NumPadPeriod = 83,
	Key_OEM102 = 86,
	Key_F11 = 87,
	Key_F12 = 88,
	Key_F13 = 100,
	Key_F14 = 101,
	Key_F15 = 102,
	Key_Kana = 112,
	Key_AbntC1 = 115,
	Key_Convert = 121,
	Key_NoConvert = 123,
	Key_Yen = 125,
	Key_AbntC2 = 126,
	Key_NumPadEquals = 141,
	Key_Circumflex = 144,
	Key_PrevTrack = 144,
	Key_At = 145,
	Key_Colon = 146,
	Key_Underline = 147,
	Key_Kanji = 148,
	Key_Stop = 149,
	Key_AX = 150,
	Key_Unlabeled = 151,
	Key_NextTrack = 153,
	Key_NumPadEnter = 156,
	Key_RightControl = 157,
	Key_Mute = 160,
	Key_Calculator = 161,
	Key_PlayPause = 162,
	Key_MediaStop = 164,
	Key_VolumeDown = 174,
	Key_VolumeUp = 176,
	Key_WebHome = 178,
	Key_NumPadComma = 179,
	Key_Divide = 181,
	Key_NumPadSlash = 181,
	Key_SysRq = 183,
	Key_RightAlt = 184,
	Key_RightMenu = 184,
	Key_Pause = 197,
	Key_Home = 199,
	Key_Up = 200,
	Key_UpArrow = 200,
	Key_PageUp = 201,
	Key_Prior = 201,
	Key_Left = 203,
	Key_LeftArrow = 203,
	Key_Right = 205,
	Key_RightArrow = 205,
	Key_End = 207,
	Key_Down = 208,
	Key_DownArrow = 208,
	Key_Next = 209,
	Key_PageDown = 209,
	Key_Insert = 210,
	Key_Delete = 211,
	Key_LeftWindows = 219,
	Key_RightWindows = 220,
	Key_Apps = 221,
	Key_Power = 222,
	Key_Sleep = 223,
	Key_Wake = 227,
	Key_WebSearch = 229,
	Key_WebFavorites = 230,
	Key_WebRefresh = 231,
	Key_WebStop = 232,
	Key_WebForward = 233,
	Key_WebBack = 234,
	Key_MyComputer = 235,
	Key_Mail = 236,
	Key_MediaSelect = 237,
};

struct KeyboardState
{
	bool keys[256];

	operator void*() { return (void *)&keys; }
	bool operator [](DInputKey key) const { return keys[(int)key]; }
	bool operator [](int key) const  { return keys[key]; };
};

#define MOUSE_LEFT_BUTTON 0
#define MOUSE_RIGHT_BUTTON 1
#define MOUSE_WHEEL_BUTTON 2
#define MOUSE_OTHER_BUTTON 3

struct MouseState
{
	int X;
	int Y;
	int Z;
	BYTE mouseButtons[4];

	BYTE * GetMouseButtons(){ return mouseButtons; }
	operator void*() { return (void *)this; }
};

class InputManager
{
public:
	static KeyboardState m_antKeyboardState;
	static KeyboardState m_keyboardState;
	static MouseState m_antMouseState;
	static MouseState m_mouseState;
	static Vector3 m_delta_mouse;

	static LPDIRECTINPUT8 m_dinput;
	static LPDIRECTINPUTDEVICE8 m_pKeyboard;
	static LPDIRECTINPUTDEVICE8 m_pMouse;

	static bool Init( void );
	static void Shutdown(void);
	static void Update();
	static bool IsDown(DInputKey key) { return m_keyboardState[key]; };
	static bool IsPressed(int key) { return m_antKeyboardState[key] && !m_keyboardState[key]; };
	static bool IsLButtonDown() { return m_mouseState.mouseButtons[MOUSE_LEFT_BUTTON]; };
	static bool IsLButtonPressed() { return m_antMouseState.mouseButtons[MOUSE_LEFT_BUTTON] && !m_mouseState.mouseButtons[MOUSE_LEFT_BUTTON]; };
	static bool IsRButtonDown() { return m_mouseState.mouseButtons[MOUSE_RIGHT_BUTTON]; };
	static bool IsRButtonPressed() { return m_antMouseState.mouseButtons[MOUSE_RIGHT_BUTTON] && !m_mouseState.mouseButtons[MOUSE_RIGHT_BUTTON]; };
	static bool IsWheelButtonDown() { return m_mouseState.mouseButtons[MOUSE_WHEEL_BUTTON]; };
	static bool IsWheelButtonPressed() { return m_antMouseState.mouseButtons[MOUSE_WHEEL_BUTTON] && !m_mouseState.mouseButtons[MOUSE_WHEEL_BUTTON]; };
};

