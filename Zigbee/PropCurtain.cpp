// PropCurtain.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropCurtain.h"
#include "afxdialogex.h"


// CPropCurtain 对话框

IMPLEMENT_DYNAMIC(CPropCurtain, CPropertyPage)

CPropCurtain::CPropCurtain()
	: CPropertyPage(CPropCurtain::IDD)
{

}

CPropCurtain::~CPropCurtain()
{
}

void CPropCurtain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropCurtain, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CUR_ON, &CPropCurtain::OnBnClickedBtnCurOn)
	ON_BN_CLICKED(IDC_BTN_CUR_OFF, &CPropCurtain::OnBnClickedBtnCurOff)
END_MESSAGE_MAP()


// CPropCurtain 消息处理程序


BOOL CPropCurtain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

static int width=200;
void CPropCurtain::OnPaint()
{
	//擦除已画图形
	this->Invalidate(true);

	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CPropertyPage::OnPaint()
	
	/*
	//CClientDC dc(this);
	CDC* pDC=GetDC();
	CDC* pMemDC=new CDC;
	CBitmap* pMemBitmap=new CBitmap;
	CBitmap* pMemBitmapOld;
	CRect rectTemp;
	pMemDC->CreateCompatibleDC(NULL);
	pMemBitmap->CreateCompatibleBitmap(pDC,rectTemp.Width(),rectTemp.Height());
	pMemBitmapOld=pMemDC->SelectObject(pMemBitmap);
	//CBitmap* pBitmapOld=MemDC.SelectObject(&MemBitmap);
	//MemDC.FillSolidRect(0,0,rectTemp.Width(),rectTemp.Height(),RGB(255,255,255));
	CBrush brush2(RGB(0,128,255));
	pMemDC->SelectObject(brush2);
	pMemDC->Rectangle(90,66,90+width,250);
	pMemDC->Rectangle(290+(200-width),66,490,250);

	pDC->BitBlt(rectTemp.left,rectTemp.top,rectTemp.Width(),rectTemp.Height(),
		pMemDC,0,0,SRCCOPY);
	pMemDC->SelectObject(pMemBitmapOld);
	pMemBitmap->DeleteObject();
	pMemDC->DeleteDC();
	*/

	
	//窗帘上部
	CBrush brush1(RGB(128,0,0));
	dc.SelectObject(brush1);
	HRGN hRgn,hRgn1,hRgn2;
	hRgn = CreateRectRgn(50, 50, 530, 66);
	hRgn1 = CreateEllipticRgn(42, 50, 58, 66);
	hRgn2 = CreateEllipticRgn(522, 50, 538, 66);
	CombineRgn(hRgn, hRgn, hRgn1, RGN_OR);
	CombineRgn(hRgn, hRgn, hRgn2, RGN_OR);
	CRgn* rgn=CRgn::FromHandle(hRgn);
	dc.FillRgn(rgn, &brush1);
	DeleteObject(hRgn);
	DeleteObject(hRgn1);
	DeleteObject(hRgn2);

	//窗帘绘制
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	//CBrush* pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush brush2(RGB(0,128,255));
	dc.SelectObject(brush2);
	//CClientDC dc(this);
	dc.SelectObject(&pen);
	dc.Rectangle(90,66,90+width,250);
	dc.Rectangle(290+(200-width),66,490,250);
	
}


void CPropCurtain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 0:
		width-=1;
		if(width==50)
		{
			KillTimer(0);
		}
		break;
	case 1:
		width+=1;
		if(width==200)
		{
			KillTimer(1);
		}
		break;
	}
	CPropCurtain::OnPaint();
	this->Invalidate(FALSE);//显示内存中绘制的图形

	CPropertyPage::OnTimer(nIDEvent);
}

void CPropCurtain::OnBnClickedBtnCurOn()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	if(width>50&&width<=200)
		SetTimer(0,10,NULL);
}

void CPropCurtain::OnBnClickedBtnCurOff()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(0);
	if(width>=50&&width<200)
		SetTimer(1,10,NULL);
}
