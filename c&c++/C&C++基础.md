
## 引用(reference)   为对象起的别名
- 定义引用时,把引用和它的初始值绑定在一起,而不是将初始值拷贝给引用
- 引用本身并不是对象,所以不能定义引用的引用
```c++
 int ival = 1024;
 int &refVal = ival;//refVal指向ival(是ival的另一个名字) int &refVal2;//报错:引用必须初始化
 refVal = 2;//把2给refVal指向的对象,此处即是赋给了ival
 int li = refVal;//等同于li=ival

 int &refVal3 = refVal;
//正确: refVal13绑定到了那个与refVal绑定的对象上,即绑定了ival
```

## 指针
- 引用不是对象,不存在地址,所以不能定义指向引用的指针。
- 指针(pointer)对地址的封装,本身就是一个对象
- 定义指针类型的方法是将声明符写成`*d`的形式
- 如果一条语句中定义了几个指针变量,每个变量前面都必须加上`*`符号
- 和其他内置类型一样,在块作用域内定义指针如果没有初始化,将拥有一个不确定的值
```c++
 int *ip1, *ip2;//ip1和ip2都是指向int型对象的指针 
 double dp, *dp2;
```
- 可以使用取地址符(运算符&)获取指针所封装的地址:
```c++
 int ival = 42;
 int *p = &ival;//p是指向ival的指针 
 double *dp = &ival;//错误:类型不匹配
```
- 在声明中,&和`*`用于组成复合类型;在表达式中,他们是运算。含义截然不同
- 可以使用解引用符(运算符*)利用指针访问对象:
```c++
 int ival = 42;
 int *p = &ival;//p是指向ival的指针
 std::cout<<*p;//输出4指针是对地址的封装。
 *p=0;
 std::cout<<*p; //输出0
```
- 空指针(null pointer)
	- 不指向任何对象
	- 在使用一个指针之前,可以首先检查它是否为空。
```c++
 int *p1 = nullptr; //C++11
 int *p2 = 0;
 int *p3 = NULL; //需要#include cstdlib
 int zero = 0;
 p1= zero; //错误:类型不匹配
```
- ` void *`指针
	- 纯粹的地址封装,与类型无关。可以用于存放任意对象的地址。
```c++
 double obj = 3.14, *pd = &obj; 
 void *pv = &obj;
 pv = pd;
```
- 指向指针的指针
	- 通过`*`的个数可以区分指针的级别
```c++
 int ival = 1024;
 int *pi = &ival;
 int **ppi= &pi;//ppi指向一个int型的指针
```
- 指针的引用
	- 指针是对象,可以定义引用。
```c++
int i = 1024;
int *p;
int *&r = p; //r是一个对指针p的引用

r= &i; //r引用了一个指针,就是令p指向i
*r= 0; //解引用r得到i,也就是p指向的对象,将i的值改为0
```

## const限定符
- 把变量定义成一个常量
- 使用const对变量的类型加以限定,变量的值不能被改变。
```c++
 const int bufSize = 512; //输入缓冲区大小
 bufSize = 512; //错误:试图向const对象写值
```
- const对象必须初始化(其他时候不能出现在等号左边)
```c++
 const int i= get_size (); //正确:运行时初始化 
 const int j= 42; //正确:编译时初始化
 const int k; //错误: k是一个未经初始化的常量,

 const int bb = 0;
 void * a= bb;//在编译的时候,会把bb编成常量
```
- 默认状态下, const对象仅在文件内有效，如果想在多个文件之间共享const对象,必须在变量的定义之前添加extern关键字
```c++
//file_1.cc定义并初始化了一个常量,该常量能被其他文件访问 extern const int bufSize = fcn();
 //file_1.h头文件
 extern const int bufSize;
```
- const的引用:对常量的引用
```c++
const int ci= 1024,
const int &rl= ci; //正确:引用及其绑定的对象都是常量
rl= 42;//错误,相当于cl=42,试图修改常量
int &r2 = ci;//错误: ci是常量,存在通过r2改变ci (const)的风险
```
```c++
int i= 42;
const int &rl = i; //正确: i依然可以通过其他途径修改
const int &r2 = 42;
const int &r3 = r1*2;
int &r4= rl*2; //错误:不能通过一个非常量的引用指向一个常量
```
```c++
 double dval = 3. 14;
 const int &ri= dval; //允许
 int &ri = dval; //错误:因为改变的是编译器生成的中间值，dval会强制类型转换为int，存储在中间值变量中
```
- 指针和const
	- 指向常量的指针
