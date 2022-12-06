#pragma once
#include"stdafx.h"
#include"Object.h"
#include"Scene.h"
class CDynamicCubeMappingObject : public CGameObject
{
public:
	CDynamicCubeMappingObject(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, LONG nCubeMapSize, D3D12_CPU_DESCRIPTOR_HANDLE d3dDsvCPUDescriptorHandle, D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle, CShader* pShader);
	virtual ~CDynamicCubeMappingObject();

	virtual void OnPreRender(ID3D12GraphicsCommandList* pd3dCommandList, CScene* pScene);

	CCamera* m_ppCameras[6];

	D3D12_CPU_DESCRIPTOR_HANDLE		m_pd3dRtvCPUDescriptorHandles[6];


	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	ID3D12Resource* m_pd3dDepthStencilBuffer = NULL;
	D3D12_CPU_DESCRIPTOR_HANDLE		m_d3dDsvCPUDescriptorHandle;
};

