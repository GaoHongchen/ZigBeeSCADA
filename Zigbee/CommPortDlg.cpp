// CommPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "CommPortDlg.h"
#include "afxdialogex.h"


// CCommPortDlg 对话框

IMPLEMENT_DYNAMIC(CCommPortDlg, CDialog)

CCommPortDlg::CCommPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommPortDlg::IDD, pParent)
{

}

CCommPortDlg::~CCommPortDlg()
{
}

void CCommPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCommPortDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_COM_PORT, &CCommPortDlg::OnCbnSelchangeComboComPort)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUDRATE, &CCommPortDlg::OnCbnSelchangeComboBaudrate)
END_MESSAGE_MAP()


// CCommPortDlg 消息处理程序


BOOL CCommPortDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	/*********************** 串口设置 **************************/
	//串口号
	((CComboBox*)GetDlgItem(IDC_COMBO_COM_PORT))->SetCurSel(0);
	m_indexPort=((CComboBox*)GetDlgItem(IDC_COMBO_COM_PORT))->GetCurSel();
	m_nCommPort=m_indexPort+1;	
	//波特率
	((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->SetCurSel(0);
	m_indexBaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->GetCurSel();
	switch(m_indexBaudRate)
	{
	case 0:
		m_nBaudRate=9600;
		break;
	case 1:
		m_nBaudRate=115200;
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CCommPortDlg::OnCbnSelchangeComboComPort()
{
	// TODO: 在此添加控件通知处理程序代码	
	m_indexPort=((CComboBox*)GetDlgItem(IDC_COMBO_COM_PORT))->GetCurSel();
	m_nCommPort=m_indexPort+1;
}


void CCommPortDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_indexBaudRate=((CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE))->GetCurSel();
	switch(m_indexBaudRate)
	{
	case 0:
		m_nBaudRate=9600;
		break;
	case 1:
		m_nBaudRate=115200;
		break;
	}
}