```c++
 const double pi = 3.14;
 double *ptr = &pi; //错误:存在通过ptr指针修改pi的风险
 const double *
 cptr = &pi;
 *cptr = 42; //错误
 double dval = 3.14;
 cptr= &dval; //正确:但不能通过cptr修改dval的值,
```
- const指针:指针是对象,也可以限定为常量(必须初始化)
	- 把`*`放在const之前,说明指针是一个常量
	- 不变的是指针本身的值,而非指向的那个值
	- const指针的用法类似于引用
```c++
int errNumb = 0;
int *const curErr = &errNumb;
const double pi = 3.14159; const double *const
pip =&pi;//指向常量的常量指针,

*pip =2.71;//错误: 试图修改常量pi
if(*curErr){
	errorHandler();
	*curErr =0; //正确:试图修改变量errNumb
}
```
- 顶层const
	- 顶层const:表示变量本身是一个常量
	- 底层const:表示指针所指向的对象是一个const

```c++
 int i= 0;
 int *const p1 = &i; //n层
 const int ci = 42; //顶层
 const int *p2 = &ci;//底层
 const int *const p3 = p2;// (左:底层), (右:顶层)
 i= ci;//正确
 p2 = p3;//正确
 int *p = p3;//错误:存在通过*p修改*p3 (const)的风险
 p2 =&i; //正确:只是不能通过p2修改i而已
 int &r = ci; //错误:存在通过r修改ci (const)的风险
 const int &r2 = i; //正确:只是不能通过r2修改i而已

```
- constexpr和常量表达式
	- 常量表达式(const expression)是指:值不会改变并且在编译过程就能得到计算结果的表达式。
	- 能用于常量表达式的函数:函数的返回类型以及所有的形参都是字面值类型
```c++
 const int max_files = 20; //是
 const int limit = max_files +1; //是
 int staff_size = 27; //不是
 const int sz = get_size(); //不是
```
	- `constexpr变量`
- C++11标准规定,允许将变量声明为constexpr类型,以便由编译器来验证变量的值是否是一个常量表达式。
	- 一定是一个常量
	- 必须用常量表达式初始化
	- 需要在编译时就得到计算,声明constexpr时用到的类型必须显而易见,容易得到(称为:字面值类型)
	-  自定义类型(例如: Sales_item)、I0库、 string等类型不能被定义为constexpr
```c++
 constexpr int mf = 20;
 constexpr int limit = mf +1;
 constexpr int sz = size(); //只有当size是一个constexpr函数时才正确
```
- 指针和constexpr
	- 限定符仅对指针有效,对指针所指的对象无关
```c++
 constexpr int *np = nullptr; //常量指针
 int j= 0;
 constexpr int i = 42;
//i和j必须定义在函数之外
 constexpr const int *p = &i; //p是常量指针,指向常量 
 constexpr int *p1= &j;//p1是常量指针,指向变量i
```

## 类型别名 typedef：提高可读性
- `typedef`
```c++
 typedef double wages;
 typedef wages base, *p; //base是double的同义词, p是double *的同义词 using SI = Sales_item; //C++11,别名声明
 wages hourly, weekly;
 SI item; //等价于Sales item item
```
- 对于指针这样的复合类型,类型别名的使用可能会产生意想不到的结果:
```c++
 typedef char *pstring;
 const pstring cstr = 0; //指向char的常量指针
 const pstring *ps; //ps是指针变量,它的对象是指向char的常量指针
 const char *cstr = 0; //是对const pstring cstr =0 的错误理解
```
## auto类型说明符
- C++11,让编译器通过初始值推断变量的类型
```c++
 auto item = val1 + val2;
 auto i =0, *p = &i; //正确
 auto sz = 0, pi = 3.14; //错误: auto已经被推断为int型,却需要被推断为double型
```
## decltype类型说明符
- 选择并返回操作数的数据类型
- 只要数据类型,不要其值
```c++
 decltype(f()) sum = x;// sum的类型就是函数f返回的类型
 const int ci = 0, &cj = ci;
 decltype(ci) x = 0; //x的类型是const int
 decltype(cj) y = x; //y的类型是const int &
 decltype(cj) z; //错误: z是一个引用,必须初始化
```
- 引用从来都是作为其所指对象的同义词出现,只有用在decltype处是一个例外
- 如果表达式的内容是解 引用操作,则decltype将得到引用类型
-  decltype( (variable) )的结 果永远为引用, variable本身也可以是引用
## 自定义数据结构: 一组数据以及相关操作的集合
- 类定义: 类定义可以使用关键字class或struct
	- 二者默认的继承、访问权限不同
	- struct是publicb, class是private的
