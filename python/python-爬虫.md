#### 正则表达式

- Python中字符串前面加上 r 表示原生字符串，与大多数编程语言相同，正则表达式里使用"\"作为转义字符，这就可能造成反斜杠困扰。假如你需要匹配文本中的字符""，那么使用编程语言表示的正则表达式里将需要4个反斜杠`\`：前两个和后两个分别用于在编程语言里转义成反斜杠，转换成两个反斜杠后再在正则表达式里转义成一个反斜杠。

  Python里的原生字符串很好地解决了这个问题，有了原生字符串，你再也不用担心是不是漏写了反斜杠，写出来的表达式也更直观。

- pattern.match 从头找一个
- pattern.search 找一个
- pattern.findall  找所有
- pattern.sub 替换
- re.compile

#### selenium

- 等待页面元素到来

```python
# 创建等待操作对象
wait_ob = WebDriverWait(driver, 10)#最多等待10s
i_understand = wait_ob.until(expected_conditions.presence_of_element_located((By.XPATH, "//*[@id='wapat']/div/div[2]/div")))
```

#### Pyppeteer

- selenium升级版，无法被检测到
- 支持chromium浏览器和asyncio框架，默认无头浏览器
- 一些网站主要通过 window.navigator.webdriver 来对 webdriver 进行检测，所以我们只需要使用 JavaScript 将它设置为 false 即可

#### requests

- Content-Length  stream=True  iter_content
- 请求头headers
  - cookie
  - user-agent
- 响应头
- 发送带查询参数的URL
  - params={}
  - URL中直接携带
- post请求体，默认都是form表单
  - data={}，form表单
  - json={}，json
- http是无状态的，cookie存在浏览器，session存在服务器
- 发送请求时携带cookie有三种方法
  1. cookie字符串放在headers中
  2. 把cookie字典传给请求方法的cookies参数接收
  3. 使用requests提供的session模块
- 获取响应头的cookie
  - `response.cookies`是`CookieJar`类型
  - 使用`requests.utils.dict_from_cookiejar`，能够实现把`cookiejar`对象转化为字典
- allow_redirects=False，不允许重定向，r.history重定向记录
- SSL证书，verify=False
- 超时设定，timeout=1
- retrying模块，装饰器
  - 自动尝试指定次数执行函数
- Session会话
  - 保存cookie，下一次请求会自动带上前一次响应头的set-cookie
  - 实现和服务端的长连接，加快请求速度
  - 
- HTTP代理 proxies

#### 提取数据

- 结构化数据：json，xml等
  - 处理方式：直接转化为python类型：json.loads()  json.dumps()

- 非结构化数据：HTML
  - 处理方式：正则表达式、xpath、BS4

- xpath

  - 谷歌浏览器插件xpath helper

  - lxml，返回值是一个列表，还可以继续用xpath

  - xpath语法

    | 表达式     | 描述                                                     |
    | :--------- | :------------------------------------------------------- |
    | `nodename` | 选中该元素                                               |
    | `/`        | 从根节点选取、或者是元素和元素间的过渡                   |
    | `//`       | 从匹配选择的当前节点选择文档中的节点，而不考虑它们的位置 |
    | `.`        | 选取当前节点                                             |
    | `..`       | 选取当前节点的父节点                                     |
    | `@`        | 选取属性                                                 |
    | `text()`   | 选取文本                                                 |

- jsonpath
  - 快速取字典中的数据

- Beautifal Soup   简称BS4  最简单，速度最慢

  - 提取xml中的数据
  - 有自动补全

  - find_all
  - select

#### scrapy 爬虫框架

- 

#### pyspider



#### 抓包工具

- charles
- Fiddler
