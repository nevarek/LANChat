
// LANChatDlg.h : header file
//

#pragma once
#include <fstream>
using std::ofstream;
using std::ifstream;

// CLANChatDlg dialog
class CLANChatDlg : public CDialogEx
{
// Construction
public:
	CLANChatDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LANCHAT_DIALOG };
#endif

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

	CString m_HISTORY_FILENAME;
	CString m_myName;
	CString m_message;
	CString m_history;
	ofstream m_out_history;
	ifstream m_in_history;

	void WriteToFile(CString filename, CString data);
	void ReadFromFile(CString file);
	void GetLoginName();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedSend();
	afx_msg void OnClose();
};
