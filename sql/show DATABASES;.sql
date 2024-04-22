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
insert into emp values(1,'001','����','��',88,'123456789101231231','2023-05-01');
insert into emp values(2,'002','����','Ů',43,'123456789101231232','2023-07-01');
insert into emp values(3,'003','����','��',25,'123456789101231233','2023-07-01');
insert into emp values(4,'004','������','��',21,'123456789101231234','2023-07-01');
insert into emp values(5,'005','����','Ů',53,'123456789101231235','2023-06-01');
insert into emp values(6,'006','���޼�','��',18,'12345678910123124x','2023-06-01');
insert into emp values(7,'007','ΤһЦ','Ů',30,'12345678910123123x','2023-05-01');
insert into emp values(8,'008','��ΰ','Ů',22,'12345678910123123x','2023-04-01');
insert into emp values(9,'009','������','Ů',29,'123456789101231444','2023-02-01');
insert into emp values(10,'0010','��ʵ','Ů',15,'123456789101231220','2023-02-01');
insert into emp(id,worken,name,gender,age,en) 
values(10,'0010','��ʵ��','Ů',15,'2023-02-01');
use y;
SELECT * from emp;
select gender,name from emp;
select gender from emp group by gender;
select gender,en from emp group by gender,en;

/*�����ѯһ��;ۺϺ���ʹ�� count*/
select count(gender) from emp;
select gender,count(gender) from emp group by gender;
/*��ʽ select ������ֶ�����ۺϺ��� from ���� group by �����ѯ�ֶ���*/
/*count ͳ��
sum ���
max ���ֵ
min ��Сֵ
avg ƽ��ֵ
std ��׼��
varince ����*/
select*from emp;
select count(*) from emp;
select count(idcard) from emp;
select age+10 from emp;/*���������� ������ʵ��ֵ*/
update emp set age=age+10;/*��������*/
select sum(age)as��ͺ� from emp;
select max(age)as������ from emp;
select min(age)as��С��� from emp;
select avg(age)asƽ����� from emp;
select gender,max(age) from emp group by gender;
/*�����ͬʱ�ڵ�ƽ������ �� ����*/
select en,count(en),avg(age) from emp group by en;
/*�����Ŵ���5 ������Ů��������� ��ͳ������*/
select id,name from emp where id>5;/*�жϱ�Ŵ���5*/
select gender,count(gender),sum(age) from emp group by gender;/*����Ů��������� ��ͳ������*/
select gender,count(gender),sum(age) from emp where id>5 group by gender;
/*having �Է��ຯ�������ݽ����ж� ��ʹ�þۺϺ���*/
select gender,count(gender),sum(age) from emp group by gender;
select gender,count(gender),sum(age) from emp group by gender
having sum(age)>200;
/*�����ѯ��ͬ���ڵ���Ů��Ϣ��ͳ��������������������1��*/
select gender,en,count(*) from emp group by gender,en having count(*)>1;
/*���������20���˽��з��࣬�����Ա����ڣ��������������䳬��35�������*/
select age,name from emp where age>30;/*����������30*/
select gender,en from emp group by gender,en;/*�����Ա������*/
select gender,en,max(age),count(*) from emp where age>30 
group by gender,en having max(age)>35;/*���������� ��������������35�����

/*�����ѯ order by ��һ�������н��Ӵ�С������desc�����ߴ�С��������asc��*/

/*������������� ���Ӵ�С*/
select age,name from emp order by age desc;
/*��С����*/
select age,name from emp order by age asc;
/*��������д asc desc Ĭ��Ϊasc*/
select age,name from emp order by age;

/*����ͳ�����ʮ���Ա���������򣬰���� �Ӵ�С*/
select age,name from emp where age>35 order by age desc;

/*limit ������������ݽ���Ҫ�������� */
/*�ж���������������*/
select age,name from emp where age>35 order by age desc limit 3;

/*limit 3,2 �ӵ����еĿ�ʼ�����������Ϣ*/
select age,name from emp order by age desc limit 3,2;



