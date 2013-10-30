// OtchetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Reader.h"
#include "OtchetDlg.h"


// COtchetDlg dialog

IMPLEMENT_DYNAMIC(COtchetDlg, CDialog)
COtchetDlg::COtchetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COtchetDlg::IDD, pParent)
	, m_lByte_Vsego(0)
{
}

COtchetDlg::~COtchetDlg()
{
}

void COtchetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFO, m_strFileName);
	DDX_Text(pDX, IDC_BYTE_VSEGO, m_lByte_Vsego);
	DDX_Text(pDX, IDC_BYTE_READ, m_lByte_Read);
	DDX_Text(pDX, IDC_BYTE_BAD, m_lByte_Bad);
	DDX_Text(pDX, IDC_BYTE_PR_BAD, m_dByte_Pr_Bad);
}


BEGIN_MESSAGE_MAP(COtchetDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// COtchetDlg message handlers
void COtchetDlg::Rach_Pr_Byte_Bad()
{
	// Рассчитать процент плохив байт
	double dPr = m_lByte_Vsego/100.0;
	m_dByte_Pr_Bad = m_lByte_Bad/dPr;
}
void COtchetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
