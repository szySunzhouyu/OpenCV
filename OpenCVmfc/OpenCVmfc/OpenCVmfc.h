
// OpenCVmfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COpenCVmfcApp:
// �йش����ʵ�֣������ OpenCVmfc.cpp
//

class COpenCVmfcApp : public CWinApp
{
public:
	COpenCVmfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COpenCVmfcApp theApp;