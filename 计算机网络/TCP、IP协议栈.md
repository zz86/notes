
## 网络为什么要分层
我们都知道网络是复杂的。对于复杂的问题，我们自然要通过分层处理简化问题难度，降低复杂度，由于分层后的各层之间相互独立，我们可以把大问题分割成小问题。同样，分 层也保证了网络的松耦合和相对的灵活，分层拆分后易于各层的实现和维护，也方便了各 层的后续扩展。

网络分层解决了网络复杂的问题，在网络中传输数据中，我们对不同设备之间的传输数据 的格式，需要定义一个数据标准，所以就有了网络协议。网络协议是双方通信的一种约定，以便双方都可以理解对方的信息。

Linux 网络基于 TCP/IP 模型，构建了其网络协议栈，把繁杂的网络功能划分为应用层、传输层、网络层、网络接口层等四个不同的层次，既解决了网络环境中设备异构的问题，也解耦了网络协议的复杂性。

![[Pasted image 20220926222332.png]]
![[Pasted image 20220926222435.png]]
![[Pasted image 20221001000840.png|600]]
![[Pasted image 20221001000919.png|800]]
## Linux 通用 IP 网络栈
![[Pasted image 20220926222408.png|700]]

## 网络协议
![[Pasted image 20220824164609.png|800]]

![[Pasted image 20220901144125.png|900]]


## 无类型域间选路（CIDR）
这种方式打破了原来设计的几类地址的做法，将 32 位的 IP 地址一分为二，前面是**网络号**，后面是**主机号**。从哪里分呢？你如果注意观察的话可以看到，10.100.122.2/24，这个 IP 地址中有一个斜杠，斜杠后面有个数字 24。这种地址表示形式，就是 CIDR。后面 24 的意思是，32 位中，前 24 位是网络号，后 8 位是主机号。

伴随着 CIDR 存在的，一个是**广播地址**，10.100.122.255。如果发送这个地址，所有 10.100.122 网络里面的机器都可以收到。另一个是**子网掩码**，255.255.255.0。

将子网掩码和 IP 地址进行 AND 计算。前面三个 255，转成二进制都是 1。1 和任何数值取 AND，都是原来数值，因而前三个数不变，为 10.100.122。后面一个 0，转换成二进制是 0，0 和任何数值取 AND，都是 0，因而最后一个数变为 0，合起来就是 10.100.122.0。这就是**网络号**。**将子网掩码和 IP 地址按位计算 AND，就可得到网络号。**

## **动态主机配置协议（Dynamic Host Configuration Protocol）**，简称**DHCP**
-   DHCP 协议主要是用来给客户租用 IP 地址，和房产中介很像，要商谈、签约、续租，广播还不能“抢单”；
-   DHCP 协议能给客户推荐“装修队”PXE，能够安装操作系统，这个在云计算领域大有用处。

## **预启动执行环境（Pre-boot Execution Environment）**，简称**PXE**
![[Pasted image 20220824203000.png|800]]
## 第一层：物理层

## 第二层：数据链路层
不同链路层协议的地址表示非常不同，比如局域网所采纳的以太网（Ethernet）协议用的是 MAC 地址。

**MAC**的全称是**Medium Access Control**，即**媒体访问控制。**控制什么呢？其实就是控制在往媒体上发数据的时候，谁先发、谁后发的问题。防止发生混乱。这解决的是第二个问题。这个问题中的规则，学名叫**多路访问**。有很多算法可以解决这个问题。就像车管所管束马路上跑的车，能想的办法都想过了。

比如接下来这三种方式：
-   方式一：分多个车道。每个车一个车道，你走你的，我走我的。这在计算机网络里叫作**信道划分；**
-   方式二：今天单号出行，明天双号出行，轮着来。这在计算机网络里叫作**轮流协议；**
-   方式三：不管三七二十一，有事儿先出门，发现特堵，就回去。错过高峰再出。我们叫作**随机接入协议。**著名的以太网，用的就是这个方式。

接下来要解决第一个问题：发给谁，谁接收？这里用到一个物理地址，叫作**链路层地址**。但是因为第二层主要解决媒体接入控制的问题，所以它常被称为**MAC 地址**。
![[Pasted image 20220824212343.png]]
ARP协议发生在数据链路层
![[Pasted image 20220824212539.png|800]]

交换机and转发表也是发生在数据链路层

总结：
第一，MAC 层是用来解决多路访问的堵车问题的；

第二，ARP 是通过吼的方式来寻找目标 MAC 地址的，吼完之后记住一段时间，这个叫作缓存；

第三，交换机是有 MAC 地址学习能力的，学完了它就知道谁在哪儿了，不用广播了。

### STP 协议
在数据结构中，有一个方法叫作**最小生成树**。有环的我们常称为**图**。将图中的环破了，就生成了**树**。在计算机网络中，生成树的算法叫作**STP**，全称**Spanning Tree Protocol**。

-   **Root Bridge**，也就是**根交换机**。这个比较容易理解，可以比喻为“掌门”交换机，是某棵树的老大，是掌门，最大的大哥。
    
-   **Designated Bridges**，有的翻译为**指定交换机**。这个比较难理解，可以想像成一个“小弟”，对于树来说，就是一棵树的树枝。所谓“指定”的意思是，我拜谁做大哥，其他交换机通过这个交换机到达根交换机，也就相当于拜他做了大哥。这里注意是树枝，不是叶子，因为叶子往往是主机。
    
-   **Bridge Protocol Data Units （BPDU）** ，**网桥协议数据单元**。可以比喻为“相互比较实力”的协议。行走江湖，比的就是武功，拼的就是实力。当两个交换机碰见的时候，也就是相连的时候，就需要互相比一比内力了。BPDU 只有掌门能发，已经隶属于某个掌门的交换机只能传达掌门的指示。
    
