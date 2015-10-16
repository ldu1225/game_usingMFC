// GameDoc.h : CGameDoc Ŭ������ �������̽�
//


#pragma once


class CGameDoc : public CDocument
{
public:
  CBitmap m_bmp[6][6];  // ��Ʈ���� �����Ѵ�. 
  CSize  m_bmCell;      // ���� �� �׸� �ϳ��� ũ��
  int      m_nRow;	// ���ڼ��� ������ ���� 
  int      m_nCol;  
  // �ִ� 36���� �׸��� ��ġ�� �����Լ��� �� ���� �����ϱ� ���� ���� 
  int      m_nRnd[36];
  //�׸��� ID���� 6X6�� 2���� �迭�� �����Ѵ�. �ִ� 36������ ����ȴ�. 
  UINT  m_nBmpID[6][6];
  bool    m_bRandom;      // ������ / ������ ���� �ľ�

  bool    m_bShow[6][6];

  int  m_nRowIndex;
  int  m_nColIndex;

  //ù��° ���� �׸��� ���̵� ����
  UINT  m_nBmpFirstID;

  //�ι�° ���� �׸��� ���̵� ���� ��ġ�ϴ��� �˾ƺ��� ���ؼ� 
  UINT  m_nBmpSecondID;

  //true�̸� ù ��° ���콺 ��ư�� ���� ���̰� false�̸� �� ��° ���콺 ��ư�� ���� ����
  bool  m_bMouse;

protected: // serialization������ ��������ϴ�.
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// Ư���Դϴ�.

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void ResizeWindow(void);
	void OnRandom(void);
};


