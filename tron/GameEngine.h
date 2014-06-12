/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "\gigc\miniengine\engine\graphics\RenderEngine.h"
#include <mmsystem.h>
#include "\Program Files (x86)\Microsoft DirectX SDK (April 2006)\include\d3dx9.h"
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include "\gigc\miniengine\engine\math\Vector3.h"
#include "mouse.h"
#include "dxgui.h"
#include "mysocket.h"
#include "sndmng.h"


#define MAX_PUNTOS		10000
#define MAX_PART		1000
#define MAX_PAQ			5000


// vertice en FVF 
struct CUSTOMVERTEX
{
	FLOAT x,y,z;			// Posicion
	D3DXVECTOR3 N;			// Normal
	D3DCOLOR    color;		// Color
	FLOAT       tu, tv;		// Coordenada u,v de la textura
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


// Particle System
struct particle
{
	Vector3 Pos;
	Vector3 Dir;
	double delay;
	double rtime;
	double vel;
	double vel_v;
	double acel;
	double dq;
};


class CParticleSystem
{
public:
	int cant_part;
	particle particle[MAX_PART];
	double g_time;
	Vector3 P0;
	int textura;
	BYTE r0,g0,b0;		// modula con el color
	double t0,t1;
	float gravedad;
	int cant_pasos;
	int max_pasos;
	BOOL rastro;
	char tipo;

	// DIRECTX
	CGameEngine *model;		// modelo 3d
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;			// Buffer para vertices
	size_t vertex_size;

	CParticleSystem();
	~CParticleSystem();

	// simulacion stage
	virtual HRESULT Create(CGameEngine *model,Vector3 Pos,int cant,int nro_textura,char tipo_explosion=0);
	virtual HRESULT Update(float time,Vector3 pos_emisor);
	// rendering stage
	virtual void Render();
	void Release();

};

// vertice para la particula
struct VERTEX_PARTICLE
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DCOLOR    color;		// Color
	D3DXVECTOR2 texcoord0;
	D3DXVECTOR3 texcoord1;
};



// modos de juego
#define GAME_TEST_RUTA		0		
#define GAME_GRID_BATTLE		1		
#define GAME_GRID_SURVIVAL	2		
// Tests
#define GAME_TEST_LABERINTO	10		

// animacion_gui
#define GUI_ESCENARIO		0
#define GUI_PREVIEW_RUTA	1
#define GUI_RECORRER_RUTA	2
#define GUI_PRESENTACION	3
#define GUI_PREVIEW_MOTO	4
#define GUI_GAME_PAUSED		5


#define MAX_MSG_DBG		30
#define MAX_TRAMOS		100
struct cell
{
	int cant_tramos;		// cantidad de tramos del ligth paths
	int p[MAX_TRAMOS];				// puntero a path[]
	char player[MAX_TRAMOS];		// de que jugador es
};




class player
{
	public:
	BOOL init;
	int nro_player;							// numero de jugador
	static double max_an_lat;		// maximo angulo lateral al girar
	static double max_w0;			// maxima velocidad angular
	static Vector3 size_cycle;	// tamaño de la moto
	double vel_salto;				// aceleracion vertical para saltar
	char cant_vidas;
	char score;
	char explosion_barata;


	Vector3 Pos_Inicial;	// posicion de salida del juego, cada vez que pierde vuelve a esta posicion
	Vector3 Pos;			// posicion
	Vector3 Dir;			// Direccion del motor (no incluye gravedad, saltos etc)
	Vector3 Vmoto;		// Velocidad vectorial de la moto |Vmoto| = dir moto
	Vector3 antVel;		// Vmoto anterior
	Vector3 Dir_Original;	// Direccion Original (para hacer un cambio suave de direccion)
	float Hpiso;			// Altura del piso en la Pos
	float Hpiso_s;			// Altura del piso en la Pos delantera

	// angulos de direccion del motor
	double alfa,alfa_d;
	double beta;
	
	double vel_ini;
	double vel;				// modulo de la velocidad de la moto
	double vel_v;			// Velocidad Vertical
	double an_lat;			// angulo lateral al girar

	// Test
	double ant_alfa_1,ant_alfa_2;



	// Espacio de la moto, (Dir,Up,N)
	Vector3 Cycle_Dir;	// Direccion de la trayectoria de la moto
	Vector3 Cycle_Up;		// Direccion Arriba de la moto
	Vector3 Cycle_N;		// Direccion normal a la trayectoria
	Vector3 Cycle_Pos;	// Posicion del centro del mesh

