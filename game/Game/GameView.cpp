// GameView.cpp : CGameView Ŭ������ ����
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
	// ǥ�� �μ� ����Դϴ�.
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

// CGameView ����/�Ҹ�

CGameView::CGameView()
	: timer(30)
	
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	nMatchCount=0;
	m_people=0;
}

CGameView::~CGameView()
{
}

BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGameView �׸���

void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CString str;
	str.Format(_T("��������:%d/%d"),nMatchCount*10+minus,pDoc->m_nRow*pDoc->m_nCol/2*10);
	pDC->TextOutW(20,0,str);
	
	CString str1;
	str1.Format(_T("�����ð� : %d"), timer);
	pDC->TextOutW(180,0,str1);

	CString str2,str3;
	str2.Format(_T("* ��ü���� �����ֱ�  :  -3��"));
	str3.Format(_T("* �ð� �߰�  : -5��  ( �� 20�� �̸������� ��밡�� )"));
	pDC->TextOutW(10,30,str2);
	pDC->TextOutW(10,50,str3);

	CBrush redB,brush,*pOldB;

	brush.CreateSolidBrush(RGB(255,255,255));//����������brush
	pOldB=pDC->SelectObject(&brush);
	pDC->SelectStockObject(BLACK_PEN);
	pDC->Rectangle(280,0,280+35*5,20);
	
	redB.CreateSolidBrush(RGB(255,0,0));
	pOldB=pDC->SelectObject(&redB);
	pDC->Rectangle(280,0,280+timer*5,20);

	Chance(pDC);
}


// CGameView �μ�

BOOL CGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGameView ����

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}

void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameDoc* CGameView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameView �޽��� ó����

void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
  CGameDoc* pDoc = GetDocument();
  
  // ���� ���콺�� ������ �ִ� �ε���
  pDoc->m_nRowIndex = point.y / pDoc->m_bmCell.cy - 1;
  pDoc->m_nColIndex = point.x / pDoc->m_bmCell.cx - 1;

 // ���� Ŭ���� ���� �ٽ� Ŭ��, �ι� �̻� Ŭ��, ���� �ۿ� Ŭ���ߴٸ� ����
 if( pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] == true
          || pDoc->m_nBmpSecondID != 0
          || pDoc->m_nRowIndex > pDoc->m_nRow -1
          || pDoc->m_nColIndex > pDoc->m_nCol -1
          || pDoc->m_nRowIndex < 0
          || pDoc->m_nColIndex < 0)

    return;

  // ���콺�� ������ �ִ� �ε��� ���� �׸��� ������
  pDoc->m_bShow[pDoc->m_nRowIndex][pDoc->m_nColIndex] = true;

  CRect    rect;
  SetRect(&rect, pDoc->m_nRowIndex * (pDoc->m_bmCell.cx + 1),
                 pDoc->m_nColIndex * (pDoc->m_bmCell.cy + 1),
                 pDoc->m_nRowIndex * (pDoc->m_bmCell.cx + 2),
                 pDoc->m_nColIndex * (pDoc->m_bmCell.cy + 2));

  InvalidateRect(rect);

  // ���콺�� Ŭ���� ���� �ε��� �� �׸� ���̵� ����
  if(pDoc->m_nBmpFirstID == 0)
  {
    // ù��° ���콺 Ŭ��
    pDoc->m_bMouse = true;

    pDoc->m_nBmpFirstID =
           pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];

    m_nRowTempIndex = pDoc->m_nRowIndex;
    m_nColTempIndex = pDoc->m_nColIndex;    
  }
  else
  {
    // �ι�° ���콺 Ŭ��
	pDoc->m_bMouse = false;
    
	pDoc->m_nBmpSecondID =
           pDoc->m_nBmpID[pDoc->m_nRowIndex][pDoc->m_nColIndex];
  }

  // ���� �׸����� �Ǵ��Ѵ�
  OnMatching();

  CView::OnLButtonDown(nFlags, point);
}

void CGameView::OnMatching(void)
{

 CGameDoc* pDoc = GetDocument();

  // �׸��� ���ٸ�
  if(pDoc->m_nBmpFirstID == pDoc->m_nBmpSecondID 
	  && pDoc->m_bMouse == false)
  {
    // Ŭ�� �̺�Ʈ �ʱ�ȭ
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
    // �ٸ� �׸��̶�� ��� ������
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

    // Ŭ�� �̺�Ʈ �ʱ�ȭ
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
	int res2 = AfxMessageBox(_T("GAME OVER! ������ ����Ͻðڽ��ϱ�?"),MB_YESNO);
	
	if(res2 == IDYES)
	{	
		m_people++;
		m_score[m_people] = timer * nMatchCount * 10+minus;
		if(timer==0)
		m_score[m_people] = nMatchCount * 10+minus;
		OnShowDlg();
	}

  int res=AfxMessageBox(_T("�ٽ� �����Ͻðڽ��ϱ�?"), MB_YESNO);
	
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
	pDoc->m_bRandom=true;// �����ϰ� �׸��� ID ���� 
	
	SetTimer(1,1000,NULL);
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�. 
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


int CGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(1,1000,NULL);
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}





void CGameView::On4x5()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_nRow = 4;
	pDoc->m_nCol = 5;

	pDoc->m_bRandom=true;// �����ϰ� �׸��� ID ���� 
	
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	timer = 32;
	Invalidate();
}


