/*  THIS PROGRAM FIGURES OUT HOW MANY SOLUTIONS WILL BE HAD, WITH THESE 3 REGIONS FILLED IN...
  
  LATER, WE'LL RUN A PROGRAM TO PRINT THE POSSIBLE PERMUTATIONS, OF THESE FIRST THREE REGIONS, AND GIVE
    US THE COUNT, WHICH I BELIEVE TO BE 9!*6!*(3!^4)= 338,610,585,600.....
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
    
    
    printf("THIS PROGRAM WILL TAKE SIX DAYS TO RUN!!!!\n");
    
    setupTables();
    setupMultipleTable();
    
    multAnsTable[0][0] = 6;
    multAnsTable[0][1] = 9;
    multAnsTable[0][2] = 7;
    multAnsTable[0][3] = 5;
    multAnsTable[0][4] = 1;
    multAnsTable[0][5] = 2;
    multAnsTable[0][6] = 3;
    multAnsTable[0][7] = 4;
    multAnsTable[0][8] = 8;        
    multAnsTable[1][0] = 5;
    multAnsTable[1][1] = 8;
    multAnsTable[1][2] = 2;
    multAnsTable[1][3] = 9;
    multAnsTable[1][4] = 4;
    multAnsTable[1][5] = 3;
    multAnsTable[1][6] = 6;
    multAnsTable[1][7] = 1;
    multAnsTable[1][8] = 7;
    multAnsTable[2][0] = 4;
    multAnsTable[2][1] = 1;
    multAnsTable[2][2] = 3;
    multAnsTable[2][3] = 6;
    multAnsTable[2][4] = 7;
    multAnsTable[2][5] = 8;
    multAnsTable[2][6] = 9;
    multAnsTable[2][7] = 2;
    multAnsTable[2][8] = 5;
    
    sub = 27;
 
    //54 for statements ............................................
    
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
    
    
    
    //54 for statements ......
         
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
      --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } 
      --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } 
      --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } 
      --sub; } --sub; } 
      
   
    
//    EIGHTYONERIGHTBRACKETS
     
    // 54 ending brackets for the 54 for statements.........
    
    //print the number of possible Sudoku solutions...........
    printf("THE NUMBER OF POSSIBLE SUDOKU SOLUTIONS FOR THIS PERMUTATION IS:\n");
    printf("\t\t %d BILLION %lld ...\n", billions, regCount);
    printf("THE ACTUAL NUMBER OF POSSIBLE SOLUTIONS, IS THIS NUMBER MULTIPLIED BY THE NUMBER OF \
THREE REGIONS PERMUTATIONS, WHICH IS 948,109,639,680...\n");
    
    system("pause");
    system("pause");
    system("pause");
    
    
    return 0;
}
    
    


