// PropAircon.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropAircon.h"
#include "afxdialogex.h"

#include<math.h>

// CPropAircon 对话框

IMPLEMENT_DYNAMIC(CPropAircon, CPropertyPage)

CPropAircon::CPropAircon()
	: CPropertyPage(CPropAircon::IDD)
{

}

CPropAircon::~CPropAircon()
{
}

void CPropAircon::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropAircon, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPropAircon 消息处理程序


BOOL CPropAircon::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//空调1
	m_btnAircondition1.SubclassDlgItem(IDC_BTN_AIRCON1,this);
	m_btnAircondition1.SetIcon(IDI_ICON9,IDI_ICON9);
	m_btnAircondition1.SetFlat(true);//平面按钮
	m_btnAircondition1.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);//CButtonST::ST_ALIGN_VERT文字在下
	//空调2
	m_btnAircondition2.SubclassDlgItem(IDC_BTN_AIRCON2,this);
	m_btnAircondition2.SetIcon(IDI_ICON9,IDI_ICON9);
	m_btnAircondition2.SetFlat(true);//平面按钮
	m_btnAircondition2.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);//文字在左
	//m_btnAircondition2.EnableWindow(false);

	//btn左
	HRGN rgnLeft;
	HDC hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	BeginPath(hDC);

	MoveToEx(hDC,int(200-80/2*sqrt(2.0)),int(200-80/2*sqrt(2.0)),NULL);
	LineTo(hDC,int(200-40/2*sqrt(2.0)),int(200-40/2*sqrt(2.0)));

	AngleArc(hDC,200,200,40,135,90);

	LineTo(hDC,int(200-80/2*sqrt(2.0)),int(200+80/2*sqrt(2.0)));

	AngleArc(hDC,200,200,80,225,-90);

	EndPath(hDC);

	rgnLeft = PathToRegion(hDC);
	m_BtnLeft.Create(_T("L"), WS_CHILD | WS_VISIBLE, CPoint(80, 200), rgnLeft, this, UNI_BTNL, 2, RGB(250, 207, 194), RGB(0, 255, 0), RGB(255, 0, 0), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnLeft);
	DeleteObject(hDC);

	//btn右
	HRGN rgnRight;
	hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	BeginPath(hDC);

	MoveToEx(hDC,int(200+80/2*sqrt(2.0)),int(200-80/2*sqrt(2.0)),NULL);
	LineTo(hDC,int(200+40/2*sqrt(2.0)),int(200-40/2*sqrt(2.0)));

	AngleArc(hDC,200,200,40,45,-90);

	LineTo(hDC,int(200+80/2*sqrt(2.0)),int(200+80/2*sqrt(2.0)));

	AngleArc(hDC,200,200,80,-45,90);

	EndPath(hDC);

	rgnRight = PathToRegion(hDC);
	m_BtnRight.Create(_T("R"), WS_CHILD | WS_VISIBLE, CPoint(198, 196), rgnRight, this, UNI_BTNR, 2, RGB(250, 207, 194), RGB(0, 255, 0), RGB(255, 0, 0), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnRight);
	DeleteObject(hDC);

	//btn上
	HRGN rgnUp;
	hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	BeginPath(hDC);

	MoveToEx(hDC,int(200+80/2*sqrt(2.0)),int(200-80/2*sqrt(2.0)),NULL);
	LineTo(hDC,int(200+40/2*sqrt(2.0)),int(200-40/2*sqrt(2.0)));

	AngleArc(hDC,200,200,40,45,90);

	LineTo(hDC,int(200-80/2*sqrt(2.0)),int(200-80/2*sqrt(2.0)));

	AngleArc(hDC,200,200,80,135,-90);

	EndPath(hDC);

	rgnUp = PathToRegion(hDC);
	m_BtnUp.Create(_T("U"), WS_CHILD | WS_VISIBLE, CPoint(110, 170), rgnUp, this, UNI_BTNU, 2, RGB(250, 207, 194), RGB(0, 255, 0), RGB(255, 0, 0), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnUp);
	DeleteObject(hDC);

	//btn下
	HRGN rgnDown;
	hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	BeginPath(hDC);

	MoveToEx(hDC,int(200+80/2*sqrt(2.0)),int(200+80/2*sqrt(2.0)),NULL);
	LineTo(hDC,int(200+40/2*sqrt(2.0)),int(200+40/2*sqrt(2.0)));

	AngleArc(hDC,200,200,40,-45,-90);

	LineTo(hDC,int(200-80/2*sqrt(2.0)),int(200+80/2*sqrt(2.0)));

	AngleArc(hDC,200,200,80,225,90);

	EndPath(hDC);

	rgnDown = PathToRegion(hDC);
	m_BtnDown.Create(_T("D"), WS_CHILD | WS_VISIBLE, CPoint(107, 288), rgnDown, this, UNI_BTND, 2, RGB(250, 207, 194), RGB(0, 255, 0), RGB(255, 0, 0), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnDown);
	DeleteObject(hDC);

	//btn中
	HRGN rgnMid;
	hDC = CreateCompatibleDC(GetDC() -> GetSafeHdc());
	BeginPath(hDC);
	AngleArc(hDC,200,200,40,0,360);
	//Ellipse(hDC,170,170,230,230);
	EndPath(hDC);
	rgnMid = PathToRegion(hDC);
	m_BtnMid.Create(_T("M"), WS_CHILD | WS_VISIBLE, CPoint(125, 215), rgnMid, this, UNI_BTNM, 2, RGB(250, 207, 194), RGB(0, 255, 0), RGB(255, 0, 0), GetSysColor(COLOR_BTNFACE)); 

	DeleteObject(rgnMid);
	DeleteObject(hDC);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPropAircon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CPropertyPage::OnPaint()
}
