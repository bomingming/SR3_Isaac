#pragma once

#include "Base.h"
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CMapParts : public Engine::CUI
{
private:
	explicit CMapParts(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMapParts(const CMapParts& rhs);
	virtual ~CMapParts();

	// 현재 방 / 가본 방 / 못 가본 방
	enum ROOMSTATE{ ROOM_NOW, ROON_OPEN, ROOM_CLOSE, ROOM_END };

public:
	_int			Get_RoomNumber() { return m_iRoomNumber; }
	void			Set_RoomNumber(_int iNum) { m_iRoomNumber = iNum; }
	void			Set_NowRoom(_bool IsNowRoom) { m_bNowRoom = IsNowRoom; }

public:
	virtual HRESULT Ready_GameObject()						 override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject()					 override;
	virtual void Render_GameObject()						 override;

private:
	HRESULT			Add_Component();

private:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTransform* m_pTransformCom;
	Engine::CTexture* m_pTextureCom;

	_bool				m_bFrontRoom;
	_bool				m_bNowRoom;

	_float				m_fAnimSpeed = 1.f;
	_float				m_fCurFrame = 0.f;

	_int				m_iStartFrame;
	_int				m_iEndFrame;

	_int				m_iAnimFrameCount;
	_int				m_iMaxFrameCount;

	_int				m_iRoomNumber;

	ROOMSTATE			m_eRoomState;


public:
	static CMapParts* Create(LPDIRECT3DDEVICE9	pGraphicDev,
		_float fSizeX, _float fSizeY,
		_float fPosX, _float fPosY,
		_int iAnimFrameCount, _int iMaxFrameCount,
		_float fWinCX = WINCX, _float fWinCY = WINCY);

private:
	virtual void Free() override;
};

