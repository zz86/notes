# notes

**第一，你要吃透基础技术。基础技术是各种上层技术共同的基础**。吃透基础技术是为了更好地理解程序的运行原理，并基于这些基础技术进化出更优化的产品。吃透基础技术，有很多好处，具体来说，有如下几点。

1.  万丈高楼平地起。一栋楼能盖多高，一座大桥能造多长，重要的是它们的地基。同样对于技术人员来说，基础知识越扎实，走得就会越远。
    
2.  计算机技术太多了，但是仔细分析你会发现，只是表现形式很多，而基础技术并不多。学好基础技术，能让你一通百通，更快地使用各种新技术，从而可以更轻松地与时代同行。
    
3.  很多分布式系统架构，以及高可用、高性能、高并发的解决方案基本都可以在基础技术上找到它们的身影。所以，学习基础技术能让你更好地掌握更高维度的技术。
    

那么，哪些才是基础技术呢？我在下面罗列了一些。老实说，这些技术你学起来可能会感到枯燥无味，但是，我还是鼓励你能够克服人性的弱点，努力啃完。

具体来说，可以分成两个部分：**编程和系统**。

## 编程部分

-   **C 语言**：相对于很多其他高级语言来说，C 语言更接近底层。在具备跨平台能力的前提下，它可以比较容易地被人工翻译成相应的汇编代码。它的内存管理更为直接，可以让我们直接和内存地址打交道。
    
    学习好 C 语言的好处是能掌握程序的运行情况，并能进行应用程序和操作系统编程（操作系统一般是汇编和 C 语言）。要学好 C 语言，你可以阅读 C 语言的经典书籍《C 程序设计语言（第 2 版）》，同时，肯定也要多写程序，多读一些优秀开源项目的源代码。
    
    除了让你更为了解操作系统之外，学习 C 语言还能让你更清楚地知道程序是怎么精细控制底层资源的，比如内存管理、文件操作、网络通信……
    
    这里需要说明的是，我们还是需要学习汇编语言的。因为如果你想更深入地了解计算机是怎么运作的，那么你是需要了解汇编语言的。虽然我们几乎不再用汇编语言编程了，但是如果你需要写一些如 lock free 之类高并发的东西，那么了解汇编语言，就能有助于你更好地理解和思考。
    
-   **编程范式**：各种编程语言都有它们各自的编程范式，用于解决各种问题。比如面向对象编程（C++、Java）、泛型编程（C++、Go、C#）、函数式编程（JavaScript、 Python、Lisp、Haskell、Erlang）等。
    
    学好编程范式，有助于培养你的抽象思维，同时也可以提高编程效率，提高程序的结构合理性、可读性和可维护性，降低代码的冗余度，进而提高代码的运行效率。要学习编程范式，你还可以多了解各种程序设计语言的功能特性。
    
-   **算法和数据结构**：算法（及其相应的数据结构）是程序设计的有力支撑。适当地应用算法，可以有效地抽象问题，提高程序的合理性和执行效率。算法是编程中最最重要的东西，也是计算机科学中最重要的基础。
    
    任何有技术含量的软件中一定有高级的算法和数据结构。比如 epoll 中使用了红黑树，数据库索引使用了 B+ 树……而就算是你的业务系统中，也一定使用各种排序、过滤和查找算法。学习算法不仅是为了写出运转更为高效的代码，而且更是为了能够写出可以覆盖更多场景的正确代码。
    

## 系统部分

-   **计算机系统原理**：CPU 的体系结构（指令集 [CISC/RISC]、分支预测、缓存结构、总线、DMA、中断、陷阱、多任务、虚拟内存、虚拟化等），内存的原理与性能特点（SRAM、DRAM、DDR-SDRAM 等），磁盘的原理（机械硬盘 [盘面、磁头臂、磁头、启停区、寻道等]、固态硬盘 [页映射、块的合并与回收算法、TRIM 指令等]），GPU 的原理等。
    
    学习计算机系统原理的价值在于，除了能够了解计算机的原理之外，你还能举一反三地反推出高维度的分布式架构和高并发高可用的架构设计。
    
    比如虚拟化内存就和今天云计算中的虚拟化的原理是相通的，计算机总线和分布式架构中的 ESB 也有相通之处，计算机指令调度、并发控制可以让你更好地理解并发编程和程序性能调优……这里，推荐书籍《深入理解计算机系统》（Randal E. Bryant）。
    
-   **操作系统原理和基础**：进程、进程管理、线程、线程调度、多核的缓存一致性、信号量、物理内存管理、虚拟内存管理、内存分配、文件系统、磁盘管理等。
    
    学习操作系统的价值在于理解程序是怎样被管理的，操作系统对应用程序提供了怎样的支持，抽象出怎样的编程接口（比如 POSIX/Win32 API），性能特性如何（比如控制合理的上下文切换次数），怎样进行进程间通信（如管道、套接字、内存映射等），以便让不同的软件配合一起运行等。
    
    要学习操作系统知识，一是要仔细观察和探索当前使用的操作系统，二是要阅读操作系统原理相关的图书，三是要阅读 API 文档（如 man pages 和 MSDN Library），并编写调用操作系统功能的程序。这里推荐三本书《UNIX 环境高级编程》、《UNIX 网络编程》和《Windows 核心编程》。
    
    学习操作系统基础原理的好处是，这是所有程序运行的物理世界，无论上层是像 C/C++ 这样编译成机器码的语言，还是像 Java 这样有 JVM 做中间层的语言，再或者像 Python/PHP/Perl/Node.js 这样直接在运行时解释的语言，其在底层都逃离不了操作系统这个物理世界的“物理定律”。
    
    所以，了解操作系统的原理，可以让你更能从本质理解各种语言或是技术的底层原理。一眼看透本质可以让你更容易地掌握和使用高阶技术。
    
