// GameView.cpp : CGameView 클래스의 구현
//

#include "stdafx.h"
#include "Game.h"
#include "NAMEADD.h"
#include "GameDoc.h"
#include "GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)

BEGIN_MESSAGE_MAP(CGameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
//	ON_WM_SIZE()
ON_WM_TIMER()
ON_WM_DESTROY()
ON_WM_CREATE()

ON_COMMAND(ID_4x5, &CGameView::On4x5)
ON_COMMAND(ID_6x6, &CGameView::On6x6)
ON_COMMAND(ID_3x4, &CGameView::On3x4)




ON_COMMAND(ID_32782, &CGameView::OnRestart)
ON_COMMAND(ID_32783, &CGameView::OnPause)
ON_COMMAND(ID_32784, &CGameView::OnContinue)
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_RankShow, &CGameView::OnRankshow)
ON_COMMAND(ID_CHANCE1, &CGameView::OnChance1)
ON_COMMAND(ID_TIMEPLUS, &CGameView::OnTimeplus)
END_MESSAGE_MAP()

// CGameView 생성/소멸

CGameView::CGameView()
	: timer(30)
	
{
	// TODO: 여기에 생성 코드를 추가합니다.
	nMatchCount=0;
	m_people=0;
}

CGameView::~CGameView()
{
}

BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGameView 그리기

void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CString str;
	str.Format(_T("현재점수:%d/%d"),nMatchCount*10+minus,pDoc->m_nRow*pDoc->m_nCol/2*10);
	pDC->TextOutW(20,0,str);
	
	CString str1;
	str1.Format(_T("남은시간 : %d"), timer);
	pDC->TextOutW(180,0,str1);

	CString str2,str3;
	str2.Format(_T("* 전체사진 보여주기  :  -3점"));
	str3.Format(_T("* 시간 추가  : -5점  ( 단 20초 미만에서만 사용가능 )"));
	pDC->TextOutW(10,30,str2);
	pDC->TextOutW(10,50,str3);

	CBrush redB,brush,*pOldB;

	brush.CreateSolidBrush(RGB(255,255,255));//완전불투명brush
	pOldB=pDC->SelectObject(&brush);
	pDC->SelectStockObject(BLACK_PEN);
	pDC->Rectangle(280,0,280+35*5,20);
	
	redB.CreateSolidBrush(RGB(255,0,0));
	pOldB=pDC->SelectObject(&redB);
	pDC->Rectangle(280,0,280+timer*5,20);

	Chance(pDC);
}


// CGameView 인쇄

BOOL CGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGameView 진단

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDoc* CGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameView 메시지 처리기

void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
  CGameDoc* pDoc = GetDocument();
  
  // 현재 마우스가 가지고 있는 인덱스
  pDoc->m_nRowIndex = point.y / pDoc->m_bmCell.cy - 1;
  pDoc->m_nColIndex = point.x / pDoc->m_bmCell.cx - 1;

 // 이전 클릭한 곳에 다시 클릭, 두번 이상 클릭, 격자 밖에 클릭했다면 리턴
 if( pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] == true
          || pDoc->m_nBmpSecondID != 0
          || pDoc->m_nRowIndex > pDoc->m_nRow -1
          || pDoc->m_nColIndex > pDoc->m_nCol -1
          || pDoc->m_nRowIndex < 0
          || pDoc->m_nColIndex < 0)

    return;

  // 마우스가 가지고 있는 인덱스 값에 그림을 보여줌
  pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;

  CRect    rect;
  SetRect(&rect, pDoc->m_nRowIndex * (pDoc->m_bmCell.cx + 1),
                 pDoc->m_nColIndex * (pDoc->m_bmCell.cy + 1),
                 pDoc->m_nRowIndex * (pDoc->m_bmCell.cx + 2),
                 pDoc->m_nColIndex * (pDoc->m_bmCell.cy + 2));

  InvalidateRect(rect);

  // 마우스가 클릭한 곳의 인덱스 및 그림 아이디 저장
  if(pDoc->m_nBmpFirstID == 0)
  {
    // 첫번째 마우스 클릭
    pDoc->m_bMouse = true;

    pDoc->m_nBmpFirstID =
           pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];

    m_nRowTempIndex = pDoc->m_nRowIndex;
    m_nColTempIndex = pDoc->m_nColIndex;    
  }
  else
  {
    // 두번째 마우스 클릭
	pDoc->m_bMouse = false;
    
	pDoc->m_nBmpSecondID =
           pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];
  }

  // 같은 그림인지 판단한다
  OnMatching();

  CView::OnLButtonDown(nFlags, point);
}

