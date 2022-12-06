#include"stdafx.h"
#include"2dUIObjectsShader.h"

C2dUIObjectsShader::C2dUIObjectsShader()
{
}

C2dUIObjectsShader::~C2dUIObjectsShader()
{
}

D3D12_RASTERIZER_DESC C2dUIObjectsShader::CreateRasterizerState()
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

D3D12_BLEND_DESC C2dUIObjectsShader::CreateBlendState()
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
	//
	//	D3D12_BLEND_DESC d3dBlendDesc;
	//::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	//d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	//d3dBlendDesc.IndependentBlendEnable = FALSE;
	//d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	//d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	//d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	//d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	//d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	//d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	//d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	//d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	//d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	//d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	//
	//return(d3dBlendDesc);
}

void C2dUIObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext)
{
	CTexture* ppMiniMapTexture[1];
	ppMiniMapTexture[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppMiniMapTexture[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"Image/Base_Texture.dds", RESOURCE_TEXTURE2D, 0);//미니맵 텍스 쳐생성

	CMaterial* ppMiniMapMaterials[1]; //->메테리얼 생성 텍스쳐와 쉐이더를 넣어야되는데 쉐이더이므로 안 넣어도 됨
	ppMiniMapMaterials[0] = new CMaterial();
	ppMiniMapMaterials[0]->SetTexture(ppMiniMapTexture[0]);

	CTexture* ppHPBarTexture[1];
	ppHPBarTexture[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppHPBarTexture[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"UIimage/hpBar2.dds", RESOURCE_TEXTURE2D, 0);//미니맵 텍스 쳐생성

	CMaterial* ppHPBarMaterials[1]; //->메테리얼 생성 텍스쳐와 쉐이더를 넣어야되는데 쉐이더이므로 안 넣어도 됨
	ppHPBarMaterials[0] = new CMaterial();
	ppHPBarMaterials[0]->SetTexture(ppHPBarTexture[0]);

	CTexture* ppHeli2dUITexture[1];
	ppHeli2dUITexture[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppHeli2dUITexture[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"UIimage/HeliUI.dds", RESOURCE_TEXTURE2D, 0);//헬기맵 텍스 쳐생성

	CMaterial* ppHeli2dUIMaterials[1]; //->메테리얼 생성 텍스쳐와 쉐이더를 넣어야되는데 쉐이더이므로 안 넣어도 됨
	ppHeli2dUIMaterials[0] = new CMaterial();
	ppHeli2dUIMaterials[0]->SetTexture(ppHeli2dUITexture[0]);


	CTexture* ppCrosshairTexture[1];
	ppCrosshairTexture[0] = new CTexture(1, RESOURCE_TEXTURE2D, 0, 1);
	ppCrosshairTexture[0]->LoadTextureFromFile(pd3dDevice, pd3dCommandList, L"UIimage/Crosshair.dds", RESOURCE_TEXTURE2D, 0);//헬기맵 텍스 쳐생성

	CMaterial* ppCrosshairMaterials[1]; //->메테리얼 생성 텍스쳐와 쉐이더를 넣어야되는데 쉐이더이므로 안 넣어도 됨
	ppCrosshairMaterials[0] = new CMaterial();
	ppCrosshairMaterials[0]->SetTexture(ppCrosshairTexture[0]);

	CTexturedRectMesh* pMiniMapMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 4.0f, 4.0f, 0.0f, 5.0f, 5.0f, 0.0f);
	CTexturedRectMesh* pHPBarMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 4.0f, 2.0f, 0.0f, 5.0f, 5.0f, 0.0f);
	CTexturedRectMesh* pHeli2dUIBarMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 10.0f, 10.0f, 0.0f, 5.0f, 5.0f, 0.0f);
	CTexturedRectMesh* pCrosshairMesh = new CTexturedRectMesh(pd3dDevice, pd3dCommandList, 2.0f, 2.0f, 0.0f, 5.0f, 5.0f, 0.0f);


	//CRawFormatImage* pRawFormatImage = new CRawFormatImage(L"BillboardImage/ObjectsMap.raw", 257, 257, true);
	m_nObjects = 2;
	UINT ncbElementBytes = ((sizeof(CB_GAMEOBJECT_INFO) + 255) & ~255);

	//CreateShader(pd3dDevice,  pd3dCommandList,pd3dGraphicsRootSignature);
	CreateCbvSrvDescriptorHeaps(pd3dDevice, m_nObjects, 4);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	CreateConstantBufferViews(pd3dDevice, m_nObjects, m_pd3dcbGameObjects, ncbElementBytes);
	CreateShaderResourceViews(pd3dDevice, ppMiniMapTexture[0], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppHPBarTexture[0], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppHeli2dUITexture[0], 0, 11);
	CreateShaderResourceViews(pd3dDevice, ppCrosshairTexture[0], 0, 11);


	m_ppObjects = new CGameObject * [m_nObjects];//UI오브젝트의 개수

	CUiObject* pUiObject[4]{};
	CHPObject* pHpObject = NULL;
	CMaterial* pMaterial = NULL;
	CMesh* pMesh = NULL;
	int nObjects = 0;
	/*case 102:
	pMesh = pGrassMesh;
	pMaterial = ppGrassMaterials[0];*/
	int i = 0;
	pUiObject[0] = new CUiObject();

	pUiObject[0]->SetMesh(0, pMiniMapMesh);
	pUiObject[0]->SetMaterial(0, ppMiniMapMaterials[0]);
	pUiObject[0]->SetPosition(15, 8.5, 30);
	pUiObject[0]->Rotate(0.0f, 180.0f, 0.0f);
	pUiObject[0]->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nObjects));
	m_ppObjects[nObjects++] = pUiObject[0];

	pUiObject[1] = new CUiObject();

	pUiObject[1]->SetMesh(0, pHPBarMesh);
	pUiObject[1]->SetMaterial(0, ppHPBarMaterials[0]);
	pUiObject[1]->SetPosition(0, -15, 20);
	pUiObject[1]->Rotate(0.0f, 180.0f, 0.0f);
	pUiObject[1]->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nObjects));
	m_ppObjects[nObjects++] = pUiObject[1];

	/*pUiObject[2] = new CUiObject();

	pUiObject[2]->SetMesh(0, pHeli2dUIBarMesh);
	pUiObject[2]->SetMaterial(0, ppHeli2dUIMaterials[0]);
	pUiObject[2]->SetPosition(0, 0, 10);
	pUiObject[2]->Rotate(0.0f, 180.0f, 0.0f);
	pUiObject[2]->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nObjects));
	m_ppObjects[nObjects++] = pUiObject[2];*/

	/*pUiObject[3] = new CUiObject();

	pUiObject[3]->SetMesh(0, pCrosshairMesh);
	pUiObject[3]->SetMaterial(0, ppCrosshairMaterials[0]);
	pUiObject[3]->SetPosition(0, -100, 10);
	pUiObject[3]->Rotate(0.0f, 180.0f, 0.0f);
	pUiObject[3]->SetCbvGPUDescriptorHandlePtr(m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nObjects));
	m_ppObjects[nObjects++] = pUiObject[3];*/
}

