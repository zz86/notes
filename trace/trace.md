1. **克隆代码**

   git下来含有span context的common_msg以及测试用例的代码

   ```
   git clone -b opentracingDEMO https://gitee.com/se_lab/food_delivery_ws.git
   ```

2. **编译安装`opentracing `和`zipkin`，源码在Demo中**

   [opentracing-cpp](https://github.com/opentracing/opentracing-cpp.git)

   [zipkin-cpp-opentracing](https://github.com/rnburn/zipkin-cpp-opentracing.git)

   ```shell
   以下例子为opentracing-cpp的源码安装，zipkin-cpp-opentracing同理
   cd Demo/opentracing-cpp-master
   mkdir build
   cd build
   cmake ..
   make 
   sudo make install 
   ```

3. **编译msg**

   编译`common_msg_ws`（含有geometry_msgs等消息），进入`common_msg_ws`然后`catkin_make`即可

4. **修改md5sum**

   - 修改`common_msg_ws/devel/include/geometry_msgs/`目录下的`PoseStamped.h、PoseWithCovarianceStamped.h、Twist.h`文件中md5sum的值，相应的值为`/opt/ros/melodic/include/geometry_msgs/`目录下的对应文件中的md5sum的值，也就是将前者文件中的md5sum改为后者

   - 同理`common_msg_ws/devel/lib/python2.7/dist-packages/geometry_msgs/msg/`目录下的`PoseStamped.py、PoseWithCovarianceStamped.py、Twist.py`也需要修改，对应文件为`/opt/ros/melodic/lib/python2.7/dist-packages/geometry_msgs/msg/`目录下的同名文件。

5. **替换msg编译后的.h头文件和py文件**

   - 可提前备份接下来将被替换的两个文件夹

   - 将`common_msg_ws/devel/include/geometry_msgs/`整体复制到`/opt/ros/melodic/include/geometry_msgs/`

   - 将`common_msg_ws/devel/lib/python2.7/dist-packages/geometry_msgs/`整体复制到`/opt/ros/melodic/lib/python2.7/dist-packages/geometry_msgs/`

6. **编译`food_delivery_ws`和`navigation_ws`**工作空间

   - 方法同`common_msg_ws`

   - `food_delivery_ws`：turtlebot + web_app

   - `navigation_ws`：move_base、amcl、map_server、costmap2d、global planner、local planner等导航相关功能包

7. **添加环境变量**

   在~/.bashrc中增加以下两条内容

   ```shell
   source ~/food_delivery_ws/food_delivery_ws/devel/setup.bash
   source ~/food_delivery_ws/navigation_ws/devel/setup.bash
   ```

   

8. **启动`turtlebot`仿真和`move_base`**

   - `roslaunch turtlebot_gazebo turtlebot_world.launch `
   - `roslaunch turtlebot_navigation rplidar_amcl_gazebo.launch`

9. **开启zipkin服务端**

   ```
   cd Demo
   java -jar zipkin-server-2.23.16-exec.jar
   ```

10. **浏览器打开zipkin主页面，http://127.0.0.1:9411/**

11. **运行测试用例**

    - 测试用例为`cpp_pub_nav/src/CPP_pub_nav/build/test.py`

    ```
    python test.py
    ```

12. **在zipkin主页面观察trace结果**



**注意事项**：

- 节点间trace时不应该使用方法和参数传递

- 打trace时应该以bug的根因为准



