#include"stdafx.h"
#include"GSBillBoardShader.h"


CGSBillboardObjectsShader::CGSBillboardObjectsShader()
{
}

CGSBillboardObjectsShader::~CGSBillboardObjectsShader()
{
}

D3D12_RASTERIZER_DESC CGSBillboardObjectsShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	//	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

D3D12_BLEND_DESC CGSBillboardObjectsShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = TRUE;
	d3dBlendDesc.IndependentBlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

void CGSBillboardObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext)
{
	CTexture* ppGrassTextures[2];
	ppGrassTextures[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppGrassTextures[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Grass01.dds", RESOURCE_TEXTURE2D, 0);
	ppGrassTextures[1] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppGrassTextures[1]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Grass02.dds", RESOURCE_TEXTURE2D, 0);

	CTexture* ppFlowerTextures[2];
	ppFlowerTextures[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppFlowerTextures[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Flower01.dds", RESOURCE_TEXTURE2D, 0);
	ppFlowerTextures[1] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppFlowerTextures[1]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Flower02.dds", RESOURCE_TEXTURE2D, 0);

	CTexture* ppTreeTextures[3];
	ppTreeTextures[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppTreeTextures[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Tree01.dds", RESOURCE_TEXTURE2D, 0);
	ppTreeTextures[1] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppTreeTextures[1]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Tree02.dds", RESOURCE_TEXTURE2D, 0);
	ppTreeTextures[2] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppTreeTextures[2]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Tree03.dds", RESOURCE_TEXTURE2D, 0);

	CMaterial* ppGrassMaterials[2]; //->메테리얼 생성 텍스쳐와 쉐이더를 넣어야되는데 쉐이더이므로 안 넣어도 됨
	ppGrassMaterials[0] = new CMaterial();
	ppGrassMaterials[0]->SetTexture(ppGrassTextures[0]);
	ppGrassMaterials[1] = new CMaterial();
	ppGrassMaterials[1]->SetTexture(ppGrassTextures[1]);

	CMaterial* ppFlowerMaterials[2];
	ppFlowerMaterials[0] = new CMaterial();
	ppFlowerMaterials[0]->SetTexture(ppFlowerTextures[0]);
	ppFlowerMaterials[1] = new CMaterial();
	ppFlowerMaterials[1]->SetTexture(ppFlowerTextures[1]);

	CMaterial* ppTreeMaterials[3];
	ppTreeMaterials[0] = new CMaterial();
	ppTreeMaterials[0]->SetTexture(ppTreeTextures[0]);
	ppTreeMaterials[1] = new CMaterial();
	ppTreeMaterials[1]->SetTexture(ppTreeTextures[1]);
	ppTreeMaterials[2] = new CMaterial();
	ppTreeMaterials[2]->SetTexture(ppTreeTextures[2]);

	/*CCubeMeshTextured* pGrassMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 10.f, 10.5f, 5.f);
	CCubeMeshTextured* pFlowerMesh = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 10.f, 10.5f, 5.f);
	CCubeMeshTextured* pTreeMesh01 = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 10.f, 10.5f, 5.f);
	CCubeMeshTextured* pTreeMesh02 = new CCubeMeshTextured(pd3dDevice, pd3dCommandList, 10.f, 10.5f, 5.f);*/
	CTexturedRectMesh* pGrassMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 8.0f, 8.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	CTexturedRectMesh* pFlowerMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 8.0f, 16.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	CTexturedRectMesh* pTreeMesh01 = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 24.0f, 36.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	CTexturedRectMesh* pTreeMesh02 = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 16.0f, 46.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	CRawFormatImage* pRawFormatImage = new CRawFormatImage(L"BillboardImage/ObjectsMap.raw", 257, 257, true);

	int nGrassObjects = 0, nFlowerObjects = 0, nBlacks = 0, nOthers = 0, nTreeObjects[3] = { 0, 0, 0 };
	for (int z = 2; z <= 254; z++)
	{
		for (int x = 2; x <= 254; x++)
		{
			BYTE nPixel = pRawFormatImage->GetRawImagePixel(x, z);
			switch (nPixel)
			{
			case 102: nGrassObjects++; break;
			case 128: nGrassObjects++; break;
			case 153: nFlowerObjects++; break;
			case 179: nFlowerObjects++; break;
			case 204: nTreeObjects[0]++; break;
			case 225: nTreeObjects[1]++; break;
			case 255: nTreeObjects[2]++; break;
			case 0: nBlacks++; break;
			default: nOthers++; break;
			}
		}
	}
	m_nObjects = nGrassObjects + nFlowerObjects + nTreeObjects[0] + nTreeObjects[1] + nTreeObjects[2];

	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	//	CreateShader(pd3dDevice,  pd3dCommandList,pd3dGraphicsRootSignature);
	CreateCbvSrvDescriptorHeaps(pd3dDevice, m_nObjects, 7);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, ppGrassTextures[0], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppGrassTextures[1], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppFlowerTextures[0], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppFlowerTextures[1], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppTreeTextures[0], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppTreeTextures[1], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppTreeTextures[2], 0, 11);

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;

	int nTerrainWidth = int(pTerrain->GetWidth());
	int nTerrainLength = int(pTerrain->GetLength());

	XMFLOAT3 xmf3Scale = pTerrain->GetScale();

	m_ppObjects = new CGameObject * [m_nObjects];

	CGrassObject* pBillboardObject = NULL;
	for (int nObjects = 0, z = 2; z <= 254; z++)
	{
		for (int x = 2; x <= 254; x++)
		{
			BYTE nPixel = pRawFormatImage->GetRawImagePixel(x, z);

			float fyOffset = 0.0f;

			CMaterial* pMaterial = NULL;
			CMesh* pMesh = NULL;

			switch (nPixel)
			{
			case 102:
				pMesh = pGrassMesh;
				pMaterial = ppGrassMaterials[0];
				fyOffset = 8.0f * 0.5f;
				break;
			case 128:
				pMesh = pGrassMesh;
				pMaterial = ppGrassMaterials[1];
				fyOffset = 6.0f * 0.5f;
				break;
			case 153:
				pMesh = pFlowerMesh;
				pMaterial = ppFlowerMaterials[0];
				fyOffset = 16.0f * 0.5f;
				break;
			case 179:
				pMesh = pFlowerMesh;
				pMaterial = ppFlowerMaterials[1];
				fyOffset = 16.0f * 0.5f;
				break;
			case 204:
				pMesh = pTreeMesh01;
				pMaterial = ppTreeMaterials[0];
				fyOffset = 33.0f * 0.5f;
				break;
			case 225:
				pMesh = pTreeMesh01;
				pMaterial = ppTreeMaterials[1];
				fyOffset = 33.0f * 0.5f;
				break;
			case 255:
				pMesh = pTreeMesh02;
				pMaterial = ppTreeMaterials[2];
				fyOffset = 40.0f * 0.5f;
				break;
			default:
				break;
			}

			if (pMesh && pMaterial)
			{
				pBillboardObject = new CGrassObject();

				pBillboardObject->SetMesh(0, pMesh);
				pBillboardObject->SetMaterial(0, pMaterial);

				float xPosition = x * xmf3Scale.x;
				float zPosition = z * xmf3Scale.z;
				float fHeight = pTerrain->GetHeight(xPosition, zPosition);
				pBillboardObject->SetPosition(xPosition, fHeight + fyOffset, zPosition);
				pBillboardObject->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nObjects));

				m_ppObjects[nObjects++] = pBillboardObject;
			}
		}
	}
}

void CGSBillboardObjectsShader::ReleaseUploadBuffers()
{
	if (m_pd3dVertexBuffer)
		m_pd3dVertexBuffer->Release();
	m_pd3dVertexBuffer = nullptr;
}
void CGSBillboardObjectsShader::ReleaseShaderVariables()
{
	if (m_pd3dVertexBuffer)
		m_pd3dVertexBuffer->Release();
	m_pd3dVertexBuffer = nullptr;
}
void CGSBillboardObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader();
	d3dPipelineStateDesc.GS = CreateGeometryShader();
	d3dPipelineStateDesc.PS = CreatePixelShader();
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	HRESULT hResult = pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);

	if (m_pd3dVertexShaderBlob) m_pd3dVertexShaderBlob->Release();
	if (m_pd3dPixelShaderBlob) m_pd3dPixelShaderBlob->Release();
	if (m_pd3dGeometeryShaderBlob) m_pd3dGeometeryShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}
void CGSBillboardObjectsShader::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
}
void CGSBillboardObjectsShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
}
D3D12_INPUT_LAYOUT_DESC CGSBillboardObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "SIZE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE CGSBillboardObjectsShader::CreateVertexShader()
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VS_Geometry", "vs_5_1", &m_pd3dVertexShaderBlob));
}
D3D12_SHADER_BYTECODE CGSBillboardObjectsShader::CreateGeometryShader()
{
	return (CShader::CompileShaderFromFile(L"Shaders.hlsl", "GS", "gs_5_1", &m_pd3dVertexShaderBlob));
}
D3D12_SHADER_BYTECODE CGSBillboardObjectsShader::CreatePixelShader()
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSBillBoardTextured", "ps_5_1", &m_pd3dPixelShaderBlob));
}
void CGSBillboardObjectsShader::ReleaseObjects()
{
	CObjectsShader::ReleaseObjects();
}

void CGSBillboardObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, int pipelinestate)
{
	XMFLOAT3 xmf3CameraPosition = pCamera->GetPosition();
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]) m_ppObjects[j]->SetBillboardLookAt(xmf3CameraPosition, XMFLOAT3(0.0f, 1.0f, 0.0f));
	}

	CObjectsShader::Render(pd3dCommandList, pCamera);
}

