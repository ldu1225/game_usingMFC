#pragma once
#include "afxwin.h"


// NAMEADD ��ȭ �����Դϴ�.

class NAMEADD : public CDialogEx
{
	DECLARE_DYNAMIC(NAMEADD)

public:
	NAMEADD(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~NAMEADD();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_nName;
	
};
