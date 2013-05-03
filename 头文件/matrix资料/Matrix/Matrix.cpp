//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Matrix.cpp
//
// 操作矩阵的类 CMatrix 的实现文件
//
// 周长发编制, 2002/8
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 基本构造函数
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix()
{
	m_nNumColumns = 1;
	m_nNumRows = 1;
	m_pData = NULL;
	BOOL bSuccess = Init(m_nNumRows, m_nNumColumns);
	ASSERT(bSuccess);
}

//////////////////////////////////////////////////////////////////////
// 指定行列构造函数
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix(int nRows, int nCols)
{
	m_nNumRows = nRows;
	m_nNumColumns = nCols;
	m_pData = NULL;
	BOOL bSuccess = Init(m_nNumRows, m_nNumColumns);
	ASSERT(bSuccess);
}

//////////////////////////////////////////////////////////////////////
// 指定值构造函数
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
// 3. double value[] - 一维数组，长度为nRows*nCols，存储矩阵各元素的值
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix(int nRows, int nCols, double value[])
{
	m_nNumRows = nRows;
	m_nNumColumns = nCols;
	m_pData = NULL;
	BOOL bSuccess = Init(m_nNumRows, m_nNumColumns);
	ASSERT(bSuccess);
	SetData(value);
}

//////////////////////////////////////////////////////////////////////
// 方阵构造函数
//
// 参数：
// 1. int nSize - 方阵行列数
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix(int nSize)
{
	m_nNumRows = nSize;
	m_nNumColumns = nSize;
	m_pData = NULL;
	BOOL bSuccess = Init(nSize, nSize);
	ASSERT (bSuccess);
}

//////////////////////////////////////////////////////////////////////
// 方阵构造函数
//
// 参数：
// 1. int nSize - 方阵行列数
// 2. double value[] - 一维数组，长度为nRows*nRows，存储方阵各元素的值
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix(int nSize, double value[])
{
	m_nNumRows = nSize;
	m_nNumColumns = nSize;
	m_pData = NULL;
	BOOL bSuccess = Init(nSize, nSize);
	ASSERT (bSuccess);
	
	SetData(value);
}

//////////////////////////////////////////////////////////////////////
// 拷贝构造函数
//
// 参数：
// 1. const CMatrix& other - 源矩阵
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix(const CMatrix& other)
{
	m_nNumColumns = other.GetNumColumns();
	m_nNumRows = other.GetNumRows();
	m_pData = NULL;
	BOOL bSuccess = Init(m_nNumRows, m_nNumColumns);
	ASSERT(bSuccess);
	
	// copy the pointer
	memcpy(m_pData, other.m_pData, 
		sizeof(double)*m_nNumColumns*m_nNumRows);
}

//////////////////////////////////////////////////////////////////////
// 析构函数
//////////////////////////////////////////////////////////////////////
CMatrix::~CMatrix()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// 初始化函数
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
//
// 返回值：BOOL 型，初始化是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::Init(int nRows, int nCols)
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}
	
	m_nNumRows = nRows;
	m_nNumColumns = nCols;
	int nSize = nCols*nRows;
	if (nSize < 0)
		return FALSE;
	
	// 分配内存
	m_pData = new double[nSize];
	
	if (m_pData == NULL)
		return FALSE;                                   // 内存分配失败
	
	if (IsBadReadPtr(m_pData, sizeof(double) * nSize))
		return FALSE;
	
	// 将各元素值置0
	memset(m_pData, 0, sizeof(double) * nSize);
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 将方阵初始化为单位矩阵
//
// 参数：
// 1. int nSize - 方阵行列数
//
// 返回值：BOOL 型，初始化是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::MakeUnitMatrix(int nSize)
{
	if (! Init(nSize, nSize))
		return FALSE;
	
	for (int i=0; i<nSize; ++i)
		for (int j=0; j<nSize; ++j)
			if (i == j)
				SetElement(i, j, 1);
			
			return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 将字符串转化为矩阵的值
//
// 参数：
// 1. CString s - 数字和分隔符构成的字符串
// 2. const CString& sDelim - 数字之间的分隔符，默认为空格
// 3. BOOL bLineBreak - 行与行之间是否有回车换行符，默认为真(有换行符)
//         当该参数为FALSE时，所有元素值都在一行中输入，字符串的第一个
//         数值应为矩阵的行数，第二个数值应为矩阵的列数
//
// 返回值：BOOL 型，转换是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::FromString(CString s, const CString& sDelim /*= " "*/, BOOL 
						 bLineBreak /*= TRUE*/)
{
	if (s.IsEmpty())
		return FALSE;
	
	// 分行处理
	if (bLineBreak)
	{
		CTokenizer tk(s, "\r\n");
		
		CStringList ListRow;
		CString sRow;
		while (tk.Next(sRow))
		{
			sRow.TrimLeft();
			sRow.TrimRight();
			if (sRow.IsEmpty())
				break;
			
			ListRow.AddTail(sRow);
		}
		
		// 行数
		m_nNumRows = ListRow.GetCount();
		
		sRow = ListRow.GetHead();
		CTokenizer tkRow(sRow, sDelim);
		CString sElement;
		// 列数
		m_nNumColumns = 0;
		while (tkRow.Next(sElement))
		{
			m_nNumColumns++;
		}
		
		// 初始化矩阵
		if (! Init(m_nNumRows, m_nNumColumns))
			return FALSE;
		
		// 设置值
		POSITION pos = ListRow.GetHeadPosition();
		for (int i=0; i<m_nNumRows; i++)
		{
			sRow = ListRow.GetNext(pos);
			int j = 0;
			CTokenizer tkRow(sRow, sDelim);
			while (tkRow.Next(sElement))
			{
				sElement.TrimLeft();
				sElement.TrimRight();
				double v = atof(sElement);
				SetElement(i, j++, v);
			}
		}
		
		return TRUE;
	}
	
	// 不分行（单行）处理
	
	CTokenizer tk(s, sDelim);
	
	CString sElement;
	
	// 行数
	tk.Next(sElement);
	sElement.TrimLeft();
	sElement.TrimRight();
	m_nNumRows = atoi(sElement);
	
	// 列数
	tk.Next(sElement);
	sElement.TrimLeft();
	sElement.TrimRight();
	m_nNumColumns = atoi(sElement);
	
	// 初始化矩阵
	if (! Init(m_nNumRows, m_nNumColumns))
		return FALSE;
	
	// 设置值
	int i = 0, j = 0;
	while (tk.Next(sElement))
	{
		sElement.TrimLeft();
		sElement.TrimRight();
		double v = atof(sElement);
		SetElement(i, j++, v);
		
		if (j == m_nNumColumns)
		{
			j = 0;
			i++;
			if (i == m_nNumRows)
				break;
		}
	}
	
	return TRUE;
}
						 
//////////////////////////////////////////////////////////////////////
// 将矩阵各元素的值转化为字符串
//
// 参数：
// 1. const CString& sDelim - 数字之间的分隔符，默认为空格
// 2 BOOL bLineBreak - 行与行之间是否有回车换行符，默认为真(有换行符)
//
// 返回值：CString 型，转换得到的字符串
//////////////////////////////////////////////////////////////////////
CString CMatrix::ToString(const CString& sDelim /*= " "*/, BOOL bLineBreak 
						  /*= TRUE*/) const
{
	CString s="";
	
	for (int i=0; i<m_nNumRows; ++i)
	{
		for (int j=0; j<m_nNumColumns; ++j)
		{
			CString ss;
			ss.Format("%f", GetElement(i, j));
			s += ss;
			
			if (bLineBreak)
			{
				if (j != m_nNumColumns-1)
					s += sDelim;
			}
			else
			{
				if (i != m_nNumRows-1 || j != m_nNumColumns-1)
					s += sDelim;
			}
		}
		if (bLineBreak)
			if (i != m_nNumRows-1)
				s += "\r\n";
	}
	
	return s;
}

//////////////////////////////////////////////////////////////////////
// 将矩阵指定行中各元素的值转化为字符串
//
// 参数：
// 1. int nRow - 指定的矩阵行，nRow = 0表示第一行
// 2. const CString& sDelim - 数字之间的分隔符，默认为空格
//
// 返回值：CString 型，转换得到的字符串
//////////////////////////////////////////////////////////////////////
CString CMatrix::RowToString(int nRow, const CString& sDelim /*= " "*/) const
{
	CString s = "";
	
	if (nRow >= m_nNumRows)
		return s;
	
	for (int j=0; j<m_nNumColumns; ++j)
	{
		CString ss;
		ss.Format("%f", GetElement(nRow, j));
		s += ss;
		if (j != m_nNumColumns-1)
			s += sDelim;
	}
	
	return s;
}

//////////////////////////////////////////////////////////////////////
// 将矩阵指定列中各元素的值转化为字符串
//
// 参数：
// 1. int nCol - 指定的矩阵行，nCol = 0表示第一列
// 2. const CString& sDelim - 数字之间的分隔符，默认为空格
//
// 返回值：CString 型，转换得到的字符串
//////////////////////////////////////////////////////////////////////
CString CMatrix::ColToString(int nCol, const CString& sDelim /*= " "*/) const
{
	CString s = "";
	
	if (nCol >= m_nNumColumns)
		return s;
	
	for (int i=0; i<m_nNumRows; ++i)
	{
		CString ss;
		ss.Format("%f", GetElement(i, nCol));
		s += ss;
		if (i != m_nNumRows-1)
			s += sDelim;
	}
	
	return s;
}

//////////////////////////////////////////////////////////////////////
// 设置矩阵各元素的值
//
// 参数：
// 1. double value[] - 一维数组，长度为m_nNumColumns*m_nNumRows，存储
//                     矩阵各元素的值
//
// 返回值：无
//////////////////////////////////////////////////////////////////////
void CMatrix::SetData(double value[])
{
	// empty the memory
	memset(m_pData, 0, sizeof(double) * m_nNumColumns*m_nNumRows);
	// copy data
	memcpy(m_pData, value, sizeof(double)*m_nNumColumns*m_nNumRows);
}

