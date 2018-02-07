
// AgoraSignalingutorialDlg.h : 头文件
//

#pragma once

class CDlgChatMsg;
// CAgoraSignalingutorialDlg 对话框
class CAgoraSignalInstance;
class CSingleCallBack;
class CAgoraSignalingutorialDlg : public CDialogEx
{
// 构造
public:
	CAgoraSignalingutorialDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AGORASIGNALINGUTORIAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


private:
	void initCtrl();
	void uninitCtrl();
	
	void initResource();
	void uninitResource();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();

	LRESULT onLoginSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT onLogout(WPARAM wParam, LPARAM lParam);
	LRESULT onLogFailed(WPARAM wParam, LPARAM lParam);
	LRESULT onError(WPARAM wParam, LPARAM lParam);
	LRESULT onLog(WPARAM wParam, LPARAM lParam);

private:
	std::string m_account;
	CDlgChatMsg* m_pDlgChatMsg;
	bool m_isLogin;

	CAgoraSignalInstance* m_pSignalInstance;
	CSingleCallBack* m_pSignalCallBack;
};
