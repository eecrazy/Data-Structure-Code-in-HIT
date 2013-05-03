// ArrayMatrix.cpp: implementation of the CArrayMatrix class.
// Download by http://www.codefans.net
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Matrix.h"
#include "ArrayMatrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CArrayMatrix, CObject, 1)



CArrayMatrix::CArrayMatrix()
{
	m_Name=_T("");
	m_wCon=0;
	m_wRow=0;
}

CArrayMatrix::~CArrayMatrix()
{

}

void CArrayMatrix::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
    if(ar.IsStoring())
	{
		ar<<m_Name<<m_wRow<<m_wCon;
	}
    else
    {
		ar>>m_Name>>m_wRow>>m_wCon;
	}
	m_Array.Serialize(ar);
}

CArrayMatrix::CArrayMatrix(const CArrayMatrix & m)
{
	m_Name=m.m_Name;
	m_wRow=m.m_wRow;
	m_wCon=m.m_wCon;
	m_Array.SetSize(m_wRow*m_wCon);
	for(int i=0;i<int(m_wRow*m_wCon);i++)
	{
		m_Array[i]=m.m_Array[i];
	}
}

CArrayMatrix CArrayMatrix::operator +(const CArrayMatrix & m)
{
	CArrayMatrix temp;
	temp.m_wCon=m_wCon;
	temp.m_wRow=m_wRow;
	temp.m_Array.SetSize(m_wCon*m_wRow);
	for(int i=0;i<int(m_wCon*m_wRow);i++)
	{
		temp.m_Array[i]=m_Array[i]+m.m_Array[i];
	}
	return temp;
}



BOOL CArrayMatrix::ProcessInput(CString DataString)
{
	//获得等号右边的字符串
	CString RightString=DataString;
	if(!SetStringName(RightString,m_Name)) return FALSE;	//获得变量名称，存储到m_Name中去
	ProcString(RightString);
	int tipnum=0;
	int len=lstrlen(RightString);
	if(len==0) return FALSE;//表示矩阵没有数据
	if(!InputRow(RightString)) return FALSE;
	CString * SPtBuffer=NULL;//指向矩阵每行字符串CString的指针
	if(!InputCon(RightString,SPtBuffer)) return FALSE;
	m_Array.SetSize(m_wCon*m_wRow);
	for(int i=0;i<(int)m_wRow;i++)
	{
		for(int j=0;j<(int)m_wCon;j++)
		{
			float temp=0.0;
			if(!ConvertToNum(SPtBuffer[i],j,temp)) return FALSE;
			m_Array[i*m_wCon+j]=temp;
		}
	}
	if(SPtBuffer!=NULL) delete []SPtBuffer;
	return true;
}

void CArrayMatrix::ProcStringBlank(CString & sHead)
{
	int len=lstrlen(sHead);
	if(len==0) return;
	CString m_temp=sHead;
	sHead.GetBufferSetLength(len+1);
	int j=0;
	for(int i=0;i<len;i++)
	{
		if(m_temp[i]==TCHAR(' ')) 
		{
			if((i+1)!=len&&m_temp[i+1]==TCHAR(' ')) continue;
			else 
			{
				sHead.SetAt(j,sHead[i]);
				j++;
			}
		}
		else {sHead.SetAt(j,m_temp[i]);j++;}
	}
	sHead.SetAt(j,TCHAR('\0'));
	j=lstrlen(sHead);
	sHead.GetBufferSetLength(j);
	sHead.Replace(" \n","\n");
	sHead.Replace("\n ","\n");
}

void CArrayMatrix::ProcStringComma(CString & sHead)
{
	sHead.Replace(',',' ');
	sHead.Replace(';','\n');
}

void CArrayMatrix::ProcStringEnter(CString & sHead)
{
	CString m_temp=sHead;
	int len=lstrlen(sHead);
	sHead.GetBufferSetLength(len+1);
	int j=0;
	for(int i=0;i<len;i++)
	{
		if(m_temp[i]==TCHAR('\n')) 
		{
			if((i+1)!=len&&m_temp[i+1]==TCHAR('\n')) continue;
			else 
			{
				sHead.SetAt(j,m_temp[i]);
				j++;
			}
		}
		else {sHead.SetAt(j,m_temp[i]);j++;}
	}
	sHead.SetAt(j,TCHAR('\0'));
	j=lstrlen(sHead);
	sHead.GetBufferSetLength(j);
}

