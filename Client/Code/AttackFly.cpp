#include "stdafx.h"
#include "AttackFly.h"

#include "Export_Utility.h"

CAttackFly::CAttackFly(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev),
	m_CenterFly(nullptr)
{
	//ZeroMemory(&m_NormalFlyList, sizeof(m_NormalFlyList));
}

CAttackFly::CAttackFly(const CAttackFly& rhs)
	: CMonster(rhs),
	m_CenterFly(rhs.m_CenterFly)
{
}

CAttackFly::~CAttackFly()
{
}

HRESULT CAttackFly::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//Create_AttackFly();
	m_bCreate = false;
	return S_OK;
}

_int CAttackFly::Update_GameObject(const _float& fTimeDelta)
{
	CGameObject::Update_GameObject(fTimeDelta);

	if (!m_bCreate)
	{
		Create_AttackFly();
		m_bCreate = true;
	}

	if (m_CenterFly != nullptr)
		m_CenterFly->Update_GameObject(fTimeDelta);

	if (!m_NormalFlyList.empty())
	{
		for (auto& iter : m_NormalFlyList)
		{
			iter->Update_GameObject(fTimeDelta);
		}
	}

	return 0;
}

void CAttackFly::LateUpdate_GameObject()
{
	__super::LateUpdate_GameObject();

	if (m_CenterFly != nullptr)
		m_CenterFly->LateUpdate_GameObject();

	if (!m_NormalFlyList.empty())
	{
		for (auto& iter : m_NormalFlyList)
		{
			iter->LateUpdate_GameObject();
		}
	}
}

void CAttackFly::Render_GameObject()
{
	for (auto& iter : m_NormalFlyList)
	{
		iter->Render_GameObject();
	}
}

HRESULT CAttackFly::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTex", pComponent });

#pragma region Texture

	// IDLE
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_AttackFlyTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_AttackFlyTexture", pComponent });

	// DEAD
	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_FlyDeadTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_FlyDeadTexture", pComponent });

#pragma endregion Texture

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_Transform", pComponent });

	pComponent = m_pCalculCom = dynamic_cast<CCalculator*>(Engine::Clone_Proto(L"Proto_Calculator"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_Calculator", pComponent });

	return S_OK;
}

void CAttackFly::Create_AttackFly()
{
	m_CenterFly = CCenterFly::Create(m_pGraphicDev);
	m_CenterFly->Get_Transform()->m_vInfo[INFO_POS] = m_pTransformCom->m_vInfo[INFO_POS];
	m_CenterFly->Set_MyLayer(m_vecMyLayer[0]);

	if (m_CenterFly == nullptr)
		return;

	for (int i = 1; i < 13; ++i)
	{
		CNormalFly* pNormalFly = CNormalFly::Create(m_pGraphicDev, i);
		pNormalFly->Set_MyLayer(m_vecMyLayer[0]);
		pNormalFly->Set_TargetTransform(m_CenterFly->Get_Transform());
		m_NormalFlyList.push_back(pNormalFly);
	}
}

CAttackFly* CAttackFly::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAttackFly* pInstance = new CAttackFly(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Attack Fly Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CAttackFly::Free()
{
	__super::Free();

	Safe_Release<CCenterFly*>(m_CenterFly);
	m_CenterFly = nullptr;

	for_each(m_NormalFlyList.begin(), m_NormalFlyList.end(), CDeleteObj());
}
