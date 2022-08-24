
1.  你是否知道如何修复容器中的 top 指令以及 /proc 文件系统中的信息呢？（提示：lxcfs）
	- top 是从 /prof/stats 目录下获取数据，所以道理上来讲，容器不挂载宿主机的该目录就可以了。lxcfs就是来实现这个功能的，做法是把宿主机的 /var/lib/lxcfs/proc/memoinfo 文件挂载到Docker容器的/proc/meminfo位置后。容器中进程读取相应文件内容时，LXCFS的FUSE实现会从容器对应的Cgroup中读取正确的内存限制。从而使得应用获得正确的资源约束设定。kubernetes环境下，也能用，以ds 方式运行 lxcfs ，自动给容器注入争取的 proc 信息。

2.  在从虚拟机向容器环境迁移应用的过程中，你还遇到哪些容器与虚拟机的不一致问题？
	- 遇到的主要挑战就是性能损失和多租户隔离问题，性能损失目前没想到好办法，可能的方案是用ipvs 替换iptables ，以及用 RPC 替换 rest。多租户隔离也没有很好的方法，现在是让不同的namespace调度到不同的物理机上。也许 rancher和openshift已经多租户隔离。

4.  既然容器的 rootfs（比如，Ubuntu 镜像），是以只读方式挂载的，那么又如何在容器里修改 Ubuntu 镜像的内容呢？（提示：Copy-on-Write）
	- 上面的读写层通常也称为容器层，下面的只读层称为镜像层，所有的增删查改操作都只会作用在容器层，相同的文件上层会覆盖掉下层。知道这一点，就不难理解镜像文件的修改，比如修改一个文件的时候，首先会从上到下查找有没有这个文件，找到，就复制到容器层中，修改，修改的结果就会作用到下层的文件，这种方式也被称为copy-on-write。

5.  除了 AuFS，你知道 Docker 项目还支持哪些 UnionFS 实现吗？你能说出不同宿主机环境下推荐使用哪种实现吗？
	- 查了一下，包括但不限于以下这几种：aufs, device mapper, btrfs, overlayfs, vfs, zfs。aufs是ubuntu 常用的，device mapper 是 centos，btrfs 是 SUSE，overlayfs ubuntu 和 centos 都会使用，现在最新的 docker 版本中默认两个系统都是使用的 overlayfs，vfs 和 zfs 常用在 solaris 系统。

6.  你在查看 Docker 容器的 Namespace 时，是否注意到有一个叫 cgroup 的 Namespace？它是 Linux 4.6 之后新增加的一个 Namespace，你知道它的作用吗？
	- 4.6内核之前，查看/proc/$PID/cgroup，或者挂载cgroup时，在容器中会看到整个系统的cgroup，存在安全隐患，4.6内核之后新增cgroup namespace ，每个namespace中的进程都有自己的cgroup了；

7.  如果你执行 docker run -v /home:/test 的时候，容器镜像里的 /test 目录下本来就有内容的话，你会发现，在宿主机的 /home 目录下，也会出现这些内容。这是怎么回事？为什么它们没有被绑定挂载隐藏起来呢？（提示：Docker 的“copyData”功能）

8.  请尝试给这个 Python 应用加上 CPU 和 Memory 限制，然后启动它。根据我们前面介绍的 Cgroups 的知识，请你查看一下这个容器的 Cgroups 文件系统的设置，是不是跟我前面的讲解一致。

9. 这今天的分享中，我介绍了 Kubernetes 项目的架构。你是否了解了 Docker Swarm（SwarmKit 项目）跟 Kubernetes 在架构上和使用方法上的异同呢？

10.  在 Kubernetes 之前，很多项目都没办法管理“有状态”的容器，即，不能从一台宿主机“迁移”到另一台宿主机上的容器。你是否能列举出，阻止这种“迁移”的原因都有哪些呢？

11.  在 Linux 上为一个类似 kube-apiserver 的 Web Server 制作证书，你知道可以用哪些工具实现吗？

12.  回忆一下我在前面文章中分享的 Kubernetes 架构，你能够说出 Kubernetes 各个功能组件之间（包含 Etcd），都有哪些建立连接或者调用的方式吗？（比如：HTTP/HTTPS，远程调用等等）

你能否举出一些 Pod（即容器）的状态是 Running，但是应用其实已经停止服务的例子？相信 Java Web 开发者的亲身体会会比较多吧。
	1. 程序本身有 bug，本来应该返回 200，但因为代码问题，返回的是500；  
	2. 程序因为内存问题，已经僵死，但进程还在，但无响应；  
	3. Dockerfile 写的不规范，应用程序不是主进程，那么主进程出了什么问题都无法发现；  
	4. 程序出现死循环。