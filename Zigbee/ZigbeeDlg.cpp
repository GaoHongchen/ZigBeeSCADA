
// ZigbeeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Zigbee.h"
#include "ZigbeeDlg.h"
#include "afxdialogex.h"

#include "SplashWnd.h"
#include "CommPortDlg.h"
#include "TemperatureDlg.h"
#include "HumidityDlg.h"
#include "IlluminationDlg.h"
#include "CarbonDioxideDlg.h"
#include "DataTypeConverter.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT BASED_CODE indicators[]=
	//状态栏的指示器列表，如有未定义的字符串名，需在Resource View的String Table中添加定义
{
	IDS_COMMPORTINFO,
	IDS_NODE_INFO,//ID_INDICATOR_NUM,
	//ID_SEPARATOR,
	IDS_TIMER,
	IDS_AUTHOR
	//ID_INDICATOR_USER,//需在Resource View的String Table中添加定义
};

CZigbeeDlg* CZigbeeDlg::s_pZDlg=NULL;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CFont m_FontLink;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	HCURSOR m_hCursor;
	RECT m_HomeLinkRect;
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnStnClickedStaticHomepageLink();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_STN_CLICKED(IDC_STATIC_HOMEPAGE_LINK, &CAboutDlg::OnStnClickedStaticHomepageLink)
END_MESSAGE_MAP()


// CZigbeeDlg 对话框

CZigbeeDlg::CZigbeeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZigbeeDlg::IDD, pParent)
	, m_strDataRX(_T(""))
	, m_strDataTX(_T(""))
	, m_bAlert(false)
	, m_bAlertBeep(false)
	, strTemperatureValue(_T(""))
	, strTemperatureHumidityRX(_T(""))
	, m_strDataRXTemp(_T(""))
	, isBright(false)
	, strInfraredRX(_T(""))
	, strLightRX(_T(""))
	, strClassRX(_T(""))
	, flagLightAddr(false)
	, m_strSysTitle(_T("Smartroom SCADA（大学生创新训练计划）"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CZigbeeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_DATAREC, m_strDataRX);
	DDX_Text(pDX, IDC_EDIT_DATASEND, m_strDataTX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}

BEGIN_MESSAGE_MAP(CZigbeeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CZigbeeDlg::OnBnClickedBtnSend)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CZigbeeDlg::OnTcnSelchangeTab)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_DEVMGMT, &CZigbeeDlg::OnBnClickedBtnDevmgmt)
	ON_BN_CLICKED(IDC_BTN_COMM_PORT, &CZigbeeDlg::OnBnClickedBtnCommPort)
	ON_BN_CLICKED(IDC_BTN_TEMPERATURE, &CZigbeeDlg::OnBnClickedBtnTemperature)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BTN_HUMIDITY, &CZigbeeDlg::OnBnClickedBtnHumidity)
	//ON_BN_CLICKED(IDC_BTN_ILLUMINATION, &CZigbeeDlg::OnBnClickedBtnIllumination)
	//ON_BN_CLICKED(IDC_BTN_CARBON_DIOXIDE, &CZigbeeDlg::OnBnClickedBtnCarbonDioxide)
	ON_BN_CLICKED(IDC_BTN_HELP, &CZigbeeDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_SYS_SETTING, &CZigbeeDlg::OnBnClickedBtnSysSetting)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDOK, &CZigbeeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CZigbeeDlg::OnBnClickedBtnClear)
	//ON_MESSAGE(WM_RECVLIGHTDATA_MSG, OnRecvLightDataMessage)//自定义消息
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CZigbeeDlg::OnBnClickedBtnAbout)
END_MESSAGE_MAP()


// CZigbeeDlg 消息处理程序

