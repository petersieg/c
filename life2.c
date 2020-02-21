#include <stdio.h>

#include <stdlib.h>



#define ROWS 20

#define COLS 40



#define GETCOL(c) (c%COLS)

#define GETROW(c) (c/COLS)



#define D_LEFT(c)   ((GETCOL(c) == 0) ? (COLS-1) :  -1)

#define D_RIGHT(c)  ((GETCOL(c) == COLS-1) ? (-COLS+1) :  1)

#define D_TOP(c)   ((GETROW(c) == 0) ? ((ROWS-1) * COLS) : -COLS)

#define D_BOTTOM(c) ((GETROW(c) == ROWS-1) ? (-(ROWS-1) * COLS) : COLS)



typedef struct _cell

{

   struct _cell* neighbour[8];

   char curr_state;

   char next_state;

} cell;



typedef struct 

{

   int rows;

   int cols;

   cell* cells;

} world;



void evolve_cell(cell* c)

{

   int count=0, i;

   for (i=0; i<8; i++)

   {

      if (c->neighbour[i]->curr_state) count++;

   }

   if (count == 3 || (c->curr_state && count == 2)) c->next_state = 1;

   else c->next_state = 0;

}



void update_world(world* w)

{

   int nrcells = w->rows * w->cols, i;

   for (i=0; i<nrcells; i++)

   {

      evolve_cell(w->cells+i);

   }

   for (i=0; i<nrcells; i++)

   {

      w->cells[i].curr_state = w->cells[i].next_state;

      if (!(i%COLS)) printf("\n");

      printf("%c",w->cells[i].curr_state ? '*' : ' ');

   }

}



world* init_world()

{

   world* result = (world*)malloc(sizeof(world));

   result->rows = ROWS;

   result->cols = COLS;

   result->cells = (cell*)malloc(sizeof(cell) * COLS * ROWS);

   

   int nrcells = result->rows * result->cols, i;

   

   for (i = 0; i < nrcells; i++)

   {

      cell* c = result->cells + i;

         

      c->neighbour[0] = c+D_LEFT(i);

      c->neighbour[1] = c+D_RIGHT(i);

      c->neighbour[2] = c+D_TOP(i);

      c->neighbour[3] = c+D_BOTTOM(i);

      c->neighbour[4] = c+D_LEFT(i)   + D_TOP(i);

      c->neighbour[5] = c+D_LEFT(i)   + D_BOTTOM(i);

      c->neighbour[6] = c+D_RIGHT(i)  + D_TOP(i);

      c->neighbour[7] = c+D_RIGHT(i)  + D_BOTTOM(i);

      

      c->curr_state = rand() % 2;

   }

   return result;

}



int main()

{

   srand(3);

   world* w = init_world();

   

   while (1)

   {

      system("clear");

      update_world(w);

      getchar();

   }

}

