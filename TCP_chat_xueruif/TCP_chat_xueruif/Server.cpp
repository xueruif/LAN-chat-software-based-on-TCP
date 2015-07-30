// Server.cpp: implementation of the CServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "TCP_chat_xueruif.h"
#include "TCP_chat_xueruifDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServer::CServer()
{
	m_hSocket=NULL;
}

CServer::~CServer()
{
	WSAAsyncSelect(m_hSocket, m_hWnd, 0, 0);
}

BOOL CServer::InitAndListen(HWND hwnd,UINT port)
{
	m_uPort=port;
	m_hWnd=hwnd;

	if(m_hSocket != NULL)
    {
        //����Ѿ��������׽����ȹر�ԭ����
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
	if(m_hSocket == NULL)
	{
		//�����µ��׽��֣������Ǵ����������͵��׽���
	//	m_hSocket = socket(AF_INET, SOCK_STREAM,0);//SOCK_STREAM���������ӵİ�
	//	m_hSocket = socket(AF_INET, SOCK_DGRAM,0);//����listen ERROR����binding error
		m_hSocket = socket(AF_INET, SOCK_STREAM,0);
		ASSERT(m_hSocket != NULL);
		ServerInit();
	}
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_addr.sin_port = htons(m_uPort);

	int ret = 0;
	int error = 0;
	//��һ���׽��ֵ������ĵ�ַ
	ret = bind(m_hSocket, (LPSOCKADDR)&m_addr, sizeof(m_addr));

	if(ret == SOCKET_ERROR)
	{	//�󶨴���
		AfxMessageBox("Binding Error");
		return FALSE;
	}
	
	//��ʼһ���������̣��ȴ��ͻ�������
	ret = listen(m_hSocket, 5);    //����ĵڶ���������ʾ���֧�ֵĿͻ�ͬʱ����������
	if(ret == SOCKET_ERROR)
	{	//listenʧ��
		AfxMessageBox("Listen Error");
		return FALSE;
	}

	return TRUE;
}
void CServer::ServerInit()
{
	if(WSAAsyncSelect(m_hSocket, m_hWnd, SER_MESSAGE, FD_ACCEPT|FD_READ|FD_WRITE|FD_CLOSE)>0)
		AfxMessageBox("error select");
}
