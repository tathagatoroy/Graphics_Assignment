#include "main.h"

int HASH_CONSTANT = 1234;

int hash(int x,int y)
{
return y*HASH_CONSTANT+x;
}
int reverse_hash(int hashed,int &x,int &y){
    x = hashed % HASH_CONSTANT;
    y = hashed / HASH_CONSTANT;
     
}
void create_maze(int height,int width)
{
 int matrix[height][width];
 for(int i=0;i<height;i++){
     for(int j=0;j<width;j++){
         matrix[i][j] = 0;
     }
 } 
 vector<pair<pair<int,int>,pair<int,int>>> no_walls
 srand(time(NULL));  
}