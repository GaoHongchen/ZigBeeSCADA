// CommPortDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Zigbee.h"
#include "CommPortDlg.h"
#include "afxdialogex.h"


// CCommPortDlg �Ի���

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


// CCommPortDlg ��Ϣ�������


BOOL CCommPortDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	/*********************** �������� **************************/
	//���ں�
	((CComboBox*)GetDlgItem(IDC_COMBO_COM_PORT))->SetCurSel(0);
	m_indexPort=((CComboBox*)GetDlgItem(IDC_COMBO_COM_PORT))->GetCurSel();
	m_nCommPort=m_indexPort+1;	
	//������
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCommPortDlg::OnCbnSelchangeComboComPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	m_indexPort=((CComboBox*)GetDlgItem(IDC_COMBO_COM_PORT))->GetCurSel();
	m_nCommPort=m_indexPort+1;
}


void CCommPortDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
