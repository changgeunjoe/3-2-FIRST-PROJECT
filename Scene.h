//-----------------------------------------------------------------------------
// File: Scene.h
//-----------------------------------------------------------------------------

#pragma once

#include "Shader.h"
#include "Player.h"
#include"MissileObjectShader.h"
#include"MultiSpriteObjectsShader.h"
#include"GSBillBoardShader.h"
#include"CParticleObject.h"
#include"CMeshIlluminated.h"
#include"CDynamicCubeMappingShader.h"
#include"2dUIObjectsShader.h"
#include"COutlineShader.h"
#include"SceneShader.h"
#define MAX_LIGHTS			50

#define POINT_LIGHT			1
#define SPOT_LIGHT			2
#define DIRECTIONAL_LIGHT	3

struct LIGHT
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular;
	XMFLOAT3				m_xmf3Position;
	float 					m_fFalloff;
	XMFLOAT3				m_xmf3Direction;
	float 					m_fTheta; //cos(m_fTheta)
	XMFLOAT3				m_xmf3Attenuation;
	float					m_fPhi; //cos(m_fPhi)
	bool					m_bEnable;
	int						m_nType;
	float					m_fRange;
	float					padding;
};

struct LIGHTS
{
	LIGHT					m_pLights[MAX_LIGHTS];
	XMFLOAT4				m_xmf4GlobalAmbient;
	int						m_nLights;
};

struct TIMER
{
	float						m_nTimer;
	float						m_nAlpha;
	XMFLOAT4X4					m_identityview;
};

class CScene
{
public:
    CScene();
    ~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	void BuildDefaultLightsAndMaterials();
	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();

	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature() { return(m_pd3dGraphicsRootSignature); }
	void SetGraphicsRootSignature(ID3D12GraphicsCommandList* pd3dCommandList) { pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature); }

	bool ProcessInput(UCHAR *pKeysBuffer);
    void AnimateObjects(float fTimeElapsed);
    void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera=NULL);
	void OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);


	void RenderParticle(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	void OnPostRenderParticle();
	void OnPreRender(ID3D12Device* pd3dDevice, ID3D12CommandQueue* pd3dCommandQueue, ID3D12Fence* pd3dFence, HANDLE hFenceEvent);

	void ReleaseUploadBuffers();
	void CheckObjectByObjectCollisions(float ftimeelapsed);
	CHeightMapTerrain* GetTerrain() { return(m_pTerrain); }

	void CarMove();
	void CarMove2();
	void CarMove3();
	void CarMove4();
	CPlayer								*m_pPlayer = NULL;
	CBulletShader						*m_pBulletShader{ NULL };

	CObjectsShader                      *pObjectsShader;

	COutlineShader						*m_pOutlineShader = NULL;

public:
	ID3D12RootSignature					*m_pd3dGraphicsRootSignature = NULL;

	int									m_nGameObjects = 0;
	CGameObject							**m_ppGameObjects = NULL;

	int									m_nShaders = 0;
	
	int								m_nParticleObjects = 0;
	CParticleObject** m_ppParticleObjects = NULL;


	CShader								**m_ppShaders = NULL;

	CSkyBox								*m_pSkyBox = NULL;
	CHeightMapTerrain					*m_pTerrain = NULL;
	CHeightMapTerrain					*m_pWater = NULL;
	CMissileObjectsShader*				pMissileobjectShader;
	CMultiSpriteObjectsShader    * pMultiSpriteObjectShader;
	LIGHT								*m_pLights = NULL;
	int									m_nLights = 0;

	XMFLOAT4							m_xmf4GlobalAmbient;

	ID3D12Resource						*m_pd3dcbLights = NULL;
	LIGHTS								*m_pcbMappedLights = NULL;

	ID3D12Resource						*m_pd3dcbTimer = NULL;
	TIMER								*m_pcbMappedTimer = NULL;

	float								fTimer = 5.0f;
	float								fAlPha = 0.3f;
	float								CollisionTimer = 0.0f;
	float								m_ftimesecond = 0.0f;
	int							m_nEnvironmentMappingShaders = 0;
	CDynamicCubeMappingShader** m_ppEnvironmentMappingShaders = NULL;
};
