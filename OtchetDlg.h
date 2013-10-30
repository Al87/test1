#pragma once


// COtchetDlg dialog

class COtchetDlg : public CDialog
{
	DECLARE_DYNAMIC(COtchetDlg)

public:
	COtchetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COtchetDlg();

public:
	void SetFileName(CString strFileName) {m_strFileName = strFileName;}  // Установить имя скопированного файла
	void SetByteVsego(ULONGLONG lVsego) {m_lByte_Vsego = lVsego;}	// Установить общий размер файла
	void SetByteRead(ULONGLONG lRead) {m_lByte_Read = lRead;}		// Установить кол-во успешно прочитанных байт
	void SetByteBad(ULONGLONG lBad) {m_lByte_Bad = lBad;}	// Установить кол-во поврежденных байт
	void Rach_Pr_Byte_Bad();	// Рассчитать процент плохих байт


// Dialog Data
	enum { IDD = IDD_OTCHET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();

private:
	CString	m_strFileName;		// Имя скопированного файла
	ULONGLONG m_lByte_Vsego;	// Байт в файле всего
	ULONGLONG m_lByte_Read;		// Байт успешно прочитанных
	ULONGLONG m_lByte_Bad;		// Поврежденных байт
	double m_dByte_Pr_Bad;		// Процент поврежденных байт (данных)

};
