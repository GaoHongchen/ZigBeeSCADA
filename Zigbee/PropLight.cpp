// PropLight.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropLight.h"
#include "afxdialogex.h"

#include "DataTypeConverter.h"
#include "ZigbeeDlg.h"

// CPropLight 对话框

IMPLEMENT_DYNAMIC(CPropLight, CPropertyPage)

CPropLight::CPropLight()
	: CPropertyPage(CPropLight::IDD)
	, on(_T(""))
	, off(_T(""))
	, isOnManFL(false)
	, isOnManFR(false)
	, isOnManBL(false)
	, isOnManBR(false)
	, strAddrBL(_T(""))
	, m_strLightBL(_T(""))
	, strAddrBR(_T(""))
{
	isOnFL=false;
	isOnFR=false;
	isOnBL=false;
	isOnBR=false;

	isOnManFL=false;
	isOnManFR=false;
	isOnManBL=false;
	isOnManBR=false;


	on="00";
	off="01";
}

CPropLight::~CPropLight()
{
}

void CPropLight::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_LIGHT_BL, m_strLightBL);
}


BEGIN_MESSAGE_MAP(CPropLight, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_FRONT_LEFT, &CPropLight::OnBnClickedBtnFrontLeft)
	ON_BN_CLICKED(IDC_BTN_FRONT_RIGHT, &CPropLight::OnBnClickedBtnFrontRight)
	ON_BN_CLICKED(IDC_BTN_BACK_LEFT, &CPropLight::OnBnClickedBtnBackLeft)
	ON_BN_CLICKED(IDC_BTN_BACK_RIGHT, &CPropLight::OnBnClickedBtnBackRight)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPropLight 消息处理程序


BOOL CPropLight::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//前排左侧
	m_btnFL.SubclassDlgItem(IDC_BTN_FRONT_LEFT,this);
	m_btnFL.SetIcon(IDI_ICON4);
	m_btnFL.SetFlat(true);//平面按钮
	//m_btnFL.SetWindowTextW(_T("前排左侧"));
	//m_btnFL.SetAlign(CButtonST::ST_ALIGN_HORIZ);//文字在下
	m_strLightBL=_T("BL");
		
	//前排右侧
	m_btnFR.SubclassDlgItem(IDC_BTN_FRONT_RIGHT,this);
	m_btnFR.SetIcon(IDI_ICON4);
	m_btnFR.SetFlat(true);//平面按钮
	//m_btnFR.SetWindowTextW(_T("前排右侧"));
	//m_btnFR.SetAlign(CButtonST::ST_ALIGN_HORIZ);//文字在下

	//后排左侧
	m_btnBL.SubclassDlgItem(IDC_BTN_BACK_LEFT,this);
	m_btnBL.SetIcon(IDI_ICON4);
	m_btnBL.SetFlat(true);//平面按钮
	//m_btnBL.SetWindowTextW(_T("后排左侧"));
	//m_btnBL.SetAlign(CButtonST::ST_ALIGN_HORIZ);//文字在下

	//后排右侧
	m_btnBR.SubclassDlgItem(IDC_BTN_BACK_RIGHT,this);
	m_btnBR.SetIcon(IDI_ICON4);
	m_btnBR.SetFlat(true);//平面按钮
	//m_btnBR.SetWindowTextW(_T("后排右侧"));
	//m_btnBR.SetAlign(CButtonST::ST_ALIGN_HORIZ);//文字在下 
	
	/*
	m_btnHall.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(208,208,208));
	m_btnHall.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(208,208,208));
	m_btnHall.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(208,208,208));
	*/

	m_Font.CreatePointFont(150, _T("黑体"), NULL);
	GetDlgItem(IDC_STATIC_LIGHT_BL)->SetFont(&m_Font,true);
	GetDlgItem(IDC_STATIC_LIGHT_BR)->SetFont(&m_Font,true);
	GetDlgItem(IDC_STATIC_LIGHT_FL)->SetFont(&m_Font,true);
	GetDlgItem(IDC_STATIC_LIGHT_FR)->SetFont(&m_Font,true);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


