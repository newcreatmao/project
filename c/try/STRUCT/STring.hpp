#ifndef __STRING_H_
#define __STRING_H_
typedef struct String_Node String_Node;
typedef struct String_end String_end;
typedef struct String_Link String_Link;

String_Node* GO_Next_String(String_Node*frent);
String_end* Get_end_Flag();
String_Link* Create_String_link();
void Create_String(String_Link* link);
String_Node* Add_Node_String(String_Node*frent);
void Output_String(String_Link*link);
int String_Lenth(String_Link*link);
String_Link* String_Cat(String_Link*link1,String_Link*link2);
String_Link* String_Copy_Shallow(String_Link*link);
String_Link* String_Copy_Dept(String_Link*link);
int String_Compare(String_Link*link1,String_Link*link2);

#endif