// GameDoc.cpp : CGameDoc 클래스의 구현
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


// CGameDoc 생성/소멸

CGameDoc::CGameDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_bmCell = CSize(79, 81);
	m_nRow = 3;        // 격자의 초기 행 열 값
	m_nCol = 4;

	m_bRandom = true;    // 랜덤하게 그림의 ID 변경 
	for(int n = 0; n < m_nRow; n++)
      for(int m = 0; m < m_nCol; m++)
        m_bShow[n][m] = false;

	 //아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다. 
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

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

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
		// TODO: 여기에 저장 코드를 추가합니다.
		m_people = pView->m_people;

		ar << pView->m_people;
		for(int i = 1; i<=pView->m_people; i++)
			ar<<pView->m_str[i]<<pView->m_score[i];
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
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

// CGameDoc 진단

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


// CGameDoc 명령
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
  // 시간을 Seed로 잡아 똑같은 난수 발생을 방지
  srand((unsigned)time(NULL));

  // 비트맵 삽입 여부 / 격자의 총 수 / 처음 넣을 비트맵의 아이디
  // 동일한 아이디를 두 번씩 배치되도록 하기 위한 변수를 설정한다. 
  BOOL  bInsert = TRUE;   
  //격자의 총수를 구한다. 
  int nGrating = m_nRow * m_nCol;

  // 격자의 수만큼 돌면서 난수 발생
  for(int n = 0; n < nGrating; n++)  //격자 수 만큼만 돈다. 
  {
    // 시작 비트맵 아이디에 난수를 더해 비트맵을 변경
    // 일단 발생한 난수를 배열에 저장하고 본다. 
    m_nRnd[n] =  (rand() % (nGrating / 2)) + 1;
  
    //현재 진행한 격자수까지만 비교한다. 
    for(int m = 0; m < n; m++){
      if(m_nRnd[n] == m_nRnd[m]){//만일 같은값이있다면 변수에 삽입불가능한지를 알아본다.
          if(bInsert == FALSE){ //bInsert가 FALSE이면 세 번째 동일한 값이므로 
            n--;  //배열에 이미 세번째 저장된 랜덤값을 취소하기 위해서 첨자를 감소한다. 
            bInsert = TRUE; //세번이상은 절대 동일한 값이 저장되어 있지 않을 것이므로 
            break;  //안쪽 반복문을 벗어난다. 벗어나기전에 bInsert값을 TRUE로 설정
          }//if
          bInsert = FALSE;//새로 생성된 랜덤값이 이미 배열에 설정되어 있지만 한번 만난 
      }//랜덤값이면 bInsert가 TRUE이므로 두 번쨰 동일한 값은 배열에 저장된 후에
       //다음부터 진행되는 배열에 세 번째 동일한 값이 나타나면 
       //더 이상 배열에 저장되지 않도록 하기 위해서 bInsert에 FALSE값을 저장한다. 
    }//안쪽 for
  }//바깥쪽 for
//36개의 랜덤값이 저장된 일차원 배열 m_nRnd에 의해 그림의 위치가 결정될 것이면
//동일한 그림을 맞추기 위해 나타날 그림의 위치에 해당 그림의 아이디 값을 
//  m_nBmpID배열에 일대일 대응으로 배치한다. 
  int    nCount = 0;

  for(int n = 0; n < m_nRow; n++)  {
    for(int m = 0; m < m_nCol; m++)    {
      m_nBmpID[n][m] = m_nRnd[nCount];
      nCount++;
    }
  }
}
