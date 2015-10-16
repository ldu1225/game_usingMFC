// NAMEADD.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "NAMEADD.h"
#include "afxdialogex.h"


// NAMEADD 대화 상자입니다.

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


// NAMEADD 메시지 처리기입니다.
