// ReaderDlg.h : header file
//

#pragma once
#include "afxcmn.h"

struct stOtchet			// Структура для хранения информации для отчета
{
	CString strFileName;		// Имя скопированного файла
	ULONGLONG lByte_Vsego;		// Размер файла в байтах
	ULONGLONG lByte_Read;		// Байт прочитанно
	ULONGLONG lByte_Bad;		// Плохих байт
};

// CReaderDlg dialog
class CReaderDlg : public CDialog
{
// Construction
public:
	CReaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_READER_DIALOG };

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
private:
	CString m_strFrom;				// Источник файла (путь + файл)
	CString m_strTo;				// Приемник файла (путь + файл)
	CProgressCtrl m_ctrlProcess;	// Идикатор процесса копирования
	BOOL m_bOtchet;				// Показывать ли отчет после копирования файла

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	void OnFinishCopy();		// По завершении копирования 
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCheck1();
};
