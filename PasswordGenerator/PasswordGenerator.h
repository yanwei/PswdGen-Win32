// PasswordGenerator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPasswordGeneratorApp:
// �йش����ʵ�֣������ PasswordGenerator.cpp
//

class CPasswordGeneratorApp : public CWinApp
{
public:
	CPasswordGeneratorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPasswordGeneratorApp theApp;