
#### 虚拟环境python包freeze与install

- pip freeze > requirements.txt
- pip install -r requirements.txt

#### subprocess

- 开启子进程执行shell命令

#### PyQt

- Graphical User Interface（GUI）
- sys.argv是程序运行时传递的参数列表，第一个是python程序本身，后面是参数

#### pymysql

- 执行sql流程：
  1. 链接
  2. 获取游标
  3. 通过游标执行sql语句
  4. commit

- sql语句的参数化可以有效防止sql注入，注意：此处不同于python的字符串格式化，全部使用%s占位

#### uiautomation

- 基于windows的ui自动化框架

#### OpenCV   cv2

