
// AgoraSdkWrapperDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AgoraSdkWrapperDemo.h"
#include "AgoraSdkWrapperDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CAgoraSdkWrapperDemoDlg �Ի���



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


// CAgoraSdkWrapperDemoDlg ��Ϣ�������

BOOL CAgoraSdkWrapperDemoDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	initCtrl();
	initAgoraSource();
	SetTimer(1, 1000, nullptr);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAgoraSdkWrapperDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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