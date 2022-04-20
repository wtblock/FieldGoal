
// FieldGoalView.cpp : implementation of the CFieldGoalView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FieldGoal.h"
#endif

#include "FieldGoalDoc.h"
#include "FieldGoalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFieldGoalView

IMPLEMENT_DYNCREATE(CFieldGoalView, CScrollView)

BEGIN_MESSAGE_MAP(CFieldGoalView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFieldGoalView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFieldGoalView construction/destruction

CFieldGoalView::CFieldGoalView()
{
	// TODO: add construction code here

}

CFieldGoalView::~CFieldGoalView()
{
}

BOOL CFieldGoalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CFieldGoalView drawing

void CFieldGoalView::OnDraw(CDC* /*pDC*/)
{
	CFieldGoalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CFieldGoalView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CFieldGoalView printing


void CFieldGoalView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFieldGoalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFieldGoalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFieldGoalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFieldGoalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFieldGoalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFieldGoalView diagnostics

#ifdef _DEBUG
void CFieldGoalView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFieldGoalView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFieldGoalDoc* CFieldGoalView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFieldGoalDoc)));
	return (CFieldGoalDoc*)m_pDocument;
}
#endif //_DEBUG


// CFieldGoalView message handlers
