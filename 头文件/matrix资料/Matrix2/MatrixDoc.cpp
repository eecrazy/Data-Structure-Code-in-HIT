// MatrixDoc.cpp : implementation of the CMatrixDoc class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "Matrix.h"

#include "MatrixDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixDoc

IMPLEMENT_DYNCREATE(CMatrixDoc, CDocument)

BEGIN_MESSAGE_MAP(CMatrixDoc, CDocument)
	//{{AFX_MSG_MAP(CMatrixDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixDoc construction/destruction

CMatrixDoc::CMatrixDoc()
{
	// TODO: add one-time construction code here

}

CMatrixDoc::~CMatrixDoc()
{
}

BOOL CMatrixDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMatrixDoc serialization

void CMatrixDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixDoc diagnostics

#ifdef _DEBUG
void CMatrixDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMatrixDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatrixDoc commands

void CMatrixDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	int num=m_VariablePtrList.GetCount();
	POSITION pos=m_VariablePtrList.GetHeadPosition();
	for(int i=0;i<num;i++)
	{
		CArrayMatrix * tp=(CArrayMatrix *)m_VariablePtrList.GetAt(pos);
		delete tp;
		m_VariablePtrList.GetNext(pos);
	}
	if(num!=0) m_VariablePtrList.RemoveAll();
	CDocument::DeleteContents();
}


void CMatrixDoc::ProcOpenDocText(const CString sDataString)
{
	DeleteContents();
	CString temp=sDataString;
	temp.GetBufferSetLength(temp.GetLength()+1);
	int num=0;
	for(int i=0;i<sDataString.GetLength();i++)//把多个邻接的分号和并为一个
	{
		if(sDataString[i]==TCHAR(';'))
		{
			if((i+1)!=sDataString.GetLength()&&sDataString[i+1]==TCHAR(';'))
				continue;
			else
			{
				temp.SetAt(num,sDataString[i]);
				num++;
			}
		}
		else
		{
			temp.SetAt(num,sDataString[i]);
			num++;
		}
	}
	temp.SetAt(num,'\0');
	temp.GetBufferSetLength(lstrlen(temp));
	num=temp.Replace(';',';');
	if(num==0) return;
	CString *p=new CString[num];
	for(i=0;i<num;i++) p[i]=_T("");
	CString tpRS=temp;
	int nlen=0;
	int len=lstrlen(temp);
	for(i=0;i<num;i++)
	{
		tpRS=temp.Right(len-nlen);
		p[i]=tpRS.SpanExcluding(";");
		nlen=lstrlen(p[i])+1+nlen;
	}	
	//现在每个数据项保存着每个字符串中
	for(i=0;i<num;i++)
	{
		ProcOneString(p[i]);
	}
	delete []p;
}

BOOL CMatrixDoc::ProcOneString(const CString & sData)
{
	CString temp=sData;
	CString sName=_T("");
	bool IsExisted=false;
	CArrayMatrix *PtrNew=NULL;
	if(!CArrayMatrix::SetStringName(temp,sName)) return FALSE;
	CArrayMatrix::ProcString(temp);
	POSITION pos=m_VariablePtrList.GetHeadPosition();
	for(int i=0;i<m_VariablePtrList.GetCount();i++)
	{
		CArrayMatrix *Ptr=(CArrayMatrix *)m_VariablePtrList.GetAt(pos);
		if(Ptr->GetName()==sName) {IsExisted=true;PtrNew=Ptr;break;}
		m_VariablePtrList.GetNext(pos);
	}
	if(!IsExisted)
	{
		PtrNew=new CArrayMatrix;
		pos=m_VariablePtrList.AddTail(PtrNew);
	}
	//现在PtrNew指向新的目标变量
	CArrayMatrix tpMatrix;
	if(!GetResult(temp,tpMatrix))
	{
		if(!IsExisted)
		{
			delete PtrNew;
			m_VariablePtrList.RemoveAt(pos);
			return FALSE;
		}
	}
	*PtrNew=tpMatrix;
	return true;
}

