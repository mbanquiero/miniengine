
// tronView.cpp: implementación de la clase CtronView
//

#include "stdafx.h"
// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de búsqueda, y permiten compartir código de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "tron.h"
#endif

#include "tronDoc.h"
#include "tronView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtronView

IMPLEMENT_DYNCREATE(CtronView, CView)

BEGIN_MESSAGE_MAP(CtronView, CView)
END_MESSAGE_MAP()

// Construcción o destrucción de CtronView

CtronView::CtronView()
{
	// TODO: agregar aquí el código de construcción

}

CtronView::~CtronView()
{
}

BOOL CtronView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificar aquí la clase Window o los estilos cambiando
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Dibujo de CtronView

void CtronView::OnDraw(CDC* /*pDC*/)
{
	CtronDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: agregar aquí el código de dibujo para datos nativos
}


// Diagnósticos de CtronView

#ifdef _DEBUG
void CtronView::AssertValid() const
{
	CView::AssertValid();
}

void CtronView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtronDoc* CtronView::GetDocument() const // La versión de no depuración es en línea
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtronDoc)));
	return (CtronDoc*)m_pDocument;
}
#endif //_DEBUG


// Controladores de mensaje de CtronView
