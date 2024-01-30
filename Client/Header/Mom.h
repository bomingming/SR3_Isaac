#pragma once

#include "Monster.h"
#include "GameObject.h"

class CMom : public CMonster
{
private:
	explicit CMom(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMom(const CMom& rhs);
	virtual ~CMom();

	enum MOMSTATE{ MOM_IDLE, MOM_ATTACK, MOM_UP, MOM_WAIT, MOM_END }; // 필요 없을 거 같음

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject()					 override;
	virtual void	Render_GameObject()						 override;
	
private:
	virtual HRESULT		Add_Component()						override;
	virtual void		Motion_Change()						override;

	void				Attack(const _float& fTimeDelta);
	void				Scale_Change();

private:
	_bool				m_bReduce;
	_int				m_iRandNum;
	_int				m_iPicNum;
	_float				m_fFrameSpeed = 1.f;

	MOMSTATE			m_eState;

public:
	static CMom*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void	Free()									override;
};

