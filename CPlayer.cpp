#include "pch.h"

#include "CScene.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CMissile.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer() : m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(IDB_PLAYER);

	// 이미지 싸이즈 설정
	m_Width = (int)m_pTex->Width();
	m_Height = (int)m_pTex->Height();

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 12.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

	m_pPilsalAnimTex = CResMgr::GetInst()->LoadTexture(IDB_PILSAL);
	// 필살기
	CreateAnimator();

}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT * m_iSpeed;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT * m_iSpeed;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT * m_iSpeed;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT * m_iSpeed;
	}
	if (KEY_TAP(KEY::J))
	{
		CreateMissile();
	}

	if (KEY_TAP(KEY::K))
	{
		CreatePilsal();
	}

	if (KEY_HOLD(KEY::SPACE))
	{
		m_iSpeed = 2;
	}
	if (KEY_AWAY(KEY::SPACE))
	{
		m_iSpeed = 1;
	}

	SetPos(vPos);

	GetAnimator()->update();
	if (nullptr != GetAnimator()->GetCurAnimation())
	{
		bool finish = GetAnimator()->GetCurAnimation()->IsFinish();
		if (finish)
		{
			GetAnimator()->ResetAnimation();
		}

	}
}

void CPlayer::render(HDC _dc)
{

	Vec2 vPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, int(vRenderPos.x - (float)(m_Width / 2)) // 좌상단
		, int(vRenderPos.y - (float)(m_Height / 2)) // 좌상단
		, m_Width, m_Height // 가로, 세로 길이
		, m_pTex->GetDC() // 원본 DC
		, 0, 0 // 원본 소스내의 좌상단
		, m_Width, m_Height // 원본 내에서 좌상단으로부터 길이값
		, RGB(255, 0, 255) // 무시할 색상
	);

	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	// 즉시생성하지 않고 이벤트 매니저를 통하여 지연 처리
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::CreatePilsal()
{
	GetAnimator()->CreateAnimation(std::to_wstring(IDB_PILSAL)
		, m_pPilsalAnimTex
		, Vec2(0.f, 0.f)
		, Vec2(64.f, 64.f)
		, Vec2(64.f * 15.f, 64.f * 15.f)
		, Vec2(64.f, 0.f)
		, 0.1f
		, 6
	);

	GetAnimator()->Play(std::to_wstring(IDB_PILSAL), false);
}