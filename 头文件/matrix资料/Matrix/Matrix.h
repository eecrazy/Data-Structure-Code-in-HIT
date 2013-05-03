// Matrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__ACEC32EA_5254_4C23_A8BD_12F9220EF43A__INCLUDED_)
#define AFX_MATRIX_H__ACEC32EA_5254_4C23_A8BD_12F9220EF43A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

#if !defined(_BITSET_)
#include <bitset>
#endif // !defined(_BITSET_)

///////////////////////////////////////////////////////////////////////////////
///////
//
//(-- class CTokenizer
//
class CTokenizer
{
public:
	CTokenizer(const CString& cs, const CString& csDelim) : m_cs(cs),m_nCurPos(0)
	{
		SetDelimiters(csDelim);
	}
	void SetDelimiters(const CString& csDelim)
	{
		for(int i = 0; i < csDelim.GetLength(); ++i)
			m_sDelimiter.set(static_cast<BYTE>(csDelim[i]));
	}
	
	BOOL Next(CString& cs)
	{
		cs.Empty();
		
		while(m_nCurPos < m_cs.GetLength() && 
			m_sDelimiter[static_cast<BYTE>(m_cs[m_nCurPos])])
			++m_nCurPos;
		
		if(m_nCurPos >= m_cs.GetLength())
			return FALSE;
		
		int nStartPos = m_nCurPos;
		while(m_nCurPos < m_cs.GetLength() && 
			!m_sDelimiter[static_cast<BYTE>(m_cs[m_nCurPos])])
			++m_nCurPos;
		
		cs = m_cs.Mid(nStartPos, m_nCurPos - nStartPos);
		
		return TRUE;
	}
	
	CString Tail() const
	{
		int nCurPos = m_nCurPos;
		
		while(nCurPos < m_cs.GetLength() && 
			m_sDelimiter[static_cast<BYTE>(m_cs[nCurPos])])
			++nCurPos;
		
		CString csResult;
		
		if(nCurPos < m_cs.GetLength())
			csResult = m_cs.Mid(nCurPos);
		
		return csResult;
	}
	
private:
	CString m_cs;
	std::bitset<256> m_sDelimiter;
	int m_nCurPos;
};
//
//--) // class CTokenizer
//
///////////////////////////////////////////////////////////////////////////////
///////

///////////////////////////////////////////////////////////////////////////////
///////
//
//(-- class CMatrix
//
class CMatrix  
{
	//
	// 公有接口函数
	//
public:
	
	//
	// 构造与析构
	//
	
	
	CMatrix();                                                                     
	// 基础构造函数
	CMatrix(int nRows, int nCols);                                  // 指定
//	行列构造函数
        CMatrix(int nRows, int nCols, double value[]);  // 指定数据构造函数
	CMatrix(int 
		nSize);                                                             // 方阵构造
//	函数
        CMatrix(int nSize, double value[]);                             // 指定
//	数据方阵构造函数
        CMatrix(const CMatrix& other);                                  // 拷贝
//	构造函数
        BOOL    Init(int nRows, int nCols);                             // 初始
//	化矩阵   
        BOOL    MakeUnitMatrix(int nSize);                              // 将方
//	阵初始化为单位矩阵
        virtual 
		~CMatrix();                                                             // 析构
//	函数
		
        //
        // 输入与显示
        //
		
        // 将字符串转换为矩阵数据
        BOOL FromString(CString s, const CString& sDelim = " ", BOOL 
		bLineBreak = TRUE);        
	// 将矩阵转换为字符串
	CString ToString(const CString& sDelim = " ", BOOL bLineBreak = TRUE) 
		const;
	// 将矩阵的指定行转换为字符串
	CString RowToString(int nRow, const CString& sDelim = " ") const;
	// 将矩阵的指定列转换为字符串
	CString ColToString(int nCol, const CString& sDelim = " ") const;
	
	//
	// 元素与值操作
	//
	
	BOOL    SetElement(int nRow, int nCol, double value);   // 设置指定元素的值
    double  GetElement(int nRow, int nCol) const;                   // 获取指定元素的值
    void    SetData(double value[]);                                                // 设置矩阵的值
	int     GetNumColumns() const;
		                                                  // 获取矩阵的列数
	int     GetNumRows() const; 
		                                                            // 获取矩阵的行数
    int     GetRowVector(int nRow, double* pVector) const;  // 获取矩阵的指定行矩阵
	
