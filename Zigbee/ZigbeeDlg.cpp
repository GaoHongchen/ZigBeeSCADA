
// ZigbeeDlg.cpp : ʵ���ļ�
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
	//״̬����ָʾ���б�����δ������ַ�����������Resource View��String Table����Ӷ���
{
	IDS_COMMPORTINFO,
	IDS_NODE_INFO,//ID_INDICATOR_NUM,
	//ID_SEPARATOR,
	IDS_TIMER,
	IDS_AUTHOR
	//ID_INDICATOR_USER,//����Resource View��String Table����Ӷ���
};

CZigbeeDlg* CZigbeeDlg::s_pZDlg=NULL;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CZigbeeDlg �Ի���

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
	, m_strSysTitle(_T("Smartroom SCADA����ѧ������ѵ���ƻ���"))
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
	//ON_MESSAGE(WM_RECVLIGHTDATA_MSG, OnRecvLightDataMessage)//�Զ�����Ϣ
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CZigbeeDlg::OnBnClickedBtnAbout)
END_MESSAGE_MAP()


// CZigbeeDlg ��Ϣ�������

BOOL CZigbeeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	/************************ ��ȡ.exeĿ¼ **************************/
	GetModuleFileNameW(NULL,dirApp,MAX_PATH);
	(_tcsrchr(dirApp,_T('\\')))[1] = 0;//ɾ���ļ�����ֻ���·��

	//��ʼ�����ڱ���
	this->SetWindowTextW(m_strSysTitle);

	//����X�͹رհ�ť
	ASSERT(pSysMenu != NULL);
	//pSysMenu->EnableMenuItem(SC_CLOSE,MF_DISABLED);//ʹ�رհ�ť��Ч
	//VERIFY(pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND));
	pSysMenu->ModifyMenu(SC_CLOSE,MF_BYCOMMAND | MF_GRAYED );//���ùرհ�ť

	/************************ �����ʼ�� **************************/
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

	/************************ ��̬�ı����ʼ�� **************************/
	GetDlgItem(IDC_STATIC_TEMPERATURE)->SetWindowTextW(_T("0 ��"));
	GetDlgItem(IDC_STATIC_HUMIDITY)->SetWindowTextW(_T("0 ��"));
	//��������
	m_FontIllumination.CreatePointFont(300, _T("����"), NULL);  
	GetDlgItem(IDC_STATIC_ILLUMINATION)->SetFont(&m_FontIllumination,true); 

	/************************ ���Ա� **************************/
	//���ѡ�
	m_tab.InsertItem(0,_T("�ƹ����"));  
	m_tab.InsertItem(1,_T("�յ�����"));
	m_tab.InsertItem(2,_T("��������"));
	m_tab.InsertItem(3,_T("�������"));
	m_tab.InsertItem(4,_T("����豸"));
	//�����Ի���,���ҽ�IDC_TAB�ؼ���Ϊ������ 
	m_pageLight.Create(IDD_PROPAGE_CTRL_LIGHT,&m_tab);
	m_pageAircon.Create(IDD_PROPAGE_CTRL_AIRCON,&m_tab);
	m_pageCurtain.Create(IDD_PROPAGE_CTRL_CURTAIN,&m_tab);
	m_pageAlarm.Create(IDD_PROPAGE_CTRL_ALARM,&m_tab);
	m_pageCam.Create(IDD_PROPAGE_CTRL_CAM,&m_tab);
	
	//���IDC_TAB�ͻ�����С 
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	//�����ӶԻ���ߴ粢�ƶ���ָ��λ�� 
	m_pageLight.MoveWindow(&rc);
	m_pageAircon.MoveWindow(&rc);
	m_pageCurtain.MoveWindow(&rc);
	m_pageCam.MoveWindow(&rc);
	m_pageAlarm.MoveWindow(&rc);
	//�ֱ��������غ���ʾ 
	m_pageLight.ShowWindow(true);
	m_pageAircon.ShowWindow(false);
	m_pageCurtain.ShowWindow(false);
	m_pageCam.ShowWindow(false);
	m_pageAlarm.ShowWindow(false);
	//����Ĭ�ϵ�ѡ� 
	m_tab.SetCurSel(0);

	/************************ ״̬�� **************************/
	m_StatusBar.CreateEx(this,SBT_TOOLTIPS,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,AFX_IDW_STATUS_BAR );
	unsigned short int nIndicators=sizeof(indicators)/sizeof(UINT);
	m_StatusBar.SetIndicators(indicators,nIndicators);//����ָʾ������
	CRect rect;
	GetClientRect(&rect);
	m_StatusBar.SetPaneInfo(0,IDS_COMMPORTINFO,SBPS_NORMAL ,rect.Width()/6*2);
	m_StatusBar.SetPaneInfo(1,IDS_NODE_INFO,SBPS_NORMAL,rect.Width()/6*2);
	m_StatusBar.SetPaneInfo(2,IDS_TIMER,SBPS_NORMAL,rect.Width()/6*1);//szCurTime.cx
	m_StatusBar.SetPaneInfo(3,IDS_AUTHOR,SBPS_NORMAL,rect.Width()/6*1);
	//����Ҫ****
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,IDS_COMMPORTINFO);
	//m_StatusBar.GetStatusBarCtrl().SetBkColor(RGB(255,0,0));//���ñ���RGB(180,20,180)
	//״̬��ʱ��
	SetTimer(0,1000,NULL);//ϵͳʱ��

	s_pZDlg=this;

	/************************ ���ڳ�ʼ������״̬����Ϣ��ʾ **************************/
	SetCommPort(1,9600);
	m_StatusBar.SetPaneText(0,_T("���ڣ�COM 1     �����ʣ�9600"),0);

	/************************ ������ʼ�� **************************/
	if(false)
	{
		SetTimer(1,100,NULL);//��������
	}

	SetTimer(2,500,NULL);//�������

	m_color=RGB(121,255,0);//����ɫ

	//GetSystemMetrics(  SM_CXSCREEN  );  //�����Ļ�ķֱ���

	//��ȡ�Ի���Ĵ�С���Ӷ��ı���λ��
	//this->GetClientRect(m_RectDlgClient);
	this->GetWindowRect(m_RectDlgScreen);
	m_RectDlgClient=m_RectDlgScreen;
	ScreenToClient(m_RectDlgClient);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZigbeeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/***************** ���ñ���ɫ *******************/
		CRect rect; 
		CPaintDC dc(this); 
		GetClientRect(rect); 
		dc.FillSolidRect(rect,m_color);

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	// TODO:  �ڴ������ר�õĴ�������

	//�����������
	CenterWindow();  
    CSplashWnd::ShowSplashScreen(this);  
    Sleep(1000);//ʹ�û���ֹͣԼ1s�����������棬ò�ƿ����ö�ʱ��
	
	return 0;
}


