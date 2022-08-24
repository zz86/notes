#### 快速入门

- 内部标签

```html
<script>
	<!-- javascript代码 -->
</script>
```

- 外部引入

```html
<script src="js/helloworld.js"></script>
```

#### 基本语法入门

- `js`不区分小数和整数
  - `NaN：not a number`
  - `Infinity`：无穷大

- 比较运算符
  - == 等于（类型不一样，值一样，也会判断为true）
  - ===绝对等于（类型一样，值也一样，结果为true）
- `NaN===NaN`返回`false`，NaN与所有的数值都不想等，包括自己，只能通过`isNaN(NaN)`来判断是否是NaN

- 浮点数问题
  - `(1/3)===(1-2/3)`返回`false`
  - 尽量避免使用浮点数进行计算，存在精度问题！
  - `Math.abs(1/3-(1-2/3))<0.00000001`该方法可以判断

- `null`空
- `undifined`未定义

- 取数组下标，如果越界了会返回`undefined`

- 对象是大括号，数组是中括号，对象里的每个属性用逗号隔开，最后一个不需要逗号
- 所有变量都是`var`

#### 严格检查模式

- 前提：需要使用设置支持`ES6`语法

- `use strict`：预防`javascript`的随意性导致产生的一些问题，必须写在`javascript`的第一行！
- 建议局部变量都使用let去定义

#### 数据类型

- 字符串
  - 多行字符串编写：用反引号包裹起来
  - 模板字符串：用反引号包裹起来，并且含有`${xxx}`，`xxx`是已定义的变量

- 数组
  - Array可以包含任意的数据类型
  - `indexOf()`通过元素获得下标索引
  - `concat()`拼接数组，并没有修改数组，而是返回一个新的数组
  - 连接符`join`，打印拼接数组，使用特定的字符串连接

- 对象：若干个键值对
  - `js`的对象，`{...}`表示一个对象，所有的键都是字符串，值是任意对象
  - 使用一个不存在的对象属性不会报错！`undeifined`
  - 对象的删减属性，通过delete删除对象的属性
  - 动态的添加，直接给属性添加值即可
  - 判断属性值是否在这个对象中：`xxx in xxx`

- 流程控制
  - `forEach`循环
  - `for...in`

#### 函数

- 定义方式一：

  `function abs(x){...}`

- 定义方式二，匿名函数

  `var abs = function(x){...}`

#### JSON

- 在`javascript`中一切皆对象，任何js支持的类型都可以用`JSON`表示：number、string...

- 格式：
  - 对象都用{}
  - 数组都用[]
  - 所有的键值对都用key：value
- `JSON`和`javascript`对象的转化
  - `JSON.stringify()`
  - `JSON.parse()`

#### 面向对象

- 原型
- 原型链
- `class`

#### 操作BOM对象（浏览器对象模型）

- window代表浏览器窗口
- Navigator封装了浏览器的信息
- screen代表屏幕尺寸
- location代表当前页面的URL信息
- document代表当前的页面，HTML DOM文档树，网页的具体内容
- history代表浏览器的历史记录

#### 操作DOM对象（文档对象模型）

- 浏览器网页就是一个DOM树形结构

  - 获得DOM节点

  - 更新DOM节点
  - 遍历DOM节点
  - 删除DOM节点
  - 添加DOM节点

#### 操作表单

- 表单的目的：提交信息

  - 文本框 text

  - 下拉框 <select>

  - 单选框 radio

  - 多选框 checkbox

  - 隐藏域 hidden

  - 密码框 password

  - ......

- 提交表单

#### Ajax

- Asynchromous JavaScript and XML
- xhr = XMLHttpRequest

#### jQuery库

- 事件驱动，操作Dom对象

- 公式`$(selector).action()`，selector选择器，action事件
- css选择器
  - 标签
  - id
  - 类
  - ......
- 事件
  - 鼠标事件
  - 键盘事件
  - ......

#### axios

- 发送请求
- 拦截器
- 取消请求

#### Promise

- promise是一门新的技术（ES6规范），是JS中进行异步编程的新解决方案（旧方案是单纯使用回调函数）

  - 从语法上说：promise是一个构造函数
  - 从功能上说：promise对象用来封装一个异步操作并可以获取其成功/失败的结果值

- 异步编程：

  - fs文件操作

  - 数据库操作

  - AJAX

  - 定时器

    ......

- 使用promise的优点：
  1. 指定回调函数的方式更加灵活
     - 旧方案必须在启动异步任务之前指定
     - promise：启动异步任务 => 返回promise对象 => 给promise对象绑定回调函数（甚至可以在异步任务结束后指定/多个）
  2. 支持链式调用，可以解决回调地狱问题
     - 回调地狱：回调函数嵌套调用，外部回调函数异步执行的结果是嵌套的回调执行的条件
     - 回调地狱的缺点：不便于阅读，不便于异常处理
