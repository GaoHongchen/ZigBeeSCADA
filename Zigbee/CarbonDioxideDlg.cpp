// CarbonDioxideDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "CarbonDioxideDlg.h"
#include "afxdialogex.h"


// CCarbonDioxideDlg 对话框

IMPLEMENT_DYNAMIC(CCarbonDioxideDlg, CDialogEx)

CCarbonDioxideDlg::CCarbonDioxideDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarbonDioxideDlg::IDD, pParent)
{

}

CCarbonDioxideDlg::~CCarbonDioxideDlg()
{
}

void CCarbonDioxideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCarbonDioxideDlg, CDialogEx)
END_MESSAGE_MAP()


// CCarbonDioxideDlg 消息处理程序
