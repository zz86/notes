#### ros navigation

​		ROS Navigation整个包的一个命名规则是，带有ROS后缀的类完成的是该子过程与整体和其他过程的衔接框架和数据流通，不带ROS后缀的类中完成该部分的实际工作，并作为带有ROS后缀的类的成员。

move_base运行时会有以下四个自己特有的线程（除了几个任何ros节点都有的线程）：

|          包名          |                             功能                             |
| :--------------------: | :----------------------------------------------------------: |
|          amcl          |                             定位                             |
|   fake_localization    |                             定位                             |
|       map_server       |                           提供地图                           |
|       move_base        |                         路径规划节点                         |
|        nav_core        | 路径规划的接口类，包括base_local_planner、base_global_planner和recovery_behavior三个接口 |
|   base_local_planner   |        实现了Trajectory Rollout和DWA两种局部规划算法         |
|   dwa_local_planner    | 重新实现了DWA局部规划算法，可以看作是base_local_planner的改进版本   （默认） |
|     carrot_planner     |                  实现了较简单的全局规划算法                  |
|         navfn          |                实现了Dijkstra和A*全局规划算法                |
|     global_planner     | 重新实现了Dijkstra和A*全局规划算法，可以看作navfn的改进版 （默认） |
| clear_costmap_recovery |                 实现了清除代价地图的恢复行为                 |
|    rotate_recovery     |                     实现了旋转的恢复行为                     |
|  move_slow_and_clear   |                   实现了缓慢移动的恢复行为                   |
|       costmap_2d       |                         二维代价地图                         |
|       voxel_grid       |                     三维小方块（体素？）                     |
|     robot_pose_ekf     |                    机器人位姿的卡尔曼滤波                    |

ros navigation 导航默认的局部路径规划和全局路径规划为：

```shell
base_local_planner: "dwa_local_planner/DWAPlannerROS"
base_global_planner: "navfn/NavfnROS" #alternatives: global_planner/GlobalPlanner, carrot_planner/CarrotPlanner
(turtlebot_apps/turtlebot_navigation/params/move_base_params.yaml)
```

为了使用导航包中的 move_base 节点，我们需要有全局规划器和局部规划器。

#### 全局路径规划器 --plugin

MoveBase的全局规划线程通过调用配置的实际全局规划器的makePlan方法来计算全局路径规划。基类是`class BaseGlobalPlanner（navigation\nav_core\include\nav_core\ base_global_planner.h）`， 具体的全局规划器需要继承此基类。 例如，GlobalPlanner就继承此基类，并实现相应的方法。

`class GlobalPlanner : public nav_core::BaseGlobalPlanner`

`(navigation\global_planner\include\global_planner\planner_core.h)`

在导航包中有三种全局规划器：carrot_planner、navfn 和 global_planner。

1. carrot_planner

   这是最简单的一种规划器。它检查给定的目标点是否是障碍物，如果是，则通过沿机器人和目标点的向量来选择靠近原始目标的替代目标。最终他将给局部规划器或内部控制器一个有效的目标点。因此，这种规划器没有任何全局路径规划。如果你需要机器人靠近给定的目标，即使目标不可到达的情况下，这种方法是有效的。但在复杂的室内环境中，这种方法不是很实用。

2. Navfn

   navfn 默认使用 dijkstra 算法来在起点和终点之间寻找最小代价路线。
   
   NavFn的源码中实际上是有A规划算法的函数的，但关于为什么不在NavFn中使用A，ROS Wiki上对提问者的回答是，早期NavFn包中的A有bug，没有处理，后来发布了global_planner，修改好了A的部分。global_planner封装性更强，它和NavFn都是用于全局路径规划的包。
   
3. global_planner （默认）

   global 规划器建立了更灵活的替代 navfn 的选择，这些选择包括：（1）支持 A算法（2）切换二次近似（3）切换网格路径

   global_planner功能包的GlobalPlanner继承了nav_core:: BaseGlobalPlanner，实现了makePlan()函数。makePlan()函数的基本流程就是输入起点和终点，读取代价地图，使用A*或者dijkstra算法进行规划，调用OrientationFilter类中的方法对路径进行优化，将规划好的路径以话题的形式发布。

#### 局部路径规划器 --plugin

传感器topic则在局部路径规划时起到作用，这部分就是costmap包起到的作用了，costmap为代价地图，目前主要的有inflation_layer、obstacle_layer、static_layer、voxel_layer四个plugins。分别为膨胀层、障碍物层、静态层和体素层。一般我们的全局路径需要静态层和膨胀层，因为全局规划应该只考虑到地图信息，所以一般都是静态的，而局部路径规划则需要考虑到实时的障碍物信息，所以需要障碍物层和膨胀层，这里你可能会有疑惑，为什么不把静态层放到局部路径规划里呢？因为我们的定位是会存在误差的，比如轮子打滑或其他情况，这个时候amcl会起到纠正作用，如果我们把静态层放到了局部中，这个定位会有问题，而且，假设当前机器人出现了定位的偏差，那么这个引入的静态层肯定是错误的，再加上局部的障碍物层（这里的障碍物层本应该和静态层重合的，但由于定位偏差，不会重合）可能会使得机器人误以为自己在障碍物层内，规划出现问题。

