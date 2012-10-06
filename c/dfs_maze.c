//file name : dfs_maze.c
//created at: 2012年04月23日 星期一 23时33分07秒
//author:  纪秀峰
/* dfs(深度优先算法)算法 走迷宫 */
/* int maze[5][5] = { */
/*  0, 1, 0, 0, 0, */
/*  0, 1, 0, 1, 0, */
/*  0, 0, 0, 0, 0, */
/*  0, 1, 1, 1, 0, */
/*  0, 0, 0, 1, 0, */
/* }; */
/* 它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜
   着走，要求编程序找出从左上角到右下角的路线。程序如下： */


/* 这次堆栈里的元素是结构体类型的，用来表示迷宫中一个点的x和y坐标。我们用一个新
   的数据结构保存走迷宫的路线，每个走过的点都有一个前趋（Predecessor）点，表示
   是从哪儿走到当前点的，比如predecessor[4][4]是坐标为(3, 4)的点，就表示从(3,
   4)走到了(4, 4)，一开始predecessor的各元素初始化为无效坐标(-1, -1)。在迷宫中
   探索路线的同时就把路线保存在predecessor数组中，已经走过的点在maze数组中记为
   2防止重复走，最后找到终点时就根据predecessor数组保存的路线从终点打印到起点
    */

/* 每探索一步都打印出当前迷宫的状态（标记了哪些点），从打印结果可以看出这种搜索
   算法的特点是：每次探索完各个方向相邻的点之后，取其中一个相邻的点走下去，一直
   走到无路可走了再退回来，取另一个相邻的点再走下去。这称为深度优先搜索（DFS，
   Depth First Search）。探 */
/* 如果在探索问题的解时走进了死胡同，则需要退回来从另一条路继续探索，这种思想称
   为回溯（Backtrack），一个典型的例子是很多编程书上都会讲的八皇后问题。 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAX_ROW 5
#define MAX_COL 5

struct point {
  int x, y;
} stack[215];

int top=0;

void push(struct point p){
  stack[top++]=p;
}

struct point pop(){
  return stack[--top];
}

int is_empty(){
  return top==0;
}

int maze[MAX_ROW][MAX_COL] = {
  0, 1, 0, 0, 0,
  0, 1, 0, 1, 0,
  0, 0, 0, 0, 0,
  0, 1, 1, 1, 0,
  0, 0, 0, 1, 0,
};
/* 记录每个节点的前驱是哪个节点，即从哪个节点来到此节点的 */
struct point predecessor[MAX_ROW][MAX_COL]={
  {  {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}  },
  {  {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}, },
  {  {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}, },
  {  {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}, },
  {  {-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}, }
};

void visit(int row,int col,struct point pre){
  struct point cur ={row,col};
  maze[row][col]=2;             /* 2 表示这个节点被访问过 */
  if(!(row==0&&col==0)){        /* 0,0没有前驱节点，无从加起 */
    predecessor[row][col]=pre;
  }
  push(cur);
}

void print_maze(){
  int i,j;
  for ( i = 0; i < MAX_ROW; ++i) {
    for ( j = 0; j< MAX_COL; ++j) {
      printf ("%d, ",maze[i][j]);
    }
    printf ("\n");
  }
  printf ("\n");
}
int main(int argc, char *argv[]){
  struct point p={0,0};
  visit(0,0,p);
  /* push(p); */

  while(!is_empty()){
    p=pop();
    printf ("current=%d,%d\n",p.x,p.y);
    if (p.x==MAX_ROW-1&&p.y==MAX_COL-1){
      break;
    }
    if(p.y<MAX_COL-1 && maze[p.x][p.y+1]==0){        /* right */
      visit(p.x,p.y+1,p);
    }
    if(p.x<MAX_ROW-1 && maze[p.x+1][p.y]==0){        /* down */
      visit(p.x+1,p.y,p);
    }
    if(p.y>0 && maze[p.x][p.y-1]==0){        /* left */
      visit(p.x,p.y-1,p);
    }
    if(p.x>0 && maze[p.x-1][p.y]==0){        /* up */
      visit(p.x-1,p.y,p);
    }
    print_maze();
  }
  if (p.x==MAX_ROW-1 && p.y==MAX_COL-1){ /* 如果到达了终点，打印回路 */
    printf ("%d,%d\n",p.x,p.y);
    while(predecessor[p.x][p.y].x!=-1){
      p=predecessor[p.x][p.y];
      printf ("%d,%d\n",p.x,p.y);
    }
  }
  return 0;
}
