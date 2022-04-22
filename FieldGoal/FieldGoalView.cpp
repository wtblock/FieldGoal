
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022 by W. T. Block, All Rights Reserved
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "FieldGoalDoc.h"
#include "FieldGoalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _DOUBLE_BUFFER

/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE( CFieldGoalView, CScrollView )

/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP( CFieldGoalView, CScrollView )
	// Standard printing commands
	ON_COMMAND( ID_FILE_PRINT, &CScrollView::OnFilePrint )
	ON_COMMAND( ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint )
	ON_COMMAND( ID_FILE_PRINT_PREVIEW, &CFieldGoalView::OnFilePrintPreview )
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
CFieldGoalView::CFieldGoalView()
{
	m_nPhysicalPageWidth = 0;
	m_nPhysicalPageHeight = 0;
	m_nLogicalPageWidth = 0;
	m_nLogicalPageHeight = 0;
	m_bInitialUpdate = false;
	TopOfView = 0;

} // CFieldGoalView

/////////////////////////////////////////////////////////////////////////////
CFieldGoalView::~CFieldGoalView()
{
} // ~CFieldGoalView

/////////////////////////////////////////////////////////////////////////////
BOOL CFieldGoalView::PreCreateWindow( CREATESTRUCT& cs )
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow( cs );
} // PreCreateWindow

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnPrepareDC( CDC * pDC, CPrintInfo * pInfo )
{
	if ( pInfo != nullptr ) // printing
	{
		SetPrintDC
		( 
			pDC, 
			m_nPhysicalPageWidth, m_nPhysicalPageHeight, 
			m_nLogicalPageWidth, m_nLogicalPageHeight 
		);
	}

} // OnPrepareDC

/////////////////////////////////////////////////////////////////////////////
// prepare the device context for drawing and
// return the logical width
int CFieldGoalView::SetDrawDC
( 
	CDC* pDC
)
{
	// the document has hard coded the width to be 11 inches
	CFieldGoalDoc* pDoc = Document;
	const double dDocumentWidth = pDoc->Width;

	// the logical width is 11000 since we are mapping the logical
	// coordinate system to 1000 pixels per inch which means the 
	// code does not have to be concerned about the actual resolution
	// of the output device (image, screen, or printer)
	const int nLogicalWidth = InchesToLogical( dDocumentWidth );
	if ( nLogicalWidth != 0 )
	{
		// isotropic means the values are the same in the X and Y directions
		pDC->SetMapMode( MM_ISOTROPIC );

		// using the width for X and Y so that the image will alway fit
		// horizontally in the window and the vertical dimension will 
		// adjust proportionally
		pDC->SetWindowExt( nLogicalWidth, nLogicalWidth );
		pDC->SetViewportExt( m_sizeClient.cx, m_sizeClient.cx );
	}

	return nLogicalWidth;
} // SetDrawDC

/////////////////////////////////////////////////////////////////////////////
// prepare the device context for printing
void CFieldGoalView::SetPrintDC
( 
	CDC* pDC,
	int& nPhysicalWidth, // in pixels
	int& nPhysicalHeight, // in pixels
	int& nLogicalWidth, // in inches * Map
	int& nLogicalHeight // in inches * Map
)
{
	nPhysicalWidth = pDC->GetDeviceCaps( HORZRES );
	nPhysicalHeight = pDC->GetDeviceCaps( VERTRES );
	const int nPixelsPerInchX = pDC->GetDeviceCaps( LOGPIXELSX );
	const int nPixelsPerInchY = pDC->GetDeviceCaps( LOGPIXELSY );

	CFieldGoalDoc* pDoc = Document;
	const int nMap = pDoc->Map;
	const double dWidth = (double)nPhysicalWidth * nMap / (double)nPixelsPerInchX;
	const int nWidth = (int)( dWidth + 0.5 );
	double dHeight = (double)nPhysicalHeight * nMap / (double)nPixelsPerInchY;
	const int nHeight = (int)( dHeight + 0.5 );

	if ( nWidth < nLogicalWidth && nLogicalWidth != 0 )
	{
		dHeight = (float)nHeight / (float)nWidth;
		dHeight *= (float)nLogicalWidth;
		nLogicalHeight = (int)( dHeight + 0.5 );
	}
	else
	{
		nLogicalHeight = nHeight;
		nLogicalWidth = nWidth;
	}

	// create custom MM_HIENGLISH mapping mode:
	// 	1. maintain constant aspect ratio
	//	2. accept coordinates in 1/Map inches
	//	3. keep entire page width visible at all times
	//	4. vertical dimensions increase from top to bottom
	pDC->SetMapMode( MM_ISOTROPIC );
	//	base horizontal AND VERTICAL extents on page WIDTH
	//                  ============                 =====
	pDC->SetWindowExt( nLogicalWidth, nLogicalWidth );
	//	client WIDTH
	//		   =====
	pDC->SetViewportExt( nPhysicalWidth, nPhysicalWidth );
} // SetPrintDC

