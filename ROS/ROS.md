
# ROS
ROS本身并不是一个操作系统，而是可以安装在现在已有的操作系统上（Linux、Windows、Mac）上的**软件库和工具集**

#### metapackages

- Metapackage是ROS中的特殊的package，他们不包含任何的安装文件，源代码文件，但是它依赖了其他的软件包，通过这种方法可以把其他包组合起来，我们可以认为它是一本书的目录索引，告诉我们这个包集合中有哪些子包，并且该去哪里下载。

#### topic

- 分类：全局，相对，私有

- c++实现

  - 全局名称：格式:以/开头的名称，和节点名称无关，(话题参考ROS系统，与节点命名空间平级)

  - 相对名称：格式:非/开头的名称,参考命名空间(与节点名称平级)来确定话题名称，(话题参考的是节点的命名空间，与节点名称平级)

  - 私有名称：格式:以~开头的名称，(话题参考节点名称，是节点名称的子级)

    ```c++
    ros::NodeHandle nh("~"); //需要创建不同的NodeHandle
    ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",1000);
    ```

    **结果:**`/xxx/hello/chatter`

- python实现
  - 全局名称
    格式:以/开头的名称，和节点名称无关
  - 相对名称
    格式:非/开头的名称,参考命名空间(与节点名称平级)来确定话题名称
  - 私有名称
    格式:以~开头的名称

#### param

- 分类：全局，相对，私有

- 如何设置参数

  - rosrun 在启动节点时，可以设置参数:

    语法: rosrun 包名 节点名称 _参数名:=参数值

  - 可以在 node 标签外或 node 标签中通过 param 或 rosparam 来设置参数。在 node 标签外设置的参数是全局性质的，参考的是 / ，在 node 标签中设置的参数是私有性质的，参考的是 /命名空间/节点名称。

  - 编码的方式可以更方便的设置:全局、相对与私有参数

    - 在 C++  中，可以使用 ros::param 或者 ros::NodeHandle 来设置参数

      1. ```
         ros::param::set("/set_A",100); //全局,和命名空间以及节点名称无关
         ros::param::set("set_B",100); //相对,参考命名空间
         ros::param::set("~set_C",100); //私有,参考命名空间与节点名称
         ```

      2. ```cpp
         ros::NodeHandle nh;
         nh.setParam("/nh_A",100); //全局,和命名空间以及节点名称无关
         
         nh.setParam("nh_B",100); //相对,参考命名空间
         
         ros::NodeHandle nh_private("~");
         nh_private.setParam("nh_C",100);//私有,参考命名空间与节点名称
         ```

- - - python实现

      ```py
      rospy.set_param("/py_A",100)  #全局,和命名空间以及节点名称无关
      rospy.set_param("py_B",100)  #相对,参考命名空间
      rospy.set_param("~py_C",100)  #私有,参考命名空间与节点名称
      ```

#### launch文件

- luanch标签
  - deprecated=“弃用声明”：告知用户当前launch文件已经弃用，在执行的时候提示警告信息
- node标签（roslaunch命令不能保证按照node的声明顺序启动节点，节点的启动是多进程的 ）
  - pkg：功能包
  - type：节点类型，与之相同名称的可执行文件
  - name：节点名字
  - args：将参数传递给节点
  - machine：在指定机器上启动节点
  - respawn=“true｜false”：如果节点退出，是否重启
  - respawn_delay="N"：如果respawn为true，那么节点退出后延迟N秒重启节点
  - required=“true｜false”：该节点是否为必须，如果required为true，那么如果节点退出，则关闭整个系统
  - ns=“xxx”：在指定命名空间xxx内启动节点
  - clear_params="true｜false"：在启动节点前，删除节点的私有空间的参数
  - output=“log｜screen”：日志发送目标，可以设置为log日志文件，或screen屏幕，默认是log
  - 子集标签：
    - env：环境变量设置
    - remap：重映射节点名字
    - rosparam：参数设置
    - param：参数设置
