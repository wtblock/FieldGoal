
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 by W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
class CFieldGoalView : public CScrollView
{
protected: 
	CSize m_sizeClient;	// physical size of client area
	double m_dTop; // top of view in inches

	int m_nPhysicalPageWidth;
	int m_nPhysicalPageHeight;
	int m_nLogicalPageWidth;
	int m_nLogicalPageHeight;
	bool m_bInitialUpdate;
	int m_nNumPages;

	// Attributes
public:
	CFieldGoalDoc* GetDocument() const;
	__declspec( property( get = GetDocument ) )
		CFieldGoalDoc* Document;

	// properties
public:
	// logical pixels per inch
	int GetMap()
	{
		CFieldGoalDoc* pDoc = Document;
		const int value = pDoc->Map;
	}
	// logical pixels per inch
	__declspec( property( get = GetMap ) )
		int Map;

	// height of the document in inches
	double GetDocumentHeight()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->Height;
		return value;
	}
	// height of document in inches
	__declspec( property( get = GetDocumentHeight ) )
		double DocumentHeight;

	// width of the document in inches
	double GetDocumentWidth()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->Width;
		return value;
	}
	// width of the document in inches
	__declspec( property( get = GetDocumentWidth ) )
		double DocumentWidth;

	// margin of the document in inches
	double GetDocumentMargin()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->Margin;
		return value;
	}
	// margin of the document in inches
	__declspec( property( get = GetDocumentMargin ) )
		double DocumentMargin;

	// height of the document in logical pixels
	int GetLogicalDocumentHeight()
	{
		const int value = InchesToLogical( DocumentHeight );
		return value;
	}
	// height of the document in logical pixels
	__declspec( property( get = GetLogicalDocumentHeight ) )
		int LogicalDocumentHeight;

	// width of the document in logical pixels
	int GetLogicalDocumentWidth()
	{
		const int value = InchesToLogical( DocumentWidth );
		return value;
	}
	// width of the document in logical pixels
	__declspec( property( get = GetLogicalDocumentWidth ) )
		int LogicalDocumentWidth;

	// margin of the document in logical pixels
	int GetLogicalDocumentMargin()
	{
		const int value = InchesToLogical( DocumentMargin );
		return value;
	}
	// margin of the document in logical pixels
	__declspec( property( get = GetLogicalDocumentMargin ) )
		int LogicalDocumentMargin;

	// get height of the view in inches
	double GetVisibleHeight()
	{
		CClientDC dc( this );
		SetDrawDC( &dc );
		CSize sizeLogical = m_sizeClient;
		dc.DPtoLP( &sizeLogical );
		const double value = LogicalToInches( sizeLogical.cy );
		return value;
	}
	// get height of the view in inches
	__declspec( property( get = GetVisibleHeight ) )
		double VisibleHeight;

	// get line height in inches
	double GetLineHeight()
	{
		return 0.25;
	}
	// get line height in inches
	__declspec( property( get = GetLineHeight ) )
		double LineHeight;

	// get last viewable position in inches accounting for view height
	double GetLast()
	{
		double value = DocumentHeight - VisibleHeight;
		if ( value < 0 )
		{
			value = 0;
		}
		return value;
	}
	// get last viewable position in inches accounting for view height
	__declspec( property( get = GetLast ) )
		double Last;

	// get page height in inches
	double GetPageHeight()
	{
		const double value = VisibleHeight / 2;
		return value;
	}
	// get page height in inches
	__declspec( property( get = GetPageHeight ) )
		double PageHeight;

	// number of scrolling lines
	int GetScrollLines()
	{
		const double dLines = Last / LineHeight;
		int value = int( dLines );
		if ( !NearlyEqual( double( value ), dLines ))
		{
			value++;
		}
		return value;
	}
	// number of scrolling lines
	__declspec( property( get = GetScrollLines ) )
		int ScrollLines;

	// top of view in inches
	double GetTopOfView()
	{
		return m_dTop;
	}
	// top of view in inches
	void SetTopOfView( double value )
	{
		m_dTop = value;
	}
	// top of view in inches
	__declspec( property( get = GetTopOfView, put = SetTopOfView ) )
		double TopOfView;

	// get bottom of view in inches
	double GetBottomOfView()
	{
		return m_dTop + VisibleHeight;
	}
	// get bottom of view in inches
	__declspec( property( get = GetBottomOfView ) )
		double BottomOfView;

	// angle in degrees of the kick
	double GetAngleInDegrees()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->AngleInDegrees;
		return value;
	}
	// angle in degrees of the kick
	void SetAngleInDegrees( double value )
	{
		CFieldGoalDoc* pDoc = Document;
		pDoc->AngleInDegrees = value;
	}
	// angle in degrees of the kick
	__declspec( property( get = GetAngleInDegrees, put = SetAngleInDegrees ) )
		double AngleInDegrees;

	// velocity in meters per second
	double GetVelocity()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->Velocity;
		return value;
	}
	// velocity in meters per second
	void SetVelocity( double value )
	{
		Document->Velocity = value;
	}
	// velocity in meters per second
	__declspec( property( get = GetVelocity, put = SetVelocity ) )
		double Velocity;

	// Height of goal in meters
	double GetGoalHeight()
	{
		return 3.0;
	}
	// Height of goal in meters
	__declspec( property( get = GetGoalHeight ) )
		double GoalHeight;

	// horizontal velocity in meters per second
	double GetHorizontalVelocity()
	{
		const double dRadians = AngleInRadians;
		const double dVelocity = Velocity;
		const double dSine = sin( dRadians );
		const double value = dVelocity * dSine;
		return value;
	}
	// horizontal velocity in meters per second
	__declspec( property( get = GetHorizontalVelocity ) )
		double HorizontalVelocity;

	// vertical velocity in meters per second
	double GetVerticalVelocity()
	{
		const double dRadians = AngleInRadians;
		const double dVelocity = Velocity;
		const double dCosine = cos( dRadians );
		const double value = dVelocity * dCosine;
		return value;
	}
	// vertical velocity in meters per second
	__declspec( property( get = GetVerticalVelocity ) )
		double VerticalVelocity;

	// angle in radians of the kick
	double GetAngleInRadians()
	{
		const double dAngleInDegrees = 90 - AngleInDegrees;
		const double dAngle = dAngleInDegrees;
		const double value = Radians( dAngle );
		return value;
	}
	// angle in radians of the kick
	__declspec( property( get = GetAngleInRadians ) )
		double AngleInRadians;

	// distance to goal in meters
	double GetMetersToGoal()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->MetersToGoal;
		return value;
	}
	// distance to goal in meters
	void SetMetersToGoal( double value )
	{
		CFieldGoalDoc* pDoc = Document;
		pDoc->MetersToGoal = value;
	}
	// distance to goal in meters
	__declspec( property( get = GetMetersToGoal, put = SetMetersToGoal ) )
		double MetersToGoal;

	// time in seconds between samples
	double GetSampleTime()
	{
		CFieldGoalDoc* pDoc = Document;
		const double value = pDoc->SampleTime;
		return value;
	}
	// time in seconds between samples
	void SetSampleTime( double value )
	{
		CFieldGoalDoc* pDoc = Document;
		pDoc->SampleTime = value;
	}
	// time in seconds between samples
	__declspec( property( get = GetSampleTime, put = SetSampleTime ) )
		double SampleTime;

	// meters per inch scale
	double GetMetersPerInch()
	{
		const double dMeters = MetersToGoal;
		const double dMargin = DocumentMargin;
		const double dInches = DocumentWidth - 2 * dMargin;
		const double value = dMeters / dInches;
		return value;
	}
	// meters per inch scale
	__declspec( property( get = GetMetersPerInch ) )
		double MetersPerInch;

	// rectangle defining the football
	CRect GetRectangle(int nX, int nY )
	{
		const double dHeight = 0.1;
		const double dWidth = 2 * dHeight;
		const int nDeltaX = InchesToLogical( dWidth / 2 );
		const int nDeltaY = InchesToLogical( dHeight / 2 );
		CRect value;
		value.left = nX - nDeltaX;
		value.right = nX + nDeltaX;
		value.top = nY - nDeltaY;
		value.bottom = nY + nDeltaY;
		return value;
	}
	// rectangle defining the football
	__declspec( property( get = GetRectangle ) )
		CRect Rectangle[][];

	// public methods
