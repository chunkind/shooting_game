#pragma once

#include "CObject.h"

class CTexture;

class CMonster : public CObject
{
private:
	Vec2 m_vCenterPos;
	float m_fSpeed;
	float m_fMaxDistance;
	int m_iDir;
	int m_iHP;

	CTexture* m_pTex;
	CTexture* m_pDeadTex;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _f) { m_fSpeed = _f; }

	void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	virtual void update();
	virtual void render(HDC hdc);

	CLONE(CMonster);

	void CreateMissile();
	void CreateMultiMissile();
	void CreateMultiFullMissile();

public:
	CMonster();
	virtual ~CMonster();
};

