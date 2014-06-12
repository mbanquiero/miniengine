
// tronView.h: interfaz de la clase CtronView
//

#pragma once


class CtronView : public CView
{
protected: // Crear sólo a partir de serialización
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

// Implementación
public:
	virtual ~CtronView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignación de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Versión de depuración en tronView.cpp
inline CtronDoc* CtronView::GetDocument() const
   { return reinterpret_cast<CtronDoc*>(m_pDocument); }
#endif