BOOL CMatrixDoc::IsOperator(TCHAR ch)
{
	switch(ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '#':
		{
			return TRUE;
		}
	default: return FALSE;
	}
}

BOOL CMatrixDoc::GetResult(const CString &data,CArrayMatrix & matrix)
{
//在这可以通过修改data字符串和m_VariablePtrList变量链表来实现
//具体方法是首先假如data是包含多个运算符的
	CString sDataString=data;
	sDataString.TrimLeft("\n");
	sDataString.TrimRight("\n");
	CString *pVar;
	CArrayMatrix result;
	bool ok;
	int VarNum=GetVariableNum(sDataString,pVar);
	if(VarNum==0) return FALSE;
	CTypedPtrList<CObList,CArrayMatrix *> tpVarList;
	if(!StringsToMatrixs(pVar,tpVarList,VarNum)) 
	{
		if(pVar!=NULL) delete []pVar;
		return FALSE;
	}
	TurnString(sDataString);
	//表达式求值
	{
		sDataString=sDataString+"#";
		CStack<TCHAR> OPTR;
		CStack<CArrayMatrix *> OPND;
		OPTR.Push('#');
		int index=0;
		TCHAR c=sDataString[index];
		int nVarIndex=0;
		while(c!=TCHAR('#')||OPTR.GetTop()!=TCHAR('#'))
		{
			if(!IsOperator(c)) 
			{
				POSITION pos=tpVarList.GetHeadPosition();
				CArrayMatrix * pt=NULL;
				for(int i=0;i<=nVarIndex&&i<tpVarList.GetCount();i++)
				{
					pt=tpVarList.GetAt(pos);
					tpVarList.GetNext(pos);
				}
				if(pt==NULL) return FALSE;
				OPND.Push(pt);
				nVarIndex++;
				index++;
				c=sDataString[index];
			}
			else
			{
				switch(Precede(OPTR.GetTop(),c))
				{
				case -1:
					{
						OPTR.Push(c);
						index++;
						c=sDataString[index];
						break;
					}
				case 0:
					{
						TCHAR x;
						OPTR.Pop(x);
						index++;
						c=sDataString[index];
						break;
					}
				case 1:
					{
						TCHAR theta;
						OPTR.Pop(theta);
						CArrayMatrix * b=NULL;
						CArrayMatrix * a=NULL;
						OPND.Pop(b);
						OPND.Pop(a);
						OPND.Push(Operate(a,theta,b,ok));
						break;
					}
				}
			}
		}
		result=*(OPND.GetTop());
	}
	

	
	//销毁tpvarlist变量里面的东西
	{
		POSITION pos=tpVarList.GetHeadPosition();
		int len=tpVarList.GetCount();
		for(int i=0;i<len;i++)
		{
			CArrayMatrix * tp=tpVarList.GetAt(pos);
			delete tp;
			tpVarList.GetNext(pos);
		}
		tpVarList.RemoveAll();
	}
	if(pVar!=NULL) delete []pVar;
	if(!ok) return FALSE;
	matrix=result;
	return TRUE;
}