以DWA局部规划器为例，当规划全局路径的线程planThread在控制循环中输出新的路径时，新的路径将通过setPlan()传递给DWAPlannerROS，直接保存为global_plan_。如果isGoalReached()返回false，程序继续执行调用computeVelocityCommands()。

在computeVelocityCommands()中会调用getLocalPlan()对全局路径进行分段，并调用dwaComputeVelocityCommands()使用DWA算法计算最优速度，最后在move_base中发布速度指令。当机器人到达目标位姿且速度小于停止速度时，isGoalReached()返回true。

#### recovery_behavior --plugin

ROS 导航包有两种恢复行为，分别是clear_costmap_recovery和rotate_recovery。

1. clear_costmap_recovery（清除代价地图恢复）是将本地代价地图还原成全局代价地图的状态，其实就是将给定区域内的障碍物从代价地图中清除。
2. rotate_recovery(旋转恢复)是通过旋转 360°来清楚代价地图中的障碍物。


#### Movebase

该类利用`actionlib::SimpleActionServer<move_base_msgs::MoveBaseAction>`给出的接口来实现：给定一个目标，然后控制移动机器人走到目标点的功能。move_base包采用action机制，使移动底座到达给定的目标点。

- 构造函数 MoveBase::MoveBase | 初始化Action

- 控制主体 MoveBase::executeCb | 收到目标，触发全局规划线程，循环执行局部规划

- 全局规划线程 void MoveBase::planThread | 调用全局规划

- 全局规划 MoveBase::makePlan | 调用全局规划器类方法，得到全局规划路线

- 局部规划 MoveBase::executeCycle | 传入全局路线，调用局部规划器类方法，得到速度控制指令

  

**Action注册的topic**

```ymal
move_base/goal(move_base_msgs/MoveBaseActionGoal) #move_base所搜寻的目标
move_base/cancel(actionlib_msgs/GoalID) #请求取消目标点
```

**Action发布的topic**

```
move_base/feedback(move_base_msgs/MoveBaseActionFeedback) #反馈包括底座当前相对于世界坐标系的位置
move_base/status(actionlib_msgs/GoalStatusArray) #提供发送给move_base action的目标的状态信息
move_base/result(move_base_msgs/MoveBaseActionResult) #对move_base action来说，result为空
```

**节点注册的topic**

```
move_base_simple/goal(geometry_msgs/PoseStamped) #为不需要跟踪目标执行状态的情况提供非action接口
```

**节点发布的topic**

```
cmd_vel(geometry_msgs/Twist) #速度指令流，用以移动底座
```

**actionlib**

actionlib 堆栈为与可抢占任务交互提供了一个标准化接口。这方面的示例包括将基座移动到目标位置、执行激光扫描并返回结果点云、检测门把手等

**相关参数**

```
~base_global_planner(string, default:"navfn/NavfnROS") #指定用于move_base的全局规划器插件名称
~base_local_planner(string, default:"base_local_planner/TrajectoryPlannerROS") #指定用于move_base的局部规划器名称
~recovery_behaviors(list, default:[{name:conservative_reset, type:clear_costmap_recovery/ClearCostmapRecovery},{name:rotate_recovery,type:rotate_recovery/RotateRecovery},{name:aggressive_reset,type:clear_costmap_recovery/ClearCostmapRecovery}]) #用于move_base修复的插件列表，当move_base找不到可行的路径规划方案时，move_base将按照这些顺序执行操作。每个操作执行完后，move_base会在此尝试生成路径规划方案，如果成功，则继续正常操作；否则，启动下一个修复操作。
~controller_frequency(double, default:20.0) #控制循环的执行频率，也可认为是速度发布指令的频率
~planner_patience(double, default:5.0) #规划器在空间清除操作前,能够进行路径规划的时间
~conservative_reset_dist(double, default:3.0) #当在地图中清理出空间时，距离机器人几米远的障碍会从代价地图中清除
~recovery_behavior_enabled(bool, default:true) #是否启用move_base修复机制
~clearing_rotation_allowed(bool, default:true) #在清除空间操作时，是否允许底座原地旋转
~shutdown_costmaps(bool, default:false) #当move_base不活动时，是否关闭costmaps
~oscillaiton_timeout(double, default:0.0) #执行修复机制前，允许振荡的时长
~oscillation_distance(double, default:0.5) #来回运动在多大距离以上不会被认为是振荡
~planner_frequency(double, default:0.0) #全局规划操作的执行频率。如果设置为0.0，则全局规划器仅在接收到新的目标点或者局部规划器报告路径堵塞时才会重新执行规划操作
~max_planning_retries(int32, default:-1) #在执行修复操作前，允许规划器重新规划路径的次数，-1.0表示无限多次重新尝试
```

