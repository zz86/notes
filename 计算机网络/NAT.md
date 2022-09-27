
## 网络地址转换（Network Address Translation），缩写为 NAT
NAT 技术可以重写 IP 数据包的源 IP 或者目的 IP，被普遍地用来解决公网 IP 地址短缺的 问题。它的主要原理就是，网络中的多台主机，通过共享同一个公网 IP 地址，来访问外网 资源。同时，由于 NAT 屏蔽了内网网络，自然也就为局域网中的机器提供了安全隔离。

你既可以在支持网络地址转换的路由器（称为 NAT 网关）中配置 NAT，也可以在 Linux 服务器中配置 NAT。如果采用第二种方式，Linux 服务器实际上充当的是“软”路由器的 角色。

NAT 的主要目的，是实现地址转换。根据实现方式的不同，NAT 可以分为三类：

- 静态 NAT，即内网 IP 与公网 IP 是一对一的永久映射关系；

- 动态 NAT，即内网 IP 从公网 IP 池中，动态选择一个进行映射；

- 网络地址端口转换 NAPT（Network Address and Port Translation），即把内网 IP 映 射到公网 IP 的不同端口上，让多个内网 IP 可以共享同一个公网 IP 地址。

NAPT 是目前最流行的 NAT 类型，我们在 Linux 中配置的 NAT 也是这种类型。而根据转 换方式的不同，我们又可以把 NAPT 分为三类。

- 第一类是源地址转换 SNAT，即目的地址不变，只替换源 IP 或源端口。SNAT 主要用于， 多个内网 IP 共享同一个公网 IP ，来访问外网资源的场景。

- 第二类是目的地址转换 DNAT，即源 IP 保持不变，只替换目的 IP 或者目的端口。DNAT 主要通过公网 IP 的不同端口号，来访问内网的多种服务，同时会隐藏后端服务器的真实 IP 地址。

- 第三类是双向地址转换，即同时使用 SNAT 和 DNAT。当接收到网络包时，执行 DNAT， 把目的 IP 转换为内网 IP；而在发送网络包时，执行 SNAT，把源 IP 替换为外部 IP。双向地址转换，其实就是外网 IP 与内网 IP 的一对一映射关系，所以常用在虚拟化环境中， 为虚拟机分配浮动的公网 IP 地址。

为了帮你理解 NAPT，我画了一张图。我们假设：

本地服务器的内网 IP 地址为 192.168.0.2； NAT 网关中的公网 IP 地址为 100.100.100.100； 要访问的目的服务器 baidu.com 的地址为 123.125.115.110。

那么 SNAT 和 DNAT 的过程，就如下图所示：
![[Pasted image 20220927192958.png|600]]
## 如何在 Linux 中实现 NAT 的功能(iptables 与 NAT)
Linux 中的 NAT ，基于内核的连接跟踪模块实现。所以，它维护每个连接状态的同时，也对网络性能有一定影响。

conntrack，表示连接跟踪模块。它通过内核中的连接跟踪表（也就是哈希表）， 记录网络连接的状态，是 iptables 状态过滤（-m state）和 NAT 的实现基础。

Linux 内核提供的 Netfilter 框架，允许对网络数据包进行修改（比如 NAT）和过滤（比如 防火墙）。在这个基础上，iptables、ip6tables、ebtables 等工具，又提供了更易用的命 令行接口，以便系统管理员配置和管理 NAT、防火墙的规则。

其中，iptables 就是最常用的一种配置工具。

Linux 支持 4 种表，包括 filter（用于过滤）、nat（用于 NAT）、mangle（用于修改分组数据） 和 raw（用于原 始数据包）等。

每个表有多条链（chain），用来管理具体的 iptables 规则。比如：

filter 表中，内置 INPUT、OUTPUT 和 FORWARD 链；

nat 表中，内置 PREROUTING、POSTROUTING、OUTPUT 等。

当然，你也可以根据需要，创建你自己的链。

针对今天的主题，要实现 NAT 功能，主要是在 nat 表进行操作。而 nat 表内置了三个链：

- PREROUTING，用于路由判断前所执行的规则，比如，对接收到的数据包进行 DNAT。

- POSTROUTING，用于路由判断后所执行的规则，比如，对发送或转发的数据包进行 SNAT 或 MASQUERADE。

- OUTPUT，类似于 PREROUTING，但只处理从本机发送出去的包。