void CZigbeeDlg::OnCommMscomm()
{
	// TODO: �ڴ˴������Ϣ����������
	
	CDataTypeConverter DTC;
	//�绰ͼ�������һ��ױ�ȥ���ˣ��һ��绰ͼ����edit control�Ϳ���ȥ��
	if(m_ctrlComm.get_CommEvent()==2)//�¼�ֵΪ2��ʾ�����¼�
	{
		BYTE rxdata[255]={0};//����BYTE����
		VARIANT variant_inp=m_ctrlComm.get_Input();//��������
		COleSafeArray safearray_inp = variant_inp;//VARIANT�ͱ���ת��ΪCOleSafeArray����
		long len=safearray_inp.GetOneDimSize();//�õ���Ч���ݳ���
		for(long k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE����
		m_ctrlComm.put_OutBufferCount(0);//��շ��ͻ�����
		m_ctrlComm.put_InBufferCount(0);//���ս��ջ�����
		safearray_inp.Clear();
			
		for(long k=0;k<len;k++)
		{
			BYTE bt = *(char*)(rxdata+k);//�ַ���
			short int intDec=(int)bt;
			CString strtemp=DTC.Dec2Hex(intDec);
			m_strDataRXTemp+=strtemp;//������ձ༭���Ӧ�ַ���
		}
		m_strDataRX=m_strDataRXTemp;
		m_strDataRXTemp="";

		UpdateData(false);
	}
	
	//��ʪ�ȴ�����
	if(m_strDataRX.Mid(12,4)=="0220")//m_strDataRX.GetAt(13)=='T'
	{
		strTemperatureHumidityRX = m_strDataRX;
		int intTemperatureValue,intHumidityValue;

		//�¶�ֵ
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
		strTemperatureValue += _T(" ��");
		GetDlgItem(IDC_STATIC_TEMPERATURE)->SetWindowTextW(strTemperatureValue);

		//ʪ��ֵstrHumidityValue
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
		strHumidityValue += _T(" ��");
		GetDlgItem(IDC_STATIC_HUMIDITY)->SetWindowTextW(strHumidityValue);
	}

	//����
	if(m_strDataRX.Mid(12,4)=="1110")
	{
		strIlluminationRX = m_strDataRX;
		if(strIlluminationRX.Mid(16,2)=="00")
		{
			GetDlgItem(IDC_STATIC_ILLUMINATION)->SetWindowTextW(_T("����"));
			isBright=true;
		}
		else if(strIlluminationRX.Mid(16,2)=="01")
		{
			GetDlgItem(IDC_STATIC_ILLUMINATION)->SetWindowTextW(_T("�谵"));
			isBright=false;
		}
		//this->Invalidate();
		//::SendMessage(m_hWnd, WM_CTLCOLOR, (WPARAM)(this->GetDC()->GetSafeHdc()), (LPARAM)(m_hWnd));
		GetDlgItem(IDC_STATIC_ILLUMINATION)->Invalidate();
	}

	//���͵磨���⣩
	if(m_strDataRX.Mid(12,4)=="0120")
	{
		strInfraredRX=m_strDataRX;
		if(strInfraredRX.Mid(16,2)=="01")//����
		{
			if(isBright)// && !m_pageLight.isOnManBL
			{
				//�ص�
				m_pageLight.SetLight(m_pageLight.off,m_pageLight.strAddrBL);
				m_pageLight.m_btnBL.SetIcon(IDI_ICON4);
				m_pageLight.m_strLightBL=_T("�������� ����");

			}
			if(!isBright)// && m_pageLight.isOnManBL
			{
				//����
				m_pageLight.SetLight(m_pageLight.on,m_pageLight.strAddrBL);
				m_pageLight.m_btnBL.SetIcon(IDI_ICON3);
				m_pageLight.m_strLightBL=_T("���ղ��� ����");
			}
		}
		else if(strInfraredRX.Mid(16,2)=="00" )//&& !m_pageLight.isOnManBL
		{
			//�ص�
			m_pageLight.SetLight(m_pageLight.off,m_pageLight.strAddrBL);
			m_pageLight.m_btnBL.SetIcon(IDI_ICON4);
			m_pageLight.m_strLightBL=_T("����");
		}
		m_pageLight.UpdateData(false);
	}

	//��
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

	//�������
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

		//ˢ���߼����ظ�ˢ�������棻���ظ�����������
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
					m_pageAlarm.m_strName=_T("�ߺ鳼");
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
					MessageBox(_T("����ˢ����"));
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
			m_pageAlarm.m_strName=_T("¬����");
			num++;
		}

		float rate=((float)num)/30;

		CString strRealNum,strAttendanceRate;

		strRealNum.Format(_T("%d"),num);
		m_pageAlarm.m_strStaticRealNum=strRealNum;

		strAttendanceRate.Format(_T("%.1f %%"),rate*100);		
		m_pageAlarm.m_strAttendanceRate=strAttendanceRate;

		//m_pageAlarm.m_strName=_T("�ߺ鳼");

		m_pageAlarm.UpdateData(false);
	}

	UpdateData(false);
}

void CZigbeeDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(true);//��ȡ�༭������m_strDataTX

	//���͵��ַ����ϱ���Ϊʮ�����Ƹ�ʽ
	CString m_strCtrlLightBL;
	m_strCtrlLightBL=_T("55AA0AAA")+m_pageLight.strAddrBL+_T("10100100");//"55aa0aaa6b4310100000"
	//m_strCtrlLightBL=_T("55AA0AAAB27110100000");

	CDataTypeConverter DTC;
	COleVariant m_OleVariant=DTC.HexM2OleVariant(m_strCtrlLightBL);

	m_ctrlComm.put_Output(m_OleVariant);//��������
}

void CZigbeeDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned short int nTabCurSel=m_tab.GetCurSel();
	switch(nTabCurSel)
	{
	case 0:
		//�ֱ��������غ���ʾ 
		m_pageLight.ShowWindow(true);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(false);
		break;
	case 1:
		//�ֱ��������غ���ʾ 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(true);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(false);
		break;
	case 2:
		//�ֱ��������غ���ʾ 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(true);
		m_pageAlarm.ShowWindow(false);
		m_pageCam.ShowWindow(false);
		break;
	case 3:
		//�ֱ��������غ���ʾ 
		m_pageLight.ShowWindow(false);
		m_pageAircon.ShowWindow(false);
		m_pageCurtain.ShowWindow(false);
		m_pageAlarm.ShowWindow(true);
		m_pageCam.ShowWindow(false);
		break;
	case 4:
		//�ֱ��������غ���ʾ 
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		//�������
		this->SetWindowTextW(m_strSysTitle.Right(strIndex));		
		if(strIndex<=0)
		{
			strIndex=m_strSysTitle.GetLength()+2;
		}
		strIndex-=2;
		break;
	case 3:
		//���������ƶ��˳�
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
	// TODO:  �ڴ˸��� DC ���κ�����

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_TITLE:
			pDC->SetTextColor(RGB(255,255,0));  //������ɫ
			pDC->SetBkColor(RGB(0, 0, 255));   //���屳��ɫ 
			break;
		case IDC_STATIC_ILLUMINATION://���վ�̬�ı���
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
				hbrIllumination=CreateSolidBrush(RGB(128,128,128));//�ؼ�����ɫ   
			}
			return hbrIllumination;
			break;
		}
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//���豸������
void CZigbeeDlg::OnBnClickedBtnDevmgmt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecuteW(NULL,_T("open"),_T("devmgmt.msc"),NULL,NULL,SW_SHOW);
}

