#include <stdio.h>
#include "STring.hpp"
int main(){
    String_Link* Link = Create_String_link();
    Create_String(Link);
    Output_String(Link);
    return 0;
}