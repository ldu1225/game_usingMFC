// RANKING.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "RANKING.h"
#include "afxdialogex.h"


// RANKING ��ȭ �����Դϴ�.

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


// RANKING �޽��� ó�����Դϴ�.




BOOL RANKING::OnInitDialog() //���̾�α� �����ɶ� ���� �� ������
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString str;
	for(int i = 1; i<=mem; i++)//�ٽ�
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