```c++
 struct Sales_data{
	 std::string bookNo; 
	 unsigned units_sold = 0; //C++ 11
	 double revenue = 0.0;
};//类定义的最后需要加上分号
```
- 数据成员定义了类的对象的具体内容,每个对象有自己的一份拷贝
## 头文件
![[Pasted image 20220719201128.png]]

## 命名空间的using声明
- using namespace::name;
- using namespace nameSpaceName;
- 头文件不应该包含using声明,因为会被拷贝到引用该头文件的文件中。

## 迭代器(iterator) :容器类型内置的“指针”
- 使用选代器可以访问某个元素,选代器也能从一个元素移动到另一个元素。
- 有选代器的类型都拥有begin和end成员
	- begin:返回指向第一个元素(或字符)的选代器
	- end:尾后选代器,即尾元素的下一个位置(一个本不存在的元素)
 ```c++
auto b = v.begin(), e = v.end(); //b和e的类型相同
```
- 如果容器为空,则begin和end返回的是同一个选代器,都是尾后选代器。
 - 标准容器选代器的运算符。
	 - `*iter ` 返回选代器iter所指元素的引用
	 - iter->mem   解引用iter并获取该元素的名为mem的成员,等价于`(*iter).mem`
	 - ++iter   令iter指示容器中的下一个元素(尾后选代器除外)
	 - --iter  令iter指示容器中的上一个元素
	 - iter1 == iter2   iter1 != iter2  如果两个选代器指示的是同一个元素则相等,否则不等。
- 尾后选代器并不实际指示某一个元素,所以不能对其进行递增或解引用

-  拥有选代器的标准类型使用iterator和const_iterator(和常量指针差不多)
```c++
 vector<int>::iterator it; //it能读写vector<int>元素
 string::iterator it2; //it2能读写string对象中的字符
 vector<int>::const_iterator it3; //it3只能读元素,不能写元素 string::const_iterator it4; //it4只能读元素,不能写元素
```
 - 如果对象是常量, begin和end返回const_iterator,否则返回iterator:
 ```c++
 vector<int> v;
 const vector<int> cV;
 auto it1 = v.begin(); //it1类型vector<int>::iterator
 auto it2 = cv.begin(); //it2B类型vector<int>::constaiterator
```
- 有时候我们希望即使对象不是常量,我们也要使用const_iterator
```c++
 // C++11新标准引入了cbegin和cend:
 auto it3 = v.cbegin(); //it3的类型vector<int>::const_iterator
```
- 结合解引用的成员访问:
```c++
vector<string> V;
auto it = v.begin();
(*it).empty();
*it.empty(); //错误:试图访问it的名为empty的成员,但it是选代器it->empty(); //箭头运算符:把解引用和成员访问两个操作合在一起
```
- 任何一种可能改变vector对象容量的操作,都会使得相应的选代器失效
- vector和string的选代器提供了更多额外的运算符:     可以令选代器和一个整数相加(或相减),其返回值是向前(或向后)移动了若干位置的选代器
	-  iter+n
	 - iter-n
	 - iter1 + = n
	 - iter1 -=n
	 - iter1 - iter2
	 - >     >=     <     <=     比大小，看谁在前面谁在后面

## 成员访问运算符
- 点运算符和箭头运算符都可以访问成员
- ptr->mem等价于`(*ptr).mem`
```c++
 string s1 = "a string", * p = &s1;
 auto n = s1.size(); //运行string对象s1的size成员 n = (*p).size(); //运行p所指对象的size成员
 n = p->size();
```

## 逗号运算符:
- 含有两个运算对象,按照从左向右的顺序依次求值
- 返回结果为右侧表达式的值
```c++
//逗号运算符经常被用在for循环当中
 vector<int> ivec = [1,2,3,4 );
 vector<int>::size_type cnt = ivec.size();
//将把从size到1的值赋给ivec的元素
 for (vector<int>::size_type ix = O; ix != ivec.size(); ++ix, --cnt)
 ivec[ix] = cnt;
```