//控制灯数据包：55AA0AAA6B4310100100
void CPropLight::OnBnClickedBtnFrontLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	if(isOnFL)
	{
		m_btnFL.SetIcon(IDI_ICON4);
		isOnFL=false;
		isOnManFL=false;
	}
	else
	{
		m_btnFL.SetIcon(IDI_ICON3);
		isOnFL=true;
		isOnManFL=true;
	}
}


void CPropLight::OnBnClickedBtnFrontRight()
{
	// TODO: 在此添加控件通知处理程序代码
	if(isOnFR)
	{
		m_btnFR.SetIcon(IDI_ICON4);
		isOnFR=false;
		isOnManFR=false;
	}
	else
	{
		m_btnFR.SetIcon(IDI_ICON3);
		isOnFR=true;
		isOnManFR=true;
	}
}


void CPropLight::OnBnClickedBtnBackLeft()
{
	// TODO: 在此添加控件通知处理程序代码

	if(isOnBL)
	{
		//关灯
		m_btnBL.SetIcon(IDI_ICON4);
		isOnBL=false;
		isOnManBL=false;

		SetLight(off,strAddrBL);
	}
	else
	{
		//开灯
		m_btnBL.SetIcon(IDI_ICON3);
		isOnBL=true;
		isOnManBL=true;

		SetLight(on,strAddrBL);
	}
}


void CPropLight::OnBnClickedBtnBackRight()
{
	// TODO: 在此添加控件通知处理程序代码
	if(isOnBR)
	{
		m_btnBR.SetIcon(IDI_ICON4);
		isOnBR=false;
		isOnManBR=false;

		SetLight(off,strAddrBR);
	}
	else
	{
		m_btnBR.SetIcon(IDI_ICON3);
		isOnBR=true;
		isOnManBR=true;

		SetLight(on,strAddrBR);
	}
}


// 将十六进制形式的字符串发送到串口Buffer
void CPropLight::SetLight(CString strCtrl,CString strAddr)
{
	//((CMSComm*)((CZigbeeDlg*)GetParent()->GetDlgItem(IDC_MSCOMM)))->get_InBufferSize();
	//给CZigbeeDlg发送消息
	//HWND hWnd=GetDlgItem(IDD_ZIGBEE_DIALOG)->GetSafeHwnd();///((CZigbeeDlg*)GetParent())->GetSafeHwnd();
	//::PostMessage(hWnd,WM_RECVLIGHTDATA_MSG,0,(LPARAM)(LPCTSTR)m_strCtrlLightBL);

	CString m_strCtrlLight;
	m_strCtrlLight=_T("55aa0aaa")+strAddr+_T("1010")+strCtrl+_T("00");//6b43

	CDataTypeConverter DTC;
	COleVariant dataSend=DTC.HexM2OleVariant(m_strCtrlLight);

	//获取CZigbeeDlg对象的指针
	CZigbeeDlg *m_pZigbeeDlg=CZigbeeDlg::s_pZDlg;
	m_pZigbeeDlg->m_ctrlComm.put_Output(dataSend);
}


void CPropLight::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码

	/***************** 设置背景色 *******************/
	CRect rect; 
	//CPaintDC dc(this); 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(124,171,235));

	// 不为绘图消息调用 CPropertyPage::OnPaint()
	CPropertyPage::OnPaint();

}


HBRUSH CPropLight::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_LIGHT_BL://后排左侧静态文本框
		case IDC_STATIC_LIGHT_BR:
		case IDC_STATIC_LIGHT_FL:
		case IDC_STATIC_LIGHT_FR:
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(255,0,0));  //字体颜色
			//pDC->SetBkColor(RGB(128, 255, 255));
			HBRUSH hbrLightBL=CreateSolidBrush(RGB(128,255,255));
			return hbrLightBL;
			break;
		}
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
