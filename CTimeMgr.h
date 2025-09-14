#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount; // ���� �ʴ� ī��Ʈ
	LARGE_INTEGER m_llPrevCount; // ���� �ʴ� ī��Ʈ
	LARGE_INTEGER m_llFrequency; // �ʴ� ���� ī��Ʈ�� �����´�(���ļ� ��)

	double m_dDT; // ������ ���� �ð���
	double m_dAcc; // 1�ʴ� üũ�� ���� ���� �ð�
	UINT m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT m_iFPS; // �ʴ� ȣ�� Ƚ��

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

