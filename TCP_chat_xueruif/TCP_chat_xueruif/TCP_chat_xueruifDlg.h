
// TCP_chat_xueruifDlg.h : ͷ�ļ�
//

#pragma once
#include "Server.h"
#include "Client.h"
#include <afxtempl.h>

#define SER_MESSAGE WM_USER + 100
#define CLI_MESSAGE WM_USER + 101

typedef CList <SOCKET,SOCKET&> SOCKET_ARRAY;
// CTCP_chat_xueruifDlg �Ի���
class CTCP_chat_xueruifDlg : public CDialogEx
{
// ����
public:
	CTCP_chat_xueruifDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCP_CHAT_XUERUIF_DIALOG };
public:										////////////////
	CServer m_server;
	CClient m_client;
	BOOL m_bInit;
	BOOL m_bClient;
	SOCKET_ARRAY m_connectionList;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnServerMessage(WPARAM wParam, LPARAM lParam);///////////
	afx_msg LRESULT OnClientMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedConnect();
	afx_msg void OnUpdateInputtext();
	afx_msg void OnClickedSetserver();
	CString m_sInputText;
	CIPAddressCtrl m_ServerIp;
	CString m_sShowText;
	UINT m_uPort;
};
