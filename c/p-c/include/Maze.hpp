#ifndef __MI_H
#define __MI_H

#include"iostream"
using namespace std;

class Maze{
private:
    int**I_Maze;
    int I_w;
    int I_h;
    bool hasPath;
public:
    void Creat_Maze(int,int);
    void Init_Maze();
    void Print_Maze();
    bool Is_resionable();
    void Ser_Dfs(int,int);
    void Ser_Bfs();
    ~Maze(){
        for(int i=0;i<I_w;i++){
            delete [] I_Maze[i];
        }
        delete [] I_Maze;
        I_Maze=nullptr;
        std::cout<<"delete seccess!"<<std::endl;
    }
};

#endif