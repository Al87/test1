#pragma once


// COtchetDlg dialog

class COtchetDlg : public CDialog
{
	DECLARE_DYNAMIC(COtchetDlg)

public:
	COtchetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COtchetDlg();

public:
	void SetFileName(CString strFileName) {m_strFileName = strFileName;}  // ���������� ��� �������������� �����
	void SetByteVsego(ULONGLONG lVsego) {m_lByte_Vsego = lVsego;}	// ���������� ����� ������ �����
	void SetByteRead(ULONGLONG lRead) {m_lByte_Read = lRead;}		// ���������� ���-�� ������� ����������� ����
	void SetByteBad(ULONGLONG lBad) {m_lByte_Bad = lBad;}	// ���������� ���-�� ������������ ����
	void Rach_Pr_Byte_Bad();	// ���������� ������� ������ ����


// Dialog Data
	enum { IDD = IDD_OTCHET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();

private:
	CString	m_strFileName;		// ��� �������������� �����
	ULONGLONG m_lByte_Vsego;	// ���� � ����� �����
	ULONGLONG m_lByte_Read;		// ���� ������� �����������
	ULONGLONG m_lByte_Bad;		// ������������ ����
	double m_dByte_Pr_Bad;		// ������� ������������ ���� (������)

};
