#pragma once
#include "btnst.h"
#include "unibutton.h"


// CPropAircon 对话框

class CPropAircon : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropAircon)

public:
	CPropAircon();
	virtual ~CPropAircon();

// 对话框数据
	enum { IDD = IDD_PROPAGE_CTRL_AIRCON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CButtonST m_btnAircondition1;
	CButtonST m_btnAircondition2;

	CUniButton m_BtnLeft;
	CUniButton m_BtnRight;
	CUniButton m_BtnUp;
	CUniButton m_BtnDown;
	CUniButton m_BtnMid;
	enum {UNI_BTNL = 1001, UNI_BTNR = 1002, UNI_BTNU = 1003, UNI_BTND = 1004, UNI_BTNM = 1005};
	afx_msg void OnPaint();
};
