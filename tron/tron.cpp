
// tron.cpp : define los comportamientos de las clases para la aplicación.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "tron.h"
#include "MainFrm.h"

#include "tronDoc.h"
#include "tronView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtronApp

BEGIN_MESSAGE_MAP(CtronApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CtronApp::OnAppAbout)
	// Comandos de documento estándar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Construcción de CtronApp

CtronApp::CtronApp()
{
	// TODO: reemplace la cadena de identificador de aplicación siguiente por una cadena de identificador único; el formato
	// recomendado para la cadena es NombreCompañía.NombreProducto.Subproducto.InformaciónDeVersión
	SetAppID(_T("tron.AppID.NoVersion"));

	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}

// El único objeto CtronApp

CtronApp theApp;
// Este identificador se generó para que sea único para la aplicación desde el punto de vista estadístico
// Puede cambiarlo si prefiere elegir un identificador específico

// {0C29F21C-B9DF-4DC1-A36A-C2E61D3B9BE0}
static const CLSID clsid =
{ 0xC29F21C, 0xB9DF, 0x4DC1, { 0xA3, 0x6A, 0xC2, 0xE6, 0x1D, 0x3B, 0x9B, 0xE0 } };

const GUID CDECL _tlid = { 0x2FAAB5C2, 0x195B, 0x4CFD, { 0xAD, 0x8D, 0x73, 0xA4, 0xD1, 0x77, 0x9D, 0xB } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// Inicialización de CtronApp

BOOL CtronApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Inicializar bibliotecas OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);

	// Se necesita AfxInitRichEdit2() para usar el control RichEdit	
	// AfxInitRichEdit2();

	// Inicialización estándar
	// Si no utiliza estas características y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	// TODO: debe modificar esta cadena para que contenga información correcta
	// como el nombre de su compañía u organización
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI estándar (incluidas las de la lista MRU)


	// Registrar las plantillas de documento de la aplicación. Las plantillas de documento
	//  sirven como conexión entre documentos, ventanas de marco y vistas
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CtronDoc),
		RUNTIME_CLASS(CMainFrame),       // Ventana de marco SDI principal
		RUNTIME_CLASS(CtronView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// Conectar COleTemplateServer con la plantilla de documento
	//  COleTemplateServer crea nuevos documentos
	//  en nombre de contenedores  OLE de solicitud utilizando información
	//  especificada en la plantilla de documento
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
		// Nota: las aplicaciones SDI sólo registran los objetos de servidor si el modificador
		//   /Embedding o /Automation está presente en la línea de comandos


	// Analizar línea de comandos para comandos Shell estándar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// La aplicación se inició con el modificador /Embedding o /Automation.
	// Ejecutar la aplicación como servidor de automatización.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Registrar todos los generadores de servidores OLE mientras se ejecutan. De este modo se habilitan
		//  las bibliotecas OLE para crear objetos desde otras aplicaciones
		COleTemplateServer::RegisterAll();

		// No mostrar la ventana principal
		return TRUE;
	}
	// La aplicación se inició con el modificador /Unregserver o /Unregister. Anular el registro de
	// la biblioteca de tipos. Se producirán otras cancelaciones de registro en ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// La aplicación se inició en modo independiente o con otros modificadores (por ejemplo /Register
	// o /Regserver). Actualizar entradas de Registro, incluida typelibrary.
	else
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}

	// Enviar comandos especificados en la línea de comandos. Devolverá FALSE si
	// la aplicación se inició con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Se ha inicializado la única ventana; mostrarla y actualizarla
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CtronApp::ExitInstance()
{
	//TODO: controlar recursos adicionales que se hayan podido agregar
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Controladores de mensaje de CtronApp


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Comando de la aplicación para ejecutar el cuadro de diálogo
void CtronApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Controladores de mensaje de CtronApp



