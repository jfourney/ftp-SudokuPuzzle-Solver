//biLocationSolutions Processing for Sudoku. ********************

/* First, a cell that has a biLocation is set..If this solves the puzzle, this is
  the solution for that cell, and for the puzzle. If the setting leads to an impossibility,
  all the connected pairs, in the row, column, and region are equal to this (z + 1)...
  If the setting gets stuck, all the tables are saved, and the connected pairs, in the row,
  column, and region are set.
    If these settings solve the puzzle, this is the solution for the cells, and for the
  puzzle. If these settings lead to an impossibility, the prior setting, that got stuck,
  is the answer to that cell.
    But, if both these setting get stuck, the answer tables to both sttings are compared,
  and any cells that are equal, are  kept and are part of the final solution.
    Then, if any changes- start back at square 1, else continue to next cell with biLocation
  for that particular candidate.........
*/   
/*
//Function Declarations ********************************
void setupBiLocationTable (void);
void biLocationSolutions (void);
*/

//setupBiLocationTable Function **********************
void setupBiLocationTable (void)
{
     int x, y, z, xx, yy, aa, h, region, r, c, a, xxx, yyy, aaa;
     
     //Initialize biLocationTables....................
     for ( z = 0; z < 9; ++z )
         for ( y = 0; y < 9; ++y )
             for ( x = 0; x < 9; ++x )
                 for ( h = 0; h < 3; ++h )
                 {
                     biLocationTable[z][y][x][h] = 9;
                     firstBLT[z][y][x][h] = 9;
                 } //ends for h....ends for x.... ends for y.... ends for z....
     
     for ( z = 0; z < 9; ++z )
     {
         for ( y = 0; y < 9; ++y )
         {
             xx = 9;
             for ( x = 0; ((xx == 9) && (x < 8)); ++x )
             {
                 if ( !checkTable[z][y][x] )
                    continue;
                    
                 //check row to see if only one other cand exists....
                 if ( biLocationTable[z][y][x][0] == 9 )
                 {
                      xxx = 9;
                      
                      for ( xx = (x + 1); xx < 9; ++xx )
                      {
                          if ( !checkTable[z][y][xx] )
                             continue;  //no cand here.....
                             
                          if ( xxx != 9 )
                             break;  //more than 2 cands in row...
                             
                          xxx = xx;
                      } //ends for xx.............
                      
                      if ( (xx == 9) && (xxx != 9) )
                      {
                           firstBLT[z][y][x][0] = xxx;
                           biLocationTable[z][y][x][0] = xxx;
                           biLocationTable[z][y][xxx][0] = x;
                      } // ends if xx .........
                 } //ends if biLocation.......
             } //ends for x.........
         } // ends for y........
         
         for ( x = 0; x < 9; ++x )
         {
             yy = 9;
             
             for ( y = 0; ((yy == 9) && (y < 8)); ++y )
             {
                 if ( !checkTable[z][y][x] )
                    continue;
                       
                 //check column to see if only one other cand exists....
                 if ( biLocationTable[z][y][x][1] == 9 )
                 {
                      yyy = 9;
                      
                      for ( yy = (y + 1); yy < 9; ++yy )
                      {
                          if ( !checkTable[z][yy][x] )
                             continue;  //no cand here.....
                             
                          if ( yyy != 9 )
                             break;  //more than 2 cands in column...
                             
                          yyy = yy;
                      } //ends for yy.............
                      
                      if ( (yy == 9) && (yyy != 9) )
                      {
                           firstBLT[z][y][x][1] = yyy;
                           biLocationTable[z][y][x][1] = yyy;
                           biLocationTable[z][yyy][x][1] = y;
                      } // ends if yy .........
                 } //ends if biLocation.......
             } // ends for y...............
         } // ends for x.................. 
                 
         for ( region = 0; region < 9; ++region )
         {
             aa = 9;
             aaa = 9;
                     
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                         
                 if ( !checkTable[z][r][c] )
                    continue;  //use only cells with cand....
                            
                 //check region to see if only 1 other cand exists....
                 if ( aa == 9 )
                    aa = a;   // first cell with cand....
                 else
                 {
                     if ( aaa == 9 )
                        aaa = a; //second cell with cand...
                     else
                         break;  //more than 2 cands in region...
                 } // ends if else aa........
             } // ends for a............
             
             if ( (a == 9) && (aa != 9) )
             {
                  r = regionalDispatchTable[region][aa].row;
                  c = regionalDispatchTable[region][aa].column;
                  firstBLT[z][r][c][2] = aaa;
                  biLocationTable[z][r][c][2] = aaa;
                  
                  r = regionalDispatchTable[region][aaa].row;
                  c = regionalDispatchTable[region][aaa].column;
                  biLocationTable[z][r][c][2] = aa;
             } // ends if a....
         } // ends for region.............
     } //ends for z ............
                  
     return;
}

