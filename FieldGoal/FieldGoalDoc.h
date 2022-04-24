
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 by W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////////////////////////////////////
class CFieldGoalDoc : public CDocument
{
protected: // create from serialization only
	CFieldGoalDoc();
	DECLARE_DYNCREATE(CFieldGoalDoc)
	double m_dAngle; // angle of the kick in degrees
	double m_dVelocity; // velocity in meters per second
	double m_dMetersToGoal; // distance to goal in meters
	double m_dSampleTime; // time in seconds between samples

// properties
public:
	// PI
	double GetPI()
	{
		return 3.1415926535897932384626433832795;
	}
	// PI
	__declspec( property( get = GetPI ) )
		double PI;

	// degrees from radians
	double GetDegrees( double dRadians )
	{
		return 180.0 / PI * dRadians;
	}
	// degrees from radians
	__declspec( property( get = GetDegrees ) )
		double Degrees[];

	// radians from degrees
	double GetRadians( double dDegrees )
	{
		return PI / 180.0 * dDegrees;
	}
	// radians from degrees
	__declspec( property( get = GetRadians ) )
		double Radians[];

	// logical pixels per inch
	int GetMap()
	{
		return 1000;
	}
	// logical pixels per inch
	__declspec( property( get = GetMap ) )
		int Map;

	// number of pages in the document
	UINT GetPages()
	{
		return 1;
	}
	// number of pages in the document
	__declspec( property( get = GetPages ) )
		UINT Pages;

	// height of document in inches
	double GetHeight()
	{
		return 8.5;
	}
	// height of document in inches
	__declspec( property( get = GetHeight ) )
		double Height;

	// width of document in inches
	double GetWidth()
	{
		return 11.0;
	}
	// width of document in inches
	__declspec( property( get = GetWidth ) )
		double Width;

	// margin of document in inches
	double GetMargin()
	{
		return 1.0;
	}
	// margin of document in inches
	__declspec( property( get = GetMargin ) )
		double Margin;

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
	double GetMetersToGoal()
	{
		return m_dMetersToGoal;
	}
	// distance to goal in meters
	void SetMetersToGoal( double value )
	{
		m_dMetersToGoal = value;
	}
	// distance to goal in meters
	__declspec( property( get = GetMetersToGoal, put = SetMetersToGoal ) )
		double MetersToGoal;

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

	// get a pointer to the view
	CView* GetView()
	{
		POSITION pos = GetFirstViewPosition();
		CView* value = 0;
		while ( value == 0 && pos )
		{
			value = GetNextView( pos );
		}

		return value;
	}
	// get a pointer to the view
	__declspec( property( get = GetView ) )
		CView* View;

	// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CFieldGoalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEditSettings();
};
