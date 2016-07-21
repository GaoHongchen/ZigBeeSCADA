#pragma once
#include "oscilloscopectrl.h"
#include "ZigbeeDlg.h"

// CHumidityDlg �Ի���

class CHumidityDlg : public CDialog
{
	DECLARE_DYNAMIC(CHumidityDlg)

public:
	CHumidityDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHumidityDlg();

// �Ի�������
	enum { IDD = IDD_DLG_HUMIDITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	COScopeCtrl m_OScopeCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CZigbeeDlg* m_ZigbeeDlg;
	CStatusBar m_StatusBar;
	CString m_strHumidityRX;
	afx_msg void OnBnClickedOk();
};
