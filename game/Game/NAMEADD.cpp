// NAMEADD.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "NAMEADD.h"
#include "afxdialogex.h"


// NAMEADD ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(NAMEADD, CDialogEx)

NAMEADD::NAMEADD(CWnd* pParent /*=NULL*/)
	: CDialogEx(NAMEADD::IDD, pParent)
	, m_nName(_T(""))
{

}

NAMEADD::~NAMEADD()
{
}

void NAMEADD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_nName);
	
}


BEGIN_MESSAGE_MAP(NAMEADD, CDialogEx)
END_MESSAGE_MAP()


// NAMEADD �޽��� ó�����Դϴ�.
