//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"
#include"ParticleMesh.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildDefaultLightsAndMaterials()
{
	m_nLights = 50;
	m_pLights = new LIGHT[m_nLights];
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	m_pLights[0].m_bEnable = false;
	m_pLights[0].m_nType = SPOT_LIGHT;
	m_pLights[0].m_fRange = 150.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(130.0f, 30.0f, 30.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	m_pLights[1].m_bEnable = false;
	m_pLights[1].m_nType = POINT_LIGHT;
	m_pLights[1].m_fRange = 900.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(5.0f, 5.0f, 5.0f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights[2].m_bEnable = false;
	m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.053f, 0.053f, 0.053f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.17f, 0.17f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 1.0f);
	m_pLights[3].m_bEnable = true;
	m_pLights[3].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(0.0f, 300.0f, 0.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights[4].m_bEnable = false;
	m_pLights[4].m_nType = SPOT_LIGHT;
	m_pLights[4].m_fRange = 30.0f;
	m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.012f, 0.012f, 0.012f, 1.0f);
	m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.24f, 0.14f, 0.24f, 1.0f);
	m_pLights[4].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[4].m_xmf3Position = XMFLOAT3(0.0f, 5.0f, -7.0f);
	m_pLights[4].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.25f, 0.05f);
	m_pLights[4].m_fFalloff = 1.0f;
	m_pLights[4].m_fPhi = (float)cos(XMConvertToRadians(10.0f));
	m_pLights[4].m_fTheta = (float)cos(XMConvertToRadians(5.0f));
	for (int i = 5; i < 27; i++) {
		m_pLights[i].m_bEnable = false;
		m_pLights[i].m_nType = SPOT_LIGHT;
		m_pLights[i].m_fRange = 50.0f;
		m_pLights[i].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
		m_pLights[i].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		m_pLights[i].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
		m_pLights[i].m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_pLights[i].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
		m_pLights[i].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
		m_pLights[i].m_fFalloff = 8.0f;
		m_pLights[i].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
		m_pLights[i].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	}
	for (int i = 27; i < 39; i++) {
		m_pLights[i].m_bEnable = false;
		m_pLights[i].m_nType = SPOT_LIGHT;
		m_pLights[i].m_fRange = 10.0f;
		m_pLights[i].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.4f, 1.0f);
		m_pLights[i].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
		m_pLights[i].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
		m_pLights[i].m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_pLights[i].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, -1.0f);
		m_pLights[i].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
		m_pLights[i].m_fFalloff = 8.0f;
		m_pLights[i].m_fPhi = (float)cos(XMConvertToRadians(20.0f));
		m_pLights[i].m_fTheta = (float)cos(XMConvertToRadians(10.0f));
	}
	for (int i = 39; i < 43; i++) {
		m_pLights[i].m_bEnable = false;
		m_pLights[i].m_nType = SPOT_LIGHT;
		m_pLights[i].m_fRange = 30.0f;
		m_pLights[i].m_xmf4Ambient = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		m_pLights[i].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		m_pLights[i].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
		m_pLights[i].m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_pLights[i].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, -1.0f);
		m_pLights[i].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
		m_pLights[i].m_fFalloff = 1.0f;
		m_pLights[i].m_fPhi = (float)cos(XMConvertToRadians(30.0f));
		m_pLights[i].m_fTheta = (float)cos(XMConvertToRadians(10.0f));
	}
	for (int i = 43; i < 50; i++) {
		m_pLights[i].m_bEnable = false;
		m_pLights[i].m_nType = SPOT_LIGHT;
		m_pLights[i].m_fRange = 17.0f;
		m_pLights[i].m_xmf4Ambient = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		m_pLights[i].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		m_pLights[i].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
		m_pLights[i].m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_pLights[i].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_pLights[i].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
		m_pLights[i].m_fFalloff = 8.0f;
		m_pLights[i].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
		m_pLights[i].m_fTheta = (float)cos(XMConvertToRadians(70.0f));
	}
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	BuildDefaultLightsAndMaterials();
	XMFLOAT3 xmf3Scale(8.0f, 2.0f, 8.0f);
	XMFLOAT4 xmf4Color(0.0f, 0.5f, 0.0f, 0.0f);
#ifdef _WITH_TERRAIN_PARTITION
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("Image/ImageHeightMap.raw"), 257, 257, 17, 17, xmf3Scale, xmf4Color);
	//	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("../Assets/Image/Terrain/HeightMap.raw"), 257, 257, 17, 17, xmf3Scale, xmf4Color);
#else
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("Image/HeightMap.raw"), 257, 257, 257, 257, xmf3Scale, xmf4Color);
	//m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("../Assets/Image/Terrain/HeightMap.raw"), 257, 257, 257, 257, xmf3Scale, xmf4Color);
