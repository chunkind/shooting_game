#pragma once

#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
private:
	CTexture* m_pTex;
	CTexture* m_pPilsalAnimTex;

public:
	virtual void update();
	virtual void render(HDC hdc);

private:
	void CreateMissile();
	void CreatePilsal();

	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();
};

