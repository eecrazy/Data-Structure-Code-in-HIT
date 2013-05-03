// 实现一个矩阵类,重载下标操作符, 即 m[i][j],  以及其它运算符
//重载下标操作符, m[i][j], 方法1:
#include <iostream>
//#include <cstddef>
//#include <cassert>
using namespace std;

template<typename T, size_t ROW = 10, size_t COLUMN = 10>
class Matrix
{
private:
    size_t _ROW;
    size_t _COLUMN;
    T* pData;

public:
    Matrix();
    Matrix(size_t M, size_t N);
    ~Matrix();

    //重载下标运算符,实现 a[m][n]
    T* operator[](size_t m);
    const T* operator[](size_t m) const;

    //提供 a(m, n) 这样的操作
    T& operator()(size_t m, size_t n);
    const T& operator()(size_t m, size_t n) const;

    //拷贝构造
    Matrix(const Matrix<T>& m);
    //重载 =
    Matrix<T>& operator=(const Matrix<T>& m);

    //重载 +=
    Matrix<T>& operator+=(const Matrix<T>& m);

    //重载 +, -, *
    Matrix<T> operator+(const Matrix<T>& m);
    Matrix<T> operator-(const Matrix<T>& m);
    Matrix<T> operator*(const Matrix<T>& m);

    //矩阵转置 !
    Matrix<T> operator!();

    //求反 -
    Matrix<T>& operator-();

    //显示矩阵
    void displayMatrix() const;

    //取得行, 列的大小
    const size_t getRow() const;
    const size_t getColumn() const;

    //注: 重载 << 时, template<typename T1> 必须和 模板类中的类型不一样
    template<typename T1>
    friend ostream& operator<<(ostream& os, const Matrix<T1>& m);
};

//默认构造函数
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T, ROW, COLUMN>::Matrix():_ROW(ROW),_COLUMN(COLUMN)
{
    pData = new T[_ROW*_COLUMN];
    assert(pData);
    memset(pData, 0, _ROW*_COLUMN*sizeof(T));
}
//有参构造函数
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T, ROW, COLUMN>::Matrix(size_t M, size_t N)
    :_ROW(M), _COLUMN(N)
{
    pData = new T[_ROW*_COLUMN];
    assert(pData);
    memset(pData, 0, _ROW*_COLUMN*sizeof(T));
}

//析构函数
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T, ROW, COLUMN>::~Matrix()
{
    if(pData)
        delete []pData;
    pData = NULL;
}
//拷贝构造
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T, ROW, COLUMN>::Matrix(const Matrix<T>& m)
{
    _ROW = m.getRow();
    _COLUMN = m.getColumn();
    pData = new T[_ROW*_COLUMN];
    assert(pData);
    memcpy(pData, m.pData, _ROW*_COLUMN*sizeof(T));
}
//重载下标操作符
//a[m][n], a[m] 首先调用此重载运算符, 返回指针 (pData + m*_COLUMN)
//然后进行正常的指针运算 (pData + m*_COLUMN)[n]
template<typename T, size_t ROW, size_t COLUMN>
T* Matrix<T, ROW, COLUMN>::operator[](size_t m)
{
    assert(m >= 0 && m < _ROW);
    return (pData + m*_COLUMN);
}
//for const class
template<typename T, size_t ROW, size_t COLUMN>
const T* Matrix<T, ROW, COLUMN>::operator[](size_t m) const
{
    assert(m >= 0 && m < _ROW);
    return (pData + m*_COLUMN);
    //return operator[](m);
}//*/
//a(m,n)
template<typename T, size_t ROW, size_t COLUMN>
T& Matrix<T, ROW, COLUMN>::operator()(size_t m, size_t n)
{
    assert(m < _ROW && m >= 0 && n < _COLUMN && n >= 0);
    return (pData + m*_COLUMN)[n];
}
//for const class
template<typename T, size_t ROW, size_t COLUMN>
const T& Matrix<T, ROW, COLUMN>::operator()
(size_t m, size_t n) const
{
    assert(m < _ROW && m >= 0 && n < _COLUMN && n >= 0);
    return (pData + m*_COLUMN)[n];
}//*/

//查看行列值
template<typename T, size_t ROW, size_t COLUMN>
const size_t Matrix<T, ROW, COLUMN>::getRow() const
{
    return _ROW;
}
template<typename T, size_t ROW, size_t COLUMN>
const size_t Matrix<T, ROW, COLUMN>::getColumn() const
{
    return _COLUMN;
}

