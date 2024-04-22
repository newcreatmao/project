create database y;
use y;
create table emp(
    id int,
    worken char(10),
    name char(10),
    gender char(1),
    age int,
    idcard char(18),
    en date
);
insert into emp values(1,'001','张三','男',88,'123456789101231231','2023-05-01');
insert into emp values(2,'002','李四','女',43,'123456789101231232','2023-07-01');
insert into emp values(3,'003','王五','男',25,'123456789101231233','2023-07-01');
insert into emp values(4,'004','找三四','男',21,'123456789101231234','2023-07-01');
insert into emp values(5,'005','孙琪','女',53,'123456789101231235','2023-06-01');
insert into emp values(6,'006','张无忌','男',18,'12345678910123124x','2023-06-01');
insert into emp values(7,'007','韦一笑','女',30,'12345678910123123x','2023-05-01');
insert into emp values(8,'008','张伟','女',22,'12345678910123123x','2023-04-01');
insert into emp values(9,'009','张三丰','女',29,'123456789101231444','2023-02-01');
insert into emp values(10,'0010','真实','女',15,'123456789101231220','2023-02-01');
insert into emp(id,worken,name,gender,age,en) 
values(10,'0010','真实李','女',15,'2023-02-01');
use y;
SELECT * from emp;
select gender,name from emp;
select gender from emp group by gender;
select gender,en from emp group by gender,en;

/*分类查询一般和聚合函数使用 count*/
select count(gender) from emp;
select gender,count(gender) from emp group by gender;
/*格式 select 分类的字段名或聚合函数 from 表名 group by 分类查询字段名*/
/*count 统计
sum 求和
max 最大值
min 最小值
avg 平均值
std 标准差
varince 方差*/
select*from emp;
select count(*) from emp;
select count(idcard) from emp;
select age+10 from emp;/*在输出上添加 不更改实际值*/
update emp set age=age+10;/*更新数据*/
select sum(age)as年纪和 from emp;
select max(age)as最大年纪 from emp;
select min(age)as最小年纪 from emp;
select avg(age)as平均年纪 from emp;
select gender,max(age) from emp group by gender;
/*输出不同时期的平均年龄 和 人数*/
select en,count(en),avg(age) from emp group by en;
/*分类编号大于5 男生和女生的年龄和 并统计人数*/
select id,name from emp where id>5;/*判断编号大于5*/
select gender,count(gender),sum(age) from emp group by gender;/*男生女生的年龄和 并统计人数*/
select gender,count(gender),sum(age) from emp where id>5 group by gender;
/*having 对分类函数的数据进行判断 能使用聚合函数*/
select gender,count(gender),sum(age) from emp group by gender;
select gender,count(gender),sum(age) from emp group by gender
having sum(age)>200;
/*分类查询不同日期的男女信息，统计人数，输入人数大于1的*/
select gender,en,count(*) from emp group by gender,en having count(*)>1;
/*对年龄大于20的人进行分类，分类性别日期，输出所有最大年龄超过35岁的数据*/
select age,name from emp where age>30;/*求出年龄大于30*/
select gender,en from emp group by gender,en;/*分类性别和日期*/
select gender,en,max(age),count(*) from emp where age>30 
group by gender,en having max(age)>35;/*将上两句结合 并且输出年龄大于35岁的人

/*排序查询 order by 对一个内容行进从大到小（降序desc）或者从小到大（升序asc）*/

/*对年龄进行排序 按从大到小*/
select age,name from emp order by age desc;
/*从小到大*/
select age,name from emp order by age asc;
/*如果排序后不写 asc desc 默认为asc*/
select age,name from emp order by age;

/*对年纪超过三十五的员工进行排序，按年纪 从大到小*/
select age,name from emp where age>35 order by age desc;

/*limit 输出多少行数据接需要几行数据 */
/*判断年龄最大的三个人*/
select age,name from emp where age>35 order by age desc limit 3;

/*limit 3,2 从第四行的开始，输出两行信息*/
select age,name from emp order by age desc limit 3,2;