## sizeof运算符
- 返回所占的字节数
```c++
Sales_data data, * p;
sizeof(Sales_data); //存储Sales_data类型的对象所占的空间大小
sizeof data; //data的类型大小, 即sizeof(Sales_data)
sizeof p; //指针所占的空间大小
//sizeof和*优先级一样,并且满足右结合律
 //所以下面等价于sizeof (*p)
//p可以是无效指针,并不会执行解引用
sizeof *p; //p所指类型的空间大小, 即sizeof(Sales_data)
sizeof data.revenue; //Sales_data的revenue成员对应类型的大小 
sizeof Sales_data::revenue; //另一种获取revenue大小的方式
//sizeof运算能够得到整个数组的大小
constexpr size_t sz = sizeof(ia) / sizeof(*ia);
int arr2[sz]; //正确: sizeof返回一个常量表达式
```

## 类型转换
- 隐式转换:无需程序员介入
	- 算术转换：
	```c++
	 bool  flag;
	 short sval;
	 int ival;
	 long Ival;
	 float fval;
	 char cval;
	 unsigned short unsval;
	 unsigned int uival;
	 unsigned long ulval;
	 double dval;
	 
	 3.14159L + 'a' //'a'提升成int,然后该int值转换成long double
	 dval + ival; //ival转换成double
	 dval + fval; //fval转换成double
	 ival = dval;//dval转换成(切除小数部分后) int
	 flag = dval; //如果dval是0,则flag是false,否则flag是true
	 cval + fval; //cval提升成int,然后该int值转换成float
	 sval + cval; //sval和cval都提升成int
	 cval + Ival; //cval转换成long
	 ival + ulval; //ival转换成unsigned long
	 unsval + ival; //根据unsigend short和int所占空间的大小进行提升 
	 uival + Ival; //根据unsigned int和long所占空间的大小进行转换
	 
	 // 无符号的和有符号的不要混用！
	```

	- 指针的转换
		- 0或字面值nullptr能够转换成任意指针类型
		- 指向任意非常量的指针能够转换成void*
		- 指向任意对象的指针能够转换成const void*
```c++
// 数组转换成指针
int ia[10];//含有10个整数的数组
int *ip = ia;//ia转换成指向数组首元素的指针

/*转换成布尔类型*/
char *cp = get_string();
if (cp) /*..*///如果指针cp不是0,条件为true while (*cp) /**/1/如果*cp不是空字符,条件为true
while (*cp) /*.*///如果*cp不是空字符,条件为true

/*转换成常量*/
int i;
const int &j = i; //非常量转换成const int的引用
const int *p = &i;//非常量的地址转换成const的地址,
int &r = j, *q = p; //错误:不允许const转换成非常量,因为试图删掉底层const

// 类类型定义的转换
string s, t = "a value"; //字符串字面值转换成string类型  "a value"keyi可以理解为c风格的const char * 的类型
while(cin>>s)//while的条件部分把cin转换成布尔值
```

- 显式转换： `cast-name<type> (expression)`
	-  cast-name是static_cast, dynamic_cast, const_cast和reinterpret_cast中的一种。
```c++
 /*static_cast:只要不包含底层const,都可以使用*/
//进行强制类型转换以便指向浮点数除法
int i, j;
double slope = static_cast<double>(j) / i;
double d;
void *p = &d;//正确:任何非常量对象的地址都能存入void*
double *dp = static_cast<double*>(p);//E确
// cosnt_cast:只能改变运算对象的底层const*)
const char *pc;
char *p = const_cast<char*>(pc); //正确:但通过p写值是未定义的行为

const char *cp;
char *q = static_cast<char *p>(cp); //static_cast不能转)const性质 static_cast<string>(cp); //正确
const_cast<string>(cp); //错误
// reinterpret_cast:为运算对象的位模式提供较低层次上的重新解释
int* ip;
char* pc = reinterpret_cast<char*>(ip); //效果类似c风格的强制转换
```
- 旧式的强制转换
```c++
char *pc = (char*) ip;//ip是指向整型的指针,在这里与reinterpret_cast一样
```

## try语句块和异常处理
- 运行时的反常行为。例如读取或写入数据时失去数据库连接
- throw表达式:异常检测部分使用throw表达式来表示它遇到了无法解决的问题，抛出一个异常,终止当前的函数,并把控制权交给处理异常的代码。
-  runtime_error是标准库异常类型的一种,定义在stdexcept头文件
- try语句块:异常处理部分使用try语句块处理异常,可以有一个或多个catch