BOOL CZigbeeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_hIcon   =   AfxGetApp()-> LoadIcon(IDR_ICON);//IDR_MAINFRAME
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	/************************ 获取.exe目录 **************************/
	GetModuleFileNameW(NULL,dirApp,MAX_PATH);
	(_tcsrchr(dirApp,_T('\\')))[1] = 0;//删除文件名，只获得路径

	//初始化窗口标题
	this->SetWindowTextW(m_strSysTitle);

	//禁用X型关闭按钮
	ASSERT(pSysMenu != NULL);
	//pSysMenu->EnableMenuItem(SC_CLOSE,MF_DISABLED);//使关闭按钮无效
	//VERIFY(pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND));
	pSysMenu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED );//禁用关闭按钮

	/************************ 标题初始化 **************************/
	CFont* font = new CFont;
	font->CreateFont(30,            // nHeight
		0,           // nWidth
		0,           // nEscapement
		0,           // nOrientation
		FW_BOLD,     // nWeight
		FALSE,        // bItalic
		FALSE,       // bUnderline
		0,           // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
		_T("Arial"));              // lpszFac
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(font);

	/************************ 静态文本框初始化 **************************/
	GetDlgItem(IDC_STATIC_TEMPERATURE)->SetWindowTextW(_T("0 ℃"));
	GetDlgItem(IDC_STATIC_HUMIDITY)->SetWindowTextW(_T("0 ％"));
	//光照字体
	m_FontIllumination.CreatePointFont(300, _T("黑体"), NULL);  
	GetDlgItem(IDC_STATIC_ILLUMINATION)->SetFont(&m_FontIllumination,true); 

	/************************ 属性表单 **************************/
	//添加选项卡
	m_tab.InsertItem(0,_T("灯光控制"));  
	m_tab.InsertItem(1,_T("空调控制"));
	m_tab.InsertItem(2,_T("窗帘控制"));
	m_tab.InsertItem(3,_T("考勤情况"));
	m_tab.InsertItem(4,_T("监控设备"));
	//关联对话框,并且将IDC_TAB控件设为父窗口 
	m_pageLight.Create(IDD_PROPAGE_CTRL_LIGHT,&m_tab);
	m_pageAircon.Create(IDD_PROPAGE_CTRL_AIRCON,&m_tab);
	m_pageCurtain.Create(IDD_PROPAGE_CTRL_CURTAIN,&m_tab);
	m_pageAlarm.Create(IDD_PROPAGE_CTRL_ALARM,&m_tab);
	m_pageCam.Create(IDD_PROPAGE_CTRL_CAM,&m_tab);
	
	//获得IDC_TAB客户区大小 
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	//设置子对话框尺寸并移动到指定位置 
	m_pageLight.MoveWindow(&rc);
	m_pageAircon.MoveWindow(&rc);
	m_pageCurtain.MoveWindow(&rc);
	m_pageCam.MoveWindow(&rc);
	m_pageAlarm.MoveWindow(&rc);
	//分别设置隐藏和显示 
	m_pageLight.ShowWindow(true);
	m_pageAircon.ShowWindow(false);
	m_pageCurtain.ShowWindow(false);
	m_pageCam.ShowWindow(false);
	m_pageAlarm.ShowWindow(false);
	//设置默认的选项卡 
	m_tab.SetCurSel(0);

	/************************ 状态栏 **************************/
	m_StatusBar.CreateEx(this,SBT_TOOLTIPS,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,AFX_IDW_STATUS_BAR );
	unsigned short int nIndicators=sizeof(indicators)/sizeof(UINT);
	m_StatusBar.SetIndicators(indicators,nIndicators);//设置指示器数量
	CRect rect;
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,IDS_COMMPORTINFO,SBPS_NORMAL ,rect.Width()/6*2);
	m_StatusBar.SetPaneInfo(1,IDS_NODE_INFO,SBPS_NORMAL,rect.Width()/6*2);
	m_StatusBar.SetPaneInfo(2,IDS_TIMER,SBPS_NORMAL,rect.Width()/6*1);//szCurTime.cx
	m_StatusBar.SetPaneInfo(3,IDS_AUTHOR,SBPS_NORMAL,rect.Width()/6*1);
	//很重要****
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,IDS_COMMPORTINFO);
	//m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(255,0,0));//设置背景RGB(180,20,180)
	//状态栏时间
	SetTimer(0,1000,NULL);//系统时间

	s_pZDlg=this;

	/************************ 串口初始化及其状态栏信息显示 **************************/
	SetCommPort(1,9600);
	m_StatusBar.SetPaneText(0,_T("串口：COM 1     波特率：9600"),0);

	/************************ 警报初始化 **************************/
	if(false)
	{
		SetTimer(1,100,NULL);//声音报警
	}

	SetTimer(2,500,NULL);//标题滚动

	m_color=RGB(121,255,0);//背景色

	//GetSystemMetrics(  SM_CXSCREEN  );  //获得屏幕的分辨率

	//获取对话框的大小，从而改变其位置
	//this->GetClientRect(m_RectDlgClient);
	this->GetWindowRect(m_RectDlgScreen);
	m_RectDlgClient=m_RectDlgScreen;
	ScreenToClient(m_RectDlgClient);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZigbeeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZigbeeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/***************** 设置背景色 *******************/
		CRect rect; 
		CPaintDC dc(this); 
		GetClientRect(rect); 
		dc.FillSolidRect(rect,m_color);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZigbeeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CZigbeeDlg, CDialogEx)
	ON_EVENT(CZigbeeDlg, IDC_MSCOMM, 1, CZigbeeDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()


int CZigbeeDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//启动画面代码
	CenterWindow();  
    CSplashWnd::ShowSplashScreen(this);  
    Sleep(1000);//使得画面停止约1s后启动主画面，貌似可以用定时器
	
	return 0;
}


