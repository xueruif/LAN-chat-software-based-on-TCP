
// TCP_chat_xueruifDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCP_chat_xueruif.h"
#include "TCP_chat_xueruifDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTCP_chat_xueruifDlg �Ի���




CTCP_chat_xueruifDlg::CTCP_chat_xueruifDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP_chat_xueruifDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sInputText = _T("");
	m_sShowText = _T("");
	m_uPort = 4000;/////��ʼ����Ĭ��Ϊ4000�˿�
}

void CTCP_chat_xueruifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUTTEXT, m_sInputText);
	DDX_Control(pDX, IDC_SERVERIP, m_ServerIp);
	DDX_Text(pDX, IDC_SHOWTEXT, m_sShowText);
	DDX_Text(pDX, IDC_PORT, m_uPort);
	DDV_MinMaxUInt(pDX, m_uPort, 1024, 100000);//////
}

BEGIN_MESSAGE_MAP(CTCP_chat_xueruifDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CTCP_chat_xueruifDlg::OnClickedConnect)
	ON_EN_UPDATE(IDC_INPUTTEXT, &CTCP_chat_xueruifDlg::OnUpdateInputtext)
	ON_BN_CLICKED(IDC_SETSERVER, &CTCP_chat_xueruifDlg::OnClickedSetserver)
	ON_MESSAGE(SER_MESSAGE,OnServerMessage)//////////
	ON_MESSAGE(CLI_MESSAGE,OnClientMessage)
END_MESSAGE_MAP()


// CTCP_chat_xueruifDlg ��Ϣ�������

BOOL CTCP_chat_xueruifDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	WSADATA wsaData;				////////////////
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);
	if(ret != 0)
	{
		TRACE("Initilize Error!\n");  //��ʼ��ʧ��
		AfxMessageBox("Failed in initial socket");
	}
//	m_connectionList.AssertValid();
	m_connectionList.RemoveAll();
	ASSERT(m_connectionList.GetCount()==0);
	m_bInit=FALSE;
	m_bClient=FALSE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTCP_chat_xueruifDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCP_chat_xueruifDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTCP_chat_xueruifDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP_chat_xueruifDlg::OnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BYTE  f0,f1,f2,f3;				////////////////
	m_ServerIp.GetAddress(f0,f1,f2,f3);
	CString add;
	add.Format("%d.%d.%d.%d",f0,f1,f2,f3);
	
	if(m_client.InitAndConnet(m_hWnd,m_uPort,add)==FALSE)
		return;
}


void CTCP_chat_xueruifDlg::OnUpdateInputtext()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if(!m_bInit)
	{
		AfxMessageBox("The session has not been set correctly");
		return;
	}
	CString in;
	GetDlgItem(IDC_INPUTTEXT)->GetWindowText(in);
	//�������ֻ�лس��������£����Բ����ͻس����ַ�
	if(in.GetLength()<1)
	{
		return;
	}

	if(in.GetAt(in.GetLength()-1)=='\n')
	{
		//in.TrimRight(" ")������ȥ���õĿո���ַ�
		in.TrimRight(" ");
		//��������е��ַ����,��ʾ�ַ��Ѿ�������
		GetDlgItem(IDC_INPUTTEXT)->SetWindowText("");
		if(in.GetLength()>2)
		{
			m_sShowText+=in;
			//������Ļ���ʾ����ʾ������
			GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);		
			CEdit * output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			//��ʱ���ٹ�������λ��
			output->LineScroll(output->GetLineCount());

			//��������
			if(!m_bClient)
			{
				int length=m_connectionList.GetCount();
				SOCKET  socket;
				for(int i=0;i<length;i++)
				{
					socket=m_connectionList.GetAt(m_connectionList.FindIndex(i));
					send(socket,in.GetBuffer(0),in.GetLength(),0);
				}
			}
			//�ͻ���
			else
			{
				m_client.SendString(in);
			}
		}
	}
	
}


void CTCP_chat_xueruifDlg::OnClickedSetserver()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_server.InitAndListen(this->m_hWnd,m_uPort)==FALSE)
	{					/////////
		return;
	}
	else
	{
		m_bInit=TRUE;
		m_bClient=FALSE;
		m_sShowText="Server has been set ok!\n";
		GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
	}
}

//Server��Ϣ��Ӧ����
LRESULT CTCP_chat_xueruifDlg::OnServerMessage(WPARAM wParam, LPARAM lParam)
{

	SOCKET socket,ts;
	int length,i;
	int j;
	CString str="";
	CEdit * output=NULL;
	char s[1024];
	int len;
	switch(lParam)
	{
		case FD_ACCEPT:
			socket= accept(m_server.m_hSocket,NULL,NULL);
			length=m_connectionList.GetCount();
			for(i=0;i<length;i++)
			{
				ts=m_connectionList.GetAt(m_connectionList.FindIndex(i));
				s[0]=NULL;
				strcat(s,"һ���οͽ�����������");
				send(ts,s,strlen(s),0);
			}
			m_sShowText+="\n";
			m_sShowText+="һ���οͽ�������������";
			GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
			output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			//��ʱ���ٹ�������λ��
			output->LineScroll(output->GetLineCount());
			m_connectionList.AddHead(socket);
			return 0;

		case FD_READ:
			length=m_connectionList.GetCount();
			for(i=0;i<length;i++)
			{
				socket=m_connectionList.GetAt(m_connectionList.FindIndex(i));
				if(socket==wParam)
				{
					len=recv(socket,s,1024,0);
					s[len]=NULL;
					//��һ���ͻ��˷��͵���Ϣ���ݵ������ͻ���ȥ
					for(j=0;j<length;j++)
					{
						socket=m_connectionList.GetAt(m_connectionList.FindIndex(j));
						if(socket!=wParam)
						{
							send(socket,s,strlen(s),0);
						}
					}
					m_sShowText=m_sShowText+s;
					GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
					CEdit * output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
					//��ʱ���ٹ�������λ��
					output->LineScroll(output->GetLineCount());
					return 0;
				}
			}
			return 0;

		case FD_WRITE:
			return 0;

		case FD_CLOSE:
			return 0;

		default:
			m_sShowText=m_sShowText+"An networking error has occured with a client";
			GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
			CEdit * output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			//��ʱ���ٹ�������λ��
			output->LineScroll(output->GetLineCount());
			return 0;
	}
}

LRESULT CTCP_chat_xueruifDlg::OnClientMessage(WPARAM wParam, LPARAM lParam)
{
	CEdit * output=NULL;
	char s[1024];
	int len;
	switch(lParam)
	{
		case FD_CONNECT:
			len=GetLastError();
			if(len!=0)
			{
				AfxMessageBox("Error in Connecting");
			}
			else
			{
				m_bInit=TRUE;
				m_bClient=TRUE;
				m_sShowText="Having connected to server!\n";
				GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
			}
			return 0;
		case FD_READ:
			len=recv(m_client.m_hSocket,s,1024,0);
			s[len]=NULL;
			m_sShowText+=s;
			//��ʱ���ٹ�������λ�� 
			output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			output->SetWindowText(m_sShowText);
			output->LineScroll(output->GetLineCount());
			return 0;
		case FD_WRITE:
			return 0;
		case FD_CLOSE:
			return 0;
		default:
			output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			output->SetWindowText("An network error has occured,the connection is dropped");
			closesocket(m_client.m_hSocket);
			m_bInit=false;
			return 0;
	}
}
