

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Thu Jun 12 00:19:57 2014
 */
/* Compiler settings for tron.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __tron_h_h__
#define __tron_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Itron_FWD_DEFINED__
#define __Itron_FWD_DEFINED__
typedef interface Itron Itron;

#endif 	/* __Itron_FWD_DEFINED__ */


#ifndef __CtronDoc_FWD_DEFINED__
#define __CtronDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CtronDoc CtronDoc;
#else
typedef struct CtronDoc CtronDoc;
#endif /* __cplusplus */

#endif 	/* __CtronDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __tron_LIBRARY_DEFINED__
#define __tron_LIBRARY_DEFINED__

/* library tron */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_tron;

#ifndef __Itron_DISPINTERFACE_DEFINED__
#define __Itron_DISPINTERFACE_DEFINED__

/* dispinterface Itron */
/* [uuid] */ 


EXTERN_C const IID DIID_Itron;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("52C17E91-C83C-4876-8033-A47BB37EB8E1")
    Itron : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ItronVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Itron * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Itron * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Itron * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Itron * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Itron * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Itron * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Itron * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } ItronVtbl;

    interface Itron
    {
        CONST_VTBL struct ItronVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Itron_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Itron_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Itron_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Itron_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Itron_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Itron_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Itron_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Itron_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CtronDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("0C29F21C-B9DF-4DC1-A36A-C2E61D3B9BE0")
CtronDoc;
#endif
#endif /* __tron_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