void CZigbeeDlg::OnCommMscomm()
{
	// TODO: 在此处添加消息处理程序代码
	
	CDataTypeConverter DTC;
	//电话图标可能有一半白边去不了，右击电话图标点击edit control就可以去掉
	if(m_ctrlComm.get_CommEvent()==2)//事件值为2表示接收事件
	{
		BYTE rxdata[255]={0};//设置BYTE数组
		VARIANT variant_inp=m_ctrlComm.get_Input();//读缓冲区
		COleSafeArray safearray_inp = variant_inp;//VARIANT型变量转换为COleSafeArray变量
		long len=safearray_inp.GetOneDimSize();//得到有效数据长度
		for(long k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE数组
		m_ctrlComm.put_OutBufferCount(0);//清空发送缓冲区
		m_ctrlComm.put_InBufferCount(0);//滑空接收缓冲区
		safearray_inp.Clear();
			
		for(long k=0;k<len;k++)
		{
			BYTE bt = *(char*)(rxdata+k);//字符型
			short int intDec=(int)bt;
			CString strtemp=DTC.Dec2Hex(intDec);
			m_strDataRXTemp+=strtemp;//加入接收编辑框对应字符串
		}
		m_strDataRX=m_strDataRXTemp;
		m_strDataRXTemp="";

		UpdateData(false);
	}
	
	//温湿度传感器
	if(m_strDataRX.Mid(12,4)=="0220")//m_strDataRX.GetAt(13)=='T'
	{
		strTemperatureHumidityRX = m_strDataRX;
		int intTemperatureValue,intHumidityValue;

		//温度值
		strTemperatureValue = m_strDataRX.Mid(16,2);
		if(strTemperatureValue=="")
		{
			strTemperatureValue="0";
		}
		else
		{
			intTemperatureValue=DTC.Hex2Dec(strTemperatureValue);
			strTemperatureValue.Format(_T("%d"),intTemperatureValue);
		}
		strTemperatureValue += _T(" ℃");
		GetDlgItem(IDC_STATIC_TEMPERATURE)->SetWindowTextW(strTemperatureValue);

		//湿度值strHumidityValue
		strHumidityValue = m_strDataRX.Mid(18,2);
		if(strHumidityValue=="")
		{
			strHumidityValue="0";
		}
		else
		{
			intHumidityValue=DTC.Hex2Dec(strHumidityValue);
			strHumidityValue.Format(_T("%d"),intHumidityValue);
		}
		strHumidityValue += _T(" ％");
		GetDlgItem(IDC_STATIC_HUMIDITY)->SetWindowTextW(strHumidityValue);
	}

	//光照
	if(m_strDataRX.Mid(12,4)=="1110")
	{
		strIlluminationRX = m_strDataRX;
		if(strIlluminationRX.Mid(16,2)=="00")
		{
			GetDlgItem(IDC_STATIC_ILLUMINATION)->SetWindowTextW(_T("明亮"));
			isBright=true;
		}
		else if(strIlluminationRX.Mid(16,2)=="01")
		{
			GetDlgItem(IDC_STATIC_ILLUMINATION)->SetWindowTextW(_T("昏暗"));
			isBright=false;
		}
		//this->Invalidate();
		//::SendMessage(m_hWnd, WM_CTLCOLOR, (WPARAM)(this->GetDC()->GetSafeHdc()), (LPARAM)(m_hWnd));
		GetDlgItem(IDC_STATIC_ILLUMINATION)->Invalidate();
	}

	//热释电（红外）
	if(m_strDataRX.Mid(12,4)=="0120")
	{
		strInfraredRX=m_strDataRX;
		if(strInfraredRX.Mid(16,2)=="01")//有人
		{
			if(isBright)// && !m_pageLight.isOnManBL
			{
				//关灯
				m_pageLight.SetLight(m_pageLight.off,m_pageLight.strAddrBL);
				m_pageLight.m_btnBL.SetIcon(IDI_ICON4);
				m_pageLight.m_strLightBL=_T("阳光明媚 有人");

			}
			if(!isBright)// && m_pageLight.isOnManBL
			{
				//开灯
				m_pageLight.SetLight(m_pageLight.on,m_pageLight.strAddrBL);
				m_pageLight.m_btnBL.SetIcon(IDI_ICON3);
				m_pageLight.m_strLightBL=_T("光照不足 有人");
			}
		}
		else if(strInfraredRX.Mid(16,2)=="00" )//&& !m_pageLight.isOnManBL
		{
			//关灯
			m_pageLight.SetLight(m_pageLight.off,m_pageLight.strAddrBL);
			m_pageLight.m_btnBL.SetIcon(IDI_ICON4);
			m_pageLight.m_strLightBL=_T("无人");
		}
		m_pageLight.UpdateData(false);
	}

	//灯
	if(m_strDataRX.Mid(12,4)=="1010")
	{
		strLightRX=m_strDataRX;
		if(flagLightAddr==false)
		{
			m_pageLight.strAddrBL=strLightRX.Mid(8,4);
			flagLightAddr=true;
		}
		else
		{
			if(m_pageLight.strAddrBL!=strLightRX.Mid(8,4))
			{
				m_pageLight.strAddrBR=strLightRX.Mid(8,4);
			}
		}
	}

	//课堂情况
	if(m_strDataRX.Mid(12,4)=="2320")
	{
		strClassRX=m_strDataRX;
		CString strClassValue;//ID
		strClassValue=strClassRX.Mid(16,8);

		CString strIDDec(_T(""));
		for(int n=0;n<strClassValue.GetLength()-1;n+=2)
		{		
			int intDec=DTC.Hex2Dec(strClassValue.Mid(n,2));
			CString strDec;
			strDec.Format(_T("%d"),intDec);
			if(strDec.GetLength()<3)
			{
				for(int i=0;i<3-strDec.GetLength();i++)
				{
					strDec=_T("0")+strDec;
				}
			}
			strIDDec+=strDec;
		}

		//刷卡逻辑：重复刷卡，警告；不重复，人数增加
		static CString strID[30]={_T("")};
		short int n=0;
		static short int num=0;
		bool flag=false;
		for(int i=0;i<30;i++)
		{
			if(strID[i]=="")
			{
				if(i==0)
				{
					strID[i]=strClassValue;
					m_pageAlarm.m_strID=strIDDec;
					m_pageAlarm.m_strName=_T("高洪臣");
					num=1;
					break;
				}
				n=i;
				break;
			}
			else
			{
				if(strID[i]==strClassValue)
				{
					MessageBox(_T("您已刷卡！"));
					flag=false;
					break;
				}
				flag=true;
			}
		}
		if(flag)
		{
			strID[n]=strClassValue;
			m_pageAlarm.m_strID=strIDDec;
			m_pageAlarm.m_strName=_T("卢晓健");
			num++;
		}

		float rate=((float)num)/30;

		CString strRealNum,strAttendanceRate;

		strRealNum.Format(_T("%d"),num);
		m_pageAlarm.m_strStaticRealNum=strRealNum;

		strAttendanceRate.Format(_T("%.1f %%"),rate*100);		
		m_pageAlarm.m_strAttendanceRate=strAttendanceRate;

		//m_pageAlarm.m_strName=_T("高洪臣");

		m_pageAlarm.UpdateData(false);
	}

	UpdateData(false);
}

void CZigbeeDlg::OnBnClickedBtnSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);//读取编辑框内容m_strDataTX

	//发送的字符串上表面为十六进制格式
	CString m_strCtrlLightBL;
	m_strCtrlLightBL=_T("55AA0AAA")+m_pageLight.strAddrBL+_T("10100100");//"55aa0aaa6b4310100000"
	//m_strCtrlLightBL=_T("55AA0AAAB27110100000");

	CDataTypeConverter DTC;
	COleVariant m_OleVariant=DTC.HexM2OleVariant(m_strCtrlLightBL);

	m_ctrlComm.put_Output(m_OleVariant);//发送数据
}

void CZigbeeDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned short int nTabCurSel=m_tab.GetCurSel();
	switch(nTabCurSel)
	{
	case 0:
		//分别设置隐藏和显示 
		m_pageLight.ShowWindow(true);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(false);
		break;
	case 1:
		//分别设置隐藏和显示 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(true);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(false);
		break;
	case 2:
		//分别设置隐藏和显示 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(true);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(false);
		break;
	case 3:
		//分别设置隐藏和显示 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(true);
		m_pageCam.ShowWindow(false);
		break;
	case 4:
		//分别设置隐藏和显示 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(true);
		break;
	}
	*pResult = 0;
}

CString str;
CTime curtime;
void CZigbeeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static short int strIndex=m_strSysTitle.GetLength();;	
	switch(nIDEvent)
	{
		
	case 0:
		curtime=CTime::GetCurrentTime();
		str=curtime.Format(_T("%H:%M:%S"));
		//CClientDC dc(this);
		//CSize szCurTime=dc.GetTextExtent(str);
		m_StatusBar.SetPaneText(2,str);
		break;
	case 1:
		Beep(1000,500);
		break;
	case 2:
		//标题滚动
		this->SetWindowTextW(m_strSysTitle.Right(strIndex));		
		if(strIndex<=0)
		{
			strIndex=m_strSysTitle.GetLength()+2;
		}
		strIndex-=2;
		break;
	case 3:
		//窗口向上移动退出
		this->GetWindowRect(m_RectDlgScreenRealTime);
		static int topDlg=m_RectDlgScreenRealTime.top;
		this->MoveWindow(m_RectDlgScreenRealTime.left,topDlg,m_RectDlgClient.Width(),m_RectDlgClient.Height(),1);
		topDlg-=20;
		if(topDlg<=-m_RectDlgClient.Height())
		{
			this->SendMessage(WM_CLOSE);
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

HBRUSH CZigbeeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor); 
	// TODO:  在此更改 DC 的任何特性

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_TITLE:
			pDC->SetTextColor(RGB(255,255,0));  //字体颜色
			pDC->SetBkColor(RGB(0, 0, 255));   //字体背景色 
			break;
		case IDC_STATIC_ILLUMINATION://光照静态文本框
			pDC->SetBkMode(TRANSPARENT);
			HBRUSH hbrIllumination;
			if(isBright)
			{
				//pDC->SetBkColor(RGB(128, 255, 255));
				hbrIllumination=CreateSolidBrush(RGB(128,255,255));
			}
			else
			{
				//pDC->SetBkColor(RGB(128, 128, 128));
				hbrIllumination=CreateSolidBrush(RGB(128,128,128));//控件背景色   
			}
			return hbrIllumination;
			break;
		}
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//打开设备管理器
void CZigbeeDlg::OnBnClickedBtnDevmgmt()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecuteW(NULL,_T("open"),_T("devmgmt.msc"),NULL,NULL,SW_SHOW);
}