#endif
	m_pWater = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("Image/HeightMap2.raw"), 257, 257, 257, 257, xmf3Scale, xmf4Color,150);
	m_pSkyBox = new CSkyBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	m_nShaders = 6;
	m_ppShaders = new CShader*[m_nShaders];

	pObjectsShader = new CObjectsShader();
	pObjectsShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pObjectsShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, NULL);
	m_ppShaders[0] = pObjectsShader;


	/*CGSBillboardObjectsShader* pGSBillboardObjectShader = new CGSBillboardObjectsShader();
	pGSBillboardObjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pGSBillboardObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_pTerrain);*/
	
	CBillboardObjectsShader* pBillboardObjectShader = new CBillboardObjectsShader();
	pBillboardObjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pBillboardObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature,m_pTerrain);
	pBillboardObjectShader->SetActive(false);
	m_ppShaders[4] = pBillboardObjectShader;

	pMissileobjectShader = new CMissileObjectsShader();
	pMissileobjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pMissileobjectShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pMissileobjectShader->SetActive(false);
	m_ppShaders[2] = pMissileobjectShader;


	C2dUIObjectsShader* p2dUIObjectShader = new C2dUIObjectsShader();
	p2dUIObjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	p2dUIObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_pTerrain);
	p2dUIObjectShader->SetActive(false);
	m_ppShaders[1] = p2dUIObjectShader;

	pMultiSpriteObjectShader = new CMultiSpriteObjectsShader();
	pMultiSpriteObjectShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pMultiSpriteObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pMultiSpriteObjectShader->SetActive(false);
	m_ppShaders[3] = pMultiSpriteObjectShader;

	m_nParticleObjects = 1;

	m_ppParticleObjects = new CParticleObject * [m_nParticleObjects];

	m_ppParticleObjects[0] = new CParticleObject(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 65.0f, 0.0f), 0.0f, XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(8.0f, 8.0f), MAX_PARTICLES);
	
	m_nEnvironmentMappingShaders = 1;
	m_ppEnvironmentMappingShaders = new CDynamicCubeMappingShader * [m_nEnvironmentMappingShaders];

	m_ppEnvironmentMappingShaders[0] = new CDynamicCubeMappingShader(256);
	m_ppEnvironmentMappingShaders[0]->CreateShader(pd3dDevice, pd3dCommandList,m_pd3dGraphicsRootSignature);
	m_ppEnvironmentMappingShaders[0]->BuildObjects(pd3dDevice, pd3dCommandList, m_pTerrain);

	CSceneShader* pSceneShader = new CSceneShader();
	pSceneShader->CreateShader(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	pSceneShader->BuildObjects(pd3dDevice, pd3dCommandList, "Models/Scene.bin");
	m_ppShaders[5] = pSceneShader;

	

	/*m_pOutlineShader = new COutlineShader();
	m_pOutlineShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pOutlineShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);*/
	//m_pOutlineShader->pObjectsShader = pObjectsShader;

	CreateShaderVariables(pd3dDevice, pd3dCommandList);


	
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppShaders)
	{
		for (int i = 0; i < m_nShaders; i++)
		{
			m_ppShaders[i]->ReleaseShaderVariables();
			m_ppShaders[i]->ReleaseObjects();
			m_ppShaders[i]->Release();
		}
		delete[] m_ppShaders;
	}

	if (m_pOutlineShader)
	{
		m_pOutlineShader->ReleaseShaderVariables();
		delete m_pOutlineShader;
	}

	if (m_pSkyBox)	delete m_pSkyBox;
	if (m_pTerrain) delete m_pTerrain;
	if (m_pWater)	delete	m_pWater;
	if (m_ppGameObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Release();
		delete[] m_ppGameObjects;
	}
	if (m_ppParticleObjects)
	{
		for (int i = 0; i < m_nParticleObjects; i++) delete m_ppParticleObjects[i];
		delete[] m_ppParticleObjects;
	}
	ReleaseShaderVariables();


	if (m_ppEnvironmentMappingShaders)
	{
		for (int i = 0; i < m_nEnvironmentMappingShaders; i++)
		{
			m_ppEnvironmentMappingShaders[i]->ReleaseShaderVariables();
			m_ppEnvironmentMappingShaders[i]->ReleaseObjects();
			m_ppEnvironmentMappingShaders[i]->Release();
		}
		delete[] m_ppEnvironmentMappingShaders;
	}
	if (m_pLights) delete[] m_pLights;
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