public:
	// PI
	static inline const double PI()
	{
		return 3.1415926535897932384626433832795;
	}

	// degrees from radians
	template <class T> static inline T Degrees( T radians )
	{
		return (T)180 / (T)PI() * radians;
	}

	// radians from degrees
	template <class T> static inline T Radians( T degrees )
	{
		return (T)PI() / (T)180 * degrees;
	}

	// compare two reals and determine if they are nearly equal 
	// (within the given error range)
	template <class T> static inline bool NearlyEqual
	(
		T value1, T value2, T error = T( 0.0001 )
	)
	{
		const T diff = fabs( value1 - value2 );
		return diff < error;
	}

	// Round value to nearest multiple of nearest (ie. if nearest is 0.1
	// round to the nearest tenth or if nearest is 5, round to the nearest
	// multiple of five).  If second parameter is not supplied, value is 
	// rounded to the nearest whole number 
	template <class T> static inline T RoundToNearest
	(
		T value, T nearest = T( 1 )
	)
	{
		if ( nearest == 0 )
		{
			nearest = 1;
		}
		nearest = fabs( nearest ); // positive number
		value /= nearest;
		value = value < 0 ? 
			ceil( value - T( 0.5 ) ) : 
			floor( value + T( 0.5 ) );
		value *= nearest;
		return value;
	}

	// convert logical co-ordinate value to inches
	double LogicalToInches( int nValue )
	{
		CFieldGoalDoc* pDoc = Document;
		const int nMap = pDoc->Map;
		return ( double( nValue ) / nMap );
	}

	// convert inches to logical co-ordinate value
	int InchesToLogical( double dValue )
	{
		CFieldGoalDoc* pDoc = Document;
		const int nMap = pDoc->Map;
		return int( dValue * nMap );
	}

	// prepare the device context for printing
	void SetPrintDC
	( 
		CDC* pDC,
		int& nPhysicalWidth, // in pixels
		int& nPhysicalHeight, // in pixels
		int& nLogicalWidth, // in inches * Map
		int& nLogicalHeight // in inches * Map
	);

	// prepare the device context for drawing and
	// return the logical width
	int SetDrawDC( CDC* pDC );

	// protected methods
