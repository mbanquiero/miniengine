#pragma once
#include "dxgi.h"
#include "d3dcommon.h"
#include "d3dx10Math.h"
#include "d3dx9.h"

typedef struct MATERIAL {
	char name[MAX_PATH];
	// texturas
	int cant_texturas;
	char texture_name[MAX_PATH][8];
	char nro_textura[8];
	// parametros
	int cant_param;
	char param_name[32][8];
	HANDLE param_handle[8];		// TODO

} MATERIAL;


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


