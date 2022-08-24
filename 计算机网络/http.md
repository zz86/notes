
#### HTTP/HTTPS
- HTTP，超文本传输协议，端口80
- HTTPS = HTTP + SSL（安全套接字层），即带有安全套接字层的超文本传输协议
- HTTPS比HTTP更安全，但是性能更低
- HTTP是TCP协议的字符串

#### HTTP GET请求的格式：
```
GET /path HTTP/1.1
Header1: Value1
Header2: Value2
Header3: Value3
```

- 每个Header一行一个，换行符是\r\n。

#### HTTP POST请求的格式：
```
POST /path HTTP/1.1
Header1: Value1
Header2: Value2
Header3: Value3

body data goes here...
```

- 当遇到连续两个\r\n时，Header部分结束，后面的数据全部是Body。

#### HTTP响应的格式：
```
200 OK
Header1: Value1
Header2: Value2
Header3: Value3

body data goes here...
```

- HTTP响应如果包含body，也是通过`\r\n\r\n`来分隔的。
- Body的数据类型由Content-Type头来确定，如果是网页，Body就是文本，如果是图片，Body就是图片的二进制数据。
- 当存在Content-Encoding时，Body数据是被压缩的，最常见的压缩方式是gzip，所以，看到Content-Encoding: gzip时，需要将Body数据先解压缩，才能得到真正的数据。压缩的目的在于减少Body的大小，加快网络传输。

#### request header
- referer告诉服务器这个请求是从哪里发起的，例如img请求
- user-agent （网上搜一大堆）

#### response header


#### 响应代码
- 200表示成功，3xx表示重定向，4xx表示客户端发送的请求有错误，5xx表示服务器端处理时发生了错误