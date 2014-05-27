#include "stdafx.h"
#include "RenderEngine.h"
#include "xstring.h"
#include "TGCViewer.h"


CRenderEngine::CRenderEngine()
{
	// dx
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
	g_pEffect = NULL;			
	g_pEffectStandard = NULL;	
	g_pFont = NULL;

	g_pPositionTexture = NULL;
	g_pPositionSurf = NULL;
	g_pColorTexture = NULL;
	g_pColorSurf = NULL;
	g_pNormalTexture = NULL;
	g_pNormalSurf = NULL;
	g_pDepthBuffer = NULL;
	g_pFullScreenRenderTarget = NULL;
	g_pFullScreenRenderTargetSurf = NULL;
	// propias
	cant_texturas = 0;
	cant_mesh = 0;
	total_time = 0;
	elapsed_time = 0;
	ftime = 0;
}

CRenderEngine::~CRenderEngine()
{
	if(g_pd3dDevice!=NULL)
		Release();
}


bool CRenderEngine::IsReady()
{
	return g_pd3dDevice!=NULL ? true : false;
}

void CRenderEngine::Create(HWND hwnd)
{
	// Inicializa el DirectX
	InitD3D(hwnd);
	// Inicializa el pipeline: load and compile shaders, vertex buffer, matrices de transformacion, etc
	InitPipeline();
}


void  CRenderEngine::InitD3D(HWND hWnd)
{
	// Inicializa el DirectX
	//HRESULT hr;
	// Create the D3D object.
	if( ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL)
	{
		return;
	}

	// Set up the structure used to create the D3DDevice
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	if(FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return;
	}

	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	g_pd3dDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS , TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
	g_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE );

	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE);

	// D3DTADDRESS_WRAP
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);		
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);

	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

	// habilito las tranparencias
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_BLENDDIFFUSEALPHA);
	// Color Final = (Source * A) + (Dest * (1-A))
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);		// Source * A
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);	// Dest * (1-A)
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);			// Suma ambos terminos
	g_pd3dDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x0000000F);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);


	// Inicializo el Viewport
	D3DVIEWPORT9 viewport;
	ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	viewport.X = 0;
	viewport.Y = 0;
	screenWidth = viewport.Width = d3dpp.BackBufferWidth;
	screenHeight = viewport.Height = d3dpp.BackBufferHeight;
	g_pd3dDevice->SetViewport(&viewport);

	// Creo el sprite para 2d 
	D3DXCreateSprite(g_pd3dDevice,&g_pSprite);

	// Texto
	D3DXCreateFont( g_pd3dDevice ,            // D3D device
		14,					// Height
		0,                     // Width
		FW_LIGHT,               // Weight
		0,                     // MipLevels, 0 = autogen mipmaps
		FALSE,                 // Italic
		DEFAULT_CHARSET,       // CharSet
		OUT_DEFAULT_PRECIS,    // OutputPrecision
		DEFAULT_QUALITY,       // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		"Arial",              // pFaceName
		&g_pFont);              // ppFont

	// transformation pipeline
	fov = (float)D3DX_PI / 4.0f;
	aspect_ratio = (float)screenWidth / (float)screenHeight;
	near_plane = 1;
	far_plane = 50000;

}

