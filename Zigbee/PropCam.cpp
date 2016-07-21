// PropCam.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "PropCam.h"
#include "afxdialogex.h"


#pragma comment(lib,"vfw32.lib")

// CPropCam 对话框

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


// CPropCam 消息处理程序


BOOL CPropCam::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPropCam::OnBnClickedBtnCamOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	// 设置预览窗口
	CWnd *pWnd=GetDlgItem(IDC_ANIMATE_CAM);//得到预览窗口指针，为Animate控件  AfxGetMainWnd()->
	CRect rect;
	pWnd->GetWindowRect(&rect); // 得到窗口大小

	m_hCapWnd=capCreateCaptureWindow(_T("Capture"),
		WS_CHILD|WS_VISIBLE,
		0,0,
		rect.Width(),rect.Width(),
		pWnd->GetSafeHwnd(),0); // 设置预览窗口,创建捕获窗口
	if(!m_hCapWnd)
	{
		MessageBox(_T("Set preview window failed!"));
		return;
	}

	//关联窗体到本程序实例
	capSetUserData(m_hCapWnd, this);

	// 连接摄像头
	if(!capDriverConnect(m_hCapWnd,0))
	{
		MessageBox(_T("Connect to Camera failed!"));
		return;
	}

	//获取捕获窗口的缺省参数
	CAPTUREPARMS CapParms = {0};
	capCaptureGetSetup(m_hCapWnd, &CapParms, sizeof(CapParms));
	//修改刚刚获得的参数
	CapParms.fAbortLeftMouse = FALSE;   // 退出鼠标设置
	CapParms.fAbortRightMouse = FALSE;   // ...
	CapParms.fYield = TRUE;     // 使用背景作业
	CapParms.fCaptureAudio = FALSE;         // 不获取声音
	CapParms.wPercentDropForError = 50;   // 允许遗失的百分比
	//设置捕获窗口的相关参数
	capCaptureSetSetup(m_hCapWnd, &CapParms, sizeof(CapParms));

	//得到驱动器的属性
	capDriverGetCaps(m_hCapWnd,sizeof(CAPDRIVERCAPS), &m_CapDrvCap);

	if(m_CapDrvCap.fCaptureInitialized)		//查看摄像头是否初始化成功
	{
		capGetStatus(m_hCapWnd, &m_CapStatus,sizeof(m_CapStatus)); //得到驱动器状态
		capPreviewRate(m_hCapWnd,30); // 设置预览帧频，30 ms

		//指定是否使用叠加模式，使用为1，否则为0   
		capOverlay(m_hCapWnd,   1);
		//打开预览
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
	// TODO: 在此添加控件通知处理程序代码
	//停止捕获   
	capCaptureAbort(m_hCapWnd);     
	//将捕获窗同驱动器断开   
	capDriverDisconnect(m_hCapWnd); 
	GetDlgItem(IDC_BTN_CAM_OPEN)->EnableWindow(true);
}


//void CPropCam::OnBnClickedBtnCamCapture()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	capFileSaveDIB(m_hCapWnd,"capture.bmp");
//}


//void CPropCam::OnBnClickedBtnCamRecord()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	capFileSetCaptureFile(m_hCapWnd,"video.avi");	//设置保存路径
//	capFileAlloc(m_hCapWnd,(1024L*1024L*5));		//设置文件缓存
//	capCaptureSequence(m_hCapWnd);					//开始捕捉
//}


void CPropCam::OnPaint()
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