void CArrayMatrix::ProcString(CString & RightString)
{
	DeleteHeadEnter(RightString);
	ProcStringComma(RightString);//处理字符串中的逗号，使之成为空格
	ProcStringBlank(RightString);//使多个空格成为一个空格
	ProcStringEnter(RightString);
}

void CArrayMatrix::DeleteHeadEnter(CString & RightString)
{
	int j=0;
	for(int i=0;i<lstrlen(RightString);i++)
	{
		if(RightString[i]=='\n'||RightString[i]==' '||RightString[i]==';'||RightString[i]==',')
			j++;
		else break;
	}
	if(j==0) return;
	else RightString=RightString.Right(lstrlen(RightString)-j);
}

BOOL CArrayMatrix::InputRow(const CString & RS)
{
	int len=lstrlen(RS);
	int tprow=0;
	for(int i=0;i<len;i++) 
	{
		if(RS[i]==TCHAR('\n')) tprow++;
	}
	if(tprow==0) return FALSE;
	m_wRow=tprow;
	return TRUE;
}

BOOL CArrayMatrix::InputCon(const CString & RS,CString * &PtRSBuffer)
{
	CString * p=new CString[m_wRow];
	int num=0;
	int len=lstrlen(RS);
	for(int i=0;i<(int)m_wRow;i++) p[i]=_T("");
	CString tpRS=RS;
	for(i=0;i<(int)m_wRow;i++)
	{
		tpRS=RS.Right(len-num);
		p[i]=tpRS.SpanExcluding("\n");
		num=lstrlen(p[i])+1+num;
	}
	int prenum=0;
	int nownum=0;
	for(i=0;i<(int)m_wRow;i++)//检查每行的元素个数是否相等
	{
		int total=0;
		for(int pos=0;pos<lstrlen(p[i]);pos++)
		{
			if(p[i][pos]==TCHAR(' ')) total++;
		}
		if(i==0)
		{
			prenum=total;
			nownum=total;
		}
		else
		{
			prenum=nownum;
			nownum=total;
			if(nownum!=prenum) return FALSE;
		}
	}
	m_wCon=UINT(nownum+1);
	PtRSBuffer=p;
	return TRUE;
}

BOOL CArrayMatrix::ConvertToNum
(const CString & sRowString, const int & nAtCon, float & fResult)//nAtCon从0---m_wCon-1
{
	CString sResult=_T("");;
	CString tp=sRowString;
	int len=0;
	tp.GetBufferSetLength((len=lstrlen(tp))+1);
	tp.SetAt(len,' ');
	len=lstrlen(tp);
	int num=0;
	CString tptp=tp;
	if(nAtCon>=(int)m_wCon) return FALSE;
	for(int i=0;i<nAtCon+1;i++)
	{
		tptp=tp.Right(len-num);
		sResult=tptp.SpanExcluding(" ");
		num=lstrlen(sResult)+1+num;
	}
	fResult=(float)atof(sResult);
	return TRUE;
}

BOOL CArrayMatrix::SetStringName(CString &DataString,CString & sName)
{
	int pos;
	pos=DataString.Find(_T("="));
	if(pos==-1||pos==0) return FALSE;
	CString tpName=sName;
	sName=DataString.SpanExcluding("=");//取等号作边的字符串为变量的名字
	sName.TrimLeft();
	sName.TrimRight();
	if(sName.GetLength()==0||sName.Find(_T(" "))!=-1) //当m_name为空格或则里面存在空格时返回假
	{
		sName=tpName;
		return FALSE;
	}	
	DataString=DataString.Right(lstrlen(DataString)-pos-1);//把DataString改成等号右边的字符串
	return TRUE;
}

BOOL CArrayMatrix::DisPlay(CString & out)const
{
	if(m_Array.GetSize()==0||m_wCon==0||m_wRow==0) return FALSE;
	CString clr="\n";
	CString temp;
	out=clr;
	temp.Format("%f",m_Array[0]);
	temp.TrimRight("0");
	int nMaxLen=lstrlen(temp);
	for(int i=0;i<(int)m_wRow;i++)
	{
		for(int j=0;j<(int)m_wCon;j++)
		{
			temp.Format("%f",m_Array[i*m_wCon+j]);
			temp.TrimRight("0");
			if(nMaxLen<lstrlen(temp))
				nMaxLen=lstrlen(temp);
		}
	}
	nMaxLen+=4;
	for(i=0;i<(int)m_wRow;i++)
	{
		for(int j=0;j<(int)m_wCon;j++)
		{
			TCHAR *PtrTemp=new TCHAR[nMaxLen+1];
			temp.Format("%f",m_Array[i*m_wCon+j]);
			temp.TrimRight("0");
			temp.TrimRight(".");
			lstrcpy(PtrTemp,temp);
			for(int i=lstrlen(temp);i<nMaxLen;i++) PtrTemp[i]=' ';
			PtrTemp[nMaxLen]='\0';
			out=out+PtrTemp;
			delete []PtrTemp;
		}
		if(i==((int)m_wRow-1)) out=out+";";
		else out=out+clr;
	}
	return TRUE;
}

