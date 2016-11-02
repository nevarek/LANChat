#pragma once


// CLOGIN dialog

class CLOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(CLOGIN)

public:
	CLOGIN(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLOGIN();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CString m_loginName;
public:
	CString GetLoginName() { return m_loginName; }
	afx_msg void OnBnClickedOk();
	void OnEnChangeLogininfo();
};
