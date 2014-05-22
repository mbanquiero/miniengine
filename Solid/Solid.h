
// Solid.h: archivo de encabezado principal para la aplicaci�n Solid
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // S�mbolos principales


// CSolidApp:
// Consulte la secci�n Solid.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CSolidApp : public CWinAppEx
{
public:
	CSolidApp();


// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementaci�n
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSolidApp theApp;