- include标签：用于将另一个 xml 格式的 launch 文件导入到当前文件
  - file="$(find 包名)/xxx/xxx.launch"：要包含的文件路径
  - ns=“xxx” (可选)：在指定命名空间导入文件
  - 子集标签：
    - env 环境变量设置
    - arg 将参数传递给被包含的文件

- remap标签：用于话题重命名
  - from="xxx"：原始话题名称
  - to="yyy"：目标名称

- param标签：主要用于在参数服务器上设置参数，参数源可以在标签中通过 value 指定，也可以通过外部文件加载，在`<node>`标签中时，相当于私有命名空间。
  - name="命名空间/参数名"：参数名称，可以包含命名空间
  - value="xxx" (可选)：定义参数值，如果此处省略，必须指定外部文件作为参数源
  - type="str | int | double | bool | yaml" (可选)：指定参数类型，如果未指定，roslaunch 会尝试确定参数类型，规则如下:
    - 如果包含 '.' 的数字解析未浮点型，否则为整型
    - "true" 和 "false" 是 bool 值(不区分大小写)
    - 其他是字符串

- rosparam标签：从 YAML 文件导入参数，或将参数导出到 YAML 文件，也可以用来删除参数，`<rosparam>`标签在`<node>`标签中时被视为私有。

  - command="load | dump | delete" (可选，默认 load)

    加载、导出或删除参数

  - file="$(find xxxxx)/xxx/yyy…."

    加载或导出到的 yaml 文件

  - param="参数名称"

  - ns="命名空间" (可选)

-  group标签：对节点分组，具有 ns 属性，可以让节点归属某个命名空间

  - ns="名称空间" (可选)

  - clear_params="true | false" (可选)

    启动前，是否删除组名称空间的所有参数(慎用….此功能危险)

  - 子级标签
    - 除了launch 标签外的其他标签

- arg标签：用于动态传参，类似于函数的参数，可以增强launch文件的灵活性

  - name="参数名称"

  - default="默认值" (可选)

  - value="数值" (可选)

    不可以与 default 并存

  - doc="描述"

    参数说明

#### 工作空间覆盖

- ROS 会解析 .bashrc 文件，并生成 ROS_PACKAGE_PATH ROS包路径，该变量中按照 .bashrc 中配置设置工作空间优先级，在设置时需要遵循一定的原则:ROS_PACKAGE_PATH 中的值，和 .bashrc 的配置顺序相反—>后配置的优先级更高，如果更改自定义空间A与自定义空间B的source顺序，那么调用时，将进入工作空间A。
- 功能包重名时，会按照 ROS_PACKAGE_PATH 查找，配置在前的会优先执行。
- BUG：当在 .bashrc 文件中 source 多个工作空间后，可能出现的情况，在 ROS PACKAGE PATH 中只包含两个工作空间，可以删除自定义工作空间的 build 与 devel 目录，重新 catkin_make，然后重新载入 .bashrc 文件，问题解决。

#### topic重名

- 解决方案：使用命名空间或名称重映射
- 命名空间就是为名称添加前缀，名称重映射是为名称起别名。两种策略的实现途径有多种:
  - rosrun 命令：`__ns:="xxx" `  `__name:="xxx"`
  - launch 文件：ns属性  name属性
  - 编码实现：rospy.init_node("lisi",anonymous=True)会在节点名称后缀时间戳

#### TF坐标变换

- 作用：在 ROS 中用于实现不同坐标系之间的点或向量的转换。

- TF2和TF对比

  - TF2已经替换了TF，TF2是TF的超集，建议学习 TF2 而非 TF
  - TF2 功能包的增强了内聚性，TF 与 TF2 所依赖的功能包是不同的，TF 对应的是`tf`包，TF2 对应的是`tf2`和`tf2_ros`包，在 TF2 中不同类型的 API 实现做了分包处理。
  - TF2 实现效率更高，比如在:TF2 的静态坐标实现、TF2 坐标变换监听器中的 Buffer 实现等

- 在ROS中坐标变换最初对应的是tf，不过在 hydro 版本开始, tf 被弃用，迁移到 tf2,后者更为简洁高效，tf2对应的常用功能包有:

  tf2_geometry_msgs:可以将ROS消息转换成tf2消息。

  tf2: 封装了坐标变换的常用消息。

  tf2_ros:为tf2提供了roscpp和rospy绑定，封装了坐标变换常用的API。