void CRenderEngine::InitPipeline()
{
	// load and compile shaders
	if(SUCCEEDED(LoadFx(&g_pEffectStandard,"../engine/shaders/shaders9.fx")))
	{
		g_pEffect = g_pEffectStandard;
		g_pEffect->SetTechnique("RenderScene");
	}
	// Creo el vertex declaration
	D3DVERTEXELEMENT9 VERTEX_DECL[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0}, 
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0}, 
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	g_pd3dDevice->CreateVertexDeclaration(VERTEX_DECL, &m_pVertexDeclaration);


	// Creo el vertex declaration
	D3DVERTEXELEMENT9 SKELETAL_VERTEX_DECL[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0}, 
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0}, 
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TANGENT, 0},
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_BINORMAL, 0},
		{ 0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_BLENDWEIGHT, 0},
		{ 0, 72, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_BLENDINDICES, 0},
		D3DDECL_END()
	};
	g_pd3dDevice->CreateVertexDeclaration(SKELETAL_VERTEX_DECL, &m_pSkeletalMeshVertexDeclaration);


	// Creo el vertex declaration para sprites
	D3DVERTEXELEMENT9 SPRITE_VERTEX_DECL[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0}, 
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	g_pd3dDevice->CreateVertexDeclaration(SPRITE_VERTEX_DECL, &m_pSpriteVertexDeclaration);

	// Camara
	lookFrom = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up = D3DXVECTOR3(0,1,0);
	D3DXMatrixLookAtLH(&m_View, &lookFrom, &lookAt, &up);

	// Matrices de Transformacion
	D3DXMatrixPerspectiveFovLH(&m_Proj, fov, aspect_ratio, near_plane, far_plane);
	D3DXMatrixIdentity(&m_World);


	// Deferred Render pipeline G-BUFFER
	D3DXCreateTexture( g_pd3dDevice, screenWidth, screenHeight,1, D3DUSAGE_RENDERTARGET,D3DFMT_A32B32G32R32F,
		D3DPOOL_DEFAULT, &g_pPositionTexture);
	g_pPositionTexture->GetSurfaceLevel( 0, &g_pPositionSurf);

	D3DXCreateTexture( g_pd3dDevice, screenWidth, screenHeight,1, D3DUSAGE_RENDERTARGET, D3DFMT_A32B32G32R32F,
		D3DPOOL_DEFAULT, &g_pNormalTexture);
	g_pNormalTexture->GetSurfaceLevel( 0, &g_pNormalSurf);

	D3DXCreateTexture( g_pd3dDevice, screenWidth, screenHeight,1, D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT, &g_pColorTexture);
	g_pColorTexture->GetSurfaceLevel( 0, &g_pColorSurf);

	// Depth Sentcil sin multisample
	g_pd3dDevice->CreateDepthStencilSurface(screenWidth,screenHeight,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,
			&g_pDepthBuffer,NULL);

	// FullScreen quad
	D3DXCreateTexture( g_pd3dDevice, screenWidth, screenHeight,1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, &g_pFullScreenRenderTarget );
	g_pFullScreenRenderTarget->GetSurfaceLevel( 0, &g_pFullScreenRenderTargetSurf);

	// Creo el full screen quad
	SetupFullscreenQuad();

	// Query multiple RT setting and set the num of passes required
	g_pd3dDevice->GetDeviceCaps( &Caps );
	// Caps.NumSimultaneousRTs;


}


void CRenderEngine::Release()
{
	// libera los recursos propios
	ReleaseTextures();
	ReleaseMeshes();

	// libera los recursos del dx
	if(g_pD3D==NULL)
		return;
	// Effectos
	SAFE_RELEASE(g_pEffectStandard);
	// fonts
	SAFE_RELEASE(g_pFont);
	// Sprite
	SAFE_RELEASE(g_pSprite);
	// Render Targets y surfaces
	SAFE_RELEASE( g_pNormalTexture);
	SAFE_RELEASE( g_pNormalSurf);
	SAFE_RELEASE( g_pPositionTexture);
	SAFE_RELEASE( g_pPositionSurf);
	SAFE_RELEASE( g_pColorTexture);
	SAFE_RELEASE( g_pColorSurf);
	SAFE_RELEASE( g_pDepthBuffer);
	// fullscreen quad
	SAFE_RELEASE( g_pFullScreenRenderTarget );
	SAFE_RELEASE( g_pFullScreenRenderTargetSurf);
	// Device
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pD3D);
}

void CRenderEngine::ReleaseTextures()
{
	for(int i=0;i<cant_texturas;++i)
	{
		delete m_texture[i];
		m_texture[i] = NULL;
	}
	cant_texturas = 0;
}

void CRenderEngine::ReleaseMeshes()
{
	for(int i=0;i<cant_mesh;++i)
	{
		delete m_mesh[i];
		m_mesh[i] = NULL;
	}
	cant_mesh = 0;
}


void CRenderEngine::Update(float p_elpased_time)
{
	elapsed_time = p_elpased_time;
	total_time += elapsed_time;
}


#ifdef DEFERRED_RENDER

