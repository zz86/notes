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
   - PoseStamped： d3812c3cbc69362b77dc0b19b345f8f5
   - PoseWithCovarianceStamped： 953b798c0f514ff060a53a3498ce6246
   - Twist： 9f195f881246fdfa2798d1d3eebca84a
   - nav_msgs/Odometry：9c9f4ffc7539a229fcf1a9ab5f4c3813

5. **替换msg编译后的.h头文件和py文件**

   - 可提前备份接下来将被替换的两个文件夹

   - 将`common_msg_ws/devel/include/geometry_msgs/`整体复制到`/opt/ros/melodic/include/geometry_msgs/`

   - 将`common_msg_ws/devel/lib/python2.7/dist-packages/geometry_msgs/`整体复制到`/opt/ros/melodic/lib/python2.7/dist-packages/geometry_msgs/`

6. **编译`food_delivery_ws`和`navigation_ws`**工作空间

   - 方法同`common_msg_ws`

   - `food_delivery_ws`：turtlebot + web_app

   - `navigation_ws`：move_base、amcl、map_server、costmap2d、global planner、local planner等导航相关功能包

6. **添加环境变量**

   在~/.bashrc中增加以下两条内容

   ```shell
   source ~/food_delivery_ws/food_delivery_ws/devel/setup.bash
   source ~/food_delivery_ws/navigation_ws/devel/setup.bash
   ```

   

7. **启动`turtlebot`仿真和`move_base`**

   - `roslaunch turtlebot_gazebo turtlebot_world.launch `
   - `roslaunch turtlebot_navigation rplidar_amcl_gazebo.launch`

8. **开启zipkin服务端**

   ```
   cd Demo
   java -jar zipkin-server-2.23.16-exec.jar
   ```

9. **浏览器打开zipkin主页面，http://127.0.0.1:9411/**

10. **运行测试用例**

    - 测试用例为`cpp_pub_nav/src/CPP_pub_nav/build/test.py`

    ```
    python test.py
    ```

11. **在zipkin主页面观察trace结果**



**注意事项**：

- 节点间trace时不应该使用方法和参数传递

- 打trace时应该以bug的根因为准



#### 如何trace埋点？(c++)

1. 添加头文件以及命名空间

```c++
#include "text_map_carrier.h"
```

1. 初始化一个tracer `opentracing::v3::Tracer`，Tracer是用来管理Span的统筹者，负责创建span和传播span。

```c++
    ZipkinOtTracerOptions options;
    options.service_name = "tracer_name";
    auto tracer = makeZipkinOtTracer(options);
    assert(tracer);
```

2. 创建一个root_span（该span没有Parent ID）

```c++
auto span = tracer->StartSpan("span_name");
```

2. 获取父span

- 在ros中，SpanContext通过topic传播，也就是以string的形式存放在msg中，但SpanContext本身是一个类，这就需要将string转换为SpanContext。
- 将一个string转换为*SpanContext*，如果string为空，则返回一个空的SpanContext

```c++
auto str_to_spancontext(auto &tracer, std::string spancontext_str){
    char contxt[MAXLINE];
    strcpy(contxt, spancontext_str.c_str());
    std::unordered_map<std::string, std::string> text_map;
    write_span_context(std::ref(text_map), &contxt[0]);
    TextMapCarrier carrier(text_map);
    auto span_context_maybe = tracer->Extract(carrier); // extraction

    return span_context_maybe;
}

tracer->Extract(carrier)函数的原型是：
virtual opentracing::v3::expected<std::unique_ptr<opentracing::v3::SpanContext> > opentracing::v3::Tracer::Extract(std::istream&)
virtual opentracing::v3::expected<std::unique_ptr<opentracing::v3::SpanContext> > opentracing::v3::Tracer::Extract(const opentracing::v3::TextMapReader&)
virtual opentracing::v3::expected<std::unique_ptr<opentracing::v3::SpanContext> > opentracing::v3::Tracer::Extract(const opentracing::v3::HTTPHeadersReader&)
virtual opentracing::v3::expected<std::unique_ptr<opentracing::v3::SpanContext> > opentracing::v3::Tracer::Extract(const opentracing::v3::CustomCarrierReader&)
```

- 将一个*Span*中的SpanContext转换为string

```c++
std::string span_to_str(auto &tracer, auto &span) {
    std::unordered_map<std::string, std::string> text_map;
    TextMapCarrier carrier(text_map);
    auto err = tracer->Inject(span->context(), carrier); // injection
    std::string span_context_str = read_span_context(text_map);
    
    return span_context_str; 
}

tracer->Inject(span->context(), carrier)函数的原型是:
virtual opentracing::v3::expected<void> opentracing::v3::Tracer::Inject(const opentracing::v3::SpanContext&, std::ostream&)
virtual opentracing::v3::expected<void> opentracing::v3::Tracer::Inject(const opentracing::v3::SpanContext&, const opentracing::v3::TextMapWriter&)
virtual opentracing::v3::expected<void> opentracing::v3::Tracer::Inject(const opentracing::v3::SpanContext&, const opentracing::v3::HTTPHeadersWriter&)
virtual opentracing::v3::expected<void> opentracing::v3::Tracer::Inject(const opentracing::v3::SpanContext&, const opentracing::v3::CustomCarrierWriter&)
```

- 由span获取*SpanContext*

```c++
auto spancontext = &span->context();
```

3. 创建子span

- 从一个SpanContext创建

```c++
auto spancontext = ... //智能指针
auto span = tracer->StartSpan("span_name", {ChildOf(spancontext->get())});
or
auto span = tracer->StartSpan("span_name", {FollowsFrom(spancontext->get())});
//spancontext->get()是智能指针中的get方法

tracer->StartSpan()函数原型是：
std::unique_ptr<opentracing::v3::Span> opentracing::v3::Tracer::StartSpan(opentracing::v3::string_view, std::initializer_list<opentracing::v3::option_wrapper<opentracing::v3::StartSpanOption> >)
```

- 从一个span创建（本质上也是从一个SpanContext创建）

```c++
auto span = tracer->StartSpan("child_span_name", {ChildOf(&parent_span->context())});
or
auto span = tracer->StartSpan("child_span_name", {FollowsFrom(&parent_span->context())});
```

- 注意`span`和`SpanContex`t的区别（两个类）：
  - `span`是`opentracing::v3::Span`
  - `SpanContext`是`opentracing::v3::SpanContext`



4. 为子span添加Log或者Tag（示例）

```c++
span->Log({{"event", "log"}, {"span start", ros::Time::now().toSec()}});
span->SetTag("method", "void MoveBase::executeCb(const move_base_msgs::MoveBaseGoalConstPtr& move_base_goal)");
```

5. 关闭span

```c++
span->Finish();
```

6. 关闭tracer

```c++
tracer->Close();
```

注意事项：

- 对于一个ROS节点而言，节点内部所有线程应该共享一个tracer，tracer_name设置为节点的名字，在节点类的构造函数中初始化tracer，在析构函数中关闭tracer。
- span应该插在节点内部的某个函数或者某个线程中，用完即关闭。





#### trace埋点示例

```c++
    // *** add trace *** //

    auto tracer = init_tracer("MoveBase_loadRecoveryBehaviors");
    auto span_context_maybe = str_to_spancontext(tracer, move_base::span_context);

    auto span = tracer->StartSpan("MoveBase_span", {ChildOf(span_context_maybe->get())});
    span->Log({{"event", "log"}, {"span start", ros::Time::now().toSec()}});
    span->SetTag("method", "bool MoveBase::loadRecoveryBehaviors(ros::NodeHandle node)");

    move_base::curr_context = span_to_str(tracer, span);

    // *** close trace *** //
    span->Finish();
    tracer->Close();
    // ***************** //
```





#### 如何trace埋点？(python2.7使用py_zipkin)

- Start a trace as the root span:

  1. Context manager

     ```python
     from py_zipkin.zipkin import zipkin_span
     from py_zipkin.transport import SimpleHTTPTransport
     from py_zipkin.encoding import Encoding
     from py_zipkin import util
     
     with zipkin_span(
             service_name='my_service',
             span_name='home',
             sample_rate=100, # Value between 0.0 and 100.0
             transport_handler=SimpleHTTPTransport('localhost', 9411),
             encoding=Encoding.V2_JSON,
             zipkin_attrs=util.ZipkinAttrs(trace_id='3083235226e88c08', span_id=util.generate_random_64bit_string(), parent_span_id='3eb7433239c5f037', flags='0', is_sampled=True) #不携带zipkin_attrs会开启一个新的trace，携带zipkin_attrs可以指定trace_id和parent_span_id
         ) as zipkin_context:
       xxx
     ```

     

  2. decorator

     ```python
     @zipkin_span(service_name='my_service',span_name='home',transport_handler=SimpleHTTPTransport('localhost', 9411),sample_rate=100,encoding=Encoding.V2_JSON)
     def xxx()
     	xxxx
     ```

- Log a span within the context of a zipkin trace

```python
    If you're already in a zipkin trace, you can use this to log a span inside. The
    only required param is service_name. If you're not in a zipkin trace, this won't do anything.

    # As a decorator
    @zipkin_span(service_name='my_service', span_name='my_function')
    def my_function():
        do_stuff()

    # As a context manager
    def my_function():
        with zipkin_span(service_name='my_service', span_name='do_stuff'):
            do_stuff()
```





