#pragma once
#include "afxwin.h"


// CPropAlarm �Ի���

class CPropAlarm : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropAlarm)

public:
	CPropAlarm();
	virtual ~CPropAlarm();

// �Ի�������
	enum { IDD = IDD_PROPAGE_CTRL_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