void CGameView::OnMatching(void)
{

 CGameDoc* pDoc = GetDocument();

  // 그림이 같다면
  if(pDoc->m_nBmpFirstID == pDoc->m_nBmpSecondID 
	  && pDoc->m_bMouse == false)
  {
    // 클릭 이벤트 초기화
    pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = true;
    pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;
    pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
    m_nRowTempIndex = m_nColTempIndex = 0;

   //**********************************************************
	nMatchCount++;   
   //**********************************************************
  }
  else if(pDoc->m_nBmpFirstID != pDoc->m_nBmpSecondID 
	  && pDoc->m_bMouse==false)
  {
    // 다른 그림이라면 잠시 보여줌
    CDC*    pDC=GetDC();
    CDC      memDC;
    CBitmap    bmp;

    memDC.CreateCompatibleDC(pDC);
    bmp.LoadBitmap(IDB_BITMAP1 + pDoc->m_nBmpSecondID);

    CBitmap*  pOldBmp = memDC.SelectObject (&bmp);
    pDC->BitBlt(pDoc->m_bmCell.cx*(pDoc->m_nColIndex+1),
           pDoc->m_bmCell.cy * (pDoc->m_nRowIndex + 1),
           pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,
           &memDC, 0, 0, SRCCOPY);

    bmp.DeleteObject();
    memDC.SelectObject(pOldBmp);
    Sleep(400);

    // 클릭 이벤트 초기화
    pDoc->m_bShow[m_nRowTempIndex][m_nColTempIndex] = false;
    pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = false;
    pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
    m_nRowTempIndex = m_nColTempIndex = 0;
  }

  Invalidate();
  if(nMatchCount == (pDoc->m_nRow * pDoc->m_nCol)/2){
	    OnSuccess();
  }
}

void CGameView::OnSuccess(void)
{
	KillTimer(1);
	int res2 = AfxMessageBox(_T("GAME OVER! 점수를 등록하시겠습니까?"),MB_YESNO);
	
	if(res2 == IDYES)
	{	
		m_people++;
		m_score[m_people] = timer * nMatchCount * 10+minus;
		if(timer==0)
		m_score[m_people] = nMatchCount * 10+minus;
		OnShowDlg();
	}

  int res=AfxMessageBox(_T("다시 시작하시겠습니까?"), MB_YESNO);
	
  if(res==IDYES){
	CGameDoc* pDoc = GetDocument();
	if(pDoc->m_nCol==4)
		timer= 30;
	else if(pDoc->m_nCol==5)
		timer=32;
	else if(pDoc->m_nCol==6)
		timer=35;
	else
		timer=30;
	pDoc->m_bRandom=true;// 랜덤하게 그림의 ID 변경 
	
	SetTimer(1,1000,NULL);
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	Invalidate();
  }
  else if(res==IDNO){
	  KillTimer(1);
  }
	
}





void CGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	Invalidate();
	
	if(timer>0)	
	{
			timer--;		
	}

   else if(timer<=0)
   {
	   OnDestroy();
	   OnSuccess();

   }

	CView::OnTimer(nIDEvent);
}


void CGameView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int CGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(1,1000,NULL);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}





void CGameView::On4x5()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_nRow = 4;
	pDoc->m_nCol = 5;

	pDoc->m_bRandom=true;// 랜덤하게 그림의 ID 변경 
	
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	timer = 32;
	Invalidate();
}


void CGameView::On6x6()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	

	pDoc->m_nRow = 6;
	pDoc->m_nCol = 6;

	
	pDoc->m_bRandom=true;// 랜덤하게 그림의 ID 변경 
	
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	timer = 35;
	
	Invalidate();
}


void CGameView::On3x4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_nRow = 3;
	pDoc->m_nCol = 4;

	pDoc->m_bRandom=true;// 랜덤하게 그림의 ID 변경 
	
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	timer = 30;

	Invalidate();
}

void CGameView::OnShowDlg()
{
	
	dlgName.DoModal();
	
	m_str[m_people] = dlgName.m_nName;
	
	for(int i =1; i<=m_people; i++) 
	{
		dlgRank.m_strList[m_people] = m_str[m_people];
		dlgRank.m_strScore[m_people] = m_score[m_people];
	}
	dlgRank.mem=m_people;
	dlgName.m_nName = "";
	
	dlgRank.DoModal();
	
}

