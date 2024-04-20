#include "Datatypeclass.hpp"
using namespace std;
bool Datatype_Set::operator==(Datatype_Set & p){
    if(this->age == p.age){
        return true;
    }
    else{
        return false;
    }
}