protected:
	// render the page or view
	void render
	( 
		CDC* pDC, double dTopOfView, double dBottomOfView, int nLogicalWidth
	);

	// set the scroll bar position and range
	void SetupScrollBars()
	{
		const double dLast = Last;
		if ( NearlyEqual( dLast, 0.0 ))
		{
			SetScrollPos( SB_VERT, 0, FALSE );
			SetScrollRange( SB_VERT, 0, 1, TRUE );
		}
		else
		{
			int nLines = ScrollLines;
			if ( nLines <= 1 )
			{
				nLines = 2;
			}
			const double dRatio = TopOfView / Last;
			const double dLine = double( nLines ) * dRatio;
			int nLine = int( dLine + 0.5 );
			if ( nLine >= nLines )
			{
				nLine = nLines - 1;
			}

			SetScrollPos( SB_VERT, nLine, FALSE );
			SetScrollRange( SB_VERT, 0, nLines - 1, TRUE );
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// generate font characteristics from given font enumeration, where
	// the enumeration is based on Atlas PDF definition
	static void BuildFont
	( 
		CString csFace, // name of the font face
		bool bBold, // bold font if true
		bool bItalic, // italic font if true
		int nTextHeight, // text height in pixels
		bool bVertical, // vertical orientation
		CFont& font, // generated font
		BYTE nCharSet = ANSI_CHARSET, // current character set
		bool bFlipX = false, // flip horizontally
		bool bFlipY = false, // flip vertically
		short nUp = -1, // moving up is a negative value
		int nTextWidth = 0 // default width
	);

	// Overrides
public:
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
	virtual void OnDraw( CDC* pDC );  // overridden to draw this view
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting( CPrintInfo* pInfo );
	virtual void OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo );
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );
	virtual void OnEndPrinting( CDC* pDC, CPrintInfo* pInfo );

	// Implementation
public:
	CFieldGoalView();
	virtual ~CFieldGoalView();
	DECLARE_DYNCREATE( CFieldGoalView )

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& dc ) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnContextMenu( CWnd* pWnd, CPoint point );
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FieldGoalView.cpp
inline CFieldGoalDoc* CFieldGoalView::GetDocument() const
{
	return reinterpret_cast<CFieldGoalDoc*>( m_pDocument );
}
#endif