void CRenderEngine::RenderFrame(void (*lpfnRender)())
{
	// 1- paso: dibujo el G-buffer
	RenderGBuffer(lpfnRender);

	// 2- Ya tengo el G-BUFFER, ahora dibujo el fullscreenquad
	RenderLigthPass();

	// 3- Actualizo el tiempo y computo los fps y los dibujo 
	ftime += elapsed_time;
	++cant_frames;
	if(ftime>1)
	{
		fps = (float)cant_frames/ftime;
		ftime = 0;
		cant_frames = 0;
	}
	char buffer[255];
	sprintf(buffer,"FPS: %.1f",fps);
	TextOut(10,10,buffer);

	// Presento
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

}


#else
void CRenderEngine::RenderFrame(void (*lpfnRender)())
{
	// Actualizo la matriz de view
	D3DXVECTOR3 up = D3DXVECTOR3(0,1,0);
	D3DXMatrixLookAtLH(&m_View, &lookFrom, &lookAt, &up);
	
	// Limpio la pantalla y el depth buffer
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(240,240,240), 1, 0 );

	// Y actualizo las variables en el shader de la parte de lighting, que no cambian de frame a frame
	SetShaderLighting();

	g_pd3dDevice->BeginScene();
	// dibujo a atravez del callback
	if(lpfnRender!=NULL)
		(*lpfnRender)();
	g_pd3dDevice->EndScene();

	ftime += elapsed_time;
	++cant_frames;
	if(ftime>1)
	{
		fps = (float)cant_frames/ftime;
		ftime = 0;
		cant_frames = 0;
	}

	// dibujo los fps
	char buffer[255];
	sprintf(buffer,"FPS: %.1f",fps);
	TextOut(10,10,buffer);

	// Presento
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

}
#endif


void CRenderEngine::RenderGBuffer(void (*lpfnRender)())
{
	HRESULT hr;
	// Actualizo la matriz de view
	D3DXVECTOR3 up = D3DXVECTOR3(0,1,0);
	D3DXMatrixLookAtLH(&m_View, &lookFrom, &lookAt, &up);

	// Guardo el RT anterior
	LPDIRECT3DSURFACE9 pRTOld = NULL;
	g_pd3dDevice->GetRenderTarget( 0, &pRTOld );
	LPDIRECT3DSURFACE9 pDSOld = NULL;
	g_pd3dDevice->GetDepthStencilSurface( &pDSOld);

	// Meto los render targets del G-buffer
	hr = g_pd3dDevice->SetRenderTarget (0,g_pColorSurf);
	hr = g_pd3dDevice->SetRenderTarget (1,g_pPositionSurf);
	hr = g_pd3dDevice->SetRenderTarget (2,g_pNormalSurf);
	// y pongo un DepthStencil compatible (sin multisampling), porque si no, no camina ni a patadas el mrt
	hr = g_pd3dDevice->SetDepthStencilSurface( g_pDepthBuffer);

	// Limpio el render targets y el depth buffer
	hr = g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0), 1, 0 );

	g_pd3dDevice->BeginScene();

	// dibujo a atravez del callback
	SetZEnabled(true);
	if(lpfnRender!=NULL)
		(*lpfnRender)();

	// Restauro el render target anterior 
	g_pd3dDevice->SetRenderTarget( 0, pRTOld );
	g_pd3dDevice->SetRenderTarget( 1, NULL);
	g_pd3dDevice->SetRenderTarget( 2, NULL);
	SAFE_RELEASE( pRTOld );

	// Restauro el zbuffer de la escena original
	g_pd3dDevice->SetDepthStencilSurface(pDSOld);
	SAFE_RELEASE( pDSOld);

	g_pd3dDevice->EndScene();

	// debug:
	//D3DXSaveTextureToFile("test.bmp",D3DXIFF_BMP,g_pColorTexture,NULL);
}


// Default Light pass
void CRenderEngine::RenderLigthPass()
{
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(240,240,240), 1, 0 );
	SetZEnabled(false);
	g_pEffect->SetTechnique("PhongLighting");
	// seteo el G-buffer
	g_pEffect->SetTexture( "g_txColorBuffer", g_pColorTexture);
	g_pEffect->SetTexture( "g_txPositionBuffer", g_pPositionTexture);
	g_pEffect->SetTexture( "g_txNormalBuffer", g_pNormalTexture);
	// Y actualizo las variables en el shader de la parte de lighting, que no cambian de frame a frame
	SetShaderLighting();
	// post process quuad
	RenderFullScreenQuad();
}



