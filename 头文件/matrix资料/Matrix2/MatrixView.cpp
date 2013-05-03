// MatrixView.cpp : implementation of the CMatrixView class
// Download by http://www.codefans.net
 
#include "stdafx.h"
#include "Matrix.h"

#include "MatrixDoc.h"
#include "MatrixView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixView

IMPLEMENT_DYNCREATE(CMatrixView, CEditView)

BEGIN_MESSAGE_MAP(CMatrixView, CEditView)
	//{{AFX_MSG_MAP(CMatrixView)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixView construction/destruction

CMatrixView::CMatrixView()
{
	// TODO: add construction code here

}

CMatrixView::~CMatrixView()
{
}

BOOL CMatrixView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixView drawing

void CMatrixView::OnDraw(CDC* pDC)
{
	CMatrixDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixView diagnostics

#ifdef _DEBUG
void CMatrixView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMatrixView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMatrixDoc* CMatrixView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMatrixDoc)));
	return (CMatrixDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatrixView message handlers

void CMatrixView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	CString sDataString=_T("");
	GetWindowText(sDataString);
	if(sDataString.GetLength()==0) return;
	sDataString.Replace("\xD\xA","\n");
	CMatrixDoc *pDoc=GetDocument();
	pDoc->ProcOpenDocText(sDataString);	
}

void CMatrixView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(TCHAR(nChar)=='\xd') 
	{
		CString stext;
		GetWindowText(stext);
		stext.Replace("\xd\xa","\n");
		stext.TrimRight();
		stext.TrimLeft();
		int len=lstrlen(stext);
		if(len!=0)
		{
			if(stext[len-1]==TCHAR(';'))
			{
				CString dataString=_T("");
				int num=0;
				for(int i=0;i<len;i++)
				{
					if(stext[i]==TCHAR(';')) num++;
				}
				if(num==1) dataString=stext;
				else
				{
					int nNum=0;
					int pos=0;
					for(i=0;i<len;i++)
					{
						if(stext[i]==TCHAR(';')) nNum++;
						if(nNum==(num-1)) {pos=i+1;break;}
					}
					if(stext[pos]!=TCHAR(';'))
					{
						int index=stext.ReverseFind(';');
						dataString=stext.Mid(pos,index-pos+1);
					}
				}
				if(!dataString.IsEmpty())
				{
					GetDocument()->ProcInput(dataString);
					GetEditCtrl().Paste();	
				}	
			}
		}
	}
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}
