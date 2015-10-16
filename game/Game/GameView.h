// GameView.h : CGameView 클래스의 인터페이스
//


#pragma once
#include "nameadd.h"
#include "ranking.h"


class CGameView : public CView
{
public:
  //현재 마우스가 좌표값으로 그림의 위치를 계산하여 저장하고 있는 인덱스
  UINT  m_nRowTempIndex;
  UINT  m_nColTempIndex;

  int nMatchCount;
  int minus;
protected: // serialization에서만 만들어집니다.
	CGameView();
	DECLARE_DYNCREATE(CGameView)

// 특성입니다.
public:
	CGameDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMatching(void);
	void OnSuccess(void);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int timer;
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void On3x4();
	afx_msg void On4x5();
	afx_msg void On6x6();
	void OnShowDlg(void);
	
	NAMEADD dlgName;
	
	afx_msg void On3x4();
	
	
	RANKING dlgRank;
	
	CString m_str[51];
	
	int m_people;
	int m_score[51];
	
	RANKING dlg;
	afx_msg void OnRestart();
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRankshow();
	afx_msg void OnChance1();
	void Chance(CDC* pDC);
	afx_msg void OnTimeplus();
};

#ifndef _DEBUG  // GameView.cpp의 디버그 버전
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif

