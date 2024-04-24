一：通过虚拟机去进行linux操作

清屏：clear

显示目录：ls

### 目录与文件

没有盘符（没有c，d盘这些，windows），只有一个根目录为“/“（顶级目录），所有文件都在它下面

路径之间层级用”/“表示，Windows中用”\“

例：/usr/local/hello.txt（开头的为根目录，后面为层级关系），Windows如：D\data\work\hello.txt

### 命令与命令行

命令行：终端程序，命令字符反馈界面

命令：操作指令，相当于运算符号

#### 命令通用格式

###### command 【-options】【parameter】

command：命令本身

options：命令的一些选项，可控制命令的行为细节

parameter：命令的参数，多为命令的指向目标

后两个为可选，非必填

如: cp -r test1 test2

用空格隔开对象所属，cp为命令，-r是选项，test1，2是参数



###### ls [-a -l -h] [linux路径]

ls：以平铺的形式，列出当前工作目录下的内容，相当于双击打开文件夹

home目录：用户的家目录，每个用户都有的专属目录，默认在/home/用户名，打开命令行程序时默认设置工作目录就在用户的home目录



参数：即ls的展示目标，可用于展示指定文件夹的目标

选项（可组合使用）:

-a：all，表示列出所有文件，列出的文件名前面带有.的表示隐藏文件（不用-a时不显示出的文件）

-l：list，表示以列表的形式（竖向排列）的形式展示内容，并展示更多信息（如时间日期），表示出来的数据前面是d的为目录，-为文件

-h：以阅读的形式表现出文件的大小，如k，m，g



目录切换命令

###### cd 【linux路径】

cd mao切换到目标目录mao下

cd 直接回到用户的home目录

查看当前工作目录

###### pwd直接使用

输出当前的工作目录



相对路径：以当前目录为去起点，路径无需以/开头

绝对路经：以根目录为起点，路径描述以/开头

特殊路径符：

. :当前目录，如cd./目录名

.. :表示上一级目录，如cd.. 即可切换到上一级目录，cd../..切换到上二级目录

~ :表示home目录，直接返回home目录，如cd~回到home, cd~/mao切换到mao目录

#### 文件的操作

目录的创建

###### mkdir 【-p】 linux路径

参数必填，即创建的文件夹的的路径，相对绝对都可

-p选项可选，表示自动创建不存在的父目录，可用于创建多层级的目录



创建文件夹需要修改路径，应确保操作是在home目录内，home目录外涉及权限问题，创建会不成功



文件的创建

###### touch linux路径

参数必填，表示要创建的文件路径



文件的内容查看

###### cat linux路径

显示全部内容



###### more linux路径

more支持分页，可一页页展示

必填参数

空格翻页，B返回上一页，Q退出



###### cp 【-r】参数1 参数2

-r：可选，用于复制文件夹

参数1：为被复制对象

参数2：为复制去的对象



###### mv 参数1 参数2

参数1，被移动的对象

参数2，移动去的对象，目标不存在则进行改名



###### rm 【-r，-f】参数1 参数2 参数3.......

-r表示删除文件夹

-f表示强制删除，只有root管理员用户删除内容会有提示

参数1，参数2......表示要删除的文件或文件夹路径，按照空格隔开

##### 通配符（*）：匹配任意内容

test*：表示匹配任何以test开头的内容

*test：表示匹配任何以test结尾的内容

*test *：表示匹配任何包含test的内容



切换root用户

su root，输入密码（开机密码）即可

exit或su 用户名 退回普通用户

在root时千万不能用

rm -rf /

