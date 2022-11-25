#include"stdafx.h"
#include"GSBillBoardShader.h"


CGSBillboardObjectsShader::CGSBillboardObjectsShader()
{
}

CGSBillboardObjectsShader::~CGSBillboardObjectsShader()
{

		ReleaseShaderVariables();
		ReleaseUploadBuffers();
}

D3D12_RASTERIZER_DESC CGSBillboardObjectsShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));

	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;

	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
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


	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;

	int nTerrainWidth = int(pTerrain->GetWidth());
	int nTerrainLength = int(pTerrain->GetLength());

	CTexture* ppGrassTextures[1];
	ppGrassTextures[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppGrassTextures[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"BillboardImage/Grass01.dds", RESOURCE_TEXTURE2D, 0);
	
	



	CreateCbvSrvDescriptorHeaps(pd3dDevice, m_nObjects, 1);

	CreateShaderResourceViews(pd3dDevice, ppGrassTextures[0], 0, 11);
	float TreeHeight = 100.f;
	int nStride = sizeof(CBillboardVertex);
	m_nVertices = 30000;
	XMFLOAT3 xmf3Position = XMFLOAT3(0.f, 0.f, 0.f);
	CBillboardVertex* pBillboardVertex = new CBillboardVertex[m_nVertices];

	default_random_engine dre;
	uniform_real_distribution<double> urd_x(0.f, nTerrainWidth - 100);
	uniform_real_distribution<double> urd_z(0.f, nTerrainLength - 100);
	int x = 0, y = 0, z = 0;
	//	CreateShader(pd3dDevice,  pd3dCommandList,pd3dGraphicsRootSignature);
	CMaterial* ppGrassMaterials[1]; //->메테리얼 생성 텍스쳐와 쉐이더를 넣어야되는데 쉐이더이므로 안 넣어도 됨
	ppGrassMaterials[0] = new CMaterial();
	ppGrassMaterials[0]->SetTexture(ppGrassTextures[0]);

	/*CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);*/
	

	for (int i = 0; i < m_nVertices;)
	{
		x = urd_x(dre) / 8;
		z = urd_z(dre) / 8;
		if (m_PositionArray[x][z] == 1)
		{
			x = x * 8.;
			z = z * 8.;
			y = pTerrain->GetHeight(x, z);

			xmf3Position.x = x;
			xmf3Position.z = z;
			xmf3Position.y = pTerrain->GetHeight(x, z) + TreeHeight * 0.3f;
			pBillboardVertex[i].m_xmf3Position = xmf3Position;
			pBillboardVertex[i].m_xmf2Size = XMFLOAT2(50, 70);
			++i;
		}
		else
			continue;
	}
	m_pd3dVertexBuffer = ::CreateBufferResource
	(
		pd3dDevice,
		pd3dCommandList,
		pBillboardVertex,
		nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT,
		D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
		&m_pd3dVertexUploadBuffer
	);

	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = nStride;
	m_d3dVertexBufferView.SizeInBytes = nStride * m_nVertices;

	cout << "기하셰이더 빌보드 오브젝트 개수 : " << m_nVertices << "개 생성완료" << endl;
	if (pBillboardVertex)
		delete[] pBillboardVertex;
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

	::ZeroMemory(&m_d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	m_d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	m_d3dPipelineStateDesc.VS = CreateVertexShader();
	m_d3dPipelineStateDesc.GS = CreateGeometryShader();
	m_d3dPipelineStateDesc.PS = CreatePixelShader();
	m_d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	m_d3dPipelineStateDesc.BlendState = CreateBlendState();
	m_d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	m_d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	m_d3dPipelineStateDesc.SampleMask = UINT_MAX;
	m_d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	m_d3dPipelineStateDesc.NumRenderTargets = 1;
	m_d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_d3dPipelineStateDesc.SampleDesc.Count = 1;
	m_d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	//HRESULT hResult = pd3dDevice->(&m_d3dPipelineStateDesc, __uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);//파이프라인 스테이트를 만들었다.

	if (m_pd3dVertexShaderBlob) m_pd3dVertexShaderBlob->Release();
	if (m_pd3dPixelShaderBlob) m_pd3dPixelShaderBlob->Release();
	if (m_pd3dGeometeryShaderBlob) m_pd3dGeometeryShaderBlob->Release();

	if (m_d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] m_d3dPipelineStateDesc.InputLayout.pInputElementDescs;
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
	return (CShader::CompileShaderFromFile(L"Shaders.hlsl", "GS", "gs_5_1", &m_pd3dGeometeryShaderBlob));
}
D3D12_SHADER_BYTECODE CGSBillboardObjectsShader::CreatePixelShader()
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PS_Geometry", "ps_5_1", &m_pd3dPixelShaderBlob));
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

