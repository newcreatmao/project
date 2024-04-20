#include"../include/Maze.hpp"
#include"ctime"
#include"cstdlib"
#include"queue"
#include"stack"

void Maze::Creat_Maze(int w,int h){
    I_w=w;
    I_h=h;
    I_Maze=new int*[w];
    for(int i=0;i<w;i++){
        I_Maze[i]=new int[h];
    }
}

void Maze::Init_Maze(){
    srand(time(0));
    for(int i=0;i<I_w;i++){
        for(int j=0;j<I_h;j++){
            *(*(I_Maze+i)+j)=rand()%2;
        }
    }
    *(*(I_Maze))=1;
    *(*(I_Maze+I_w-1)+I_h-1)=1;       
}

void Maze::Print_Maze(){
    for(int i=0;i<I_w;i++){
        for(int j=0;j<I_h;j++){
            cout<<*(*(I_Maze+i)+j)<<" ";
        }
        cout<<endl;
    }
}

void Maze::Ser_Bfs(){
    if (!Is_resionable()) {
        cout << "The maze is not resionable." << endl;
        return;
    }
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));
    I_Maze[0][0] = 1;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int x = p.first;
        int y = p.second;
        if (x > 0 && I_Maze[x - 1][y] == 0) {
            q.push(make_pair(x - 1, y));
            I_Maze[x - 1][y] = 2;
        }
        if (x < I_w - 1 && I_Maze[x + 1][y] == 0) {
            q.push(make_pair(x + 1, y));
            I_Maze[x + 1][y] = 2;
        }
        if (y > 0 && I_Maze[x][y - 1] == 0) {
            q.push(make_pair(x, y - 1));
            I_Maze[x][y - 1] = 2;
        }
        if (y < I_h - 1 && I_Maze[x][y + 1] == 0) {
            q.push(make_pair(x, y + 1));
            I_Maze[x][y + 1] = 2;
        }
    }
}

bool Maze::Is_resionable() {
    hasPath = false;
    Ser_Dfs(0, 0);
    return hasPath;
}

void Maze::Ser_Dfs(int x, int y) {
    if (x < 0 || x >= I_w || y < 0 || y >= I_h) {
        return;
    }
    if (x == I_w - 1 && y == I_h - 1) {
        hasPath = true;
    } else {
        Ser_Dfs(x + 1, y);
        Ser_Dfs(x - 1, y);
        Ser_Dfs(x, y + 1);
        Ser_Dfs(x, y - 1);
    }
}