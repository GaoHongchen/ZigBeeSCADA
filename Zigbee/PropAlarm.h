#pragma once
#include "afxwin.h"


// CPropAlarm 对话框

class CPropAlarm : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropAlarm)

public:
	CPropAlarm();
	virtual ~CPropAlarm();

// 对话框数据
	enum { IDD = IDD_PROPAGE_CTRL_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CFont m_FontClassroomCH;
//	CString m_strStaticRealNum;
	CString m_strStaticRealNum;
	CString m_strAttendanceRate;
	CFont m_FontClassroomEN;
	CString m_strName;
	CString m_strID;
	afx_msg void OnPaint();
};
