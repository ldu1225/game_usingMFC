// GameDoc.cpp : CGameDoc Ŭ������ ����
//

#include "stdafx.h"
#include "Game.h"
#include "GameDoc.h"
#include "GameView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameDoc

IMPLEMENT_DYNCREATE(CGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDoc, CDocument)
END_MESSAGE_MAP()


// CGameDoc ����/�Ҹ�

CGameDoc::CGameDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_bmCell = CSize(79, 81);
	m_nRow = 3;        // ������ �ʱ� �� �� ��
	m_nCol = 4;

	m_bRandom = true;    // �����ϰ� �׸��� ID ���� 
	for(int n = 0; n < m_nRow; n++)
      for(int m = 0; m < m_nCol; m++)
        m_bShow[n][m] = false;

	 //�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�. 
     m_nBmpFirstID = m_nBmpSecondID = 0;
     m_bMouse = false;
}

CGameDoc::~CGameDoc()
{
}

BOOL CGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	CGameView* pView=(CGameView*)m_viewList.GetHead();
	int m_people;
	//mem , str , score
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		m_people = pView->m_people;

		ar << pView->m_people;
		for(int i = 1; i<=pView->m_people; i++)
			ar<<pView->m_str[i]<<pView->m_score[i];
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		OnNewDocument();
			ar >> pView->m_people;
			pView->dlgRank.mem = pView->m_people;
		for(int i = 1; i<=pView->m_people;i++)
			{
				ar>>pView->m_str[i]>>pView->m_score[i];
				pView->dlgRank.m_strList[i]=pView->m_str[i];
				pView->dlgRank.m_strScore[i]=pView->m_score[i];
	}
}
}

// CGameDoc ����

#ifdef _DEBUG
void CGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameDoc ���
#include "GameView.h"
#include "MainFrm.h"

void CGameDoc::ResizeWindow(void)
{
  CMainFrame*    pMain = (CMainFrame*)AfxGetMainWnd();

  CREATESTRUCT  st;
  CREATESTRUCT&  rst = st;

  pMain->PreCreateWindow(rst);

  rst.lpszName = _T("Game");
  rst.cx = (m_nRow + 1) * m_bmCell.cx + 180;
  rst.cy = (m_nCol + 1) * m_bmCell.cy + 180;

  CRect    rect;
  pMain->GetClientRect(rect);
  pMain->MoveWindow(rect.left, rect.top, rst.cx, rst.cy);
}

void CGameDoc::OnRandom(void)
{
  // �ð��� Seed�� ��� �Ȱ��� ���� �߻��� ����
  srand((unsigned)time(NULL));

  // ��Ʈ�� ���� ���� / ������ �� �� / ó�� ���� ��Ʈ���� ���̵�
  // ������ ���̵� �� ���� ��ġ�ǵ��� �ϱ� ���� ������ �����Ѵ�. 
  BOOL  bInsert = TRUE;   
  //������ �Ѽ��� ���Ѵ�. 
  int nGrating = m_nRow * m_nCol;

  // ������ ����ŭ ���鼭 ���� �߻�
  for(int n = 0; n < nGrating; n++)  //���� �� ��ŭ�� ����. 
  {
    // ���� ��Ʈ�� ���̵� ������ ���� ��Ʈ���� ����
    // �ϴ� �߻��� ������ �迭�� �����ϰ� ����. 
    m_nRnd[n] =  (rand() % (nGrating / 2)) + 1;
  
    //���� ������ ���ڼ������� ���Ѵ�. 
    for(int m = 0; m < n; m++){
      if(m_nRnd[n] == m_nRnd[m]){//���� ���������ִٸ� ������ ���ԺҰ��������� �˾ƺ���.
          if(bInsert == FALSE){ //bInsert�� FALSE�̸� �� ��° ������ ���̹Ƿ� 
            n--;  //�迭�� �̹� ����° ����� �������� ����ϱ� ���ؼ� ÷�ڸ� �����Ѵ�. 
            bInsert = TRUE; //�����̻��� ���� ������ ���� ����Ǿ� ���� ���� ���̹Ƿ� 
            break;  //���� �ݺ����� �����. ��������� bInsert���� TRUE�� ����
          }//if
          bInsert = FALSE;//���� ������ �������� �̹� �迭�� �����Ǿ� ������ �ѹ� ���� 
      }//�������̸� bInsert�� TRUE�̹Ƿ� �� ���� ������ ���� �迭�� ����� �Ŀ�
       //�������� ����Ǵ� �迭�� �� ��° ������ ���� ��Ÿ���� 
       //�� �̻� �迭�� ������� �ʵ��� �ϱ� ���ؼ� bInsert�� FALSE���� �����Ѵ�. 
    }//���� for
  }//�ٱ��� for
//36���� �������� ����� ������ �迭 m_nRnd�� ���� �׸��� ��ġ�� ������ ���̸�
//������ �׸��� ���߱� ���� ��Ÿ�� �׸��� ��ġ�� �ش� �׸��� ���̵� ���� 
//  m_nBmpID�迭�� �ϴ��� �������� ��ġ�Ѵ�. 
  int    nCount = 0;

  for(int n = 0; n < m_nRow; n++)  {
    for(int m = 0; m < m_nCol; m++)    {
      m_nBmpID[n][m] = m_nRnd[nCount];
      nCount++;
    }
  }
}
