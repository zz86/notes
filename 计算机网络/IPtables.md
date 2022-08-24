
## IPtables介绍
- Netfilter/Iptables(以下简称Iptables)是unix/linux自带的一款优秀且开放源代码的完全自由的基于包过滤的防火墙工具,它的功能十分强大,使用非常灵活,可以对
流入和流出服务器的数据包进行很精细的控制。
- netfilter:内核态,即不以文件和形式存在(kernal space)的防火墙。是实现防火墙的功能
- iptables :用户态,在/sbin/iptables存在(User space)的防火墙。操作上二者没有区分。
- 用户和内核交互的一个工具就是iptables.
- 注: iptables主要工作在OSI七层的3和4层。七层的控制可以使用squid代理+iptables

## iptables工作原理分类:
- 主机防火墙:主要是用来防范单台主机的进出报文;
- 网络防火墙:工作与一个网络的边缘,能够实现对进出本网络的所有主机报文加以防护;

## iptables表和链和规则
- 默认情况下,iptables根据功能和表的定义划分包含三个表,filter,nat,mangle,其每个表又包含不同的操作链(chains)。实际iptables包含4张表和五个链,主要记住 filter即可。

### 四个表
- 必须是小写
1. raw                追踪数据包,----此表用处较少,可以忽略不计
2. mangle          给数据打标记,做标记
3. nat                 网络地址转换即来源与目的的IP地址和port的转换。应用:和主机本身无关
4. filter               做过滤的,防火墙里面用的最多的表。
- 表的应用顺序: raw-》mangle-》nat-》filter

### 五个链
- 五链:(必须是大写)链里面写的是规则。
1. PREROUTING          进路由之前数据包
2. INPUT                       就是过滤进来的数据包(输入)
3. FORWARD                转发
4. OUTPUT                   发出去的数据包
5. POSTROUTING        路由之后修改数据包
- 所有的访问都是按顺序:
	- 入站:比如访问自身的web服务流量。先PREROUTING (是否改地址),再INPUT (是否允许)到达程序。
	- 转发:经过linux网关的流量.先PREROUTING (是否改地址),然后路由。转发给FORWARD (转发或者丢弃),最后经过POSTROUTING (看看改不改地址。)
	- 出站:源自linux自身的流量.先OUTPUT,然后路由。再给POSTROUTING (是否改IP).
- 规则顺序:ACL逐条匹配,匹配即停止。

### 四表五链
- raw表里面:
	1. PREROUTING
	2. OUTPUT
- 总结:数据包跟踪 内核模块iptables_raw

- mangel表里面有5个链:
	1. PREROUTING
	2. INPUT
	3. FORWARD
	4. OUTPUT
	5. POSTROUTING
- 路由标记用的表。内核模块iptables_mangle

- nat表里面的链:
	1. PREROUTING
	2. INPUT
	3. OUTPUT
	4. POSTROUTING
- 转换地址的表(改IP,改端口。当网关使用的linux.保护内外网流量。内核模块叫iptable_nat)

- filter表有三个链:重点
	1. INPUTT   负责过所有目标是本机地址的数据包通俗来说:就是过滤进入主机的数据包
	3. FORWARD 负责转发流经主机的数据包。起到转发的作用
	4. OUTPUT 处理所有源地址是本机地址的数据包通俗的讲:就是处理从主机发出的数据包
- 总结:根据规则来处理数据包,如转或者丢。就是实现主机型防火墙的主要表。 
- 内核模块 iptable_filter

