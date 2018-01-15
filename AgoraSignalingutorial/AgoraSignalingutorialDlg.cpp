
// AgoraSignalingutorialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraSignalingutorial.h"
#include "AgoraSignalingutorialDlg.h"
#include "afxdialogex.h"
#include "DlgChatMsg.h"
#include "commonFun.h"
#include "SignalInstance.h"
#include "SingleWrap.h"

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


// CAgoraSignalingutorialDlg 对话框



CAgoraSignalingutorialDlg::CAgoraSignalingutorialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgoraSignalingutorialDlg::IDD, pParent),
	m_pDlgChatMsg(nullptr),
	m_isLogin(FALSE),
	m_pSignalInstance(NULL),
	m_pSignalCallBack(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgoraSignalingutorialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAgoraSignalingutorialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LoginPt, &CAgoraSignalingutorialDlg::OnBnClickedButtonLogin)
	ON_MESSAGE(WM_LoginSuccess,onLoginSuccess)
	ON_MESSAGE(WM_LogOut,onLogout)
	ON_MESSAGE(WM_LoginFailed,onLogFailed)
	ON_MESSAGE(WM_Error,onError)
	ON_MESSAGE(WM_Log,onLog)
END_MESSAGE_MAP()


// CAgoraSignalingutorialDlg 消息处理程序

BOOL CAgoraSignalingutorialDlg::OnInitDialog()
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
	initResource();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAgoraSignalingutorialDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAgoraSignalingutorialDlg::OnPaint()
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

void CAgoraSignalingutorialDlg::OnClose()
{
	uninitResource();
	uninitCtrl();

	CDialogEx::OnCancel();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAgoraSignalingutorialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAgoraSignalingutorialDlg::OnBnClickedButtonLogin()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strAccount;
	GetDlgItem(IDC_EDIT_Login_Account)->GetWindowTextW(strAccount);
	if (_T("") == strAccount){
		AfxMessageBox(_T("Account 不能为空.请重新输入.."));
		return;
	}
	else if (isContailSpace(strAccount)){
		AfxMessageBox(_T("Account 不能包含空字符.请重新输入.."));
		return;
	}

	m_account = cs2s(strAccount);
	std::string appId = m_pSignalInstance->getAppId();
	std::string appCertificateId = m_pSignalInstance->getCertificateId();

	time_t ltime;
	time(&ltime);
	int expiredSecond = ltime + 3600;
	std::string channelKey = "_no_need_token";
	m_pSignalInstance->setChannelKey(channelKey);
	m_pSignalInstance->Login(m_account);
}

void CAgoraSignalingutorialDlg::initCtrl()
{

}

void CAgoraSignalingutorialDlg::uninitCtrl()
{
	if (m_pDlgChatMsg){
		delete m_pDlgChatMsg;
		m_pDlgChatMsg = NULL;
	}
}

void CAgoraSignalingutorialDlg::initResource()
{
	std::string AppId = gConfigSignal.getAppID();
	if ("" == AppId)
	{
		gConfigSignal.setAppID("");
		std::string ConfigPath = gConfigSignal.getFilePath();
		ShellExecute(NULL, _T("open"), s2cs(ConfigPath), NULL, NULL, SW_SHOW);
		AfxMessageBox(_T("APPID 不能为空,请修改AgoraSignal.ini配置项中的AppID 和 AppCertificatedId"));
		PostQuitMessage(0);
		return;
	}

	m_pSignalInstance = CAgoraSignalInstance::getSignalInstance(AppId);
	ASSERT(m_pSignalInstance);
	std::string appCertificateID = gConfigSignal.getAppCertificatedId();
	m_pSignalInstance->setAppCertificateId(appCertificateID);
	
	m_pSignalInstance->setLoginWnd(m_hWnd);
	m_pSignalCallBack = new CSingleCallBack(m_hWnd);
	m_pSignalInstance->getAgoraAPI()->callbackSet(m_pSignalCallBack);

	std::string sdkVersion = m_pSignalInstance->getSDKVersion();
	GetDlgItem(IDC_STATIC_SDKVERSION)->SetWindowTextW(s2cs(sdkVersion));
}

