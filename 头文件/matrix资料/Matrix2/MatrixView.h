// MatrixView.h : interface of the CMatrixView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXVIEW_H__50B8F1C6_4AED_11D5_9DFE_5254AB1C303A__INCLUDED_)
#define AFX_MATRIXVIEW_H__50B8F1C6_4AED_11D5_9DFE_5254AB1C303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMatrixView : public CEditView
{
protected: // create from serialization only
	CMatrixView();
	DECLARE_DYNCREATE(CMatrixView)

// Attributes
public:
	CMatrixDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMatrixView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMatrixView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MatrixView.cpp
inline CMatrixDoc* CMatrixView::GetDocument()
   { return (CMatrixDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXVIEW_H__50B8F1C6_4AED_11D5_9DFE_5254AB1C303A__INCLUDED_)
