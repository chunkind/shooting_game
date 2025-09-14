#pragma once

#include "CCamera.h"

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; // Collider를 소유하고 있는 Object

	Vec2 m_vOffsetPos; // 오브잭트로부터 상대적인 위치
	Vec2 m_vFinalPos; // finalupdate 에서 매 프레임마다 계산
	Vec2 m_vScale; // 충돌체의 크기

	UINT m_iID; // 충돌체의 고유한 아이디
	int m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }
	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin); // 복사생성자 구현
	~CCollider();

	friend class CObject;
};
