#pragma once

#define DEFERRED_RENDER

#include "mesh.h"
#include "texture.h"

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
#define SAFE_DELETE(p) { if ( (p) ) { delete (p); (p) = 0; } }

#define MAX_MATERIAL	3000
#define MAX_TEXTURAS	3000
#define MAX_MESH		10000

struct VERTEX
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texcoord;
};

// Vertex format para Quads
struct QUADVERTEX
{
	D3DXVECTOR4 pos;	// Posicion
	FLOAT tu,tv;		// Texture coords
};
#define D3DFVF_QUADVERTEX  (D3DFVF_XYZRHW | D3DFVF_TEX1)

class CRenderEngine
{

public:

	int screenWidth, screenHeight;
	float fov;										// Field of view
	float aspect_ratio;
	float near_plane,far_plane;
	D3DXMATRIX m_World,m_View,m_Proj;
	D3DXMATRIX bonesMatWorldArray[26];					// todo, parche por ahora

	LPDIRECT3D9             g_pD3D;					// Used to create the D3DDevice
	LPDIRECT3DDEVICE9       g_pd3dDevice;			// Our rendering device
	D3DPRESENT_PARAMETERS	d3dpp;
	LPD3DXFONT				g_pFont;
	LPD3DXSPRITE			g_pSprite;		
	D3DCAPS9				Caps;

	ID3DXEffect* g_pEffect;				// current Effect
	ID3DXEffect* g_pEffectStandard;	

	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;			// Pos + Normal + TexCoords
	LPDIRECT3DVERTEXDECLARATION9 m_pSkeletalMeshVertexDeclaration;
	LPDIRECT3DVERTEXDECLARATION9 m_pSpriteVertexDeclaration;	// Pos + TexCoords

	// Geometry buffer
	LPDIRECT3DTEXTURE9          g_pPositionTexture;
	LPDIRECT3DSURFACE9          g_pPositionSurf;
	LPDIRECT3DTEXTURE9          g_pColorTexture;
	LPDIRECT3DSURFACE9          g_pColorSurf;
	LPDIRECT3DTEXTURE9          g_pNormalTexture;
	LPDIRECT3DSURFACE9          g_pNormalSurf;
	LPDIRECT3DSURFACE9			g_pDepthBuffer;			// Zbuffer sin multisample

	// FullScreenCuad
	LPDIRECT3DTEXTURE9          g_pFullScreenRenderTarget;
	LPDIRECT3DSURFACE9          g_pFullScreenRenderTargetSurf;

	QUADVERTEX  g_FullScreenQuad[4];


	// Camera support
	D3DXVECTOR3 lookFrom , lookAt;

	// Pool de texturas
	int cant_texturas;
	CTexture *m_texture[MAX_TEXTURAS];

	// Pool de Materiales
	int cant_materiales;
	MATERIAL *m_material[MAX_MATERIAL];


	// Pool de meshes
	int cant_mesh;
	CMesh **m_mesh;

	float total_time;
	float elapsed_time;

	int cant_frames;		// frame count
	float ftime;			// frame time
	float fps;				

	// lighting stage flags
	bool lighting_enabled;			// si esta en off dibuja directamente el color buffer

	// info flags
	bool show_fps;		
	bool show_camera;		


	CRenderEngine();
	~CRenderEngine();

	// inicializacion y cleanup
	void Create(HWND hWnd);		
	void InitD3D(HWND hWnd);
	void InitPipeline();
	bool IsReady();
	void Release();			// closes Direct3D and releases memory

	// Graphic pipeline
	void Update(float p_elpased_time);
	void RenderFrame(void (*lpfnRender)()=NULL);
	void RenderGBuffer(void (*lpfnRender)()=NULL);
	void RenderLigthPass();
	void RenderFullScreenQuad();

	int LoadMaterial(char *filename);
	void ReleaseMaterials();
	void SetMaterial(int n);
	int LoadTexture(char *filename);
	void ReleaseTextures();
	int LoadMesh(char *filename);
	void ReleaseMeshes();
	void ReleaseResources();			// libera los recursos PROPIOS (texturas, mesh y materiales)

	// Soporte de archivos xml
	bool LoadSceneFromXml(char *filename);
	bool LoadSceneFromFlat(char *filename);
	bool SaveSceneToFlat(char *filename);

	virtual void SetShaderTransform();		// Transform and...
	virtual void SetShaderLighting();		// Lighting


	virtual CTexture *CreateTexture(char *fname);
	

	HRESULT LoadFx(ID3DXEffect** ppEffect,char *fx_file);

	// Render states
	virtual void SetZEnabled(bool enabled=true);
	virtual void SetAlphaBlendEnabled(bool enabled=true);

	// Text
	virtual void TextOut(int x,int y,char *string);

	// Helpers
	void SetupFullscreenQuad();


private:
	virtual CMesh *LoadMeshFromFile(char *fname);
	virtual CMesh *LoadMeshFromXmlFile(char *fname,char *mesh_name,int mat_id);


};

bool IsSkeletalMesh(char *fname);
void rotar_xz(D3DXVECTOR3 *V , float an);

