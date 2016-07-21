#pragma once

#include "oscilloscopectrl.h"
#include "ZigbeeDlg.h"
#include "afxext.h"
// CTemperatureDlg �Ի���

class CTemperatureDlg : public CDialog
{
	DECLARE_DYNAMIC(CTemperatureDlg)

public:
	CTemperatureDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTemperatureDlg();

// �Ի�������
	enum { IDD = IDD_DLG_TEMPERATURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
