
// TCP_chat_xueruif.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTCP_chat_xueruifApp:
// �йش����ʵ�֣������ TCP_chat_xueruif.cpp
//

class CTCP_chat_xueruifApp : public CWinApp
{
public:
	CTCP_chat_xueruifApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTCP_chat_xueruifApp theApp;