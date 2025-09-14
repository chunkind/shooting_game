#include "pch.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CTexture.h"

#include "CCollider.h"

CMissile::CMissile()
	: m_fTheta(PI / 2.f)
	, m_vDir(1.f, -1.f)
{
	m_vDir.Normalize();

	m_pTex = CResMgr::GetInst()->LoadTexture(IDB_SHOT);

	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));
}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	Vec2 vPos = GetPos();
	// ½ºÄ®¶ó
	//vPos.x += 600.f * fDT * cosf(m_fTheta);
	//vPos.y -= 600.f * fDT * sinf(m_fTheta);
	// ¹éÅÍ
	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	int missileScale = 2;

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, int(vRenderPos.x - (float)(iWidth * missileScale / 2))
		, int(vRenderPos.y - (float)(iHeight * missileScale / 2))
		, iWidth * missileScale, iHeight * missileScale
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName().find(L"Monster") != std::wstring::npos)
	{
		DeleteObject(this);
	}
}