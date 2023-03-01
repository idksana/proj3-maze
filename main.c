
//sana abbasi
//proj3
//netid: sabbas29
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define main_h
#define TRUE 1
#define FALSE 0
int debugMode;

/* This program will read the first 3 lines of input
   and prints a static 2D maze*/


typedef struct mazeStruct{
 char arr[32][32];  /* allows for a maze of size 30x30 plus outer walls */
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;


typedef struct nodeStruct{        // declare strtuct nodeStruct
  int x;// data field: integer
  int y;
  struct nodeStruct *next;       // link field: pointer of same kind
}node;

void push(node **S, int xval, int yval){
    //•pushing an element onto the stack

  node *temp = (node*)malloc(sizeof(node));
  // initialize fields

  temp->x = xval;
  temp->y = yval;
  // points to our old head

  temp->next = *S;

  //update the head
  *S = temp;
}

void pop(node **S){
    //•popping an element off of the stack
  node *temp = *S;
  //update the head
  *S = (*S)->next;
  free(temp);
}

int isEmpty(node *S){
    //•resetting the stack so that it is empty and ready to be used again.

  if (S == NULL){
    return(1);
  }
  else{
    return(2);
  }
}

int endPoint(node *S, int xpt, int ypt){
//    x and y end points on returning
//    if doesnt equal, exit
   if (S->x == xpt){
       return(1);
   }
   else if(S->y == ypt){
       return(1);
   }
   else{
       return(0);
   }
}


int xpoint(node *S){
    //pointer to x
  return(S->x);
}

int ypoint(node *S){
    //pointer to y
  return(S->y);
}

void debugging(){
    //made a function for "(%d,%d) pushed into the stack. \n"
    node* hd = NULL;
    if (debugMode == TRUE){
      printf("(%d,%d) pushed into the stack. \n", xpoint(hd), ypoint(hd));
    }
}

void displayStack(node *S){
//    gettng the points x,y
    if(S == NULL){
      return;
    }
    displayStack(S->next);
    printf("(%d,%d) ", S->x, S->y);
}


void clearAll(node** S){
   /* deref head_ref to get the real head */
   node* current = *S;
   node* next;

   while (current != NULL){
       next = current->next;
       if (debugMode == TRUE){
         printf("(%d,%d) popped off the stack.\n", current->x , current->y);
       }
       free(current);
       current = next;
   }

   /* deref head_ref to affect the real head back
      in the caller. */
   *S = NULL;
}
void invlaid(){
    //if counter is less than 2 the data is invalid
    int counter = 0;
    if(counter < 2){
      printf("Invalid data file.\n");
      exit(0);
    }

}

/*
 (using for visual)
 size: 10, 20start: 1, 1end: 10, 20
 **********************
 *s........*..........*
 *........*...........*
 *..C....*............*
 *.*....*.............*
 **....*......C.......*
 *....C...............*
 *...*................*
 *..C.................*
 *....................*
 *...................e*
 **********************
 */

int main (int argc, char **argv){
  node *S; //bring node into main
  maze m1; //bring maze into main
  int xpos, ypos;
  int i, j;
  char k;

  FILE *src;

  /* verify the number of command lines used */
  if(argc > 3) {
     printf("Too many input files.\n");
     exit(-1);
  }

  if(argc < 2) {
     printf("Too little input files.\n");
     exit(-1);
  }

  /* Try to open the input file. */
  if ((src = fopen( argv[1], "r")) == NULL){
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  /* Verify the -d flag*/
  if(argc == 3) {
      if(strcmp(argv[1], "-d") == 0 || strcmp(argv[2], "-d") == 0){
        debugMode = TRUE;
      }
  }

  char count;
  int counter = 0;

  for (count = getc(src); count != EOF; count = getc(src)){
       if (count == '\n'){  // Increment count if this character is newline
          counter++;
        }
  }

  invlaid();

  fclose(src);

  /* Try to open the input file. */
  if ((src = fopen( argv[1], "r")) == NULL){
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */
    fscanf(src, "%d %d", &m1.xsize, &m1.ysize);
    if (m1.ysize <= 0){
        printf("Maze sizes must be greater than 0.");
        exit(0);
    }

    if (m1.xsize <= 0){
        printf("Maze sizes must be greater than 0.");
        exit(0);
    }

    printf("size: %d, %d\n", m1.xsize, m1.ysize);

    fscanf(src, "%d %d", &m1.xstart, &m1.ystart);
    if (m1.ystart > m1.ysize){
        printf("Start/End position outside of maze range.\n");
        exit(0);
    }

    if (m1.xstart > m1.xsize){
        printf("Start/End position outside of maze range.\n");
        exit(0);
    }

    printf ("start: %d, %d\n", m1.xstart, m1.ystart);

    fscanf (src, "%d %d", &m1.xend, &m1.yend);
    if (m1.yend > m1.ysize){
        printf("Start/End position outside of maze range.\n");
        exit(0);
    }

    if (m1.xend > m1.xsize){
        printf("Start/End position outside of maze range.\n");
        exit(0);
    }

    printf ("end: %d, %d\n", m1.xend, m1.yend);


  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++){
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++){
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';

  /*This code will only read the first three lines */
  /*Complete this code by reading the rest of the input
    and placing blocked and coin positions. */
  /* Blocked positions are marked with 'b' in the input file
     They should be marked by * in the maze */


  while(fscanf(src, "%d %d %c", &xpos, &ypos, &k) != EOF){

    if (xpos > (m1.xsize + 2)){
        printf("Invalid coordinates: outside of maze range.\n");
        continue;
    }

    if (ypos > (m1.ysize + 2)){
        printf("Invalid coordinates: outside of maze range.\n");
        continue;
    }

    if (xpos == m1.xstart){
        printf("Invalid coordinates: attempting to block start/end position.\n");
        continue;
    }
      if( ypos == m1.ystart){
         printf("Invalid coordinates: attempting to block start/end position.\n");
         continue;
      }
    if (xpos == m1.xend ){
        printf("Invalid coordinates: attempting to block start/end position.\n");
        continue;
    }
    if ( ypos == m1.yend){
        printf("Invalid coordinates: attempting to block start/end position.\n");
        continue;
          }



    if (k == 'b'){
    m1.arr[xpos][ypos] = '*';
    }

    if (k == 'c'){
    m1.arr[xpos][ypos] = 'C';
    }

    if (k != 'b' && k!= 'c'){
        printf("Invalid type: type is not recognized.\n");
        continue;
    }
 }

    /* print out the initial maze */
    for (i = 0; i < m1.xsize+2; i++){
    for (j = 0; j < m1.ysize+2; j++)
      printf ("%c", m1.arr[i][j]);
      printf("\n");
    }
    printf("\n");

    char v = 'V'; // visited positions
    char u = 'U'; // univisited positions
    int coin = 0; // coin counter

    for (i = 0; i < m1.xsize + 2; i++){
       for (j = 0; j < m1.ysize + 2; j++)
        if( m1.arr[i][j] == '.'){
            m1.arr[i][j] = u; //unvisted
        }
      }

    node *ptr1;    // declare pointer
    ptr1 = (node*)malloc(sizeof(node));

    int posx = m1.xstart;
    int posy = m1.ystart;

    ptr1->x = posx;
    ptr1->y = posy;
    ptr1->next = NULL;
    free(ptr1);

    node* hd = NULL;   // Declare head of the pointer and set it to NULL

    push(&hd, posx, posy);
    m1.arr[m1.xstart][m1.ystart] = v; // vistited

    debugging();

    while(isEmpty(hd) != 1 && endPoint(hd, m1.xend, m1.yend) != 1){
        // push(&head, currentPositionOfx+1, currentPositionOfy);

        if (posx == m1.xend){
           break;
        }
        if (posy == m1.yend){
            
        }
//Mazeindescriptionisflipped,aslongasyoufollowthegivenorder
        //i. x+1,y
        //ii. x,y+1
        //iii. x-1,y
        //iv. x,y-1
        
        // moving right
        // x+1,y
        if (m1.arr[posx + 1][posy] != '*' && m1.arr[posx + 1][posy] != v){
            if (m1.arr[posx + 1][posy] == 'C'){
                coin += 1;
            }
            (posx)++;
            push(&hd, posx, posy);
            m1.arr[posx][posy] = v;
            debugging();
        }

        // moving down
        // x,y+1
        else if (m1.arr[posx][posy + 1] != '*' && m1.arr[posx][posy + 1] != v){
            if (m1.arr[posx][posy + 1] == 'C'){
                coin+=1;
            }
            (posy)++;
            push(&hd, posx, posy);
            m1.arr[posx][posy] = v;
            debugging();
        }

       // moving left
        // x-1,y
        else if (m1.arr[posx - 1][posy] != '*' && m1.arr[posx - 1][posy] != v){
            if (m1.arr[posx - 1][posy] == 'C'){
                coin+=1;
            }
            (posx)--;
            push(&hd, posx, posy);
            m1.arr[posx][posy] = v;
            debugging();
        }

        // moving up
        // x,y-1
        else if (m1.arr[posx][posy - 1] != '*' && m1.arr[posx][posy - 1] != v){
            if (m1.arr[posx][posy - 1] == 'C'){
                coin+=1;
            }
            (posy)--;
            push(&hd, posx, posy);
            m1.arr[posx][posy] = v;
            debugging();
            
        }

        else{
          pop( &hd);
          if (debugMode == TRUE){
          printf("(%d,%d) popped off the stack.\n", posx , posy);
          }
          if (isEmpty(hd) == 1){
            printf("This maze has no solution.\n");
            break;
          }
            posx = xpoint(hd);
            posy = ypoint(hd);
        }

    }
      if (isEmpty(hd) == 2){
      printf("The maze has a solution.\n");
      printf("The amount of coins collected: %d\n", coin);
      printf("The path from start to end: \n");
      displayStack(hd);
      }

      clearAll(&hd);






  /*Coin positions are marked by 'c' in the input file
    They should be marked by C in the maze*/

  /*Close the file*/
   fclose(src);
}

