#pragma once
#include "btnst.h"
#include "afxwin.h"

// CPropLight 对话框

class CPropLight : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropLight)

public:
	CPropLight();
	virtual ~CPropLight();

// 对话框数据
	enum { IDD = IDD_PROPAGE_CTRL_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButtonST m_btnFL;
	CButtonST m_btnFR;
	CButtonST m_btnBL;
	CButtonST m_btnBR;

	bool isOnFL;
	bool isOnFR;
	bool isOnBL;
	bool isOnBR;

	bool isOnManFL;
	bool isOnManFR;
	bool isOnManBL;
	bool isOnManBR;

	bool isOffManFL;
	bool isOffManFR;
	bool isOffManBL;
	bool isOffManBR;

	CString on;
	CString off;

	afx_msg void OnBnClickedBtnFrontLeft();	
	afx_msg void OnBnClickedBtnFrontRight();
	afx_msg void OnBnClickedBtnBackLeft();
	afx_msg void OnBnClickedBtnBackRight();

	void SetLight(CString strCtrl,CString strAddr);
	
	CString strAddrBL;
	afx_msg void OnPaint();
	CString m_strLightBL;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CFont m_Font;
	CString strAddrBR;
};
