/*  THIS PROGRAM FIGURES OUT THE NUMBER OF PERMUTATIONS FOR ROWS 2 AND 3 COMBINED-
  ASSUMING ROW 1 IS 123456789...I BELIEVE THIS NUMBER IS 933,120....
    THE ACTUAL NUMBER OF PERMUTATIONS FOR THE FIRST 3 ROWS (REGIONS) IS: THIS NUMBER
  MULTIPLIED BY THE NUMBER OF PERMUTATIONS OF THE FIRST ROW WHICH WAS 362,880.....
    THE TOTAL NUMBER OF SUDOKU SOLUTIONS WOULD BE THAT NUMBER MULTIPLIED BY THE
  'NUMBER SOLUTIONS THREE REGIONS, WHICH COULD TAKE SEVERAL MONTHS TO DETERMINE...
*/
#include <stdio.h>
#include <stddef.h>

//GLOBAL VARIABLES .................
int multipleTable[27][3];   //[0]-cand, [1]-y co-ord, [2]-x co-ord....
int multAnsTable[3][9];   //holds possible cands for all 81 cells, (between 1-9, for all 81 cells)....
int regionalAnswerTable[3][9];   //holds region for each y, x.....

struct point
{
       int row;
       int column;
} regionalDispatchTable[3][9];

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
     for ( y = 0; y < 3; ++y )
         for ( x = 0; x < 9; ++x )
             regionalAnswerTable[y][x] = ( 3 * (y / 3)) + (x / 3);
             
     // Initialize regionalDispatchTable ****************************************
     for ( region = 0; region < 9; ++region )
     {
         a = 0;
         
         for ( y = 0; y < 3; ++y )
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
     
     for ( y = 0; y < 3; ++y )
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
    
    printf("THIS PROGRAM WILL TAKE SOME 50 DAYS TO RUN...\n");
    printf("THERE SHOULD BE 948,109,639,680 PERMUTATIONS, TOTAL...\n");
        
    setupTables();
    setupMultipleTable();
    
    
    sub = 0;
 
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
    for ( multipleTable[sub][0] = 1; multipleTable[sub][0] < 10; ++multipleTable[sub][0], \
            printf("PERMUTATIONS (col. 3) FOR THE NUMBERS UP TO AND INCLUDING %d ARE: \n\t %d BILLION %lld ...\n", \
             (multipleTable[sub][0] - 1), billions, regCount)  ) 
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
         
         //add to regCount --- 
         ++regCount;
    
         if ( regCount == 1000000000 )
         {
              ++billions;
              regCount = 0;
              printf("SO FAR %d BILLION PERMUTATIONS FOUND, ON FIRST THREE ROWS...\n", billions);
         } // ends if regCount.....
    
      } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
      --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } 
      --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
      
    // 27 ending brackets for the 27 for statements.........
    
    //print the number of permutations of the first three rows...........
    printf("THE NUMBER OF PERMUTATIONS FOR THE FIRST THREE ROWS COMBINED IS: \n");
    printf("\t %d BILLION %lld ....\n", billions, regCount);
    
    
    system("pause");
    system("pause");
    system("pause");
    
    
    return 0;
}
    
    