#### AMCl

amcl在ROS Navigation Stack中的作用就是输出map->odom的tf变换，来弥补里程计的漂移误差，它要求在机器人的定位系统中要存在里程计位姿估计，即odom->base_link的tf变换，并给定起始位姿和输入传感器数据。

#### nav_core

以上所有的插件(global planner、local planner、recovery behavior)都是继承于`nav_core`里的接口，`nav_core`属于一个接口package，它只定义了三种插件的规范，也可以说定义了三种接口类，然后分别由以上的插件来继承和实现这些接口。因此如果你要研究路径规划算法，不妨研究一下`nav_core`定义的路径规划工作流程，然后仿照`dwa_local_planner`或其他插件来实现。

1. BaseGlobalPlanner中定义了纯虚函数makePlan()，makePlan()用于实现规划全局路径，基本流程就是输入起点和终点，读取代价地图，使用A*或者dijkstra算法进行规划，调用OrientationFilter类中的方法对路径进行优化，将规划好的路径以话题的形式发布。
2. BaseLocalPlanner中定义了纯虚函数setPlan()、isGoalReached()和computeVelocityCommands()，setPlan()用于实现设定局部规划器跟踪的路径，isGoalReached()用于实现判断是否到达目标点，computeVelocityCommands()用于实现计算安全的速度指令。
3. RecoveryBehavior定义了纯虚函数runBehavior()，runBehavior()用于实现执行恢复行为。

#### costmap_2d

除了以上三个需要指定的插件外，还有一个**costmap**插件，该插件默认已经选择好，默认即为**costmap_2d**，不可更改，但costmap_2d提供了不同的Layer可以供我们设置

代价地图有一下特点：
１．首先，代价地图有两张，一张是`local_costmap`，一张是`global_costmap`，分别用于局部路径规划器和全局路径规划器，而这两个costmap都默认并且只能选择`costmap_2d`作为插件。
２. 无论是`local_costmap`还是`global_costmap`，都可以配置他们的Layer，可以选择多个层次。costmap的Layer包括以下几种：

- Static Layer：静态层，通常都是SLAM建立完成的静态地图。

  通常都是使用SLAM建立完成的静态地图，SLAM构建的地图在导航中是不可以直接使用的，因为SLAM构建的地图没有代价因子，静态地图需要转换成静态代价地图，静态地图层代表代价地图的一个很大的不变部分。

  静态地图层只是简单地将灰度图中的像素值换算成ros代价地图中的代价值


- Obstacle Layer：障碍层，用于动态的记录传感器感知到的障碍物信息。

- Inflation Layer：膨胀层，在以上两层地图上进行膨胀（向外扩张），以避免机器人的外壳会撞上障碍物。
- Voxel Layer：跟obstacle_layer基本类似，因为voxel_layer直接继承obstacle_layer类，区别是voxel_layer**用来处理3D障碍物**，多了一个**updateOrigin和clearNonLethal**。这一层具有与障碍物层相同的功能，但voxel_layer在三维空间中跟踪传感器数据。引入的三维像素网格允许更智能地清除障碍物，以反映可以看到的多个高度
- Other Layers：你还可以通过插件的形式自己实现costmap，目前已有`Social Costmap Layer`、`Range Sensor Layer`等开源插件。

可以同时选择多个Layer并存。

1. **global_costmap** 

   全局代价地图是通过膨胀导航堆栈上的地图障碍物来实现的，使用基于map_server初始化代价地图，也就是static map layer（静态地图层）

2. **local_costmap**

   局部代价地图是通过将机器人传感器检测到的障碍物膨胀产生的，基于滚动窗口的代价地图。



- Costmap2DROS类是对整个代价地图内容的封装，向外提供简洁的接口

  ```
  void start();#订阅传感器话题，启动代价地图更新
  void stop();#停止代价地图更新，并停止订阅传感器话题
  void pause();#暂停代价地图的更新，但是不会关闭传感器话题的订阅
  void resume();#恢复代价地图更新
  void resetLayers();#重置每一个代价地图层
  ```

- LayeredCostmap类是Costmap2DROS的类成员，它是“主地图”，也能够管理各层地图，因为它含有指向各层子地图的指针，能够调用子地图的类方法，开启子地图的更新。并且，各层子地图最后都会合并到主地图上，提供给规划器的使用。它含有Costmap2D类成员，这个类就是底层地图，用于记录地图数据。

