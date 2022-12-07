#include "stdafx.h"
#include "CDynamicCubeMappingShader.h"
#include "CDynamicCubeMappingObject.h"

CDynamicCubeMappingShader::CDynamicCubeMappingShader(UINT nCubeMapSize)
{
	m_nCubeMapSize = nCubeMapSize;
}

CDynamicCubeMappingShader::~CDynamicCubeMappingShader()
{

}

D3D12_INPUT_LAYOUT_DESC CDynamicCubeMappingShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CDynamicCubeMappingShader::CreateVertexShader()
{
	return(CShader::CompileShaderFromFile(L"CubeMappingShader.hlsl", "VSCubeMapping", "vs_5_1", &m_pd3dVertexShaderBlob));
}

D3D12_SHADER_BYTECODE CDynamicCubeMappingShader::CreatePixelShader()
{
	return(CShader::CompileShaderFromFile(L"CubeMappingShader.hlsl", "PSCubeMapping", "ps_5_1", &m_pd3dPixelShaderBlob));
}

void CDynamicCubeMappingShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, void* pContext)
{
	pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_pd3dCommandAllocator);
	pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pd3dCommandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&m_pd3dCommandList);
	m_pd3dCommandList->Close();

	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];

	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	CreateCbvSrvDescriptorHeaps(pd3dDevice, m_nObjects, m_nObjects);
	CreateConstantBufferViews(pd3dDevice, m_nObjects, m_pd3dcbGameObjects, ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255));

	D3D12_GPU_DESCRIPTOR_HANDLE d3dCbvGPUDescriptorStartHandle = m_d3dCbvGPUDescriptorStartHandle;

	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = m_nObjects;
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	HRESULT hResult = pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pd3dDsvDescriptorHeap);

	D3D12_CPU_DESCRIPTOR_HANDLE d3dDsvCPUDescriptorHandle = m_pd3dDsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

	d3dDescriptorHeapDesc.NumDescriptors = m_nObjects * 6;
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pd3dRtvDescriptorHeap);

	D3D12_CPU_DESCRIPTOR_HANDLE d3dRtvCPUDescriptorHandle = m_pd3dRtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
//	CCubeMeshTextured* m_pMissileTexturedMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 200.f, 200.f, 5.f);
	CMesh* pMeshIlluminated = new CSphereMeshIlluminated(pd3dDevice, pd3dCommandList, 20.0f, 20, 20);

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;
	XMFLOAT2 xmf2TerrainCenter = XMFLOAT2(pTerrain->GetWidth() * 0.5f, pTerrain->GetLength() * 0.5f);

	for (int i = 0; i < m_nObjects; i++)
	{
		m_ppObjects[i] = new CDynamicCubeMappingObject(pd3dDevice, pd3dCommandList, m_nCubeMapSize, d3dDsvCPUDescriptorHandle, d3dRtvCPUDescriptorHandle, this);

		m_ppObjects[i]->SetMesh(0, pMeshIlluminated);

		float xPosition = xmf2TerrainCenter.x + ((i + 1) * 150.0f) * ((i % 2) ? +1.0f : -1.0f);
		float zPosition = xmf2TerrainCenter.y + ((i + 1) * 150.0f) * ((i % 2) ? +1.0f : -1.0f);
		float fHeight = pTerrain->GetHeight(xPosition, zPosition);
		//m_ppObjects[i]->SetPosition(xPosition, fHeight + 0.0f, zPosition);
		m_ppObjects[i]->SetPosition(0, 50, 0);
		m_ppObjects[i]->SetCbvGPUDescriptorHandlePtr(d3dCbvGPUDescriptorStartHandle.ptr);

		d3dCbvGPUDescriptorStartHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
		d3dDsvCPUDescriptorHandle.ptr += ::gnDsvDescriptorIncrementSize;
		d3dRtvCPUDescriptorHandle.ptr += (::gnRtvDescriptorIncrementSize * 6);
	}
}

void CDynamicCubeMappingShader::ReleaseObjects()
{
	CObjectsShader::ReleaseObjects();

	if (m_pd3dDsvDescriptorHeap) m_pd3dDsvDescriptorHeap->Release();
	if (m_pd3dRtvDescriptorHeap) m_pd3dRtvDescriptorHeap->Release();

	if (m_pd3dCommandAllocator) m_pd3dCommandAllocator->Release();
	if (m_pd3dCommandList) m_pd3dCommandList->Release();
}

void CDynamicCubeMappingShader::ReleaseUploadBuffers()
{
	CObjectsShader::ReleaseUploadBuffers();
}

void CDynamicCubeMappingShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];//파이프라인을 배열로 여기서 만든다.

	CShader::CreateShader(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature);

	if (m_pd3dVertexShaderBlob) m_pd3dVertexShaderBlob->Release();
	if (m_pd3dPixelShaderBlob) m_pd3dPixelShaderBlob->Release();

	if (m_d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] m_d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CDynamicCubeMappingShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CObjectsShader::Render(pd3dCommandList, pCamera);
}

void CDynamicCubeMappingShader::OnPreRender(ID3D12Device* pd3dDevice, ID3D12CommandQueue* pd3dCommandQueue, ID3D12Fence* pd3dFence, HANDLE hFenceEvent, CScene* pScene)
{
	for (int i = 0; i < m_nObjects; i++)
	{
		m_pd3dCommandAllocator->Reset();
		m_pd3dCommandList->Reset(m_pd3dCommandAllocator, NULL);

		m_ppObjects[i]->OnPreRender(m_pd3dCommandList, pScene);

		m_pd3dCommandList->Close();

		ID3D12CommandList* ppd3dCommandLists[] = { m_pd3dCommandList };
		pd3dCommandQueue->ExecuteCommandLists(1, ppd3dCommandLists);

		UINT64 nFenceValue = pd3dFence->GetCompletedValue();
		::WaitForGpuComplete(pd3dCommandQueue, pd3dFence, nFenceValue + 1, hFenceEvent);
	}
}
