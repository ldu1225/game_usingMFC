#pragma once
#include "afxwin.h"


// RANKING 대화 상자입니다.

class RANKING : public CDialogEx
{
	DECLARE_DYNAMIC(RANKING)

public:
	RANKING(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~RANKING();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RANKING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrList;
	
	
	
	
	virtual BOOL OnInitDialog();
	CString m_strList[51];
	CListBox m_ctrScore;
	int m_strScore[51];
	int mem;
};
