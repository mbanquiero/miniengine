
// tron.h: archivo de encabezado principal para la aplicaci�n tron
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // S�mbolos principales


// CtronApp:
// Consulte la secci�n tron.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CtronApp : public CWinApp
{
public:
	CtronApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementaci�n
	COleTemplateServer m_server;
		// Objeto de servidor para la creaci�n de documentos
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtronApp theApp;
