//biValueSolutions Processing for Sudoku. ********************

//INCLUDES THE COMPARISON OF THE BI-VALUE SOLUTIONS. IF ONE VALUE SOLVES THE PUZZLE,
//THAT IS THE SOLUTION FOR THAT CELL, AND FOR THE PUZZLE.  ON THE OTHER HAND, IF THAT 
//VALUE LEADS TO AN IMPOSSIBILITY, THE OTHER VALUE IS THE SOLUTION FOR THAT CELL, AND
//IS PART OF THE ULTIMATE SOLUTION.  IF BOTH VALUES LEAD TO STICKING POINTS; WE COMPARE
//ALL THE ANSWERS, IN THE RESPECTIVE ANSWER TABLES; AND ANY ANSWERS THAT ARE THE SAME,
//ARE PART OF THE ULTIMATE SOLUTION....................
/*
//Function Declarations ********************************
void setupBiValueTable (void);
void biValueSolutions (void);
*/

//setupBiValueTable Function **********************
void setupBiValueTable (void)
{
     int x, y, z, zz;
     
     //Initialize biValueTable....................
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( zz = 0; zz < 2; ++zz )
                 biValueTable[y][x][zz] = 0;
                 
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             if ( checkRemainderTable[y][x] != 2 )
                continue;
             
             zz = 0;
             for ( z = 0; zz < 2; ++z )
                 if ( checkTable[z][y][x] )
                 {
                      biValueTable[y][x][zz] = (z + 1);
                      ++zz;
                 } //ends if cT....ends for z...........
         } //ends for x.................
             
         return;
}

//biValueSolutions Function ************************************
void biValueSolutions (void)
{
     int x, y, z, xx, zz;
     
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
             setupBiValueTable ();
             
          //Find a biValue...starting with the next cell, or restarting, etc...
          xx = ( holdX + 1);
          
          for ( y = holdY; y < 9; ++y )
          {
              for ( (x = xx); x < 9; ++x )
              {
                  if ( !biValueTable[y][x][0] )
                     continue;
                     
                  valueA = biValueTable[y][x][0];
                  valueB = biValueTable[y][x][1];
                      
                  //Set the value to valueA, and return...........
                  for ( z = 0; z < 9; ++z )
                      checkTable[z][y][x] = 0;
                      
                  checkTable[(valueA - 1)][y][x] = valueA;
                  checkRemainderTable[y][x] = 1;
                  ++changes;
                  printf("The value at [%d][%d], was set to %d.in biValueSolutions..\t", y, x, valueA);
                  holdY = y;
                  holdX = x;
                  dimension = 1;
                  
                  return;
              } // ends for x................
              
              xx = 0;
          } //ends for y..............
              
          printf("Ran out of biValues....\n");   // debug purposes............
          system("pause");
                    
          if ( biLocation == 1 )
          {
               biValue = 2;
               holdY = 0; holdX = -1; holdZ = 0;
               dimension = 0; errCode = 0;
          } // ends if biL....
          
          //ran out of biValues, return........
          return;
              
     } //ends if ( !dim.... ***************************
     
     //Processing if dimension == 1..................
     if ( dimension == 1 )
     {
  //        printAnswerTable();   //debug purposes...............
  //        fprintCheckTable();  //debug purposes.............
  //        printf("errCode = %d............\t", errCode);    //debug purposes
          
          if ( errCode == 1 )
          {
               //valueB is part of the solution.....
               
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
               
               //set cell [holdY][holdX], to valueB........................
               for ( z = 0; z < 9; ++z )
                   checkTable[z][holdY][holdX] = 0;
                   
               checkTable[(valueB - 1)][holdY][holdX] = valueB;
               checkRemainderTable[holdY][holdX] = 1;
               ++changes;
               printf("The value at [%d][%d] is equal to %d (eliminationA).in BiValueSolutions.\t", holdY, holdX, valueB);
               holdY = 0;
               holdX = -1;
               dimension = 0;
               errCode = 0;
               biLocation = 1;
               
               return;
          } //ends if ( errCode...............
               
               //Solution using valueA got stuck.......
               
               
               //deBug();  //debug purposes.
               
               //move tables from valueA (now in regular tables), into dimTables[1].....
               for ( y = 0; y < 9; ++y ) 
                   for ( x = 0; x < 9; ++x )
                   {
                       dimAnswerTable[1][y][x] = answerTable[y][x];
                       dimCheckRemainderTable[1][y][x] = checkRemainderTable[y][x];
                       
                       for ( z = 0; z < 9; ++z )
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
               
               //set cell [holdY][holdX] to valueB........return.............
               for ( z = 0; z < 9; ++z )
                   checkTable[z][holdY][holdX] = 0;
                   
               checkTable[(valueB - 1)][holdY][holdX] = valueB;
               checkRemainderTable[holdY][holdX] = 1;
               ++changes;
               printf("The value at [%d][%d] was set to %d.in BiValueSolutions.\t", holdY, holdX, valueB);
               dimension = 2;
                              
               return;
     } //ends if ( dimension == 1............................................
     
     //dimension == 2..............................
     
//     printAnswerTable();   //debug purposes...............
//     fprintCheckTable();  //debug purposes.............
//     printf("errCode = %d,,dimension = %d...\t", errCode, dimension);    //debug purposes
     
     if ( errCode == 1 )
     {
        // valueA is part of the solution.....
               
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
        
        printf("The value at [%d][%d] is equal to %d (eliminationB).inBiValuSolutions.\t", holdY, holdX, valueA);
 
        dimension = 0;
  //      ++changes;       
        holdY = 0;         
        holdX = -1;
        errCode = 0;
        biLocation = 1;
        
        goto BEGIN;         
        
  //      return;            
        
     } //ends if ( errCode...............    
     
     //BOTH BI-VALUES GOT STUCK...COMPARE THE ANSWER TABLES OF EACH, FOR EQUALITY... ALL ANSWERS
     //THAT ARE EQUAL, ARE PART OF THE ULTIMATE SOLUTION....
     
     //VALUES FOR VALUEA, ARE IN DIM[1]TABLES...VALUES FOR VALUB, ARE IN REGULAR TABLES.....
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
             printf("The value at [%d][%d] is equal to %d (comparison).in BiValueSolutions..\t", y, x, answerTable[y][x]);
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
             biLocation = 1;
        }
        else
        {
            printf("Neither of the biValues(%d,%d), provided any solutions, at [%d][%d]...\t", \
               valueA, valueB, holdY, holdX);
            ++changes;    // ends if changes...........
        } //ends if else (changes)...........
        
     return;
}
         
