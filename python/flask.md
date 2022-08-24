
#### WSGI
- web服务器与web框架之间通信的协议，Web Server Gateway Interface

#### Flask介绍

- 其` WSGI`工具箱采用` Werkzeug`（路由模块），模板引擎则使用` Jinja2`这两个也是 Flask 框架的核心

#### Flask常用扩展包：

- Flask-SQLalchemy：操作数据库；
- Flask-script：插入脚本；
- Flask-migrate：管理迁移数据库；
- Flask-Session：Session存储方式指定；
- Flask-WTF：表单；
- Flask-Mail：邮件；
- Flask-Bable：提供国际化和本地化支持，翻译；
- Flask-Login：认证用户状态；
- Flask-OpenID：认证；
- Flask-RESTful：开发REST API的工具；
- Flask-Bootstrap：集成前端Twitter Bootstrap框架；
- Flask-Moment：本地化日期和时间；
- Flask-Admin：简单而可扩展的管理接口的框架

#### 路由

- 查看所有路由：app.url_map

- 给路由添加参数：url里携带<类型：param>

#### Jinjia2模版引擎

- 对html的处理进行了封装

- render_template('xxxx.html', xxx=xxxx....)

- 控制代码块主要包含两个：

  1. `for`循环

     - 在一个 for 循环块中你可以访问这些特殊的变量:

     | 变量           | 描述                                  |
     | :------------- | :------------------------------------ |
     | loop.index     | 当前循环迭代的次数（从 1 开始）       |
     | loop.index0    | 当前循环迭代的次数（从 0 开始）       |
     | loop.revindex  | 倒序，当前循环迭代的次数（从 1 开始） |
     | loop.revindex0 | 倒序，当前循环迭代的次数（从 0 开始） |
     | loop.first     | 如果是第一次迭代，为 True             |
     | loop.last      | 如果是最后一次迭代，为 True           |
     | loop.length    | 序列中的项目数                        |

  2. `if`判断

     `Jinja2模板引擎` 语法中的if语句跟 Python 中的 if 语句相似, if 判断的结果是布尔值，将决定代码中的哪个流程会被执行

#### SQLAlchemy
- 

#### MVT模型

- **models**
- **views**
- **templates**
- static静态文件

#### 重定向

- redirect("url")
- redirect(url_for("视图函数"))

### Blueprint(蓝图)

#### 1. Blueprint概念

简单来说，Blueprint 是一个存储操作方法的容器，这些操作在这个Blueprint 被注册到一个应用之后就可以被调用，Flask 可以通过Blueprint来组织URL以及处理请求。

Flask使用Blueprint让应用实现模块化，在Flask中，Blueprint具有如下属性：

- 一个应用可以具有多个Blueprint
- 可以将一个Blueprint注册到任何一个未使用的URL下比如 “/”、“/sample”或者子域名
- 在一个应用中，一个模块可以注册多次
- Blueprint可以单独具有自己的模板、静态文件或者其它的通用操作方法，它并不是必须要实现应用的视图和函数的
- 在一个应用初始化时，就应该要注册需要使用的Blueprint

但是一个Blueprint并不是一个完整的应用，它不能独立于应用运行，而必须要注册到某一个应用中。

#### 2. 运行机制

- 蓝图是保存了一组将来可以在应用对象上执行的操作，注册路由就是一种操作
- 当在应用对象上调用 route 装饰器注册路由时,这个操作将修改对象的url_map路由表。然而，蓝图对象根本没有路由表，当我们在蓝图对象上调用route装饰器注册路由时,它只是在内部的一个延迟操作记录列表defered_functions中添加了一个项
- 当执行应用对象的 register_blueprint() 方法时，应用对象将从蓝图对象的 defered_functions 列表中取出每一项，并以自身作为参数执行该匿名函数，即调用应用对象的 add_url_rule() 方法，这将真正的修改应用对象的路由表

#### 3. 蓝图的url前缀

- 当我们在应用对象上注册一个蓝图时，可以指定一个url_prefix关键字参数（这个参数默认是/）

