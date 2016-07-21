#pragma once
#include "oscilloscopectrl.h"
#include "ZigbeeDlg.h"

// CHumidityDlg 对话框

class CHumidityDlg : public CDialog
{
	DECLARE_DYNAMIC(CHumidityDlg)

public:
	CHumidityDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHumidityDlg();

// 对话框数据
	enum { IDD = IDD_DLG_HUMIDITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