//biLocationSolutions Function ************************************
void biLocationSolutions (void)
{
     int x, y, z, xx, zz, region, r, c, a;
     
   BEGIN:    //ADDED.........
     if ( !dimension )
     {
          //Move regular tables into dimTables[0]..............
          for ( y = 0; y < 9; ++y )
              for ( x = 0; x < 9; ++x )
              {
                  dimAnswerTable[0][y][x] = answerTable[y][x];
                  dimCheckRemainderTable[0][y][x] = checkRemainderTable[y][x];
                  
                  for ( z = 0; z < 9; ++z )
                      dimCheckTable[0][z][y][x] = checkTable[z][y][x];
              } // ends for x...ends for y............
          
          dimAnswersSolved[0] = answersSolved;
          
//          printAnswerTable();   //debug purposes...............
//          fprintCheckTable();  //debug purposes.............

            
          if ( holdX == (-1) )
             setupBiLocationTable ();
             
          //Find a biLocation...starting with the next cell, or restarting, etc...
          xx = ( holdX + 1);
          
          for ( z = holdZ; z < 9; ++z )
          for ( y = holdY; y < 9; ++y )
          {
              for ( x = xx; x < 9; ++x )
              {
                  aBLT = biLocationTable[z][y][x][0];
                  bBLT = biLocationTable[z][y][x][1];
                  cBLT = biLocationTable[z][y][x][2];
                  fABLT = firstBLT[z][y][x][0];
                  fBBLT = firstBLT[z][y][x][1];
                  fCBLT = firstBLT[z][y][x][2];
                  
                  if ( (fABLT == 9) && (fBBLT == 9) && (fCBLT == 9) )
                     continue;  // no connected pairs here.............
                      
                  //found a connected pair(s) at [z,y,x]...........
                  //Set [y][x] to (z + 1)...........
                  for ( zz = 0; zz < 9; ++zz )
                      checkTable[zz][y][x] = 0;
                      
                  checkTable[z][y][x] = (z + 1);
                  checkRemainderTable[y][x] = 1;
                  ++changes;
                  printf("The value at [%d][%d], was set to %d.in biLocationSolutions..\t", y, x, (z + 1));
                  holdZ = z;
                  holdY = y;
                  holdX = x;
                  dimension = 3;
                  
                  return;
              } // ends for x................
              
              xx = 0;
          } //ends for y..ends for z............
              
          printf("Ran out of biLocations....\n");   // debug purposes............
          system("pause");
                    
          biLocation = 2;
          biValue = 1;
          holdY = 0; holdX = (-1);
          //++changes;
          
          //ran out of biLocations, return........
          return;
              
     } //ends if ( !dim.... ***************************
     
     //Processing if dimension == 3..................
     if ( dimension == 3 )
     {
  //        printAnswerTable();   //debug purposes...............
  //        fprintCheckTable();  //debug purposes.............
  //        printf("errCode = %d............\t", errCode);    //debug purposes
          
          if ( errCode == 1 )
          {
               //All the connected pairs are equal to the candidate, not[y,x] (eliminationA)..
               
               //first move dimTables[0], back into regular tables..............
               for ( y = 0; y < 9; ++y )
                   for ( x = 0; x < 9; ++x )
                   {
                       answerTable[y][x] = dimAnswerTable[0][y][x];
                       checkRemainderTable[y][x] = dimCheckRemainderTable[0][y][x];
                       
                       for ( z = 0; z < 9; ++z )
                           checkTable[z][y][x] = dimCheckTable[0][z][y][x];
                   } //ends for z.... ends for x..... ends for y..............
               
               answersSolved = dimAnswersSolved[0];
               
               //set all connected pairs to cand.......
               
               //check row.............
               z = holdZ;
               y = holdY;
               x = holdX;
               aBLT = biLocationTable[z][y][x][0];
               bBLT = biLocationTable[z][y][x][1];
               cBLT = biLocationTable[z][y][x][2];
               if ( aBLT != 9)
               {
                  for ( zz = 0; zz < 9; ++zz )
                      checkTable[zz][y][aBLT] = 0;
                   
                   checkTable[z][y][aBLT] = (z + 1);
                   checkRemainderTable[y][aBLT] = 1;
                   ++changes;
                   printf("The value at [%d][%d] is equal to %d (eliminationA).in BiLocationSolutionsRow.\t", y, aBLT, (z + 1));
               } //ends if aBLT.........
               
               //check column.............
               if ( bBLT != 9)
               {
                  for ( zz = 0; zz < 9; ++zz )
                      checkTable[zz][bBLT][x] = 0;
                   
                   checkTable[z][bBLT][x] = (z + 1);
                   checkRemainderTable[bBLT][x] = 1;
                   ++changes;
                   printf("The value at [%d][%d] is equal to %d (eliminationA).in BiLocationSolutionsCol.\t", bBLT, x, (z + 1));
               } //ends if bBLT.........
               
               //check region.............
               if ( cBLT != 9)
               {
                  region = regionalAnswerTable[y][x];
                  r = regionalDispatchTable[region][cBLT].row;
                  c = regionalDispatchTable[region][cBLT].column;
                  
                  if ( (r != y) || (c != aBLT) )
                      if ( (r != bBLT) || (c != x) )
                      {
                         for ( zz = 0; zz < 9; ++zz )
                             checkTable[zz][r][c] = 0;
                             
                         checkTable[z][r][c] = (z + 1);
                         checkRemainderTable[r][c] = 1;
                         ++changes;
                         printf("The value at [%d][%d] is equal to %d (eliminationA).in BiLocationSolutionsReg.\t", r, c, (z + 1));
                      } // ends if r ... if r........
               } //ends if cBLT.........
               
               holdZ = 0;
               holdY = 0;
               holdX = -1;
               dimension = 0;
               errCode = 0;
               biLocation = 1;
               
               return;
          } //ends if ( errCode...............
               
               //Solution using partA got stuck.......
               
               
               //deBug();  //debug purposes.
               
               //move tables from partA (now in regular tables), into dimTables[1].....
               for ( y = 0; y < 9; ++y ) 
                   for ( x = 0; x < 9; ++x )
                   {
                       dimAnswerTable[1][y][x] = answerTable[y][x];
                       dimCheckRemainderTable[1][y][x] = checkRemainderTable[y][x];
                       
                       for ( z = 0; z < 9;++z )
                           dimCheckTable[1][z][y][x] = checkTable[z][y][x];
                   }  //ends for z... ends for x..... ends for y...............
                   
               dimAnswersSolved[1] = answersSolved;
               
                             
               //Move dimTables[0], back into regular tables..............
               for ( y = 0; y < 9; ++y )
                   for ( x = 0; x < 9; ++x )
                   {
                       answerTable[y][x] = dimAnswerTable[0][y][x];
                       checkRemainderTable[y][x] = dimCheckRemainderTable[0][y][x];
                       
                       for ( z = 0; z < 9; ++z )
                           checkTable[z][y][x] = dimCheckTable[0][z][y][x];
                   } //ends for z.... ends for x..... ends for y..............
               
               answersSolved = dimAnswersSolved[0];
               
               //set the connected pairs to the candidate...return.............
               //for row.....
               if ( aBLT != 9)
               {
                  for ( z = 0; z < 9; ++z )
                      checkTable[z][holdY][aBLT] = 0;
                   
                   checkTable[holdZ][holdY][aBLT] = (holdZ + 1);
                   checkRemainderTable[holdY][aBLT] = 1;
                   printf("The value at [%d][%d] was set to %d.in BiLocationSolutionsRow.\t", holdY, aBLT, (holdZ + 1));
               } // ends if aBLT.........
               
               //for column.....
               if ( bBLT != 9)
               {
                  for ( z = 0; z < 9; ++z )
                      checkTable[z][bBLT][holdX] = 0;
                   
                   checkTable[holdZ][bBLT][holdX] = (holdZ + 1);
                   checkRemainderTable[bBLT][holdX] = 1;
                   printf("The value at [%d][%d] was set to %d.in BiLocationSolutionsCol.\t", bBLT, holdX, (holdZ + 1));
               } // ends if bBLT.........
               
               //for region.....
               if ( cBLT != 9)
               {
                  region = regionalAnswerTable[holdY][holdX];
                  r = regionalDispatchTable[region][cBLT].row;
                  c = regionalDispatchTable[region][cBLT].column;
                  
                  if ( (r != holdY) || (c != aBLT) )
                     if ( (r != bBLT) || (c != holdX) )
                     {
                        for ( z = 0; z < 9; ++z )
                            checkTable[z][r][c] = 0;
                   
                        checkTable[holdZ][r][c] = (holdZ + 1);
                        checkRemainderTable[r][c] = 1;
                        printf("The value at [%d][%d] was set to %d.in BiLocationSolutionsReg.\t", r, c, (holdZ + 1));
                   } // ends if r.....if r.......
               } // ends if cBLT.........
               
               
               
               ++changes;
               dimension = 4;
                                             
               return;
     } //ends if ( dimension == 3............................................
     
     //dimension == 4..............................
     
//     printAnswerTable();   //debug purposes...............
//     fprintCheckTable();  //debug purposes.............
//     printf("errCode = %d,,dimension = %d...\t", errCode, dimension);    //debug purposes
     
     if ( errCode == 1 )
     {
        // partA is part of the solution (eliminationB).....
               
        //first move dimTables[1], back into regular tables..............
        for ( y = 0; y < 9; ++y )
            for ( x = 0; x < 9; ++x )
            {
                answerTable[y][x] = dimAnswerTable[1][y][x];
                checkRemainderTable[y][x] = dimCheckRemainderTable[1][y][x];
                       
                for ( z = 0; z < 9; ++z )
                    checkTable[z][y][x] = dimCheckTable[1][z][y][x];
            } //ends for z.... ends for x..... ends for y..............
               
        answersSolved = dimAnswersSolved[1];
        
        printf("The value at [%d][%d] is equal to %d (eliminationB).inBiLocationSolutions.\t", holdY, holdX, (holdZ + 1));
 
        dimension = 0;
  //      ++changes;
        holdZ = 0;       
        holdY = 0;         
        holdX = -1;
        errCode = 0;
        biLocation = 1;
        
        goto BEGIN;         
        
  //      return;            
        
     } //ends if ( errCode...............    
     
     //BOTH BILOCATIONS GOT STUCK...COMPARE THE ANSWER TABLES OF EACH, FOR EQUALITY... ALL ANSWERS
     //THAT ARE EQUAL, ARE PART OF THE ULTIMATE SOLUTION....
     
     //VALUES FOR PARTA, ARE IN DIM[1]TABLES...VALUES FOR PARTB, ARE IN REGULAR TABLES.....
     //ORIGINAL VALUES ARE IN DIM[0]TABLES, WHICH WOULD BE CHANGED, AND WHEN DONE, 
     //MOVED TO THE REGULAR TABLES...........
     
     //COMPARE THE ANSWER TABLES...............................
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             if ( dimAnswerTable[0][y][x] )
                continue;
                
             if ( !answerTable[y][x] )
                continue;
                
             if ( dimAnswerTable[1][y][x] != answerTable[y][x] )
                continue;
                
             //The answerTables for valueA, and valueB, are equal for a particular cell...
             for ( z = 0; z < 9; ++z )
                 dimCheckTable[0][z][y][x] = 0;
                 
             dimCheckTable[0][(answerTable[y][x] - 1)][y][x] = answerTable[y][x];
             dimCheckRemainderTable[0][y][x] = 1;
             ++changes;
             printf("The value at [%d][%d] is equal to %d (comparison).in BiLocationSolutions..\t", y, x, answerTable[y][x]);
         } // ends for x..... for y..............
         
         //Move dim[0]Tables, back into regular tables..................
         for ( y = 0; y < 9; ++y )
            for ( x = 0; x < 9; ++x )
            {
                answerTable[y][x] = dimAnswerTable[0][y][x];
                checkRemainderTable[y][x] = dimCheckRemainderTable[0][y][x];
                       
                for ( z = 0; z < 9; ++z )
                    checkTable[z][y][x] = dimCheckTable[0][z][y][x];
            } //ends for z.... ends for x..... ends for y..............
               
        answersSolved = dimAnswersSolved[0];
        
        //if changes................
        dimension = 0;
        if ( changes )
        {
             holdY = 0;
             holdX = -1;
             holdZ = 0;
             biLocation = 1;
        }
        else
        {
            printf("None of the biLocations for candidate (%d), provided any solutions, at [%d][%d]...\t", \
               (holdZ + 1), holdY, holdX);
            ++changes;    // ends if changes...........
        } //ends if else (changes)...........
        
     return;
}
         

