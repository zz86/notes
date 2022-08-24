### vue核心

- vue是数据驱动的

#### 学习vue之前要掌握的javascript基础知识

- ES6语法规范

- ES6模块化

- 包管理器

- 原型、原型链

- 数组常用方法

- axios

- promise

  ......

#### 模板语法

- 插值语法：用于解析标签体内容
- 指令语法：用于解析标签（包括：标签属性、标签体内容、绑定事件......）

#### 计算属性

- 

#### vue指令

- v-bind:value=       简写 :value=
- v-on:事件=，简写@事件=
- v-text=''
- v-html=''
- v-model
- v-once：也可以插入值，但是不更新
- v-if=
- v-else
- v-for

#### 数据绑定

- 单向绑定（v-bind）：数据只能从data流向页面
- 双向绑定（v-model）：数据不仅能从data流向页面，还可以从页面流向data
  - 发布者->订阅者

备注：

1. 双向绑定一般用在表单类元素上（如：input，select等）
2. v-bind:value可以简写为:value
3. v-model:value可以简写为v-model，因为v-model默认搜集的就是value值

#### MVVM模型

1. M：模型（Model）：data中的数据
2. V：视图（View）：模板代码
3. VM：视图模型（ViewModel）：Vue实例

备注：

- data中的所有属性最终都出现在了vm身上
- vm身上的所有属性及vue原型上的所有属性，在Vue模板中都可以直接使用

#### 数据代理

- 通过一个对象代理对另一个对象中属性的操作（读/写），更方便的操作data中的数据

- 基本原理：通过Object.defineProperty()把data对象中所有属性加到VM上，为每一个添加到vm上的属性都指定一个getter/setter，在getter/setter内部去操作（读/写）data中对应的属性

#### 事件处理



### vue组件编程

#### 组件

- 扩展了html标签的
- 以.vue结尾的文件，都可以叫做组件
- 不成文的规矩：组件首字母大写

#### 组件间通信

- 父组件 传 子组件
- 子组件 传 父组件
- 兄弟组件之间的传值

#### 非单文件组件

- 每次调用Vue.extend时返回的都是一个全新的VueComponent
- Vue.extend(options)组件配置中：data函数、methods函数、watch函数、computed函数中，它们的this均是VueComponent的实例对象
- new Vue(options)配置中：data函数、methods函数、watch函数、computed函数中，它们的this均是Vue实例对象
- VueComponent的实例对象简称vc，也可称之为组件实例对象，Vue实例对象简称vm

- 一个重要的内置关系

![image-20220512101052709](/home/zzm/snap/typora/57/.config/Typora/typora-user-images/image-20220512101052709.png)

#### 单文件组件

- 不同版本的vue

  - vue.js和vue.runtime.js的区别
    - vue.js包含完整版的Vue，包含：核心功能+模板解析器
    - vue.runtime.js是运行版的Vue，只包含：核心功能，没有模板解析器

  - 因为vue.runtime.js没有模板解析器，所以不能使用template配置项，需要使用render函数接收到的creatElement函数去指定具体内容



### vue-router

- v4.x对应vue3，v3.x对应vue2

#### 单页面应用

- single page web application，SPA
- 整体应用只有一个完整的页面
- 点击页面中的导航链接不会刷新页面，只会做页面的局部更新
- 数据需要通过ajax请求获取

#### 路由

- 一个路由就是一组映射关系（key-value），key为路径，value可能是function或component

#### 几个注意点：

- 路由组件通常存放在pages文件夹，一般组件通常存放在components文件夹
- 通过切换，“隐藏”了的路由组件，默认是被销毁的，需要的时候再去挂载
- 每个组件都有自己的$route属性，里面存放着自己的路由信息
- 整个应用只有一个router，可以通过组件的$router属性获取到

#### 缓存路由组件 keep-alive

- 作用：让不展示的路由组件保持挂载，不被销毁，防止dom重复渲染
- include：包含哪个组件
- exclude：不包含哪个组件
- 具体编码

```html
<keep-alive>
	<router-view></router-view>
</keep-alive>
```

#### 懒加载

#### 重定向

```
{
	path: '*',
	redirect: Home
}
```

#### 路由传值

- this.$route

#### 两个新的生命周期钩子

- 作用：路由组件所独有的两个钩子，用于捕获路由组件的激活状态
- 具体名字：
  - activated路由组件被激活时触发
  - deactivated路由组件失活时触发

#### 全局前置路由守卫

- 初始化的时候、每次路由切换之前被调用

#### 全局后置路由守卫

- 初始化的时候、每次路由切换之后被调用

#### 独享路由守卫

- 只有前置，没有后置

#### 组件内路由守卫

- beforeRouteEnter，通过路由规则进入该组件时被调用
- beforeRouteLeave，通过路由规则离开该组件时被调用

#### 路由器的两种工作模式

- 对于一个url来说，#以及其后面的内容就是hash值
- hash值不会包含在http请求中，即hash值不会带给服务器
- hash模式
  - 地址中永远带着#号，不美观
  - 若以后将地址通过第三方手机app分享，若app校验严格，则地址会被标记不合法
  - 兼容性较好
- history模式
  - 地址干净，美观
  - 兼容性和hash模式相比略差
  - 应用部署上线时需要后端人员支持，解决刷新页面服务端404的问题



### Vue脚手架

#### 生命周期（钩子函数）

- 四个地方存在生命周期
  1. 创建
  2. 组件渲染
  3. 修改数据
  4. 销毁

- 生命周期在什么地方使用

  比如：在一刷新（进入）页面时要请求接口

- vue组件的created和mounted

  created:在模板渲染成html前调用，即通常初始化某些属性值，然后再渲染成视图。

  mounted:在模板渲染成html后调用，通常是初始化页面完成后，再对html的dom节点进行一些需要的操作。

#### style模块化

- scoped，该样式仅在当前组件生效

- 

#### 样式穿透

- 父元素 >>> 子元素

#### 样式中的stylus

#### swiper

- 滑动

#### reset.css

- 重置样式

#### fastclick

- 解决click事件在移动端300ms延迟的问题

#### iconfont

- 图标库

#### animate.css

- 动画

#### windi css



### vue中的axios

#### 使用axios

- 下载 npm install axios --save
- 引入axios
  - import axios from 'axios'
  - Vue.prototype.axios = axios

- get请求只能传query参数，query参数都是拼在请求地址上的，post可以传body和query两种形式的参数
- quary参数（params）          body参数（data）

### vuex

#### 状态管理

#### State

- 存数据

#### mapState

- 取数据

#### mapMutations

- 修改数据

#### actions

- 异步修改数据



### vue-cli目录结构

#### vue.config.js

- publicPath

  - '/'表示静态资源文件在根目录下

    '/dist/'表示静态资源文件在/dist文件夹下

    './'表示相对路径


  - 区分环境


```
publicPath: process.env.NODE_ENV ==='production'
  ? './'
  : '/'
```

#### package.json

- devDependencies 是开发环境下的依赖，这里是开发环境下的依赖，上线后非必需，比如：webpack，gulp等压缩打包工具.
- dependencies 是生产环境下的依赖，项目刚需的依赖在这里，比如UI框架，字体文件等线上必需的东西.



### Vue UI 组件库





