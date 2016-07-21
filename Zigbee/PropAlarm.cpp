// PropAlarm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropAlarm.h"
#include "afxdialogex.h"


// CPropAlarm �Ի���

IMPLEMENT_DYNAMIC(CPropAlarm, CPropertyPage)

CPropAlarm::CPropAlarm()
	: CPropertyPage(CPropAlarm::IDD)
	, m_strStaticRealNum(_T(""))
	, m_strAttendanceRate(_T(""))
	, m_strName(_T(""))
	, m_strID(_T(""))
{

}

CPropAlarm::~CPropAlarm()
{
}

void CPropAlarm::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_REALNUM_VALUE, m_strStaticRealNum);
	DDX_Text(pDX, IDC_STATIC_REALNUM_VALUE, m_strStaticRealNum);
	DDX_Text(pDX, IDC_STATIC_RATE_VALUE, m_strAttendanceRate);
	DDX_Text(pDX, IDC_STATIC_NAME, m_strName);
	DDX_Text(pDX, IDC_STATIC_ID, m_strID);
}


BEGIN_MESSAGE_MAP(CPropAlarm, CPropertyPage)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPropAlarm ��Ϣ�������


BOOL CPropAlarm::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//����ѡ�����
	m_FontClassroomCH.CreatePointFont(200, _T("����"), NULL);

	GetDlgItem(IDC_STATIC_SUBJECT)->SetFont(&m_FontClassroomCH,true); 
	GetDlgItem(IDC_STATIC_CLASS)->SetFont(&m_FontClassroomCH,true); 
	GetDlgItem(IDC_STATIC_NUM)->SetFont(&m_FontClassroomCH,true); 
	GetDlgItem(IDC_STATIC_REALNUM)->SetFont(&m_FontClassroomCH,true); 
	GetDlgItem(IDC_STATIC_RATE)->SetFont(&m_FontClassroomCH,true); 

	GetDlgItem(IDC_STATIC_SUBJECT_VALUE)->SetFont(&m_FontClassroomCH,true); 
	GetDlgItem(IDC_STATIC_CLASS_VALUE)->SetFont(&m_FontClassroomCH,true);

	GetDlgItem(IDC_STATIC_NAME)->SetFont(&m_FontClassroomCH,true);

	//m_FontClassroom.DeleteObject();

	m_FontClassroomEN.CreatePointFont(200, _T("Arial"), NULL);

	GetDlgItem(IDC_STATIC_NUM_VALUE)->SetFont(&m_FontClassroomEN,true);
	GetDlgItem(IDC_STATIC_NUM_VALUE)->SetWindowTextW(_T("30"));
	GetDlgItem(IDC_STATIC_REALNUM_VALUE)->SetFont(&m_FontClassroomEN,true);
	GetDlgItem(IDC_STATIC_REALNUM_VALUE)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_STATIC_RATE_VALUE)->SetFont(&m_FontClassroomEN,true); 
	GetDlgItem(IDC_STATIC_RATE_VALUE)->SetWindowTextW(_T("0 %"));

	GetDlgItem(IDC_STATIC_ID)->SetFont(&m_FontClassroomEN,true); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPropAlarm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	/***************** ���ñ���ɫ *******************/
	CRect rect; 
	//CPaintDC dc(this); 
	GetClientRect(rect); 
	dc.FillSolidRect(rect,RGB(124,171,235));

	// ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
	CPropertyPage::OnPaint();
}