//////////////////////////////////////////////////////////////////////
// 设置指定元素的值
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
// 3. double value - 指定元素的值
//
// 返回值：BOOL 型，说明设置是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::SetElement(int nRow, int nCol, double value)
{
	if (nCol < 0 || nCol >= m_nNumColumns || nRow < 0 || nRow >= m_nNumRows)
		return FALSE;// array bounds error
	
    if (m_pData == NULL)
		return FALSE;// bad pointer error
	
    m_pData[nCol + nRow * m_nNumColumns] = value;
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 设置指定元素的值
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2. int nCols - 指定的矩阵列数
//
// 返回值：double 型，指定元素的值
//////////////////////////////////////////////////////////////////////
double CMatrix::GetElement(int nRow, int nCol) const
{
	ASSERT(nCol >= 0 && nCol < m_nNumColumns && nRow >= 0 && nRow < m_nNumRows); // array bounds error
	ASSERT(m_pData);// bad pointer error
	return m_pData[nCol + nRow * m_nNumColumns];
}

//////////////////////////////////////////////////////////////////////
// 获取矩阵的列数
//
// 参数：无
//
// 返回值：int 型，矩阵的列数
//////////////////////////////////////////////////////////////////////
int     CMatrix::GetNumColumns() const
{
	return m_nNumColumns;
}

//////////////////////////////////////////////////////////////////////
// 获取矩阵的行数
//
// 参数：无
//
// 返回值：int 型，矩阵的行数
//////////////////////////////////////////////////////////////////////
int     CMatrix::GetNumRows() const
{
	return m_nNumRows;
}

//////////////////////////////////////////////////////////////////////
// 获取矩阵的数据
//
// 参数：无
//
// 返回值：double型指针，指向矩阵各元素的数据缓冲区
//////////////////////////////////////////////////////////////////////
double* CMatrix::GetData() const
{
	return m_pData;
}

//////////////////////////////////////////////////////////////////////
// 获取指定行的向量
//
// 参数：
// 1. int nRows - 指定的矩阵行数
// 2.  double* pVector - 指向向量中各元素的缓冲区
//
// 返回值：int 型，向量中元素的个数，即矩阵的列数
//////////////////////////////////////////////////////////////////////
int CMatrix::GetRowVector(int nRow, double* pVector) const
{
	if (pVector == NULL)
		delete pVector;
	
	pVector = new double[m_nNumColumns];
	ASSERT(pVector != NULL);
	
	for (int j=0; j<m_nNumColumns; ++j)
		pVector[j] = GetElement(nRow, j);
	
	return m_nNumColumns;
}

//////////////////////////////////////////////////////////////////////
// 获取指定列的向量
//
// 参数：
// 1. int nCols - 指定的矩阵列数
// 2.  double* pVector - 指向向量中各元素的缓冲区
//
// 返回值：int 型，向量中元素的个数，即矩阵的行数
//////////////////////////////////////////////////////////////////////
int CMatrix::GetColVector(int nCol, double* pVector) const
{
	if (pVector == NULL)
		delete pVector;
	
	pVector = new double[m_nNumRows];
	ASSERT(pVector != NULL);
	
	for (int i=0; i<m_nNumRows; ++i)
		pVector[i] = GetElement(i, nCol);
	
	return m_nNumRows;
}

//////////////////////////////////////////////////////////////////////
// 重载运算符=，给矩阵赋值
//
// 参数：
// 1. const CMatrix& other - 用于给矩阵赋值的源矩阵
//
// 返回值：CMatrix型的引用，所引用的矩阵与other相等
//////////////////////////////////////////////////////////////////////
CMatrix& CMatrix::operator=(const CMatrix& other)
{
	if (&other != this)
	{
		BOOL bSuccess = Init(other.GetNumRows(), 
			other.GetNumColumns());
		ASSERT(bSuccess);
		
		// copy the pointer
		memcpy(m_pData, other.m_pData, 
			sizeof(double)*m_nNumColumns*m_nNumRows);
	}
	
	// finally return a reference to ourselves
	return *this ;
}

//////////////////////////////////////////////////////////////////////
// 重载运算符==，判断矩阵是否相等
//
// 参数：
// 1. const CMatrix& other - 用于比较的矩阵
//
// 返回值：BOOL 型，两个矩阵相等则为TRUE，否则为FALSE
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::operator==(const CMatrix& other) const
{
	// 首先检查行列数是否相等
	if (m_nNumColumns != other.GetNumColumns() || m_nNumRows != 
		other.GetNumRows())
		return FALSE;
	
	for (int i=0; i<m_nNumRows; ++i)
	{
		for (int j=0; j<m_nNumColumns; ++j)
		{
			if (GetElement(i, j) != other.GetElement(i, j))
				return FALSE;
		}
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 重载运算符!=，判断矩阵是否不相等
//
// 参数：
// 1. const CMatrix& other - 用于比较的矩阵
//
// 返回值：BOOL 型，两个不矩阵相等则为TRUE，否则为FALSE
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::operator!=(const CMatrix& other) const
{
	return !(*this == other);
}

//////////////////////////////////////////////////////////////////////
// 重载运算符+，实现矩阵的加法
//
// 参数：
// 1. const CMatrix& other - 与指定矩阵相加的矩阵
//
// 返回值：CMatrix型，指定矩阵与other相加之和
//////////////////////////////////////////////////////////////////////
CMatrix CMatrix::operator+(const CMatrix& other) const
{
	// 首先检查行列数是否相等
	ASSERT (m_nNumColumns == other.GetNumColumns() && m_nNumRows == 
		other.GetNumRows());
	
	// 构造结果矩阵
	CMatrix result(*this) ;         // 拷贝构造
	// 矩阵加法
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j <  m_nNumColumns; ++j)
			result.SetElement(i, j, result.GetElement(i, j) + 
			other.GetElement(i, j)) ;
	}
	
	return result ;
}

//////////////////////////////////////////////////////////////////////
// 重载运算符-，实现矩阵的减法
//
// 参数：
// 1. const CMatrix& other - 与指定矩阵相减的矩阵
//
// 返回值：CMatrix型，指定矩阵与other相减之差
//////////////////////////////////////////////////////////////////////
CMatrix CMatrix::operator-(const CMatrix& other) const
{
	// 首先检查行列数是否相等
	ASSERT (m_nNumColumns == other.GetNumColumns() && m_nNumRows == 
		other.GetNumRows());
	
	// 构造目标矩阵
	CMatrix result(*this) ;         // copy ourselves
	// 进行减法操作
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j <  m_nNumColumns; ++j)
			result.SetElement(i, j, result.GetElement(i, j) - 
			other.GetElement(i, j)) ;
	}
	
	return result ;
}

//////////////////////////////////////////////////////////////////////
// 重载运算符*，实现矩阵的数乘
//
// 参数：
// 1. double value - 与指定矩阵相乘的实数
//
// 返回值：CMatrix型，指定矩阵与value相乘之积
//////////////////////////////////////////////////////////////////////
CMatrix CMatrix::operator*(double value) const
{
	// 构造目标矩阵
	CMatrix result(*this) ;         // copy ourselves
	// 进行数乘
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j <  m_nNumColumns; ++j)
			result.SetElement(i, j, result.GetElement(i, j) * 
			value) ;
	}
	
	return result ;
}

//////////////////////////////////////////////////////////////////////
// 重载运算符*，实现矩阵的乘法
//
// 参数：
// 1. const CMatrix& other - 与指定矩阵相乘的矩阵
//
// 返回值：CMatrix型，指定矩阵与other相乘之积
//////////////////////////////////////////////////////////////////////
CMatrix CMatrix::operator*(const CMatrix& other) const
{
	// 首先检查行列数是否符合要求
	ASSERT (m_nNumColumns == other.GetNumRows());
	
	// construct the object we are going to return
	CMatrix result(m_nNumRows, other.GetNumColumns()) ;
	
	// 矩阵乘法，即
	//
	// [A][B][C]   [G][H]     [A*G + B*I + C*K][A*H + B*J + C*L]
	// [D][E][F] * [I][J] =   [D*G + E*I + F*K][D*H + E*J + F*L]
	//             [K][L]
	//
	double  value ;
	for (int i = 0 ; i < result.GetNumRows() ; ++i)
	{
		for (int j = 0 ; j < other.GetNumColumns() ; ++j)
		{
			value = 0.0 ;
			for (int k = 0 ; k < m_nNumColumns ; ++k)
			{
				value += GetElement(i, k) * 
					other.GetElement(k, j) ;
			}
			
			result.SetElement(i, j, value) ;
		}
	}
	
	return result ;
}

//////////////////////////////////////////////////////////////////////
// 复矩阵的乘法
//
// 参数：
// 1. const CMatrix& AR - 左边复矩阵的实部矩阵
// 2. const CMatrix& AI - 左边复矩阵的虚部矩阵
// 3. const CMatrix& BR - 右边复矩阵的实部矩阵
// 4. const CMatrix& BI - 右边复矩阵的虚部矩阵
// 5. CMatrix& CR - 乘积复矩阵的实部矩阵
// 6. CMatrix& CI - 乘积复矩阵的虚部矩阵
//
// 返回值：BOOL型，复矩阵乘法是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::CMul(const CMatrix& AR, const CMatrix& AI, const CMatrix& BR, 
				   const CMatrix& BI, CMatrix& CR, CMatrix& CI) const
{
	// 首先检查行列数是否符合要求
	if (AR.GetNumColumns() != AI.GetNumColumns() ||
		AR.GetNumRows() != AI.GetNumRows() ||
		BR.GetNumColumns() != BI.GetNumColumns() ||
		BR.GetNumRows() != BI.GetNumRows() ||
		AR.GetNumColumns() != BR.GetNumRows())
		return FALSE;
	
	// 构造乘积矩阵实部矩阵和虚部矩阵
	CMatrix mtxCR(AR.GetNumRows(), BR.GetNumColumns()), 
		mtxCI(AR.GetNumRows(), BR.GetNumColumns());
	// 复矩阵相乘
    for (int i=0; i<AR.GetNumRows(); ++i)
	{
		for (int j=0; j<BR.GetNumColumns(); ++j)
		{
			double vr = 0;
			double vi = 0;
            for (int k =0; k<AR.GetNumColumns(); ++k)
			{
                double p = AR.GetElement(i, k) * BR.GetElement(k, j);
                double q = AI.GetElement(i, k) * BI.GetElement(k, j);
                double s = (AR.GetElement(i, k) + AI.GetElement(i, k)) * 
					(BR.GetElement(k, j) + BI.GetElement(k, j));
                vr += p - q;
                vi += s - p - q;
			}
            mtxCR.SetElement(i, j, vr);
            mtxCI.SetElement(i, j, vi);
        }
	}
	
	CR = mtxCR;
	CI = mtxCI;
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 矩阵的转置
//
// 参数：无
//
// 返回值：CMatrix型，指定矩阵转置矩阵
//////////////////////////////////////////////////////////////////////
CMatrix CMatrix::Transpose() const
{
	// 构造目标矩阵
	CMatrix Trans(m_nNumColumns, m_nNumRows);
	
	// 转置各元素
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j < m_nNumColumns ; ++j)
			Trans.SetElement(j, i, GetElement(i, j)) ;
	}
	
	return Trans;
}

