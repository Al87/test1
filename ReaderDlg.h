// ReaderDlg.h : header file
//

#pragma once
#include "afxcmn.h"

struct stOtchet			// ��������� ��� �������� ���������� ��� ������
{
	CString strFileName;		// ��� �������������� �����
	ULONGLONG lByte_Vsego;		// ������ ����� � ������
	ULONGLONG lByte_Read;		// ���� ����������
	ULONGLONG lByte_Bad;		// ������ ����
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
	CString m_strFrom;				// �������� ����� (���� + ����)
	CString m_strTo;				// �������� ����� (���� + ����)
	CProgressCtrl m_ctrlProcess;	// �������� �������� �����������
	BOOL m_bOtchet;				// ���������� �� ����� ����� ����������� �����

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	void OnFinishCopy();		// �� ���������� ����������� 
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCheck1();
};