int CMatrixDoc::GetVariableNum(const CString &m,CString * & pVar)
{
	pVar=NULL;
	int CharNum=0;
	bool bSign=true;
	int num=0;
	int len=lstrlen(m);
	{
		for(int pos=0;pos<len;pos++)
		{
			if(IsCharAlpha(m[pos])) CharNum++;
		}
	}
	if(CharNum==0)
	{
		pVar=new CString[1];
		*pVar=m;
		pVar->TrimLeft();
		pVar->TrimRight();
		return 1;
	}
	for(int i=0;i<len;i++)
	{
		if(!IsOperator(m[i]))
		{
			if(bSign)
			{
				num++;
				bSign=false;
			}
			else continue;
		}
		else bSign=true;
	}
	if(num==0) return num;
	else
	{
		int tpnum=0;
		pVar=new CString[num];
		CString temp;
		int slen=0;
		bSign=true;
		for(int i=0;i<len;i++)
		{
			if(!IsOperator(m[i]))
			{
				if(bSign)
				{
					tpnum++;
					if(tpnum==num)
					{
						int j=i;
						int number=0;
						CString stp;
						while(j<len&&!IsOperator(m[i]))
						{
							stp.GetBufferSetLength(number+1);
							stp.SetAt(number,m[j]);
							number++;
							j++;
						}
						pVar[num-1]=stp;
					}
					else if(tpnum>1)
					{
						pVar[tpnum-1]=temp;
					}
					temp=_T("");
					slen=1;
					temp.GetBufferSetLength(slen);
					temp.SetAt(0,m[i]);
					if(i<len-1&&IsOperator(m[i+1])) pVar[tpnum-1]=temp;
					bSign=false;
				}
				else
				{
					slen++;
					temp.GetBufferSetLength(slen);
					temp.SetAt(slen-1,m[i]);
				}
			}
			else bSign=true;
		}
	}
	return num;
}

BOOL CMatrixDoc::StringsToMatrixs(CString * pVar,CTypedPtrList<CObList,CArrayMatrix *> & m_List,int num)
{
	for(int i=0;i<num;i++)	
	{
		pVar[i].TrimLeft();
		pVar[i].TrimRight();
		if(pVar[i]==_T("")) return FALSE;
		if(IsCharAlpha(pVar[i][0]))//pVar[i]是变量
		{
			int nVarNum=m_VariablePtrList.GetCount();
			POSITION pos=m_VariablePtrList.GetHeadPosition();
			POSITION tippos=NULL;
			for(int j=0;j<nVarNum;j++)
			{
				CString sVarName=pVar[i];
				sVarName.TrimRight("\'");
				sVarName.TrimLeft("~");
				CArrayMatrix * pt=m_VariablePtrList.GetAt(pos);
				if(pt->GetName()==sVarName) {tippos=pos;break;}
				m_VariablePtrList.GetNext(pos);
			}
			if(tippos==NULL) return FALSE;
			else
			{
				CArrayMatrix *pMatrix=new CArrayMatrix;
				*pMatrix=*(m_VariablePtrList.GetAt(tippos));
				//对多次求转置的处理，比如A''''的求值
				{
					int len=lstrlen(pVar[i]);
					int index=len-1;
					if(pVar[i][index]==TCHAR('\''))
					{
						while(pVar[i][index]==TCHAR('\'')&&index>0)
						{
							(*pMatrix)=pMatrix->T();
							index--;
						}
					}
				}
				m_List.AddTail(pMatrix);
			}
		}
		else if(pVar[i][0]==TCHAR('~'))//处理~~~A的值
		{
			int glen=lstrlen(pVar[i]);
			int gnum=0;
			for(int g=0;g<glen&&pVar[i][g]==TCHAR('~');g++) gnum++;
			if(glen==num) return FALSE;
			CString Var=pVar[i].Right(glen-gnum);
			int nVarNum=m_VariablePtrList.GetCount();
			POSITION pos=m_VariablePtrList.GetHeadPosition();
			POSITION tippos=NULL;
			for(int j=0;j<nVarNum;j++)
			{
				CArrayMatrix * pt=m_VariablePtrList.GetAt(pos);
				if(pt->GetName()==Var) {tippos=pos;break;}
				m_VariablePtrList.GetNext(pos);
			}
			if(tippos==NULL) return FALSE;
			else
			{
				CArrayMatrix *pMatrix=new CArrayMatrix;
				*pMatrix=*(m_VariablePtrList.GetAt(tippos));
				int k=gnum%2;
				if(k==1) 
				{
					if(!(*pMatrix).CanContrary()) {delete pMatrix;return FALSE;}
					(*pMatrix)=~(*pMatrix);
				}
				m_List.AddTail(pMatrix);
				
			}
			
		}
		else
		{	
			if(IsCharAlphaNumeric(pVar[i][0])||(IsOperator(pVar[i][0])&&IsCharAlphaNumeric(pVar[i][1])))
			{
				CString sName="hyx=";
				sName=sName+pVar[i];
				sName=sName+";";
				CArrayMatrix * Ptr=new CArrayMatrix;
				if(!Ptr->ProcessInput(sName)) {delete Ptr;return FALSE;}
				m_List.AddTail(Ptr);
			}
			else return FALSE;	
		}
	}
	return TRUE;
}

