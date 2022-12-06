#include"stdafx.h"
#include "COutlineShader.h"

COutlineShader::COutlineShader()
{
}

COutlineShader::~COutlineShader()
{
}

D3D12_INPUT_LAYOUT_DESC COutlineShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

void COutlineShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature, UINT nPipelineState)
{
	m_nPipelineStates = 2;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	ID3DBlob* pd3dVertexShaderBlob = NULL, * pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CShader::CompileShaderFromFile(L"OutlineShader.hlsl", "VSOutline", "vs_5_1", &pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CShader::CompileShaderFromFile(L"OutlineShader.hlsl", "PSOutline", "ps_5_1", &pd3dPixelShaderBlob);

	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
#ifdef _WITH_SCALING
	d3dPipelineStateDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
	d3dPipelineStateDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	d3dPipelineStateDesc.DepthStencilState.DepthEnable = FALSE;
#endif
#ifdef _WITH_NORMAL_DISPLACEMENT
	d3dPipelineStateDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
	d3dPipelineStateDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ZERO;
	d3dPipelineStateDesc.DepthStencilState.DepthEnable = FALSE;
#endif
#ifdef _WITH_PROJECTION_SPACE
	d3dPipelineStateDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
	d3dPipelineStateDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dPipelineStateDesc.DepthStencilState.DepthEnable = FALSE;
#endif
	d3dPipelineStateDesc.RasterizerState.DepthClipEnable = TRUE;
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);
	
	d3dPipelineStateDesc.VS = CShader::CompileShaderFromFile(L"OutlineShader.hlsl", "VSLighting", "vs_5_1", &pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CShader::CompileShaderFromFile(L"OutlineShader.hlsl", "PSLighting", "ps_5_1", &pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	d3dPipelineStateDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dPipelineStateDesc.DepthStencilState.DepthEnable = FALSE;
	//	d3dPipelineStateDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;

	hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[1]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void COutlineShader::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255); //256의 배수
	m_pd3dcbGameObject = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbGameObject->Map(0, NULL, (void**)&m_pcbMappedGameObject);
}

void COutlineShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	//UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);
	//for (int j = 0; j < pObjectsShader->m_nObjects; j++)
	//{
	//	CB_GAMEOBJECT_INFO* pbMappedcbGameObject = (CB_GAMEOBJECT_INFO*)((UINT8*)m_pcbMappedGameObject + (j * ncbElementBytes));
	//	XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&pObjectsShader->m_ppObjects[j]->m_xmf4x4World)));
	//	if (&pObjectsShader->m_ppObjects[j]->m_ppMaterials)
	//	{
	//		if (&pObjectsShader->m_ppObjects[j]->m_ppMaterials[0] && &pObjectsShader->m_ppObjects[j]->m_ppMaterials[0]->m_pTexture)//오류
	//		{
	//			XMStoreFloat4x4(&pbMappedcbGameObject->m_xmf4x4Texture, XMMatrixTranspose(XMLoadFloat4x4(&(pObjectsShader->m_ppObjects[j]->m_ppMaterials[0]->m_pTexture->m_xmf4x4Texture))));
	//		}
	//	}
	//}
}

void COutlineShader::UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList, CGameObject* pGameObject)
{

	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&pGameObject->m_xmf4x4World)));
	::memcpy(&m_pcbMappedGameObject->m_xmf4x4World, &xmf4x4World, sizeof(XMFLOAT4X4));
	//m_pcbMappedGameObject->m_nMaterial = pGameObject->m_pMaterial->m_nReflection;
}
void COutlineShader::ReleaseShaderVariables()
{
	if (m_pd3dcbGameObject)
	{
		m_pd3dcbGameObject->Unmap(0, NULL);
		m_pd3dcbGameObject->Release();
	}
}



void COutlineShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, UINT nPipelineState)
{
	CShader::Render(pd3dCommandList, pCamera, nPipelineState);

	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = m_pd3dcbGameObject->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(1, d3dGpuVirtualAddress);

	
}

D3D12_SHADER_BYTECODE COutlineShader::CreateVertexShader()
{
	return(CShader::CompileShaderFromFile(L"CubeMappingShader.hlsl", "VSLighting", "vs_5_1", &m_pd3dVertexShaderBlob));
}

D3D12_SHADER_BYTECODE COutlineShader::CreatePixelShader()
{
	return(CShader::CompileShaderFromFile(L"CubeMappingShader.hlsl", "PSLighting", "ps_5_1", &m_pd3dPixelShaderBlob));
}
