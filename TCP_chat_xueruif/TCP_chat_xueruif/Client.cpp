// Client.cpp: implementation of the CClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCP_chat_xueruif.h"
#include "Client.h"
#include "TCP_chat_xueruifDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClient::CClient()
{
	m_hSocket  =NULL;
}

CClient::~CClient()
{

}
BOOL CClient::InitAndConnet(HWND hwnd,UINT port,CString strserver)
{
	m_hWnd=hwnd;
	m_uPort=port;
	m_strServer=strserver;
	if(m_hSocket != NULL)
	{
		//���ԭ�������׽����ȹر�
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
	if(m_hSocket == NULL)
	{
		//�����µ����׽���
		//m_hSocket = socket(AF_INET, SOCK_STREAM,0);//SOCK_STREAM���������ӵİ�
		//m_hSocket = socket(AF_INET, SOCK_DGRAM,0);//����listen ERROR����binding error
		m_hSocket = socket(AF_INET, SOCK_STREAM,0);
		ASSERT(m_hSocket != NULL);
		ClientInit();
	}

	//׼������������Ϣ��������Ҫָ���������ĵ�ַ
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.S_un.S_addr = inet_addr(m_strServer.GetBuffer(0));
	m_addr.sin_port = htons(m_uPort);   //�ı�˿ںŵ����ݸ�ʽ
	
	//�����������ӷ��������ù��̽��ȴ�һ��ʱ��
	int ret = 0;
	int error = 0;
	ret = connect(m_hSocket, (LPSOCKADDR)&m_addr, sizeof(m_addr));
	if(ret == SOCKET_ERROR)
	{//����ʧ��
		if(GetLastError()!=WSAEWOULDBLOCK)
		{
			AfxMessageBox(_T("��ȷ�Ϸ�����ȷʵ�Ѿ��򿪲�������ͬ���Ķ˿ڣ�"));
			return FALSE;
		}
	}
	return TRUE;
}

void CClient::SendString(CString a)
{
	if(send(m_hSocket,a.GetBuffer(0),a.GetLength(),0)==SOCKET_ERROR)
	{
		AfxMessageBox("Client Send data error");
	}
}

void CClient::GetString(CString &str)
{
	recv(m_hSocket,str.GetBuffer(0),1024,MSG_DONTROUTE);
}

void CClient::ClientInit()
{
	if(WSAAsyncSelect(m_hSocket,m_hWnd,CLI_MESSAGE,FD_READ|FD_WRITE|FD_CLOSE|FD_CONNECT)>0)
	{
		AfxMessageBox("Error in select");
	}
}