void CGameView::OnChance1() //돋보기 찬스
{
	CDC *pDC = GetDC();
	//CClientDC pDC(this);
	int a=timer;
	timer=30;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Chance(pDC);
	timer=a;
	minus-=3;
	ReleaseDC(pDC);
	
}

void CGameView::OnRestart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGameDoc* pDoc = GetDocument();
	if(pDoc->m_nCol==4)
		timer= 30;
	else if(pDoc->m_nCol==5)
		timer=32;
	else if(pDoc->m_nCol==6)
		timer=35;
	else
		timer=30;
	
	
	pDoc->m_bRandom=true;// 랜덤하게 그림의 ID 변경 
	
	SetTimer(1,1000,NULL);
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//아무 그림도 선택되지 않은 것으로 인식하기 위해서 초기값을 0으로 설정한다. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	Invalidate();
}


void CGameView::OnPause()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(1);	
}


void CGameView::OnContinue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetTimer(1,1000,NULL);					//OnTimer함수호출
}


void CGameView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu *subMenu = menu.GetSubMenu(5);
	CMenu *pContextMenu=subMenu->GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

}


void CGameView::OnRankshow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	 dlgRank.DoModal();
	
}




void CGameView::Chance(CDC* pDC)  
{
	CGameDoc* pDoc = GetDocument();
			
	
	int nCount = 0;
	
    CDC memDC;
    CBitmap*  pOldBmp;	
	 // 랜덤하게 되어있지 않다면 랜덤함수 호출
  if(pDoc->m_bRandom)
  {
	nMatchCount=0;
	minus=0;					//찬스 사용시 차감될 점수 변수 초기화	
    pDoc->OnRandom();
    pDoc->m_bRandom = false; 	
  }

  memDC.CreateCompatibleDC (pDC);        


  for(int n = 0; n < pDoc->m_nRow; n++)
  {
    for(int m = 0; m < pDoc->m_nCol; m++)
    {

	  if(pDoc->m_bShow[n][m] == true)
	  {
	     pDoc->m_bmp[n][m].LoadBitmap(IDB_BITMAP1+pDoc->m_nRnd[nCount]);
         pOldBmp = memDC.SelectObject(&pDoc->m_bmp[n][m]);

	     //왼쪽과 위쪽에 여백을 주기 위해서 1을 더 했다. 
         pDC->BitBlt(pDoc->m_bmCell.cx*(m+1),pDoc->m_bmCell.cy*(n+1), //출력될 위치
                pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,           //그림하나의 크기
                 &memDC, 0, 0, SRCCOPY);
	   
         pDoc->m_bmp[n][m].DeleteObject();		

	    }
	  //서로 다른 그림이 나타나도록 그림의 아이디 값을 1씩 증가시킴
	  nCount++; 

	  if(pDoc->m_bShow[n][m] == false) 
	  {
        CBitmap    bmp;
		if(timer>28){											//잠깐 카드보여주기
			
			 pDoc->m_bmp[n][m].LoadBitmap(IDB_BITMAP1+pDoc->m_nRnd[nCount-1]);
			 pOldBmp = memDC.SelectObject(&pDoc->m_bmp[n][m]);

			 pDC->BitBlt(pDoc->m_bmCell.cx*(m+1),pDoc->m_bmCell.cy*(n+1), //출력될 위치
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,           //그림하나의 크기
					 &memDC, 0, 0, SRCCOPY);
	   
			 pDoc->m_bmp[n][m].DeleteObject();	
		}
		
			else
			{
			bmp.LoadBitmap(IDB_BITMAP1);
			pOldBmp = memDC.SelectObject(&bmp);
	  
			pDC->BitBlt(pDoc->m_bmCell.cx*(m+1),pDoc->m_bmCell.cy*(n+1), //출력될 위치
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,           //그림하나의 크기
					&memDC, 0, 0, SRCCOPY);
			bmp.DeleteObject();}
	  }      
    }//for
  }//for
  memDC.SelectObject(pOldBmp);
  pDoc->ResizeWindow(); 
}


void CGameView::OnTimeplus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(timer>20)
		int res=AfxMessageBox(_T("시간 찬스를 사용할 수 없습니다."), MB_OK);
	else
	{
		timer+=5;
		minus -= 5;	
	}
}
