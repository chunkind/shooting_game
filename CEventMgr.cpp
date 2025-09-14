#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	//====================================================
	// ���� �����ӿ��� ����ص� Dead Object ���� �����Ѵ�.
	//====================================================
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();

	//============
	// Event ó��.
	//============
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// Object�� Dead ���·� ����.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		// ���� ���� Object���� ��Ƶд�.
		m_vecDead.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	}
}