-   **网络基础**：计算机网络是现代计算机不可或缺的一部分。需要了解基本的网络层次结构（ISO/OSI 模型、TCP/IP 协议栈），包括物理层、数据链路层（包含错误重发机制）、网络层（包含路由机制）、传输层（包含连接保持机制）、会话层、表示层、应用层（在 TCP/IP 协议栈里，这三层可以并为一层）。
    
    比如，底层的 ARP 协议、中间的 TCP/UDP 协议，以及高层的 HTTP 协议。这里推荐书籍《TCP/IP 详解》，学习这些基础的网络协议，可以为我们的高维分布式架构中的一些技术问题提供很多的技术方案。比如 TCP 的滑动窗口限流，完全可以用于分布式服务中的限流方案。
    
-   **数据库原理**：数据库管理系统是管理数据库的利器。通常操作系统提供文件系统来管理文件数据，而文件比较适合保存连续的信息，如一篇文章、一个图片等。但有时需要保存一个名字等较短的信息。如果单个文件只保存名字这样的几个字节的信息的话，就会浪费大量的磁盘空间，而且无法方便地查询（除非使用索引服务）。
    
    但数据库则更适合保存这种短的数据，而且可以方便地按字段进行查询。现代流行的数据库管理系统有两大类：SQL（基于 B+ 树，强一致性）和 NoSQL（较弱的一致性，较高的存取效率，基于哈希表或其他技术）。
    
    学习了数据库原理之后便能了解数据库访问性能调优的要点，以及保证并发情况下数据操作原子性的方法。要学习数据库，你可以阅读各类数据库图书，并多做数据库操作以及数据库编程，多观察分析数据库在运行时的性能。
    
-   **分布式技术架构**：数据库和应用程序服务器在应对互联网上数以亿计的访问量的时候，需要能进行横向扩展，这样才能提供足够高的性能。为了做到这一点，要学习分布式技术架构，包括负载均衡、DNS 解析、多子域名、无状态应用层、缓存层、数据库分片、容错和恢复机制、Paxos、Map/Reduce 操作、分布式 SQL 数据库一致性（以 Google Cloud Spanner 为代表）等知识点。
    
    学习分布式技术架构的有效途径是参与到分布式项目的开发中去，并阅读相关论文。
    

注意，**上面这些基础知识通常不是可以速成的**。虽然说，你可以在一两年内看完相关的书籍或论文，但是，我想说的是，这些基础技术是需要你用一生的时间来学习的，因为基础上的技术和知识，会随着阅历和经验的增加而有不同的感悟。

**第二，提高学习能力。所谓学习能力，就是能够很快地学习新技术，又能在关键技术上深入的能力**。只有在掌握了上述的基础原理之上，你才能拥有好的学习能力。

下面是让你提升学习能力的一些做法。

-   **学习的信息源**。信息源很重要，有好的信息源就可以更快速地获取有价值的信息，并提升学习效率。常见的信息源有 Google 等搜索引擎，Stack Overflow、Quora 等社区，图书，API 文档，论文和博客等。
    
    这么说吧，如果今天使用中文搜索就可以满足你的知识需求，那么你就远远落后于这个时代了。如果用英文搜索才能找到你想要的知识，那么你才能算跟得上这个时代。而如果说有的问题你连用英文搜索都找不到，只能到社区里去找作者或者其他人交流，那么可以说你已真正和时代同频了。
    
-   **与高手交流**。程序员可以通过技术社区以及参加技术会议与高手交流，也可以通过参加开源项目来和高手切磋。常闻“听君一席话，胜读十年书”便是如此。与高手交流对程序员的学习和成长很有益处，不仅有助于了解热门的技术方向及关键的技术点，更可以通过观察和学习高手的技术思维及解决问题的方式，提高自己的技术前瞻性和技术决策力。
    
    我在 Amazon 的时候，就有人和我说，多和美国的 Principle SDE 以上的工程师交流，无论交流什么，你都会有收获的。其实，这里说的就是，学习这些牛人的思维方式和看问题的角度，这会让你有质的提高。
    
-   **举一反三的思考**。比如，了解了操作系统的缓存和网页缓存以后，你要思考其相同点和不同点。了解了 C++ 语言的面向对象特性以后，思考 Java 面向对象的相同点和不同点。遇到故障的时候，举一反三，把同类问题一次性地处理掉。
    
-   **不怕困难的态度**。遇到难点，有时不花一番力气，是不可能突破的。此时如果没有不怕困难的态度，你就容易打退堂鼓。但如果能坚持住，多思考，多下功夫，往往就能找到出路。绝大多数人是害怕困难的，所以，如果你能够不怕困难，并可以找到解决困难的方法和路径，时间一长，你就能拥有别人所不能拥有的能力。
    
-   **开放的心态**。实现一个目的通常有多种办法。带有开放的心态，不拘泥于一个平台、一种语言，往往能带来更多思考，也能得到更好的结果。而且，能在不同的方法和方案间做比较，比较它们的优缺点，那么你会知道在什么样的场景下用什么样的方案，你就会比一般人能够有更全面和更完整的思路。