- 在坐标转换实现中常用的 msg:`geometry_msgs/TransformStamped`和`geometry_msgs/PointStamped`

  前者用于传输坐标系相关位置信息，后者用于传输某个坐标系内坐标点的信息

  - geometry_msgs/TransformStamped

```
std_msgs/Header header                     #头信息
  uint32 seq                                #|-- 序列号
  time stamp                                #|-- 时间戳
  string frame_id                            #|-- 坐标 ID
string child_frame_id                    #子坐标系的 id
geometry_msgs/Transform transform        #坐标信息
  geometry_msgs/Vector3 translation        #偏移量
    float64 x                                #|-- X 方向的偏移量
    float64 y                                #|-- Y 方向的偏移量
    float64 z                                #|-- Z 方向上的偏移量
  geometry_msgs/Quaternion rotation        #四元数
    float64 x                                
    float64 y                                
    float64 z                                
    float64 w
```

- - geometry_msgs/PointStamped

```
std_msgs/Header header                    #头
  uint32 seq                                #|-- 序号
  time stamp                                #|-- 时间戳
  string frame_id                            #|-- 所属坐标系的 id
geometry_msgs/Point point                #点坐标
  float64 x                                    #|-- x y z 坐标
  float64 y
  float64 z
```

- 静态坐标变换

  - static_transform_publisher静态坐标变换发布节点

  - TF2 版静态坐标变换：rosrun tf2_ros static_transform_publisher x偏移量 y偏移量 z偏移量 z偏航角度 y俯仰角度 x翻滚角度 父级坐标系 子级坐标系

  - TF 版静态坐标变换：rosrun tf static_transform_publisher x偏移量 y偏移量 z偏移量 z偏航角度 y俯仰角度 x翻滚角度 父级坐标系 子级坐标系 发布频率

  - TF 版本的启动中最后多一个参数，该参数是指定发布频率

  - 使用`rostopic`查看话题，包含`/tf`与`/tf_static`, 前者是 TF 发布的话题，后者是 TF2 发布的话题，分别调用命令打印二者的话题消息

    `rostopic echo /tf`: 当前会循环输出坐标系信息

    `rostopic echo /tf_static`: 坐标系信息只有一次

- 动态坐标变换

- 多坐标变换

#### 机器人系统仿真

- 在 ROS 中，仿真实现涉及的内容主要有三:对机器人建模(URDF)、创建仿真环境(Gazebo)以及感知环境(Rviz)等系统性实现。

- Unified Robot Description Format 的首字母缩写，直译为**统一(标准化)机器人描述格式**，可以以一种 XML 的方式描述机器人的部分结构，比如底盘、摄像头、激光雷达、机械臂以及不同关节的自由度…..,该文件可以被 C++ 内置的解释器转换成可视化的机器人模型，是 ROS 中实现机器人仿真的重要组件。
- RViz 是 ROS Visualization Tool 的首字母缩写，直译为**ROS的三维可视化工具**。它的主要目的是以三维方式显示ROS消息，可以将 数据进行可视化表达。例如:可以显示机器人模型，可以无需编程就能表达激光测距仪（LRF）传感器中的传感 器到障碍物的距离，RealSense、Kinect或Xtion等三维距离传感器的点云数据（PCD， Point Cloud Data），从相机获取的图像值等。
- Gazebo是一款3D动态模拟器，用于显示机器人模型并创建仿真环境,能够在复杂的室内和室外环境中准确有效地模拟机器人。与游戏引擎提供高保真度的视觉模拟类似，Gazebo提供高保真度的物理模拟，其提供一整套传感器模型，以及对用户和程序非常友好的交互方式。

