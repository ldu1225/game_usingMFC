// Game.h : Game ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGameApp:
// �� Ŭ������ ������ ���ؼ��� Game.cpp�� �����Ͻʽÿ�.
//

class CGameApp : public CWinApp
{
public:
	CGameApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGameApp theApp;