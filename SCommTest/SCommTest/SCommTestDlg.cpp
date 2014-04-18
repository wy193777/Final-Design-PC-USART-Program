
// SCommTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SCommTest.h"
#include "SCommTestDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnComm();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(IDC_MSCOMM1, &CAboutDlg::OnComm)
END_MESSAGE_MAP()


// CSCommTestDlg dialog




CSCommTestDlg::CSCommTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSCommTestDlg::IDD, pParent)
	, m_strRecvData(_T(""))
	, m_strSendData(_T(""))
	//, m_Degree(_T(""))
	//, m_Time(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Degree = 0;
	m_Time = 0;
}

void CSCommTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSendData);
	DDX_Control(pDX, IDC_MSCOMM1, m_cComm);
	DDX_Text(pDX, IDC_EDIT_DEGREE, m_Degree);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Time);
}

BEGIN_MESSAGE_MAP(CSCommTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_SEND, &CSCommTestDlg::OnClickedButtonSend)
	ON_COMMAND(IDC_MSCOMM1, &CSCommTestDlg::OnMscomm1)
	ON_BN_CLICKED(IDC_BUTTON_SENDCONFIG, &CSCommTestDlg::OnBnClickedButtonSendconfig)
END_MESSAGE_MAP()


// CSCommTestDlg message handlers

BOOL CSCommTestDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	//添加的对串口的初始化语句 
	if(m_cComm.get_PortOpen()) //如果发现串口本来是打开的，则关闭串口 
	{
		m_cComm.put_PortOpen(FALSE);
	}
	m_cComm.put_CommPort(3); //选择COM1端口 
	m_cComm.put_InputMode(1);//输入方式为二进制方式 
	m_cComm.put_InBufferSize(1024);//设置输入缓冲区 
	m_cComm.put_OutBufferSize(512); //设置输出缓冲区 
	m_cComm.put_Settings(TEXT("9600,n,8,1"));//波特率9600，无校验，8个数据位，1个停止位 
	m_cComm.put_Settings(_T("9600,n,8,1"));
	if(!m_cComm.get_PortOpen())
	{
		m_cComm.put_PortOpen(TRUE); //打开串口 
		m_cComm.put_RThreshold(1); //每当接收缓冲区有1个字符则接收串口数据 
		m_cComm.put_InputLen(0); //设置当前缓冲区长度为0 
		m_cComm.get_Input(); //预读缓冲区以清除残留数据 
	}
	else	
	{
		AfxMessageBox(TEXT("打开端口失败!"),MB_ICONSTOP,0);
	}
	//AfxMessageBox(_T("打开端口失败!"),MB_ICONSTOP,0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSCommTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSCommTestDlg::OnPaint()
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
HCURSOR CSCommTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSCommTestDlg::OnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(true); //读取编辑框内容  
	m_cComm.put_Output(COleVariant(m_strSendData));//发送数据 
	//m_strSendData.Empty(); //发送后清空输入框 
	UpdateData(false); //更新编辑框内容  //对发送的数据进行强制类型转换，由CString 字符串数据转换为VARIANT 类型。
}
void CAboutDlg::OnComm()
{

}

void CSCommTestDlg::OnMscomm1()
{
	// TODO: Add your command handler code here
	//从串口接收数据并显示在编辑框中 
	VARIANT variant_inp; 
	COleSafeArray safearray_inp; 
	long len,k; 
	byte rxdata[512]; //设置BYTE数组 
	CString strtemp;  
	if(m_cComm.get_CommEvent()==2) //值为2表示接收缓冲区内有字符 
	{ 
		variant_inp=m_cComm.get_Input(); //读缓冲区消息 
		safearray_inp=variant_inp; ///变量转换  
		len=safearray_inp.GetOneDimSize(); //得到有效的数据长度 
		for(k=0;k<len;k++)  
			safearray_inp.GetElement(&k,rxdata+k);  
		for(k=0;k<len;k++) //将数组转换为CString型变量 
		{  
			char bt=*(char*)(rxdata+k); //字符型  
			strtemp.Format(TEXT("%c"),bt); //将字符送入临时变量strtemp存放 
			//strtemp.Format(_T("%c"),bt);   
			m_strRecvData+=strtemp; //加入接收编辑框对应字符串 
		} 
	}  
	CString temp=(TEXT("\r\n")); //显示完成后要自动换行 
	m_strRecvData+=temp; 
	//UpdateData(FALSE); //更新编辑框内容
	//UpdateData(TRUE);
}


void CSCommTestDlg::OnBnClickedButtonSendconfig()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// for some unknown reasons, it could only transmit right number from
	// 0-128, if the number are larger, this couldn't transmit properly.
	BYTE x[4];
	x[0] = 'D';
	x[1] = m_Degree;
	x[2] = 'T';
	x[3] = m_Time;
	CString result((LPCSTR) &x, sizeof(x));  
	m_cComm.put_Output(COleVariant(result));


	/* This block of code always transmit wrong number to MCU
	//BYTE test = 5;
	BYTE *degree;
	BYTE *time;
	degree = &m_Degree;
	time = &m_Time;
	CString sdegree((char)degree);
	CString stime((char)time);
	CString result = _T("D") + sdegree + _T("T") + stime;
	m_cComm.put_Output(COleVariant(result));
	//m_cComm.put_Output(COleVariant(test));  //invalid property value!!
	*/


	/* This block of code always transmit wrong number to MCU
	m_cComm.put_Output(COleVariant(CString("D")));
	m_cComm.put_Output(COleVariant(sdegree));
	//m_cComm.put_Output(COleVariant(CString sStr((char)degree)));
	m_cComm.put_Output(COleVariant(CString("T")));
	m_cComm.put_Output(COleVariant(stime));
	//m_cComm.put_Output(COleVariant(CString((char)time)));*/
}