- URDF

  - robot 根标签，类似于 launch文件中的launch标签

    - 属性

      name: 指定机器人模型的名称

  - link 连杆标签

    - 属性
      name —> 为连杆命名

    - 子标签
      visual —> 描述外观(对应的数据是可视的)

      geometry 设置连杆的形状

      ​	标签1: box(盒状)

      属性:size=长(x) 宽(y) 高(z)
      	标签2: cylinder(圆柱)

      属性:radius=半径 length=高度
      	标签3: sphere(球体)

      属性:radius=半径
      	标签4: mesh(为连杆添加皮肤)

      属性: filename=资源路径(格式：package://<packagename>/<path>/文件)
      origin 设置偏移量与倾斜弧度

      属性1: xyz=x偏移 y便宜 z偏移

      属性2: rpy=x翻滚 y俯仰 z偏航 (单位是弧度)

      metrial 设置材料属性(颜色)

      属性: name

      ​	标签: color

      属性: rgba=红绿蓝权重值与透明度 (每个权重值以及透明度取值[0,1])
      collision —> 连杆的碰撞属性

      Inertial —> 连杆的惯性矩阵

  - joint 关节标签

    - 属性

      name —> 为关节命名

      type —> 关节运动形式

      ​	continuous: 旋转关节，可以绕单轴无限旋转

      ​	revolute: 旋转关节，类似于 continues,但是有旋转角度限制

      ​	prismatic: 滑动关节，沿某一轴线移动的关节，有位置极限

      ​	planer: 平面关节，允许在平面正交方向上平移或旋转

      ​	floating: 浮动关节，允许进行平移、旋转运动

      ​	fixed: 固定关节，不允许运动的特殊关节

    - 子标签
      parent(必需的)

      parent link的名字是一个强制的属性：

      ​	link:父级连杆的名字，是这个link在机器人结构树中的名字。
      child(必需的)

      child link的名字是一个强制的属性：

      ​	link:子级连杆的名字，是这个link在机器人结构树中的名字。
      origin

      ​	属性: xyz=各轴线上的偏移量 rpy=各轴线上的偏移弧度。
      axis

      ​	属性: xyz用于设置围绕哪个关节轴运动

  - gazebo 集成gazebo需要使用的标签

- 在 ROS 中，提供了一些工具来方便 URDF 文件的编写，比如:
  - `check_urdf`命令可以检查复杂的 urdf 文件是否存在语法问题
  - `urdf_to_graphiz`命令可以查看 urdf 模型结构，显示不同 link 的层级关系

- xacro

  - Xacro 是 XML Macros 的缩写，Xacro 是一种 XML 宏语言，是可编程的 XML

  - 命令行进入 xacro文件 所属目录，执行:`rosrun xacro xacro xxx.xacro > xxx.urdf`, 会将 xacro 文件解析为 urdf 文件

  - #### 集成launch文件

    **方式1:**先将 xacro 文件转换出 urdf 文件，然后集成

    先将 xacro 文件解析成 urdf 文件:`rosrun xacro xacro xxx.xacro > xxx.urdf`然后再按照之前的集成方式直接整合 launch 文件

    **方式2:**在 launch 文件中直接加载 xacro(**建议使用**)

    核心代码:

    ```xml
    <param name="robot_description" command="$(find xacro)/xacro $(find demo01_urdf_helloworld)/urdf/xacro/my_base.urdf.xacro" />
    ```

    加载`robot_description`时使用`command`属性，属性值就是调用 xacro 功能包的 xacro 程序直接解析 xacro 文件

  - #### 1.属性与算数运算

    用于封装 URDF 中的一些字段，比如: PAI 值，小车的尺寸，轮子半径 ….

    **属性定义**

    ```xml
    <xacro:property name="xxxx" value="yyyy" />
    ```

    **属性调用**

    ```
    ${属性名称}
    ```

    **算数运算**

    ```
    ${数学表达式}
    ```

    #### 2.宏

    类似于函数实现，提高代码复用率，优化代码结构，提高安全性

    **宏定义**

    ```xml
    <xacro:macro name="宏名称" params="参数列表(多参数之间使用空格分隔)">
    
        .....
    
        参数调用格式: ${参数名}
    
    </xacro:macro>
    ```

    **宏调用**

    ```xml
    <xacro:宏名称 参数1=xxx 参数2=xxx/>
    ```

    #### 3.文件包含

    机器人由多部件组成，不同部件可能封装为单独的 xacro 文件，最后再将不同的文件集成，组合为完整机器人，可以使用文件包含实现

    **文件包含**

    ```xml
    <robot name="xxx" xmlns:xacro="http://wiki.ros.org/xacro">
          <xacro:include filename="my_base.xacro" />
          <xacro:include filename="my_camera.xacro" />
          <xacro:include filename="my_laser.xacro" />
          ....
    </robot>
    ```

- **Arbotix:**Arbotix 是一款控制电机、舵机的控制板，**并提供相应的 ros 功能包**，这个功能包的功能不仅可以驱动真实的 Arbotix 控制板，它还提供一个差速控制器，通过接受速度控制指令更新机器人的 joint 状态，从而帮助我们实现机器人在 rviz 中的运动。

  这个差速控制器在 arbotix_python 程序包中，完整的 arbotix 程序包还包括多种控制器，分别对应 dynamixel 电机、多关节机械臂以及不同形状的夹持器。

- gazebo

  - 当 URDF 需要与 Gazebo 集成时，和 Rviz 有明显区别:

    1.必须使用 collision 标签，因为既然是仿真环境，那么必然涉及到碰撞检测，collision 提供碰撞检测的依据。

    2.必须使用 inertial 标签，此标签标注了当前机器人某个刚体部分的惯性矩阵，用于一些力学相关的仿真计算。

    

    3.颜色设置，也需要重新使用 gazebo 标签标注，因为之前的颜色设置为了方便调试包含透明度，仿真环境下没有此选项。

  - 较之于 rviz，gazebo在集成 URDF 时，需要做些许修改，比如:必须添加 collision 碰撞属性相关参数、必须添加 inertial 惯性矩阵相关参数，另外，如果直接移植 Rviz 中机器人的颜色设置是没有显示的，颜色设置也必须做相应的变更。

    #### 1.collision

    如果机器人link是标准的几何体形状，和link的 visual 属性设置一致即可。

    #### 2.inertial

    惯性矩阵的设置需要结合link的质量与外形参数动态生成，标准的球体、圆柱与立方体的惯性矩阵公式如下(已经封装为 xacro 实现):

    球体惯性矩阵

    ```xml
    <!-- Macro for inertia matrix -->
        <xacro:macro name="sphere_inertial_matrix" params="m r">
            <inertial>
                <mass value="${m}" />
                <inertia ixx="${2*m*r*r/5}" ixy="0" ixz="0"
                    iyy="${2*m*r*r/5}" iyz="0" 
                    izz="${2*m*r*r/5}" />
            </inertial>
        </xacro:macro>
    ```

    圆柱惯性矩阵

    ```xml
    <xacro:macro name="cylinder_inertial_matrix" params="m r h">
            <inertial>
                <mass value="${m}" />
                <inertia ixx="${m*(3*r*r+h*h)/12}" ixy = "0" ixz = "0"
                    iyy="${m*(3*r*r+h*h)/12}" iyz = "0"
                    izz="${m*r*r/2}" /> 
            </inertial>
        </xacro:macro>
    ```

    立方体惯性矩阵

    ```xml
     <xacro:macro name="Box_inertial_matrix" params="m l w h">
           <inertial>
                   <mass value="${m}" />
                   <inertia ixx="${m*(h*h + l*l)/12}" ixy = "0" ixz = "0"
                       iyy="${m*(w*w + l*l)/12}" iyz= "0"
                       izz="${m*(w*w + h*h)/12}" />
           </inertial>
       </xacro:macro>
    ```

    需要注意的是，原则上，除了 base_footprint 外，机器人的每个刚体部分都需要设置惯性矩阵，且惯性矩阵必须经计算得出，如果随意定义刚体部分的惯性矩阵，那么可能会导致机器人在 Gazebo 中出现抖动，移动等现象。

    #### 3.颜色设置

    在 gazebo 中显示 link 的颜色，必须要使用指定的标签:

    ```xml
    <gazebo reference="link节点名称">
         <material>Gazebo/Blue</material>
    </gazebo>
    ```

    **PS：**material 标签中，设置的值区分大小写，颜色可以设置为 Red Blue Green Black …..

- gazebo 中已经可以正常显示机器人模型了，那么如何像在 rviz 中一样控制机器人运动呢？在此，需要涉及到ros中的组件: ros_control。

  #### 1.ros_control 简介

  **场景:**同一套 ROS 程序，如何部署在不同的机器人系统上，比如：开发阶段为了提高效率是在仿真平台上测试的，部署时又有不同的实体机器人平台，不同平台的实现是有差异的，如何保证 ROS 程序的可移植性？ROS 内置的解决方式是 ros_control。

  **ros_control:**是一组软件包，它包含了控制器接口，控制器管理器，传输和硬件接口。ros_control 是一套机器人控制的中间件，是一套规范，不同的机器人平台只要按照这套规范实现，那么就可以保证 与ROS 程序兼容，通过这套规范，实现了一种可插拔的架构设计，大大提高了程序设计的效率与灵活性。

  gazebo 已经实现了 ros_control 的相关接口，如果需要在 gazebo 中控制机器人运动，直接调用相关接口即可

- 本章主要介绍了ROS中仿真实现涉及的三大知识点:

  - URDF(Xacro)
  - Rviz
  - Gazebo

  URDF 是用于描述机器人模型的 xml 文件，可以使用不同的标签具代表不同含义，URDF 编写机器人模型代码冗余，xacro 可以优化 URDF 实现，代码实现更为精简、高效、易读。容易混淆的是Rviz与Gazebo，在此我们着重比较以下二者的区别:

  > rviz是**三维可视化工具**，强调把已有的数据可视化显示；
  >
  > gazebo是**三维物理仿真平台**，强调的是创建一个虚拟的仿真环境。
  >
  > rviz需要**已有数据**。
  >
  > rviz提供了很多插件，这些插件可以显示图像、模型、路径等信息，但是前提都是这些数据已经以话题、参数的形式发布，rviz做的事情就是订阅这些数据，并完成可视化的渲染，让开发者更容易理解数据的意义。
  >
  > gazebo不是显示工具，强调的是仿真，**它不需要数据，而是创造数据**

#### 导航

- 总结下来，涉及的关键技术有如下五点:

  1. 全局地图
  2. 自身定位
  3. 路径规划
  4. 运动控制
  5. 环境感知

- 定位实现
  - 通过里程计定位:时时收集机器人的速度信息计算并发布机器人坐标系与父级参考系的相对关系。
  - 通过传感器定位:通过传感器收集外界环境信息通过匹配计算并发布机器人坐标系与父级参考系的相对关系。

- 两种定位方式都有各自的优缺点。

  里程计定位:

  - 优点:里程计定位信息是连续的，没有离散的跳跃。
  - 缺点:里程计存在累计误差，不利于长距离或长期定位。

  传感器定位:

  - 优点:比里程计定位更精准；
  - 缺点:传感器定位会出现跳变的情况，且传感器定位在标志物较少的环境下，其定位精度会大打折扣。

  两种定位方式优缺点互补，应用时一般二者结合使用。

- 坐标系变换
  上述两种定位实现中，机器人坐标系一般使用机器人模型中的根坐标系(base_link 或 base_footprint)，里程计定位时，父级坐标系一般称之为 odom，如果通过传感器定位，父级参考系一般称之为 map。当二者结合使用时，map 和 odom 都是机器人模型根坐标系的父级，这是不符合坐标变换中"单继承"的原则的，所以，一般会将转换关系设置为: map -> doom -> base_link 或 base_footprint。

- 地图服务

  - xxx.yaml 保存的是地图的元数据信息，用于描述图片，内容格式如下:

    ```yaml
    image: /home/rosmelodic/ws02_nav/src/mycar_nav/map/nav.pgm
    resolution: 0.050000
    origin: [-50.000000, -50.000000, 0.000000]
    negate: 0
    occupied_thresh: 0.65
    free_thresh: 0.196
    ```

    解释:

    - **image**:被描述的图片资源路径，可以是绝对路径也可以是相对路径。
    - **resolution**: 图片分片率(单位: m/像素)。
    - **origin**: 地图中左下像素的二维姿势，为（x，y，偏航），偏航为逆时针旋转（偏航= 0表示无旋转）。
    - **occupied_thresh**: 占用概率大于此阈值的像素被视为完全占用。
    - **free_thresh**: 占用率小于此阈值的像素被视为完全空闲。
    - **negate**: 是否应该颠倒白色/黑色自由/占用的语义。

    map_server 中障碍物计算规则:

    1. 地图中的每一个像素取值在 [0,255] 之间，白色为 255，黑色为 0，该值设为 x；
    2. map_server 会将像素值作为判断是否是障碍物的依据，首先计算比例: p = (255 – x) / 255.0，白色为0，黑色为1(negate为true，则p = x / 255.0)；
    3. 根据步骤2计算的比例判断是否是障碍物，如果 p > occupied_thresh 那么视为障碍物，如果 p < free_thresh 那么视为无物。

- 代价地图

  - 代价地图有两张:global_costmap(全局代价地图) 和 local_costmap(本地代价地图)，前者用于全局路径规划，后者用于本地路径规划。

    两张代价地图都可以多层叠加,一般有以下层级:

    - Static Map Layer：静态地图层，SLAM构建的静态地图。
    - Obstacle Map Layer：障碍地图层，传感器感知的障碍物信息。
    - Inflation Layer：膨胀层，在以上两层地图上进行膨胀（向外扩张），以避免机器人的外壳会撞上障碍物。
    - Other Layers：自定义costmap。

    多个layer可以按需自由搭配。

#### Action

![10.1 Action 通信](http://www.wenjiangs.com/wp-content/uploads/2021/docimg27/575-hvjtg5asof4.png)

- goal:目标任务;
- cacel:取消任务;
- status:服务端状态;
- result:最终执行结果(只会发布一次);
- feedback:连续反馈(可以发布多次)。

- action 文件内容组成分为三部分:请求目标值、最终响应结果、连续反馈，三者之间使用`---`分割
- action基于topic实现

#### 动态参数

- 一种可以在运行时更新参数而无需重启节点的参数配置策略。

#### pluginlib插件

- **pluginlib**是一个c++库， 用来从一个ROS功能包中加载和卸载插件(plugin)。插件是指从运行时库中动态加载的类。通过使用Pluginlib，不必将某个应用程序显式地链接到包含某个类的库，Pluginlib可以随时打开包含类的库，而不需要应用程序事先知道包含类定义的库或者头文件。

- 实现流程
  1. 准备；
  2. 创建基类；
  3. 创建插件类；
  4. 注册插件;
  5. 构建插件库;
  6. 使插件可用于ROS工具链;
     - 配置xml
     - 导出插件
  7. 使用插件;
  8. 执行

#### nodelet

- 通过Nodelet可以将多个节点集成进一个进程。

- nodelet软件包旨在提供在同一进程中运行多个算法(节点)的方式，不同算法之间通过传递指向数据的指针来代替了数据本身的传输(类似于编程传值与传址的区别)，从而实现零成本的数据拷贝。

  nodelet功能包的核心实现也是插件，是对插件的进一步封装:

  - 不同算法被封装进插件类，可以像单独的节点一样运行；
  - 在该功能包中提供插件类实现的基类:Nodelet；
  - 并且提供了加载插件类的类加载器:NodeletLoader。

- 应用于大容量数据传输的场景，提高节点间的数据交互效率，避免延时与阻塞

- nodelet 基本使用语法

  - ```
    nodelet load pkg/Type manager - Launch a nodelet of type pkg/Type on manager manager
    nodelet standalone pkg/Type   - Launch a nodelet of type pkg/Type in a standalone node
    nodelet unload name manager   - Unload a nodelet a nodelet by name from manager
    nodelet manager               - Launch a nodelet manager node
    ```

- 实现流程
  1. 准备；
  2. 创建插件类并注册插件;
  3. 构建插件库;
  4. 使插件可用于ROS工具链；
  5. 执行。