void CGameView::On6x6()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGameDoc* pDoc = GetDocument();
	

	pDoc->m_nRow = 6;
	pDoc->m_nCol = 6;

	
	pDoc->m_bRandom=true;// �����ϰ� �׸��� ID ���� 
	
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	timer = 35;
	
	Invalidate();
}


void CGameView::On3x4()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGameDoc* pDoc = GetDocument();
	pDoc->m_nRow = 3;
	pDoc->m_nCol = 4;

	pDoc->m_bRandom=true;// �����ϰ� �׸��� ID ���� 
	
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�. 
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

void CGameView::OnChance1() //������ ����
{
	CDC *pDC = GetDC();
	//CClientDC pDC(this);
	int a=timer;
	timer=30;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Chance(pDC);
	timer=a;
	minus-=3;
	ReleaseDC(pDC);
	
}

void CGameView::OnRestart()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGameDoc* pDoc = GetDocument();
	if(pDoc->m_nCol==4)
		timer= 30;
	else if(pDoc->m_nCol==5)
		timer=32;
	else if(pDoc->m_nCol==6)
		timer=35;
	else
		timer=30;
	
	
	pDoc->m_bRandom=true;// �����ϰ� �׸��� ID ���� 
	
	SetTimer(1,1000,NULL);
	for(int n = 0; n < pDoc->m_nRow; n++)
     for(int m = 0; m < pDoc->m_nCol; m++)
        pDoc->m_bShow[n][m] = false;

	//�ƹ� �׸��� ���õ��� ���� ������ �ν��ϱ� ���ؼ� �ʱⰪ�� 0���� �����Ѵ�. 
	pDoc->m_nBmpFirstID = pDoc->m_nBmpSecondID = 0;
	pDoc->m_bMouse = false;
	Invalidate();
}


void CGameView::OnPause()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	KillTimer(1);	
}


void CGameView::OnContinue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	SetTimer(1,1000,NULL);					//OnTimer�Լ�ȣ��
}


void CGameView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu *subMenu = menu.GetSubMenu(5);
	CMenu *pContextMenu=subMenu->GetSubMenu(0);
	pContextMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

}


void CGameView::OnRankshow()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	 dlgRank.DoModal();
	
}




void CGameView::Chance(CDC* pDC)  
{
	CGameDoc* pDoc = GetDocument();
			
	
	int nCount = 0;
	
    CDC memDC;
    CBitmap*  pOldBmp;	
	 // �����ϰ� �Ǿ����� �ʴٸ� �����Լ� ȣ��
  if(pDoc->m_bRandom)
  {
	nMatchCount=0;
	minus=0;					//���� ���� ������ ���� ���� �ʱ�ȭ	
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

	     //���ʰ� ���ʿ� ������ �ֱ� ���ؼ� 1�� �� �ߴ�. 
         pDC->BitBlt(pDoc->m_bmCell.cx*(m+1),pDoc->m_bmCell.cy*(n+1), //��µ� ��ġ
                pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,           //�׸��ϳ��� ũ��
                 &memDC, 0, 0, SRCCOPY);
	   
         pDoc->m_bmp[n][m].DeleteObject();		

	    }
	  //���� �ٸ� �׸��� ��Ÿ������ �׸��� ���̵� ���� 1�� ������Ŵ
	  nCount++; 

	  if(pDoc->m_bShow[n][m] == false) 
	  {
        CBitmap    bmp;
		if(timer>28){											//��� ī�庸���ֱ�
			
			 pDoc->m_bmp[n][m].LoadBitmap(IDB_BITMAP1+pDoc->m_nRnd[nCount-1]);
			 pOldBmp = memDC.SelectObject(&pDoc->m_bmp[n][m]);

			 pDC->BitBlt(pDoc->m_bmCell.cx*(m+1),pDoc->m_bmCell.cy*(n+1), //��µ� ��ġ
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,           //�׸��ϳ��� ũ��
					 &memDC, 0, 0, SRCCOPY);
	   
			 pDoc->m_bmp[n][m].DeleteObject();	
		}
		
			else
			{
			bmp.LoadBitmap(IDB_BITMAP1);
			pOldBmp = memDC.SelectObject(&bmp);
	  
			pDC->BitBlt(pDoc->m_bmCell.cx*(m+1),pDoc->m_bmCell.cy*(n+1), //��µ� ��ġ
					pDoc->m_bmCell.cx, pDoc->m_bmCell.cy,           //�׸��ϳ��� ũ��
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if(timer>20)
		int res=AfxMessageBox(_T("�ð� ������ ����� �� �����ϴ�."), MB_OK);
	else
	{
		timer+=5;
		minus -= 5;	
	}
}