BOOL CArrayMatrix::CanAddSub(const CArrayMatrix &m)const
{
	if((int)m_wCon==(int)m.m_wCon&&(int)m.m_wRow==(int)m_wRow) return TRUE;
	return FALSE;
}

CArrayMatrix & CArrayMatrix::operator =(const CArrayMatrix & m)
{
	m_wRow=m.m_wRow;
	m_wCon=m.m_wCon;
	m_Array.SetSize(m_wRow*m_wCon);
	for(int i=0;i<int(m_wRow*m_wCon);i++)
	{
		m_Array[i]=m.m_Array[i];
	}
	return *this;
}

CArrayMatrix & CArrayMatrix::operator =(float m)
{
	m_wRow=1;
	m_wCon=1;
	m_Array.SetSize(1);
	m_Array.SetAt(0,m);
	return *this;
}

CArrayMatrix CArrayMatrix::operator -(const CArrayMatrix & m)
{
	CArrayMatrix temp;
	temp.m_wCon=m_wCon;
	temp.m_wRow=m_wRow;
	temp.m_Array.SetSize(m_wCon*m_wRow);
	for(int i=0;i<int(m_wCon*m_wRow);i++)
	{
		temp.m_Array[i]=m_Array[i]-m.m_Array[i];
	}
	return temp;	
}



BOOL CArrayMatrix::CanMutiply(const CArrayMatrix &m)const
{
	if(m_wCon==0||m.m_wCon==0) return FALSE;
	if(m_wCon==1&&m_wRow==1) return TRUE;
	if(m.m_wCon==1&&m.m_wRow==1) return TRUE;
	if(m_wCon==m.m_wRow) return TRUE;
	return FALSE;
}

CArrayMatrix CArrayMatrix::operator *(const CArrayMatrix &m)
{
	if(m_wCon==1)
	{
		CArrayMatrix temp;
		temp.m_Array.SetSize(m.m_Array.GetSize());
		temp.m_wCon=m.m_wCon;
		temp.m_wRow=m.m_wRow;
		for(int i=0;i<m.m_Array.GetSize();i++)
		{
			temp.m_Array[i]=m_Array[0]*m.m_Array[i];
		}
		return temp;
	}
	if(m.m_wCon==1)
	{
		CArrayMatrix temp;
		temp.m_Array.SetSize(m_Array.GetSize());
		temp.m_wCon=m_wCon;
		temp.m_wRow=m_wRow;
		for(int i=0;i<m_Array.GetSize();i++)
		{
			temp.m_Array[i]=m_Array[i]*m.m_Array[0];
		}
		return temp;
	}
	CArrayMatrix temp;
	temp.m_wRow=m_wRow;
	temp.m_wCon=m.m_wCon;
	temp.m_Array.SetSize(temp.m_wCon*temp.m_wRow);
	for(int i=0;i<int(temp.m_wRow);i++)
	{
		for(int j=0;j<int(temp.m_wCon);j++)
		{
			float total=0.0;
			for(int n=0;n<int(m_wCon);n++)
			{
				total+=m_Array[i*m_wCon+n]*m.m_Array[n*m.m_wCon+j];
			}
			temp.m_Array[i*temp.m_wCon+j]=total;
		}
	}
	return temp;	
}

CArrayMatrix CArrayMatrix::operator / (CArrayMatrix &m)
{
	CArrayMatrix tp;
	tp=(*this)*~m;
	return tp;
}

CArrayMatrix CArrayMatrix::operator ~()
//求逆矩阵
{
	CArrayMatrix tp;
	tp.m_wCon=1;
	tp.m_wRow=1;
	tp.m_Array.SetSize(1);
	tp.m_Array[0]=float(1.0/m_Array[0]);
	if(m_wRow==1&&m_wCon==1) return tp;
	tp.m_Array[0]=float(1.0/GetRange());
	return GetAccompany()*tp;
}

