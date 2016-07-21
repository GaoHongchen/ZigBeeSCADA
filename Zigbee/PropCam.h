#pragma once

#include <vfw.h>
#include "atltypes.h"

// CPropCam 对话框

class CPropCam : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropCam)

public:
	CPropCam();
	virtual ~CPropCam();

// 对话框数据
	enum { IDD = IDD_PROPAGE_CTRL_CAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HWND m_hCapWnd;
	CAPDRIVERCAPS m_CapDrvCap;
	CAPSTATUS m_CapStatus;
	afx_msg void OnBnClickedBtnCamOpen();
//	afx_msg void OnBnClickedBtnCamCapture();
//	afx_msg void OnBnClickedBtnCamRecord();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnCamClose();
};