- 可以util.promisify()方法进行promise风格转化
- Promise的状态：实例对象中的一个属性（**PromiseState**）。转变形式只有两种：pending 变为 resolved，pending 变为 rejected，且一个promise对象只能改变一次。无论成功还是失败，都会有一个结果数据，成功的结果一般称为value，失败的结果数据一般称为reason
  1. pending 未决定的
  2. resolved / fullfilled 成功
  3. rejected 失败

- Promise对象的值：实例对象中的另一个属性（**PromiseResult**），保存着异步任务成功或者失败的结果。由resolve()函数和reject()函数改变。

- Promise的构造函数：Promise(executor){}

  1. executor函数：执行器 (resolve,reject) => {}
  2. resolve函数：内部定义成功时调用的函数 value => {}
  3. reject 函数：内部定义失败时调用的函数 reason => {}

  说明：executor会在Promise内部立即同步调用，异步操作在执行器中执行

- Promise.prototype.then 方法：(onResolved,onRejected) => {}

  1. onResolved函数：成功的回调函数 (value) => {}
  2. onRejected函数：失败的回调函数 (reason) => {}

  说明：指定用于得到成功value的成功回调和用于得到失败reason的失败回调返回一个新的promise对象

- Promise.prototype.catch 方法：(onRejected) => {}

  1. onRejected函数：失败的回调函数 (reason) => {}

- Promise.resolve 方法：(value) => {}

  1. value：成功的数据或者promise对象

  说明：返回一个成功/失败的promise对象

- Promise.reject 方法：(reason) => {}

  1. reason：失败的原因

  说明：返回一个失败的promise对象

- 如果为一个promise对象指定多个成功/失败回调函数，当promise改变为对应状态时都会调用
- promise的then()返回一个新的promise对象，其结果状态由then()指定的回调函数执行的结果决定，具体说来：
  1. 如果抛出异常，新promise变为rejected，reason为抛出的异常
  2. 如果返回的是非promise的任意值，新promise变为resolved，value为返回的值
  3. 如果返回的是另一个新promise，此promise的结果就会成为新promise的结果

- 通过then的链式调用串联起多个同步/异步任务，并且可以只在最后指定失败的回调，也即前面任何操作出了异常，都会传到最后失败的回调中处理，中断方法只有一个：在回调函数中返回一个pendding状态的promise对象
- async函数
  - 函数的返回值为promise对象
  - promise对象的结果由async函数执行的返回值决定，和then返回结果的规则一样
- await函数
  - await函数的右侧一般为promise对象，但也可以是其它的值
  - 如果表达式是promise对象，await返回的是promise成功的值
  - 如果表达式是其他值，直接将此值作为await的返回值

#### ES6

- let和const命令

  - 传统定义变量和常量的方式，统一使用var

  - ES6定义的方式：let变量，const常量

    - let和const解决了什么问题：

      1. var的变量穿透问题

      2. 常量修改的问题


  - 注意事项：在实际开发中和生产中，如果是nodejs，小程序，uniapp或者是一些脚手架中，可以大胆的去使用let和const，但是如果是web开发，建议还是使用var，因为在一些低版本的浏览器还是不支持let和const


- 模板字符串
  - ${变量名}


- 函数默认参数与箭头函数
  - 箭头函数
    - 在小程序、uniapp或者一些常见的脚手架中大量使用
    - 普通函数如何变为箭头函数：
      1. 去掉function
      2. 在括号后面加箭头 =>
      3. 如果逻辑代码仅有return可以直接省去，如果有逻辑体就不能省去
      4. 如果参数只有一个，可以把括号也省去


- 对象初始化简写
  - 如果key和变量的名字一致，可以只定义一次即可
  - 如果value是一个函数，可以把:function去掉，只剩下()即可

- 对象解构：快捷获取对象属性和行为方式
  - 对象是key:value存在，获取对象属性和方法的方式有两种
    - 通过 .
    - 通过 []
  - `var {title,link} = info;`
  - `var title = info.title;` `var link = info.link`
  - 以上两种方式等同，函数也可以解构

- 传播操作符[...]：把一个对象的属性传播到另一个对象中

- 数组map方法：自带循环，并且会把处理后的值回填到对应的位置
- 数组reduce方法

#### 模块化

- CommonJS规范  `const xxx = require('xxx'`)
- ES6规范   `import xxx from 'xxx'`

#### Babel

- ES6的高级语法在浏览器环境甚至是Node.js环境中无法运行，Babel是一个广泛使用的转码器，可以将ES6的代码转为ES5的代码，从而在现有环境中执行

#### webpack

- 

#### 前端小技巧

- 如何巩固JS：看jQuery源码，看游戏源码！

- 如何巩固HTML，CSS：扒网站，全部down下来，然后修改看效果~