-   **Priority Vector**，**优先级向量**。可以比喻为实力 （值越小越牛）。实力是啥？就是一组 ID 数目，[Root Bridge ID, Root Path Cost, Bridge ID, and Port ID]。为什么这样设计呢？这是因为要看怎么来比实力。先看 Root Bridge ID。拿出老大的 ID 看看，发现掌门一样，那就是师兄弟；再比 Root Path Cost，也即我距离我的老大的距离，也就是拿和掌门关系比，看同一个门派内谁和老大关系铁；最后比 Bridge ID，比我自己的 ID，拿自己的本事比。

### **虚拟隔离**
就是用我们常说的**VLAN**，或者叫**虚拟局域网**。使用 VLAN，一个交换机上会连属于多个局域网的机器，那交换机怎么区分哪个机器属于哪个局域网呢？
![[Pasted image 20220824214037.png]]
我们只需要在原来的二层的头上加一个 TAG，里面有一个 VLAN ID，一共 12 位。为什么是 12 位呢？因为 12 位可以划分 4096 个 VLAN。这样是不是还不够啊。现在的情况证明，目前云计算厂商里面绝对不止 4096 个用户。

有人会问交换机之间怎么连接呢？将两个交换机连接起来的口应该设置成什么 VLAN 呢？对于支持 VLAN 的交换机，有一种口叫作**Trunk 口**。它可以转发属于任何 VLAN 的口。交换机之间可以通过这种口相互连接。
![[Pasted image 20220824214315.png]]

总结：
-   当交换机的数目越来越多的时候，会遭遇环路问题，让网络包迷路，这就需要使用 STP 协议，通过华山论剑比武的方式，将有环路的图变成没有环路的树，从而解决环路问题。
-   交换机数目多会面临隔离问题，可以通过 VLAN 形成虚拟局域网，从而解决广播问题和安全问题。

## 第三层：网络层
### IP地址
IP 地址是 TCP/IP 协议中，用来确定通信双方的一个重要标识。每个 IP 地址又包括了主机号和网络号两部分。相同网络号的主机组成一个子网；不同子网再通过路由器连接，组成一个庞大的网络。

### ICMP
ping 是基于 ICMP 协议工作的。**ICMP**全称**Internet Control Message Protocol**，就是**互联网控制报文协议**。

ICMP 报文是封装在 IP 包里面的。因为传输指令的时候，肯定需要源地址和目标地址。它本身非常简单。
![[Pasted image 20220824214522.png]]
ICMP 报文有很多的类型，不同的类型有不同的代码。**最常用的类型是主动请求为 8，主动请求的应答为 0**。

查询报文类型：例如，常用的**ping 就是查询报文，是一种主动请求，并且获得主动应答的 ICMP 协议**。所以，ping 发的包也是符合 ICMP 协议格式的，只不过它在后面增加了自己的格式。

对 ping 的主动请求，进行网络抓包，称为**ICMP ECHO REQUEST**。同理主动请求的回复，称为**ICMP ECHO REPLY**。比起原生的 ICMP，这里面多了两个字段，一个是**标识符**。这个很好理解，你派出去两队侦查兵，一队是侦查战况的，一队是去查找水源的，要有个标识才能区分。另一个是**序号**，你派出去的侦查兵，都要编个号。如果派出去 10 个，回来 10 个，就说明前方战况不错；如果派出去 10 个，回来 2 个，说明情况可能不妙。

差错报文类型：我举几个 ICMP 差错报文的例子：**终点不可达为 3，源抑制为 4，超时为 11，重定向为 5**
**第一种是终点不可达**：具体的原因在代码中表示就是，网络不可达代码为 0，主机不可达代码为 1，协议不可达代码为 2，端口不可达代码为 3，需要进行分片但设置了不分片位代码为 4。
**第二种是源站抑制**，也就是让源站放慢发送速度。
**第三种是时间超时**，也就是超过网络包的生存时间还是没到。
**第四种是路由重定向**，也就是让下次发给另一个路由器。

ping 命令执行的时候，源主机首先会构建一个 ICMP 请求数据包，ICMP 数据包内包含多个字段。最重要的是两个，第一个是**类型字段**，对于请求数据包而言该字段为 8；另外一个是**顺序号**，主要用于区分连续 ping 的时候发出的多个数据包。每发出一个请求数据包，顺序号会自动加 1。为了能够计算往返时间 RTT，它会在报文的数据部分插入发送时间。

总结：
-   ICMP 相当于网络世界的侦察兵。我讲了两种类型的 ICMP 报文，一种是主动探查的查询报文，一种异常报告的差错报文；
-   ping 使用查询报文，Traceroute 使用差错报文。


**网关往往是一个路由器，是一个三层转发的设备**。

**静态路由，其实就是在路由器上，配置一条一条规则。**

#### IP 头和 MAC 头哪些变、哪些不变？

对于 IP 头和 MAC 头哪些变、哪些不变的问题，可以分两种类型。我把它们称为“**欧洲十国游”型**和“**玄奘西行”型**。

之前我说过，MAC 地址是一个局域网内才有效的地址。因而，MAC 地址只要过网关，就必定会改变，因为已经换了局域网。两者主要的区别在于 IP 地址是否改变。不改变 IP 地址的网关，我们称为**转发网关**；改变 IP 地址的网关，我们称为**NAT 网关**，这个过程用英文说就是**Network Address Translation**，简称**NAT**。

其实这第二种方式我们经常见，现在大家每家都有家用路由器，家里的网段都是 192.168.1.x，所以你肯定访问不了你邻居家的这个私网的 IP 地址的。所以，当我们家里的包发出去的时候，都被家用路由器 NAT 成为了运营商的地址了。

路由器就是一台网络设备，它有多张网卡。当一个入口的网络包送到路由器时，它会根据一个本地的转发信息库，来决定如何正确地转发流量。这个转发信息库通常被称为**路由表**。

