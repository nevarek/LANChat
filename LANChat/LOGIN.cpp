// LOGIN.cpp : implementation file
//

#include "stdafx.h"
#include "LANChat.h"
#include "LOGIN.h"
#include "afxdialogex.h"


// CLOGIN dialog

IMPLEMENT_DYNAMIC(CLOGIN, CDialogEx)

CLOGIN::CLOGIN(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
	m_loginName = "";
}

CLOGIN::~CLOGIN()
{
}

void CLOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLOGIN, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLOGIN::OnBnClickedOk)
	ON_EN_CHANGE(IDC_LoginInfo, &CLOGIN::OnEnChangeLogininfo)
END_MESSAGE_MAP()


// CLOGIN message handlers


void CLOGIN::OnBnClickedOk()
{
	GetDlgItemText(IDC_LoginInfo, m_loginName);
	CDialogEx::OnOK();
}

void CLOGIN::OnEnChangeLogininfo()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
