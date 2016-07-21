// HumidityDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "HumidityDlg.h"
#include "afxdialogex.h"

#include "DataTypeConverter.h"

// CHumidityDlg 对话框

static UINT BASED_CODE indicators[]={ID_SEPARATOR};

IMPLEMENT_DYNAMIC(CHumidityDlg, CDialog)

CHumidityDlg::CHumidityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHumidityDlg::IDD, pParent)
{

}

CHumidityDlg::~CHumidityDlg()
{
}

void CHumidityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHumidityDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CHumidityDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHumidityDlg 消息处理程序


BOOL CHumidityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//*********************** 示波器设置 **************************//
	//控件的区域
	CRect rect;
	GetDlgItem(IDC_SCOPE_HUMIDITY)->GetWindowRect(rect);
	ScreenToClient(rect);
	//创建控件
	m_OScopeCtrl.Create(WS_VISIBLE | WS_CHILD,rect,this);
	//自定义控件
	m_OScopeCtrl.SetRange(0,40,1);
	m_OScopeCtrl.SetYUnits(_T("Humidity"));
	m_OScopeCtrl.SetXUnits(_T("Time Elapse: 100 msec"));
	m_OScopeCtrl.SetBackgroundColor(RGB(0,0,0));
	m_OScopeCtrl.SetGridColor(RGB(192,192,192));
	m_OScopeCtrl.SetPlotColor(RGB(255,0,0),RGB(0,255,0),RGB(0,0,255));

	/************************ 状态栏 **************************/
	m_ZigbeeDlg=(CZigbeeDlg*)GetParent();
	m_strHumidityRX=m_ZigbeeDlg->strTemperatureHumidityRX;
	//MessageBox(m_strTemperatureRX);
	m_StatusBar.CreateEx(this,SBT_TOOLTIPS,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,AFX_IDW_STATUS_BAR );
	//m_StatusBar.Create(WS_BORDER|WS_VISIBLE|CBRS_BOTTOM,m_Rect,this,3);
	m_StatusBar.SetIndicators(indicators,1);//设置指示器数量
	//CRect rect;
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL ,rect.Width());
	//很重要****
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,ID_SEPARATOR);

	m_StatusBar.SetPaneText(0,_T("设备类型： ")+m_strHumidityRX.Mid(2,3)
							 +_T("      主节点地址： ")+m_strHumidityRX.Mid(5,4)
							 +_T("      副节点地址： ")+m_strHumidityRX.Mid(9,4)
							 +_T("      湿度值： ")+m_strHumidityRX.Mid(14,2),0);


	SetTimer(0,200,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CHumidityDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_strHumidityRX=((CZigbeeDlg*)GetParent())->strTemperatureHumidityRX;
	//状态栏设置
	m_StatusBar.SetPaneText(0,_T("设备类型： ")+m_strHumidityRX.Mid(2,3)
							 +_T("    网络地址： ")+m_strHumidityRX.Mid(5,4)
							 +_T("    节点地址： ")+m_strHumidityRX.Mid(9,4)
							 +_T("    温度值： ")+m_strHumidityRX.Mid(14,2),0);

	CDataTypeConverter DTC;
	int intHumidityValue=DTC.Hex2Dec(m_strHumidityRX.Mid(18,2));

	m_OScopeCtrl.AppendPoint(intHumidityValue,-1,-1);

	CDialog::OnTimer(nIDEvent);
}


void CHumidityDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(0);
	CDialog::OnOK();
}