-   路由分静态路由和动态路由，静态路由可以配置复杂的策略路由，控制转发策略；
-   动态路由主流算法有两种，距离矢量算法和链路状态算法。基于两种算法产生两种协议，基于链路状态路由算法的 OSPF和基于距离矢量路由算法的 BGP

### TTL详解
TTL 是 IP 包（网络层）的一个属性，字面上就差不多是生命长度的意思，每一个三层设备 都会把路过的 IP 包的 TTL 值减去 1。而 IP 包的归宿，无非以下几种：
- 网络包最终达到目的地； 
- 进入路由黑洞并被丢弃； 
- 因为网络设备问题被中途丢弃； 
- 持续被路由转发并 TTL 减 1，直到 TTL 为 0 而被丢弃。

在RFC791中规定了 TTL 值为 8 位，所以取值范围是 0~255。

因为 TTL 是从出发后就开始递减的，那么必然，网络上我们能抓到的包，它的当前 TTL 一 定比出发时的值要小。而且，我们可能也早就知道，TTL 从初始值到当前值的差值，就是 经过的三层设备的数量。

不同的操作系统其初始 TTL 值不同，一般来说 Windows 是 128，Linux 是 64。

内网同一个连接中的报文，其 TTL 值一般不会变化。

### MTU
中文叫最大传输单元，也就是第三层的报文大小的上限。

MTU 本身是三层的概念，而在第四层的 TCP 层面，有个对应的概念叫 MSS，Maximum Segment Size（最大分段尺寸），也就是单纯的 TCP 载荷的最大尺寸。MTU 是三层报 文的大小，在 MTU 的基础上刨去 IP 头部 20 字节和 TCP 头部 20 字节，就得到了最常见的 MSS 1460 字节。如果你之前对 MTU 和 MSS 还分不清楚的话，现在应该能搞清楚 了。
![[Pasted image 20220902130248.png]]
MSS 在 TCP 里是怎么体现的呢？其实我在 TCP 握手那一讲里提到过 Window Scale， 你很容易能联想到，MSS 其实也是在握手阶段完成“通知”的。在 SYN 报文里，客户端 向服务端通报了自己的 MSS。而在 SYN+ACK 里，服务端也做了类似的事情。这样，两端 就知道了对端的 MSS，在这条连接里发送报文的时候，双方发送的 TCP 载荷都不会超过 对方声明的 MSS。

物理链路中并不能传输任意 大小的数据包。网络接口配置的最大传输单元（MTU），就规定了最大的 IP 包大小。在我 们最常用的以太网中，MTU 默认值是 1500（这也是 Linux 的默认值）。

一旦网络包超过 MTU 的大小，就会在网络层分片，以保证分片后的 IP 包不大于 MTU 值。显然，MTU 越大，需要的分包也就越少，自然，网络吞吐能力就越好。

### IP分片和TCP分段
在 TCP 这一层，分段的对象是应用层发给 TCP 的消息体（message）。比如应用给 TCP 协议栈发送了 3000 字节的消息，那么 TCP 发现这个消息超过了 MSS（常见值为 1460），就必须要进行分段，比如可能分成 1460，1460，80 这三个 TCP 段。
![[Pasted image 20220902131051.png|600]]
在 IP 这一层，分片的对象是 IP 包的载荷，它可以是 TCP 报文，也可以是 UDP 报文，还 可以是 IP 层自己的报文比如 ICMP。

为了帮助你理解 segmentation 和 fragmentation 的区别，我现在假设一个“奇葩”的场 景，也就是 MSS 为 1460 字节，而 MTU 却只有 1000 字节，那么 segmentation 和 fragmentation 将按照如下示意图来工作:
![[Pasted image 20220902131137.png]]
补充：为了方便讨论，我们假设 TCP 头部就是没有 Option 扩展的 20 字节。但实际场 景里，很可能 MSS 小于 1460 字节，而 TCP 头部也超过 20 字节。

不过在现实场景里，IP 分片是需要尽量避免的，


## 第四层：传输层

一般面试的时候我问这两个协议的区别，大部分人会回答，TCP 是面向连接的，UDP 是面向无连接的。

什么叫面向连接，什么叫无连接呢？在互通之前，面向连接的协议会先建立连接。例如，TCP 会三次握手，而 UDP 不会。为什么要建立连接呢？你 TCP 三次握手，我 UDP 也可以发三个包玩玩，有什么区别吗？

**所谓的建立连接，是为了在客户端和服务端维护连接，而建立一定的数据结构来维护双方交互的状态，用这样的数据结构来保证所谓的面向连接的特性。**

例如，**TCP 提供可靠交付**。通过 TCP 连接传输的数据，无差错、不丢失、不重复、并且按序到达。我们都知道 IP 包是没有任何可靠性保证的，一旦发出去，就像西天取经，走丢了、被妖怪吃了，都只能随它去。但是 TCP 号称能做到那个连接维护的程序做的事情，这个下两节我会详细描述。而**UDP 继承了 IP 包的特性，不保证不丢失，不保证按顺序到达。**

再如，**TCP 是面向字节流的**。发送的时候发的是一个流，没头没尾。IP 包可不是一个流，而是一个个的 IP 包。之所以变成了流，这也是 TCP 自己的状态维护做的事情。而**UDP 继承了 IP 的特性，基于数据报的，一个一个地发，一个一个地收。**

还有**TCP 是可以有拥塞控制的**。它意识到包丢弃了或者网络的环境不好了，就会根据情况调整自己的行为，看看是不是发快了，要不要发慢点。**UDP 就不会，应用让我发，我就发，管它洪水滔天。**

因而**TCP 其实是一个有状态服务**，通俗地讲就是有脑子的，里面精确地记着发送了没有，接收到没有，发送到哪个了，应该接收哪个了，错一点儿都不行。而 **UDP 则是无状态服务。** 通俗地说是没脑子的，天真无邪的，发出去就发出去了。

