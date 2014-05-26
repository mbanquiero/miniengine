#include "stdafx.h"
#include "ExampleTest.h"

REGISTER_EXAMPLE(CExampleTest)

CExampleTest::CExampleTest()
{
}


CExampleTest::~CExampleTest()
{
}

const char * CExampleTest::getName()
{
	return "Escenario de Prueba";
}

const char * CExampleTest::getDescription()
{
	return "Descripcion de ejemplo de prueba";
}

void CExampleTest::init()
{
	//cargo el mesh del escenario del quake

	char mesh_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, mesh_path);
	strcat(mesh_path, "\\media\\QuakeRoom1\\QuakeMap-TgcScene.flat");

	//por algun motivo no anda usando un path relativo y usando \ en vez de /
	//reemplazo todas las \\ por /
	for (char * p = mesh_path; *p; p++) if (*p == '\\') *p = '/';

	_engine.LoadSceneFromFlat(mesh_path);

	D3DXVECTOR3 min = D3DXVECTOR3(10000, 10000, 10000);
	D3DXVECTOR3 max = D3DXVECTOR3(-10000, -10000, -10000);
	for (int i = 0; i<_engine.cant_mesh; ++i)
	{
		D3DXVECTOR3 p0 = _engine.m_mesh[i]->m_pos;
		if (p0.x<min.x)
			min.x = p0.x;
		if (p0.y<min.y)
			min.y = p0.y;
		if (p0.z<min.z)
			min.z = p0.z;


		D3DXVECTOR3 p1 = p0 + _engine.m_mesh[i]->m_size;
		if (p1.x>max.x)
			max.x = p1.x;
		if (p1.y>max.y)
			max.y = p1.y;
		if (p1.z>max.z)
			max.z = p1.z;
	}

	_engine.lookFrom = _engine.lookAt = (min + max) * 0.5;
	_engine.lookFrom.x += D3DXVec3Length(&(max - min)) * 2;
}

void CExampleTest::render(float elapsedTime)
{
	for (int i = 0; i < _engine.cant_mesh; i++)
	{
		_engine.m_mesh[i]->Render();
	}

}

void CExampleTest::close()
{

}
