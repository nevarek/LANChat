// 
// LANChatDlg.cpp : implementation file
//
// TODO: 
// - history file w/ mutex protection
// - user implementation
// - socket integration

#include "stdafx.h"
#include "LANChat.h"
#include "LANChatDlg.h"
#include "afxdialogex.h"
#include "LOGIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLANChatDlg dialog

CLANChatDlg::CLANChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LANCHAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLANChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLANChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLANChatDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDCANCEL, &CLANChatDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_EXIT, &CLANChatDlg::OnBnClickedExit)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLANChatDlg message handlers

BOOL CLANChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// void SetWindowTitle(m_myName)
	// create a login window, the window asks for user name
	// when the user clicks OK, the username is stored in the login dialog
	// After that, the main window retrieves the login name by calling
	GetLoginName();
	m_HISTORY_FILENAME = "messagehistory.txt";

	
/* CREATES A NEW POINTER, MEMORY LEAK HERE UNTIL IT'S DELETED
	CLOGIN* pLogin2 = new CLOGIN();
	pLogin2->Create(IDD_LOGIN);
	pLogin2->ShowWindow(SW_SHOW);
*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLANChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLANChatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLANChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLANChatDlg::OnBnClickedSend()
{
	// send a message
	GetDlgItemText(IDC_MessageSendBox, m_message); // save message
	SetDlgItemText(IDC_MessageSendBox, CString("")); // empty message box
	if (m_message != "") // do nothing on empty text
	{
		// newline charater is \r\n
		m_message += CString("\r\n");
		m_history += CString("[") + m_myName + CString("]: ") + m_message;
		SetDlgItemText(IDC_MessageHistory, m_history);
		WriteToFile(m_HISTORY_FILENAME, m_history);
	}
	GotoDlgCtrl(GetDlgItem(IDC_MessageSendBox)); // reset focus back to mesasge send
}

void CLANChatDlg::GetLoginName()
{
	CLOGIN login;
	if (login.DoModal() == IDOK) // create dialog box
	{
		m_myName = login.GetLoginName();
	}
	SetWindowText(CString("User: ") + m_myName);
}

void CLANChatDlg::WriteToFile(CString filename, CString write_data)
{
	// Note: I had trouble with Unicode being able to only write one character to the file.
	//			To fix this, I had to change Project > Project Settings > Character Set to
	//			'Use Multi-Byte Character Set'.
	ofstream file;
	file.open(filename,std::ios::app);
	if (file.fail())
	{
		AfxMessageBox("Failure in opening history file.");
		return;
	}
	file << (LPCSTR)write_data.GetString();
	file.close();
}

void CLANChatDlg::ReadFromFile(CString filename)
{
	std::string some_data;
	CString history_data;
	ifstream file;
	file.open(filename);
	if (file.fail())
	{
		AfxMessageBox("Failure in opening history file.");
		return;
	}
	//file.getline(history_data);
}

void CLANChatDlg::OnBnClickedOk()
{
	// Disabled Enter key from exiting program
}

// Make sure this doesn't close the window with esc
void CLANChatDlg::OnBnClickedCancel()
{
	// Disabled Escape key from exiting program
}

void CLANChatDlg::OnBnClickedExit()
{
	// Exits when user hits Exit button
	CDialogEx::OnCancel();
}

void CLANChatDlg::OnClose()
{
	// Exits when user clicks 'x' button
	CDialogEx::OnCancel();
}
