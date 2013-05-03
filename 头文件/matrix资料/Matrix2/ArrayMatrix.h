// ArrayMatrix.h: interface for the CArrayMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYMATRIX_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_)
#define AFX_ARRAYMATRIX_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include <string.h>

class CArrayMatrix : public CObject  
{
public:
	BOOL SetName(CString m);
	CString GetName();
	CArrayMatrix GetAccompany()const;//求矩阵的伴随矩阵
	float GetRange()const;//求矩阵的行列式
	BOOL CanContrary()const;//是否可以求逆
	CArrayMatrix T()const;//求矩阵的转置矩阵
	CArrayMatrix operator ~();//求矩阵的逆矩阵
	CArrayMatrix operator /(CArrayMatrix & m);
	CArrayMatrix operator /(float m);
	CArrayMatrix operator *(const CArrayMatrix & m);
	CArrayMatrix operator *(float m);
	BOOL CanMutiply(const CArrayMatrix & m)const;
	BOOL CanAddSub(const CArrayMatrix & m)const;
	BOOL DisPlay(CString & out)const;
	static void DeleteHeadEnter(CString &);	//删除字符串矩阵信息中放在等号右边的连续换行符和空格
	static void ProcString(CString &);
	static void ProcStringEnter(CString &);
	static void ProcStringComma(CString &);//是字符串中的逗号（，）变成空格，是结束符分号（；）变成换行符'\n'
	static void ProcStringBlank(CString &);//使字符串规格化，即使其中的空格都为一个
	static BOOL SetStringName(CString & DataString,CString & sName);
	BOOL ProcessInput(CString DataString);
	CArrayMatrix(const CArrayMatrix &);
	void Serialize(CArchive& ar);
	DECLARE_SERIAL(CArrayMatrix)
	CArrayMatrix();
	virtual ~CArrayMatrix();
	CArrayMatrix operator +(const CArrayMatrix & m);
	CArrayMatrix operator -(const CArrayMatrix & m);
	CArrayMatrix & operator =(const CArrayMatrix &m);
	CArrayMatrix & operator =(float m);

protected:
	BOOL ConvertToNum(const CString &,const int &,float &);
	BOOL InputCon(const CString &,CString *&);
	BOOL InputRow(const CString &);
	CString m_Name;
	UINT m_wRow;
	UINT m_wCon;
	CArray<float,float &> m_Array;
};

#endif // !defined(AFX_ARRAYMATRIX_H__75314E61_4BBF_11D5_9DFE_5254AB1C303A__INCLUDED_)
