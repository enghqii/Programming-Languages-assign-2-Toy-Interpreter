
// PL_assign2_toy.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPL_assign2_toyApp:
// �� Ŭ������ ������ ���ؼ��� PL_assign2_toy.cpp�� �����Ͻʽÿ�.
//

class CPL_assign2_toyApp : public CWinApp
{
public:
	CPL_assign2_toyApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPL_assign2_toyApp theApp;