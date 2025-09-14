#include "pch.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CScene.h"

#include "CTexture.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(5)
	, m_pTex(nullptr)
{
	int r = std::rand();
	m_iDir = (r % 2 == 0) ? 1 : -1;
	m_fSpeed = ((r * 0.0001f) * 40) + 10;

	m_pTex = CResMgr::GetInst()->LoadTexture(IDB_ENEMY);
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));

	// 이미지 싸이즈 설정
	m_Width = (int)m_pTex->Width();
	m_Height = (int)m_pTex->Height();

	m_pDeadTex = CResMgr::GetInst()->LoadTexture(IDB_PUNG);
	// 소멸
	CreateAnimator();
	GetAnimator()->CreateAnimation(std::to_wstring(IDB_PUNG)
		, m_pDeadTex
		, Vec2(0.f, 0.f)
		, Vec2(64.f, 64.f)
		, Vec2(64.f, 64.f)
		, Vec2(64.f, 0.f)
		, 0.1f
		, 3
	);

}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	vCurPos.x += fDT * m_fSpeed * m_iDir;

	float fDist = abs(vCurPos.x - m_vCenterPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	if (std::rand() % 3000 == 0)
	{
		if (std::rand() % 2 == 0)
			CreateMultiMissile();
		else if (std::rand() % 2 == 1)
			CreateMultiFullMissile();
		else
			CreateMissile();
	}

	SetPos(vCurPos);

	GetAnimator()->update();

	// 몬스터 파괴 애니메이션
	if (nullptr != GetAnimator()->GetCurAnimation())
	{
		bool finish = GetAnimator()->GetCurAnimation()->IsFinish();
		if (finish)
		{
			DeleteObject(this);
		}
	}

}

void CMonster::render(HDC _dc)
{
	HDC hdcTmp = CreateCompatibleDC(_dc);
	HBITMAP hbmTmp = CreateCompatibleBitmap(_dc, m_Width, m_Height);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTmp, hbmTmp);

	Vec2 vPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	StretchBlt(hdcTmp
		, 0, 0
		, m_Width, m_Height
		, m_pTex->GetDC()
		, m_Width - 1, m_Height - 1
		, -m_Width, -m_Height
		, SRCCOPY);

	TransparentBlt(_dc
		, int(vRenderPos.x - (float)(m_Width / 2)) // 좌상단
		, int(vRenderPos.y - (float)(m_Height / 2)) // 좌상단
		, m_Width, m_Height // 가로, 세로 길이
		, hdcTmp // 원본 DC
		, 0, 0 // 원본 소스내의 좌상단
		, m_Width, m_Height // 원본 내에서 좌상단으로부터 길이값
		, RGB(255, 0, 255) // 무시할 색상
	);

	SelectObject(hdcTmp, hbmOld);
	DeleteObject(hbmTmp);
	DeleteDC(hdcTmp);

	component_render(_dc);
}

void CMonster::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, 1.f));

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::CreateMultiMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (size_t i = 0; i < 3.f; ++i)
	{
		CMissile* pMissile = new CMissile;
		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(25.f, 25.f));
		if (i == 0)
			pMissile->SetDir(Vec2(1.f, 1.f));
		else if (i == 1)
			pMissile->SetDir(Vec2(0.f, 1.f));
		else
			pMissile->SetDir(Vec2(-1.f, 1.f));

		pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
	}
}

void CMonster::CreateMultiFullMissile()
{
	int bullCnt = 20;
	float angleStep = 360.f / bullCnt;

	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (int i = 0; i < bullCnt; ++i)
	{
		float angle = i * angleStep;
		float rad = angle * (PI / 180.0f);

		CMissile* pMissile = new CMissile;
		pMissile->SetPos(vMissilePos);
		pMissile->SetDir(Vec2(cos(rad), sin(rad)));

		pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
	}
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		m_iHP -= 1;

		if (m_iHP <= 0)
		{
			GetAnimator()->Play(std::to_wstring(IDB_PUNG), false);
			m_Width = 1;
			m_Height = 1;

			/*bool finish = GetAnimator()->GetCurAnimation()->IsFinish();
			if(finish)
				DeleteObject(this);*/
		}

	}
}