void CZigbeeDlg::OnBnClickedBtnCommPort()
{
	// TODO: 在此添加控件通知处理程序代码
	CCommPortDlg commportDlg;
	if(commportDlg.DoModal()==IDOK)
	{
		if(m_ctrlComm.get_PortOpen())
		{
			m_ctrlComm.put_PortOpen(false);//关闭串口
		}
		SetCommPort(commportDlg.m_nCommPort,commportDlg.m_nBaudRate);		 
		//状态栏设置
		CString strCommPort,strBaudrate;
		strCommPort.Format(_T("%d"),commportDlg.m_nCommPort);
		strBaudrate.Format(_T("%d"),commportDlg.m_nBaudRate);
		m_StatusBar.SetPaneText(0,_T("串口：COM ")+strCommPort
								 +_T( "     波特率：")+strBaudrate,0);
	}
}


//温度对话框
void CZigbeeDlg::OnBnClickedBtnTemperature()
{
	// TODO: 在此添加控件通知处理程序代码
	CTemperatureDlg* temperatureDlg = new CTemperatureDlg;
	temperatureDlg->Create(IDD_DLG_TEMPERATURE,this);
	temperatureDlg->ShowWindow(SW_SHOW);
}

//湿度对话框
void CZigbeeDlg::OnBnClickedBtnHumidity()
{
	// TODO: 在此添加控件通知处理程序代码
	CHumidityDlg* humidityDlg = new CHumidityDlg;
	humidityDlg->Create(IDD_DLG_HUMIDITY,this);
	humidityDlg->ShowWindow(SW_SHOW);
}

