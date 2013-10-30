// ReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Reader.h"
#include "ReaderDlg.h"
#include "OtchetDlg.h"
#include ".\readerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReaderDlg dialog



CReaderDlg::CReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReaderDlg::IDD, pParent)
	, m_strFrom(_T(""))
	, m_strTo(_T(""))
	, m_bOtchet(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strFrom);
	DDX_Text(pDX, IDC_EDIT2, m_strTo);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProcess);
	DDX_Check(pDX, IDC_CHECK1, m_bOtchet);
}

BEGIN_MESSAGE_MAP(CReaderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
END_MESSAGE_MAP()


// CReaderDlg message handlers


CString* m_pstrFileTo;			// ��������� ��� ������ (�� ����� ���������� ������)
CString* m_pstrFileFrom;
CProgressCtrl* m_pctrlProcess;	// ��������� �� ������ ��������� �����������

BOOL CReaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// �������������� ��������� ��� ������
	m_pstrFileTo = &m_strTo;
	m_pstrFileFrom = &m_strFrom;
	m_pctrlProcess = &m_ctrlProcess;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReaderDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CReaderDlg::OnBnClickedButton1()
{
	// ��������� ���������� ���� ��� ������ ����� ��� �����������
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_strFrom = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CReaderDlg::OnBnClickedButton2()
{
	// ��������� ���������� ���� ��� ���������� ������������� �����
	CFileDialog dlg(FALSE);

	if (dlg.DoModal() == IDOK)
	{
		m_strTo = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CReaderDlg::OnBnClickedOk()
{
	
}



BOOL bCont;		// ���������� �� ���������� ������
stOtchet stInfo;	// ��������� ��� ������

void CReaderDlg::OnFinishCopy()
{
	// �� ���������� �����������
	// ������������� ������ ������
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	// �������������� ������ ����������
	GetDlgItem(IDC_BUTTON3)->EnableWindow();

	// ������ ������� �������� � 0
	m_ctrlProcess.SetPos(0);

	// ���� ����� ������� �������� �����. ���������� �����
	if (m_bOtchet)
	{
		COtchetDlg dlg;
		dlg.SetFileName(stInfo.strFileName);
		dlg.SetByteVsego(stInfo.lByte_Vsego);
		dlg.SetByteBad(stInfo.lByte_Bad);
		dlg.SetByteRead(stInfo.lByte_Read);
		dlg.Rach_Pr_Byte_Bad();
		dlg.DoModal();
	}
}

BYTE buf[30720];	// ����� ��� �������� ������
long lKol;		// ���������� ���� ������� ���� ���������� (���� ��� �� ��������)
long SafeCopy(CFile* fFileFrom, CFile* fFileTo)
{
	// ������� ��� ����������� ������������� ����� (���������� ���-�� ��������� ����)
	
	int iKolReadByte = 0; // ���������� ����������� ����
	// ������ �� ������������� �����, ���� �� �������� ������ 0
	try 
	{
		iKolReadByte = fFileFrom->Read(&buf, 1024);
		lKol=1024; // ��������������� �������� (������ �����������)
		// ��� ������. ����������� ������� ������� ��������� ����
		stInfo.lByte_Read += iKolReadByte;
	}
	catch (CFileException* e)
	{
		// ����������, ���� �� ������_�� �������� ���� �����
		for (int j=0; j<lKol; j++) buf[j]=0;
		// ������������ �� lKol ���� ������
		fFileFrom->Seek(lKol, CFile::current);	
		iKolReadByte=lKol;

		// ��� ������. ����������� ������� ������ ����
		stInfo.lByte_Bad += lKol;

		// ��������� ���-�� ���� ��� �������� (���� ����� ����� �� �����������)
		if (lKol*3<30000) lKol=lKol*3;

		e->Delete();	// ������� ����������
	}

	// ����� � ����� ����
	fFileTo->Write(&buf, iKolReadByte);

	return iKolReadByte;
}

UINT CopyFiles(LPVOID pParam)
{
	// ����� ��� ����������� ������
	// ��������, ������� ���������� ���� ������
	CFile fFileFrom(*m_pstrFileFrom, CFile::typeBinary|CFile::modeRead);
	CFile fFileTo(*m_pstrFileTo, CFile::typeBinary|CFile::modeCreate|CFile::modeWrite);

	ULONGLONG iLen = fFileFrom.GetLength();
	// ��� ������. ��������� ����� �����
	stInfo.lByte_Vsego = iLen;

	// �������������� ������ ������� �������� (�����������)
	double iProcent=0;	// ������� ��������� ����� �����������
	double iPr = iLen/100.0;	// ������� ���� ���������� 1%
	m_pctrlProcess->SetRange(0, 100);
	
	fFileFrom.SeekToBegin();
	long lShag = 10;

	for (ULONGLONG i = 0; i<iLen; i=i+lShag)
	{
		// ��������� ���������� �� �����������
		if (bCont) 
		{
			lShag = SafeCopy(&fFileFrom, &fFileTo);	
			// ��������� ����� ������� �� ����� ��� ����������
			iProcent = i/iPr;
			// �������� ������ ������� �������� ����������� �����
			m_pctrlProcess->SetPos((int)iProcent);
		}
		else
		{
			// ��������� ����� � ���������� �����
			fFileFrom.Close();
			fFileTo.Close();
			// ������� ����, ������� ���������
			::DeleteFile(*m_pstrFileTo);

			((CReaderDlg*)pParam)->OnFinishCopy();
			bCont = FALSE;
			AfxEndThread(0, TRUE);
			return 0;
		}

	}

	// ��������� ��� �����
	fFileFrom.Close();
	fFileTo.Close();

	((CReaderDlg*)pParam)->OnFinishCopy();
	bCont = FALSE;
	AfxEndThread(0, TRUE);
	return 0;
}

CWinThread* p;		// ��������� �� �����
void CReaderDlg::OnBnClickedButton3()
{
	// �������� ���� �������, ���������� ���� �������� ������

	// ��������� ���� �� ���� ��������� � ��������� (������, ����)
	if (m_strFrom=="") {AfxMessageBox("��� ���� �� ����� (������)."); return;}
	if (m_strTo=="") {AfxMessageBox("��� ���� ��� ���������� ����� (����)"); return;}
	
	// ������ ���� ��� ����������� ����������� = TRUE
	bCont = TRUE;
	// �������� ���������� ��� ������
	stInfo.lByte_Bad = 0;
	stInfo.lByte_Read = 0;
	stInfo.lByte_Vsego = 0;
	stInfo.strFileName = m_strFrom;

	// ��������� ����� ����������� �����
	p = AfxBeginThread(CopyFiles, this);

	// ������������ ������ ������
	GetDlgItem(IDC_BUTTON4)->EnableWindow();
	// ������������� ������ ����������
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
}

void CReaderDlg::OnBnClickedButton4()
{
	// ���������� ����� 
	bCont = FALSE;
	// ����� ���� ����� ������������
	::WaitForSingleObject(p->m_hThread, 1000);
}


void CReaderDlg::OnBnClickedOk2()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CReaderDlg::OnBnClickedCheck1()
{
	UpdateData(TRUE);
}