- 一套异常类: throw表达式和相关的catch子句之间传递异常的具体信息。
- 这些异常类分别定义在4个头文件中:
	1. exception头文件:最通用的异常类exception,只报告异常的发生,不提供额外信息
	2. stdexcept头文件:定义了几种常用的异常类
	3. new头文件: bad_alloc异常类
	4. type_info头文件: bad_cast异常类

## 函数重载:函数名称相同但形参列表不同
- 定义重载函数
```c++
 Record lookup(const Account&);
 bool lookup(const Account&);//错误
 Record lookup(const Phone&);
 Record lookup(const Name&);
 Account acct;
 Phone phone;
 Record r1 = lookup(acct);
 Record r2 = lookup(phone);
```
-  const_cast和重载
```c++
//比较两个string对象的长度,返回较短的那个引用
const string& shorterString(const string& s1, const string& s2){
	return s1.size() <= s2.size() ? s1: s2;
}
string& shorterString(string& s1, string& s2){
	auto& r = shorterString(<const_cast<const string&> (s1), < const_cast<const string&> (s2)); 
	return const_cast<string&>(r);
}
// 强制转换不能省略,否则就成了递归(最佳匹配原则)
```
- 重载与作用域
	- 一旦在当前作用域中找到了所需的名字,编译器就会忽略掉外层作用域中的同名实体
	- 内层比外层优先级高，在同一层的情况下才有重载的情况
- 函数匹配:寻找最佳匹配、不能具有二义性
	- 编译器将实参类型到形参类型的转换划分成几个等级:
		1. 精确匹配
		2. 通过const转换实现的匹配
		3. 通过类型提升实现的匹配
		4. 通过算术类型转换实现的匹配
		5. 通过类类型转换实现的匹配

## 默认实参
- 一旦某个形参被赋予了默认值,它后面的所有形参都必须有默认值
- 只能省略尾部的实参
- 局部变量不能作为默认实参。
- 除此之外,只要表达式的类型能转换成形参所需的类型,就能作为默认实参

## 内联函数:(inline)
- 在每个调用点上“内联地”展开,避免函数调用的开销
- 内联说明只是向编译器发出的一个请求,编译器可以选择忽略这个请求
```c++
//比较两个string对象的长度,返回较短的那个引用
inline const string& shorterString(const string& sl, const string& s2){
	return s1.size() <= s2.size() ? s1: s2;
}
cout<<shorterString(s1,s2)<<endl;
//在编译过程中展开成类似于下面的形式
cout<<( sl.size()<s2.size()?s1:s2)<<endl;
//一般来说,内联机制用于优化规模较小,流程直接、频繁调用的函数
```

## 调试帮助:只在开发过程中使用的代码,发布时屏蔽掉
-  assert预处理宏: cassert头文件中, 用于检测“不能发生”的条件
```c++
//如果表达式为假, assert输出信息并终止程序的执行//如果表达式为真, assert什么也不做
 assert(word.size()>threshold);
```
- NDEBUG预处理变量: assert的行为依赖NDEBUG预处理变量的状态,如果定义了NDEBUG,则assert无效
```c++
#define NDEBUG//关闭调试状态,必须在cassert头文件上面
#include <cassert>
int main( void ){
	int x = 0;
	assert(x);
}
```
- 除了用于assert外,也可以使用NDEBUG编写自己的条件调试代码
```c++
//除了C++编译器定义的__func__之外
//预处理器还定义了另外4个对于程序调试很有用的名字
// __FILE__:存放文件名的字符串字面值。
// __LINE__:存放当前行号的整形字面值。
// __TIME__:存放文件编译时间的字符串字面值。
// __DATE__:存放文件编译日期的字符串字面值。
```

