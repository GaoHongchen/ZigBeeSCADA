#pragma once


// CPropCurtain 对话框

class CPropCurtain : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropCurtain)

public:
	CPropCurtain();
	virtual ~CPropCurtain();

// 对话框数据
	enum { IDD = IDD_PROPAGE_CTRL_CURTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnCurOn();
	afx_msg void OnBnClickedBtnCurOff();
};