	// status
	int pos_en_ruta;
	float timer_cayendo;		// cayendo de la ruta
	float timer_rebotando;		// rebotando del toolpath
	float timer_rearmar_moto;	// la moto se esta re-armando
	float timer_light_path;		// el ligth path se prende de nuevo: delay 
	float timer_ia;				// movimiento al azar
	BOOL implotando;	// 
	BOOL derrapando;

	// Recorrido
	int cant_ptos;
	Vector3 path[MAX_PUNTOS];
	double path_an[MAX_PUNTOS];
	int pos_i,pos_j;		// posicion en la grilla
	int pos_vertex_der;
	int pos_vertex_izq;
	int cant_ptos_delay;	// valor de cant_ptos justo antes de hacer un delay

	// colisiones
	Vector2 Ip;		// ultimo punto de colision
	int path_choque;	// choco en path[path_choque]

	// colores
	D3DCOLOR c_lightpath;
	D3DCOLOR c_lightpath_espejo;
	D3DCOLOR c_linepath;

	// varios
	char nro_color;
	char nombre[255];
	char slogan[255];
	char nro_avatar;			// nro de textura del avatar


	// Particle System
	CParticleSystem PS,PSaux;

	// sounido
	CSoundManager sound;
	double timer_sound;			// sound events
	BOOL mute;					// esta con el sonido apagado

	// comportamiento automatico
	Vector3 Dir_d;			// Direccion deseada
	static double treaccion;			// tiempo de reaccion
	double timer_girando;			// esta girando
	double timer_evitando;			// evita un obstaculo
	double timer_reculando;			// esta por irse del domo...tiene que recular
	BOOL giro_horario;
	static double dist_radar;
	BOOL juego_justo;

	// multiplayer
	int cant_paquetes;
	int paq_desde;
	grid_packet paquete[MAX_PAQ];
	BOOL ack;

	class CClientSocket socket;
	virtual void Send();
	void llenar_paquete(grid_packet *packet,char cmd=1);


	class CGameEngine *model;		// modelo 3d
	class CMesh *cycle_mesh;		// mesh de la moto 
	//LPD3DXMESH g_pMeshCycle;		// auxiliara para explotar la moto

	// DIRECTX
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVBPath;			// Buffer para vertices del ligth path


	player();
	virtual void Create(CGameEngine *model,Vector3 pos,int n);
	virtual void Reset();
	virtual void SetCamara();
	virtual void poner_en_ruta();
	virtual void calc_angulos();	// recalcula alfa y beta
	virtual void SetColor(int n);
	virtual void PerderVida();

	// light path
	virtual void initPath();
	virtual void actualizarPath();
	virtual void crearLaberintoLuz();

	HRESULT DXCreatePathVertex();
	void DXCleanup();

	void RenderLightPath(BOOL resplandor=FALSE,BOOL espejo=FALSE);
	void RenderCycle(BOOL resplandor=FALSE);


	// input
	void ProcessMsg(MSG *Msg);
	void ProcessInput(CDirectInputMouse *mouse);

	// logica del jugador
	void Update();
	void UpdateTimers();
	void IA();
	void UpdateSound();

	// multiplayer
	void ProcessPacket(grid_packet *packet);
	void UpdateRemoto();
	void Wait();




};


class CGameEngine 
{


public:
	CGameEngine();
	virtual ~CGameEngine();

	// motor3d 
	CRenderEngine motor3d;

	Vector3 Dir_D;			// Direccion Deseaada
	float dtime;	
	int cant_cell;
	float dgrid;
	Vector3 centro;
	float radio;
	int cant_focos;
	int pos_vertex_focos;
	int pos_vertex_focos2;
	int pos_vertex_skydome;
	int cant_pri_skydome;

	int cant_ptos_ruta;
	int pos_vertex_ruta;
	Vector3 pt_ruta[500];
	float aux_tu;
	float aux_tv;
	int aux_tramo;
	BOOL aux_en_ruta;
	double max_tramo_ruta;
	double ancho_ruta;
	double ancho_guarray;
	float fps;
	int nro_frame;
	int tipo_ruta;
	BOOL techo_ruta;

