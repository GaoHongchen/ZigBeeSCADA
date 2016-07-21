// PropCurtain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropCurtain.h"
#include "afxdialogex.h"


// CPropCurtain �Ի���

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


// CPropCurtain ��Ϣ�������


BOOL CPropCurtain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

static int width=200;
void CPropCurtain::OnPaint()
{
	//�����ѻ�ͼ��
	this->Invalidate(true);

	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
	
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

	
	//�����ϲ�
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

	//��������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	this->Invalidate(FALSE);//��ʾ�ڴ��л��Ƶ�ͼ��

	CPropertyPage::OnTimer(nIDEvent);
}

void CPropCurtain::OnBnClickedBtnCurOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	if(width>50&&width<=200)
		SetTimer(0,10,NULL);
}

void CPropCurtain::OnBnClickedBtnCurOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(0);
	if(width>=50&&width<200)
		SetTimer(1,10,NULL);
}
