
// FieldGoal.h : main header file for the FieldGoal application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFieldGoalApp:
// See FieldGoal.cpp for the implementation of this class
//

class CFieldGoalApp : public CWinAppEx
{
public:
	CFieldGoalApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFieldGoalApp theApp;
