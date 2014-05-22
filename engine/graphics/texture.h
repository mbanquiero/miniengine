#pragma once
#include "dxgi.h"
#include "d3dcommon.h"
#include "d3dx10Math.h"
#include "d3dx9.h"


class CTexture
{
	public:
		int imgWidth , imgHeight;
		char name[MAX_PATH];
		LPDIRECT3DTEXTURE9      g_pTexture;
		CTexture();
		~CTexture();
		virtual void Release();
};