#ifdef _WITH_STANDARD_TEXTURE_MULTIPLE_DESCRIPTORS
	D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[16];
	//vector<D3D12_DESCRIPTOR_RANGE>
	pd3dDescriptorRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[0].NumDescriptors = 1;
	pd3dDescriptorRanges[0].BaseShaderRegister = 6; //t6: gtxtAlbedoTexture
	pd3dDescriptorRanges[0].RegisterSpace = 0;
	pd3dDescriptorRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[1].NumDescriptors = 1;
	pd3dDescriptorRanges[1].BaseShaderRegister = 7; //t7: gtxtSpecularTexture
	pd3dDescriptorRanges[1].RegisterSpace = 0;
	pd3dDescriptorRanges[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[2].NumDescriptors = 1;
	pd3dDescriptorRanges[2].BaseShaderRegister = 8; //t8: gtxtNormalTexture
	pd3dDescriptorRanges[2].RegisterSpace = 0;
	pd3dDescriptorRanges[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[3].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[3].NumDescriptors = 1;
	pd3dDescriptorRanges[3].BaseShaderRegister = 9; //t9: gtxtMetallicTexture
	pd3dDescriptorRanges[3].RegisterSpace = 0;
	pd3dDescriptorRanges[3].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[4].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[4].NumDescriptors = 1;
	pd3dDescriptorRanges[4].BaseShaderRegister = 10; //t10: gtxtEmissionTexture
	pd3dDescriptorRanges[4].RegisterSpace = 0;
	pd3dDescriptorRanges[4].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[5].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[5].NumDescriptors = 1;
	pd3dDescriptorRanges[5].BaseShaderRegister = 11; //t11: gtxtDetailAlbedoTexture
	pd3dDescriptorRanges[5].RegisterSpace = 0;
	pd3dDescriptorRanges[5].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[6].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[6].NumDescriptors = 1;
	pd3dDescriptorRanges[6].BaseShaderRegister = 12; //t12: gtxtDetailNormalTexture
	pd3dDescriptorRanges[6].RegisterSpace = 0;
	pd3dDescriptorRanges[6].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[7].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[7].NumDescriptors = 1;
	pd3dDescriptorRanges[7].BaseShaderRegister = 13; //t13: gtxtSkyBoxTexture
	pd3dDescriptorRanges[7].RegisterSpace = 0;
	pd3dDescriptorRanges[7].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//TEXTURE추가 ->
	pd3dDescriptorRanges[8].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[8].NumDescriptors = 1;
	pd3dDescriptorRanges[8].BaseShaderRegister = 0; //t0: gtxtTexture
	pd3dDescriptorRanges[8].RegisterSpace = 0;
	pd3dDescriptorRanges[8].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//TERRAIN SHADER 추가 
	pd3dDescriptorRanges[9].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[9].NumDescriptors = 1;
	pd3dDescriptorRanges[9].BaseShaderRegister = 1; //t1: gtxtTerrainBaseTexture
	pd3dDescriptorRanges[9].RegisterSpace = 0;
	pd3dDescriptorRanges[9].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[10].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	pd3dDescriptorRanges[10].NumDescriptors = 1;
	pd3dDescriptorRanges[10].BaseShaderRegister = 3; //GameObject //b3
	pd3dDescriptorRanges[10].RegisterSpace = 0;
	pd3dDescriptorRanges[10].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[11].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[11].NumDescriptors = 1;
	pd3dDescriptorRanges[11].BaseShaderRegister = 4; //t4: gtxtGeometrytexture
	pd3dDescriptorRanges[11].RegisterSpace = 0;
	pd3dDescriptorRanges[11].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[12].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[12].NumDescriptors = 1;
	pd3dDescriptorRanges[12].BaseShaderRegister = 14; //t14: gtxtParticleTexture
	pd3dDescriptorRanges[12].RegisterSpace = 0;
	pd3dDescriptorRanges[12].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[13].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[13].NumDescriptors = 1;
	pd3dDescriptorRanges[13].BaseShaderRegister = 15; //t15: gtxtRandomTexture
	pd3dDescriptorRanges[13].RegisterSpace = 0;
	pd3dDescriptorRanges[13].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[14].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[14].NumDescriptors = 1;
	pd3dDescriptorRanges[14].BaseShaderRegister = 16; //t16: gtxtRandomOnSphereTexture
	pd3dDescriptorRanges[14].RegisterSpace = 0;
	pd3dDescriptorRanges[14].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[15].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[15].NumDescriptors = 1;
	pd3dDescriptorRanges[15].BaseShaderRegister = 17; //t17: gtxtRandomOnSphereTexture
	pd3dDescriptorRanges[15].RegisterSpace = 0;
	pd3dDescriptorRanges[15].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	
	D3D12_ROOT_PARAMETER pd3dRootParameters[22];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 33;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject B2
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[3].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[3].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[0]);
	pd3dRootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[4].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[4].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[1]);
	pd3dRootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[5].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[5].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[2]);
	pd3dRootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[6].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[6].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[3]);
	pd3dRootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[7].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[7].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[7].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[4]);
	pd3dRootParameters[7].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[8].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[8].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[8].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[5]);
	pd3dRootParameters[8].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[9].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[9].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[9].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[6]);
	pd3dRootParameters[9].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[10].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[10].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[10].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[7]);
	pd3dRootParameters[10].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[11].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[11].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[11].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[8]);//texture
	pd3dRootParameters[11].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[12].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[12].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[12].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[9]);//terrainbase txture
	pd3dRootParameters[12].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[13].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[13].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[13].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[10]);
	pd3dRootParameters[13].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	pd3dRootParameters[14].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[14].Descriptor.ShaderRegister = 5; //Timer
	pd3dRootParameters[14].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[14].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[15].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[15].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[15].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[11]);//texturearray txture
	pd3dRootParameters[15].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[16].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[16].Descriptor.ShaderRegister = 7; //Framework Info
	pd3dRootParameters[16].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[16].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[17].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[17].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[17].DescriptorTable.pDescriptorRanges = &pd3dDescriptorRanges[12]; //t14: gtxtParticleTexture
	pd3dRootParameters[17].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[18].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[18].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[18].DescriptorTable.pDescriptorRanges = &pd3dDescriptorRanges[13]; //t15: gtxtRandomTexture
	pd3dRootParameters[18].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[19].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[19].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[19].DescriptorTable.pDescriptorRanges = &pd3dDescriptorRanges[14]; //t16: gtxtRandomOnSphereTexture
	pd3dRootParameters[19].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[20].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[20].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[20].DescriptorTable.pDescriptorRanges = &pd3dDescriptorRanges[15]; //t17: gtxtRandomOnSphereTexture
	pd3dRootParameters[20].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[21].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[21].Descriptor.ShaderRegister = 8; //Framework Info
	pd3dRootParameters[21].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[21].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;



