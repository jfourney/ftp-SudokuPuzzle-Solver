//THIS PROGRAM, WILL ENTER IN A KNOWN SOLUTION TO SUDOKU. THE ANSWERS WILL BE CONVERTED, ELEMENT BY ELEMENT,
//SO THAT THE FIRST ROW IS 123456789 ....IF THIS PROGRAM IS RUN A NUMBER OF TIMES AND NO ERROR OCCURS, THEN MY 
//PLUG-IN THEORY WAS CORRECT, AND I WILL BE ABLE TO OBTAIN THE ENTIRE SOLUTION TABLE FOR SUDUKO, IN A HALF TERABYTE..

#include <stdio.h>
#include <stddef.h>

//GLOBAL VARIABLES .................
int answerTable[9][9], newAnsTable[9][9];
int regionalAnswerTable[9][9];   //holds region for each y, x.....

struct point
{
       int row;
       int column;
} regionalDispatchTable[9][9];

int errCode;

//FUNCTION DECLARATIONS .............
void setupTables (void);
void setupAnswerTable (void);
void setupNewAnsTable (void);
void checkNewAnsTable (void);
void printNewAnsTable (void);
int main (void);

//setupTables Function ....................
void setupTables (void)
{
     int x, y, region, a;
     
     // Initialize regionalAnswerTable ******************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             regionalAnswerTable[y][x] = ( 3 * (y / 3)) + (x / 3);
             
     // Initialize regionalDispatchTable ****************************************
     for ( region = 0; region < 9; ++region )
     {
         a = 0;
         
         for ( y = 0; y < 9; ++y )
             for ( x = 0; x < 9; ++x )
                 if ( regionalAnswerTable[y][x] == region )
                 {
                      regionalDispatchTable[region][a].row = y;
                      regionalDispatchTable[region][a].column = x;
                      ++a;
                 } // ends if rAT .......ends for x.... ends for y ............
         
     } // ends for region ........................
     
     return;
}

//SETUP ANSWER TABLE ......................
void setupAnswerTable (void)
{
     int x, y, z, answer[9];
     
     //Loop to enter the answers.......... *********************
      
     //read in all 81 answers. ***********
         
     for ( y = 0; y < 9; ++y )
     {
         printf("Read in row# %d of the puzzle.\n", (y + 1) );
                  
         scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d", &answer[0], &answer[1], &answer[2], &answer[3], &answer[4], \
                                              &answer[5], &answer[6], &answer[7], &answer[8]);
                                              
         for ( x = 0; x < 9; ++x )
             if ( (answer[x] < 1) || (answer[x] > 9) )
             {
                  printf("answer[%d] = %d\n", x, answer[x]);
                  printf("\nERROR, answer not between 1 and 9. START ALL OVER!!!!\n");
                  errCode = 1;
                  return;
             }          
             else  answerTable[y][x] = answer[x];
              
                
         
     } // ends for y..........
     
     return;
}

//setupNewAnsTable Function ..............
void setupNewAnsTable (void)
{
     int y, x, xx, oldAnswer, newAnswer;
     
     for ( xx = 0; xx < 9; ++xx )
     {
         newAnswer = (xx + 1);
         oldAnswer = answerTable[0][xx];
         
         for ( y = 0; y < 9; ++y )
             for ( x = 0; x < 9; ++x )
                 if ( answerTable[y][x] == oldAnswer )
                    newAnsTable[y][x] = newAnswer;
     }// ends for xx..........
     
     return;
}


//checkNewAnsTable Function ................
void checkNewAnsTable (void)
{
  int xx, yy, region, a, r, c, y, x;
  
  for ( y = 0; y < 9; ++y )
   for ( x = 0; x < 9; ++x )
   {
     
     //check row for uniqueness....................
     for ( xx = 0; xx < x; ++xx )
     {
         if ( newAnsTable[y][xx] != newAnsTable[y][x] )
            continue;
                    
         ++errCode;
         return;
     } // ends for xx.................................
             
     //check column for uniqueness....................
     for ( yy = 0; yy < y; ++yy )
     {
         if ( newAnsTable[yy][x] != newAnsTable[y][x] )
            continue;
                    
         ++errCode;
            return;
     } // ends for yy.................................
             
     //check region for uniqueness....................
     region = regionalAnswerTable[y][x];
             
     for ( a = 0; a < 9; ++a )
     {
         r = regionalDispatchTable[region][a].row;
         c = regionalDispatchTable[region][a].column;
                 
         if ( (r == y) && (c == x) )
            break;
                    
         if ( newAnsTable[r][c] != newAnsTable[y][x] )
            continue;
                    
         ++errCode;
         return;
     } // ends for a.............
   } // ends for x...ends for y ............
          
     return;
}

//printNewAnsTable Function. ******************************************************
void printNewAnsTable (void)
{
     int x, y;
     
     //print answerTable. ************************************
     printf("Here's the newAnsTable.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", newAnsTable[y][x]);
             
         printf("\n");
     }
     

     
     return;
}

//main Function .........................
int main (void)
{
    setupTables();
    setupAnswerTable();
    
    if ( errCode )
       goto END;
       
    setupNewAnsTable();
    checkNewAnsTable();
    
    if ( errCode )
       printf("THERE IS A MAJOR FLAW, IN YOUR PLUG-IN THEORY....\n");
    else
    {
        printf("THIS IS A LEGITIMATE SOLUTION..GOOD LUCK...\n");
        printNewAnsTable();
    } // ends if errCode else....
    
    END:    
    system("pause");
        
    return 0;
}
    