/////////////////////////////////////////////////////////////////////////////
// record the client rectangle every time the windows is resized
void CFieldGoalView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize( nType, cx, cy );

	m_sizeClient.cx = cx;
	m_sizeClient.cy = cy;

	SetupScrollBars();
} // OnSize

/////////////////////////////////////////////////////////////////////////////
// render the page or view
void CFieldGoalView::render
( 
	CDC* pDC, double dTopOfView, double dBottomOfView, int nLogicalWidth
)
{
	CFieldGoalDoc* pDoc = Document;
	const UINT nPages = pDoc->Pages;
	double dTopOfPage = 0;

	// create a pen to draw with
	CPen penBlack, penRed;

	// save the entry state
	const int nDC = pDC->SaveDC();

	// 5 hundredths of an inch
	const int nBlackWidth = InchesToLogical( 0.05 );

	// 1 hundredth of an inch
	const int nRedWidth = InchesToLogical( 0.01 );

	// black color
	const COLORREF rgbBlack = RGB( 0, 0, 0 );

	// red color
	const COLORREF rgbRed = RGB( 240, 0, 0 );

	// create a solid black pen 0.05 inches wide
	penBlack.CreatePen( PS_SOLID, nBlackWidth, rgbBlack );

	// create a solid red pen 0.01 inches wide
	penRed.CreatePen( PS_SOLID, nRedWidth, rgbRed );

	// select the pen for drawing field and goal post
	pDC->SelectObject( &penBlack );

	// loop through all pages in the document and draw those which overlap 
	// our view
	for ( UINT nPage = 0; nPage < nPages; nPage++ )
	{
		const double dPageHeight = PageHeight;
		const double dBottomOfPage = dTopOfPage + dPageHeight;
		if ( dBottomOfView < dTopOfPage ) // entire view is above page
		{
			break; // we are done
		}
		else if ( dTopOfView > dBottomOfPage ) // entire view is below page
		{
			//dTopOfPage = dBottomOfPage; // move on to next page
			//continue;

			// we have defined the project as a single page
			break;
		}

		// distance from top of view to top of page, where a positive value
		// indicates the page is partially below the view
		const double dPageOffset = dTopOfPage - dTopOfView;
		const int nPageOffset = InchesToLogical( dPageOffset );
		const int nLogicalPageHeight = InchesToLogical( dPageHeight );

		// account for the shift of the view due to scrolling or printed pages
		pDC->SetWindowOrg( 0, -nPageOffset );

		// co-ordinates where the field line will be drawn
		const int nxField1 = LogicalDocumentMargin;
		const int nxField2 = LogicalDocumentWidth - nxField1;
		const int nyField = LogicalDocumentHeight - nxField1;

		// draw the field line
		pDC->MoveTo( nxField1, nyField );
		pDC->LineTo( nxField2, nyField );

		// the scale factor in meters per inch
		const double dMetersPerInch = MetersPerInch;

		// co-ordinates of the goal base
		const double dGoalHeight = GoalHeight;
		const double dInches = dGoalHeight / dMetersPerInch;
		const int nPixels = InchesToLogical( dInches );

		// draw the vertical goal post
		const int nyField2 = nyField - nPixels;
		pDC->LineTo( nxField2, nyField2 );

		// draw the horizontal goal post
		pDC->MoveTo( nxField2 - nPixels / 2, nyField2 );
		pDC->LineTo( nxField2 + nPixels / 2, nyField2 );

		// draw the upper vertical posts
		pDC->LineTo( nxField2 + nPixels / 2, nyField2 - nPixels );
		pDC->MoveTo( nxField2 - nPixels / 2, nyField2 );
		pDC->LineTo( nxField2 - nPixels / 2, nyField2 - nPixels );

		// initial velocities need to be calculated for the X and Y directions
		// using trigonometry 
		const double dHorizontalVelocity = HorizontalVelocity;
		const double dVerticalVelocity = VerticalVelocity;

		// travel time to the goal is easy to calculate because the horizontal
		// velocity is constant
		const double dMetersToGoal = MetersToGoal;

		// the travel time is the distance divided by the velocity
		const double dTravelTime = dMetersToGoal / dHorizontalVelocity;

		// time between trajectory calculations
		const double dT = 0.1;

		// draw the trajectory in red
		pDC->SelectObject( &penRed );

		// the starting point's coordinates
		int nX = nxField1;
		int nY = nyField;

		//pDC->MoveTo( nX, nY );
		// create a rectangle representing the football 
		CRect rect = Rectangle[ nX ][ nY ];

		// draw the football as an ellipse that fits into the rectangle
		pDC->Ellipse( &rect );


		// the gravity equation to calculate distance:
		//
		//		D = 1/2 a * t ^ 2 + v * t + d
		//
		// where:
		//		 a is the acceleration of gravity in the Y direction
		//			and 0 in the X direction
		//		 v is the initial velocity
		//		 d is the initial distance
		//		 D is the calculated distance
		for ( double dTime = dT; dTime <= dTravelTime; dTime += dT )
		{
			// the horizontal distance traveled is simply velocity multiplied 
			// by time since there is no acceleration in the X direction
			const double dxMeters = dHorizontalVelocity * dTime;

			// time raised to the power of 2
			const double dTimeSquared = pow( dTime, 2.0 );

			// the acceleration of gravity on the surface of the earth
			// in meters per second squared
			const double dGravity = 9.8;

			// vertical distance depends on the initial vertical velocity
			// which is negative because our mapping mode sets the upper left
			// corner as the origin (0, 0) such that X gets greater to the right
			// and Y gets greater going down. The football is being kicked up so
			// the initial vertical velocity is negative.
			double dyMeters =  -dVerticalVelocity * dTime;

			// add in the effect of gravity: 1/2 of gravity * time squared
			dyMeters += ( dGravity * dTimeSquared / 2 );

			// scale the result by converting meters on the field to inches
			// on our view
			const double dxInches = dxMeters / dMetersPerInch;
			const double dyInches = dyMeters / dMetersPerInch;

			// convert the inches on the screen to our logical coordinate system
			nX = nxField1 + InchesToLogical( dxInches );
			nY = nyField + InchesToLogical( dyInches );

			// if the Y coordinate is greater than the initial Y, the ball is 
			// on the ground and we are done
			const bool bDone = nY >= nyField;

			if ( bDone )
			{
				nY = nyField; // cannot go below the ground level
			}

			// create a rectangle representing the football 
			rect = Rectangle[ nX ][ nY ];

			// draw the football as an ellipse that fits into the rectangle
			pDC->Ellipse( &rect );

			// if we are done, break out of this loop
			if ( bDone )
			{
				break;
			}
		}

		// move on to next page
		dTopOfPage = dBottomOfPage;
	}

	// restore the device context
	pDC->RestoreDC( nDC );

} // render

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnDraw( CDC* pDC )
{
	CFieldGoalDoc* pDoc = Document;
	ASSERT_VALID( pDoc );
	if ( !pDoc )
		return;

	CDC* pTargetDC = pDC;

#ifdef _DOUBLE_BUFFER
	// double buffer output by creating a memory bitmap and drawing
	// directly to it and then copy the bitmap to the screen to reduce 
	// screen flicker
	CRect rectClient;
	GetClientRect( &rectClient );
	const int nRectWidth = rectClient.Width();
	const int nRectHeight = rectClient.Height();

	CBitmap bm;
	bm.CreateCompatibleBitmap( pDC, nRectWidth, nRectHeight );

	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap* pBmOld = dcMem.SelectObject( &bm );
	dcMem.PatBlt( 0, 0, nRectWidth, nRectHeight, WHITENESS );
	pTargetDC = &dcMem;
	int nDcOrg = pTargetDC->SaveDC();
#endif

	const int nLogicalWidth = SetDrawDC( pTargetDC );
	const double dTopOfView = TopOfView;
	const double dBottomOfView = BottomOfView;
	render( pTargetDC, dTopOfView, dBottomOfView, nLogicalWidth );

#ifdef _DOUBLE_BUFFER
	pTargetDC->RestoreDC( nDcOrg );
	
	// output the drawing to the screen in a single bitblit
	pDC->BitBlt
	( 
		0, 0, nRectWidth, nRectHeight, &dcMem, 0, 0, SRCCOPY
	);

	dcMem.SelectObject( pBmOld );
#endif

} // OnDraw

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	m_bInitialUpdate = true;
} // OnInitialUpdate

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnFilePrintPreview()
{
	AFXPrintPreview( this );

} // OnFilePrintPreview

