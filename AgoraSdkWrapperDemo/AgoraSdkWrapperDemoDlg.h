
// AgoraSdkWrapperDemoDlg.h : 头文件
//

#pragma once
#include <iostream>
#include <stdint.h>


// CAgoraSdkWrapperDemoDlg 对话框
class CAgoraSdkWrapperDemoDlg : public CDialogEx
{
// 构造
public:
	CAgoraSdkWrapperDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AGORASDKWRAPPERDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


protected:
	inline void initCtrl();
	inline void initAgoraSource();

	inline void unintCtrl();
	inline void uninitAgoraSource();

	inline void EnterChannel();
	inline void ExitChannel();

private:
	CStatic m_ctlShow1;
	CStatic m_ctlShow2;
	CStatic m_ctlShow3;
	CStatic m_ctlShow4;
	
private:
	
	std::string m_strAppID;
	std::string m_strChannelName;
	UINT m_uID;
	uint8_t m_txtId;

	//data
	unsigned char* m_pBuffer;
	int m_nBufferLen;
};