void CRenderEngine::RenderFullScreenQuad()
{
	g_pd3dDevice->BeginScene();
	UINT cPasses;
	g_pEffect->Begin( &cPasses, 0 );
	for( UINT iPass = 0; iPass < cPasses; iPass++ )
	{
		g_pEffect->BeginPass( iPass );
		g_pd3dDevice->SetFVF( D3DFVF_QUADVERTEX );
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, g_FullScreenQuad, sizeof( QUADVERTEX) );
		g_pEffect->EndPass();
	}
	g_pEffect->End();
	g_pd3dDevice->EndScene() ;
}



int CRenderEngine::LoadTexture(char *filename)
{
	// primero busco si la textura ya esta cargada
	int rta = -1;
	for(int i=0;i<cant_texturas && rta==-1;++i)
		if(strcmp(filename,m_texture[i]->name)==0)
			rta = i;

	if(rta!=-1)
		return rta;			// La textura ya estaba cargada en el pool, devuelve el nro de textura 

	// Carga la textura pp dicha
	// Primero verifico que este en la carpeta que me dice
	char fname[MAX_PATH];
	strcpy(fname,filename);
	if(!is_file(fname))
	{
		// Busco en la carpeta media\texturas
		sprintf(fname,"c:\\dev\\media\\texturas\\%s",filename);
		if(!is_file(fname))
		{
			// pruebo con la extension jpg
			extension(fname,"jpg");
			if(!is_file(fname))
			{
				// pruebo con la extension png
				extension(fname,"png");
				if(!is_file(fname))
				{
					// pruebo con la extension bmp
					extension(fname,"bmp");
				}
			}
		}
	}
	
	CTexture *p_texture = CreateTexture(fname);
	if(p_texture==NULL)
		return -1;
	m_texture[cant_texturas] = p_texture;
	return cant_texturas++;
}

int CRenderEngine::LoadMesh(char *filename)
{
	// primero busco si el mesh ya esta cargada
	int rta = -1;
	for(int i=0;i<cant_mesh&& rta==-1;++i)
		if(strcmp(filename,m_mesh[i]->fname)==0)
			rta = i;

	if(rta!=-1)
		return rta;			// el mesh ya estaba cargada en el pool, devuelve el nro de mesh

	// Carga el mesh pp dicho
	// Le pido al device que cargue el mesh 
	CMesh *p_mesh = LoadMeshFromFile(filename);
	if(p_mesh!=NULL)
		m_mesh[rta = cant_mesh++] = p_mesh;

	return rta;
}




// Soporte de archivos xml
#define BUFFER_SIZE  600000

bool CRenderEngine::LoadSceneFromXml(char *filename)
{

	CTGCMeshParser loader;
	tgc_scene_mesh tgc_mesh_lst[MAX_MESH];
	memset(tgc_mesh_lst,0,sizeof(tgc_mesh_lst));
	int cant = loader.LoadSceneHeader(filename,tgc_mesh_lst);

	if(!cant)
		return false;

	// Libero todos los recursos anteriores
	ReleaseTextures();
	ReleaseMeshes();

	// Ahora tengo que cargar los mesh pp dichos.
	for(int i=0;i<cant;++i)
	{
		// Cargo el mesh , pero le indico que de todo el xml solo tiene que cargar ese mesh id y ese mat id
		CMesh *p_mesh = LoadMeshFromXmlFile(filename,tgc_mesh_lst[i].mesh_id,tgc_mesh_lst[i].mat_id);
		if(p_mesh!=NULL)
		{
			// Corrijo el file name
			strcat(p_mesh->fname," - ");
			strcat(p_mesh->fname,tgc_mesh_lst[i].mesh_id);
			// meto el mesh en el pool de meshes
			m_mesh[cant_mesh++] = p_mesh;
		}
	}

	// si todo salio bien tiene que haber tantos mesh como cantidad queriamos cargar
	return cant==cant_mesh?true:false;
}

