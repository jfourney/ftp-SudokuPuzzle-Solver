/*
   THIS HEADER FILE WILL CHECK FOR EVERY POSSIBLE SOLUTION TO THE PUZZLE. IF THE SOLUTION FOUND IS THE SAME AS THE ORIGINAL SOLUTION;
KEEP ON GOING.. IF THE SOLUTION FOUND IS DIFFERENT THAN THE ORIGINAL; WILL PRINT BOTH SOLUTIONS FOUND - STATING THAT IT IS NOT A
UNIQUE SOLUTION, AND QUIT...
   IF NO ORIGINAL SOLUTION WAS FOUND; THIS SOLUTION WILL BE THE ORIGINAL SOLUTION, AND WILL CONTINUE TO SEE IF THERE ARE MULTIPLE
SOLUTIONS AVAILABLE...
*/

/*
// Function Declarations .....................
void saveTables (void);
void setupMultipleTable (void);
void checkMultiple (void);
void checkMultAnsTable (int y, int x);
void compareAnsTables (void);
*/

//saveTables Function ....................
void saveTables (void)
{
     int x, y, z;
     
     //Move regular tables into dimTables[2]..............
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             dimAnswerTable[2][y][x] = answerTable[y][x];
             dimCheckRemainderTable[2][y][x] = checkRemainderTable[y][x];
                  
             for ( z = 0; z < 9; ++z )
                 dimCheckTable[2][z][y][x] = checkTable[z][y][x];
         } // ends for x...ends for y............
          
         dimAnswersSolved[2] = answersSolved;
          
         return;
}

//setupMultipleTable Function .....................
void setupMultipleTable (void)
{
     int x, y, z, zz, ss, sub;
     sub = 0;
     
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x, ++sub )
         {
             //if cell has an answer already..........
             if ( !dimCheckRemainderTable[2][y][x] )
             {
                  multipleTable[sub][0] = 1;
                  multipleTable[sub][2] = y;
                  multipleTable[sub][3] = x;
                  multipleTable[sub][4] = dimAnswerTable[2][y][x];
                  continue;
             } // ends if !dimCRT....................
             
             //if cell has no answer yet..........
             multipleTable[sub][0] = dimCheckRemainderTable[2][y][x];
             multipleTable[sub][2] = y;
             multipleTable[sub][3] = x;
             zz = 0; ss = 4;
             
             for ( z = 0; zz < multipleTable[sub][0]; ++z )
             {
                 if ( !dimCheckTable[2][z][y][x] )
                    continue;
                    
                 multipleTable[sub][ss] = dimCheckTable[2][z][y][x];
                 ++zz; ++ss;
             } // ends for z.........................
         } // ends for x..... ends for y..................
     
     return;
}


//checkMultAnsTable Function .............
void checkMultAnsTable (int y, int x)
{
     int xx, yy, region, a, r, c;
     
     //check row for uniqueness....................
     for ( xx = 0; xx < 9; ++xx )
     {
         if ( xx == x )
            continue;
         
         if ( xx < x )   
         {   if ( multAnsTable[y][xx] != multAnsTable[y][x] )
               continue;
         }
         else 
              if ( multAnsTable[y][xx] != dimAnswerTable[2][y][x] )
                 continue;  // ends if xx < x else .... 
                             
         ++errCode;
         return;
     } // ends for xx.................................
             
     //check column for uniqueness....................
     for ( yy = 0; yy < 9; ++yy )
     {
         if ( yy == y )
            continue;
         
         if ( yy < y )   
         {   if ( multAnsTable[yy][x] != multAnsTable[y][x] )
               continue;
         }
         else 
              if ( multAnsTable[yy][x] != dimAnswerTable[2][y][x] )
                 continue;  // ends if xx < x else .... 
                             
         ++errCode;
         return;
     } // ends for xx.................................
             
     //check region for uniqueness....................
     region = regionalAnswerTable[y][x];
             
     for ( a = 0; a < 9; ++a )
     {
         r = regionalDispatchTable[region][a].row;
         c = regionalDispatchTable[region][a].column;
                 
         if ( (r == y) && (c == x) )
            continue;
         
         if ( (r < y) || ( (r == y) && (x < c) ) )
         {           
             if ( multAnsTable[r][c] != multAnsTable[y][x] )
                continue;
         }
         else
             if ( multAnsTable[r][c] != dimAnswerTable[2][y][x] )
                continue; // ends if r < y... else ....
                             
         ++errCode;
         return;
     } // ends for a.............
          
     return;
}


//compareAnsTable Function ...........................
void compareAnsTables (void)
{
     int y, x;
          
     if ( !multiple )
     {
          //move multAnsTable[9][9] to answerTable[9][9]..........
          for ( y = 0; y < 9; ++y )
              for ( x = 0; x < 9; ++x)
                  answerTable[y][x] = multAnsTable[y][x];
                  
          ++multiple;
          return;
     } //ends if !Multiple...................
     
     //compare answerTables - if not equal - there's not a unique solution to the puzzle...
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             if ( multAnsTable[y][x] == answerTable[y][x] )
                continue;
                
             ++multiple;
             return;
         } // ends for x... ends for y........
         
     return;
} 
             
//checkMultiple Function ...............................
void checkMultiple (void)
{
     char character[4];     
     int x, y, c, cand, sub;
     
     setupMultipleTable();
     c = 0;  //debug purposes
     sub = 0;
     //81 for statements...........................................
     
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
         ++sub;
     for ( multipleTable[sub][1] = 0; multipleTable[sub][1] < multipleTable[sub][0]; ++multipleTable[sub][1] )  
     {
         y = multipleTable[sub][2]; 
         x = multipleTable[sub][3];
         cand = multipleTable[sub][(multipleTable[sub][1] + 4)]; 
         multAnsTable[y][x] = cand;
         errCode = 0;
         checkMultAnsTable(y,x);
         if ( errCode )
            continue;
     // 81 for statements      
         
     
         if (!c )                     //debug purposes
         {
            deBug();
            system("pause");
            ++c;
         }                            //debug purposes
                 
     compareAnsTables();
         
         
         if ( multiple == 1 )
         {
              for ( x = 0; x < 25; ++x )
                  printf("\n");
                  
              printf("A SOLUTION HAS BEEN FOUND!\n");
              printAnswerTable();
              
              printf("\n\nDO YOU NEED TO CHECK FOR MULTIPLE SOLUTIONS? ENTER Y or N!!!\n");
              
              scanf("%s", character);
                            
              if ( (character[0] == 'y') || (character[0] == 'Y') ) 
              {
                   for ( x = 0; x < 25; ++x )
                       printf("\n");
                   printf("CHECKING ALL POSSIBLE COMBINATIONS TO SEE IF THERE IS A MULTIPLE SOLUTION!!!\n");
                   printf("\n\nTHIS CAN TAKE DAYS(MILLENIUM), SO PLEASE WAIT !!!!!!!!!!\n");
                   
                   continue;
              }  
              else
              {
                  ++stop;
                  return;
              } // ends if character ....else ............
         } // ends if multiple == 1
         
         if ( multiple > 1 )
            return;
     
     //81 right brackets.......................       
     }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
     --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
                
    // 81 ending brackets for the for statements......
         
     return;
}
             
              
         
         
             
             
             
                  
     
                                              