- 在应用最终的路由表 url_map中，在蓝图上注册的路由URL自动被加上了这个前缀，这个可以保证在多个蓝图中使用相同的URL规则而不会最终引起冲突，只要在注册蓝图时将不同的蓝图挂接到不同的自路径即可

- url_for

  ```python
  url_for('admin.index')  # /admin/index
  ```

### cookie

- Cookie是由服务器端生成，发送给客户端浏览器，浏览器会将Cookie的`key：value`保存，下次请求同一网站时就发送该Cookie给服务器（前提是浏览器设置为启用cookie）

  Cookie的`key：value`可以由服务器端自己定义

### session

- Session是另一种记录客户状态的机制，不同的是Cookie保存在客户端浏览器中，而Session保存在服务器上。客户端浏览器访问服务器的时候，服务器把客户端信息以某种形式记录在服务器上。这就是Session。客户端浏览器再次访问时只需要从该Session中查找该客户的状态就可以了session是一种特殊的cookie。cookie是保存在客户端的，而session是保存在服务端。
- 当客户端第一次请求服务器的时候，服务器生成一份session保存在服务端，将该数据(session)的id以cookie的形式传递给客户端；以后的每次请求，浏览器都会自动的携带cookie来访问服务器(session数据id)。

### cookie和session区别

- cookie是保存在客户端的
- cookie有大小限制
- session是保存在服务器端
- session更加安全
- session会比较占用服务器性能，当访问增多时应用cookie

### get和post

- GET与POST不同点最直接的体现在：
  - GET：放到URL中，又因为不同的浏览器对URL支持的长度不同，向谷歌浏览器URL最大长度限制为8182个字符，所以不能放入太多的数据
  - POST：放到body中，body的长度不限，所以可以提交大量的数据

### 提取请求的数据

- request.args 只能提取query参数，也就是url中的 ？后面的参数
- request.form 可以提取body里的数据
- request.files 提取文件

### Flask-SQLAlchemy

- 

###  flask对象配置方式

在 Flask 程序运行的时候，可以给 Flask 设置相关配置，比如：配置 `Debug`模式，配置数据库连接地址等等，设置 Flask 配置有以下三种方式：

- 从配置对象中加载(常用)

  `app.config.from_object()`

- 从配置文件中加载

  `app.config.from_pyfile()`

- 从环境变量中加载(了解)

  `app.config.from_envvar()`

### 异常捕获

####  HTTP 主动抛出异常

`abort` 方法

功能：抛出一个给定状态代码的 `HTTPException` 或者 指定响应，例如想要用一个页面未找到异常来终止请求，你可以调用 `abort(404)`

参数：状态码

```python
# abort(404)
abort(500)复制Error复制成功...
```

> 抛出状态码的话，只能抛出 HTTP 协议的错误状态码

#### 捕获错误状态码

```
errorhandler 装饰器
```

说明：errorhandler注册一个错误处理程序，当程序抛出指定错误状态码的时候，就会调用该装饰器所装饰的方法

参数：HTTP的错误状态码或指定异常

demo1：统一处理状态码为500的错误

```python
@app.errorhandler(500)
def internal_server_error(e):
    return '服务器搬家了'
```

### 钩子函数

钩子函数是指在执行函数和目标函数之间挂载的函数, 框架开发者给调用方提供一个**point** -挂载点, 至于挂载什么函数由我们调用方决定, 这样大大提高了灵活性

#### flask的四种请求钩子函数

- before_first_request

  在处理第一个请求前执行

- before_request

  在每次请求前执行

  如果在某修饰的函数中返回了一个响应，视图函数将不再被调用

- after_request

  如果没有抛出错误，在每次请求后执行

  接受一个参数：视图函数作出的响应

  在此函数中可以对响应值在返回之前做最后一步修改处理

  需要将参数中的响应在此参数中进行返回

- teardown_request：

  在每次请求后执行

  接受一个参数：错误信息，如果有相关错误抛出

- 注意
  - 在debug模式下，teardown_request装饰的函数不会执行；
  - after_request请求钩子会自动传入response对象作为参数，同时必须返回一个response对象；
  - before_request装饰的函数不需要返回数据，如果返回了数据，那么视图函数不会再执行，而是直接返回结果。

### 上下文

上下文：相当于一个容器，保存了 Flask 程序运行过程中的一些信息

Flask中有两种上下文

- 请求上下文
- 应用上下文

#### 1. 请求上下文(request context

思考：在视图函数中，如何取到当前请求的相关数据？比如：请求地址，请求方式，cookie等等

在 flask 中，可以直接在视图函数中使用 `request` 这个对象进行获取相关数据，而 `request` 就是请求上下文的对象，保存了当前本次请求的相关数据，请求上下文对象有：request、session

- request 封装了HTTP请求的内容，针对的是http请求。举例：`user = request.args.get('user')`获取的是get请求的参数
- session 用来记录请求会话中的信息，针对的是用户信息。举例：`session['name'] = user.id`可以记录用户信息。还可以通过`session.get('name')`获取用户信息

#### 2. 应用上下文(application context)

它的字面意思是 应用上下文，但它不是一直存在的，它只是request context 中的一个对 app 的代理(人)，所谓local proxy。它的作用主要是帮助 request 获取当前的应用，它是伴 request 而生，随 request 而灭

应用上下文对象有：

- `current_app`
- `g`

##### current_app

应用程序上下文，用于存储应用程序中的变量，可以通过current_app.name打印当前app的名称，也可以在current_app中存储一些变量，例如：

- 应用的启动脚本是哪个文件，启动时指定了哪些参数
- 加载了哪些配置文件，导入了哪些配置
- 连了哪个数据库
- 有哪些public的工具类、常量
- 应用跑再哪个机器上，IP多少，内存多大

```python
current_app.name
current_app.test_value='value'
```

##### g变量

g 作为 flask 程序全局的一个临时变量,充当者中间媒介的作用,我们可以通过它传递一些数据，g 保存的是当前请求的全局变量，不同的请求会有不同的全局变量，通过不同的thread id区别

```python
g.name='abc'
```

> 注意：不同的请求，会有不同的全局变量

##### 两者区别：

- 请求上下文：保存了客户端和服务器交互的数据
- 应用上下文：flask 应用程序运行过程中，保存的一些配置信息，比如程序名、数据库连接、应用信息等

### 分页

#### paginate()

- paginate(偏移量，取出量)函数,用于BaseQuery，是SQLAlchemy里的函数，不是flask

- paginate的属性、方法说明：

```python
has_next：判断是否有下一页
has_prev：判断是否有上一页
next_num：返回下一页页码
prev_num：返回上一页页码
page ：当前页码
pages：总页数
per_page：每一页的数据量
prev():返回Pagination上一页的对象
next():返回Pagination下一页的对象
items:返回当前页面项目，可遍历
iter_pages(left_edge = 2，left_current = 2，right_current = 5，right_edge = 2):迭代分页中的页码
```

### 邮箱

#### flask-email

### jinja2模版引擎

#### 宏macro

#### 模版继承

#### include

#### 过滤器

- 过滤器的本质就是函数

### 数据库迁移

### flask-migrate

### CSRF

- `CSRF`全拼为`Cross Site Request Forgery`，译为跨站请求伪造
- `CSRF`指攻击者盗用了你的身份，以你的名义发送恶意请求 包括：以你名义发送邮件，发消息，盗取你的账号，甚至于购买商品，虚拟货币转账......
- 造成的问题：个人隐私泄露以及财产安全

![img](https://doc.itprojects.cn/0001.zhishi/python.0026.flaskgaoji/assets/CSRF%E6%94%BB%E5%87%BB%E8%BF%87%E7%A8%8B.png)

#### 防止 CSRF 攻击思路

1. 在浏览器向服务器请求时，服务器通过session的方式将得到的随机值(可以用hash)存储在服务器
2. 且在页面中添加一个隐藏（隐藏的目的是不让用户看见，看见也没有任何用处）的的值，这个值与上一步的值一样
3. 在用户点击提交的时候，将隐藏的那个值一起传递给后端服务器
4. 服务器接下来从session提取第1步生成的数据，与第3步隐藏的那个数据进行判断是否想相等
   1. 如果比较之后两值一样，那么代表是正常的请求
   2. 如果没取到或者比较不一样，代表不是正常的请求，不执行下一步操作
