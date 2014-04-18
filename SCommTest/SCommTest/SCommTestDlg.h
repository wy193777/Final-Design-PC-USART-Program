
// SCommTestDlg.h : header file
//

#pragma once
#include "cmscomm.h"


// CSCommTestDlg dialog
class CSCommTestDlg : public CDialogEx
{
// Construction
public:
	CSCommTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SCOMMTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonSend();
	CString m_strRecvData;
	CString m_strSendData;
	CMSComm m_cComm;
	afx_msg void OnMscomm1();
	afx_msg void OnBnClickedButton1();
	BYTE m_Degree;  //send str, change to number in MCU
	BYTE m_Time;
	afx_msg void OnBnClickedButtonSendconfig();
};
