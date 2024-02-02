#pragma once

#include "Item.h"
#include "GameObject.h"

class CSadOnion : public CItem
{
	explicit CSadOnion(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSadOnion(const CSadOnion& rhs);
	virtual ~CSadOnion();

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void	LateUpdate_GameObject()					 override;
	virtual void	Render_GameObject()						 override;

public:
	void			Run_Item_Effect()						override;

private:
	virtual HRESULT		Add_Component()						override;
	virtual void		Motion_Change()						override;


private:
	// 랜덤값으로 한 이미지 지정하면 계속 유지
	_float					m_fPicNum;

public:
	static CSadOnion* Create(LPDIRECT3DDEVICE9 pGraphicDev, int spawnspot);

private:
	virtual void		Free()									override;
};