    int     GetColVector(int nCol, double* pVector) const;  // 获取矩阵的指定列矩阵
	
    double* GetData() const; 
		                                                               // 获取矩阵的值
	
		
        //
        // 数学操作
        //
		
    CMatrix& operator=(const CMatrix& other);
	BOOL operator==(const CMatrix& other) const;
	BOOL operator!=(const CMatrix& other) const;
	CMatrix operator+(const CMatrix& other) const;
	CMatrix operator-(const CMatrix& other) const;
	CMatrix operator*(double value) const;
	CMatrix operator*(const CMatrix& other) const;
	// 复矩阵乘法
	BOOL CMul(const CMatrix& AR, const CMatrix& AI, const CMatrix& BR, 
		const CMatrix& BI, CMatrix& CR, CMatrix& CI) const;
	// 矩阵的转置
	CMatrix Transpose() const;
	
	//
	// 算法
	//
	
	// 实矩阵求逆的全选主元高斯－约当法
	BOOL 
		InvertGaussJordan();                                               
	// 复矩阵求逆的全选主元高斯－约当法
	BOOL InvertGaussJordan(CMatrix& 
		mtxImag);                                 
	// 对称正定矩阵的求逆
	BOOL InvertSsgj();                                              
	// 托伯利兹矩阵求逆的埃兰特方法
	BOOL 
		InvertTrench();                                                    
	// 求行列式值的全选主元高斯消去法
	double 
		DetGauss();                                                              
	// 求矩阵秩的全选主元高斯消去法
	int RankGauss();
	// 对称正定矩阵的乔里斯基分解与行列式的求值
	BOOL DetCholesky(double* 
		dblDet);                                                               
	// 矩阵的三角分解
	BOOL SplitLU(CMatrix& mtxL, CMatrix& 
		mtxU);                                     
	// 一般实矩阵的QR分解
	BOOL SplitQR(CMatrix& 
		mtxQ);                                                      
	// 一般实矩阵的奇异值分解
	BOOL SplitUV(CMatrix& mtxU, CMatrix& mtxV, double eps = 
		0.000001);                                       
	// 求广义逆的奇异值分解法
	BOOL GInvertUV(CMatrix& mtxAP, CMatrix& mtxU, CMatrix& mtxV, double 
		eps = 0.000001);
	// 约化对称矩阵为对称三对角阵的豪斯荷尔德变换法
	BOOL MakeSymTri(CMatrix& mtxQ, CMatrix& mtxT, double dblB[], double 
		dblC[]);
	// 实对称三对角阵的全部特征值与特征向量的计算
	BOOL SymTriEigenv(double dblB[], double dblC[], CMatrix& mtxQ, int 
		nMaxIt = 60, double eps = 0.000001);
	// 约化一般实矩阵为赫申伯格矩阵的初等相似变换法
	void MakeHberg();
	// 求赫申伯格矩阵全部特征值的QR方法
	BOOL HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, 
		double eps = 0.000001);
	// 求实对称矩阵特征值与特征向量的雅可比法
	BOOL JacobiEigenv(double dblEigenValue[], CMatrix& mtxEigenVector, 
		int nMaxIt = 60, double eps = 0.000001);
	// 求实对称矩阵特征值与特征向量的雅可比过关法
	BOOL JacobiEigenv2(double dblEigenValue[], CMatrix& mtxEigenVector, 
		double eps = 0.000001);
	
	//
	// 保护性数据成员
	//
protected:
	int     m_nNumColumns;                  // 矩阵列数
	int     m_nNumRows;                             // 矩阵行数
	double* m_pData;                        // 矩阵数据缓冲区
	
	//
	// 内部函数
	//
private:
	void ppp(double a[], double e[], double s[], double v[], int m, int 
		n);
	void sss(double fg[2], double cs[2]);
	
};
//
//--) // class CMatrix
//
///////////////////////////////////////////////////////////////////////////////
///////

#endif // !defined(AFX_MATRIX_H__ACEC32EA_5254_4C23_A8BD_12F9220EF43A__INCLUDED_)