/////////////////////////////////////////////////////////////////////////////
BOOL CFieldGoalView::OnPreparePrinting( CPrintInfo* pInfo )
{
	// turning off multiple copies and collation 
	pInfo->m_pPD->m_pd.Flags &= ~PD_USEDEVMODECOPIES;

	return DoPreparePrinting( pInfo );

} // OnPreparePrinting

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	// setup the device context for our printer
	SetPrintDC
	( 
		pDC, 
		m_nPhysicalPageWidth, 
		m_nPhysicalPageHeight, 
		m_nLogicalPageWidth, 
		m_nLogicalPageHeight 
	);

	// height of the document in inches
	const double dDocumentHeight = DocumentHeight; 

	// height of a page in inches
	const double dPageHeight = LogicalToInches( m_nLogicalPageHeight );

	// number of printer pages
	double dPages = dDocumentHeight / dPageHeight;

	// add a page if there is a fraction of a page
	m_nNumPages = (int)dPages;
	if ( !NearlyEqual( double( m_nNumPages ), dPages, 0.05 ))
	{
		m_nNumPages++; // account for fractional page
	}

	// let the print dialog know
	pInfo->SetMinPage( 1 );
	pInfo->SetMaxPage( m_nNumPages );

} // OnBeginPrinting

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	const double dPageHeight = LogicalToInches( m_nLogicalPageHeight );
	const int nPage = (int)pInfo->m_nCurPage;
	const double dTopOfView = ( (float)( nPage - 1 ) ) * dPageHeight;
	const double dBottomOfView = dTopOfView + dPageHeight;

	// the same render method used to draw on the screen
	render( pDC, dTopOfView, dBottomOfView, m_nLogicalPageWidth );

} // OnPrint

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
	// nothing to clean up
}

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnRButtonUp( UINT /* nFlags */, CPoint point )
{
	ClientToScreen( &point );
	OnContextMenu( this, point );
}

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnContextMenu( CWnd* /* pWnd */, CPoint point )
{
}

