#pragma once


// CCarbonDioxideDlg �Ի���

class CCarbonDioxideDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCarbonDioxideDlg)

public:
	CCarbonDioxideDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCarbonDioxideDlg();

// �Ի�������
	enum { IDD = IDD_DLG_CARBON_DIOXIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
