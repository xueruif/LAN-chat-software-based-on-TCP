// Client.h: interface for the CClient class.
//
//////////////////////////////////////////////////////////////////////


#pragma once

#include "winsock.h"

class CTCP_chat_xueruifDlg;

class CClient  
{
public:
	CClient();
	virtual ~CClient();
private:
	void ClientInit();
public:
	BOOL InitAndConnet(HWND hwnd,UINT port,CString m_strServer);
public:
	void GetString(CString & str);
	void SendString(CString a);
	CString m_strServer;
	SOCKET m_hSocket;
	sockaddr_in m_addr;
	UINT m_uPort;
    HWND m_hWnd;
};

