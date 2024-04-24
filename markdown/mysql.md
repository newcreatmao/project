[toc]

### 数据库概念

![image-20230802195209189](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802195209189.png)

![image-20230802195306581](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802195306581.png)



### sql的通用语法

![image-20230802191339307](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802191339307.png)

![image-20230802191356129](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802191356129.png)

跳转数据库使用 use 数据库名

#### DDL

![image-20230802191554504](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802191554504.png)

[]里的都是可选的,使用时不需要[]

因为有四字节数据故字符集应用utf8mb4

![image-20230802193352520](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802193352520.png)

![image-20230802193445420](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802193445420.png)

![image-20230802193902373](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802193902373.png)



![image-20230802200356945](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802200356945.png)

![image-20230802200809187](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802200809187.png)

![image-20230802200924601](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802200924601.png)

![image-20230802201002252](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802201002252.png)

![image-20230802201054914](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802201054914.png)

##### 数据类型

![image-20230802194337424](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802194337424.png)

![image-20230802194442141](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802194442141.png)

char(num):num表示最长的字符

![image-20230802194730599](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802194730599.png)

命名规则 ：变量名  数据类型

comment是定义注释的作用

#### DML

![image-20230802202650345](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802202650345.png)

![image-20230802202750932](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802202750932.png)

![image-20230802202834283](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802202834283.png)

![image-20230802202958152](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802202958152.png)

![image-20230802203144454](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802203144454.png)

![image-20230802203238105](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802203238105.png)

#### DQL

![image-20230802203546887](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802203546887.png)

![image-20230802203840065](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802203840065.png)

as可省略

![image-20230803131223065](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803131223065.png)

![image-20230803131913098](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803131913098.png)

![image-20230803132100019](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803132100019.png)

![image-20230803132221145](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803132221145.png)

聚合函数（*）表示作用一整列

![image-20230803132522214](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803132522214.png)

![image-20230803133142949](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803133142949.png)

![image-20230803133402790](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803133402790.png)



![image-20230803134311829](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803134311829.png)

![image-20230803135509462](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803135509462.png)

##### 执行顺序

![image-20230803135725712](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803135725712.png)



![image-20230803135958557](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803135958557.png)

![image-20230803140036042](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803140036042.png)

![image-20230803141412862](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803141412862.png)

![image-20230803141440239](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803141440239.png)

![image-20230803141543787](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803141543787.png)

![image-20230803141753729](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803141753729.png)

### 函数



#### 字符串函数

![image-20230803143134558](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230803143134558.png)

#### 数值函数

![image-20230808163100608](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808163100608.png)

#### 日期函数

![image-20230808164602151](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808164602151.png)

####  流程函数

![image-20230808164728124](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808164728124.png)

### mysql图形化界面



![image-20230802202444462](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230802202444462.png)

#### 约束

![image-20230808170052449](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808170052449.png)

可在修改或创建的时候添加或修改约束

![image-20230808174554448](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808174554448.png)

![image-20230808174816339](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808174816339.png)

![image-20230808175039665](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808175039665.png)

![image-20230808175348127](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808175348127.png)

![image-20230808175514215](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808175514215.png)

![image-20230808175653944](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230808175653944.png)

##### 多表查询

![image-20230811151324057](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811151324057.png)

![image-20230811152313807](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811152313807.png)

![image-20230811152400124](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811152400124.png)

![image-20230811152519643](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811152519643.png)

![image-20230811152626392](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811152626392.png)

![image-20230811153454252](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811153454252.png)

![image-20230811153741803](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811153741803.png)

加连接条件筛选符合条件的数据

![image-20230811153916411](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811153916411.png)

###### 内连接（交集）

![image-20230811154145921](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811154145921.png)

![image-20230811154558932](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811154558932.png)

注意：起别名后原名不能用了

###### 外连接（单集合）

![image-20230811154718142](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811154718142.png)



###### 自连接

![image-20230811154948943](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811154948943.png)

![image-20230811155753820](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811155753820.png)

###### 联合查询

![image-20230811155839573](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811155839573.png)

![image-20230811160302957](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811160302957.png)

###### 子查询

![image-20230811160407666](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811160407666.png)

![image-20230811160600263](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811160600263.png)

![image-20230811160635677](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811160635677.png)









![image-20230811160722741](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811160722741.png)

![image-20230811160902178](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811160902178.png)

![image-20230811161605493](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811161605493.png)



![image-20230811161644928](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811161644928.png)

![image-20230811162135823](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811162135823.png)

in

##### 事务

![image-20230811162357533](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811162357533.png)

![image-20230811162427096](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811162427096.png)

三步都要手动

回滚就是回到未修改时的数据

![image-20230811162504764](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811162504764.png)

![image-20230811162719633](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811162719633.png)







Set   ....=0表示手动

![image-20230811163211175](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811163211175.png)

方式二

![image-20230811163145342](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811163145342.png)

###### 事务的四大特性

![image-20230811163414899](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811163414899.png)

![image-20230811163511128](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811163511128.png)

###### 并发事务问题

![image-20230811163813920](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811163813920.png)

![image-20230811163933594](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811163933594.png)

![image-20230811164042570](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811164042570.png)

###### 事务的隔离级别

![image-20230811164159821](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811164159821.png)

![image-20230811164247188](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811164247188.png)

![image-20230811164606700](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230811164606700.png)