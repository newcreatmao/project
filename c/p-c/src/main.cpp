#include<iostream>
#include"Maze.hpp"
using namespace std;

int main(){
    Maze text;
    text.Creat_Maze(3,3);
    text.Init_Maze();
    text.Print_Maze();
    text.Ser_Bfs();
    text.Print_Maze();
}
