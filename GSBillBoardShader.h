#pragma once
#pragma once
#include"stdafx.h"
#include"Shader.h"
#include"Player.h"

class CGSBillboardObjectsShader : public CObjectsShader
{
public:
	CGSBillboardObjectsShader();
	virtual ~CGSBillboardObjectsShader();

	virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
	virtual D3D12_BLEND_DESC CreateBlendState();
	virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();

	virtual void CreateShader(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature);
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);

	virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext = NULL);
	virtual void ReleaseObjects();
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, int pipelinestate);

	virtual void ReleaseUploadBuffers();
	virtual void ReleaseShaderVariables();



	virtual D3D12_SHADER_BYTECODE CreateVertexShader();
	virtual D3D12_SHADER_BYTECODE CreateGeometryShader();
	virtual D3D12_SHADER_BYTECODE CreatePixelShader();

	// 빌보드 정점 리소스 생성
	ID3D12Resource* m_pd3dVertexUploadBuffer = nullptr;
	ID3D12Resource* m_pd3dVertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	m_d3dVertexBufferView;
	D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;

	D3D12_GPU_DESCRIPTOR_HANDLE		m_d3dCbvGPUDescriptorHandle;

	int									m_nVertices;
	int									m_nStride;

#ifdef _WITH_BATCH_MATERIAL
	CMaterial* m_ppGrassMaterials[2] = { NULL, NULL };
	CMaterial* m_ppFlowerMaterials[2] = { NULL, NULL };
#endif
};