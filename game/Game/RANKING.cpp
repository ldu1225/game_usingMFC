// RANKING.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Game.h"
#include "RANKING.h"
#include "afxdialogex.h"


// RANKING 대화 상자입니다.

IMPLEMENT_DYNAMIC(RANKING, CDialogEx)

RANKING::RANKING(CWnd* pParent /*=NULL*/)
	: CDialogEx(RANKING::IDD, pParent)
	
	
	, mem(0)
{
	
}

RANKING::~RANKING()
{
}

void RANKING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RANKING, m_ctrList);

	DDX_Control(pDX, IDC_LIST1, m_ctrScore);
}


BEGIN_MESSAGE_MAP(RANKING, CDialogEx)
	
	
	
END_MESSAGE_MAP()


// RANKING 메시지 처리기입니다.




BOOL RANKING::OnInitDialog() //다이얼로그 생성될때 값을 다 가져옴
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString str;
	for(int i = 1; i<=mem; i++)//다시
	{
		for(int j = i+1; j<=mem; j++)
		{
			if(m_strScore[i] < m_strScore[j])
			{
				int temp=m_strScore[i];
				m_strScore[i]=m_strScore[j];
				m_strScore[j]=temp;
				
				CString temp2=m_strList[i];
				m_strList[i]=m_strList[j];
				m_strList[j]=temp2;

			}
		}
	}
	for(int i=1; i<=mem; i++){
	m_ctrList.AddString(m_strList[i]);
	
	str.Format(_T("%d"),m_strScore[i]);
	m_ctrScore.AddString(str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