void CZigbeeDlg::OnBnClickedBtnCommPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CCommPortDlg commportDlg;
	if(commportDlg.DoModal()==IDOK)
	{
		if(m_ctrlComm.get_PortOpen())
		{
			m_ctrlComm.put_PortOpen(false);//�رմ���
		}
		SetCommPort(commportDlg.m_nCommPort,commportDlg.m_nBaudRate);		 
		//״̬������
		CString strCommPort,strBaudrate;
		strCommPort.Format(_T("%d"),commportDlg.m_nCommPort);
		strBaudrate.Format(_T("%d"),commportDlg.m_nBaudRate);
		m_StatusBar.SetPaneText(0,_T("���ڣ�COM ")+strCommPort
								 +_T( "     �����ʣ�")+strBaudrate,0);
	}
}


//�¶ȶԻ���
void CZigbeeDlg::OnBnClickedBtnTemperature()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTemperatureDlg* temperatureDlg = new CTemperatureDlg;
	temperatureDlg->Create(IDD_DLG_TEMPERATURE,this);
	temperatureDlg->ShowWindow(SW_SHOW);
}

//ʪ�ȶԻ���
void CZigbeeDlg::OnBnClickedBtnHumidity()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CHumidityDlg* humidityDlg = new CHumidityDlg;
	humidityDlg->Create(IDD_DLG_HUMIDITY,this);
	humidityDlg->ShowWindow(SW_SHOW);
}

//���նԻ���
//void CZigbeeDlg::OnBnClickedBtnIllumination()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CIlluminationDlg* illuminationDlg = new CIlluminationDlg;
//	illuminationDlg->Create(IDD_DLG_ILLUMINATION,this);
//	illuminationDlg->ShowWindow(SW_SHOW);
//}

//������̼�Ի���
//void CZigbeeDlg::OnBnClickedBtnCarbonDioxide()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CCarbonDioxideDlg* carbonDioxideDlg = new CCarbonDioxideDlg;
//	carbonDioxideDlg->Create(IDD_DLG_CARBON_DIOXIDE,this);
//	carbonDioxideDlg->ShowWindow(SW_SHOW);
//}


void CZigbeeDlg::OnBnClickedBtnHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/************************ ��ȡ.exeĿ¼ **************************/
	//CString strAppDir = dirApp;
	ShellExecuteW(NULL,_T("open"),_T("Help.txt"),NULL,NULL,SW_SHOW);
}


void CZigbeeDlg::OnBnClickedBtnSysSetting()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	/*
	RECT rect;
	GetClientRect(&rect);
	CMenu m_Menu; 
	CWnd *pWnd=AfxGetMainWnd(); 

	if(point.y<=rect.top)
	{
		// *********************** �˵��� **************************
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
	//��Esc���˳�Ҳ���˳�

	//�ӶԻ���رո��Ի��򣺸��Ի���ָ��->SendMessage(WM_CLOSE);

	/*
	��1�����IDOK��ť�˳����ȵ���OnOK()��Ȼ����OnDestory()�������PostNcDestroy() 
	��2�����IDCANCEL��ť�˳����ȵ���OnCancel()��Ȼ����OnDestory()�������PostNcDestroy() 
	��3��������ϽǵĹرհ�ť�˳�����OnClose()��Ȼ����OnCancel()����Ȼ����OnDestory() �������PostNcDestroy()
	*/

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_ctrlComm.get_PortOpen())
	{
		m_ctrlComm.put_PortOpen(false);//�رմ���
	}

	SetTimer(3,50,NULL);//�����ƶ��˳�

	//CDialogEx::OnOK();
}


void CZigbeeDlg::OnBnClickedBtnClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strDataRX="";
	UpdateData(false);
}


