
// tronDoc.h: interfaz de la clase CtronDoc
//


#pragma once


class CtronDoc : public CDocument
{
protected: // Crear s�lo a partir de serializaci�n
	CtronDoc();
	DECLARE_DYNCREATE(CtronDoc)

// Atributos
public:

// Operaciones
public:

// Reemplazos
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementaci�n
public:
	virtual ~CtronDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignaci�n de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()

	// Funciones de asignaci�n de env�o OLE generadas

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
	// Funci�n auxiliar que establece contenido de b�squeda para un controlador de b�squeda
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
