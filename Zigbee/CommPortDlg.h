#pragma once


// CCommPortDlg �Ի���

class CCommPortDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommPortDlg)

public:
	CCommPortDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommPortDlg();

// �Ի�������
	enum { IDD = IDD_DLG_COMM_PORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	short m_indexPort;
	short m_indexBaudRate;
	short m_nCommPort;
	long m_nBaudRate;
	afx_msg void OnCbnSelchangeComboComPort();
	afx_msg void OnCbnSelchangeComboBaudrate();
};
