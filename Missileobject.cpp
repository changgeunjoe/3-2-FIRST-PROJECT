#include "stdafx.h"
#include "Missileobject.h"


CMissleObject::CMissleObject() :CGameObject(1, 1)
{
}

CMissleObject::~CMissleObject()
{
}

void CMissleObject::AnimateObject(float fElapsedTime)
{
	/*cout << "�߻�" << endl;
	cout << b_Active << endl;*/
	
	if (GetActive()) {
		//cout << GetActive() << endl;
		if (m_fRotationSpeed != 0.0f)
			Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fElapsedTime);
		// �Ѿ��� �̵��ӵ��� 0�� �ƴϸ� �̵��� �Ѵ�.
		m_fMovingSpeed = 100;
		if (m_fMovingSpeed != 0.0f)
			
			
			Move(m_xmf3MovingDirection, m_fMovingSpeed * fElapsedTime);
		

		// �Ѿ��� �浹�ڽ��� ��� �ִϸ���Ʈ ���־�� �Ѿ��� ��ġ�� ���Կ����� �浹 �ڽ��� ���� ��ġ�� ���Ѵ�.
		m_xmOOBBTransformed.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmOOBBTransformed.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBBTransformed.Orientation)));
	}
}

void CMissleObject::OnPrepareRender()
{
}

void CMissleObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender();

	if (m_ppMaterials)
	{
		if (m_ppMaterials[0]->m_pShader)//->���̴� 
		{
			m_ppMaterials[0]->m_pShader->Render(pd3dCommandList, pCamera);
			m_ppMaterials[0]->m_pShader->UpdateShaderVariables(pd3dCommandList);

			UpdateShaderVariables(pd3dCommandList);
		}
		if (m_ppMaterials[0]->m_pTexture)
		{
			m_ppMaterials[0]->m_pTexture->UpdateShaderVariables(pd3dCommandList);
			if (m_pcbMappedGameObject) XMStoreFloat4x4(&m_pcbMappedGameObject->m_xmf4x4Texture, XMMatrixTranspose(XMLoadFloat4x4(&m_ppMaterials[0]->m_pTexture->m_xmf4x4Texture)));
		}
	}

	pd3dCommandList->SetGraphicsRootDescriptorTable(13, m_d3dCbvGPUDescriptorHandle);

	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Render(pd3dCommandList);
		}
	}
}
void CMissleObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

void CMissleObject::Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle)
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationAxis(xmf3RotationAxis, fAngle);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}
