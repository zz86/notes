
#### nodelet

ROS是以一种分布式网络通讯的操作系统，它是以master为中心构建的hybrid P2P网络，节点之间的信息传递时会存在一定的时延和阻塞，nodelet就是为了解决这一问题，提供在算法之间具有零拷贝传输的相同进程中运行多个算法的方式。

使用ROS中nodelet包可以实现在同一个进程内同时运行多种算法，且算法之间通信开销零拷贝。这个包有2个重要的class：1）提供了实现nodelet插件所必须的基类nodelet::Nodelet； 2）提供了NodeletLoader类用以实例化nodelet插件。由于nodelets实现了零拷贝，所以常常应用于大数据吞吐量场景，避免了多node通过ROSTCP通信带来的延时问题。

nodelets动态加载nodelet插件类到同一个node中实现了零拷贝， 加入进来的各个nodelet虽然在同一个进程内，但是由于nodelet拥有自己的命名空间，所以看似是一个个独立的node在存在。

1）nodelet包定义了一个基类nodelet::Nodelet，所有的nodelet插件类会继承这个基类，并通过pluginlib实现nodelet插件的动态加载；

2）存在一个nodelet_manager进程，可以把nodelet到加载到该manager内进行管理；

3）任何nodelet之间的通信可以使用零拷贝的roscpp publish完成，这种零拷贝实质上是使用了boost shared_ptr;

4). 节点管理器具有线程池，该线程池在管理器内运行的所有节点之间共享。Thread Sharing线程共享，所有nodelet共享管理器的线程池。如果nodelet阻塞线程，它们可能会阻止其他nodelet获得回调。确保管理器配置了足够的线程以防止阻塞。

**nodelet usage:**

```shell
nodelet load pkg/Type manager - Launch a nodelet of type pkg/Type on manager manager  
nodelet standalone pkg/Type   - Launch a nodelet of type pkg/Type in a standalone node  
nodelet unload name manager   - Unload a nodelet a nodelet by name from manager  
nodelet manager               - Launch a nodelet manager node
```



启动turtlebot后一共会启动如下七个节点：

#### 1. mobile_base_nodelet_manager (nodelet/nodelet)

mobile_base_nodelet_manager为整个设备的基础节点，类似于kobuki的设备控制台。

#### 2. bumper2pointcloud (nodelet/nodelet) 

package：kobuki_bumper2pc/Bumper2PcNodelet

- 保险杆和悬崖传感器点云Nodelet节点实现
- 发布导航包可使用的点云话题
- 在导航中作为Nodelet与kobuki_node一起工作。

#### 3. cmd_vel_mux (nodelet/nodelet)

package：yocs_cmd_vel_mux/CmdVelMuxNodelet

进行速度的选择,比如机器人在自主导航时遇到紧急情况要切换到手动控制模式，这时就要将机器人控制权从自主导航的节点切换到方向盘、手柄、键盘、急停开关等控制节点。
例如机器人自主导航时可能会有下面4种优先级的任务（通常将自主行为的优先级设为最低）：
3 (highest priority): safety controller （安全控制）
2: keyboard teleop （键盘遥控）
1: android teleop （Android 遥控）
0 (lowest priority): navi stack teleop （导航包自主控制）

**订阅topic：**

- ~input/cmd_vel （geometry_msgs/Twist）
  - /cmd_vel_mux/input/navi
  - /cmd_vel_mux/input/safety_controller

  - /cmd_vel_mux/input/switch

  - /cmd_vel_mux/input/teleop

**发布topic**

- ~/output （geometry_msgs/Twist）

启动时被重定向到mobile_base/commands/velocity，也就是最终kobuki的运行速度

`<remap from="cmd_vel_mux/output" to="mobile_base/commands/velocity"/>`

- ~/active  （std_msgs/String）

某时刻cmd_vel_mux选择的速度，如果没有速度输入则为idle

#### 4. mobile_base (nodelet/nodelet)

package：kobuki_node/KobukiNodelet

- kobuki核心类，作为nodelet节点使用，封装了与kobuki通信的c++驱动
- 发布版本信息话题，IMU数据话题，各类事件话题，各类传感器话题
- 订阅速度话题，电机话题，LED灯命令话题等

#### 5. diagnostic_aggregator (diagnostic_aggregator/aggregator_node)

一个诊断器，收集tutlebot的信息在经过处理分类后发布出来。有两种分析方法GenericAnalyzer和AnalyzerGroup

#### 6. robot_state_publisher (robot_state_publisher/robot_state_publisher)

这个节点维护并发布robot的关键(关节)位置的坐标系信息到tf上，一旦该这些信息被发布说明robot的各个关键(关节)坐标系的依赖关系确定，robot也就可以做各种动作。package也可以当成库文件用来发布自己robot的节点关键信息。

#### 7. turtlebot_laptop_battery (laptop_battery_monitor/laptop_battery.py)



#### topic list

- **/cmd_vel_mux/active**

- **/cmd_vel_mux/input/navi**

- **/cmd_vel_mux/input/safety_controller**

- **/cmd_vel_mux/input/switch**

- **/cmd_vel_mux/input/teleop**

- **/cmd_vel_mux/parameter_descriptions**

- **/cmd_vel_mux/parameter_updates**

- **/diagnostics**

(diagnostic_msgs/DiagnosticArray)1Hz的系统诊断信息

- **/diagnostics_agg**

- **/diagnostics_toplevel_state**

- /**joint_states**

(sensor_msgs/JointState)更新轮胎节点信息

- **/laptop_charge**

- **/mobile_base/commands/controller_info**

(kobuki_msgs/ControllerInfo) 对robot的轮胎速度控制器设置预期的PID增益

- **/mobile_base/commands/digital_output**

(kobuki_msgs/DigitalOutput) 设置数字输出端口

- **/mobile_base/commands/external_power**

(kobuki_msgs/ExternalPower) 开启关闭额外的电源

- **/mobile_base/commands/led1**

(kobuki_msgs/Led) led1的控制命令

- **/mobile_base/commands/led2**

(kobuki_msgs/Led) led2的控制命令

- **/mobile_base/commands/motor_power**

(kobuki_msgs/MotorPower)开启、关闭电机电源

- **/mobile_base/commands/reset_odometry**

(std_msgs/Empty) 重启里程计数器

- **/mobile_base/commands/sound**

(kobuki_msgs/Sound) 发送播放的声音

- **/mobile_base/commands/velocity**

(geometry_msgs/Twist) 设置预期速度，控制移动底盘

- **/mobile_base/controller_info**

(kobuki_msgs/ControllerInfo) robot 轮胎速度控制器的PID增益

- **/mobile_base/debug/raw_control_command**

(std_msgs/Int16MultiArray) 包括两个控制命令的原始数据，从xxx node 接受到的命令和发送到robot的命令。

- **/mobile_base/debug/raw_data_command**

(std_msgs/String) 发送到robot的原始byte数据

- **/mobile_base/debug/raw_data_stream**

(std_msgs/String) 从robot接收到的原始byte数据

- **/mobile_base/events/bumper**

(kobuki_msgs/BumperEvent)减震器被挤压或松开事件

- **/mobile_base/events/button**

(kobuki_msgs/ButtonEvent)按键被按下或抬起事件

- **/mobile_base/events/cliff**

(kobuki_msgs/CliffEvent)悬崖传感器事件，是否接近或离开悬崖

- **/mobile_base/events/digital_input**

(kobuki_msgs/DigitalInputEvent) 数字输入端口改变事件

-  **/mobile_base/events/power_system**

(kobuki_msgs/PowerSystemEvent)电源系统事件，插入/拔出，高/低电量，更换电源

- **/mobile_base/events/robot_state**

(kobuki_msgs/RobotStateEvent)robot 上线或下线事件

- **/mobile_base/events/wheel_drop**

(kobuki_msgs/WheelDropEvent)轮胎悬空事件，当悬空时发布

- **/mobile_base/sensors/bumper_pointcloud**

- **/mobile_base/sensors/core**

(kobuki_msgs/SensorState)kobuki整体传感器详细信息，50Hz

- **/mobile_base/sensors/dock_ir**

