
// AgoraSignalingutorialDlg.h : ͷ�ļ�
//

#pragma once

class CDlgChatMsg;
// CAgoraSignalingutorialDlg �Ի���
class CAgoraSignalInstance;
class CSingleCallBack;
class CAgoraSignalingutorialDlg : public CDialogEx
{
// ����
public:
	CAgoraSignalingutorialDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AGORASIGNALINGUTORIAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


private:
	void initCtrl();
	void uninitCtrl();
	
	void initResource();
	void uninitResource();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
