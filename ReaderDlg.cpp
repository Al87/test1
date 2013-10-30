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


CString* m_pstrFileTo;			// Указатели для потока (не видит переменных класса)
CString* m_pstrFileFrom;
CProgressCtrl* m_pctrlProcess;	// Указатель на полуса прогресса копирования

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

	// Инициализируем указатели для потока
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
	// Открываем диалоговое окно для выбора файла для копирования
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_strFrom = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CReaderDlg::OnBnClickedButton2()
{
	// Открываем диалоговое окно для сохранения поврежденного файла
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



BOOL bCont;		// Продолжать ли выполнения потока
stOtchet stInfo;	// Инормация для отчета

void CReaderDlg::OnFinishCopy()
{
	// По завершении копирования
	// Заблокировать кнопку Отмена
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	// Разблокировать кнопку Копировать
	GetDlgItem(IDC_BUTTON3)->EnableWindow();

	// Полосу статуса процесса в 0
	m_ctrlProcess.SetPos(0);

	// Если стаит галочка Показать отчет. Показываем отчет
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

BYTE buf[30720];	// Буфер для загрузки данных
long lKol;		// Количество байт которые надо пропустить (если они не читаются)
long SafeCopy(CFile* fFileFrom, CFile* fFileTo)
{
	// Функция для копирования поврежденного файла (возвращает кол-во считанных байт)
	
	int iKolReadByte = 0; // Количество прочитанных байт
	// Читаем из поврежденного файла, если не читается ставим 0
	try 
	{
		iKolReadByte = fFileFrom->Read(&buf, 1024);
		lKol=1024; // Восстанавливаем значение (ставим минимальное)
		// Для отчета. Увеличиваем счетчик успешно считанных байт
		stInfo.lByte_Read += iKolReadByte;
	}
	catch (CFileException* e)
	{
		// Исключение, файл не читает_ся заменяем байт нулем
		for (int j=0; j<lKol; j++) buf[j]=0;
		// Перемещаемся на lKol байт вперед
		fFileFrom->Seek(lKol, CFile::current);	
		iKolReadByte=lKol;

		// Для отчета. Увеличиваем счетчик плохих байт
		stInfo.lByte_Bad += lKol;

		// Добавляем кол-во байт для пропуска (если далее опять не прочитаются)
		if (lKol*3<30000) lKol=lKol*3;

		e->Delete();	// Удаляем исключение
	}

	// Пишем в новый файл
	fFileTo->Write(&buf, iKolReadByte);

	return iKolReadByte;
}

UINT CopyFiles(LPVOID pParam)
{
	// Поток для копирования файлов
	// Копируем, заменяя нечетаемые биты нулями
	CFile fFileFrom(*m_pstrFileFrom, CFile::typeBinary|CFile::modeRead);
	CFile fFileTo(*m_pstrFileTo, CFile::typeBinary|CFile::modeCreate|CFile::modeWrite);

	ULONGLONG iLen = fFileFrom.GetLength();
	// Для отчета. Сохраняем длину файла
	stInfo.lByte_Vsego = iLen;

	// Инициализируем полусу статуса процесса (копирования)
	double iProcent=0;	// Сколько процентов файла скопировано
	double iPr = iLen/100.0;	// Сколько байт составляет 1%
	m_pctrlProcess->SetRange(0, 100);
	
	fFileFrom.SeekToBegin();
	long lShag = 10;

	for (ULONGLONG i = 0; i<iLen; i=i+lShag)
	{
		// Проверяем продолжать ли копирование
		if (bCont) 
		{
			lShag = SafeCopy(&fFileFrom, &fFileTo);	
			// Вычисляем какой процент от файла уже скопирован
			iProcent = i/iPr;
			// Обновить полусу статуса процесса копирования файла
			m_pctrlProcess->SetPos((int)iProcent);
		}
		else
		{
			// Закрываем файлы и прекращаем поток
			fFileFrom.Close();
			fFileTo.Close();
			// Удаляем файл, который создавали
			::DeleteFile(*m_pstrFileTo);

			((CReaderDlg*)pParam)->OnFinishCopy();
			bCont = FALSE;
			AfxEndThread(0, TRUE);
			return 0;
		}

	}

	// Закрываем оба файла
	fFileFrom.Close();
	fFileTo.Close();

	((CReaderDlg*)pParam)->OnFinishCopy();
	bCont = FALSE;
	AfxEndThread(0, TRUE);
	return 0;
}

CWinThread* p;		// Указатель на поток
void CReaderDlg::OnBnClickedButton3()
{
	// Копируем файл побитно, нечетаемые биты заменяем нулями

	// Проверяем есть ли пути приемника и источника (Откуда, Куда)
	if (m_strFrom=="") {AfxMessageBox("Нет пути до файла (Откуда)."); return;}
	if (m_strTo=="") {AfxMessageBox("Нет пути для сохранения файла (Куда)"); return;}
	
	// Ставим боол для продолжения копирования = TRUE
	bCont = TRUE;
	// Обнуляем информация для отчета
	stInfo.lByte_Bad = 0;
	stInfo.lByte_Read = 0;
	stInfo.lByte_Vsego = 0;
	stInfo.strFileName = m_strFrom;

	// Запустить поток копирования файла
	p = AfxBeginThread(CopyFiles, this);

	// Активировать кнопку Отмена
	GetDlgItem(IDC_BUTTON4)->EnableWindow();
	// Заблокировать кнопку Копировать
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
}

void CReaderDlg::OnBnClickedButton4()
{
	// Остановить поток 
	bCont = FALSE;
	// Ждать пока поток остановиться
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
