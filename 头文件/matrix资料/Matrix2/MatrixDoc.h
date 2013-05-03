// MatrixDoc.h : interface of the CMatrixDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXDOC_H__50B8F1C4_4AED_11D5_9DFE_5254AB1C303A__INCLUDED_)
#define AFX_MATRIXDOC_H__50B8F1C4_4AED_11D5_9DFE_5254AB1C303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "ArrayMatrix.h"
#include "stack.h"

class CMatrixDoc : public CDocument
{
protected: // create from serialization only
	CMatrixDoc();
	DECLARE_DYNCREATE(CMatrixDoc)

// Attributes
public:
	CTypedPtrList<CObList,CArrayMatrix *> m_VariablePtrList;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ProcInput(const CString & all);
	CArrayMatrix * Operate(CArrayMatrix * a,TCHAR theta,CArrayMatrix * b,bool & ok);
	void ProcOpenDocText(const CString sDataString);
	virtual ~CMatrixDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL IsFood(const CString & Name,CArrayMatrix * & p);
	void TurnString(CString & sdata);
	int Precede(TCHAR m,TCHAR n);
	BOOL StringsToMatrixs(CString * pVar,CTypedPtrList<CObList,CArrayMatrix *> & m_List,int num);
	int GetVariableNum(const CString & m,CString * & pVar);
	BOOL GetResult(const CString & data,CArrayMatrix & matrix);
	BOOL IsOperator(TCHAR ch);
	BOOL ProcOneString(const CString &);
	//{{AFX_MSG(CMatrixDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXDOC_H__50B8F1C4_4AED_11D5_9DFE_5254AB1C303A__INCLUDED_)
