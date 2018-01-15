#pragma once


#include <map>
// CDlgChatMsg �Ի���

class CChatDlg;
class CAgoraSignalInstance;
class CSingleCallBack;
class CDlgInput;
class CDlgChatMsg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChatMsg)

public:
	CDlgChatMsg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChatMsg();
	void setCallBack(CSingleCallBack* pCallBack);

// �Ի�������
	enum { IDD = IDD_DIALOG_MsgList };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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

	HRESULT onUpdateInputParam(WPARAM wParam, LPARAM lParam);
	HRESULT onQueryUserStatusResult(WPARAM wParam, LPARAM lParam);
	HRESULT onMessageSendSuccess(WPARAM wParam, LPARAM lParam);
	HRESULT onMessageSendError(WPARAM wParam, LPARAM lParam);
	HRESULT onMessageInstantReceive(WPARAM wParam, LPARAM lParam);
	HRESULT onMessageChannelReceive(WPARAM wParam, LPARAM lParam);

	HRESULT onChannelJoined(WPARAM wParam, LPARAM lParam);
	HRESULT onChannelJoinFailed(WPARAM wParam, LPARAM lParam);
	HRESULT onChannelLeaved(WPARAM wParam, LPARAM lParam);
	HRESULT onChannelUserList(WPARAM wParam,LPARAM lParam);
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