#else
	D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[2];

	pd3dDescriptorRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[0].NumDescriptors = 7;
	pd3dDescriptorRanges[0].BaseShaderRegister = 6; //t6: gtxtStandardTextures[7] //0:Albedo, 1:Specular, 2:Metallic, 3:Normal, 4:Emission, 5:DetailAlbedo, 6:DetailNormal
	pd3dDescriptorRanges[0].RegisterSpace = 0;
	pd3dDescriptorRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[1].NumDescriptors = 1;
	pd3dDescriptorRanges[1].BaseShaderRegister = 13; //t13: gtxtSkyBoxTexture
	pd3dDescriptorRanges[1].RegisterSpace = 0;
	pd3dDescriptorRanges[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_ROOT_PARAMETER pd3dRootParameters[5];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 33;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[3].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[3].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[0]);
	pd3dRootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[4].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[4].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[1]);
	pd3dRootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
#endif

	D3D12_STATIC_SAMPLER_DESC pd3dSamplerDescs[4];

	pd3dSamplerDescs[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].MipLODBias = 0;
	pd3dSamplerDescs[0].MaxAnisotropy = 1;
	pd3dSamplerDescs[0].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[0].MinLOD = 0;
	pd3dSamplerDescs[0].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[0].ShaderRegister = 0;
	pd3dSamplerDescs[0].RegisterSpace = 0;
	pd3dSamplerDescs[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dSamplerDescs[1].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].MipLODBias = 0;
	pd3dSamplerDescs[1].MaxAnisotropy = 1;
	pd3dSamplerDescs[1].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[1].MinLOD = 0;
	pd3dSamplerDescs[1].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[1].ShaderRegister = 1;
	pd3dSamplerDescs[1].RegisterSpace = 0;
	pd3dSamplerDescs[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dSamplerDescs[2].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[2].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[2].AddressV = D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
	pd3dSamplerDescs[2].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[2].MipLODBias = 0;
	pd3dSamplerDescs[2].MaxAnisotropy = 1;
	pd3dSamplerDescs[2].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[2].MinLOD = 0;
	pd3dSamplerDescs[2].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[2].ShaderRegister = 2;
	pd3dSamplerDescs[2].RegisterSpace = 0;
	pd3dSamplerDescs[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dSamplerDescs[3].Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
	pd3dSamplerDescs[3].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[3].AddressV = D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
	pd3dSamplerDescs[3].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[3].MipLODBias = 0;
	pd3dSamplerDescs[3].MaxAnisotropy = 1;
	pd3dSamplerDescs[3].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[3].MinLOD = 0;
	pd3dSamplerDescs[3].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[3].ShaderRegister = 3;
	pd3dSamplerDescs[3].RegisterSpace = 0;
	pd3dSamplerDescs[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = _countof(pd3dSamplerDescs);
	d3dRootSignatureDesc.pStaticSamplers = pd3dSamplerDescs;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytesLight = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytesLight, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);

	UINT ncbElementBytesTimer = ((sizeof(TIMER) + 255) & ~255); //256의 배수
	m_pd3dcbTimer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytesTimer, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbTimer->Map(0, NULL, (void**)&m_pcbMappedTimer);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
	::memcpy(&m_pcbMappedTimer->m_nAlpha, &fAlPha, sizeof(float));
	::memcpy(&m_pcbMappedTimer->m_nTimer, &fTimer, sizeof(float));
	XMFLOAT4X4 m_xmf4x4World = Matrix4x4::Identity();
	XMStoreFloat4x4(&m_pcbMappedTimer->m_identityview, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));

}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
	if (m_pd3dcbTimer)
	{
		m_pd3dcbTimer->Unmap(0, NULL);
		m_pd3dcbTimer->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	if (m_pSkyBox) m_pSkyBox->ReleaseUploadBuffers();
	if (m_pTerrain) m_pTerrain->ReleaseUploadBuffers();
	if (m_pWater) m_pWater->ReleaseUploadBuffers();

	for (int i = 0; i < m_nShaders; i++) m_ppShaders[i]->ReleaseUploadBuffers();
	for (int i = 0; i < m_nGameObjects; i++) m_ppGameObjects[i]->ReleaseUploadBuffers();
	for (int i = 0; i < m_nParticleObjects; i++) m_ppParticleObjects[i]->ReleaseUploadBuffers();
	for (int i = 0; i < m_nEnvironmentMappingShaders; i++) m_ppEnvironmentMappingShaders[i]->ReleaseUploadBuffers();
}

