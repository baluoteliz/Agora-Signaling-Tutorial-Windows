#pragma once


#include <map>
// CDlgChatMsg 对话框

class CChatDlg;
class CAgoraSignalInstance;
class CSingleCallBack;
class CDlgInput;
class CDlgChatMsg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChatMsg)

public:
	CDlgChatMsg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChatMsg();
	void setCallBack(CSingleCallBack* pCallBack);

// 对话框数据
	enum { IDD = IDD_DIALOG_MsgList };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); 


	DECLARE_MESSAGE_MAP()

private:
	void initCtrl();
	void uninitCtrl();

	void initResource();
	void uninitResource();

	void chooseInstance(const std::string &userAccount);
	void chooseChannel(const std::string &channelName);
	void showChannelInfo(const std::string &channelName);
	
public:
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonP2pmsg();
	afx_msg void OnBnClickedButtonChannelmsg();

	LRESULT onUpdateInputParam(WPARAM wParam, LPARAM lParam);
	LRESULT onQueryUserStatusResult(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageSendSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageSendError(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageInstantReceive(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageChannelReceive(WPARAM wParam, LPARAM lParam);

	LRESULT onChannelJoined(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelJoinFailed(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelLeaved(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelUserList(WPARAM wParam,LPARAM lParam);
	LRESULT onChannelQueryUserNumResult(WPARAM wParam, LPARAM lParam);


private:
	std::map<std::string, CChatDlg* > m_mapChatP2P;
	std::map<std::string, CChatDlg*> m_mapChatChannel;
	CChatDlg* m_pCurChat;
	std::string m_curAccount;
	std::string m_curChannel;
	CAgoraSignalInstance *m_pSignalInstance;
	CSingleCallBack *m_pSignalCallBack;
	CDlgInput* m_pDlgInput;
	eTagMsgtype m_curOptionType;
};

