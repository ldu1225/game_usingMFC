// GameView.h : CGameView Ŭ������ �������̽�
//


#pragma once
#include "nameadd.h"
#include "ranking.h"


class CGameView : public CView
{
public:
  //���� ���콺�� ��ǥ������ �׸��� ��ġ�� ����Ͽ� �����ϰ� �ִ� �ε���
  UINT  m_nRowTempIndex;
  UINT  m_nColTempIndex;

  int nMatchCount;
  int minus;
protected: // serialization������ ��������ϴ�.
	CGameView();
	DECLARE_DYNCREATE(CGameView)

// Ư���Դϴ�.
public:
	CGameDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // GameView.cpp�� ����� ����
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif

