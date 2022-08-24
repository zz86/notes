
## psutil
- psutil 是一个跨平台库(http://code.google.com/p/psutil/) ,能够轻松实现获取系统运行的进程和系统利用率(包括CPU、内存、磁盘、网络等)信息。
- 它实现了同等命令行工具提供的功能,如ps,top, Isof, netstat, ifconfig, who. df, kill, free, nice, ionice, iostat, iotop, uptime, pidof, tty, taskset. pmap 等。

## IPy
- IPy模块包含IP类,使用它可以方便处理绝大部分格式为IPv6 及IPv4的网络和地址。
- 比如通过version方法就可以区分出IPv4与IPv6,如:
```python
IP('10.0.0.0/8').version()
# 4代表IPv4类型
IP('::1').version()
# 6代表IPv6类型
```
- 多网络计算方法详解
	- 有时候我们想比较两个网段是否存在包含、重叠等关系,比如同网络但不同prefixlen 会认为是不相等的网段,如10.0.0.0/16不等于10.0.0.0/24,另外即使具有相同的 prefixlen,但处于不同的网络地址,同样也视为不相等,如10.0.0.0/16 不等于192.0.0.0/16。 IPy支持类似于数值型数据的比较,以帮助IP对象进行比较

## dnspython
- dnspython (http://www.dnspython.org/)Python 实现的一个 DNS 工具包, 它支持几乎所有的记录类型,可以用于查询、传输并动态更新ZONE信息,同时支持TSIG (事务签名)验证消息和EDNSO (扩展DNS)。在系统管理方面,我们可以利用其查询功能来实现DNS服务监控以及解析结果的校验,可以代替nslookup及 dig等工具,轻松做到与现有平台的整合
- dns记录详解
	1. A记录,将主机名转换成IP地址;
	2. MX记录,邮件交换记录,定义邮件服务器的域名;
	3. CNAME 记录,指别名记录,实现域名间的映射;  ftp
	4. NS记录,标记区域的域名服务器及授权子域;
	5. PTR记录,反向解析,与A记录相反,将IP转换成主机名;
	6. SOA 记录, SOA标记,一个起始授权区的定义。
- dns常见解新类型示例说明:
	- 常见的DNS解析类型包括A、MX、NS、CNAME 等。利用dnspython的dns.resolver.
	- query方法可以简单实现这些DNS类型的查询,为后面要实现的功能提供数据来源,比如对一个使用DNS 轮循业务的域名进行可用性监控,需要得到当前的解析结果。

## 文件内容差异对比difflib
- difflib作为Python的标准库模块,无需安装,作用是对比文本之间的差异,且支持输出可读性比较强的HTML文档,与Linux下的diff命令相似。我们可以使用difflib对比代码、配置文件的差别,在版本控制方面是非常有用。

## 文件与目录差异对比方法filecmp
- 当我们进行代码审计或校验备份结果时,往往需要检查原始与目标目录的文件一致性,Python的标准库已经自带了满足此需求的模块filecmpo filecmp可以实现文件、目录、遍历子目录的差异对比功能。比如报告中输出目标目录比原始多出的文件或子目录,即使文件同名也会判断是否为同一个文件(内容级对比)等
- 单文件对比,采用filecmp.cmp(fl, f2[, shallow])方法,比较文件名为fl和f2的文 件,相同返回True,不相同返回False, shallow默认为True,意思是只根据os.stat()方法返回的文件基本信息进行对比,比如最后访问时间、修改时间、状态改变时间等
-  多文件对比,采用filecmp.cmpfiles(dirl, dir2, common[, shallow])方法,对比dir1 与dir2目录给定的文件清单。该方法返回文件名的三个列表,分别为匹配、不匹配、错误。匹配为包含匹配的文件的列表,不匹配反之,错误列表包括了目录不存在文件、不具备读权限或其他原因导致的不能比较的文件清单。

## 发送电子邮件模块smtplib
- 普通文本
- MIME富文本    html网页
- MIME+照片
- 附件

## Pycurl模块
-  pycurl (http://pycurl.sourceforge.net) 用C语言写的 libcurl Python 实现,功能非常强大,支持的操作协议有FTP、 HTTP、 HTTPS、TELNET等,可以理解成Linux 下 curl 命令功能的Python 封装,简单易用。本节通过调用pycurl提供的方法,实现探测Web服务质量的情况,比如响应的HTTP状态码、请求延时、HTTP头信息、下载速度等,利用这些信息可以定位服务响应慢的具体环节

## Scapy模块
- scapy (http://www.secdev.org/projects/scapy/)是一个强大的交互式数据包处理程序,它能够对数据包进行伪造或解包,包括发送数据包、包嗅探、应答和反馈匹配等功能。可以用在处理网络扫描、路由跟踪、服务探测、单元测试等方面,本节主要针对scapy的路由跟踪功能,实现TCP协议方式对服务可用性的探测,比如常用的80 (HTTP)与443 (HTTPS)服务,并生成美观的路由线路图报表,让管理员清晰了解探测点到目标主机的服务状态、骨干路由节点所处的IDC位置、经过的运营商路由节点等信息。

## paramiko模块 
- ssh执行命令

## fabric模块 
- paramiko的封装