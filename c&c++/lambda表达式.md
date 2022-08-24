
![[Pasted image 20220801202729.png]]

### lambda捕获和返回
•向函数传递lambda时，同时定义了一个（未命名的）新类型和该类型的一个对象。
•默认情况下，新类型包含了捕获的变量，作为数据成员。
```c++
// 值捕获
void fcn1(){
	size_t v1 = 42;  // 局部变量
	// 将v1拷贝到名为f的可调用对象
	auto f = [v1] { return v1; };
	v1 = 0;
	auto j = f(); // j 为 42; f stored a copy of v1 when we created it
}

// 引用捕获
void fcn2(){
	size_t v1 = 42;  // local variable
	// the object f2 contains a reference to v1
	auto f2 = [&v1] { return v1; };
	v1 = 0;
	auto j = f2(); // j is 0; f2 refers to v1; it doesn't store it
}

当以引用方式捕获一个变量时，必须保证在lambda执行时变量时存在的
```
- 隐式捕获：让编译器根据lambda体中的代码来推断需要使用哪些变量
![[Pasted image 20220801203516.png]]