void CAgoraSignalingutorialDlg::uninitResource()
{
	if (m_pSignalCallBack){
		m_pSignalInstance->getAgoraAPI()->callbackSet(nullptr);
		delete m_pSignalCallBack;
		m_pSignalCallBack = NULL;
	}

	if (m_pSignalInstance){
		m_pSignalInstance->ReleaseInstance();
		m_pSignalInstance = nullptr;
	}
}

HRESULT CAgoraSignalingutorialDlg::onLoginSuccess(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGINSUCCESS lpData = (PAG_SIGNAL_LOGINSUCCESS)wParam;
	char logDesc[MAXPATHLEN] = { '\0' };
	sprintf_s(logDesc, "onLoginSuccess(%u,%u)", lpData->uid, lpData->fd);
	LOG_MSG(logDesc, LogType_CallBack);

	delete lpData; lpData = nullptr;

	m_pSignalInstance->setptStatus(true);

	if (NULL == m_pDlgChatMsg)
	{
		m_pDlgChatMsg = new CDlgChatMsg;
		m_pDlgChatMsg->Create(CDlgChatMsg::IDD);
		m_pDlgChatMsg->setCallBack(m_pSignalCallBack);
		m_pDlgChatMsg->CenterWindow();
		m_pDlgChatMsg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pDlgChatMsg->CenterWindow();
		m_pDlgChatMsg->ShowWindow(SW_SHOW);
	}

	return true;
}

HRESULT CAgoraSignalingutorialDlg::onLogout(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGOUT lpData = (PAG_SIGNAL_LOGOUT)wParam;
	char logDesc[MAXPATHLEN] = { '\0' };
	sprintf_s(logDesc, "onLogout(%d)", lpData->ecode);
	LOG_MSG(logDesc, LogType_CallBack);
	
	delete lpData; lpData = NULL;
	if (m_pDlgChatMsg){
		delete m_pDlgChatMsg;
		m_pDlgChatMsg = nullptr;
	}

	return TRUE;
}


HRESULT CAgoraSignalingutorialDlg::onLogFailed(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOGINFAILED lpData = (PAG_SIGNAL_LOGINFAILED)wParam;
	char logDesc[MAXPATHLEN] = { '\0' };
	sprintf_s(logDesc, "onLogFailed(%d)", lpData->ecode);
	LOG_MSG(logDesc, LogType_CallBack);

	delete lpData; lpData = nullptr;
	return TRUE;
}


LRESULT CAgoraSignalingutorialDlg::onError(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_ERROR lpData = (PAG_SIGNAL_ERROR)wParam;
	char logDesc[MAXPATHLEN] = { '\0' };
	sprintf_s(logDesc, "onError(%s,%u,%d,%s,%u)", lpData->name.data(), lpData->name.size(),lpData->ecode,lpData->desc.data(),lpData->desc.size());
	LOG_MSG(logDesc, LogType_SDK_Error);
	
	delete lpData; lpData = nullptr;
	return TRUE;
}

LRESULT CAgoraSignalingutorialDlg::onLog(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_LOG lpData = (PAG_SIGNAL_LOG)wParam;
	char logDesc[MAXPATHLEN] = { '\0' };
	sprintf_s(logDesc, "onLog(%s,%u)", lpData->txt.data(),lpData->txt.size());
	LOG_MSG(logDesc, LogType_SDK_LOG);

	delete lpData; lpData = nullptr;
	return TRUE;
}

BOOL CAgoraSignalingutorialDlg::PreTranslateMessage(MSG* pMsg)
{
	if (VK_RETURN == pMsg->wParam && WM_KEYDOWN == pMsg->message){
		
		if (GetFocus() == GetDlgItem(IDC_EDIT_Login_Account)){
			OnBnClickedButtonLogin();
		}
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}