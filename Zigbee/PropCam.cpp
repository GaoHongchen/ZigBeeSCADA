// PropCam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropCam.h"
#include "afxdialogex.h"


#pragma comment(lib,"vfw32.lib")

// CPropCam �Ի���

IMPLEMENT_DYNAMIC(CPropCam, CPropertyPage)

CPropCam::CPropCam()
	: CPropertyPage(CPropCam::IDD)
{

}

CPropCam::~CPropCam()
{
}

void CPropCam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropCam, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_CAM_OPEN, &CPropCam::OnBnClickedBtnCamOpen)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_CAM_CLOSE, &CPropCam::OnBnClickedBtnCamClose)
END_MESSAGE_MAP()


// CPropCam ��Ϣ�������


BOOL CPropCam::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ�� 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPropCam::OnBnClickedBtnCamOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ����Ԥ������
	CWnd *pWnd=GetDlgItem(IDC_ANIMATE_CAM);//�õ�Ԥ������ָ�룬ΪAnimate�ؼ�  AfxGetMainWnd()->
	CRect rect;
	pWnd->GetWindowRect(&rect); // �õ����ڴ�С

	m_hCapWnd=capCreateCaptureWindow(_T("Capture"),
		WS_CHILD|WS_VISIBLE,
		0,0,
		rect.Width(),rect.Width(),
		pWnd->GetSafeHwnd(),0); // ����Ԥ������,�������񴰿�
	if(!m_hCapWnd)
	{
		MessageBox(_T("Set preview window failed!"));
		return;
	}

	//�������嵽������ʵ��
	capSetUserData(m_hCapWnd, this);

	// ��������ͷ
	if(!capDriverConnect(m_hCapWnd,0))
	{
		MessageBox(_T("Connect to Camera failed!"));
		return;
	}

	//��ȡ���񴰿ڵ�ȱʡ����
	CAPTUREPARMS CapParms = {0};
	capCaptureGetSetup(m_hCapWnd, &CapParms, sizeof(CapParms));
	//�޸ĸոջ�õĲ���
	CapParms.fAbortLeftMouse = FALSE;   // �˳��������
	CapParms.fAbortRightMouse = FALSE;   // ...
	CapParms.fYield = TRUE;     // ʹ�ñ�����ҵ
	CapParms.fCaptureAudio = FALSE;         // ����ȡ����
	CapParms.wPercentDropForError = 50;   // ������ʧ�İٷֱ�
	//���ò��񴰿ڵ���ز���
	capCaptureSetSetup(m_hCapWnd, &CapParms, sizeof(CapParms));

	//�õ�������������
	capDriverGetCaps(m_hCapWnd,sizeof(CAPDRIVERCAPS), &m_CapDrvCap);

	if(m_CapDrvCap.fCaptureInitialized)		//�鿴����ͷ�Ƿ��ʼ���ɹ�
	{
		capGetStatus(m_hCapWnd, &m_CapStatus,sizeof(m_CapStatus)); //�õ�������״̬
		capPreviewRate(m_hCapWnd,30); // ����Ԥ��֡Ƶ��30 ms

		//ָ���Ƿ�ʹ�õ���ģʽ��ʹ��Ϊ1������Ϊ0   
		capOverlay(m_hCapWnd,   1);
		//��Ԥ��
		capPreview(m_hCapWnd,true);
		GetDlgItem(IDC_BTN_CAM_OPEN)->EnableWindow(false);
	}
	else
	{
		MessageBox(_T("Camera initilize failed!"));
		return;
	}
}


void CPropCam::OnBnClickedBtnCamClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ֹͣ����   
	capCaptureAbort(m_hCapWnd);     
	//������ͬ�������Ͽ�   
	capDriverDisconnect(m_hCapWnd); 
	GetDlgItem(IDC_BTN_CAM_OPEN)->EnableWindow(true);
}


//void CPropCam::OnBnClickedBtnCamCapture()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	capFileSaveDIB(m_hCapWnd,"capture.bmp");
//}


//void CPropCam::OnBnClickedBtnCamRecord()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	capFileSetCaptureFile(m_hCapWnd,"video.avi");	//���ñ���·��
//	capFileAlloc(m_hCapWnd,(1024L*1024L*5));		//�����ļ�����
//	capCaptureSequence(m_hCapWnd);					//��ʼ��׽
//}


void CPropCam::OnPaint()
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
