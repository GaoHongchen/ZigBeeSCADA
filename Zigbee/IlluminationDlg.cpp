// IlluminationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "IlluminationDlg.h"
#include "afxdialogex.h"


// CIlluminationDlg 对话框

IMPLEMENT_DYNAMIC(CIlluminationDlg, CDialog)

CIlluminationDlg::CIlluminationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIlluminationDlg::IDD, pParent)
{

}

CIlluminationDlg::~CIlluminationDlg()
{
}

void CIlluminationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIlluminationDlg, CDialog)
END_MESSAGE_MAP()


// CIlluminationDlg 消息处理程序