//光照对话框
//void CZigbeeDlg::OnBnClickedBtnIllumination()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CIlluminationDlg* illuminationDlg = new CIlluminationDlg;
//	illuminationDlg->Create(IDD_DLG_ILLUMINATION,this);
//	illuminationDlg->ShowWindow(SW_SHOW);
//}

//二氧化碳对话框
//void CZigbeeDlg::OnBnClickedBtnCarbonDioxide()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CCarbonDioxideDlg* carbonDioxideDlg = new CCarbonDioxideDlg;
//	carbonDioxideDlg->Create(IDD_DLG_CARBON_DIOXIDE,this);
//	carbonDioxideDlg->ShowWindow(SW_SHOW);
//}


void CZigbeeDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	/************************ 获取.exe目录 **************************/
	//CString strAppDir = dirApp;
	ShellExecuteW(NULL,_T("open"),_T("Help.txt"),NULL,NULL,SW_SHOW);
}


void CZigbeeDlg::OnBnClickedBtnSysSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if(IDOK==dlg.DoModal())
	{
		m_color=dlg.m_cc.rgbResult;
		//Sleep(500);
		//this->SendMessage(WM_PAINT);
		this->Invalidate(false);		
	}		
}


void CZigbeeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	/*
	RECT rect;
	GetClientRect(&rect);
	CMenu m_Menu; 
	CWnd *pWnd=AfxGetMainWnd(); 

	if(point.y<=rect.top)
	{
		// *********************** 菜单栏 **************************
		m_Menu.LoadMenuW(IDR_MENU);  
		SetMenu(&m_Menu);  	 
	}
	else
	{
		pWnd->DrawMenuBar(); 
		pWnd->SetMenu(NULL);  
		pWnd->DrawMenuBar(); 
	}
	*/

	CDialogEx::OnMouseMove(nFlags, point);
}


void CZigbeeDlg::OnBnClickedOk()
{
	//按Esc键退出也可退出

	//子对话框关闭父对话框：父对话框指针->SendMessage(WM_CLOSE);

	/*
	（1）点击IDOK按钮退出：先调用OnOK()，然后是OnDestory()，最后是PostNcDestroy() 
	（2）点击IDCANCEL按钮退出：先调用OnCancel()，然后是OnDestory()，最后是PostNcDestroy() 
	（3）点击右上角的关闭按钮退出：先OnClose()，然后是OnCancel()，再然后是OnDestory() ，最后是PostNcDestroy()
	*/

	// TODO: 在此添加控件通知处理程序代码
	if(m_ctrlComm.get_PortOpen())
	{
		m_ctrlComm.put_PortOpen(false);//关闭串口
	}

	SetTimer(3,50,NULL);//窗口移动退出

	//CDialogEx::OnOK();
}


void CZigbeeDlg::OnBnClickedBtnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strDataRX="";
	UpdateData(false);
}