/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void CFieldGoalView::AssertValid() const
{
	CScrollView::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::Dump( CDumpContext& dc ) const
{
	CScrollView::Dump( dc );
}

/////////////////////////////////////////////////////////////////////////////
CFieldGoalDoc* CFieldGoalView::GetDocument() const // non-debug version is inline
{
	ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CFieldGoalDoc ) ) );
	return (CFieldGoalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
BOOL CFieldGoalView::OnEraseBkgnd( CDC* pDC )
{
#ifdef _DOUBLE_BUFFER
	// double buffer output by creating a memory bitmap and drawing
	// directly to it and then copy the bitmap to the screen to reduce flicker
	// need to prevent the default erase background behavior
	return TRUE;
#else
	return CView::OnEraseBkgnd( pDC );
#endif
} // OnEraseBkgnd

/////////////////////////////////////////////////////////////////////////////
void CFieldGoalView::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	CFieldGoalDoc* pDoc = Document;
	ASSERT_VALID( pDoc );

	double dTop = TopOfView;
	double dLast = Last;
	const double dLineHeight = LineHeight;
	const double dPageHeight = PageHeight;

	switch ( nSBCode )
	{
		case SB_PAGEDOWN: // Scroll one page down.
			if ( NearlyEqual( dTop, dLast ) ) return;
			dTop += dPageHeight;
			if ( dTop > dLast )
			{
				dTop = dLast;
			}
			break;
		case SB_LINEDOWN: // Scroll one line down.
			if ( NearlyEqual( dTop, dLast ) ) return;
			dTop += dLineHeight;
			break;
		case SB_PAGEUP: // Scroll one page up.
			if ( NearlyEqual( dTop, 0.0 ) ) return;
			dTop -= dPageHeight;
			break;
		case SB_LINEUP: // Scroll one line up.
			if ( NearlyEqual( dTop, 0.0 ) ) return;
			dTop -= dLineHeight;
			break;
		case SB_THUMBTRACK: 	// Drag scroll box to specified position. 
								// The current position is provided in nPos.
			dTop = nPos * dLineHeight;
			break;
		case SB_THUMBPOSITION: // Scroll to the absolute position. 
								// The current position is provided in nPos.

			dTop = nPos * dLineHeight;
			break;
		case SB_TOP: // Scroll to top.
			dTop = 0;
			break;
		case SB_BOTTOM: // Scroll to bottom.
			dTop = dLast;
			break;
		case SB_ENDSCROLL: // End scroll.
			return;
	} // switch 

	// cannot scroll above the top
	if ( dTop < 0 )
	{
		dTop = 0;
	}
	// cannot scroll below the bottom
	else if ( dTop > dLast )
	{
		dTop = dLast;
	}

	if ( !NearlyEqual( dLast, 0.0 ) )
	{
		const double dLines = dLast / dLineHeight;
		const int nLines = int( dLines + 0.5f );
		const double dRatio = dTop / dLast;
		const double dLine = dLines * dRatio;
		int nLine = int( dLine + 0.5f );
		SetScrollPos( SB_VERT, nLine );
	}

	SetTopOfView( dTop );
	InvalidateRect( NULL );
} // OnVScroll

/////////////////////////////////////////////////////////////////////////////
