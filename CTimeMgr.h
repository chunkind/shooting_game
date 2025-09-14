#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount; // 현재 초당 카운트
	LARGE_INTEGER m_llPrevCount; // 이전 초당 카운트
	LARGE_INTEGER m_llFrequency; // 초당 고성능 카운트를 가져온다(주파수 값)

	double m_dDT; // 프레임 간의 시간값
	double m_dAcc; // 1초당 체크를 위한 누적 시간
	UINT m_iCallCount; // 함수 호출 횟수 체크
	UINT m_iFPS; // 초당 호출 횟수

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

