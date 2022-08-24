
## ROS2对比ROS1
 - OS
	 1. ROS1: Linux
	 2. ROS2: Linux, Windows, MAC RTOS
- 通讯
	 1. ROS1: TCPROS/UDPROS
	 2. ROS2: DDS
- 节点模型
	 1. ROS1: publish/subscribe
	 2. ROS2: discovery
- 进程
	 1. ROS1: Nodelet
	 2. ROS2: Intra-process


# 通信方式

ROS2提供了四种通信方式：

- 话题-Topics

  话题是单向的，而且不需要等待服务端上线，直接发就行，数据的实时性比较高。

  频率高，实时性强的传感器数据的传递一般使用话题实现。

- 服务-Services

  服务是双向的，客户端发送请求后，服务端有响应，可以得知服务端的处理结果。

  频率较低，强调服务特性和反馈的场景一般使用服务实现。

- 动作-Action

  动作适用于需要实时反馈的场景，原理基于话题和服务。

- 参数-Parameters

  参数是节点的设置，用于配置节点，原理基于服务。
  
  除了参数之外，话题、服务和动作(Action)都支持自定义接口，每一种通信方式所适用的场景各不相同，所定义的接口也被分为话题接口、服务接口、动作接口三种。
