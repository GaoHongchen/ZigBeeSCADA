#pragma once

#include "oscilloscopectrl.h"
#include "ZigbeeDlg.h"
#include "afxext.h"
// CTemperatureDlg 对话框

class CTemperatureDlg : public CDialog
{
	DECLARE_DYNAMIC(CTemperatureDlg)

public:
	CTemperatureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTemperatureDlg();

// 对话框数据
	enum { IDD = IDD_DLG_TEMPERATURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	COScopeCtrl m_OScopeCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CZigbeeDlg* m_ZigbeeDlg;
	CStatusBar m_StatusBar;
	CString m_strTemperatureRX;
	afx_msg void OnBnClickedOk();
};