void C2dUIObjectsShader::ReleaseUploadBuffers()
{
	CObjectsShader::ReleaseUploadBuffers();
}
void C2dUIObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];//파이프라인을 배열로 여기서 만든다.

	CShader::CreateShader(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature);

	if (m_pd3dVertexShaderBlob) m_pd3dVertexShaderBlob->Release();
	if (m_pd3dPixelShaderBlob) m_pd3dPixelShaderBlob->Release();

	if (m_d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[] m_d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}
D3D12_INPUT_LAYOUT_DESC C2dUIObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}
D3D12_SHADER_BYTECODE C2dUIObjectsShader::CreateVertexShader()
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSUITextured", "vs_5_1", &m_pd3dVertexShaderBlob));
}
D3D12_SHADER_BYTECODE C2dUIObjectsShader::CreatePixelShader()
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSUITextured", "ps_5_1", &m_pd3dPixelShaderBlob));
}
void C2dUIObjectsShader::ReleaseObjects()
{
	CObjectsShader::ReleaseObjects();
}

void C2dUIObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera, int pipelinestate)
{
	/*XMFLOAT3 xmf3CameraPosition = pCamera->GetPosition();
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j]) m_ppObjects[j]->SetBillboardLookAt(xmf3CameraPosition, XMFLOAT3(0.0f, 1.0f, 0.0f));
	}*/
	if(GetActive())
	CObjectsShader::Render(pd3dCommandList, pCamera);
}