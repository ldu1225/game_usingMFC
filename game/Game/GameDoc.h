// GameDoc.h : CGameDoc 클래스의 인터페이스
//


#pragma once


class CGameDoc : public CDocument
{
public:
  CBitmap m_bmp[6][6];  // 비트맵을 저장한다. 
  CSize  m_bmCell;      // 셀에 들어갈 그림 하나의 크기
  int      m_nRow;	// 격자수를 저장할 변수 
  int      m_nCol;  
  // 최대 36개의 그림의 위치를 랜덤함수로 얻어낸 값을 저장하기 위한 변수 
  int      m_nRnd[36];
  //그림의 ID값을 6X6의 2차원 배열에 저장한다. 최대 36개까지 저장된다. 
  UINT  m_nBmpID[6][6];
  bool    m_bRandom;      // 게임중 / 랜덤의 유무 파악

  bool    m_bShow[6][6];

  int  m_nRowIndex;
  int  m_nColIndex;

  //첫번째 눌린 그림의 아이디 값과
  UINT  m_nBmpFirstID;

  //두번째 눌린 그림의 아이디 값이 매치하는지 알아보기 위해서 
  UINT  m_nBmpSecondID;

  //true이면 첫 번째 마우스 버튼이 눌린 것이고 false이면 두 번째 마우스 버튼이 눌린 것임
  bool  m_bMouse;

protected: // serialization에서만 만들어집니다.
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// 특성입니다.

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현입니다.
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ResizeWindow(void);
	void OnRandom(void);
};


