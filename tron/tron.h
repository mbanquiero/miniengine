
// tron.h: archivo de encabezado principal para la aplicación tron
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // Símbolos principales


// CtronApp:
// Consulte la sección tron.cpp para obtener información sobre la implementación de esta clase
//

class CtronApp : public CWinApp
{
public:
	CtronApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementación
	COleTemplateServer m_server;
		// Objeto de servidor para la creación de documentos
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtronApp theApp;