- CostmapLayer类派生自Layer类和Costmap2D类。Layer类中含有子地图层用到的一些函数，如更新size、更新bound、和主地图合并等；Costmap2D类存储该层维护的地图数据。由CostmapLayer类派生出StaticLayer类和ObstacleLayer类，即静态层和障碍层，前者获取静态地图，后者通过传感器数据不断更新，获得能反映障碍物信息的子地图。

- 由Layer类单独派生出InflationLayer类，即膨胀层，用它来反映障碍物在地图上向周边的膨胀。由于它的父类中不含Costmap2D类，所以其实膨胀层自身没有栅格地图要维护，这一点和另外两层有区别



#### map / 锁存

地图在ROS中是以Topic的形式维护和呈现的，这个Topic名称就叫做`/map`，它的消息类型是`nav_msgs/OccupancyGrid`。

通常我们是在launch文件中加载map_server，发布地图。而map_server发布的消息包括：

- /map_metadata: 发布地图的描述信息
- /map: 发布锁存的地图消息

由于`/map`中实际上存储的是一张图片，为了减少不必要的开销，这个Topic往往采用锁存（latched）的方式来发布。什么是锁存？其实就是：地图如果没有更新，就维持着上次发布的内容不变，此时如果有新的订阅者订阅消息，这时只会收到一个`/map`的消息，也就是上次发布的消息；只有地图更新了（比如SLAM又建出来新的地图），这时`/map`才会发布新的内容。
锁存器的作用就是，将发布者最后一次发布的消息保存下来，然后把它自动发送给后来的订阅者。这种方式非常适合变动较慢、相对固定的数据（例如地图），然后只发布一次，相比于同样的消息不定的发布，锁存的方式既可以减少通信中对带宽的占用，也可以减少消息资源维护的开销。

#### 启动navigation

1. **/amcl**

packages：navigation/amcl

2. **/laser_filter**

packages：turtlebot_navigation/laser_footprint_filter.cpp

3. **/map_server**

packages：navigation/map_server

4. **/move_base**

packages：navigation/move_base

**订阅topic：**

- move_base_simple/goal  （geometry_msgs/PoseStamped）



**发布topic：**

- cmd_vel （geometry_msgs/Twist）

启动时被重定向到navigation_velocity_smoother/raw_cmd_vel，也就是转发给navigation_velocity_smoother

​    `<remap from="cmd_vel" to="navigation_velocity_smoother/raw_cmd_vel"/>`

5. **/navigation_velocity_smoother （nodelet/nodelet）**

package：yocs_velocity_smoother/VelocitySmootherNodelet

如果一个节点发布的速度指令不能保证其平滑度，在节点和cmd_vel_mux之间增加这个平滑器

**订阅topic：**

1. ~/raw_cmd_vel （geometry_msgs / Twist）

要平滑的输入速度

2. ~/robot_cmd_vel （geometry_msgs / Twist）

比较输出速度命令和最终机器人运行的速度命令，以确保我们不会在速度曲线中创建非常大的跳跃

启动时被重定向到mobile_base/commands/velocity，也就是从mobile_base/commands/velocity话题接收速度消息

`<remap from="navigation_velocity_smoother/robot_cmd_vel" to="mobile_base/commands/velocity"/>`

3. ~/odometry （nav_msgs /Odometry ）

将输出速度命令与测得的速度进行比较，以确保我们不会在速度曲线中产生非常大的跳跃。

启动时被重定向到odom，也就是从odom话题接收消息

`<remap from="navigation_velocity_smoother/odometry" to="odom"/>`

**发布topic：**

- navigation_velecity_smoother/smooth_cmd_vel

启动时被重定向到cmd_vel_mux/input/navi，也就是转发给了cmd_vel_mux节点

`<remap from="navigation_velocity_smoother/smooth_cmd_vel" to="cmd_vel_mux/input/navi"/>`



6. **/kobuki_safety_controller （nodelet/nodelet）**

package：kobuki_safety_controller/SafetyControllerNodelet

监控机器人的保险杠（bumper）、悬崖（cliff）和落轮（wheel drop）传感器和相应的行为，使用此控制器可以实现我们自己的控制器。

触发保险杠和悬崖传感器时会导致kobuki后退，触发落轮传感器时会使kobuki的轮子立马停止转动。



#### topic list

1. /amcl/parameter_descriptions

2. /amcl/parameter_updates

3. /amcl_pose

4. /diagnostics

5. /initialpose

6. /map

7. /map_metadata

8. /move_base/current_goal

9. /move_base/goal

10. /move_base/recovery_status

11. /move_base_simple/goal

12. /navigation_velocity_smoother/raw_cmd_vel（geometry_msgs / Twist）

    yocs_velocity_smoother要平滑的输入速度

13. /particlecloud

14. /scan

15. /scan_filtered

16. /tf

17. /tf_static