void CScene::CheckObjectByObjectCollisions(float ftimeelapsed)
{
		if (pMultiSpriteObjectShader->GetActive()) {
			CollisionTimer += ftimeelapsed;
			if (CollisionTimer > 2) 
			{
				CollisionTimer = 0;
				pMultiSpriteObjectShader->SetActive(false);
			}
		}
		// 총알과 몬스터와의 충돌체크
		if (pObjectsShader && pMissileobjectShader)
		{
			for (int i=0;i< pObjectsShader->m_nObjects;++i)
			{
				for (int j = 0; j < pMissileobjectShader->m_nObjects; ++j)
				{
					if (pObjectsShader->m_ppObjects[i]->GetActive() && pMissileobjectShader->m_ppObjects[j]->GetActive()) {
						if (pObjectsShader->m_ppObjects[i]->m_xmOOBB.Intersects(pMissileobjectShader->m_ppObjects[j]->m_xmOOBB))
						{
							pObjectsShader->m_ppObjects[i]->SetActive(FALSE);
							pMissileobjectShader->m_ppObjects[j]->SetActive(FALSE);
							for (int t = 0; t < pMultiSpriteObjectShader->m_nObjects; ++t) {
								pMultiSpriteObjectShader->SetActive(true);
								pMultiSpriteObjectShader->m_ppObjects[t]->SetPosition(pMissileobjectShader->m_ppObjects[j]->GetPosition());
							}
							break;
						}
					}
				}
			}
		}
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W': m_ppShaders[3]->m_ppObjects[1]->MoveForward(+1.0f); break;
		case 'S': m_ppShaders[3]->m_ppObjects[1]->MoveForward(-1.0f); break;
		case 'A': m_ppShaders[3]->m_ppObjects[1]->MoveStrafe(-1.0f); break;
		case 'D': m_ppShaders[3]->m_ppObjects[1]->MoveStrafe(+1.0f); break;
		case 'Q': m_ppShaders[3]->m_ppObjects[1]->MoveUp(+1.0f); break;
		case 'R': m_ppShaders[3]->m_ppObjects[1]->MoveUp(-1.0f); break;

		// 총알 발사 키
		case VK_CONTROL:
			if (pMissileobjectShader && m_pPlayer)
			{
				std::cout << typeid(VK_CONTROL).name();
				//m_pBulletShader->SetParticleShader(m_pFireParticleShader);
				pMissileobjectShader->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam,&fTimer);
			}
			break;
		case VK_F1:
			m_ppShaders[1]->SetActive(true);
			break;
		case VK_F2:
			m_ppShaders[1]->SetActive(true);
			break;
		case VK_F3:
			m_ppShaders[1]->SetActive(true);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	fTimer += fTimeElapsed;
	for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);
	for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->UpdateTransform(NULL);
	if (m_pPlayer&& pMissileobjectShader) {
		pMissileobjectShader->SetPlayer(m_pPlayer);
	}
	for (int i = 0; i < m_nShaders; i++) if (m_ppShaders[i]) m_ppShaders[i]->AnimateObjects(fTimeElapsed);
	CheckObjectByObjectCollisions(fTimeElapsed);
	if (m_pLights)
	{
		m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
		m_pLights[4].m_xmf3Position = Vector3::Add(m_pPlayer->GetPosition(), Vector3::Add(Vector3::ScalarProduct(m_pPlayer->GetLookVector(), -15.0f, false), XMFLOAT3(0.0f, 5.0f, 0.0f)));
		m_pLights[4].m_xmf3Direction = m_pPlayer->GetLookVector();
		int j = 5;


		for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
			char light2[100] = {};
			std::string light = "light";
			std::string num = std::to_string(i + 1);
			light = light + num;
			//strcpy_s(light2, );
			for (int k = 0; k < m_ppShaders[5]->m_nObjects; k++)
				if (strcmp(m_ppShaders[5]->m_ppObjects[k]->m_pstrName, light.c_str()) == 0) {
					m_pLights[j].m_bEnable = true;
					m_pLights[j].m_xmf3Position = m_ppShaders[5]->m_ppObjects[k]->GetPosition();
					m_pLights[j].m_xmf3Position.y = m_ppShaders[5]->m_ppObjects[k]->GetPosition().y + 0.3;
					j++;
					break;
				}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightblue1") == 0) {
				m_pLights[27].m_bEnable = true;
				//m_pLights[27].m_lightcolor = "blue";
				m_pLights[27].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[27].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z + 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightgreen1") == 0) {
				m_pLights[28].m_xmf4Ambient = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[28].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[28].m_xmf4Specular = XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f);
				m_pLights[28].m_bEnable = true;
				//m_pLights[28].lightcolor = "green";
				m_pLights[28].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[28].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z + 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightred1") == 0) {
				m_pLights[29].m_xmf4Ambient = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[29].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[29].m_xmf4Specular = XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f);
				m_pLights[29].m_bEnable = true;
				m_pLights[29].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[29].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z + 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightblue2") == 0) {
				m_pLights[32].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
				m_pLights[32].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
				m_pLights[32].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
				m_pLights[32].m_xmf3Direction = XMFLOAT3(-1.0f, 0.0f, 0.0f);
				m_pLights[32].m_bEnable = true;
				m_pLights[32].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[32].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x + 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightgreen2") == 0) {
				m_pLights[30].m_xmf4Ambient = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[30].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[30].m_xmf4Specular = XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f);
				m_pLights[30].m_xmf3Direction = XMFLOAT3(-1.0f, 0.0f, 0.0f);
				m_pLights[30].m_bEnable = true;
				m_pLights[30].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[30].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x + 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightred2") == 0) {
				m_pLights[31].m_xmf4Ambient = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[31].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[31].m_xmf4Specular = XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f);
				m_pLights[31].m_xmf3Direction = XMFLOAT3(-1.0f, 0.0f, 0.0f);
				m_pLights[31].m_bEnable = true;
				m_pLights[31].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[31].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x + 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightblue3") == 0) {
				m_pLights[34].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
				m_pLights[34].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
				m_pLights[34].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
				m_pLights[34].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
				m_pLights[34].m_bEnable = true;
				m_pLights[34].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[34].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightgreen3") == 0) {
				m_pLights[35].m_xmf4Ambient = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[35].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[35].m_xmf4Specular = XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f);
				m_pLights[35].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
				m_pLights[35].m_bEnable = true;
				m_pLights[35].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[35].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightred3") == 0) {
				m_pLights[33].m_xmf4Ambient = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[33].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[33].m_xmf4Specular = XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f);
				m_pLights[33].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
				m_pLights[33].m_bEnable = true;
				m_pLights[33].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[33].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightblue4") == 0) {
				m_pLights[36].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
				m_pLights[36].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
				m_pLights[36].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.5f, 0.0f);
				m_pLights[36].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
				m_pLights[36].m_bEnable = true;
				m_pLights[36].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[36].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightgreen4") == 0) {
				m_pLights[37].m_xmf4Ambient = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[37].m_xmf4Diffuse = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
				m_pLights[37].m_xmf4Specular = XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f);
				m_pLights[37].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
				m_pLights[37].m_bEnable = true;
				m_pLights[37].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[37].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "lightred4") == 0) {
				m_pLights[38].m_xmf4Ambient = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[38].m_xmf4Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
				m_pLights[38].m_xmf4Specular = XMFLOAT4(0.5f, 0.0f, 0.0f, 0.0f);
				m_pLights[38].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
				m_pLights[38].m_bEnable = true;
				m_pLights[38].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[38].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "CAR1") == 0) {
				m_pLights[39].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, -1.0f);
				m_pLights[39].m_bEnable = true;
				m_pLights[39].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				//m_pLights[38].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "CAR2") == 0) {
				m_pLights[40].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
				m_pLights[40].m_bEnable = true;
				m_pLights[40].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				//m_pLights[38].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "CAR3") == 0) {
				m_pLights[41].m_xmf3Direction = XMFLOAT3(-1.0f, 0.0f, 0.0f);
				m_pLights[41].m_bEnable = true;
				m_pLights[41].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				//m_pLights[38].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "CAR4") == 0) {
				m_pLights[42].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
				m_pLights[42].m_bEnable = true;
				m_pLights[42].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				//m_pLights[38].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z - 0.6f;
			}
			if (strcmp(m_ppShaders[5]->m_ppObjects[i]->m_pstrName, "LightWindow") == 0) {
				m_pLights[43].m_bEnable = true;
				m_pLights[43].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
				//	m_pLights[43].m_bEnable = true;
				m_pLights[43].m_xmf3Position = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				m_pLights[43].m_xmf3Position.x = m_ppShaders[5]->m_ppObjects[i]->GetPosition().x + 7;
				//m_pLights[43].m_xmf3Position.y = m_ppShaders[5]->m_ppObjects[i]->GetPosition().y + 1.25;
				//m_pLights[43].m_xmf3Position.z = m_ppShaders[5]->m_ppObjects[i]->GetPosition().z + -0.60;
			}
			//	
			//}
			/*if (m_bNight = true) {
				m_pLights[43].m_bEnable = true;
				m_pLights[43].m_xmf3Position = XMFLOAT3(-10.0f, 98.8, -393.0f);
			}*/
			for (int i = 27; i < 39; i++) {
				if (m_ftimesecond > 0 && m_ftimesecond < 5) {
					if (i % 3 == 0) {
						m_pLights[i].m_bEnable = true;
					}
					else
					{
						m_pLights[i].m_bEnable = false;
					}
				}
				if (m_ftimesecond > 5 && m_ftimesecond < 10) {
					if (i % 3 == 1) {
						m_pLights[i].m_bEnable = true;
					}
					else
					{
						m_pLights[i].m_bEnable = false;
					}
				}
				if (m_ftimesecond > 10 && m_ftimesecond < 15) {
					if (i % 3 == 2) {
						m_pLights[i].m_bEnable = true;
					}
					else
					{
						m_pLights[i].m_bEnable = false;
					}
				}
				if (m_ftimesecond > 15) {
					m_ftimesecond = 0;
				}
			}

		}

	}
	CarMove();
	CarMove2();
	CarMove3();
	CarMove4();
	m_ftimesecond += fTimeElapsed;
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	if (m_pd3dGraphicsRootSignature) pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbTimerGpuVirtualAddress = m_pd3dcbTimer->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(14, d3dcbTimerGpuVirtualAddress); //Timer


	if (m_pSkyBox) m_pSkyBox->Render(pd3dCommandList, pCamera);

	


	//if (m_pTerrain) m_pTerrain->Render(pd3dCommandList, pCamera);
	
	/*if (m_pPlayer && pMissileobjectShader) {
		pMissileobjectShader->SetPlayer(m_pPlayer);
	}*/
	for (int i = 0; i < m_nShaders; i++) if (m_ppShaders[i]) m_ppShaders[i]->Render(pd3dCommandList, pCamera);
