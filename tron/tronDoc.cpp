
// tronDoc.cpp: implementación de la clase CtronDoc
//

#include "stdafx.h"
// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de búsqueda, y permiten compartir código de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "tron.h"
#endif

#include "tronDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CtronDoc

IMPLEMENT_DYNCREATE(CtronDoc, CDocument)

BEGIN_MESSAGE_MAP(CtronDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CtronDoc, CDocument)
END_DISPATCH_MAP()

// Nota: se agrega compatibilidad para IID_Itron para admitir enlaces con seguridad de tipos
//  desde VBA. IID debe coincidir con el id. GUID adjuntado a 
//  la interfaz dispinterface del archivo .IDL.

// {52C17E91-C83C-4876-8033-A47BB37EB8E1}
static const IID IID_Itron =
{ 0x52C17E91, 0xC83C, 0x4876, { 0x80, 0x33, 0xA4, 0x7B, 0xB3, 0x7E, 0xB8, 0xE1 } };

BEGIN_INTERFACE_MAP(CtronDoc, CDocument)
	INTERFACE_PART(CtronDoc, IID_Itron, Dispatch)
END_INTERFACE_MAP()


// Construcción o destrucción de CtronDoc

CtronDoc::CtronDoc()
{
	// TODO: agregar aquí el código de construcción único

	EnableAutomation();

	AfxOleLockApp();
}

CtronDoc::~CtronDoc()
{
	AfxOleUnlockApp();
}

BOOL CtronDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: agregar aquí código de reinicio
	// (los documentos SDI volverán a utilizar este documento)

	return TRUE;
}




// Serialización de CtronDoc

void CtronDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: agregar aquí el código de almacenamiento
	}
	else
	{
		// TODO: agregar aquí el código de carga
	}
}

#ifdef SHARED_HANDLERS

// Compatibilidad con miniaturas
void CtronDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modifique este código para dibujar los datos del documento
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Compatibilidad con controladores de búsqueda
void CtronDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Establezca contenido de búsqueda a partir de los datos del documento. 
	// Las partes de contenido deben ir separadas por ";"

	// Por ejemplo:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CtronDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Diagnósticos de CtronDoc

#ifdef _DEBUG
void CtronDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtronDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandos de CtronDoc