bool CRenderEngine::LoadSceneFromFlat(char *filename)
{
	// Libero todos los recursos anteriores
	ReleaseTextures();
	ReleaseMeshes();
	
	FILE * file = fopen(filename, "rb");

	if (!file)
		return false; //el archivo no existe

	char cur_dir[MAX_PATH] = {0};
	char aux_path[MAX_PATH];

	strncpy(cur_dir, filename, strrchr(filename, '/') - filename + 1);
	
	int cur_dir_len = strlen(cur_dir);

	int signature;
	int version;
	int cant;

	fread(&signature, sizeof(int), 1, file);
	fread(&version, sizeof(int), 1, file);
	fread(&cant, sizeof(int), 1, file);

	// Ahora tengo que cargar los mesh pp dichos.
	for (int i = 0; i < cant; ++i)
	{
		CMesh * m = new CMesh;

		int blockSize = (int)&m->layers - (int)&m->m_pos;
		fread(&m->m_pos, blockSize, 1, file);

		//todo lo que es fijo ya esta leido con el fread anterior
		//leo los vectores variables
		m->pVertices = new MESH_VERTEX[m->cant_vertices];
		m->pIndices = new DWORD[m->cant_indices];
		m->pAttributes = new DWORD[m->cant_faces];

		fread(m->layers, sizeof(MESH_LAYER), m->cant_layers, file);
		fread(m->pVertices, sizeof(MESH_VERTEX), m->cant_vertices, file);
		fread(m->pIndices, sizeof(DWORD), m->cant_indices, file);
		fread(m->pAttributes, sizeof(DWORD), m->cant_faces, file);

		for (int j = 0; j < m->cant_layers; j++)
		{
			//La textura se guarda de forma relativa la transformo en absoluta
			//TODO: agregar validacion
			sprintf(aux_path, "%s%s", cur_dir, m->layers[j].texture_name);
			for (char * p = aux_path; *p; p++) if (*p == '\\') *p = '/';
			strcpy(m->layers[j].texture_name, aux_path);
		}

		m->engine = this;
		m->CreateMeshFromData(this);

		m_mesh[cant_mesh++] = m;
	}

	fclose(file);

	// si todo salio bien tiene que haber tantos mesh como cantidad queriamos cargar
	return cant == cant_mesh ? true : false;
}

bool CRenderEngine::SaveSceneToFlat(char *filename)
{
	FILE * file = fopen(filename, "wb");

	if (!file)
		return false; //no se pudo crear el archivo

	char cur_dir[MAX_PATH] = { 0 };
	char aux_path[MAX_PATH];

	strncpy(cur_dir, filename, strrchr(filename, '/') - filename + 1);

	int cur_dir_len = strlen(cur_dir);
	
	int signature = *((int *)"GIGC");
	int version = 1;
	int cant = cant_mesh;

	fwrite(&signature, sizeof(int), 1, file);
	fwrite(&version, sizeof(int), 1, file);
	fwrite(&cant, sizeof(int), 1, file);

	// Ahora tengo que cargar los mesh pp dichos.
	for (int i = 0; i < cant; ++i)
	{
		CMesh * m = m_mesh[i];

		int blockSize = (int)&m->layers - (int)&m->m_pos;
		fwrite(&m->m_pos, blockSize, 1, file);

		for (int j = 0; j < m->cant_layers; j++)
		{
			//saco el principio del path de la textura para transformarla en relativa, OJO solo funciona
			//para path relativos al cur_dir, TODO: agregar validacion
			strcpy(aux_path, m->layers[j].texture_name);
			ZeroMemory(m->layers[j].texture_name, sizeof(m->layers[j].texture_name)); //hago un zeromemory para que no vaya basura en el archivo
			strcpy(m->layers[j].texture_name, aux_path + cur_dir_len);
		}

		//todo lo que es fijo ya esta escrito con el fwrite anterior
		//grabo los vectores variables
		fwrite(m->layers, sizeof(MESH_LAYER), m->cant_layers, file);
		fwrite(m->pVertices, sizeof(MESH_VERTEX), m->cant_vertices, file);
		fwrite(m->pIndices, sizeof(DWORD), m->cant_indices, file);
		fwrite(m->pAttributes, sizeof(DWORD), m->cant_faces, file);

		for (int j = 0; j < m->cant_layers; j++)
		{
			//restauro el path de las texturas ojo solo funciona si el nombre de la textura es mas largo que el cur_dir
			strcpy(m->layers[j].texture_name, aux_path);
		}

	}

	fclose(file);

	return true;
}