(kobuki_msgs/DockInfraRed) 红外传感器对接信息

- **/mobile_base/sensors/imu_data**

(sensor_msgs/Imu) 陀螺仪数据信息，提供它的航向和角速度

- **/mobile_base/sensors/imu_data_raw**

(sensor_msgs/Imu) 3D陀螺仪的原始信息(x,y,z)

- **/mobile_base/version_info**

(kobuki_msgs/VersionInfo)kobuki版本，UID，平台特点。

- **/mobile_base_nodelet_manager/bond**

- **/odom**

(nav_msgs/Odometry)基于robot的陀螺仪和电机编码器计算出来的里程信息，包括：位置信息和速度信息

- **/rosout**

- **/rosout_agg**

- **/tf**

- **/tf_static**

#### param list 

- **/bumper2pointcloud/pointcloud_radius**
- **/cmd_vel_mux/yaml_cfg_data**
- **/cmd_vel_mux/yaml_cfg_file**
- **/diagnostic_aggregator/analyzers/input_ports/contains**
- **/diagnostic_aggregator/analyzers/input_ports/path**
- **/diagnostic_aggregator/analyzers/input_ports/remove_prefix**
- **/diagnostic_aggregator/analyzers/input_ports/timeout**
- **/diagnostic_aggregator/analyzers/input_ports/type**
- **/diagnostic_aggregator/analyzers/kobuki/contains**
- **/diagnostic_aggregator/analyzers/kobuki/path**
- **/diagnostic_aggregator/analyzers/kobuki/remove_prefix**
- **/diagnostic_aggregator/analyzers/kobuki/timeout**
- **/diagnostic_aggregator/analyzers/kobuki/type**
- **/diagnostic_aggregator/analyzers/power/contains**
- **/diagnostic_aggregator/analyzers/power/path**
- **/diagnostic_aggregator/analyzers/power/remove_prefix**
- **/diagnostic_aggregator/analyzers/power/timeout**
- **/diagnostic_aggregator/analyzers/power/type**
- **/diagnostic_aggregator/analyzers/sensors/contains**
- **/diagnostic_aggregator/analyzers/sensors/path**
- **/diagnostic_aggregator/analyzers/sensors/remove_prefix**
- **/diagnostic_aggregator/analyzers/sensors/timeout**
- **/diagnostic_aggregator/analyzers/sensors/type**
- **/diagnostic_aggregator/base_path**
- **/diagnostic_aggregator/pub_rate**
- **/mobile_base/base_frame**

(string, default: base_footprint) 基础TF框架名称

- **/mobile_base/battery_capacity**

(double, default: 16.5) 电池放电电压

- **/mobile_base/battery_dangerous**

(double, default: 13.2) 电量危险标准

- **/mobile_base/battery_low**

(double, default: 13.5) 电量警告标准

- **/mobile_base/cmd_vel_timeout**

(double, default: 0.6) 新命令超时时间

- **/mobile_base/device_port**

(string, default: /dev/kobuki) linux usb 设备端口，出厂默认为/dev/kobuki

- **/mobile_base/odom_frame**

(string, default: odom) 里程计数器tf框架名字

- **/mobile_base/publish_tf**

(bool, default: False) false: 大多数情况下tf从odom到base_link ，true:由robot_pose_ekf发布tf，当odom不使用的情况下

- **/mobile_base/use_imu_heading**

(bool, default: True) 使用imu读航向方式代替其编码，这是kobuki的正常模式，因为陀螺仪非常准确。当你想要使用更复杂的方式则disable它，例如过滤并使用robot_pose_ekf。

- **/mobile_base/wheel_left_joint_name**

(string, default: wheel_left_joint) 左轮胎关节状态的名称

- **/mobile_base/wheel_right_joint_name**

(string, default: wheel_right_joint) 右轮胎关节状态的名称

- **/robot/name**
- **/robot/type**
- **/robot_description**
- **/robot_state_publisher/publish_frequency**
- **/rosdistro**
- **/rosversion**
- **/run_id**
- **/turtlebot_laptop_battery/acpi_path**
- **/use_sim_time**





