
// stdafx.h: archivo de inclusi�n para archivos de inclusi�n est�ndar del sistema,
// o archivos de inclusi�n espec�ficos del proyecto utilizados frecuentemente,
// pero cambiados rara vez

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Excluir material rara vez utilizado de encabezados de Windows
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // Algunos constructores CString ser�n expl�citos

// Desactiva la ocultaci�n de MFC para algunos mensajes de advertencia comunes y, muchas veces, omitidos de forma consciente
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // Componentes principales y est�ndar de MFC
#include <afxext.h>         // Extensiones de MFC


#include <afxdisp.h>        // Clases de automatizaci�n de MFC



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Compatibilidad MFC para controles comunes de Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Compatibilidad MFC para controles comunes de Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // Compatibilidad de MFC con cintas y barras de control


#include <afxsock.h>            // Extensiones socket de MFC








