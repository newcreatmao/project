#ifndef __DATATYPECLASS_H_
#define __DATATYPECLASS_H_
using namespace std;
class Datatype_Stack{
    public:
    int age;
};

class Datatype_Tree{
    public:
    int age;
};

class Datatype_List{
    public:
    int age;
};

class Datatype_Set{
    public:
    int age;
    bool operator==(Datatype_Set & p);
};

class Datatype_Queue{
    public:
    int age;
};

class Datatype_Dir{
    public:
    int age;
};
#endif