/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 by W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FieldGoal.h"

#include "FieldGoalDoc.h"
#include "resource.h"
#include "SettingsDialog.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CFieldGoalDoc, CDocument)

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CFieldGoalDoc, CDocument)
	ON_COMMAND( ID_EDIT_SETTINGS, &CFieldGoalDoc::OnEditSettings )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFieldGoalDoc construction/destruction
CFieldGoalDoc::CFieldGoalDoc()
{
	AngleInDegrees = 70;
	Velocity = 20;
	MetersToGoal = 80;
}

/////////////////////////////////////////////////////////////////////////////
CFieldGoalDoc::~CFieldGoalDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL CFieldGoalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CFieldGoalDoc serialization
void CFieldGoalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
} // Serialize

/////////////////////////////////////////////////////////////////////////////
// CFieldGoalDoc diagnostics
#ifdef _DEBUG
void CFieldGoalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFieldGoalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalDoc::OnEditSettings()
{
	// create an instance of the dialog
	CSettingsDialog dlg;

	// setup the dialog parameter
	dlg.Distance = MetersToGoal;
	dlg.Velocity = Velocity;
	dlg.AngleInDegrees = AngleInDegrees;

	// launch the dialog
	INT_PTR ipResponse = dlg.DoModal();

	// if the user canceled, bail out
	if ( ipResponse == IDCANCEL )
	{
		return;
	}

	MetersToGoal = dlg.Distance;
	Velocity = dlg.Velocity;
	AngleInDegrees = dlg.AngleInDegrees;

	CView* pView = View;
	if ( pView != nullptr )
	{
		pView->Invalidate();
	}
} // OnEditSettings

/////////////////////////////////////////////////////////////////////////////
