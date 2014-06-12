
// tron.cpp : define los comportamientos de las clases para la aplicaci�n.
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
	// Comandos de documento est�ndar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// Construcci�n de CtronApp

CtronApp::CtronApp()
{
	// TODO: reemplace la cadena de identificador de aplicaci�n siguiente por una cadena de identificador �nico; el formato
	// recomendado para la cadena es NombreCompa��a.NombreProducto.Subproducto.Informaci�nDeVersi�n
	SetAppID(_T("tron.AppID.NoVersion"));

	// TODO: agregar aqu� el c�digo de construcci�n,
	// Colocar toda la inicializaci�n importante en InitInstance
}

// El �nico objeto CtronApp

CtronApp theApp;
// Este identificador se gener� para que sea �nico para la aplicaci�n desde el punto de vista estad�stico
// Puede cambiarlo si prefiere elegir un identificador espec�fico

// {0C29F21C-B9DF-4DC1-A36A-C2E61D3B9BE0}
static const CLSID clsid =
{ 0xC29F21C, 0xB9DF, 0x4DC1, { 0xA3, 0x6A, 0xC2, 0xE6, 0x1D, 0x3B, 0x9B, 0xE0 } };

const GUID CDECL _tlid = { 0x2FAAB5C2, 0x195B, 0x4CFD, { 0xAD, 0x8D, 0x73, 0xA4, 0xD1, 0x77, 0x9D, 0xB } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// Inicializaci�n de CtronApp

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

	// Inicializaci�n est�ndar
	// Si no utiliza estas caracter�sticas y desea reducir el tama�o
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicializaci�n espec�ficas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuraci�n
	// TODO: debe modificar esta cadena para que contenga informaci�n correcta
	// como el nombre de su compa��a u organizaci�n
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI est�ndar (incluidas las de la lista MRU)


	// Registrar las plantillas de documento de la aplicaci�n. Las plantillas de documento
	//  sirven como conexi�n entre documentos, ventanas de marco y vistas
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
	//  en nombre de contenedores  OLE de solicitud utilizando informaci�n
	//  especificada en la plantilla de documento
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
		// Nota: las aplicaciones SDI s�lo registran los objetos de servidor si el modificador
		//   /Embedding o /Automation est� presente en la l�nea de comandos


	// Analizar l�nea de comandos para comandos Shell est�ndar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// La aplicaci�n se inici� con el modificador /Embedding o /Automation.
	// Ejecutar la aplicaci�n como servidor de automatizaci�n.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Registrar todos los generadores de servidores OLE mientras se ejecutan. De este modo se habilitan
		//  las bibliotecas OLE para crear objetos desde otras aplicaciones
		COleTemplateServer::RegisterAll();

		// No mostrar la ventana principal
		return TRUE;
	}
	// La aplicaci�n se inici� con el modificador /Unregserver o /Unregister. Anular el registro de
	// la biblioteca de tipos. Se producir�n otras cancelaciones de registro en ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// La aplicaci�n se inici� en modo independiente o con otros modificadores (por ejemplo /Register
	// o /Regserver). Actualizar entradas de Registro, incluida typelibrary.
	else
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}

	// Enviar comandos especificados en la l�nea de comandos. Devolver� FALSE si
	// la aplicaci�n se inici� con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Se ha inicializado la �nica ventana; mostrarla y actualizarla
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


// Cuadro de di�logo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de di�logo
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementaci�n
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

// Comando de la aplicaci�n para ejecutar el cuadro de di�logo
void CtronApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Controladores de mensaje de CtronApp



