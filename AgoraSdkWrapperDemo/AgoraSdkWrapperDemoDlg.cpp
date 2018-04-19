
// AgoraSdkWrapperDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSdkWrapperDemo.h"
#include "AgoraSdkWrapperDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAgoraSdkWrapperDemoDlg 对话框



CAgoraSdkWrapperDemoDlg::CAgoraSdkWrapperDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgoraSdkWrapperDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgoraSdkWrapperDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHOW1, m_ctlShow1);
	DDX_Control(pDX, IDC_STATIC_SHOW2, m_ctlShow2);
	DDX_Control(pDX, IDC_STATIC_SHOW3, m_ctlShow3);
	DDX_Control(pDX, IDC_STATIC_SHOW4, m_ctlShow4);
}

BEGIN_MESSAGE_MAP(CAgoraSdkWrapperDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAgoraSdkWrapperDemoDlg 消息处理程序

BOOL CAgoraSdkWrapperDemoDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	initCtrl();
	initAgoraSource();
	SetTimer(1, 1000, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAgoraSdkWrapperDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAgoraSdkWrapperDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAgoraSdkWrapperDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

inline void CAgoraSdkWrapperDemoDlg::initCtrl(){

	m_strAppID = "6c5f22f0d668403d8256117e904dbf8b";
	m_strChannelName = "baluoteliz";
	m_uID = 1234;
}

inline void CAgoraSdkWrapperDemoDlg::initAgoraSource(){
	createEngine(m_strAppID.data());
	const char* pszVersion = getSdkVersion();

	setClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER,"");
	setChannelProfile(CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_GAME);
	enableVideo();
	setVideoProfile(40, FALSE);
	startPreviewEx(m_ctlShow1);
}

inline void CAgoraSdkWrapperDemoDlg::unintCtrl(){

	m_strChannelName = "";
	m_strAppID = "";
}

inline void CAgoraSdkWrapperDemoDlg::uninitAgoraSource(){

	stopPreview();
	disableVideo();

	deleteEngine();
}

void CAgoraSdkWrapperDemoDlg::OnTimer(UINT_PTR nIDEvent){

	if (1 == nIDEvent){

		EnterChannel();
		KillTimer(nIDEvent);

		SetTimer(2, 40, nullptr);
	}

	if (2 == nIDEvent){

		char* msg = getMessage();
		OutputDebugStringA( msg);
		freeObject(msg);
	}

}

void CAgoraSdkWrapperDemoDlg::OnClose(){

	KillTimer(1);
	KillTimer(2);

	ExitChannel();
	uninitAgoraSource();
	unintCtrl();

	CDialogEx::OnCancel();
}

inline void CAgoraSdkWrapperDemoDlg::EnterChannel(){

	//joinchannel todo
	enableVideoObserver();

	const char *pszChannlKey = "";
	joinChannel(pszChannlKey, m_strChannelName.data(), "1", m_uID);
}

inline void CAgoraSdkWrapperDemoDlg::ExitChannel(){

	//leavechannel todo
	disableVideoObserver();

	leaveChannel();
}