// Helper, para saber si es un xml dato es un skeletal o no
bool IsSkeletalMesh(char *fname)
{
	bool rta = false;
	FILE *fp = fopen(fname,"rt");
	
	if(fp)
	{
		char buffer[255];
		fgets(buffer,sizeof(buffer),fp);
		if(strncmp(buffer,"<tgcSkeletalMesh>",17)==0)
			rta = true;
		fclose(fp);
	}
	return rta;
}


void CRenderEngine::SetShaderTransform()
{
	// matrices de transformacion
	g_pEffect->SetMatrix( "m_World", &m_World);
	g_pEffect->SetMatrix( "m_View", &m_View);
	g_pEffect->SetMatrix( "m_Proj", &m_Proj);

	// punto de vista: 
	g_pEffect->SetValue( "m_LookFrom", &lookFrom, sizeof(D3DXVECTOR3));

	// precalculadas para ganar tiempo: 
	D3DXMATRIXA16 mWorldViewProjection = m_World * m_View * m_Proj;
	g_pEffect->SetMatrix( "m_WorldViewProj", &mWorldViewProjection);
	D3DXMATRIXA16 mWorldView = m_World * m_View;
	g_pEffect->SetMatrix( "m_WorldView", &mWorldView);

	// Transpuesta inversa del world, (para transformar direcciones)		
	D3DXMATRIXA16 m_TransposeInvWorld;
	FLOAT det;
	D3DXMatrixTranspose(&m_TransposeInvWorld,D3DXMatrixInverse(&m_TransposeInvWorld,&det,&m_World));
	g_pEffect->SetMatrix( "m_TransposeInvWorld", &m_TransposeInvWorld);

	// Resolucion de pantalla
	g_pEffect->SetFloat("screen_dx", (float)d3dpp.BackBufferWidth);      
	g_pEffect->SetFloat("screen_dy", (float)d3dpp.BackBufferHeight);      

}

void CRenderEngine::SetShaderLighting()
{
	float phi = 2;
	float theta = 0.95f;

	D3DXVECTOR3 vLightPos = D3DXVECTOR3(100,1250,1000);
	D3DXVECTOR3 vLightDir = D3DXVECTOR3(0,-1,0);
	D3DXVECTOR3 vLightColor = D3DXVECTOR3(1,1,1);

	g_pEffect->SetValue( "g_LightDir", vLightDir, sizeof(D3DXVECTOR3));
	g_pEffect->SetValue( "g_LightPos", vLightPos, sizeof(D3DXVECTOR3));
	g_pEffect->SetValue( "g_LightColor", vLightColor, sizeof(D3DXVECTOR3));
	g_pEffect->SetFloat( "g_LightPhi", (float)cos(phi/2.0));
	g_pEffect->SetFloat( "g_LightTheta", (float)cos(theta/2.0));

	//	g_pEffect->SetFloat( "k_la", shader_la);	// luz ambiente
	//	g_pEffect->SetFloat( "k_ld", shader_ld);	// luz difusa
	//	g_pEffect->SetFloat( "k_ls", shader_ls);	// luz specular
	//	g_pEffect->SetFloat( "k_brightness", g_brillo);	
	//	g_pEffect->SetFloat( "k_contrast", g_contraste);

}




CTexture *CRenderEngine::CreateTexture(char *fname)
{
	CTexture *p_texture = NULL;
	LPDIRECT3DTEXTURE9      g_pTexture;

	if(SUCCEEDED(D3DXCreateTextureFromFileEx( g_pd3dDevice, fname, 
		D3DX_DEFAULT_NONPOW2,    // default width
		D3DX_DEFAULT_NONPOW2,    // default height
		1,				//D3DX_DEFAULT,    // default mip mapping (genera todos los mipmaps)
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		0,				// MAGIC COLOR 
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&g_pTexture)))
	{
		p_texture = new CTexture();
		strcpy(p_texture->name , fname);
		p_texture->g_pTexture = g_pTexture;

		D3DSURFACE_DESC desc;
		g_pTexture->GetLevelDesc(0,&desc);
		p_texture->imgWidth = desc.Width;
		p_texture->imgHeight = desc.Height;
	}
	return (CTexture *)p_texture;
}


