#pragma once
#include "afxwin.h"


// RANKING ��ȭ �����Դϴ�.

class RANKING : public CDialogEx
{
	DECLARE_DYNAMIC(RANKING)

public:
	RANKING(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~RANKING();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RANKING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrList;
	
	
	
	
	virtual BOOL OnInitDialog();
	CString m_strList[51];
	CListBox m_ctrScore;
	int m_strScore[51];
	int mem;
};