void CZigbeeDlg::SetCommPort(short port, long baudrate)
{
	//*********************** 串口设置 **************************//

	//m_pCtrlComm=(CMSComm *)GetDlgItem(IDC_MSCOMM);

	m_ctrlComm.put_CommPort(port);//选择com口
	m_ctrlComm.put_InputMode(1);//输入方式为二进制方式
	m_ctrlComm.put_InBufferSize(1024);//输入缓冲区大小为1024byte
	m_ctrlComm.put_OutBufferSize(512);//输出缓冲区大小为512byte

	CString strBaudrate;
	strBaudrate.Format(_T("%ld"),baudrate);
	m_ctrlComm.put_Settings(strBaudrate+_T(",n,8,1"));//设置串口参数：9600波特率，无奇偶校验，8个数据位，1个停止位
	
	if(!m_ctrlComm.get_PortOpen())
	{
		/*
		HANDLE m_hCom;        
		CString strCom;  
		strCom.Format(_T("\\\\.\\COM%d"),(int)(m_ctrlComm.get__CommPort()));  
		// 这里的CreateFile函数起了很大的作用，可以用来创建系统设备文件，
		//如果该设备不存在或者被占用，则会返回一个错误，即下面的 INVALID_HANDLE_VALUE ，
		//据此可以判断可使用性。详细参见MSDN中的介绍。  
		m_hCom = CreateFile(strCom, 0, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);  
		if(m_hCom == INVALID_HANDLE_VALUE)//如果没有该设备，或者被其他应用程序在用  
		{  
			int errornum=GetLastError();  
			if(errornum==2)  
				strCom.Format(_T("端口%d 不存在"),(int)(m_ctrlComm.get__CommPort()));  
			else if(errornum==5)  
				strCom.Format(_T("端口%d被占用"),(int)(m_ctrlComm.get__CommPort()));  
			AfxMessageBox(strCom);  
			CloseHandle(m_hCom); // 关闭文件句柄，后面我们采用控件，不用API  
			return ;//这是因为串口初始化封装在另一个函数里面在OnInitDialog调用。  
		}  
		CloseHandle(m_hCom); // 关闭文件句柄，后面我们采用控件，不用API  
		*/
		try
		{
			m_ctrlComm.put_PortOpen(true);//打开串口
		}
		catch(COleDispatchException *e)
		{
			CString strError;
			strError.Format(_T("打开串口失败！\n\nError Number: %d \nError Message: %s"),
				e->m_wCode,e->m_strDescription);
			MessageBoxW(strError,_T("错误提示"),MB_ICONERROR);
			return;
		}
	}
	else
	{
		//MessageBox(_T("Cannot open serial port!"));
	}

	m_ctrlComm.put_OutBufferCount(0);//清空发送缓冲区
	m_ctrlComm.put_InBufferCount(0);//滑空接收缓冲区

	m_ctrlComm.put_RThreshold(11);//每当串口接收缓冲区有RThreshold个字符时将触发一次onComm事件
	m_ctrlComm.put_InputLen(0);//设置当前接收区数据长度为0
	m_ctrlComm.get_Input();//预读缓冲区以清空残留数据

	return;
}

//接受数据消息映射函数
//LRESULT CZigbeeDlg::OnRecvLightDataMessage(WPARAM wParam, LPARAM lParam)
//{
//	CString str;
//	str.Format(_T("%s"),(char*)lParam);
//	CDataTypeConverter DTC;
//	COleVariant dataSend=DTC.HexM2OleVariant(str);
//	m_ctrlComm.put_Output(dataSend);
//	return 0; 
//}

void CZigbeeDlg::OnBnClickedBtnAbout()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}




// CAboutDlg 对话框

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_FontLink.CreatePointFont(90,_T("Arial"),NULL);
	GetDlgItem(IDC_STATIC_HOMEPAGE_LINK)->SetFont(&m_FontLink,true);

	GetDlgItem(IDC_STATIC_HOMEPAGE_LINK)->SetWindowTextW(_T("http://www.cnblogs.com/gaohongchen01/"));

	//GetDlgItem(IDC_STATIC_HOMEPAGE_LINK)->GetWindowRect(&m_HomeLinkRect);//GetClientRect(&m_HomeLinkRect)
	//ScreenToClient(&m_HomeLinkRect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_HOMEPAGE_LINK:
			pDC->SetTextColor(RGB(0,0,255));
			break;
		}
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


//void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	if(point.x>m_HomeLinkRect.left && point.x<m_HomeLinkRect.right && 
//		point.y>m_HomeLinkRect.top && point.y<m_HomeLinkRect.bottom)
//	{
//		SetCursor(LoadCursor(NULL,IDC_HAND));
//	}
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}


BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_hCursor=AfxGetApp()->LoadCursor(IDC_HAND);
	if(pWnd==GetDlgItem(IDC_STATIC_HOMEPAGE_LINK))//文本框IDC_STATIC_HOMEPAGE_LINK的Notify设为true
	{
		SetCursor(LoadCursor(NULL,IDC_HAND));
		return true;//必须加上
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CAboutDlg::OnStnClickedStaticHomepageLink()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, NULL, _T("http://www.cnblogs.com/gaohongchen01/"), NULL, NULL, SW_SHOWNORMAL);
}
