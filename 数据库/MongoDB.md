
#### NoSQL

- 不仅仅是SQL

- 非关系型数据库
  - Redis
  - MongoDB

#### MongoDB  （JS语法）

- 默认主键_id

- 数据库 -> 集合 -> 文档 -> 域：值

#### 增删改查

- insert  insertMany
- remove
- update
- find  findOne
  - 比较运算符  逻辑运算符  范围运算符  正则表达式  指定域查询  自定义查询：$where:{js代码}

#### python操作MongoDB

- pymongo

#### 进阶用法

- limit()用于读取指定数量的文档
- skip()用于跳过指定数量的文档
- limit和skip同时的时候先skip再limit效率会高点
- sort()用于对结果集进行排序
- count()用于统计结果集中文档条数
- distinct()用于对数据进行去重

#### 聚合 Aggregation

- 聚合(aggregate)是基于数据处理的聚合管道，每个文档通过一个由多个阶段（stage）组成的管道，可以对每个阶段的管道进行分组、过滤等功能，然后经过一系列的处理，输出相应的结果。

- 语法：

  ```
  db.集合名称.aggregate({管道:{表达式}})
  ```

- 在MongoDB中，⽂档处理完毕后， 通过管道进⾏下⼀次处理 常用管道命令如下：
  - `$match`： 过滤数据， 只输出符合条件的⽂档
  - `$group`： 将集合中的⽂档分组， 可⽤于统计结果
  - `$project`： 修改输⼊⽂档的结构， 如重命名、 增加、 删除字段、 创建计算结果
  - `$sort`： 将输⼊⽂档排序后输出
  - `$limit`： 限制聚合管道返回的⽂档数
  - `$skip`： 跳过指定数量的⽂档， 并返回余下的⽂档

#### 索引

- 默认情况下，_id是集合的索引
- 唯一索引
- 复合索引