//输出整个矩阵
template<typename T, size_t ROW, size_t COLUMN>
void Matrix<T, ROW, COLUMN>::displayMatrix() const
{
    cout << endl << "Now The Matrix is: " << endl;
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            cout << *(pData+i*_COLUMN+j) << " ";
            if(j == _COLUMN - 1)
                cout << endl;
        }
    cout << endl;
}
//重载 =
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T>& Matrix<T, ROW, COLUMN>::operator=(const Matrix<T>& m)
{
    if(this == &m)
        return *this;
    assert(_ROW == m.getRow() && _COLUMN == m.getColumn());
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            operator()(i, j) = m(i, j);
        }

    return *this;
}
//重载 +=
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T>& Matrix<T, ROW, COLUMN>::operator+=(const Matrix<T>& m)
{
    assert(_ROW == m.getRow() && _COLUMN == m.getColumn());
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            operator()(i, j) += m(i, j);
        }
    return *this;
}
//operator+(const Matrix<T>& m)
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T> Matrix<T, ROW, COLUMN>::operator+(const Matrix<T>& m)
{
    assert(_ROW == m.getRow() && _COLUMN == m.getColumn());
    Matrix<T, ROW, COLUMN> matrix;
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            matrix(i, j) = operator()(i, j) + m(i, j);
        }
    return matrix;
}
//operator-()
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T>& Matrix<T, ROW, COLUMN>::operator-()
{
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            operator()(i, j) =     -operator()(i, j);
        }
    return *this;
}
//operator*()
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T> Matrix<T, ROW, COLUMN>::operator*(const Matrix<T>& m)
{
    assert(_ROW == m.getRow() && _COLUMN == m.getColumn());
    Matrix<T, ROW, COLUMN> matrix;
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            matrix(i, j) = operator()(i, j) * m(i, j);
        }
    return matrix;
}
//矩阵转置 operator!()
template<typename T, size_t ROW, size_t COLUMN>
Matrix<T> Matrix<T, ROW, COLUMN>::operator!()
{
    Matrix<T, ROW, COLUMN> matrix;
    for(size_t i = 0; i < _ROW; i++)
        for(size_t j = 0; j < _COLUMN; j++)
        {
            matrix(i, j) = (*this)(j, i);
        }
    return matrix;
}

//for cout << matrix;
template<typename T1>
ostream& operator<<(ostream& os, const Matrix<T1>& m)
{
    if(m.getRow() <= 0 || m.getColumn() <= 0)
        return os;
    for(size_t i = 0; i < m.getRow(); i++)
        for(size_t j = 0; j < m.getColumn(); j++)
        {
            os << m(i, j) << " ";
            if(j == m.getColumn() - 1)
                os << endl;
        }
    return os;
}

//重载下标操作符, m[i][j], 方法2:
//使用代理类. 定义两个类，当第一个类调用重载的操作符时，使此函数返回
//第二个类的对象，在第二个类中，同样定义了运算符 [] 重载。但在第一个
//类中的重载操作符要能访问第二个类的私有成员，那么就应该把第一个类声明
//为第二个类的友元。
//----
//每个MatrixBody对象扮演的是一个一维数组，而这个一维数组没有在使用Matrixs的
//程序中出现。扮演其它对象的对象通常被称为代理类。在这个例子里，MatrixBody是
//一个代理类。它的实例扮演的是一个在概念上不存在的一维数组。
//代理类的概念见: More Effective C++ Item M30：代理类
template <typename T>
class Matrixs
{
    class MatrixBody
    {
        friend class Matrixs<T>;
    private:
        T* _pData;
        size_t _Rows;
        size_t _Column;
        size_t _CurrentRow;     //当前行

        MatrixBody(size_t row, size_t column);

    public:
        T& operator[](size_t j);
        const T& operator[](size_t j) const;
        ~MatrixBody();
    } mBody;

public:
    Matrixs(size_t row, size_t column)
        :mBody(row, column)
    { }


    //[] 返回第二个类的对象
    MatrixBody& operator[](size_t i);
    const MatrixBody& operator[](size_t i) const;

    //输出矩阵内容
    void displayMatrix() const;

};

//代理类构造函数
template <typename T>
Matrixs<T>::MatrixBody::MatrixBody(size_t row, size_t column)
{
    _Rows   = row;
    _Column = column;
    _CurrentRow = -1;
    _pData = new T[_Rows*_Column];
    assert(_pData != NULL);
    memset(_pData, 0, _Rows*_Column*sizeof(T));
}
//代理类的下标重载符
template <typename T>
T& Matrixs<T>::MatrixBody::operator[](size_t j)
{
    bool row_error = false;
    bool column_error = false;
    try
    {
        if(_CurrentRow < 0 || _CurrentRow >= _Rows)
            row_error = true;
        if(j < 0 || j >= _Column)
            column_error = true;
        if(row_error || column_error)
            throw 'e';
    }
    catch(char)
    {
        if(row_error)
            cerr << "Row access invalid!" << _CurrentRow << endl;
        if(column_error)
            cerr << "Column access invalid!" << j << endl;
    }

    return _pData[_CurrentRow*_Column + j];
}

