/* * * * * * * * * * * * * * * * * * * * * 
* FileName:    Matrix.h
* Description: Matrix Class 
* 
* Version:     1.0
* Author:      wxs
* Finish Time: 2001年7月2日
* * * * * * * * * * * * * * * * * * * * * */

#ifndef _MATRIX_H_
#define _MATRIX_H_

class CMatrix : public CObject
{
public:

	//构造函数
	CMatrix();
	CMatrix(int nRow, int nCol);
	CMatrix(int nRow, int nCol, double* pAry);
	CMatrix(CMatrix & src);//拷贝构造函数

	//析构函数
	virtual ~CMatrix();

	void Serialize(CArchive& ar);//文件流操作

	void Draw(CDC *pDC, CPoint pos);//画矩阵

	//运算符重载
	double* & operator [] (int nRow);
	CMatrix & operator =  (CMatrix & mx);
	CMatrix & operator += (CMatrix & mx);
	CMatrix & operator -= (CMatrix & mx);
	CMatrix & operator *= (CMatrix & mx);
	
	//矩阵运算
	void Empty(void);
	BOOL IsEmpty(void);
	void SetMatrix(int nRow, int nCol);
	void SetMatrix(int nRow, int nCol, double* pAry);
	void SetMatrix(double* pAry);
	int Pivot(int nRow);//private partial pivoting method

    void SwapRow(int nRow1, int nRow2);//行交换   
    void SwapCol(int nCol1, int nCol2);//列交换
	void ToUnit(void);//单位矩阵
	void ToNull(void);//零矩阵
	double Max(void);//矩阵大极值
	double Min(void);//矩阵极小值
	double Det(void);//行列式
	int SolveLinearQquations(double ary []);//列主元消元法求线性方程组 Solution system of linear eqations

	int Row() const { return m_nRow; }
	int Col() const { return m_nCol; }
  
	BOOL LoadMatrix();
	BOOL LoadMatrix(CString strPath);
	BOOL SaveMatrix(CString strPath, BOOL bASCII = TRUE); 
	BOOL SaveMatrix();

	//友元
	friend CMatrix operator + (CMatrix & mx, double k);
	friend CMatrix operator + (double k, CMatrix & mx);
    friend CMatrix operator + (CMatrix & mx1, CMatrix & mx2);
	//friend CMatrix operator - (CMatrix & mx, double k);
	//friend CMatrix operator - (double k, CMatrix & mx);
	//friend CMatrix operator - (CMatrix & mx1, CMatrix & mx2);
	friend CMatrix operator * (CMatrix & mx, double k);
	friend CMatrix operator * (double k, CMatrix & mx);
	friend CMatrix operator * (CMatrix & mx1, CMatrix & mx2);
	friend CMatrix operator ^ (CMatrix & mx, int pow);//矩阵次幂
	friend BOOL operator != (CMatrix & mx1, CMatrix & mx2);
	friend BOOL operator == (CMatrix & mx1, CMatrix & mx2);
	friend CMatrix operator ~ (CMatrix & mx);//矩阵转置
	friend CMatrix operator ! (CMatrix & mx);//逆矩阵

#ifdef _DEBUG
    void Output() const;
#endif

private:

    int m_nRow;//行数
	int m_nCol;//列数

	double* *m_pData;
};

#endif //#ifndef _MATRIX_H_