void CZigbeeDlg::SetCommPort(short port, long baudrate)
{
	//*********************** �������� **************************//

	//m_pCtrlComm=(CMSComm *)GetDlgItem(IDC_MSCOMM);

	m_ctrlComm.put_CommPort(port);//ѡ��com��
	m_ctrlComm.put_InputMode(1);//���뷽ʽΪ�����Ʒ�ʽ
	m_ctrlComm.put_InBufferSize(1024);//���뻺������СΪ1024byte
	m_ctrlComm.put_OutBufferSize(512);//�����������СΪ512byte

	CString strBaudrate;
	strBaudrate.Format(_T("%ld"),baudrate);
	m_ctrlComm.put_Settings(strBaudrate+_T(",n,8,1"));//���ô��ڲ�����9600�����ʣ�����żУ�飬8������λ��1��ֹͣλ
	
	if(!m_ctrlComm.get_PortOpen())
	{
		/*
		HANDLE m_hCom;        
		CString strCom;  
		strCom.Format(_T("\\\\.\\COM%d"),(int)(m_ctrlComm.get__CommPort()));  
		// �����CreateFile�������˺ܴ�����ã�������������ϵͳ�豸�ļ���
		//������豸�����ڻ��߱�ռ�ã���᷵��һ�����󣬼������ INVALID_HANDLE_VALUE ��
		//�ݴ˿����жϿ�ʹ���ԡ���ϸ�μ�MSDN�еĽ��ܡ�  
		m_hCom = CreateFile(strCom, 0, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);  
		if(m_hCom == INVALID_HANDLE_VALUE)//���û�и��豸�����߱�����Ӧ�ó�������  
		{  
			int errornum=GetLastError();  
			if(errornum==2)  
				strCom.Format(_T("�˿�%d ������"),(int)(m_ctrlComm.get__CommPort()));  
			else if(errornum==5)  
				strCom.Format(_T("�˿�%d��ռ��"),(int)(m_ctrlComm.get__CommPort()));  
			AfxMessageBox(strCom);  
			CloseHandle(m_hCom); // �ر��ļ�������������ǲ��ÿؼ�������API  
			return ;//������Ϊ���ڳ�ʼ����װ����һ������������OnInitDialog���á�  
		}  
		CloseHandle(m_hCom); // �ر��ļ�������������ǲ��ÿؼ�������API  
		*/
		try
		{
			m_ctrlComm.put_PortOpen(true);//�򿪴���
		}
		catch(COleDispatchException *e)
		{
			CString strError;
			strError.Format(_T("�򿪴���ʧ�ܣ�\n\nError Number: %d \nError Message: %s"),
				e->m_wCode,e->m_strDescription);
			MessageBoxW(strError,_T("������ʾ"),MB_ICONERROR);
			return;
		}
	}
	else
	{
		//MessageBox(_T("Cannot open serial port!"));
	}

	m_ctrlComm.put_OutBufferCount(0);//��շ��ͻ�����
	m_ctrlComm.put_InBufferCount(0);//���ս��ջ�����

	m_ctrlComm.put_RThreshold(11);//ÿ�����ڽ��ջ�������RThreshold���ַ�ʱ������һ��onComm�¼�
	m_ctrlComm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0
	m_ctrlComm.get_Input();//Ԥ������������ղ�������

	return;
}

//����������Ϣӳ�亯��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}




// CAboutDlg �Ի���

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_FontLink.CreatePointFont(90,_T("Arial"),NULL);
	GetDlgItem(IDC_STATIC_HOMEPAGE_LINK)->SetFont(&m_FontLink,true);

	GetDlgItem(IDC_STATIC_HOMEPAGE_LINK)->SetWindowTextW(_T("http://www.cnblogs.com/gaohongchen01/"));

	//GetDlgItem(IDC_STATIC_HOMEPAGE_LINK)->GetWindowRect(&m_HomeLinkRect);//GetClientRect(&m_HomeLinkRect)
	//ScreenToClient(&m_HomeLinkRect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if(nCtlColor==CTLCOLOR_STATIC)
	{
		switch(pWnd->GetDlgCtrlID())
		{
		case IDC_STATIC_HOMEPAGE_LINK:
			pDC->SetTextColor(RGB(0,0,255));
			break;
		}
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


//void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_hCursor=AfxGetApp()->LoadCursor(IDC_HAND);
	if(pWnd==GetDlgItem(IDC_STATIC_HOMEPAGE_LINK))//�ı���IDC_STATIC_HOMEPAGE_LINK��Notify��Ϊtrue
	{
		SetCursor(LoadCursor(NULL,IDC_HAND));
		return true;//�������
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CAboutDlg::OnStnClickedStaticHomepageLink()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, NULL, _T("http://www.cnblogs.com/gaohongchen01/"), NULL, NULL, SW_SHOWNORMAL);
}
