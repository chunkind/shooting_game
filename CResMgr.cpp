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

	// 리소스 정보알게 셋팅
	pTex->Load(strFilePath);
	//m_pTex->LoadFromResource(IDB_PLAYER);  // 리소스에서 로딩

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

	// 리소스 정보알게 셋팅
	pTex->LoadFromResource(type);  // 리소스에서 로딩

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