//代理类析构函数
template <typename T>
Matrixs<T>::MatrixBody::~MatrixBody()
{
    if(_pData != NULL)
        delete []_pData;
    _pData = NULL;
}

//矩阵类下标重载符[] //模板的语法实在是太奇怪了,注意下面必须有 typename
template<typename T>
typename Matrixs<T>::MatrixBody& Matrixs<T>::operator[](size_t i)
{
    mBody._CurrentRow = i;
    return mBody;
}

template <typename T>
const typename Matrixs<T>::MatrixBody& Matrixs<T>::operator[](size_t i) const
{
    mBody._CurrentRow = i;
    return mBody;
    //operator[](i);
}

//输出矩阵内容
template <typename T>
void Matrixs<T>::displayMatrix() const
{
    cout << endl << "Now The Matrix is: " << endl;
    for(size_t i = 0; i < mBody._Rows; i++)
    {
        for(size_t j = 0; j < mBody._Column; j++)
        {
            cout << *(mBody._pData+i*mBody._Column+j) << " ";

            if(j == mBody._Column - 1)
                cout << endl;
        }
    }
    cout << endl;
}

int main()
{

    //指定矩阵大小
    Matrix<int, 6, 5> matrix;
    cout << "ROW = " << matrix.getRow() << " "
         << "COLUMN = " << matrix.getColumn() << endl;
    matrix.displayMatrix();
    matrix[1][2] = 5;
    cout << "matirx[1][2] = " << matrix[1][2] << endl;
    matrix[5][4] = 6;
    cout << "matirx[5][4] = " << matrix[5][4] << endl;
    //matrix[6][4] = 3; //溢出
    matrix.displayMatrix();
    matrix(3, 3) = matrix[5][4];
    matrix.displayMatrix();

    //采用默认构造参数，默认大小
    Matrix<int> matrix1;
    matrix.displayMatrix();
    matrix1[3][4] = 5;
    cout << "ROW = " << matrix1.getRow() << " "
         << "COLUMN = " << matrix1.getColumn() << endl;
    cout << "matirx1[3][4] = " << matrix1[3][4] << endl;
    cout << "matirx1[3][3] = " << matrix1[3][3] << endl;
    matrix1.displayMatrix();//*/

    //test for +=
    Matrix<int> matrix2;
    matrix2[3][4] = 2;
    matrix2[1][4] = 3;
    matrix2.displayMatrix();
    cout << "Test for the operator+=(): ";
    matrix2 += matrix1;     //*/
    matrix2.displayMatrix();

    //test for operator-()
    cout << "Test for operator-(): ";
    -matrix2;
    matrix2.displayMatrix();

    //test for opeartor+() and =
    cout << "Test for operator+() and operator=(): ";
    matrix1 = matrix2;
    matrix1 = matrix1 + matrix2;
    matrix1.displayMatrix();

    //test for opeartor!()
    cout << "Test for operator!(): ";
    matrix2 = !matrix1;
    matrix2.displayMatrix();

    cout << "Test for cout << matrix : " << endl;;
    cout << matrix2 << endl;

    //测试代理类
    cout << "Test for the proxy class: ";
    Matrixs<int> a(5,5);
    a.displayMatrix();
    a[2][1] = 3;
    a.displayMatrix();

    return 0;
}

/*使用 C++ 实现二维数组, 主要有如下不同的方法,程序中使用的是第一种:
    ////////////////////////////
    //不同的方法创建一个 m[3][5]
    //1):
    int* m1 = new int[3*5];
    delete []m1;
    //点：调用不够直观
    //优点：连续储存，n 可以不是已知

    //2):
    int (*m2)[5] = new int[3][5];
    delete []m2;
    //缺点：n 必须是已知
    //优点：调用直观，连续储存，程序简洁(经过测试，析构函数能正确调用)

    //3):
    int** m3 = new int*[3];
    for(int i = 0; i < 3; i++)
        m3[i] = new int[5];

    for(int i = 0; i < 3; i++)
        delete []m3[i];
    delete []m3;
    //缺点：非连续储存，程序烦琐，m3 为 A** 类型
    //优点：调用直观，n 可以不是已知

    //4):
    vector< vector<int> > m4;
    m4.resize(3);
    for(int i = 0; i < 5; i++)
        m4.resize(5);
    //缺点：非连续储存，调试不够方便，编译速度下降，程序膨胀(实际速度差别不大)
    //优点：调用直观，自动析构与释放内存，可以调用 stl 相关函数，动态增长

    //5):
    vector< vector<int> > m5;
    m5.resize(3*5);
    //方法 1, 4 的结合

    //6):  3) 的改进
    int** m6 = new int*[3];
    m6[0] = new int[3*5];
    for(int i = 1; i < 3; i++)
        m6[i] = m6[i-1] + 5;
    //优点: 连续存储, n 可以不是已知, 析构方便
*/
