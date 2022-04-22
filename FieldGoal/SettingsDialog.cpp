/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 by W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FieldGoal.h"
#include "SettingsDialog.h"
#include "afxdialogex.h"

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSettingsDialog, CDialogEx)

CSettingsDialog::CSettingsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTINGS, pParent)
	, m_dDistance( 0 )
	, m_dAngle( 0 )
	, m_dVelocity( 0 )
{

}

/////////////////////////////////////////////////////////////////////////////
CSettingsDialog::~CSettingsDialog()
{
}

/////////////////////////////////////////////////////////////////////////////
void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text( pDX, IDC_EDIT_DISTANCE, m_dDistance );
	DDV_MinMaxDouble( pDX, m_dDistance, 10, 100 );
	DDX_Text( pDX, IDC_EDIT_ANGLE, m_dAngle );
	DDV_MinMaxDouble( pDX, m_dAngle, 0, 90 );
	DDX_Text( pDX, IDC_EDIT_VELOCITY, m_dVelocity );
}

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSettingsDialog, CDialogEx)
	ON_BN_CLICKED( IDOK, &CSettingsDialog::OnOkay )
	ON_BN_CLICKED( IDCANCEL, &CSettingsDialog::OnCancel )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
BOOL CSettingsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CenterWindow();

	// write the variables to the controls
	UpdateData( FALSE );

	// return TRUE  unless you set the focus to a control
	return TRUE;
} // OnInitDialog

/////////////////////////////////////////////////////////////////////////////
void CSettingsDialog::OnOkay()
{
	// update the data from the controls
	UpdateData();

	// let the application know that the user said to do it
	CDialogEx::OnOK();

} // OnOkay

/////////////////////////////////////////////////////////////////////////////
void CSettingsDialog::OnCancel()
{
	// let the application know the user canceled
	CDialogEx::OnCancel();

} // OnCancel

/////////////////////////////////////////////////////////////////////////////