## 函数指针:指针指向的是函数
```c++
//比较两个string对象的长度
 bool lengthCompare(const string &, const string &);
 //该函数的类型是bool (const string &, const string &)
//声明一个可以指向该类型函数的指针,只要用指针替换函数名即可
 bool (*pf)(const string &, const string &); //括号不能少
 
 pf = lengthCompare;
 pf = &lengthCompare; //等价的赋值语句:取地址符是可选的
//可以直接使用指针函数的指针调用该函数,无需提前解引用
 bool b1 = pf("hello","goodbye");
 bool b2 = (*pf)("hello", "goodbye"); //等价的调用
 bool b3 = lengthCompare("hello","goodbye");

 string::size_type sumLength(const string&,const string&); 
 bool cstringCompare(const char*,const char*);
 pf = 0; //正确,pf不指向任何函数
 pf= sumLength; //错误:返回类型不匹配
 pf = cstringCompare; //错误:形参类型不匹配 pf= lengthCompare; //正确:函数和指针的类型精确匹配

```
- 重载函数的指针:必须精确匹配
```c++
 void ff(int *);
 void ff(unsigned int);
 void (*pf1)(unsigned int) = ff; //pf1指向ff(unsigned)void (*pf2)(int) = ff; //错误:没有任何一个ff与该形参列表匹配
 double (*pf3)(int *) = ff; //错误: ff和pf3的返回类型不匹配
```
- 函数指针形参
- 不能定义函数类型的形参,但是形参可以是指向函数的指针
```c++
//第三个形参是函数类型,它会自动地转换成指向函数的指针
 void useBigger(const string &sl, const string &s2, bool pf(const string &, const string &));
//等价的声明:显式地将形参定义成指向函数的指针,
 void useBigger(const string &s1, const string &s2, bool (*pf)(const string &, const string &));

//可以直接把函数作为实参使用,会自动转换成指针 
useBigger(s1,s2,lengthCompare);

/通过使用类型别名,简化使用函数指针
 //Func和Func2是函数类型
 typedef bool Func(const string&, const string&); 
 typedef decltype(lengthCompare) Func2; //等价的类型
 //FuncP和FuncP2是指向函数的指针
 typedef bool(*FuncP)(const string&,const string&); 
 typedef decltype(lengthCompare) *FuncP2;//等价的类型
 //useBigger的等价声明,其中使用了类型别名
 void useBigger(const string&, const string&,Func); 
 void useBigger(const string&, const string&,FuncP2);
```
- 不能返回函数,但可以返回指向函数的指针(和函数类型的形参不一样,返回类型必须写成指针形式)

## IO类
- 每个输出流都管理一个缓冲区
- 有了缓冲机制,操作系统就可以在需要时将程序的多个输出操作合并，提高性能
- 如果程序崩溃,输出缓冲区不会被刷新
```c++
//刷新输出缓冲区
cout<< "hi!" <<endl; //输出hi和一个换行,然后刷新缓冲区
cout<< "hi!" <<flush; //输出hi,然后刷新缓冲区,不附加任何额外字符
cout<< "hi!" <<ends; //输出hi和一个空字符,然后刷新缓冲区

//通过设置unitbuf操纵符来控制是否立即刷新
cout<<unitbuf; //所有输出操作后都会立即刷新缓冲区 
cout<<nounitbuf; //回到正常的缓冲方式
```


## 参数绑定(bind函数)
- 调用bind的一般形式为:`auto newCallable = bind (callable, arg_list); `
- 定义在functional头文件中
```c++
 using namespace std;
 using namespace std::placeholders;
 vector<string> words = ["string1", "abcde" ); 
 bool check_size(const string& s, string::size_type sz){
	 return s.size() >= Sz;
 }

int main(){
	//check6是一个可调用对象,接受一个string类型的参数
	 //并用此string和值6来调用check_size
	 auto check6 = bind(check_size,_1, 6);
	 string s = "hello";
	 bool b1 = check6(s);//check6(s)a调用check_size(s,6),
	 auto wc = find if(words.begin(), words.end(), bind(check_size, _1, 6));
	 auto wc2 = find if(words.begin(), words.end(), check6);
}
```
- bind的参数
```c++
//g是一个有两个参数的可调用对象 
auto g = bind(f,a,b,_2,c,_1);
 //g(X,Y)的调用会映射到: f(a,b,Y,c,X)
```
- 用bind重排参数顺序
```c++
//按单词长度由短至长排序
 sort(words.begin(),words.end(),isShorter);
//按单词长度由长至短排序
 sort(words.begin(), words.end(),bind(isShorter,_2,_1)); 
 //当sort需要比较两个元素A和B时,调用isShorter(A,B)
 //当sort比较两个元素时,就好像调用了isShorter(B,A)一样
```
- 绑定引用参数:默认情况下, bind的那些不是占位符的参数会被拷贝
```c++
//错误:不能拷贝os
 for_each(words.begin(),words.end(), bind(print,os,_1,' '));
//对于ostream对象,不能拷贝。必须使用标准库ref函数包含给定的引用 
for_each(words.begin(),words.end(), bind(print,ref(os),_1,' '));
```

