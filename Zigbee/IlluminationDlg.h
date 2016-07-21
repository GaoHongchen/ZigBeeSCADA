#pragma once


// CIlluminationDlg 对话框

class CIlluminationDlg : public CDialog
{
	DECLARE_DYNAMIC(CIlluminationDlg)

public:
	CIlluminationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIlluminationDlg();

// 对话框数据
	enum { IDD = IDD_DLG_ILLUMINATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