//	for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Render(pd3dCommandList, pCamera);
	//if (m_pWater) m_pWater->Render(pd3dCommandList, pCamera);
	/*for (int i = 0; i < 10; i++) {
		if (m_ppShaders[0]->m_ppObjects[i])
		{
			m_pOutlineShader->UpdateShaderVariable(pd3dCommandList, m_ppShaders[0]->m_ppObjects[i]->m_pChild);
			m_pOutlineShader->Render(pd3dCommandList, pCamera, 0);
			m_ppShaders[0]->m_ppObjects[i]->Render(pd3dCommandList);
			m_pOutlineShader->Render(pd3dCommandList, pCamera, 1);
			m_ppShaders[0]->m_ppObjects[i]->Render(pd3dCommandList);
		}
	}*/

	for (int i = 0; i < m_nEnvironmentMappingShaders; i++)
	{
		m_ppEnvironmentMappingShaders[i]->Render(pd3dCommandList, pCamera);
	}

	//if (m_ppShaders[0])
	//{
	//	m_pOutlineShader->UpdateShaderVariable(pd3dCommandList);
	//	m_pOutlineShader->Render(pd3dCommandList, pCamera, 0);
	////	m_pSelectedObject->m_pMesh->Render(pd3dCommandList);
	//	m_pOutlineShader->Render(pd3dCommandList, pCamera, 1);
	//	//m_ppShaders[0]->m_ppObjects[1]->m_pMesh->Render(pd3dCommandList);
	//}
	
}