int CMatrixDoc::Precede(TCHAR m, TCHAR n)
{
	switch(m)
	{
	case '+':
		{
		switch(n)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return -1;
		case '/':
			return -1;
		case '(':
			return -1;
		case ')':
			return 1;
		case '#':
			return 1;
		default: return 100;
		}
		}
	case '-':
		{
		switch(n)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return -1;
		case '/':
			return -1;
		case '(':
			return -1;
		case ')':
			return 1;
		case '#':
			return 1;
		default:return 100;
		}
		}
	case '*':
		{
		switch(n)
		{
		case '+':return 1;
		case '-':return 1;
		case '*':return 1;
		case '/':return 1;
		case '(':return -1;
		case ')':return 1;
		case '#':return 1;
		default:return 100;
		}
		}
	case '/':
		{
		switch(n)
		{
		case '+':return 1;
		case '-':return 1;
		case '*':return 1;
		case '/':return 1;
		case '(':return -1;
		case ')':return 1;
		case '#':return 1;
		default:return 100;
		}		
		}
	case '(':
		{
		switch(n)
		{
		case '+':return -1;
		case '-':return -1;
		case '*':return -1;
		case '/':return -1;
		case '(':return -1;
		case ')':return 0;
		default:return 100;
		}		
		}
	case ')':
		{
		switch(n)
		{
		case '+':return 1;
		case '-':return 1;
		case '*':return 1;
		case '/':return 1;
		case ')':return 1;
		case '#':return 1;
		default:return 100;
		}
		}
	case '#':
		{
		switch(n)
		{
		case '+':return -1;
		case '-':return -1;
		case '*':return -1;
		case '/':return -1;
		case '(':return -1;
		case '#':return 0;
		default:return 100;
		}		
		}
	default:return 100;
	}
}

void CMatrixDoc::TurnString(CString &sdata)
{
	CString * pVal=NULL;
	int num=GetVariableNum(sdata,pVal);
	int debug=num;
	for(int i=0;i<num;i++)
	{
		sdata.Replace(pVal[i],"@");
	}
	CString temp=sdata;
	num=0;
	for(int j=0;j<lstrlen(temp);j++)
	{
		if(temp[j]!=TCHAR(' ')) 
		{
			sdata.SetAt(num,temp[j]);
			num++;
		}
		else continue;
	}
	if(num<lstrlen(temp))
	{
		sdata.SetAt(num,'\0');
		sdata.GetBufferSetLength(lstrlen(sdata));
	}
	if(pVal!=NULL)	delete []pVal;
}

CArrayMatrix * CMatrixDoc::Operate(CArrayMatrix *a, TCHAR theta, CArrayMatrix *b, bool &ok)
{
	switch(theta)
	{
	case '+':
		{
			if(!(a->CanAddSub(*b))) ok=false;
			else (*a)=(*a)+(*b);
			break;
		}
	case '-':
		{
			if(!(a->CanAddSub(*b))) ok=false;
			else (*a)=(*a)-(*b);
			break;
		}
	case '*':
		{
			if(!(a->CanMutiply(*b))) ok=false;
			else (*a)=(*a)*(*b);
			break;
		}
	case '/':
		{
			if(!(b->CanContrary()&&(a->CanMutiply(*b)))) ok=false;
			else (*a)=(*a)/(*b);
			break;
		}
	default: 
		{
			ok=false;
		}
	}
	return a;
}

