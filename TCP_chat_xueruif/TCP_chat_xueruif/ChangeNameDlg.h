#pragma once


// CChangeNameDlg �Ի���

class CChangeNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangeNameDlg)

public:
	CChangeNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeNameDlg();

// �Ի�������
	enum { IDD = IDD_SETNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sName;
};