void CScene::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	UpdateShaderVariables(pd3dCommandList);

	if (m_pd3dcbLights)
	{
		D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
		pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights
	}
	//if (m_pd3dcbMaterials)
	//{
	//	D3D12_GPU_VIRTUAL_ADDRESS d3dcbMaterialsGpuVirtualAddress = m_pd3dcbMaterials->GetGPUVirtualAddress();
	//	pd3dCommandList->SetGraphicsRootConstantBufferView(3, d3dcbMaterialsGpuVirtualAddress); //Materials
	//}
}

void CScene::RenderParticle(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	for (int i = 0; i < m_nParticleObjects; i++) m_ppParticleObjects[i]->Render(pd3dCommandList, pCamera);
}

void CScene::OnPostRenderParticle()
{
	for (int i = 0; i < m_nParticleObjects; i++) m_ppParticleObjects[i]->OnPostRender();
}

void CScene::OnPreRender(ID3D12Device* pd3dDevice, ID3D12CommandQueue* pd3dCommandQueue, ID3D12Fence* pd3dFence, HANDLE hFenceEvent)
{
	for (int i = 0; i < m_nEnvironmentMappingShaders; i++)
	{
		m_ppEnvironmentMappingShaders[i]->OnPreRender(pd3dDevice, pd3dCommandQueue, pd3dFence, hFenceEvent, this);
	}
}