void CMatrixDoc::ProcInput(const CString &all)
{
	CString DisplayData=_T("");
	CString temp=all;//包含了';'号
	CString sName=_T("");
	int IsError=100;//1代表无此变量；2代表变量显示错误
	//3代表赋值有误；4代表字符串变量信息输入有误
	//5格式输入不合法
	if(CArrayMatrix::SetStringName(temp,sName)) //输入的第一个数组
	{
		CArrayMatrix::ProcString(temp);
		CString result=temp;
		temp=temp+";";
		int number=0;
		for(int i=0;i<lstrlen(temp);i++)
		{
			if(temp[i]!=TCHAR('\n')&&temp[i]!=TCHAR(';')&&temp[i]!=TCHAR(' ')&&!IsOperator(temp[i]))
				number++;
		}
		if(number==0||temp.IsEmpty())
		{
			CArrayMatrix * p;
			if(!IsFood(sName,p)) IsError=1;
			else
			{
				if(!p->DisPlay(DisplayData)) IsError=2;
				else IsError=-1;
			}
		}
		else
		{
			CArrayMatrix *pt;
			if(IsFood(sName,pt)) 
			{
				CArrayMatrix tp;
				if(GetResult(result,tp))
				{
					*pt=tp;
					IsError=0;
				}
				else
				{
					IsError=3;
				}
			}
			else
			{
				pt=new CArrayMatrix;
				if(!(pt->SetName(sName)&&GetResult(result,*pt))) {IsError=4;delete pt;}
				else
				{
					m_VariablePtrList.AddTail(pt);
					IsError=0;
				}
			}
		}
	}
	else IsError=5;
	//打开剪贴板
	if(IsError!=0)
	{
		switch(IsError)
		{
		case 1:
			{
				DisplayData="\n!!!变量未定义，不存在此变量!;";
				break;
			}
		case 2:
			{
				DisplayData="\n!!!变量未初始化，或则变量内无数据!;";
				break;
			}
		case 3:
			{
				DisplayData="\n!!!变量赋值错误，赋值格式不合法!;";
				break;
			}
		case 4:
			{
				DisplayData="\n!!!初始化新变量时，字符输入不合法!;";
				break;
			}
		case 5:
			{
				DisplayData="\n!!!变量名输入有误!;";
				break;
			}
		case -1:
			{
				CString tpok="\n";
				tpok=tpok+sName;
				tpok=tpok+"=\n";
				DisplayData.TrimLeft("\n");
				DisplayData.TrimLeft("\xd\xa");
				DisplayData=tpok+DisplayData;
				break;
			}
		default:
			{
				DisplayData="\n系统出错，请马上推出程序!;";
			}
		}

	}
	//获得视图的指针
	POSITION pos=GetFirstViewPosition();
	CView *p=GetNextView(pos);
	//	
	if(IsError!=0)
	{

		DisplayData.Replace("\n","\xd\xa");
		int len=lstrlen(DisplayData);
		HGLOBAL hGlobal;
		PTSTR pGlobal;
		hGlobal=GlobalAlloc(GHND|GMEM_SHARE,len*sizeof(TCHAR)+1);
		pGlobal=(PTSTR)GlobalLock(hGlobal);
		for(int g=0;g<len;g++) *pGlobal++=DisplayData[g];
		GlobalUnlock(hGlobal);
		p->OpenClipboard();
		EmptyClipboard();
		SetClipboardData(CF_TEXT,hGlobal);
		CloseClipboard();
	}
	else
	{
		p->OpenClipboard();
		EmptyClipboard();
		CloseClipboard();
	}
}

BOOL CMatrixDoc::IsFood(const CString &Name, CArrayMatrix *&p)
{
	int num=m_VariablePtrList.GetCount();
	POSITION pos=m_VariablePtrList.GetHeadPosition();
	for(int i=0;i<num;i++)
	{
		CArrayMatrix * ptItem=m_VariablePtrList.GetAt(pos);
		if(ptItem->GetName()==Name) {p=ptItem;return TRUE;}
		m_VariablePtrList.GetNext(pos);
	}
	p=NULL;
	return FALSE;
}