CArrayMatrix CArrayMatrix::T()const
//求转置矩阵
{
	CArrayMatrix temp;
	if(m_wCon==0||m_wRow==0) return temp;
	if(m_wCon==1&&m_wRow==1) return *this;
	temp.m_Array.SetSize(m_Array.GetSize());
	temp.m_wCon=m_wRow;
	temp.m_wRow=m_wCon;
	for(int i=0;i<int(m_wRow);i++)
	{
		for(int j=0;j<int(m_wCon);j++)
		{
			temp.m_Array[j*temp.m_wCon+i]=m_Array[i*m_wCon+j];
		}
	}
	return temp;
}

BOOL CArrayMatrix::CanContrary()const
//矩阵是方阵
{
	if(int(m_wRow)!=int(m_wCon)) return FALSE;
	if(GetRange()==0.0) return FALSE;
	return TRUE;
}

float CArrayMatrix::GetRange() const
//计算矩阵的行列式的值,矩阵是方阵
{
	if(m_wRow==0||m_wCon==0) return 0.0;
	if(m_wRow==1&&m_wCon==1) return m_Array[0];
	if(m_wRow==2&&m_wCon==2) return m_Array[0]*m_Array[3]-m_Array[1]*m_Array[2];
	float sum=0.0;
	float sub=0.0;
	for(int i=0;i<(int)m_wCon;i++)
	{
		{
			float total=1.0;
			int tpRow=0;
			int num=0;
			for(int tpCon=i;tpCon<int(m_wCon);tpCon++,tpRow++)
			{
				total*=m_Array[tpRow*m_wCon+tpCon];
				num++;
			}
			tpRow=num;
			for(tpCon=0;tpRow<int(m_wRow)&&num!=int(m_wRow);tpCon++,tpRow++)
			{
				total*=m_Array[tpRow*m_wCon+tpCon];
			}
			sub+=total;
		}
		{
			float total=1.0;
			int tpRow=0;
			int num=0;
			for(int tpCon=i;tpCon>=0;tpCon--,tpRow++)
			{
				total*=m_Array[tpRow*m_wCon+tpCon];
				num++;
			}
			tpRow=num;
			for(tpCon=m_wCon-1;tpRow<int(m_wRow)&&num!=int(m_wRow);tpRow++,tpCon--)
			{
				total*=m_Array[tpRow*m_wCon+tpCon];
			}
			sum+=total;
		}
	}
	return sub-sum;
}

CArrayMatrix CArrayMatrix::GetAccompany()const
{
	CArrayMatrix m;
	m.m_wCon=m_wCon;
	m.m_wRow=m_wRow;
	m.m_Array.SetSize(m_Array.GetSize());
	for(int i=0;i<int(m_wRow);i++)
	{
		for(int j=0;j<int(m_wCon);j++)
		{
			CArrayMatrix tp;
			tp.m_wCon=m_wCon-1;
			tp.m_wRow=m_wRow-1;
			tp.m_Array.SetSize(tp.m_wCon*tp.m_wRow);
			int num=0;
			for(int g=0;g<int(m_wRow);g++)
			{
				if(g==i) continue;
				for(int h=0;h<int(m_wCon);h++)
				{
					if(h==j) continue;
					else
					{
						tp.m_Array[num]=m_Array[g*m_wCon+h];
						num++;
					}
				}
			}
			int tip;
			float fuhao;
			tip=i+j+2;
			fuhao=1.0;
			if(tip%2==1) fuhao=-1.0;
			m.m_Array[i*m_wCon+j]=fuhao*tp.GetRange();
		}
	}
	m=m.T();
	return m;
}

CArrayMatrix CArrayMatrix::operator *(float m)
{
	CArrayMatrix tp=*this;
	for(int i=0;i<int(m_wRow*m_wCon);i++)
	{
		tp.m_Array[i]*=m;
	}
	return tp;
}

CArrayMatrix CArrayMatrix::operator /(float m)
{
	CArrayMatrix tp=*this;
	if(m==0) return tp;
	for(int i=0;i<int(m_wRow*m_wCon);i++)
	{
		tp.m_Array[i]*=float(1.0/m);
	}
	return tp;
}

CString CArrayMatrix::GetName()
{
	return m_Name;
}

BOOL CArrayMatrix::SetName(CString m)
{
	m.TrimLeft();
	m.TrimRight();
	if(lstrlen(m)==0) return FALSE;
	m_Name=m;
	return TRUE;
}
