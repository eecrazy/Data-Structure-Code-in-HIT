#include<iostream>
using namespace std;


int main()
{
    //String类的构造函数和析构函数如下：
    string s;
    //生成一个空字符串s
    string s(str);
    //拷贝构造函数 生成str的复制品。
    string s(str,stridx);
    //将字符串str内“始于位置stridx”的部分当作字符串的初值。
    string s(str,stridx,strlen);
    //将字符串str内“始于stridx且长度顶多strlen”的部分作为字符串的初值。
    string s(cstr);
    //将C字符串作为s的初值。
    string s(chars,chars_len);
    //将C字符串前chars_len个字符作为字符串s的初值。
    string s(num,c);
    //生成一个字符串，包含num个c字符。
    string s(beg,end);
    //以区间beg;end(不包含end)内的字符作为字符串s的初值。
    s.~string();
    //销毁所有字符，释放内存
}
/*
字符串操作函数：
a) =,assign()                   //赋以新值
b) swap()                       //交换两个字符串的内容
c) +=,append(),push_back()      //在尾部添加字符
d) insert()                     //插入字符
e) erase()                      //删除字符
f) clear()                      //删除全部字符
g) replace()                    //替换字符
h) +                            //串联字符串
i) ==,!=,<,<=,>,>=,compare()    //比较字符串
j) size(),length()              //返回字符数量
k) max_size()   //返回字符的可能最大个数
l) empty()      //判断字符串是否为空
m) capacity()   //返回重新分配之前的字符容量
n) reserve()    //保留一定量内存以容纳一定数量的字符
o) [ ], at()    //存取单一字符
p) >>,getline() //从stream读取某值
q) <<           //将某值写入stream
r) copy()       //将某值赋值为一个C_string
s) c_str()      //将内容以C_string返回
t) data()       //将内容以字符数组形式返回
u) substr()     //返回某个子字符串
v)查找函数
w) begin() end()   //提供类似STL的迭代器支持
x) rbegin() rend() //逆向迭代器
y) get_allocator() //返回配置器
*/

/*
c与c++:
data()以字符数组的形式返回字符串内容，但并不添加’\0’。
c_str()返回一个以‘\0’结尾的字符数组，
而copy()则把字符串的内容复制或写入既有的c_string或字符数组内。
C++字符串并不以’\0’结尾
*/

/*大小
现有的字符数，函数是size()和length()，他们等效。
Empty()用来检查字符串是否为空
*/

/*
字符串比较：
一个功能强大的比较函数是成员函数compare()。
他支持多参数处理，支持用索引值和长度定位子串来进行比较。
他返回一个整数来表示比较结果，返回值意义如下：
0-相等； >0-大于； <0-小于。
举例如下：
string s(“abcd”);
s.compare(“abcd”); //返回0
s.compare(“dcba”); //返回一个小于0的值
s.compare(“ab”); //返回大于0的值
s.compare(s); //相等
s.compare(0,2,s,2,2); //用”ab”和”cd”进行比较小于零。
s.compare(1,2,”bcx”,2); //用”bc”和”bc”比较。
*/

字符串更改内容:
 s.assign(str); 
s.assign(str,1,3);            //如果str是”iamangel” 就是把”ama”赋给字符串。
s.assign(str,2,string::npos); //把字符串str从索引值2开始到结尾赋给s。
s.assign(“gaint”); 
s.assign(“nico”,5);           //把’n’ ‘I’ ‘c’ ‘o’ ‘\0’赋给字符串。
s.assign(5,’x’);              //把五个x赋给字符串。
把字符串清空的方法有三个：
s=””;
s.clear();
s.erase();

string提供了很多函数用于插入（insert）、删除（erase）、替换（replace）、增加字符。
先说增加字符（这里说的增加是在尾巴上），函数有 +=、append()、push_back()。举例如下：
s+=str;                       //加个字符串
s+=”my name is jiayp”;        //加个C字符串。
s+=’a’;                       //加个字符
s.append(str);
s.append(str,1,3);            //同前面的函数参数assign的解释
s.append(str,2,string::npos)  //不解释了
s.append(“my name is jiayp”);
s.append(“nico”,5);
s.append(5,’x’);
s.push_back(‘a’);             //这个函数只能增加单个字符