CMesh *CRenderEngine::LoadMeshFromFile(char *fname)
{
	CMesh *p_mesh = NULL;
	char ext[4];
	que_extension(fname,ext);
	bool ok;
	if(ext[0]=='y' || ext[0]=='Y')
	{
		// Cargo un archivo fomrato .Y 
		p_mesh = new CMesh;
		ok = p_mesh->LoadFromFile(this,fname);
	}
	else
	{
		// Cargo un archivo formato xml
		if(IsSkeletalMesh(fname))
		{
			// Skeletal mesh
			p_mesh = new CSkeletalMesh;
			ok = ((CSkeletalMesh *)p_mesh)->LoadFromXMLFile(this,fname);
		}
		else
		{
			// Mesh comun 
			p_mesh = new CMesh;
			ok = p_mesh->LoadFromXMLFile(this,fname);
		}
	}

	if(!ok)
		SAFE_DELETE(p_mesh);			// y p_mesh queda en NULL
	return p_mesh;

}

CMesh *CRenderEngine::LoadMeshFromXmlFile(char *fname,char *mesh_name,int mat_id)
{
	CMesh *p_mesh = NULL;
	p_mesh = new CMesh;
	bool ok = p_mesh->LoadFromXMLFile(this,fname,mesh_name,mat_id);
	if(!ok)
		SAFE_DELETE(p_mesh);			// y p_mesh queda en NULL
	return p_mesh;
}

HRESULT CRenderEngine::LoadFx(ID3DXEffect** ppEffect,char *fx_file)
{
	ID3DXBuffer *pBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile( g_pd3dDevice, fx_file,
		NULL, NULL, D3DXFX_NOT_CLONEABLE, NULL, ppEffect, &pBuffer);
	if( FAILED(hr) )
	{
		char *saux = (char*)pBuffer->GetBufferPointer();
		MessageBox(NULL, saux, NULL, MB_OK);
	}
	return hr;
}


void CRenderEngine::SetZEnabled(bool enabled)
{
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, enabled);
}


void CRenderEngine::SetAlphaBlendEnabled(bool enabled)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,enabled);
}


void CRenderEngine::TextOut(int x,int y,char *string)
{
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	RECT rc;
	rc.left = x;
	rc.top = y;
	rc.right = 0;
	rc.bottom = 0;

	g_pFont->DrawText( g_pSprite, string, -1, &rc, DT_NOCLIP, D3DXCOLOR(0,1,1,1));
	g_pSprite->End();
}


// Helper a reprogramar en math.h
// rotacion xz es sobre el eje y
void rotar_xz(D3DXVECTOR3 *V , float an)
{
	float xr=V->x*cos(an)+V->z*sin(an); 
	float zr=-V->x*sin(an)+V->z*cos(an);
	V->x = xr;
	V->z = zr;
}


// helper
//-----------------------------------------------------------------------------

void CRenderEngine::SetupFullscreenQuad(  )
{
	D3DSURFACE_DESC desc;

	g_pFullScreenRenderTargetSurf->GetDesc( &desc );

	float fWidth5 = ( float )screenWidth - 0.5f;
	float fHeight5 = ( float )screenHeight- 0.5f;

	float fTexWidth1 = ( float )screenWidth / ( float)desc.Width;
	float fTexHeight1 = ( float )screenHeight / (float)desc.Height;

	// Fill in the vertex values
	g_FullScreenQuad[0].pos = D3DXVECTOR4( fWidth5, -0.5f, 0.0f, 1.0f );
	g_FullScreenQuad[0].tu = fTexWidth1;
	g_FullScreenQuad[0].tv = 0.0f;

	g_FullScreenQuad[1].pos = D3DXVECTOR4( fWidth5, fHeight5, 0.0f, 1.0f );
	g_FullScreenQuad[1].tu = fTexWidth1;
	g_FullScreenQuad[1].tv = fTexHeight1;


	g_FullScreenQuad[2].pos = D3DXVECTOR4( -0.5f, -0.5f, 0.0f, 1.0f );
	g_FullScreenQuad[2].tu = 0;
	g_FullScreenQuad[2].tv = 0;


	g_FullScreenQuad[3].pos = D3DXVECTOR4( -0.5f, fHeight5, 0.0f, 1.0f );
	g_FullScreenQuad[3].tu = 0;
	g_FullScreenQuad[3].tv = fTexHeight1 ;
}


