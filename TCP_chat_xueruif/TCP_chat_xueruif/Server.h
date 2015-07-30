// Server.h: interface for the CServer class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "winsock.h"

class CTCP_chat_xueruifDlg;

class CServer  
{
public:
	CServer();
	virtual ~CServer();
private:
	void ServerInit();
public:
	BOOL InitAndListen(HWND hwnd,UINT port);
public:
	SOCKET m_hSocket;
	sockaddr_in m_addr;
	UINT m_uPort;
    HWND m_hWnd;
};