现在直播比较火，直播协议多使用 RTMP，这个协议我们后面的章节也会讲，而这个 RTMP 协议也是基于 TCP 的。

我们可以这样比喻，如果 MAC 层定义了本地局域网的传输行为，IP 层定义了整个网络端到端的传输行为，这两层基本定义了这样的基因：网络传输是以包为单位的，二层叫帧，网络层叫包，传输层叫段。我们笼统地称为包。包单独传输，自行选路，在不同的设备封装解封装，不保证到达。基于这个基因，生下来的孩子 UDP 完全继承了这些特性，几乎没有自己的思想。

**TCP 是数据流**，上层业务的一个请求可能会被分为多个 TCP 包 （TCP Segment），同样地，多个请求也可能被合并为一个 TCP 包。也就是说，TCP 流 是很难和应用数据关联起来的。

#### UDP头
![[Pasted image 20220825095208.png]]
#### TCP头
![[Pasted image 20220825100554.png]]

#### UDP 的三大使用场景
第一，**需要资源少，在网络情况比较好的内网，或者对于丢包不敏感的应用**
第二，**不需要一对一沟通，建立连接，而是可以广播的应用**。UDP 的不面向连接的功能，可以使得可以承载广播或者多播的协议。 DHCP 就是基于 UDP 协议的。一般的获取 IP 地址都是内网请求，而且一次获取不到 IP 又没事，过一会儿还有机会。我们讲过 PXE 可以在启动的时候自动安装操作系统，操作系统镜像的下载使用的 TFTP，这个也是基于 UDP 协议的。在后面云中网络部分，有一个协议 VXLAN，也是需要用到组播，也是基于 UDP 协议的。
第三，**需要处理速度快，时延低，可以容忍少数丢包，但是要求即便网络拥塞，也毫不退缩，一往无前的时候**。例如直播。

如果你实现的应用需要有自己的连接策略，可靠保证，时延要求，使用 UDP，然后再应用层实现这些是再好不过了。

Google 旗下的 Nest 建立 Thread Group，推出了物联网通信协议 Thread，就是基于 UDP 协议的。

#### TCP三次握手 
![[Pasted image 20220825101130.png]]
![[Pasted image 20220901151852.png|800]]
#### 当服务器不回复客户端发来的SYN请求时会发生什么？
TCP握手请求一直没有成功，客户端一共有7个SYN包发出。因为TCP 握手没响应的话，操作系统会做重试。在 Linux 中， 这个设置是由内核参数 net.ipv4.tcp_syn_retries 控制的，默认值为 6，也就是 1 秒，2 秒，4.2 秒，8.2 秒，16.1 秒，33 秒，每个间隔是上一个的两倍左右。到第 6 次重试失败后，客户端就彻底放弃了。

显然，这里的翻倍时间，就是“指数退避”原则的体现。这里的时间不是精确的整秒，因为指数退避原则本身就不建议在精确的整秒做重试，最好是有所浮动，这样可以让重试成功的机会变得更大一些。

#### 当服务器拒绝客户端发来的SYN请求时会发生什么？
服务端拒绝 TCP 握手，除了用 TCP RST，另外一种方式是通过 ICMP Destination unreachable（Port unreachable）消息。从客户端应用程序看，这两种回复都属 于“对端拒绝”，所以应用表面看不出区别，但我们在抓包的时候要注意，如果单纯抓 取服务端口的报文，就会漏过这个 ICMP 消息，可能对排查不利。
![[Pasted image 20220901151318.png]]
#### 通信双方还可以同时向对方发送 SYN，也能建立起连接。
![[Pasted image 20220901154142.png|700]]
#### TCP 延迟确认（Delayed ACK）
这是针对 TCP ACK 的一种优化机制，也就是说，不用每次请求 都发送一个 ACK，而是先等一会儿（比如 40ms），看看有没有“顺风车”。如果这段时 间内，正好有其他包需要发送，那就捎带着 ACK 一起发送过去。当然，如果一直等不到其 他包，那就超时后单独发送 ACK。

查询 TCP 文档（执行 man tcp），你就会发现，只有 TCP 套接字专门设置了 TCP_QUICKACK ，才会开启快速确认模式；否则，默认情况下，采用的就是延迟确认机 制。

#### Nagle 算法（纳格算法）
Nagle 算法，是 TCP 协议中用于减少小包发送数量的一种优化算法，目的是为了提高实际带宽的利用率。

举个例子，当有效负载只有 1 字节时，再加上 TCP 头部和 IP 头部分别占用的 20 字节，整 个网络包就是 41 字节，这样实际带宽的利用率只有 2.4%（1/41）。往大了说，如果整个 网络带宽都被这种小包占满，那整个网络的有效利用率就太低了。

Nagle 算法正是为了解决这个问题。它通过合并 TCP 小包，提高网络带宽的利用率。 Nagle 算法规定，一个 TCP 连接上，最多只能有一个未被确认的未完成分组；在收到这个 分组的 ACK 前，不发送其他分组。这些小分组会被组合起来，并在收到 ACK 后，用同一 个分组发送出去。

显然，Nagle 算法本身的想法还是挺好的，但是知道 Linux 默认的延迟确认机制后，你应该就不这么想了。因为它们一起使用时，网络延迟会明显。
![[Pasted image 20220927191810.png|500]]
当 Sever 发送了第一个分组后，由于 Client 开启了延迟确认，就需要等待 40ms 后才会 回复 ACK。 同时，由于 Server 端开启了 Nagle，而这时还没收到第一个分组的 ACK，Server 也会 在这里一直等着。

直到 40ms 超时后，Client 才会回复 ACK，然后，Server 才会继续发送第二个分组。

#### 四次挥手
![[Pasted image 20220825101159.png]]
实际上 TCP 挥手可能不是表面上的四次报文，因为并包也就是 Piggybacking 的存在， 它可能看起来是三次。

在某些特殊情况下，在 Wireshark 里看不到第一个 FIN。这个时候你不要真的把后面那 个被 Wireshark 直接展示的 FIN 当作是第一个 FIN。你需要选中挥手阶段附近的报文， 在 TCP 详情里面查看是否有报文携带了 FIN 标志位。

握手一定时客户端发起的，但是挥手双方都可以。

#### 挥手可以双方同时发起
![[Pasted image 20220901160947.png]]
双方同时发起关闭后，也同时进入了 FIN_WAIT_1 状态； 
然后也因为收到了对方的 FIN，也都进入了 CLOSING 状态； 
当双方都收到对方的 ACK 后，最终都进入了 TIME_WAIT 状态。

这也意味着，两端都需要等待 2MSL 的时间，才能复用这个五元组 TCP 连接。这种情况是 比较少见的，但是协议设计需要考虑各种边界条件下的实现，比普通的应用程序所要考虑 的事情要多不少。所以也许有些 RFC 看似简单，但背后其实都十分不简单。

#### TCP挥手时并不是双方同时停止发送数据
实际上，一方发送 FIN 只是表示这一方不再发送新的数据，但对方仍可以发送数据。 

还是在 Richard Stevens 的《TCP/IP 详解（第一卷）》中，明确提到 TCP 可以有“半 关闭”的做法，也就是： 

- 一端（A）发送 FIN，表示“我要关闭，不再发送新的数据了，但我可以接收新的数据”。 
- 另一端（B）可以回复 ACK，表示“我知道你那头不会再发送了，我这头未必哦”。
- B 可以继续发送新的数据给 A，A 也会回复 ACK 表示确认收到新数据。 
- 在发送完这些新数据后，B 才启动了自己的关闭过程，也就是发送 FIN 给 A，表示“我 的事情终于忙好了，我也要关闭，不会再发送新数据了”。 

这时候才是真正的两端都关闭了连接。
![[Pasted image 20220901161215.png|600]]

#### TCP状态机
![[Pasted image 20220825101353.png|800]]
TCP 包头很复杂，但是主要关注五个问题，顺序问题，丢包问题，连接维护，流量控制，拥塞控制；
顺序问题、丢包问题、流量控制都是通过**滑动窗口**来解决的，拥塞控制是通过**拥塞窗口**来解决的

#### 滑动窗口
发送端
![[Pasted image 20220825102643.png]]
-   LastByteAcked：第一部分和第二部分的分界线
-   LastByteSent：第二部分和第三部分的分界线
-   LastByteAcked + AdvertisedWindow：第三部分和第四部分的分界线

接收端
![[Pasted image 20220825102723.png]]
-   MaxRcvBuffer：最大缓存的量；
-   LastByteRead 之后是已经接收了，但是还没被应用层读取的；
-   NextByteExpected 是第一部分和第二部分的分界线。

### TCP拥塞控制  拥塞窗口
![[Pasted image 20220909143730.png|700]]
为了应对错综复杂的互联网网络环境，TCP 使用了拥塞控制机制来确保传输速度和稳定性。这里你也要注意，总的来说，拥塞控制主要是通信两端自己需要实现的功能，而途中 的网络设备，比如交换机、路由器等等，除了可能会发出拥塞通知报文以外，其他时候它们只管转发报文，都是不会担负更多的拥塞控制的责任的。

TCP 拥塞控制主要有四个重要阶段：
1. 慢启动：每收到一个 ACK，拥塞窗口（CW）增加一个 MSS。
2. 拥塞避免：传输过了慢启动阈值（ssthresh）之后，就进入了拥塞避免阶段。策略是“和性增长乘性降低”，每一个 RTT，CW 增加一个 MSS。
3. 快速重传：TCP 每发送一个报文，就启动一个超时计时器。如果在限定时间内没收到这个报文的确 认，那么发送方就会认为，这个报文已经在网络上丢失了，于是需要重传这个报文，这种 形式叫做超时重传。TCP 会用另外一种方式来解决超时重传带来的时间空耗的问题，就是用快速重传。 在这个机制里，一旦发送方收到 3 次重复确认（加上第一次确认就一共是 4 次），就不用 等超时计时器了，直接重传这个报文。![[Pasted image 20220905143534.png|500]]。
4. 快速恢复：结合快速重传，在遇到拥塞点后，跳过慢启动阶段，进入线性增长

### 超时重传VS快速重传
产生TCP重传的问题主要是丢包和网络拥塞这两种情况。TCP重传时会调用特定的内核函数，我们可以追踪该函数的调用情况来追踪TCP重传事件，例如使用Kprobe、Tracepoint、tcpretrans等工具。

对于超时重传：
- TCP 对于每条连接都维护了一个超时计时器，当数据发送出去后一定时限内还没有收到 确认，就认为是发生了超时，然后重传这部分数据。这个等待的时间就是重传超时，Retransmission Timeout，简称 RTO。
- RTO 的初始值是 1 秒（在发送 SYN 但未收到 SYN+ACK 阶段）。 
- 在连接建立后，TCP 会动态计算出 TRO。 RTO 有上限值和下限值，常见值分别为 2 分钟和 200ms。 实际场景中，RTO 为 200ms 出头最为常见。
![[Pasted image 20220905150151.png|600]]

对于快速重传：
- 快速重传的触发条件是：收到 3 个或者 3 个以上的重复确认报文（DupAck）。 
- 在快速重传中，SACK（SACK 全称是 Selective Acknowlegement，中文叫“选择性确认”）也起到了避免一部分已经到达的数据被重传。不过，也由于 TCP 头部长度的限制，SACK 只能放置 4 个块，再多也不行了。 SACK 要能工作，还需要 SACK permitted 这个 TCP 扩展属性的支持。这个字段只有在 TCP 握手的 SYN 和 SYN+ACK 报文中出现，表示自己是否支持 SACK 特性。知道对方支持 SACK，那我们就可以在后续报文里带上 SACK，也就是上面的含有 left edge 和 right edge，来告诉对方我实际收到的 TCP 段了，就可以避免这部分报文也被连带重传。
- 快速重传只要 3 个 DupAck 就可以触发，实际上我们还可能观察到远多于 3 个 DupAck 的情况，这也是正常现象。
![[Pasted image 20220905150325.png|600]]


#### TCP 和 UDP 的 Socket 编程
TCP
![[Pasted image 20220825104750.png|300]]
UDP
![[Pasted image 20220825104819.png|300]]
### TCP Keep-alive 和HTTP Keep-alive 的区别

对于 TCP Keep-alive：
- 默认 TCP 连接并不启用 Keep-alive，若要打开的话要显式地调用 setsockopt()，来设 置保活包的发送间隔、等待时间、重试个数等配置。在全局层面，Linux 还默认有 3 个跟 Keep-alive 相关的内核配置项可以调整：tcp_Keepalive_time，tcp_Keepalive_probes，还有 tcp_Keepalive_intvl。
- TCP 心跳包的特点是，它的序列号是上一个包的序列号 -1，而心跳回复包的确认号是这 个序列号 -1+1（即还是这个序列号）。

对于 HTTP Keep-alive
- HTTP/1.0 默认是短连接，HTTP/1.1 和 2 默认是长连接。 
- Connection: Keep-alive 在 HTTP/1.0 里，能起到维持长连接的作用，而在 HTTP/1.1 里面没有这个作用（因为默认就是长连接）。 
- Connection: Close 在 HTTP/1.1 里，可以起到优雅关闭连接的作用。这个头部在流量 调度场景下也很有用，能明显加快基于 DNS/GSLB 的流量调整的收敛速度。

### **服务端挂了，客户端的 TCP 连接会发生什么？**
如果「服务端挂掉」指的是「**服务端进程崩溃**」，服务端的进程在发生崩溃的时候，内核会发送 FIN 报文，与客户端进行四次挥手。

但是，如果「服务端挂掉」指的是「**服务端主机宕机**」，那么是不会发生四次挥手的，具体后续会发生什么？还要看客户端会不会发送数据？

-   如果客户端会发送数据，由于服务端已经不存在，客户端的数据报文会超时重传，当重传总间隔时长达到一定阈值（内核会根据 tcp_retries2 设置的值计算出一个阈值）后，会断开 TCP 连接；
-   如果客户端一直不会发送数据，再看客户端有没有开启 TCP keepalive 机制？
	-   如果有开启，客户端在一段时间没有进行数据交互时，会触发 TCP keepalive 机制，探测对方是否存在，如果探测到对方已经消亡，则会断开自身的 TCP 连接；
	-   如果没有开启，客户端的 TCP 连接会一直存在，并且一直保持在 ESTABLISHED 状态。

在补充一点，如果服务端主机宕机后，然后马上重启了服务端，重启完成后，如果这时客户端发送了数据，由于服务端之前的连接信息已经不存在，所以会回 RST 报文给客户端，客户端收到 RST 报文后，就断开连接。

在没有使用 TCP 保活机制，且双方不传输数据的情况下，一方的 TCP 连接处在 ESTABLISHED 状态时，并不代表另一方的 TCP 连接还一定是正常的。

## 第五层：应用层
HTTP流程
![[Pasted image 20220824165624.png|800]]

## 大端小端问题
在网络上传输超过一个 Byte 的类型，还有大端 Big Endian 和小端 Little Endian 的问题。

假设我们要在 32 位四个 Byte 的一个空间存放整数 1，很显然只要一个 Byte 放 1，其他三个 Byte 放 0 就可以了。那问题是，最后一个 Byte 放 1 呢，还是第一个 Byte 放 1 呢？或者说 1 作为最低位，应该是放在 32 位的最后一个位置呢，还是放在第一个位置呢？

最低位放在最后一个位置，叫作 Little Endian，最低位放在第一个位置，叫作 Big Endian。TCP/IP 协议栈是按照 Big Endian 来设计的，而 X86 机器多按照 Little Endian 来设计的，因而发出去的时候需要做一个转换。

## 什么是TCP流？UDP数据报？
这里的 TCP 流，就是英文的 TCP Stream。Stream 这个词有“流”的意思，也 有“连续的事件”这样一个含义，所以它是有前后、有顺序的，这也正对应了 TCP 的特 性。

跟 Stream 相对的一个词是 Datagram，它是指没有前后关系的数据单元，比如 UDP 和 IP 都属于 Datagram。在 Linux 网络编程里面，TCP 对应的 socket 类型是 SOCK_STREAM，而 UDP 对应的，就是 SOCK_DGRAM 了。显然，DGRAM 就是 Datagram 的简写。

## 帧、分组、段、数据报
**帧**（frame）是二层也就是数据链路层的概念，代表了二层报文，它包含帧头、载荷、帧 尾。注意，帧是有尾部的，而其他像 IP、TCP、HTTP 等层级的报文，都没有尾部。我们 不可以说“TCP 帧”或者“IP 帧”，虽然也许对方也明白你的意思，但我们都想做得专业 一点，不是嘛。这里还有个小知识点：HTTP/2 实现了多路复用，其中也有帧的概念，不 过那个帧，跟这里网络二层的帧，除了名称相同以外，就没有别的联系了。 

**分组**是 IP 层报文，也就是狭义的 packet。 

**段特指 TCP segment**，也就是 TCP 报文。既然 segment 是“部分”的意思，那这 个“整体”又是什么呢？它就是在应用层交付给传输层的消息（message）。当 message 被交付给传输层时，如果这个 message 的原始尺寸，超出了传输层数据单元的限制（比如 超出了 TCP 的 MSS），它就会被划分为多个 segment。这个过程就是分段 （segmentation），也是 TCP 层的一个很重要的职责。 

