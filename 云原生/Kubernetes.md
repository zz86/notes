## Kubernetes架构
![[Pasted image 20220822215142.png|800]]

## Kubernetes的核心思想
声明式 API与控制器模式- Infrastructure as Data (laD)
	1. 将任何一个底层基础设施的“能力”都建模为一份“数据”
	2. “数据”中的内容是对该应用基础设期望状态的描述
	3. “数据”的增删改查会触发控制器(Controller)执行对应的运维逻辑,以此来驱动底层基础设施向“数据”所定义的期望状态逼近

在 Kubernetes 项目中，我们所推崇的使用方法是：

-   首先，通过一个“编排对象”，比如 Pod、Job、CronJob 等，来描述你试图管理的应用；
-   然后，再为它定义一些“服务对象”，比如 Service、Secret、Horizontal Pod Autoscaler（自动水平扩展器）等。这些对象，会负责具体的平台级功能。

**这种使用方法，就是所谓的“声明式 API”。这种 API 对应的“编排对象”和“服务对象”，都是 Kubernetes 项目中的 API 对象（API Object）。**
## Kubernetes 项目的本质
- Kubernetes项目其实只有“两个部分”
	1. 对底层基础设施各种能力的声明式 API定义
	2. 上述声明式API对应的控制器

## k8s集群架构组件
-  master(主控节点)和node (工作节点)
-  master组件
	-  apiserver：集群统一入口,以restful方式,交给etcd存储
	-  scheduler：节点调度,选择node节点应用部署
	-  controller-manager：处理集群中常规后台任务,一个资源对应一个控制器
	- etcd：存储系统,用于保存集群相关的数据
 - node组件
	 -  kubelet：master派到node节点代表,管理本机容器
	 -  kube-proxy：提供网络代理,负载均衡等操作

## k8s核心概念
-  Pod
	- 最小部署单元
	- 一组容器的集合
	- 共享网络
	- 生命周期是短暂的
 - controller
	 - 确保预期的pod副本数量
	- 无状态应用部署，有状态应用部署
	- 确保所有的node运行同一个pod
	- 一次性任务和定时任务
- Service
	- 定义一组pod的访问规则

## 搭建集群方式
1. kubeadm
2. 二进制包

## yaml文件
- 语法格式
	1. 通过缩进表示层级关系
	2. 不能使用Tab进行缩进,只能使用空格
	3. 一般缩进两个空格
	4. 字符后缩进一个空格,比如冒号,逗号等后面
	5. 使用---表示新的yaml文件开始
	6. 使用#代表注释

## Pod
- Pod 是Kubernetes的最重要概念,每一个Pod都有一个特殊的被称为”根容器“的Pause容器。Pause容器对应的镜像属于Kubernetes平台的一部分,除了Pause容器,每个Pod还包含一个或多个紧密相关的用户业务容器
- 存在意义
	1. 创建容器使用docker,一个docker对应:一个容器,一个容器有进程,一个容器运行一个应用程序
	2. Pod是多进程设计,运行多个应用程序，一个Pod有多个容器,一个容器里面运行一个应用程序
	3. Pod存在为了亲密性应用
		- 两个应用之间进行交互
		- 网络之间调用
		- 两个应用需要频繁调用
- Pod实现机制
	- 共享网络: 通过Pause容器,把其他业务容器加入到Pause容器里面,让所有业务容器在同一个名称空间中,可以实现网络共享
	- 共享存储：引入数据卷概念Volumn,使用数据卷进行持久化存储
- Pod镜像拉取策略
	- IfNotPresent:默认值,镜像在宿主机上不存在时才拉取
	- Always:每次创建Pod都会重新拉取一次镜像
	- Never: Pod永远不会主动拉取这个镜像
- Pod资源限制
- Pod重启策略
	- Always:当容器终止退出后,总是重启容器,默认策略。
	- OnFailure:当容器异常退出(退出状态码非0)时,才重启容器。
	- Never:当容器终止退出,从不重启容器。

## Deployment

## Service
ClusterIP 模式的 Service 为你提供的，就是一个 Pod 的稳定的 IP 地址，即 VIP。并且，这里 Pod 和 Service 的关系是可以通过 Label 确定的。

而 Headless Service 为你提供的，则是一个 Pod 的稳定的 DNS 名字，并且，这个名字是可以通过 Pod 名字和 Service 名字拼接出来的。

所谓 Service，其实就是 Kubernetes 为 Pod 分配的、固定的、基于 iptables（或者 IPVS）的访问入口

**Service 是由 kube-proxy 组件，加上 iptables 来共同实现的。**

kube-proxy 通过 iptables 处理 Service 的过程，其实需要在宿主机上设置相当多的 iptables 规则。而且，kube-proxy 还需要在控制循环里不断地刷新这些规则来确保它们始终是正确的。

不难想到，当你的宿主机上有大量 Pod 的时候，成百上千条 iptables 规则不断地被刷新，会大量占用该宿主机的 CPU 资源，甚至会让宿主机“卡”在这个过程中。所以说，**一直以来，基于 iptables 的 Service 实现，都是制约 Kubernetes 项目承载更多量级的 Pod 的主要障碍。**

而 IPVS 模式的 Service，就是解决这个问题的一个行之有效的方法。

## StatefulSet
StatefulSet 的设计其实非常容易理解。它把真实世界里的应用状态，抽象为了两种情况：

1.  **拓扑状态**。这种情况意味着，应用的多个实例之间不是完全对等的关系。这些应用实例，必须按照某些顺序启动，比如应用的主节点 A 要先于从节点 B 启动。而如果你把 A 和 B 两个 Pod 删除掉，它们再次被创建出来时也必须严格按照这个顺序才行。并且，新创建出来的 Pod，必须和原来 Pod 的网络标识一样，这样原先的访问者才能使用同样的方法，访问到这个新 Pod。
    
2.  **存储状态**。这种情况意味着，应用的多个实例分别绑定了不同的存储数据。对于这些应用实例来说，Pod A 第一次读取到的数据，和隔了十分钟之后再次读取到的数据，应该是同一份，哪怕在此期间 Pod A 被重新创建过。这种情况最典型的例子，就是一个数据库应用的多个存储实例。
    

所以，**StatefulSet 的核心功能，就是通过某种方式记录这些状态，然后在 Pod 被重新创建时，能够为新 Pod 恢复这些状态。**

## DaemonSet


## Job


## Ingress
**所谓 Ingress，就是 Service 的“Service”**


## 声明式API
kubectl apply

**Kubernetes“声明式 API”的独特之处：**

-   首先，所谓“声明式”，指的就是我只需要提交一个定义好的 API 对象来“声明”，我所期望的状态是什么样子。
-   其次，“声明式 API”允许有多个 API 写端，以 PATCH 的方式对 API 对象进行修改，而无需关心本地原始 YAML 文件的内容。
-   最后，也是最重要的，有了上述两个能力，Kubernetes 项目才可以基于对 API 对象的增、删、改、查，在完全无需外界干预的情况下，完成对“实际状态”和“期望状态”的调谐（Reconcile）过程。

所以说，**声明式 API，才是 Kubernetes 项目编排能力“赖以生存”的核心所在**

## 从外部访问 Service 的三种方式
NodePort、LoadBalancer 和 External Name



