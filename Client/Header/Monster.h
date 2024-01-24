#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class CTriCol;
class CTransform;

END

class CMonster :	public Engine::CGameObject
{
private:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonster(const CMonster& rhs);
	virtual ~CMonster();

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject()					 override;
	virtual void Render_GameObject()						 override;

private:
	HRESULT			Add_Component();

private:
	Engine::CTriCol*		m_pBufferCom;
	Engine::CTransform*		m_pTransformCom;

public:
	static CMonster*		Create(LPDIRECT3DDEVICE9	pGraphicDev);

private:
	virtual void Free() override;
};

