//Author: James Chen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void changeLivingStatus(int row, int col, int cells[5][5], int result[5][5]){
  int numAliveNeighbors = 0;
  if (row>0){
    if (col>0){
      if(cells[row-1][col-1]==1){
        //check neighbor up and to the left
        numAliveNeighbors++;
        }
    }
    if (cells[row-1][col]==1){
      //check neighbor up
      numAliveNeighbors++;
    }
    if (col<4){
      if (cells[row-1][col+1]==1){
        //check neighbor up and to the right
        numAliveNeighbors++;
      }
    }
  }
  if (col>0){
    if(cells[row][col-1]==1){
      //check neighbor left
      numAliveNeighbors++;
    }
  }
  if (col<4){
    if(cells[row][col+1]==1){
      //check neighbor right
      numAliveNeighbors++;
    }
  }
  if (row<4){
    if (col>0){
      if(cells[row+1][col-1]==1){
        //check neighbor down and to the left
        numAliveNeighbors++;
      }
    }
    if(cells[row+1][col]==1){
      //check neighbor down
      numAliveNeighbors++;
    }
    if(col<4){
      if(cells[row+1][col+1]==1){
        //check neighbor down and to the right
        numAliveNeighbors++;
      }
    }
  }
  //done checking number of alive neighbors
  if(cells[row][col]==0){
    //dead cell case
    if(numAliveNeighbors==3){
      result[row][col]=1;
    }
    else{
      result[row][col]=0;
    }
  }
  else{
    //alive cell case
    if(numAliveNeighbors<2||numAliveNeighbors>3){
      result[row][col]=0;
    }
    else{
      result[row][col]=1;
    }
  }
}


int main(int argc, char *argv[]) {
  //Open file and read the contents into the 2D array cells
  if (argc!=3){
    printf("Usage: ./automata N FILENAME\nnum = number of generations\nfile = the filename that contains the initial position cells");
    exit(-1);
  }
  FILE *fptr;
  fptr = fopen(argv[2],"r");
  if(fptr == NULL)
   {
     printf("Error opening file."); 
     exit(1);
   }
  int cells[5][5];
  for (int i=0; i<5;i++){
    for (int j=0; j<5; j++){
      fscanf(fptr, "%d", &cells[i][j]);
    }
  }
  fclose(fptr);
  int generations = atoi(argv[1]);
  //store new generation in result
  int result[5][5];
  for(int countgen=1;countgen<=generations; countgen++){
    for(int row=0; row<5; row++){
      for (int col=0; col<5; col++){
        changeLivingStatus(row, col, cells, result);
      }
    }
    for(int i=0; i<5; i++){
          for (int j=0; j<5; j++){
              cells[i][j]=result[i][j];
            }
          }  
  }

  //Export contents of result[][] into output file
  char *outputname=argv[2];
  strncat(outputname,".out",4);
  FILE *output;
  output = fopen(outputname,"w");
  if (output==NULL){
    printf("Can't open file %s to write to", outputname);
  }
  for(int row=0; row<5; row++){
      for (int col=0; col<5; col++){
        fprintf(output, "%d ", result[row][col]);
      }
    fprintf(output, "\n");
  }
  fclose(output);
}