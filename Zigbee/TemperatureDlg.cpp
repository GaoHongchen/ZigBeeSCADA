// TemperatureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Zigbee.h"
#include "TemperatureDlg.h"
#include "afxdialogex.h"

#include "DataTypeConverter.h"

static UINT BASED_CODE indicators[]={ID_SEPARATOR};

// CTemperatureDlg �Ի���

IMPLEMENT_DYNAMIC(CTemperatureDlg, CDialog)

CTemperatureDlg::CTemperatureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTemperatureDlg::IDD, pParent)
	, m_strTemperatureRX(_T(""))
{
}

CTemperatureDlg::~CTemperatureDlg()
{
}

void CTemperatureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTemperatureDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTemperatureDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTemperatureDlg ��Ϣ�������


BOOL CTemperatureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//*********************** ʾ�������� **************************//
	//�ؼ�������
	CRect rect;
	GetDlgItem(IDC_OSCOPE)->GetWindowRect(rect);
	ScreenToClient(rect);
	//�����ؼ�
	m_OScopeCtrl.Create(WS_VISIBLE | WS_CHILD,rect,this);
	//�Զ���ؼ�
	m_OScopeCtrl.SetRange(0,40,1);
	m_OScopeCtrl.SetYUnits(_T("Temperature"));
	m_OScopeCtrl.SetXUnits(_T("Time Elapse: 100 msec"));
	m_OScopeCtrl.SetBackgroundColor(RGB(0,0,0));
	m_OScopeCtrl.SetGridColor(RGB(192,192,192));
	m_OScopeCtrl.SetPlotColor(RGB(255,0,0),RGB(0,255,0),RGB(0,0,255));

	/************************ ״̬�� **************************/
	m_ZigbeeDlg=(CZigbeeDlg*)GetParent();
	m_strTemperatureRX=m_ZigbeeDlg->strTemperatureHumidityRX;
	//MessageBox(m_strTemperatureRX);
	m_StatusBar.CreateEx(this,SBT_TOOLTIPS,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,AFX_IDW_STATUS_BAR );
	//m_StatusBar.Create(WS_BORDER|WS_VISIBLE|CBRS_BOTTOM,m_Rect,this,3);
	m_StatusBar.SetIndicators(indicators,1);//����ָʾ������
	//CRect rect;
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL ,rect.Width());
	//����Ҫ****
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,ID_SEPARATOR);

	m_StatusBar.SetPaneText(0,_T("�豸���ͣ� ")+m_strTemperatureRX.Mid(2,3)
							 +_T("      ���ڵ��ַ�� ")+m_strTemperatureRX.Mid(5,4)
							 +_T("      ���ڵ��ַ�� ")+m_strTemperatureRX.Mid(9,4)
							 +_T("      �¶�ֵ�� ")+m_strTemperatureRX.Mid(14,2),0);


	SetTimer(0,200,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTemperatureDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_strTemperatureRX=((CZigbeeDlg*)GetParent())->strTemperatureHumidityRX;
	//״̬������
	m_StatusBar.SetPaneText(0,_T("�豸���ͣ� ")+m_strTemperatureRX.Mid(2,3)
							 +_T("    �����ַ�� ")+m_strTemperatureRX.Mid(5,4)
							 +_T("    �ڵ��ַ�� ")+m_strTemperatureRX.Mid(9,4)
							 +_T("    �¶�ֵ�� ")+m_strTemperatureRX.Mid(14,2),0);

		
	CDataTypeConverter DTC;
	int intTemperatureValue=DTC.Hex2Dec(m_strTemperatureRX.Mid(16,2));

	m_OScopeCtrl.AppendPoint(intTemperatureValue,-1,-1);

	CDialog::OnTimer(nIDEvent);
}


void CTemperatureDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(0);
	CDialog::OnOK();
}
