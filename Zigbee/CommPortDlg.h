#pragma once


// CCommPortDlg 对话框

class CCommPortDlg : public CDialog
{
	DECLARE_DYNAMIC(CCommPortDlg)

public:
	CCommPortDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommPortDlg();

// 对话框数据
	enum { IDD = IDD_DLG_COMM_PORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
