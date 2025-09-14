#pragma once

class CCollider;
class CAnimator;

class CObject
{
private:
	wstring m_strName;
	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	// 자기 자신이 활성화상태인지 비활성화상태인지 갖고 있는다.
	bool m_bAlive;

protected:
	int m_Width;
	int m_Height;
	int m_iSpeed;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator()
	{
		return m_pAnimator;
	}

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();

	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void update() = 0;
	virtual void finalupdate();
	virtual void render(HDC _dc);
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	// 이벤트 매니저만 SedDead를 접근한다.
	friend class CEventMgr;
};