	int animacion_gui;			// animacion del escenario en modo gui
	double pr_pos;
	Vector3 pr_LA;
	Vector3 pr_LF;

	Vector3 LA_d;		// Look at deseado
	Vector3 LF_d;		// Look from deseado
	float vel_camara;	// Velocidad de la camara (para el LF)
	float vel_rot_camara;	// Velocidad de la camara (para el LA)
	BOOL smooth_cam;


	BOOL modo_camara;
	BOOL modo_gui;
	BOOL fpc;			// camara en primera persona


	float timer_pausa;
	gui_frame *frame_pausa;
	gui_item *msg_pausa;

	float timer_warming;
	float timer_presentacion;
	float timer_game_over;
	float timer_lag;
	float timer_modalless;
	BOOL lagging;

	// celdas
	cell celdas[64][64];


	// mutiplayer
	BOOL multiplayer;
	BOOL socket_init;
	BOOL es_servidor;
	class CServerSocket server;


	int textura_piso;
	int textura_pared;
	int textura_path;
	int textura_skydome;
	int textura_ruta;
	int textura_explo;
	int textura_gui;
	int textura_face;
	int textura_face_enemigo;
	int textura_cursor;
	int textura_menu;
	int textura_roundrect;
	int textura_toolbar;

	// auxiliar para guardar el ligth path esquematico en 2D 
	D3DXVECTOR2 lightpath[10][MAX_PUNTOS];
	int ligthpath_cant[10];

	// mov. del mouse
	int mouse_dx;
	int mouse_dy;

	// tiempo
	double time,elapsed_time;
	double remote_time;
	BOOL paused;
	
	// jugadores
	player P[10];
	int cant_players;
	player *player_one;		// short cut = P[0]
	int cant_enemigos;
	int nro_player_perdio;

	// modo de juego
	char modo_juego;
	char ronda;
	char max_rondas;
	char juega_sola;
	char nivel;
	float survival_time;
	
	Vector3 VUP;			// Velocidad vectorial de la moto |Vmoto| = dir moto

	// gui
	DXGui gui;

	// direct input mouse
	CDirectInputMouse mouse;

	// sonido
	//char fname_midi[255];
	BOOL hay_radio;
	UINT midi_DeviceID;
	// play list
	char midi_files[50][MAX_PATH];
	int cant_midis;
	int midi_actual;


	// mensajes debug
	char debug_msg[MAX_MSG_DBG][255];
	int cant_msg;
	int primer_msg;
	BOOL debug_ia;
	void agregar_msg(char *buffer);


	virtual HRESULT DXInit(HWND hWnd);
	virtual HRESULT DXSetupRender();
	virtual HRESULT DXRender();
	virtual HRESULT DXCreateVertex();
	virtual HRESULT DXdibujar_planoVP(char plano=1,BOOL clear=FALSE);

	
	void scoreboard();
	void brd_player(int player);

	void MainLoop();
	void InitGame();
	void Presentacion();
	void FinRonda(int player);

	void RenderScene(BOOL resplandor=FALSE,BOOL mirror=FALSE);
	void RenderBolas();
	void RenderMirror();
	void RenderRecognizers(BOOL resplandor=FALSE);
	void RenderFocos();

	// comportamiento del juego
	int entra_en_ruta(Vector3 Pos,Vector3 Dir);
	BOOL choca_ligthpath(Vector3 desde,Vector3 hasta,int *path_choque,Vector2 *Ip,int player);
	BOOL choca(Vector3 desde,Vector3 hasta,int player,Vector2 *Ip,BOOL prediccion=FALSE);

	double que_altura(double x,double z,char *tipo_celda=NULL,int *tramo=NULL);
	double que_altura(int i,Vector2 p);

	// rutas
	int load_pt_ruta(int tipo,Vector3 *pt);
	void load_ruta();

	// gui
	void GUI_loop();
	void GUI_mainmenu();
	int GUI_messagebox(char *msg,int tipo=0);
	int GUI_options_ruta();
	int GUI_options_battle();
	int GUI_options_survival();
	int GUI_options_profile();
	int GUI_esperar_conexion();
	int GUI_input_data(char *buffer,char *titulo,char *msg);
	int GUI_pausa();
	int GUI_elegir_midi();

	// playlist
	void cargarPlayList();
	void playMidi();
	void loopMidi();

};


// motor3d 
extern CGameEngine escena;