void CScene::CarMove()
{
	bool m_Stop = false;
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C') {
			if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '1') {
				XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				if (m_pLights[29].m_bEnable && TempPosition.z<-95 && TempPosition.z > -100) {
					m_Stop = true;
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C' && m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '1') {
			XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
			if (!m_Stop) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(TempPosition.x,
					TempPosition.y,
					TempPosition.z - 0.5);
				if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[4] == 'w') {
					m_ppShaders[5]->m_ppObjects[i]->Rotate(10, 0, 0);
				}
			}
			if (m_ppShaders[5]->m_ppObjects[i]->GetPosition().z < -150) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(TempPosition.x,
					TempPosition.y
					, 0);

			}
		}

	}
}

void CScene::CarMove2()
{
	bool m_Stop = false;
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C') {
			if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '2') {
				XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				if (m_pLights[38].m_bEnable && TempPosition.z > -165 && TempPosition.z < -150) {
					m_Stop = true;
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C' && m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '2') {
			XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
			if (!m_Stop) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(TempPosition.x,
					TempPosition.y,
					TempPosition.z + 0.5);
				if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[4] == 'w') {
					m_ppShaders[5]->m_ppObjects[i]->Rotate(-10, 0, 0);
				}
			}
			if (m_ppShaders[5]->m_ppObjects[i]->GetPosition().z > 20) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(TempPosition.x,
					TempPosition.y
					, -220);
			}
		}
	}


}
void CScene::CarMove3()
{
	bool m_Stop = false;
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C') {
			if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '3') {
				XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				if (m_pLights[31].m_bEnable && TempPosition.x > 1 && TempPosition.x < 10) {
					m_Stop = true;
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C' && m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '3') {
			XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
			if (!m_Stop) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(TempPosition.x - 0.5,
					TempPosition.y,
					TempPosition.z);
				if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[4] == 'w') {
					m_ppShaders[5]->m_ppObjects[i]->Rotate(10, 0, 0);
				}
			}
			if (m_ppShaders[5]->m_ppObjects[i]->GetPosition().x < -140) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(60,
					TempPosition.y
					, TempPosition.z);
			}
		}
	}
}
void CScene::CarMove4()
{
	bool m_Stop = false;
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C') {
			if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '4') {
				XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
				if (m_pLights[33].m_bEnable && TempPosition.x > -85 && TempPosition.x < -77) {
					m_Stop = true;
					break;
				}
			}
		}
	}
	for (int i = 0; i < m_ppShaders[5]->m_nObjects; i++) {
		if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[0] == 'C' && m_ppShaders[5]->m_ppObjects[i]->m_pstrName[3] == '4') {
			XMFLOAT3 TempPosition = m_ppShaders[5]->m_ppObjects[i]->GetPosition();
			if (!m_Stop) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(TempPosition.x + 0.5,
					TempPosition.y,
					TempPosition.z);
				if (m_ppShaders[5]->m_ppObjects[i]->m_pstrName[4] == 'w') {
					m_ppShaders[5]->m_ppObjects[i]->Rotate(10, 0, 0);
				}
			}
			if (m_ppShaders[5]->m_ppObjects[i]->GetPosition().x > 50) {
				m_ppShaders[5]->m_ppObjects[i]->SetPosition(-140,
					TempPosition.y
					, TempPosition.z);
			}
		}
	}
}

//state machine이 설정에 따라 달라지므로 배열로 바꾸면 된다. 오호 ->꿀