另外，这里还要提一下，**Datagram 的中文叫“数据报”**，但不是“数据包”。读音类 似，但意思并不完全相同。前面说过，“数据包”是一个通用词，所以用“UDP 数据 包”指代“UDP 数据报”并没有问题。但反过来，非 UDP 协议的数据包，比如 TCP 段， 就不能叫“TCP 数据报”了，因为 TCP 不是 Datagram。
![[Pasted image 20220901142724.png|700]]
## 传输速度
- **时延Round Trip Time（RTT）**：也叫往返时间，是通信两端之间的一来一回的时间之和。
- **在途报文（在途字节数，Bytes in flight）**：发送端已经发出但还未被确认的报文，时延越长，发送窗口越大，在途报文可能越多，这两者是正比关系。 
- **带宽时延积，Bandwidth Delay Product，缩写是 BDP（Delay 就是 RTT）**：带宽和时延的乘积，表示这个网络能承载的最多的在途数据量。 
- **接收窗口**：它代表的是接收端当前最多能接收的字节数。通过 TCP 报文头部的 Window 字段，通信双方能互相了解到对方的接收窗口。 任意一个 TCP 报文的头部都有 Window 字段，长度为 2 个字节，所以最大值为 2 的 16 次方，即 64KB。在我 们讨论 TCP 握手相关案例时，提到过 Window Scale。它是在RFC1323中引进的，使得 Window 值最大能达到 2 的 30 次方，即 1GB。
- **拥塞窗口**：发送端根据实际传输的拥塞情况计算出来的可发送字节数，但不公开在报文 中。各自暗地里各维护各的，互相不知道，也不需要知道。
- **发送窗口**：对方的接收窗口和自身的拥塞窗口两者中，值较小者。实际发送的在途字节 数不会大于这个值。

基于以上的知识，我们得以推导出最终的核心公式：**速度上限 = 发送窗口 / 往返时间**。用 英文可以表示为：velocity = window/RTT。

当接收端有“数据滞留”现象时，就变成了**速度=确认数据/往返时间**

## 发送过程总览
应用程序首先会准备好数据，调用用户态下的库函数。接着调用系统 API 接口函数，进入 到内核态。 

内核态对应的系统服务函数会复制应用程序的数据到内核的内存空间中，然后将数据移交 给网络协议栈，在网络协议栈中将数据层层打包。 

最后，包装好的数据会交给网卡驱动，网卡驱动程序负责将打包好的数据写入网卡并让其 发送出去。
![[Pasted image 20220905101244.png|600]]
首先，应用程序调用 Socket API（比如 sendmsg）发送网络包。

由于这是一个系统调用，所以会陷入到内核态的套接字层中。套接字层会把数据包放到 Socket 发送缓冲区中。 接下来，网络协议栈从 Socket 发送缓冲区中，取出数据包；再按照 TCP/IP 栈，从上到下 逐层处理。比如，传输层和网络层，分别为其增加 TCP 头和 IP 头，执行路由查找确认下一 跳的 IP，并按照 MTU 大小进行分片。

分片后的网络包，再送到网络接口层，进行物理地址寻址，以找到下一跳的 MAC 地址。然 后添加帧头和帧尾，放到发包队列中。这一切完成后，会有软中断通知驱动程序：发包队列 中有新的网络帧需要发送。

最后，驱动程序通过 DMA ，从发包队列中读出网络帧，并通过物理网卡把它发送出去。
## 网络包的接收流程
了解了发送数据的过程以后，掌握接收数据的过程就更容易了，因为它就是发送数据的逆 过程。

首先，网卡接受到数据，通过 DMA 复制到指定的内存，接着发送中断，以便通知网卡驱动，由网卡驱动处理中断复制数据。然后网络协议收到网卡驱动传过来的数据，层层解包，获取真正的有效数据。最后，这个数据会发送给用户态监听的应用进程。
![[Pasted image 20220905101422.png|600]]

当一个网络帧到达网卡后，网卡会通过 DMA 方式，把这个网络包放到收包队列中；然后 通过硬中断，告诉中断处理程序已经收到了网络包。

接着，网卡中断处理程序会为网络帧分配内核数据结构（sk_buff），并将其拷贝到 sk_buff 缓冲区中；然后再通过软中断，通知内核收到了新的网络帧。

接下来，内核协议栈从缓冲区中取出网络帧，并通过网络协议栈，从下到上逐层处理这个网 络帧。比如，

在链路层检查报文的合法性，找出上层协议的类型（比如 IPv4 还是 IPv6），再去掉帧 头、帧尾，然后交给网络层。 网络层取出 IP 头，判断网络包下一步的走向，比如是交给上层处理还是转发。当网络层 确认这个包是要发送到本机后，就会取出上层协议的类型（比如 TCP 还是 UDP），去掉 IP 头，再交给传输层处理。

传输层取出 TCP 头或者 UDP 头后，根据 < 源 IP、源端口、目的 IP、目的端口 > 四元 组作为标识，找出对应的 Socket，并把数据拷贝到 Socket 的接收缓存中。

最后，应用程序就可以使用 Socket 接口，读取到新接收到的数据了。
![[Pasted image 20220926222547.png|900]]


## TCP 连接的建立过程会受哪些配置项的影响？
![[Pasted image 20220906103401.png|800]]
TCP 连接的建立是一个从 Client 侧调用 connect()， 到 Server 侧 accept() 成功返回的过程。

首先 Client 会给 Server 发送一个 SYN 包，但是该 SYN 包可能会在传输过程中丢失，或 者因为其他原因导致 Server 无法处理，此时 Client 这一侧就会触发超时重传机制。但是 也不能一直重传下去，重传的次数也是有限制的，这就是 tcp_syn_retries 这个配置项来决 定的。

半连接，即收到了 SYN 后还没有回复 SYNACK 的连接，Server 每收到一个新的 SYN 包，都会创建一个半连接，然后把该半连接加入到半连接队列（syn queue）中。syn queue 的长度就是 tcp_max_syn_backlog 这个配置项来决定的，当系统中积压的半连接 个数超过了该值后，新的 SYN 包就会被丢弃。对于服务器而言，可能瞬间会有非常多的新 建连接，所以我们可以适当地调大该值，以免 SYN 包被丢弃而导致 Client 收不到 SYNACK。

Server 中积压的半连接较多，也有可能是因为有些恶意的 Client 在进行 SYN Flood 攻 击。典型的 SYN Flood 攻击如下：Client 高频地向 Server 发 SYN 包，并且这个 SYN 包 的源 IP 地址不停地变换，那么 Server 每次接收到一个新的 SYN 后，都会给它分配一个半 连接，Server 的 SYNACK 根据之前的 SYN 包找到的是错误的 Client IP， 所以也就无法收到 Client 的 ACK 包，导致无法正确建立 TCP 连接，这就会让 Server 的半连接队列耗 尽，无法响应正常的 SYN 包。

为了防止 SYN Flood 攻击，Linux 内核引入了 SYN Cookies 机制。

在 Server 收到 SYN 包时，不去分配资源来保存 Client 的信息，而是根据这个 SYN 包计 算出一个 Cookie 值，然后将 Cookie 记录到 SYNACK 包中发送出去。对于正常的连接， 该 Cookies 值会随着 Client 的 ACK 报文被带回来。然后 Server 再根据这个 Cookie 检查 这个 ACK 包的合法性，如果合法，才去创建新的 TCP 连接。通过这种处理，SYN Cookies 可以防止部分 SYN Flood 攻击。所以对于 Linux 服务器而言，推荐开启 SYN Cookies

Server 向 Client 发送的 SYNACK 包也可能会被丢弃，或者因为某些原因而收不到 Client 的响应，这个时候 Server 也会重传 SYNACK 包。同样地，重传的次数也是由配置选项来 控制的，该配置选项是 tcp_synack_retries。

Client 在收到 Serve 的 SYNACK 包后，就会发出 ACK，Server 收到该 ACK 后，三次握 手就完成了，即产生了一个 TCP 全连接（complete），它会被添加到全连接队列 （accept queue）中。然后 Server 就会调用 accept() 来完成 TCP 连接的建立。

但是，就像半连接队列（syn queue）的长度有限制一样，全连接队列（accept queue） 的长度也有限制，目的就是为了防止 Server 不能及时调用 accept() 而浪费太多的系统资源

全连接队列（accept queue）的长度是由 listen(sockfd, backlog) 这个函数里的 backlog 控制的，而该 backlog 的最大值则是 somaxconn。somaxconn 在 5.4 之前的内核中， 默认都是 128（5.4 开始调整为了默认 4096），建议将该值适当调大一些

当服务器中积压的全连接个数超过该值后，新的全连接就会被丢弃掉。Server 在将新连接 丢弃时，有的时候需要发送 reset 来通知 Client，这样 Client 就不会再次重试了。不过， 默认行为是直接丢弃不去通知 Client。至于是否需要给 Client 发送 reset，是由 tcp_abort_on_overflow 这个配置项来控制的，该值默认为 0，即不发送 reset 给 Client。推荐也是将该值配置为 0

这是因为，Server 如果来不及 accept() 而导致全连接队列满，这往往是由瞬间有大量新建 连接请求导致的，正常情况下 Server 很快就能恢复，然后 Client 再次重试后就可以建连 成功了。也就是说，将 tcp_abort_on_overflow 配置为 0，给了 Client 一个重试的机会。 当然，你可以根据你的实际情况来决定是否要使能该选项。

accept() 成功返回后，一个新的 TCP 连接就建立完成了，TCP 连接进入到了 ESTABLISHED 状态

## TCP 连接的断开过程会受哪些配置项的影响？
![[Pasted image 20220906103832.png|800]]
首先调用 close() 的一侧是 active close（主动关闭）；而接收到对端的 FIN 包后再调用 close() 来关闭的一侧，称之为 passive close（被动关闭）。在四次挥手的过程中，有三 个 TCP 状态需要额外关注，就是上图中深红色的那三个状态：主动关闭方的 FIN_WAIT_2 和 TIME_WAIT，以及被动关闭方的 CLOSE_WAIT 状态。除了 CLOSE_WAIT 状态外，其 余两个状态都有对应的系统配置项来控制。

## 最大连接数是不是受限于 65535 个端口
无论 TCP 还是 UDP，端口号都只占 16 位，也就说其最大值也只有 65535。那是不是说，如果使用 TCP 协议，在单台机器、单个 IP 地址时，并发连接数最大也只有 65535 呢？

对于这个问题，首先你要知道，Linux 协议栈，通过五元组来标志一个连接（即协议，源 IP、源端口、目的 IP、目的端口)。

明白了这一点，这个问题其实就有了思路。我们应该分客户端和服务器端，这两种场景来分析。

对客户端来说，每次发起 TCP 连接请求时，都需要分配一个空闲的本地端口，去连接远端 的服务器。由于这个本地端口是独占的，所以客户端最多只能发起 65535 个连接。

对服务器端来说，其通常监听在固定端口上（比如 80 端口），等待客户端的连接。根据五元组结构，我们知道，客户端的 IP 和端口都是可变的。如果不考虑 IP 地址分类以及资源限制，服务器端的理论最大连接数，可以达到 2 的 48 次方（IP 为 32 位，端口号为 16 位），远大于 65535。

所以，综合来看，客户端最大支持 65535 个连接，而服务器端可支持的连接数是海量的。 当然，由于 Linux 协议栈本身的性能，以及各种物理和软件的资源限制等，这么大的连接数，还是远远达不到的（实际上，C10M 就已经很难了）。