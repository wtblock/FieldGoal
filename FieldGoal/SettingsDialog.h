/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 by W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////////////////////////////////////
class CSettingsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingsDialog)

public:
	CSettingsDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSettingsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTINGS };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnOkay();
	afx_msg void OnCancel();

protected:
	double m_dDistance;
	double m_dAngle;
	double m_dVelocity;
	double m_dSampleTime;

public:
	// angle in degrees of the kick
	double GetAngleInDegrees()
	{
		return m_dAngle;
	}
	// angle in degrees of the kick
	void SetAngleInDegrees( double value )
	{
		m_dAngle = value;
	}
	// angle in degrees of the kick
	__declspec( property( get = GetAngleInDegrees, put = SetAngleInDegrees ) )
		double AngleInDegrees;

	// velocity in meters per second
	double GetVelocity()
	{
		return m_dVelocity;
	}
	// velocity in meters per second
	void SetVelocity( double value )
	{
		m_dVelocity = value;
	}
	// velocity in meters per second
	__declspec( property( get = GetVelocity, put = SetVelocity ) )
		double Velocity;

	// distance to goal in meters
	double GetDistance()
	{
		return m_dDistance;
	}
	// distance to goal in meters
	void SetDistance( double value )
	{
		m_dDistance = value;
	}
	// distance to goal in meters
	__declspec( property( get = GetDistance, put = SetDistance ) )
		double Distance;

	// time in seconds between samples
	double GetSampleTime()
	{
		return m_dSampleTime;
	}
	// time in seconds between samples
	void SetSampleTime( double value )
	{
		m_dSampleTime = value;
	}
	// time in seconds between samples
	__declspec( property( get = GetSampleTime, put = SetSampleTime ) )
		double SampleTime;
};
