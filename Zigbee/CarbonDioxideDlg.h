#pragma once


// CCarbonDioxideDlg 对话框

class CCarbonDioxideDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarbonDioxideDlg)

public:
	CCarbonDioxideDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCarbonDioxideDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CARBON_DIOXIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
