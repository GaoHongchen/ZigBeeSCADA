
// ZigbeeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "cmscomm.h"
#include "afxcmn.h"

#include "PropAircon.h"
#include "PropAlarm.h"
#include "PropCam.h"
#include "PropCurtain.h"
#include "PropLight.h"
#include "atltypes.h"
#include "btnst.h"


// CZigbeeDlg 对话框
class CZigbeeDlg : public CDialogEx
{
// 构造
public:
	CZigbeeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ZIGBEE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
	//////
	DECLARE_EVENTSINK_MAP()
	//////
public:
	TCHAR dirApp[MAX_PATH];

	CMSComm m_ctrlComm;
	//DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	CString m_strDataRX;
	CString m_strDataRXTemp;
	CString m_strDataTX;
	CString strTemperatureHumidityRX;
	CString strTemperatureValue;
	CString strHumidityValue;
	CString strIlluminationRX;
	CString strInfraredRX;
	CString strLightRX;
	CString strClassRX;

	afx_msg void OnBnClickedBtnSend();
	CTabCtrl m_tab;
	CPropAircon m_pageAircon;
	CPropAlarm m_pageAlarm;
	CPropCam m_pageCam;
	CPropCurtain m_pageCurtain;
	CPropLight m_pageLight;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	CStatusBar m_StatusBar;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnDevmgmt();
	afx_msg void OnBnClickedBtnCommPort();
	afx_msg void OnBnClickedBtnTemperature();
	bool m_bAlert;
	bool m_bAlertBeep;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedBtnHumidity();
//	afx_msg void OnBnClickedBtnIllumination();
//	afx_msg void OnBnClickedBtnCarbonDioxide();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnSysSetting();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnClear();	
	void SetCommPort(short port, long baudrate);
//	afx_msg LRESULT OnRecvLightDataMessage(WPARAM wParam, LPARAM lParam); /////

	static CZigbeeDlg *s_pZDlg;
	//friend CPropLight;
	bool isBright;
	CFont m_FontIllumination;
	
	bool flagLightAddr;
	afx_msg void OnBnClickedBtnAbout();
	CString m_strSysTitle;
	CRect m_RectDlgScreen;
	CRect m_RectDlgClient;
	CRect m_RectDlgScreenRealTime;
	COLORREF m_color;
};


#define WM_RECVLIGHTDATA_MSG WM_USER+100