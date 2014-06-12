
// tronView.h: interfaz de la clase CtronView
//

#pragma once


class CtronView : public CView
{
protected: // Crear s�lo a partir de serializaci�n
	CtronView();
	DECLARE_DYNCREATE(CtronView)

// Atributos
public:
	CtronDoc* GetDocument() const;

// Operaciones
public:

// Reemplazos
public:
	virtual void OnDraw(CDC* pDC);  // Reemplazado para dibujar esta vista
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementaci�n
public:
	virtual ~CtronView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignaci�n de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Versi�n de depuraci�n en tronView.cpp
inline CtronDoc* CtronView::GetDocument() const
   { return reinterpret_cast<CtronDoc*>(m_pDocument); }
#endif

