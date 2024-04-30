CREATE table st_table(
    id int NOT NULL PRIMARY KEY,
    name varchar(20),
    age int,
    grade int,
    class int,
    st_id varchar(30),
    phone varchar(20),
    wechat varchar(20)
);

CREATE table user(
    username varchar(20),
    password varchar(20),
    auth varchar(10)
);