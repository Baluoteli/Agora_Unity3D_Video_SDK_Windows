
// AgoraSdkWrapperDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAgoraSdkWrapperDemoApp: 
// �йش����ʵ�֣������ AgoraSdkWrapperDemo.cpp
//

class CAgoraSdkWrapperDemoApp : public CWinApp
{
public:
	CAgoraSdkWrapperDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAgoraSdkWrapperDemoApp theApp;