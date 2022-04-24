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
	SampleTime = 0.1;
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
	CString csAngle, csVelocity, csDistance, csSample;
	if (ar.IsStoring())
	{
		csAngle.Format( _T( "%g\n" ), AngleInDegrees );
		csVelocity.Format( _T( "%g\n" ), Velocity );
		csDistance.Format( _T( "%g\n" ), MetersToGoal );
		csSample.Format( _T( "%g\n" ), SampleTime );

		ar.WriteString( csAngle );
		ar.WriteString( csVelocity );
		ar.WriteString( csDistance );
		ar.WriteString( csSample );
	}
	else
	{
		ar.ReadString( csAngle );
		ar.ReadString( csVelocity );
		ar.ReadString( csDistance );
		ar.ReadString( csSample );

		AngleInDegrees = _tstof( csAngle );
		Velocity = _tstof( csVelocity );
		MetersToGoal = _tstof( csDistance );
		SampleTime = _tstof( csSample );
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
	dlg.SampleTime = SampleTime;

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
	SampleTime = dlg.SampleTime;

	CView* pView = View;
	if ( pView != nullptr )
	{
		pView->Invalidate();
	}
} // OnEditSettings

/////////////////////////////////////////////////////////////////////////////
