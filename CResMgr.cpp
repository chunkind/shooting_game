#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;

	// ���ҽ� �����˰� ����
	pTex->Load(strFilePath);
	//m_pTex->LoadFromResource(IDB_PLAYER);  // ���ҽ����� �ε�

	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::LoadTexture(UINT type)
{
	CTexture* pTex = FindTexture(std::to_wstring(type));
	if (nullptr != pTex)
	{
		return pTex;
	}

	pTex = new CTexture;

	// ���ҽ� �����˰� ����
	pTex->LoadFromResource(type);  // ���ҽ����� �ε�

	pTex->SetKey(std::to_wstring(type));
	pTex->SetRelativePath(std::to_wstring(type));

	m_mapTex.insert(make_pair(std::to_wstring(type), pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return (CTexture*)iter->second;
}