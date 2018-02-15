/*  THIS PROGRAM FIGURES OUT HOW MANY SOLUTIONS WILL BE HAD, WITH THE TOP SIX ROWS FILLED IN...
  THEY ARE FILLED IN WITH: 123456789, 456789123, 789123456, 214365897, 365897214, 897214365 ....
  I'M HOPING THAT THE RESULT WILL AID IN CALCULATING A MATHEMATICAL EXPLANATION, FOR THE NUMBER OF SOLUTIONS FOUND...
*/
#include <stdio.h>
#include <stddef.h>

//GLOBAL VARIABLES .................
int multipleTable[81][3];   //[0]-cand, [1]-y co-ord, [2]-x co-ord....
int multAnsTable[9][9];   //holds possible cands for all 81 cells, (between 1-9, for all 81 cells)....
int regionalAnswerTable[9][9];   //holds region for each y, x.....

struct point
{
       int row;
       int column;
} regionalDispatchTable[9][9];

int sub, errCode;

//FUNCTION DECLARATIONS .............
void setupTables (void);
void setupMultipleTable (void);
void checkMultAnsTable (int y, int x);
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

//setupMultipleTable Function ..............
void setupMultipleTable (void)
{
     int x, y;
     
     sub = 0;
     
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x, ++sub )
         {
             multipleTable[sub][1] = y;
             multipleTable[sub][2] = x;
         } // ends for x ..... ends for y ...........
         
     return;
}

//checkMultAnsTable Function ................
void checkMultAnsTable (int y, int x)
{
     int xx, yy, region, a, r, c;
     
     //check row for uniqueness....................
     for ( xx = 0; xx < x; ++xx )
     {
         if ( multAnsTable[y][xx] != multAnsTable[y][x] )
            continue;
                    
         ++errCode;
         return;
     } // ends for xx.................................
             
     //check column for uniqueness....................
     for ( yy = 0; yy < y; ++yy )
     {
         if ( multAnsTable[yy][x] != multAnsTable[y][x] )
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
                    
         if ( multAnsTable[r][c] != multAnsTable[y][x] )
            continue;
                    
         ++errCode;
         return;
     } // ends for a.............
          
     return;
}

//main Function .........................
int main (void)
{
    int x, y, xx, yy, billions = 0;
    long long int regCount = 0;
    
    
    printf("THIS PROGRAM IS RUNNING!!!!\n");
    
    setupTables();
    setupMultipleTable();
    
    for ( sub = 0; sub < 9; ++sub )
        multAnsTable[0][sub] = (sub + 1);
        
    multAnsTable[1][0] = 4;
    multAnsTable[1][1] = 5;
    multAnsTable[1][2] = 6;
    multAnsTable[1][3] = 7;
    multAnsTable[1][4] = 8;
    multAnsTable[1][5] = 9;
    multAnsTable[1][6] = 1;
    multAnsTable[1][7] = 2;
    multAnsTable[1][8] = 3;
    multAnsTable[2][0] = 7;
    multAnsTable[2][1] = 8;
    multAnsTable[2][2] = 9;
    multAnsTable[2][3] = 1;
    multAnsTable[2][4] = 2;
    multAnsTable[2][5] = 3;
    multAnsTable[2][6] = 4;
    multAnsTable[2][7] = 5;
    multAnsTable[2][8] = 6;
    multAnsTable[3][0] = 2;
    multAnsTable[3][1] = 1;
    multAnsTable[3][2] = 4;
    multAnsTable[3][3] = 3;
    multAnsTable[3][4] = 6;
    multAnsTable[3][5] = 5;
    multAnsTable[3][6] = 8;
    multAnsTable[3][7] = 9;
    multAnsTable[3][8] = 7;
    multAnsTable[4][0] = 3;
    multAnsTable[4][1] = 6;
    multAnsTable[4][2] = 5;
    multAnsTable[4][3] = 8;
    multAnsTable[4][4] = 9;
    multAnsTable[4][5] = 7;
    multAnsTable[4][6] = 2;
    multAnsTable[4][7] = 1;
    multAnsTable[4][8] = 4;
    multAnsTable[5][0] = 8;
    multAnsTable[5][1] = 9;
    multAnsTable[5][2] = 7;
    multAnsTable[5][3] = 2;
    multAnsTable[5][4] = 1;
    multAnsTable[5][5] = 4;
    multAnsTable[5][6] = 3;
    multAnsTable[5][7] = 6;
    multAnsTable[5][8] = 5;
    
    sub = 54;
 
    //27 for statements ............................................
    
    
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
        ++sub;
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0] ) 
    { 
        y = multipleTable[sub][1]; 
        x = multipleTable[sub][2]; 
        multAnsTable[y][x] = multipleTable[sub][0];
        errCode = 0;
        checkMultAnsTable(y,x);
        if ( errCode )
           continue;
    
    
    
    //27 for statements ......
         
         //add to regCount --- check to see if == billion ----
         ++regCount;
    
         if ( regCount == 1000000000 )
         {
            ++billions;
            regCount = 0;
            printf("SO FAR %d BILLION SOLUTIONS FOUND!!!!\n", billions);
         } // ends if regCount .......
         
         if ( regCount == 1 )
            printf("****\n");        //debug purposes
         
    
      } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } 
      --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } 
      --sub; } --sub; } --sub; } --sub; } --sub; } 
      
   
    
//    EIGHTYONERIGHTBRACKETS
     
    // 27 ending brackets for the 27 for statements.........
    
    //print the number of possible Sudoku solutions...........
    printf("THE NUMBER OF POSSIBLE SUDOKU SOLUTIONS FOR THIS PERMUTATION IS:\n");
    printf("\t\t %d BILLION %lld ...\n", billions, regCount);
        
    system("pause");
    system("pause");
    system("pause");
    
    
    return 0;
}
    
    


