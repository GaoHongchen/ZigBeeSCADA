#pragma once


// CIlluminationDlg �Ի���

class CIlluminationDlg : public CDialog
{
	DECLARE_DYNAMIC(CIlluminationDlg)

public:
	CIlluminationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIlluminationDlg();

// �Ի�������
	enum { IDD = IDD_DLG_ILLUMINATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