//////////////////////////////////////////////////////////////////////
// 实矩阵求逆的全选主元高斯－约当法
//
// 参数：无
//
// 返回值：BOOL型，求逆是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::InvertGaussJordan()
{
	int *pnRow, *pnCol,i,j,k,l,u,v;
    double d = 0, p = 0;
	
	// 分配内存
    pnRow = new int[m_nNumColumns];
    pnCol = new int[m_nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return FALSE;
	
	// 消元
    for (k=0; k<=m_nNumColumns-1; k++)
    { 
		d=0.0;
        for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				l=i*m_nNumColumns+j; p=fabs(m_pData[l]);
				if (p>d) 
				{ 
					d=p; 
					//保存绝对值最大的值的位置
					pnRow[k]=i; 
					pnCol[k]=j;
				}
			}
		}
        
		// 失败
		if (d == 0.0)
		{
			delete[] pnRow;
			delete[] pnCol;
			return FALSE;
		}
		
        if (pnRow[k] != k)//如果绝对值最大的项不在第k行
		{
			for (j=0; j<=m_nNumColumns-1; j++)//将该行和第k行交换
			{ 
				u=k*m_nNumColumns+j; 
				v=pnRow[k]*m_nNumColumns+j;
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
			}
		}
        
		if (pnCol[k] != k)//如果绝对值最大的项不在第k列
		{
			for (i=0; i<=m_nNumColumns-1; i++)//将该列河第k列交换
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnCol[k];
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
            }
		}
		//此时k行第k列的项绝对值最大
        l=k*m_nNumColumns+k;//得到第k行第k列在数组中的位置
        m_pData[l]=1.0/m_pData[l];//该项取倒数
        for (j=0; j<=m_nNumColumns-1; j++)//第k行的其他项 * 1/m_pData[k][k]
		{
			if (j != k)
            { 
				u=k*m_nNumColumns+j; 
				m_pData[u]=m_pData[u]*m_pData[l];
			}
		}

        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
			{
				for (j=0; j<=m_nNumColumns-1; j++)
				{
					if (j!=k)
					{ 
						u=i*m_nNumColumns+j;
						//m_pData[i][j] = m_pData[i][j] - m_pData[i][k] * m_pData[k][j];
						m_pData[u]=m_pData[u]-m_pData[i*m_nNumColumns+k]*m_pData[k*m_nNumColumns+j];
					}
                }
			}
		}
		//m_pData[][k](第k列) = m_pData[][k] * 1/m_pData[k][k]
        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
            { 
				u=i*m_nNumColumns+k; 
				m_pData[u]=-m_pData[u]*m_pData[l];
			}
		}
    }
	
    // 调整恢复行列次序
    for (k=m_nNumColumns-1; k>=0; k--)
    { 
		if (pnCol[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=pnCol[k]*m_nNumColumns+j;
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
            }
		}
		
        if (pnRow[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnRow[k];
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
            }
		}
    }
	
	// 清理内存
	delete[] pnRow;
	delete[] pnCol;
	
	// 成功返回
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 复矩阵求逆的全选主元高斯－约当法
//
// 参数：
// 1. CMatrix& mtxImag - 复矩阵的虚部矩阵，当前矩阵为复矩阵的实部
//
// 返回值：BOOL型，求逆是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::InvertGaussJordan(CMatrix& mtxImag)
{
	int *pnRow,*pnCol,i,j,k,l,u,v,w;
    double p,q,s,t,d,b;
	
	// 分配内存
    pnRow = new int[m_nNumColumns];
    pnCol = new int[m_nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return FALSE;
	
	// 消元
    for (k=0; k<=m_nNumColumns-1; k++)
    { 
		d=0.0;
        for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				u=i*m_nNumColumns+j;
				
				p=m_pData[u]*m_pData[u]+mtxImag.m_pData[u]*mtxImag.m_pData[u];
				if (p>d) 
				{ 
					d=p; 
					pnRow[k]=i; 
					pnCol[k]=j;
				}
			}
		}
		
		// 失败
        if (d == 0.0)
        { 
			delete[] pnRow;
			delete[] pnCol;
            return(0);
        }
		
        if (pnRow[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=pnRow[k]*m_nNumColumns+j;
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}
		
        if (pnCol[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnCol[k];
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}
		
        l=k*m_nNumColumns+k;
        m_pData[l]=m_pData[l]/d; mtxImag.m_pData[l]=-mtxImag.m_pData[l]/d;
        for (j=0; j<=m_nNumColumns-1; j++)
		{
			if (j!=k)
            { 
				u=k*m_nNumColumns+j;
				p=m_pData[u]*m_pData[l]; 
				q=mtxImag.m_pData[u]*mtxImag.m_pData[l];
				
				s=(m_pData[u]+mtxImag.m_pData[u])*(m_pData[l]+mtxImag.m_pData[l]);
				m_pData[u]=p-q; 
				mtxImag.m_pData[u]=s-p-q;
            }
		}
		
        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
            { 
				v=i*m_nNumColumns+k;
				for (j=0; j<=m_nNumColumns-1; j++)
				{
					if (j!=k)
					{ 
						u=k*m_nNumColumns+j;  
						w=i*m_nNumColumns+j;
						p=m_pData[u]*m_pData[v]; 
						
						q=mtxImag.m_pData[u]*mtxImag.m_pData[v];
						
						s=(m_pData[u]+mtxImag.m_pData[u])*(m_pData[v]+mtxImag.m_pData[v]);
						t=p-q; 
						b=s-p-q;
						m_pData[w]=m_pData[w]-t;
						
						mtxImag.m_pData[w]=mtxImag.m_pData[w]-b;
					}
				}
            }
		}
		
        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
            { 
				u=i*m_nNumColumns+k;
				p=m_pData[u]*m_pData[l]; 
				q=mtxImag.m_pData[u]*mtxImag.m_pData[l];
				
				s=(m_pData[u]+mtxImag.m_pData[u])*(m_pData[l]+mtxImag.m_pData[l]);
				m_pData[u]=q-p; 
				mtxImag.m_pData[u]=p+q-s;
            }
		}
    }
	
    // 调整恢复行列次序
    for (k=m_nNumColumns-1; k>=0; k--)
    { 
		if (pnCol[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=pnCol[k]*m_nNumColumns+j;
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}
		
        if (pnRow[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnRow[k];
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}
    }
	
	// 清理内存
	delete[] pnRow;
	delete[] pnCol;
	
	// 成功返回
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 对称正定矩阵的求逆
//
// 参数：无
//
// 返回值：BOOL型，求逆是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::InvertSsgj()
{ 
	int i, j ,k, m;
    double w, g, *pTmp;
	
	// 临时内存
    pTmp = new double[m_nNumColumns];
	
	// 逐列处理
    for (k=0; k<=m_nNumColumns-1; k++)
    { 
		w=m_pData[0];
        if (w == 0.0)
        { 
			delete[] pTmp;
			return FALSE;
		}
		
        m=m_nNumColumns-k-1;
        for (i=1; i<=m_nNumColumns-1; i++)
        { 
			g=m_pData[i*m_nNumColumns]; 
			pTmp[i]=g/w;
            if (i<=m) 
				pTmp[i]=-pTmp[i];
            for (j=1; j<=i; j++)
				
				m_pData[(i-1)*m_nNumColumns+j-1]=m_pData[i*m_nNumColumns+j]+g*pTmp[j];
        }
		
        m_pData[m_nNumColumns*m_nNumColumns-1]=1.0/w;
        for (i=1; i<=m_nNumColumns-1; i++)
			m_pData[(m_nNumColumns-1)*m_nNumColumns+i-1]=pTmp[i];
    }
	
	// 行列调整
    for (i=0; i<=m_nNumColumns-2; i++)
		for (j=i+1; j<=m_nNumColumns-1; j++)
			m_pData[i*m_nNumColumns+j]=m_pData[j*m_nNumColumns+i];
		
        // 临时内存清理
        delete[] pTmp;
		
        return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 托伯利兹矩阵求逆的埃兰特方法
//
// 参数：无
//
// 返回值：BOOL型，求逆是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::InvertTrench()
{ 
	int i,j,k;
    double a,s,*t,*tt,*c,*r,*p;
	
	// 上三角元素
	t = new double[m_nNumColumns];
	// 下三角元素
	tt = new double[m_nNumColumns];
	
	// 上、下三角元素赋值
	for (i=0; i<m_nNumColumns; ++i)
	{
		t[i] = GetElement(0, i);
		tt[i] = GetElement(i, 0);
	}
	
	// 临时缓冲区
	c = new double[m_nNumColumns];
	r = new double[m_nNumColumns];
	p = new double[m_nNumColumns];
	
	// 非Toeplitz矩阵，返回
    if (t[0] == 0.0)
    { 
		delete[] t;
		delete[] tt;
		delete[] c;
		delete[] r;
		delete[] p;
		return FALSE;
    }
	
    a=t[0]; 
	c[0]=tt[1]/t[0]; 
	r[0]=t[1]/t[0];
	
    for (k=0; k<=m_nNumColumns-3; k++)
    { 
		s=0.0;
        for (j=1; j<=k+1; j++)
			s=s+c[k+1-j]*tt[j];
		
        s=(s-tt[k+2])/a;
		for (i=0; i<=k; i++)
			p[i]=c[i]+s*r[k-i];
		
        c[k+1]=-s;
        s=0.0;
        for (j=1; j<=k+1; j++)
			s=s+r[k+1-j]*t[j];
        
		s=(s-t[k+2])/a;
        for (i=0; i<=k; i++)
        { 
			r[i]=r[i]+s*c[k-i];
            c[k-i]=p[k-i];
        }
		
        r[k+1]=-s;
		a=0.0;
        for (j=1; j<=k+2; j++)
			a=a+t[j]*c[j-1];
		
        a=t[0]-a;
		
		// 求解失败
        if (a == 0.0)
		{ 
			delete[] t;
			delete[] tt;
			delete[] c;
			delete[] r;
			delete[] p;
			return FALSE;
		}
    }
	
    m_pData[0]=1.0/a;
    for (i=0; i<=m_nNumColumns-2; i++)
    { 
		k=i+1; 
		j=(i+1)*m_nNumColumns;
        m_pData[k]=-r[i]/a; 
		m_pData[j]=-c[i]/a;
    }
	
	for (i=0; i<=m_nNumColumns-2; i++)
	{
		for (j=0; j<=m_nNumColumns-2; j++)
		{ 
			k=(i+1)*m_nNumColumns+j+1;
			
			m_pData[k]=m_pData[i*m_nNumColumns+j]-c[i]*m_pData[j+1];
			
			m_pData[k]=m_pData[k]+c[m_nNumColumns-j-2]*m_pData[m_nNumColumns-i-1];
		}
	}
	
    // 临时内存清理
	delete[] t;
	delete[] tt;
	delete[] c;
	delete[] r;
	delete[] p;
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 求行列式值的全选主元高斯消去法
//
// 参数：无
//
// 返回值：double型，行列式的值
//////////////////////////////////////////////////////////////////////
double CMatrix::DetGauss()
{ 
	int i,j,k,is,js,l,u,v;
    double f,det,q,d;
    
	// 初值
	f=1.0; 
	det=1.0;
    
	// 消元
	for (k=0; k<=m_nNumColumns-2; k++)
    { 
		q=0.0;
        for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				l=i*m_nNumColumns+j; 
				d=fabs(m_pData[l]);
				if (d>q) 
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
		}
		
        if (q == 0.0)
        { 
			det=0.0; 
			return(det);
		}
        
		if (is!=k)
        { 
			f=-f;
            for (j=k; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=is*m_nNumColumns+j;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
        
		if (js!=k)
        { 
			f=-f;
            for (i=k; i<=m_nNumColumns-1; i++)
            {
				u=i*m_nNumColumns+js; 
				v=i*m_nNumColumns+k;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
		
        l=k*m_nNumColumns+k;
        det=det*m_pData[l];
        for (i=k+1; i<=m_nNumColumns-1; i++)
        { 
			d=m_pData[i*m_nNumColumns+k]/m_pData[l];
            for (j=k+1; j<=m_nNumColumns-1; j++)
            { 
				u=i*m_nNumColumns+j;
                m_pData[u]=m_pData[u]-d*m_pData[k*m_nNumColumns+j];
            }
        }
    }
    
	// 求值
	det=f*det*m_pData[m_nNumColumns*m_nNumColumns-1];
	
    return(det);
}

//////////////////////////////////////////////////////////////////////
// 求矩阵秩的全选主元高斯消去法
//
// 参数：无
//
// 返回值：int型，矩阵的秩
//////////////////////////////////////////////////////////////////////
int CMatrix::RankGauss()
{ 
	int i,j,k,nn,is,js,l,ll,u,v;
    double q,d;
    
	// 秩小于等于行列数
	nn = m_nNumRows;
    if (m_nNumRows >= m_nNumColumns) 
		nn = m_nNumColumns;
	
    k=0;
	
	// 消元求解
    for (l=0; l<=nn-1; l++)
    { 
		q=0.0;
        for (i=l; i<=m_nNumRows-1; i++)
		{
			for (j=l; j<=m_nNumColumns-1; j++)
			{ 
				ll=i*m_nNumColumns+j; 
				d=fabs(m_pData[ll]);
				if (d>q) 
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
		}
		
        if (q == 0.0) 
			return(k);
		
        k=k+1;
        if (is!=l)
        { 
			for (j=l; j<=m_nNumColumns-1; j++)
            { 
				u=l*m_nNumColumns+j; 
				v=is*m_nNumColumns+j;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
        if (js!=l)
        { 
			for (i=l; i<=m_nNumRows-1; i++)
            { 
				u=i*m_nNumColumns+js; 
				v=i*m_nNumColumns+l;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
        
		ll=l*m_nNumColumns+l;
        for (i=l+1; i<=m_nNumColumns-1; i++)
        { 
			d=m_pData[i*m_nNumColumns+l]/m_pData[ll];
            for (j=l+1; j<=m_nNumColumns-1; j++)
            { 
				u=i*m_nNumColumns+j;
                m_pData[u]=m_pData[u]-d*m_pData[l*m_nNumColumns+j];
            }
        }
    }
    
	return(k);
}

//////////////////////////////////////////////////////////////////////
// 对称正定矩阵的乔里斯基分解与行列式的求值
//
// 参数：
// 1. double* dblDet - 返回行列式的值
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::DetCholesky(double* dblDet)
{ 
	int i,j,k,u,l;
    double d;
    
	// 不满足求解要求
	if (m_pData[0] <= 0.0)
		return FALSE;
	
	// 乔里斯基分解
	
    m_pData[0]=sqrt(m_pData[0]);
    d=m_pData[0];
	
    for (i=1; i<=m_nNumColumns-1; i++)
    { 
		u=i*m_nNumColumns; 
		m_pData[u]=m_pData[u]/m_pData[0];
	}
    
	for (j=1; j<=m_nNumColumns-1; j++)
    { 
		l=j*m_nNumColumns+j;
        for (k=0; k<=j-1; k++)
        { 
			u=j*m_nNumColumns+k; 
			m_pData[l]=m_pData[l]-m_pData[u]*m_pData[u];
		}
        
		if (m_pData[l] <= 0.0)
			return FALSE;
		
        m_pData[l]=sqrt(m_pData[l]);
        d=d*m_pData[l];
        
		for (i=j+1; i<=m_nNumColumns-1; i++)
        { 
			u=i*m_nNumColumns+j;
            for (k=0; k<=j-1; k++)
				
				m_pData[u]=m_pData[u]-m_pData[i*m_nNumColumns+k]*m_pData[j*m_nNumColumns+k];
            
			m_pData[u]=m_pData[u]/m_pData[l];
        }
    }
    
	// 行列式求值
	*dblDet=d*d;
    
	// 下三角矩阵
    for (i=0; i<=m_nNumColumns-2; i++)
		for (j=i+1; j<=m_nNumColumns-1; j++)
			m_pData[i*m_nNumColumns+j]=0.0;
		
        return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 矩阵的三角分解，分解成功后，原矩阵将成为Q矩阵
//
// 参数：
// 1. CMatrix& mtxL - 返回分解后的L矩阵
// 2. CMatrix& mtxU - 返回分解后的U矩阵
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::SplitLU(CMatrix& mtxL, CMatrix& mtxU)
{ 
	int i,j,k,w,v,ll;
    
	// 初始化结果矩阵
	if (! mtxL.Init(m_nNumColumns, m_nNumColumns) ||
		! mtxU.Init(m_nNumColumns, m_nNumColumns))
		return FALSE;
	
	for (k=0; k<=m_nNumColumns-2; k++)
    { 
		ll=k*m_nNumColumns+k;
		if (m_pData[ll] == 0.0)
			return FALSE;
		
        for (i=k+1; i<=m_nNumColumns-1; i++)
		{ 
			w=i*m_nNumColumns+k; 
			m_pData[w]=m_pData[w]/m_pData[ll];
		}
		
        for (i=k+1; i<=m_nNumColumns-1; i++)
        { 
			w=i*m_nNumColumns+k;
            for (j=k+1; j<=m_nNumColumns-1; j++)
            { 
				v=i*m_nNumColumns+j;
                m_pData[v]=m_pData[v]-m_pData[w]*m_pData[k*m_nNumColumns+j];
            }
        }
    }
    
	for (i=0; i<=m_nNumColumns-1; i++)
    {
		for (j=0; j<i; j++)
        { 
			w=i*m_nNumColumns+j; 
			mtxL.m_pData[w]=m_pData[w]; 
			mtxU.m_pData[w]=0.0;
		}
		
        w=i*m_nNumColumns+i;
        mtxL.m_pData[w]=1.0; 
		mtxU.m_pData[w]=m_pData[w];
        
		for (j=i+1; j<=m_nNumColumns-1; j++)
        { 
			w=i*m_nNumColumns+j; 
			mtxL.m_pData[w]=0.0; 
			mtxU.m_pData[w]=m_pData[w];
		}
    }
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 一般实矩阵的QR分解，分解成功后，原矩阵将成为R矩阵
//
// 参数：
// 1. CMatrix& mtxQ - 返回分解后的Q矩阵
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::SplitQR(CMatrix& mtxQ)
{ 
	int i,j,k,l,nn,p,jj;
    double u,alpha,w,t;
    
	if (m_nNumRows < m_nNumColumns)
		return FALSE;
	
	// 初始化Q矩阵
	if (! mtxQ.Init(m_nNumRows, m_nNumRows))
		return FALSE;
	
	// 对角线元素单位化
    for (i=0; i<=m_nNumRows-1; i++)
	{
		for (j=0; j<=m_nNumRows-1; j++)
		{ 
			l=i*m_nNumRows+j; 
			mtxQ.m_pData[l]=0.0;
			if (i==j) 
				mtxQ.m_pData[l]=1.0;
		}
	}
	
	// 开始分解
	
    nn=m_nNumColumns;
    if (m_nNumRows == m_nNumColumns) 
		nn=m_nNumRows-1;
	
    for (k=0; k<=nn-1; k++)
    { 
		u=0.0; 
		l=k*m_nNumColumns+k;
        for (i=k; i<=m_nNumRows-1; i++)
        { 
			w=fabs(m_pData[i*m_nNumColumns+k]);
            if (w>u) 
				u=w;
        }
        
		alpha=0.0;
        for (i=k; i<=m_nNumRows-1; i++)
        { 
			t=m_pData[i*m_nNumColumns+k]/u; 
			alpha=alpha+t*t;
		}
		
        if (m_pData[l]>0.0) 
			u=-u;
		
        alpha=u*sqrt(alpha);
        if (alpha == 0.0)
			return FALSE;
		
        u=sqrt(2.0*alpha*(alpha-m_pData[l]));
        if ((u+1.0)!=1.0)
        { 
			m_pData[l]=(m_pData[l]-alpha)/u;
            for (i=k+1; i<=m_nNumRows-1; i++)
            { 
				p=i*m_nNumColumns+k; 
				m_pData[p]=m_pData[p]/u;
			}
            
			for (j=0; j<=m_nNumRows-1; j++)
            { 
				t=0.0;
                for (jj=k; jj<=m_nNumRows-1; jj++)
					
					t=t+m_pData[jj*m_nNumColumns+k]*mtxQ.m_pData[jj*m_nNumRows+j];
				
                for (i=k; i<=m_nNumRows-1; i++)
                { 
					p=i*m_nNumRows+j; 
					
					mtxQ.m_pData[p]=mtxQ.m_pData[p]-2.0*t*m_pData[i*m_nNumColumns+k];
				}
            }
            
			for (j=k+1; j<=m_nNumColumns-1; j++)
            { 
				t=0.0;
                
				for (jj=k; jj<=m_nNumRows-1; jj++)
					
					t=t+m_pData[jj*m_nNumColumns+k]*m_pData[jj*m_nNumColumns+j];
                
				for (i=k; i<=m_nNumRows-1; i++)
                { 
					p=i*m_nNumColumns+j; 
					
					m_pData[p]=m_pData[p]-2.0*t*m_pData[i*m_nNumColumns+k];
				}
            }
            
			m_pData[l]=alpha;
            for (i=k+1; i<=m_nNumRows-1; i++)
				m_pData[i*m_nNumColumns+k]=0.0;
        }
    }
    
	// 调整元素
	for (i=0; i<=m_nNumRows-2; i++)
	{
		for (j=i+1; j<=m_nNumRows-1;j++)
		{ 
			p=i*m_nNumRows+j; 
			l=j*m_nNumRows+i;
			t=mtxQ.m_pData[p]; 
			mtxQ.m_pData[p]=mtxQ.m_pData[l]; 
			mtxQ.m_pData[l]=t;
		}
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 一般实矩阵的奇异值分解，分解成功后，原矩阵对角线元素就是矩阵的奇异值
//
// 参数：
// 1. CMatrix& mtxU - 返回分解后的U矩阵
// 2. CMatrix& mtxV - 返回分解后的V矩阵
// 3. double eps - 计算精度，默认值为0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::SplitUV(CMatrix& mtxU, CMatrix& mtxV, double eps /*= 0.000001*/)
{ 
	int i,j,k,l,it,ll,kk,ix,iy,mm,nn,iz,m1,ks;
    double d,dd,t,sm,sm1,em1,sk,ek,b,c,shh,fg[2],cs[2];
    double *s,*e,*w;
	
	int m = m_nNumRows;
	int n = m_nNumColumns;
	
	// 初始化U, V矩阵
	if (! mtxU.Init(m, m) || ! mtxV.Init(n, n))
		return FALSE;
	
	// 临时缓冲区
	int ka = max(m, n) + 1;
    s = new double[ka];
    e = new double[ka];
    w = new double[ka];
	
	// 指定迭代次数为60
    it=60; 
	k=n;
	
    if (m-1<n) 
		k=m-1;
	
    l=m;
    if (n-2<m) 
		l=n-2;
    if (l<0) 
		l=0;
	
	// 循环迭代计算
    ll=k;
    if (l>k) 
		ll=l;
    if (ll>=1)
    { 
		for (kk=1; kk<=ll; kk++)
        { 
			if (kk<=k)
            { 
				d=0.0;
                for (i=kk; i<=m; i++)
                { 
					ix=(i-1)*n+kk-1; 
					d=d+m_pData[ix]*m_pData[ix];
				}
				
                s[kk-1]=sqrt(d);
                if (s[kk-1]!=0.0)
                { 
					ix=(kk-1)*n+kk-1;
                    if (m_pData[ix]!=0.0)
                    { 
						s[kk-1]=fabs(s[kk-1]);
                        if (m_pData[ix]<0.0) 
							s[kk-1]=-s[kk-1];
                    }
                    
					for (i=kk; i<=m; i++)
                    { 
						iy=(i-1)*n+kk-1;
                        m_pData[iy]=m_pData[iy]/s[kk-1];
                    }
                    
					m_pData[ix]=1.0+m_pData[ix];
                }
                
				s[kk-1]=-s[kk-1];
            }
            
			if (n>=kk+1)
            { 
				for (j=kk+1; j<=n; j++)
                { 
					if ((kk<=k)&&(s[kk-1]!=0.0))
                    { 
						d=0.0;
                        for (i=kk; i<=m; i++)
                        { 
							ix=(i-1)*n+kk-1;
                            iy=(i-1)*n+j-1;
                            d=d+m_pData[ix]*m_pData[iy];
                        }
                        
						d=-d/m_pData[(kk-1)*n+kk-1];
                        for (i=kk; i<=m; i++)
                        { 
							ix=(i-1)*n+j-1;
                            iy=(i-1)*n+kk-1;
                            m_pData[ix]=m_pData[ix]+d*m_pData[iy];
                        }
                    }
                    
					e[j-1]=m_pData[(kk-1)*n+j-1];
                }
            }
            
			if (kk<=k)
            { 
				for (i=kk; i<=m; i++)
                { 
					ix=(i-1)*m+kk-1; 
					iy=(i-1)*n+kk-1;
                    mtxU.m_pData[ix]=m_pData[iy];
                }
            }
            
			if (kk<=l)
            { 
				d=0.0;
                for (i=kk+1; i<=n; i++)
					d=d+e[i-1]*e[i-1];
                
				e[kk-1]=sqrt(d);
                if (e[kk-1]!=0.0)
                { 
					if (e[kk]!=0.0)
                    { 
						e[kk-1]=fabs(e[kk-1]);
                        if (e[kk]<0.0) 
							e[kk-1]=-e[kk-1];
                    }
					
                    for (i=kk+1; i<=n; i++)
						e[i-1]=e[i-1]/e[kk-1];
                    
					e[kk]=1.0+e[kk];
                }
                
				e[kk-1]=-e[kk-1];
                if ((kk+1<=m)&&(e[kk-1]!=0.0))
                { 
					for (i=kk+1; i<=m; i++) 
						w[i-1]=0.0;
                    
					for (j=kk+1; j<=n; j++)
						for (i=kk+1; i<=m; i++)
							
							w[i-1]=w[i-1]+e[j-1]*m_pData[(i-1)*n+j-1];
						
						for (j=kk+1; j<=n; j++)
						{
							for (i=kk+1; i<=m; i++)
							{ 
								ix=(i-1)*n+j-1;
								
								m_pData[ix]=m_pData[ix]-w[i-1]*e[j-1]/e[kk];
							}
						}
                }
                
				for (i=kk+1; i<=n; i++)
					mtxV.m_pData[(i-1)*n+kk-1]=e[i-1];
            }
        }
    }
    
	mm=n;
    if (m+1<n) 
		mm=m+1;
    if (k<n) 
		s[k]=m_pData[k*n+k];
    if (m<mm) 
		s[mm-1]=0.0;
    if (l+1<mm) 
		e[l]=m_pData[l*n+mm-1];
	
    e[mm-1]=0.0;
    nn=m;
    if (m>n) 
		nn=n;
    if (nn>=k+1)
    { 
		for (j=k+1; j<=nn; j++)
        { 
			for (i=1; i<=m; i++)
				mtxU.m_pData[(i-1)*m+j-1]=0.0;
            mtxU.m_pData[(j-1)*m+j-1]=1.0;
        }
    }
    
	if (k>=1)
    { 
		for (ll=1; ll<=k; ll++)
        { 
			kk=k-ll+1; 
			iz=(kk-1)*m+kk-1;
            if (s[kk-1]!=0.0)
            { 
				if (nn>=kk+1)
				{
					for (j=kk+1; j<=nn; j++)
					{ 
						d=0.0;
						for (i=kk; i<=m; i++)
						{ 
							ix=(i-1)*m+kk-1;
							iy=(i-1)*m+j-1;
							
							d=d+mtxU.m_pData[ix]*mtxU.m_pData[iy]/mtxU.m_pData[iz];
						}
						
						d=-d;
						for (i=kk; i<=m; i++)
						{ 
							ix=(i-1)*m+j-1;
							iy=(i-1)*m+kk-1;
							
							mtxU.m_pData[ix]=mtxU.m_pData[ix]+d*mtxU.m_pData[iy];
						}
					}
				}
				
				for (i=kk; i<=m; i++)
				{ 
					ix=(i-1)*m+kk-1; 
					mtxU.m_pData[ix]=-mtxU.m_pData[ix];
				}
				
				mtxU.m_pData[iz]=1.0+mtxU.m_pData[iz];
				if (kk-1>=1)
				{
					for (i=1; i<=kk-1; i++)
						
						mtxU.m_pData[(i-1)*m+kk-1]=0.0;
				}
			}
            else
            { 
				for (i=1; i<=m; i++)
					mtxU.m_pData[(i-1)*m+kk-1]=0.0;
                mtxU.m_pData[(kk-1)*m+kk-1]=1.0;
            }
		}
    }
	
    for (ll=1; ll<=n; ll++)
    { 
		kk=n-ll+1; 
		iz=kk*n+kk-1;
        
		if ((kk<=l)&&(e[kk-1]!=0.0))
        { 
			for (j=kk+1; j<=n; j++)
            { 
				d=0.0;
                for (i=kk+1; i<=n; i++)
                { 
					ix=(i-1)*n+kk-1; 
					iy=(i-1)*n+j-1;
                    d=d+mtxV.m_pData[ix]*mtxV.m_pData[iy]/mtxV.m_pData[iz];
                }
                
				d=-d;
                for (i=kk+1; i<=n; i++)
                { 
					ix=(i-1)*n+j-1; 
					iy=(i-1)*n+kk-1;
                    mtxV.m_pData[ix]=mtxV.m_pData[ix]+d*mtxV.m_pData[iy];
                }
            }
        }
        
		for (i=1; i<=n; i++)
			mtxV.m_pData[(i-1)*n+kk-1]=0.0;
        
		mtxV.m_pData[iz-n]=1.0;
    }
    
	for (i=1; i<=m; i++)
		for (j=1; j<=n; j++)
			m_pData[(i-1)*n+j-1]=0.0;
		
        m1=mm; 
        it=60;
		while (TRUE)
		{ 
			if (mm==0)
			{ 
				ppp(m_pData,e,s,mtxV.m_pData,m,n);
				return TRUE;
			}
			if (it==0)
			{ 
				ppp(m_pData,e,s,mtxV.m_pData,m,n);
				return FALSE;
			}
			
			kk=mm-1;
			while ((kk!=0)&&(fabs(e[kk-1])!=0.0))
			{ 
				d=fabs(s[kk-1])+fabs(s[kk]);
				dd=fabs(e[kk-1]);
				if (dd>eps*d) 
					kk=kk-1;
				else 
					e[kk-1]=0.0;
			}
			
			if (kk==mm-1)
			{ 
				kk=kk+1;
				if (s[kk-1]<0.0)
				{ 
					s[kk-1]=-s[kk-1];
					for (i=1; i<=n; i++)
					{ 
						ix=(i-1)*n+kk-1; 
						mtxV.m_pData[ix]=-mtxV.m_pData[ix];}
				}
				
				while ((kk!=m1)&&(s[kk-1]<s[kk]))
				{ 
					d=s[kk-1]; 
					s[kk-1]=s[kk]; 
					s[kk]=d;
					if (kk<n)
					{
						for (i=1; i<=n; i++)
						{ 
							ix=(i-1)*n+kk-1; 
							iy=(i-1)*n+kk;
							d=mtxV.m_pData[ix]; 
							
							mtxV.m_pData[ix]=mtxV.m_pData[iy]; 
							mtxV.m_pData[iy]=d;
						}
					}
					
					if (kk<m)
					{
						for (i=1; i<=m; i++)
						{ 
							ix=(i-1)*m+kk-1; 
							iy=(i-1)*m+kk;
							d=mtxU.m_pData[ix]; 
							
							mtxU.m_pData[ix]=mtxU.m_pData[iy]; 
							mtxU.m_pData[iy]=d;
						}
					}
					
					kk=kk+1;
				}
				
				it=60;
				mm=mm-1;
			}
			else
			{ 
				ks=mm;
				while ((ks>kk)&&(fabs(s[ks-1])!=0.0))
				{ 
					d=0.0;
					if (ks!=mm) 
						d=d+fabs(e[ks-1]);
					if (ks!=kk+1) 
						d=d+fabs(e[ks-2]);
					
					dd=fabs(s[ks-1]);
					if (dd>eps*d) 
						ks=ks-1;
					else 
						s[ks-1]=0.0;
				}
				
				if (ks==kk)
				{ 
					kk=kk+1;
					d=fabs(s[mm-1]);
					t=fabs(s[mm-2]);
					if (t>d) 
						d=t;
					
					t=fabs(e[mm-2]);
					if (t>d) 
						d=t;
					
					t=fabs(s[kk-1]);
					if (t>d) 
						d=t;
					
					t=fabs(e[kk-1]);
					if (t>d) 
						d=t;
					
					sm=s[mm-1]/d; 
					sm1=s[mm-2]/d;
					em1=e[mm-2]/d;
					sk=s[kk-1]/d; 
					ek=e[kk-1]/d;
					b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
					c=sm*em1; 
					c=c*c; 
					shh=0.0;
					
					if ((b!=0.0)||(c!=0.0))
					{ 
						shh=sqrt(b*b+c);
						if (b<0.0) 
							shh=-shh;
						
						shh=c/(b+shh);
					}
					
					fg[0]=(sk+sm)*(sk-sm)-shh;
					fg[1]=sk*ek;
					for (i=kk; i<=mm-1; i++)
					{ 
						sss(fg,cs);
						if (i!=kk) 
							e[i-2]=fg[0];
						
						fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
						e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
						fg[1]=cs[1]*s[i];
						s[i]=cs[0]*s[i];
						
						if ((cs[0]!=1.0)||(cs[1]!=0.0))
						{
							for (j=1; j<=n; j++)
							{ 
								ix=(j-1)*n+i-1;
								iy=(j-1)*n+i;
								
								d=cs[0]*mtxV.m_pData[ix]+cs[1]*mtxV.m_pData[iy];
								
								mtxV.m_pData[iy]=-cs[1]*mtxV.m_pData[ix]+cs[0]*mtxV.m_pData[iy];
								mtxV.m_pData[ix]=d;
							}
						}
						
						sss(fg,cs);
						s[i-1]=fg[0];
						fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
						s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
						fg[1]=cs[1]*e[i];
						e[i]=cs[0]*e[i];
						
						if (i<m)
						{
							if 
								((cs[0]!=1.0)||(cs[1]!=0.0))
							{
								for (j=1; j<=m; j++)
								{ 
									
									ix=(j-1)*m+i-1;
									iy=(j-1)*m+i;
									
									d=cs[0]*mtxU.m_pData[ix]+cs[1]*mtxU.m_pData[iy];
									
									mtxU.m_pData[iy]=-cs[1]*mtxU.m_pData[ix]+cs[0]*mtxU.m_pData[iy];
									
									mtxU.m_pData[ix]=d;
								}
							}
						}
					}
					
					e[mm-2]=fg[0];
					it=it-1;
				}
				else
				{ 
					if (ks==mm)
					{ 
						kk=kk+1;
						fg[1]=e[mm-2]; 
						e[mm-2]=0.0;
						for (ll=kk; ll<=mm-1; ll++)
						{ 
							i=mm+kk-ll-1;
							fg[0]=s[i-1];
							sss(fg,cs);
							s[i-1]=fg[0];
							if (i!=kk)
							{ 
								fg[1]=-cs[1]*e[i-2];
								e[i-2]=cs[0]*e[i-2];
							}
							
							if 
								((cs[0]!=1.0)||(cs[1]!=0.0))
							{
								for (j=1; j<=n; j++)
								{ 
									
									ix=(j-1)*n+i-1;
									
									iy=(j-1)*n+mm-1;
									
									d=cs[0]*mtxV.m_pData[ix]+cs[1]*mtxV.m_pData[iy];
									
									mtxV.m_pData[iy]=-cs[1]*mtxV.m_pData[ix]+cs[0]*mtxV.m_pData[iy];
									
									mtxV.m_pData[ix]=d;
								}
							}
						}
					}
					else
					{ 
						kk=ks+1;
						fg[1]=e[kk-2];
						e[kk-2]=0.0;
						for (i=kk; i<=mm; i++)
						{ 
							fg[0]=s[i-1];
							sss(fg,cs);
							s[i-1]=fg[0];
							fg[1]=-cs[1]*e[i-1];
							e[i-1]=cs[0]*e[i-1];
							if ((cs[0]!=1.0)||(cs[1]!=0.0))
							{
								for (j=1; j<=m; j++)
								{ 
									
									ix=(j-1)*m+i-1;
									
									iy=(j-1)*m+kk-2;
									
									d=cs[0]*mtxU.m_pData[ix]+cs[1]*mtxU.m_pData[iy];
									
									mtxU.m_pData[iy]=-cs[1]*mtxU.m_pData[ix]+cs[0]*mtxU.m_pData[iy];
									
									mtxU.m_pData[ix]=d;
								}
							}
						}
					}
				}
        }
    }
    
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 内部函数，由SplitUV函数调用
//////////////////////////////////////////////////////////////////////
void CMatrix::ppp(double a[], double e[], double s[], double v[], int m, int 
				  n)
{ 
	int i,j,p,q;
    double d;
	
    if (m>=n) 
		i=n;
    else 
		i=m;
	
    for (j=1; j<=i-1; j++)
    { 
		a[(j-1)*n+j-1]=s[j-1];
        a[(j-1)*n+j]=e[j-1];
    }
    
	a[(i-1)*n+i-1]=s[i-1];
    if (m<n) 
		a[(i-1)*n+i]=e[i-1];
    
	for (i=1; i<=n-1; i++)
	{
		for (j=i+1; j<=n; j++)
		{ 
			p=(i-1)*n+j-1; 
			q=(j-1)*n+i-1;
			d=v[p]; 
			v[p]=v[q]; 
			v[q]=d;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// 内部函数，由SplitUV函数调用
//////////////////////////////////////////////////////////////////////
void CMatrix::sss(double fg[2], double cs[2])
{ 
	double r,d;
    
	if ((fabs(fg[0])+fabs(fg[1]))==0.0)
    { 
		cs[0]=1.0; 
		cs[1]=0.0; 
		d=0.0;
	}
    else 
    { 
		d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);
        if (fabs(fg[0])>fabs(fg[1]))
        { 
			d=fabs(d);
            if (fg[0]<0.0) 
				d=-d;
        }
        if (fabs(fg[1])>=fabs(fg[0]))
        { 
			d=fabs(d);
            if (fg[1]<0.0) 
				d=-d;
        }
        
		cs[0]=fg[0]/d; 
		cs[1]=fg[1]/d;
    }
    
	r=1.0;
    if (fabs(fg[0])>fabs(fg[1])) 
		r=cs[1];
    else if (cs[0]!=0.0) 
		r=1.0/cs[0];
	
    fg[0]=d; 
	fg[1]=r;
}

//////////////////////////////////////////////////////////////////////
// 求广义逆的奇异值分解法，分解成功后，原矩阵对角线元素就是矩阵的奇异值
//
// 参数：
// 1. CMatrix& mtxAP - 返回原矩阵的广义逆矩阵
// 2. CMatrix& mtxU - 返回分解后的U矩阵
// 3. CMatrix& mtxV - 返回分解后的V矩阵
// 4. double eps - 计算精度，默认值为0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::GInvertUV(CMatrix& mtxAP, CMatrix& mtxU, CMatrix& mtxV, double 
						eps /*= 0.000001*/)
{ 
	int i,j,k,l,t,p,q,f;
	
	// 调用奇异值分解
    if (! SplitUV(mtxU, mtxV, eps))
		return FALSE;
	
	int m = m_nNumRows;
	int n = m_nNumColumns;
	
	// 初始化广义逆矩阵
	if (! mtxAP.Init(n, m))
		return FALSE;
	
	// 计算广义逆矩阵
	
    j=n;
    if (m<n) 
		j=m;
    j=j-1;
    k=0;
    while ((k<=j)&&(m_pData[k*n+k]!=0.0)) 
		k=k+1;
	
    k=k-1;
    for (i=0; i<=n-1; i++)
	{
		for (j=0; j<=m-1; j++)
		{ 
			t=i*m+j;        
			mtxAP.m_pData[t]=0.0;
			for (l=0; l<=k; l++)
			{ 
				f=l*n+i; 
				p=j*m+l; 
				q=l*n+l;
				
				mtxAP.m_pData[t]=mtxAP.m_pData[t]+mtxV.m_pData[f]*mtxU.m_pData[p]/m_pData[q];
			}
		}
	}
	
    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 约化对称矩阵为对称三对角阵的豪斯荷尔德变换法
//
// 参数：
// 1. CMatrix& mtxQ - 返回豪斯荷尔德变换的乘积矩阵Q
// 2. CMatrix& mtxT - 返回求得的对称三对角阵
// 3. double dblB[] - 一维数组，长度为矩阵的阶数，返回对称三对角阵的主对角线元素
// 4. double dblC[] - 一维数组，长度为矩阵的阶数，前n-1个元素返回对称三对角阵的次对角线元素
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::MakeSymTri(CMatrix& mtxQ, CMatrix& mtxT, double dblB[], double 
						 dblC[])
{ 
	int i,j,k,u;
    double h,f,g,h2;
    
	// 初始化矩阵Q和T
	if (! mtxQ.Init(m_nNumColumns, m_nNumColumns) ||
		! mtxT.Init(m_nNumColumns, m_nNumColumns))
		return FALSE;
	
	if (dblB == NULL || dblC == NULL)
		return FALSE;
	
	for (i=0; i<=m_nNumColumns-1; i++)
	{
		for (j=0; j<=m_nNumColumns-1; j++)
		{ 
			u=i*m_nNumColumns+j; 
			mtxQ.m_pData[u]=m_pData[u];
		}
	}
	
    for (i=m_nNumColumns-1; i>=1; i--)
    { 
		h=0.0;
        if (i>1)
		{
			for (k=0; k<=i-1; k++)
            { 
				u=i*m_nNumColumns+k; 
				h=h+mtxQ.m_pData[u]*mtxQ.m_pData[u];
			}
		}
		
        if (h == 0.0)
        { 
			dblC[i]=0.0;
            if (i==1) 
				dblC[i]=mtxQ.m_pData[i*m_nNumColumns+i-1];
            dblB[i]=0.0;
        }
        else
        { 
			dblC[i]=sqrt(h);
            u=i*m_nNumColumns+i-1;
            if (mtxQ.m_pData[u]>0.0) 
				dblC[i]=-dblC[i];
			
            h=h-mtxQ.m_pData[u]*dblC[i];
            mtxQ.m_pData[u]=mtxQ.m_pData[u]-dblC[i];
            f=0.0;
            for (j=0; j<=i-1; j++)
            { 
				
				mtxQ.m_pData[j*m_nNumColumns+i]=mtxQ.m_pData[i*m_nNumColumns+j]/h;
                g=0.0;
                for (k=0; k<=j; k++)
					
					g=g+mtxQ.m_pData[j*m_nNumColumns+k]*mtxQ.m_pData[i*m_nNumColumns+k];
				
				if (j+1<=i-1)
					for (k=j+1; k<=i-1; k++)
						
						g=g+mtxQ.m_pData[k*m_nNumColumns+j]*mtxQ.m_pData[i*m_nNumColumns+k];
					
					dblC[j]=g/h;
					f=f+g*mtxQ.m_pData[j*m_nNumColumns+i];
            }
            
			h2=f/(h+h);
            for (j=0; j<=i-1; j++)
            { 
				f=mtxQ.m_pData[i*m_nNumColumns+j];
                g=dblC[j]-h2*f;
                dblC[j]=g;
                for (k=0; k<=j; k++)
                { 
					u=j*m_nNumColumns+k;
                    
					mtxQ.m_pData[u]=mtxQ.m_pData[u]-f*dblC[k]-g*mtxQ.m_pData[i*m_nNumColumns+k];
                }
            }
            
			dblB[i]=h;
        }
    }
    
	for (i=0; i<=m_nNumColumns-2; i++) 
		dblC[i]=dblC[i+1];
    
	dblC[m_nNumColumns-1]=0.0;
    dblB[0]=0.0;
    for (i=0; i<=m_nNumColumns-1; i++)
    { 
		if ((dblB[i]!=0.0)&&(i-1>=0))
		{
			for (j=0; j<=i-1; j++)
            { 
				g=0.0;
				for (k=0; k<=i-1; k++)
					
					g=g+mtxQ.m_pData[i*m_nNumColumns+k]*mtxQ.m_pData[k*m_nNumColumns+j];
				
				for (k=0; k<=i-1; k++)
                { 
					u=k*m_nNumColumns+j;
					
					mtxQ.m_pData[u]=mtxQ.m_pData[u]-g*mtxQ.m_pData[k*m_nNumColumns+i];
                }
            }
		}
		
        u=i*m_nNumColumns+i;
        dblB[i]=mtxQ.m_pData[u]; mtxQ.m_pData[u]=1.0;
        if (i-1>=0)
		{
			for (j=0; j<=i-1; j++)
            { 
				mtxQ.m_pData[i*m_nNumColumns+j]=0.0; 
				mtxQ.m_pData[j*m_nNumColumns+i]=0.0;
			}
		}
    }
	
    // 构造对称三对角矩阵
    for (i=0; i<m_nNumColumns; ++i)
	{
		for (j=0; j<m_nNumColumns; ++j)
		{
            mtxT.SetElement(i, j, 0);
            k = i - j;
            if (k == 0) 
				mtxT.SetElement(i, j, dblB[j]);
			else if (k == 1)
				mtxT.SetElement(i, j, dblC[j]);
			else if (k == -1)
				mtxT.SetElement(i, j, dblC[i]);
        }
    }
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 实对称三对角阵的全部特征值与特征向量的计算
//
// 参数：
// 1. double dblB[] - 一维数组，长度为矩阵的阶数，传入对称三对角阵的主对角线元素；
//    返回时存放全部特征值。
// 2. double dblC[] - 一维数组，长度为矩阵的阶数，前n-1个元素传入对称三对角阵的次对角线元素
// 3. CMatrix& mtxQ - 如果传入单位矩阵，则返回实对称三对角阵的特征值向量矩阵；
//    如果传入MakeSymTri函数求得的矩阵A的豪斯荷尔德变换的乘积矩阵Q，则返回矩阵A的
//    特征值向量矩阵。其中第i列为与数组dblB中第j个特征值对应的特征向量。
// 4. int nMaxIt - 迭代次数，默认值为60
// 5. double eps - 计算精度，默认值为0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::SymTriEigenv(double dblB[], double dblC[], CMatrix& mtxQ, int 
						   nMaxIt /*= 60*/, double eps /*= 0.000001*/)
{
	int i,j,k,m,it,u,v;
    double d,f,h,g,p,r,e,s;
    
	// 初值
	int n = mtxQ.GetNumColumns();
	dblC[n-1]=0.0; 
	d=0.0; 
	f=0.0;
    
	// 迭代计算
	
	for (j=0; j<=n-1; j++)
    { 
		it=0;
        h=eps*(fabs(dblB[j])+fabs(dblC[j]));
        if (h>d) 
			d=h;
        
		m=j;
        while ((m<=n-1)&&(fabs(dblC[m])>d)) 
			m=m+1;
        
		if (m!=j)
        { 
			do
            { 
				if (it==nMaxIt)
					return FALSE;
				
                it=it+1;
                g=dblB[j];
                p=(dblB[j+1]-g)/(2.0*dblC[j]);
                r=sqrt(p*p+1.0);
                if (p>=0.0) 
					dblB[j]=dblC[j]/(p+r);
                else 
					dblB[j]=dblC[j]/(p-r);
                
				h=g-dblB[j];
                for (i=j+1; i<=n-1; i++)
					dblB[i]=dblB[i]-h;
                
				f=f+h; 
				p=dblB[m]; 
				e=1.0; 
				s=0.0;
                for (i=m-1; i>=j; i--)
                { 
					g=e*dblC[i]; 
					h=e*p;
                    if (fabs(p)>=fabs(dblC[i]))
                    { 
						e=dblC[i]/p; 
						r=sqrt(e*e+1.0);
                        dblC[i+1]=s*p*r; 
						s=e/r; 
						e=1.0/r;
                    }
                    else
					{ 
						e=p/dblC[i]; 
						r=sqrt(e*e+1.0);
                        dblC[i+1]=s*dblC[i]*r;
                        s=1.0/r; 
						e=e/r;
                    }
                    
					p=e*dblB[i]-s*g;
                    dblB[i+1]=h+s*(e*g+s*dblB[i]);
                    for (k=0; k<=n-1; k++)
                    { 
						u=k*n+i+1; 
						v=u-1;
                        h=mtxQ.m_pData[u]; 
						
						mtxQ.m_pData[u]=s*mtxQ.m_pData[v]+e*h;
                        mtxQ.m_pData[v]=e*mtxQ.m_pData[v]-s*h;
                    }
                }
                
				dblC[j]=s*p; 
				dblB[j]=e*p;
				
			} while (fabs(dblC[j])>d);
        }
        
		dblB[j]=dblB[j]+f;
    }
    
	for (i=0; i<=n-1; i++)
    { 
		k=i; 
		p=dblB[i];
        if (i+1<=n-1)
        { 
			j=i+1;
            while ((j<=n-1)&&(dblB[j]<=p))
            { 
				k=j; 
				p=dblB[j]; 
				j=j+1;
			}
        }
		
        if (k!=i)
        { 
			dblB[k]=dblB[i]; 
			dblB[i]=p;
            for (j=0; j<=n-1; j++)
            { 
				u=j*n+i; 
				v=j*n+k;
                p=mtxQ.m_pData[u]; 
				mtxQ.m_pData[u]=mtxQ.m_pData[v]; 
				mtxQ.m_pData[v]=p;
            }
        }
    }
    
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 约化一般实矩阵为赫申伯格矩阵的初等相似变换法
//
// 参数：无
//
// 返回值：无
//////////////////////////////////////////////////////////////////////
void CMatrix::MakeHberg()
{ 
	int i,j,k,u,v;
    double d,t;
	
    for (k=1; k<=m_nNumColumns-2; k++)
    { 
		d=0.0;
        for (j=k; j<=m_nNumColumns-1; j++)
        { 
			u=j*m_nNumColumns+k-1; 
			t=m_pData[u];
            if (fabs(t)>fabs(d))
            { 
				d=t; 
				i=j;
			}
        }
        
		if (d != 0.0)
        { 
			if (i!=k)
            { 
				for (j=k-1; j<=m_nNumColumns-1; j++)
                { 
					u=i*m_nNumColumns+j; 
					v=k*m_nNumColumns+j;
                    t=m_pData[u]; 
					m_pData[u]=m_pData[v]; 
					m_pData[v]=t;
                }
                
				for (j=0; j<=m_nNumColumns-1; j++)
                { 
					u=j*m_nNumColumns+i; 
					v=j*m_nNumColumns+k;
                    t=m_pData[u]; 
					m_pData[u]=m_pData[v]; 
					m_pData[v]=t;
                }
            }
            
			for (i=k+1; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k-1; 
				t=m_pData[u]/d; 
				m_pData[u]=0.0;
                for (j=k; j<=m_nNumColumns-1; j++)
                { 
					v=i*m_nNumColumns+j;
                    m_pData[v]=m_pData[v]-t*m_pData[k*m_nNumColumns+j];
                }
                
				for (j=0; j<=m_nNumColumns-1; j++)
                { 
					v=j*m_nNumColumns+k;
                    m_pData[v]=m_pData[v]+t*m_pData[j*m_nNumColumns+i];
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
// 求赫申伯格矩阵全部特征值的QR方法
//
// 参数：
// 1. double dblU[] - 一维数组，长度为矩阵的阶数，返回时存放特征值的实部
// 2. double dblV[] - 一维数组，长度为矩阵的阶数，返回时存放特征值的虚部
// 3. int nMaxIt - 迭代次数，默认值为60
// 4. double eps - 计算精度，默认值为0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::HBergEigenv(double dblU[], double dblV[], int nMaxIt /*= 60*/, 
						  double eps /*= 0.000001*/)
{ 
	int m,it,i,j,k,l,ii,jj,kk,ll;
    double b,c,w,g,xy,p,q,r,x,s,e,f,z,y;
    
	int n = m_nNumColumns;
	
	it=0; 
	m=n;
    while (m!=0)
    { 
		l=m-1;
        while ((l>0)&&(fabs(m_pData[l*n+l-1]) > 
			
			eps*(fabs(m_pData[(l-1)*n+l-1])+fabs(m_pData[l*n+l])))) 
			l=l-1;
		
        ii=(m-1)*n+m-1; 
		jj=(m-1)*n+m-2;
        kk=(m-2)*n+m-1; 
		ll=(m-2)*n+m-2;
        if (l==m-1)
        { 
			dblU[m-1]=m_pData[(m-1)*n+m-1]; 
			dblV[m-1]=0.0;
            m=m-1; 
			it=0;
        }
        else if (l==m-2)
        { 
			b=-(m_pData[ii]+m_pData[ll]);
            c=m_pData[ii]*m_pData[ll]-m_pData[jj]*m_pData[kk];
            w=b*b-4.0*c;
            y=sqrt(fabs(w));
            if (w>0.0)
            { 
				xy=1.0;
                if (b<0.0) 
					xy=-1.0;
                dblU[m-1]=(-b-xy*y)/2.0;
                dblU[m-2]=c/dblU[m-1];
                dblV[m-1]=0.0; dblV[m-2]=0.0;
            }
            else
            { 
				dblU[m-1]=-b/2.0; 
				dblU[m-2]=dblU[m-1];
                dblV[m-1]=y/2.0; 
				dblV[m-2]=-dblV[m-1];
            }
            
			m=m-2; 
			it=0;
        }
        else
        { 
			if (it>=nMaxIt)
				return FALSE;
			
            it=it+1;
            for (j=l+2; j<=m-1; j++)
				m_pData[j*n+j-2]=0.0;
            for (j=l+3; j<=m-1; j++)
				m_pData[j*n+j-3]=0.0;
            for (k=l; k<=m-2; k++)
            { 
				if (k!=l)
                { 
					p=m_pData[k*n+k-1]; 
					q=m_pData[(k+1)*n+k-1];
                    r=0.0;
                    if (k!=m-2) 
						r=m_pData[(k+2)*n+k-1];
                }
                else
                { 
					x=m_pData[ii]+m_pData[ll];
                    y=m_pData[ll]*m_pData[ii]-m_pData[kk]*m_pData[jj];
                    ii=l*n+l; 
					jj=l*n+l+1;
                    kk=(l+1)*n+l; 
					ll=(l+1)*n+l+1;
                    p=m_pData[ii]*(m_pData[ii]-x)+m_pData[jj]*m_pData[kk]+y;
                    q=m_pData[kk]*(m_pData[ii]+m_pData[ll]-x);
                    r=m_pData[kk]*m_pData[(l+2)*n+l+1];
                }
                
				if ((fabs(p)+fabs(q)+fabs(r))!=0.0)
                { 
					xy=1.0;
                    if (p<0.0) 
						xy=-1.0;
                    s=xy*sqrt(p*p+q*q+r*r);
                    if (k!=l) 
						m_pData[k*n+k-1]=-s;
                    e=-q/s; 
					f=-r/s; 
					x=-p/s;
                    y=-x-f*r/(p+s);
                    g=e*r/(p+s);
                    z=-x-e*q/(p+s);
                    for (j=k; j<=m-1; j++)
                    { 
						ii=k*n+j; 
						jj=(k+1)*n+j;
                        p=x*m_pData[ii]+e*m_pData[jj];
                        q=e*m_pData[ii]+y*m_pData[jj];
                        r=f*m_pData[ii]+g*m_pData[jj];
                        if (k!=m-2)
                        { 
							kk=(k+2)*n+j;
                            p=p+f*m_pData[kk];
                            q=q+g*m_pData[kk];
                            r=r+z*m_pData[kk]; 
							m_pData[kk]=r;
                        }
                        
						m_pData[jj]=q; m_pData[ii]=p;
                    }
                    
					j=k+3;
                    if (j>=m-1) 
						j=m-1;
                    
					for (i=l; i<=j; i++)
                    { 
						ii=i*n+k; 
						jj=i*n+k+1;
                        p=x*m_pData[ii]+e*m_pData[jj];
                        q=e*m_pData[ii]+y*m_pData[jj];
                        r=f*m_pData[ii]+g*m_pData[jj];
                        if (k!=m-2)
                        { 
							kk=i*n+k+2;
                            p=p+f*m_pData[kk];
                            q=q+g*m_pData[kk];
                            r=r+z*m_pData[kk]; 
							m_pData[kk]=r;
                        }
                        
						m_pData[jj]=q; 
						m_pData[ii]=p;
                    }
                }
            }
        }
    }
    
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 求实对称矩阵特征值与特征向量的雅可比法
//
// 参数：
// 1. double dblEigenValue[] - 一维数组，长度为矩阵的阶数，返回时存放特征值
// 2. CMatrix& mtxEigenVector - 返回时存放特征向量矩阵，其中第i列为与
//    数组dblEigenValue中第j个特征值对应的特征向量
// 3. int nMaxIt - 迭代次数，默认值为60
// 4. double eps - 计算精度，默认值为0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::JacobiEigenv(double dblEigenValue[], CMatrix& mtxEigenVector, 
						   int nMaxIt /*= 60*/, double eps /*= 0.000001*/)
{ 
	int i,j,p,q,u,w,t,s,l;
    double fm,cn,sn,omega,x,y,d;
    
	if (! mtxEigenVector.Init(m_nNumColumns, m_nNumColumns))
		return FALSE;
	
	l=1;
	//将特征相量矩阵初始化为单位阵
	//mtxEigenVector.MakeUnitMatrix(m_nNumColumns);
    for (i=0; i<=m_nNumColumns-1; i++)
    { 
		mtxEigenVector.m_pData[i*m_nNumColumns+i]=1.0;
        for (j=0; j<=m_nNumColumns-1; j++)
			if (i!=j) 
				mtxEigenVector.m_pData[i*m_nNumColumns+j]=0.0;
    }
    
	while (TRUE)
    { 
		fm=0.0;
		//将下三角矩阵中的行列信息保存在p,q中
        for (i=1; i<=m_nNumColumns-1; i++)
		{
			for (j=0; j<=i-1; j++)
			{ 
				d=fabs(m_pData[i*m_nNumColumns+j]);
				if ((i!=j)&&(d>fm))
				{ 
					fm=d; 
					p=i; 
					q=j;
				}
			}
		}
		//如果小于误差，将对角线上的值作为特征值，并返回
        if (fm<eps)
		{
			for (i=0; i<m_nNumColumns; ++i)
				dblEigenValue[i] = GetElement(i,i);
			return TRUE;
		}
		
        if (l>nMaxIt)  
			return FALSE;
        
		l=l+1;
        u=p*m_nNumColumns+q; //u = m_pData[p][q];
		w=p*m_nNumColumns+p; //w = m_pData[p][p];
		t=q*m_nNumColumns+p; //t = m_pData[q][p];
		s=q*m_nNumColumns+q;//s = m_pData[q][q];
        x=-m_pData[u]; 
		y=(m_pData[s]-m_pData[w])/2.0;
        omega=x/sqrt(x*x+y*y);
		
        if (y<0.0) 
			omega=-omega;
		
        sn=1.0+sqrt(1.0-omega*omega);
        sn=omega/sqrt(2.0*sn);
        cn=sqrt(1.0-sn*sn);
        fm=m_pData[w];
        m_pData[w]=fm*cn*cn+m_pData[s]*sn*sn+m_pData[u]*omega;
        m_pData[s]=fm*sn*sn+m_pData[s]*cn*cn-m_pData[u]*omega;
        m_pData[u]=0.0; 
		m_pData[t]=0.0;

        for (j=0; j<=m_nNumColumns-1; j++)
		{
			if ((j!=p)&&(j!=q))
			{ 
				u=p*m_nNumColumns+j; w=q*m_nNumColumns+j;
				fm=m_pData[u];
				m_pData[u]=fm*cn+m_pData[w]*sn;
				m_pData[w]=-fm*sn+m_pData[w]*cn;
			}
		}
		
        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if ((i!=p)&&(i!=q))
            { 
				u=i*m_nNumColumns+p; 
				w=i*m_nNumColumns+q;
				fm=m_pData[u];
				m_pData[u]=fm*cn+m_pData[w]*sn;
				m_pData[w]=-fm*sn+m_pData[w]*cn;
            }
		}
		
        for (i=0; i<=m_nNumColumns-1; i++)
        { 
			u=i*m_nNumColumns+p; 
			w=i*m_nNumColumns+q;
            fm=mtxEigenVector.m_pData[u];
            mtxEigenVector.m_pData[u]=fm*cn+mtxEigenVector.m_pData[w]*sn;
            mtxEigenVector.m_pData[w]=-fm*sn+mtxEigenVector.m_pData[w]*cn;
        }
    }
    
	for (i=0; i<m_nNumColumns; ++i)
		dblEigenValue[i] = GetElement(i,i);
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// 求实对称矩阵特征值与特征向量的雅可比过关法
//
// 参数：
// 1. double dblEigenValue[] - 一维数组，长度为矩阵的阶数，返回时存放特征值
// 2. CMatrix& mtxEigenVector - 返回时存放特征向量矩阵，其中第i列为与
//    数组dblEigenValue中第j个特征值对应的特征向量
// 3. double eps - 计算精度，默认值为0.000001
//
// 返回值：BOOL型，求解是否成功
//////////////////////////////////////////////////////////////////////
BOOL CMatrix::JacobiEigenv2(double dblEigenValue[], CMatrix& mtxEigenVector, 
							double eps /*= 0.000001*/)
{ 
	int i,j,p,q,u,w,t,s;
    double ff,fm,cn,sn,omega,x,y,d;
    
	if (! mtxEigenVector.Init(m_nNumColumns, m_nNumColumns))
		return FALSE;
	
	for (i=0; i<=m_nNumColumns-1; i++)
    { 
		mtxEigenVector.m_pData[i*m_nNumColumns+i]=1.0;
        for (j=0; j<=m_nNumColumns-1; j++)
			if (i!=j) 
				mtxEigenVector.m_pData[i*m_nNumColumns+j]=0.0;
    }
    
	ff=0.0;
    for (i=1; i<=m_nNumColumns-1; i++)
	{
		for (j=0; j<=i-1; j++)
		{ 
			d=m_pData[i*m_nNumColumns+j]; 
			ff=ff+d*d; 
		}
	}
	
    ff=sqrt(2.0*ff);
	
Loop_0:
    
	ff=ff/(1.0*m_nNumColumns);
	
Loop_1:
	
    for (i=1; i<=m_nNumColumns-1; i++)
	{
		for (j=0; j<=i-1; j++)
        { 
			d=fabs(m_pData[i*m_nNumColumns+j]);
            if (d>ff)
            { 
				p=i; 
				q=j;
                goto Loop_2;
            }
        }
	}
	
	if (ff<eps) 
	{
		for (i=0; i<m_nNumColumns; ++i)
			dblEigenValue[i] = GetElement(i,i);
		return TRUE;
	}
    
	goto Loop_0;
	
Loop_2: 
	
	u=p*m_nNumColumns+q; 
	w=p*m_nNumColumns+p; 
	t=q*m_nNumColumns+p; 
	s=q*m_nNumColumns+q;
    x=-m_pData[u]; 
	y=(m_pData[s]-m_pData[w])/2.0;
    omega=x/sqrt(x*x+y*y);
    if (y<0.0) 
		omega=-omega;
    
	sn=1.0+sqrt(1.0-omega*omega);
    sn=omega/sqrt(2.0*sn);
    cn=sqrt(1.0-sn*sn);
    fm=m_pData[w];
    m_pData[w]=fm*cn*cn+m_pData[s]*sn*sn+m_pData[u]*omega;
    m_pData[s]=fm*sn*sn+m_pData[s]*cn*cn-m_pData[u]*omega;
    m_pData[u]=0.0; m_pData[t]=0.0;
    
	for (j=0; j<=m_nNumColumns-1; j++)
	{
		if ((j!=p)&&(j!=q))
		{ 
			u=p*m_nNumColumns+j; 
			w=q*m_nNumColumns+j;
			fm=m_pData[u];
			m_pData[u]=fm*cn+m_pData[w]*sn;
			m_pData[w]=-fm*sn+m_pData[w]*cn;
		}
	}
	
    for (i=0; i<=m_nNumColumns-1; i++)
    {
		if ((i!=p)&&(i!=q))
        { 
			u=i*m_nNumColumns+p; 
			w=i*m_nNumColumns+q;
			fm=m_pData[u];
			m_pData[u]=fm*cn+m_pData[w]*sn;
			m_pData[w]=-fm*sn+m_pData[w]*cn;
        }
	}
    
	for (i=0; i<=m_nNumColumns-1; i++)
    { 
		u=i*m_nNumColumns+p; 
		w=i*m_nNumColumns+q;
        fm=mtxEigenVector.m_pData[u];
        mtxEigenVector.m_pData[u]=fm*cn+mtxEigenVector.m_pData[w]*sn;
        mtxEigenVector.m_pData[w]=-fm*sn+mtxEigenVector.m_pData[w]*cn;
	}

	goto Loop_1;
}