rm-rf /*

相当于c盘格式化了



查找

###### which 要查找的命令

查看所使用命令的程序文件存放的位置



###### find

按文件名查找文件

find 起始路径 -name ”被查找的文件名“（注意要带双引号）

起始路径：表明在指定目录下的文件搜索



按文件大小查找路径

find 起始路径 -size +|-n【kMG】（注意，k是小写，MG是大写，不用括号）

+，- 表示大于小于

n是大小数字

kMG表示大小单位，kb，MB，GB



停止ctrl+c

###### grep [-n] 关键字 文件路径（对关键字进行查找）

-n：显示匹配的行的行号

关键字，必填，表过滤出的关键字，可以带有其它特殊符号和空格，推荐用双引号包围

文件路径，必填，表示要过滤内容的文件路径，可作为内容输入端口（即管道符的输入窗口）



###### wc 【-c -m -l -w】 文件路径

-c：统计bytes数量

-m：统计字符数量

-l：统计行数

-w：统计单词数量

参数 文件路径，被统计的文件，可作为内容输入窗口



###### 管道符：|

含义：将管道符左边命令的结果作为右边命令的输入

可嵌套



###### echo 输出的内容

只有一个参数表示要输出的内容，复杂内容可以用双引号包围



###### 反引号 `

被包围的内容会被当做命令执行，而非普通字符，如echo `pwd``即执行了pwd命令



###### 重定向符>和>>

(>)将左侧命令的结果，覆盖写入到符号右侧指定的文件中

（>>）将左侧命令的结果，追加写入到符号右侧指定的文件中



###### tail [-f -num] linux路径

可以查看文件的尾部内容·，跟踪文件的最新更改

-f：持续跟踪，ctrl+c停止运行

-num（具体的数字）：查看尾部多少行，不填默认10行



###### vi/vim文本编译器

命令模式：通过键盘快捷键进行操作

输入模式：编辑模式，插入模式

底线模式：以：开始，通常用于文件的保存与退出



vi 文件路径

vim 文件路径

文件不存在自动创建一个新的



操作流程

vim 文件路径

进入命令模式（i为输入模式）

esc退出输入模式回到命令模式

yyp复制一行

dd删除一行

uu撤销

：进入底线模式

W保存Q退出



快捷键

![image-20230701224037699](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230701224037699.png)

![image-20230701224105282](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230701224105282.png)

![image-20230701224247782](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230701224247782.png)

粘贴模式用于从外部粘贴内容



### 用户

超级用户（root：超级管理员）：拥有最大的系统操作权限

普通账户：在许多地方的权限受限，权限在home用户内是不受限的，一旦处理home目录，在大多数地方仅有只读和执行权限，无修改权限

###### su [-] [用户名]

-可选，表示切换用户后加载环境变量

参数表指定用户，不加则默认切换到root

exit或ctrl+d可用于退回到上一个用户



root用户切换到其他用户不需要密码

普通用户切换到其他用户时需要输入密码（即该用户下的开机密码）



ubuntu切换用户用sudo -i

###### sudo 其他命令

为普通命令授权，临时以root身份执行

前提：需要为普通用户进行sudo授权

授权步骤：

1. 切换到root

2. 执行visudo命令或vi/etc/sudores

3. 按o到最后一行写入   用户名 ALL=（ALL）      NOPASSWD：ALL

4. WQ保存退出

   即配置完成

   取消即按以上操作删掉那一行即可

###### 用户与用户组

用户组管理（只能用root来执行）：

创建用户组：groupadd 用户组名

删除用户组：groupdel 用户组名



用户管理（只能用root来执行）：

useradd [-g -d] 用户名

创建用户

-g：指定用户的组，不指定则-g，会创建一个同名组并将用户自动加入，指定-g需要组已经存在，如以村子同名组，必须使用-g

-d：指定用户的home路径，不指定则home目录默认在：/home/用户名

删除用户

user [-r] 用户名

-r：删除用户的home目录，不使用-r，删除用户时，home目录保存

查看用户所属组

id 【用户名】

参数：用户名，查看用户的信息，不指定则查看本身

修改用户所属组

usermod -aG 用户组 用户名

将指定用户加入指定用户组



查看系统中的用户

getent passwd

可得七份信息：用户名：密码（x）：用户ID：描述信息：home目录：执行终端（默认bash）



查看系统中的用户组

getent group

三份信息：组名称：组认证（x）：组ID



###### 权限

![image-20230702212243457](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230702212243457.png)

![image-20230702212327860](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230702212327860.png)

![image-20230702212751442](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230702212751442.png)

###### 修改权限信息

###### chmod [-R] 权限 文件或文件夹

-R：对文件夹里的全部内容进行同样的操作

例如： chmod u=rwx,g=rx,o=x hello.txt表示将文件权限修改成rwxr-x--x

u表示user所属用户权限，g表示group组权限，o表示other其他用户权限

加上-R 文件改成文件夹则表示对该文件夹里的所有内容的权限修改成所设置的

![image-20230702214935221](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230702214935221.png)

二进制，可简化命令

如：chmod 751 hello.txt

r=4

w=2

x=1

加起来就行了（虽然没必要，哈哈哈哈）



###### chown [-R] [用户]【:】[用户组] 文件或文件夹

此命令只适用于root用户执行

-R：对文件夹内全部内容应用相同规则

用户或用户组：修改的所属地

：用于分隔用户和用户组



## linux的实用操作

###### ctrl+c强制停止

###### ctrl+d退出或登出，不能退出vi/vim

###### history 查看历史输入过的命令   history | gray ch可过滤出ch命令

###### ！+命令前缀：自动执行上一次匹配前缀的命令如！p，就近原则

###### ctrl+r，输入内容去匹配历史命令，如 ctrl+r+pass匹配命令语句，满意回车则执行，反之左右键进行修改

###### 光标移动快捷键

ctrl+a跳到命令开头

ctrl+e跳到命令末尾

ctrl+键盘左键，向左跳一个单词

ctrl+键盘右键，向右跳一个单词

###### 清屏ctrl+l或clear



#### 软件安装（分centos与ubuntu）

centos

###### yum [-y] [install | remove | search] 软件名称

-y自动确认，install安装，remove卸载，search搜索

yum需要root权限和联网

三个应用程序·后缀（.exe   ,  .pkg  ,  .rpm)



ubuntu

###### apt [-y] [install | remove |search] 软件名称

用法与yum一致，同样需要root权限

安装包：(.deb  )

wget:从网络上下载软件



##### 软件的启动和停止

###### systemctl [start | stop | status |enable |disable|服务名]

启动|关闭|查看状态|开启开机自启|关闭开机自启|

服务比较多，比如：

NetworkManager,主网络服务

netwoek,副网络服务

firewalld,防火墙服务

sshd，ssh服务



控制第三方软件

安装ntp（时间同步软件）和httpd软件

可通过ntpd和httpd服务名（他们可自动集成到systemctl中）配合systemctl进行控制



手动添加软件到systemctl中



###### 软链接：可将文件或文件夹链接到其他位置（类似于快捷方式）

ln -s 参数1 参数2

-s表示创建软链接

参数一：被链接的文件或文件夹

参数二：要链接到的地方



###### date [-d] [+格式化字符串]

-d：按照给定字符串显示日期，一般用于日期计算

格式化字符串：通过特定的字符串标记，来控制显示的日期格式

%Y：年

%y：年份后两位

%m：月份

%d：日

%H：小时

%M：分钟

%S：秒

%s：自初始时间到现在的秒数（19700101）

date可查看当前的以上全部信息



用data +"%Y-%m-%d  %H:%M:%S"（带空格会让系统误认为是新参数，用“”括起来使其为一个整体）

得年-月-日 时：分：秒



data -d “+1 day”

可得明天的日期

year，month，day，hour，minte，second



修改linux时区（需要root权限）

rm -f /etc/localtime 删除原默认时区

sudo ln -s /usr/share/zoninfo/Asia/地区名  /etc/localtime 将新时区链接到localtime中

###### 时间联网校准

ntp程序

需要下载，可自动设置为内置程序（ntpd）

可自动联网校准系统时间

手动校准

sudo ntpdata -u ntp.aliyun.com 阿里云服务器



###### ip与主机

ip：有ipv4和ipv6，联网后都有

ipv4：a.b.c.d

abcd分别为0-255得数字

查看IP：ifconfig 可查看IP地址，ip addr也行



特殊ip

127.0.0.1代指本机

0.0.0.0可用于指代本机，在端口绑定中绑定关系，在一些ip地址限制中表示所有ip



主机名：hostname查看，hostnamectl set-hostname 主机名 可修改主机名



域名解析

![image-20230703210736011](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230703210736011.png)

![image-20230703211212144](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230703211212144.png)

![image-20230703211234440](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230703211234440.png)

![image-20230703211308963](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230703211308963.png)

###### 虚拟机配置固定ip

![image-20230704164904050](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704164904050.png)

![image-20230704164939728](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704164939728.png)

![image-20230704165103237](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704165103237.png)

![image-20230704165538031](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704165538031.png)

ip地址与net8的子网IP范围要一样



###### ping [-c  num] ip或·主机名

检查指定网络服务器是否为可连通状态

-c，检查的次数，不指定则无限查询



###### wget [-b] ur1

-b可选，后台下载，可通过tail -f wget-log查看下载进度

url，下载链接



###### curl 【-O】 ur1

-O：用于下载文件，当ur1是链接时可以用此选项保存文件

ur1：发起请求的网络地址

相当于打开网址



namp程序，需下载

nmap 被查看的ip地址

可查看该ip对应的主机所连接的端口



![image-20230704172647443](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704172647443.png)

ps [-e  -f]

-e:显示出全部的进程

-f：以完全格式化的形式展示信息（展示全部信息）

![image-20230704172948187](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704172948187.png)

cmd：进程的启动命令或启动路径



###### kill 【-9】 进程Id

关闭进程

-9：表示强制关闭进程，不使用有可能不会终止进程



![image-20230704174849067](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704174849067.png)

![image-20230704175029179](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704175029179.png)

![image-20230704175111794](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704175111794.png)

![image-20230704175201249](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704175201249.png)

![image-20230704175243169](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704175243169.png)

###### df [-h]

查看硬盘使用情况

-h使数据好看



###### iostat [-x] [num1] [num2]

-x：显示更多信息

num1：刷新间隔，num2：刷新次数

![image-20230704175706333](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704175706333.png)





![image-20230704175822534](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230704175822534.png)



###### env 查看环境

![image-20230706094947253](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706094947253.png)

字典格式

![image-20230706095134725](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706095134725.png)



![image-20230706095302754](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706095302754.png)

![image-20230706095638098](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706095638098.png)

配置

![image-20230706100233252](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706100233252.png)



###### 上传和下载

finalshell 底下的文件，右键即可下载

改变底下的管理员，直接在连接界面将用户改成root

上传：找到要上传的文件夹，将文件拖进去就行了



rz：进行上传，上传速度较慢

sz：进行下载

sz+文件路径

rz 弹出程序框



###### 压缩和解压

![image-20230706092831240](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706092831240.png)

![image-20230706093018901](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706093018901.png)

![image-20230706093233192](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706093233192.png)

-c和-x分开用

![image-20230706093713148](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706093713148.png)

-C单独使用，否则解压到当前目录

![image-20230706094143031](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706094143031.png)

![image-20230706094347511](C:\Users\mao\AppData\Roaming\Typora\typora-user-images\image-20230706094347511.png)

有同名内容时会覆盖



###### 安装c与c++环境

[centos,Linux配置c++环境_summerhave7fishes的博客-CSDN博客](https://blog.csdn.net/summer_76195/article/details/125991487?ops_request_misc=%7B%22request%5Fid%22%3A%22168931857916800222813326%22%2C%22scm%22%3A%2220140713.130102334.pc%5Fall.%22%7D&request_id=168931857916800222813326&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-2-125991487-null-null.142^v88^control_2,239^v2^insert_chatgpt&utm_term=Linux安装c%2B%2B环境&spm=1018.2226.3001.4187)

[(3条消息) Ubuntu安装C/C++环境_ubuntu安装c++_郭建華的博客-CSDN博客](https://blog.csdn.net/ACE_GJH/article/details/125708735)

[(cmake的使用教程)](https://blog.csdn.net/weixin_43717839/article/details/128032486?ops_request_misc=%7B%22request%5Fid%22%3A%22168924816516800188517941%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=168924816516800188517941&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-128032486-null-null.142^v88^control_2,239^v2^insert_chatgpt&utm_term=cmake&spm=1018.2226.3001.4187)