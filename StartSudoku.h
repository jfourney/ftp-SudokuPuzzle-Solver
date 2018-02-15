// Holds the functions to begin the game. ********

// Holds only the functions. No variable declarations, Function Declarations,
//  or any include files. All those items are include in the Header File, and
// the main file. If include again, that would break the double inclusion rule.

// THIS HEADER FILE, CONTAINS THE   setupTables, and beginGame Functions. ****

//setupTables Function **************************************************
void setupTables (void)
{
     // Initialize checkTable **************************************************
     int x, y, z;
     
     for (y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 9; ++z )
                 checkTable[z][y][x] = (z + 1);
                 
     // Initialize checkRemainderTable ******************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             checkRemainderTable[y][x] = 9;
             
     // Initialize regionalAnswerTable ******************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             regionalAnswerTable[y][x] = ( 3 * (y / 3)) + (x / 3);
             
     // Initialize regionalDispatchTable ****************************************
     int a, region;
     
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
                 }
         
     }    

     return;
}

//beginGame Function ****************************************************************
void beginGame (void)
{
     int x, y, z, numAnswers, ansCount, answer[9];
     
     //Read in number of answers to give. *******************************************
     printf("Input number of answers to enter, to begin game. ");
     scanf("%d", &numAnswers);
     
     //Loop to enter the answers, at the beginning of the game. *********************
     ansCount = 0;
     
     //read in a line of answers. if no answer, enter 0. ***********
     printf("A row in the puzzle, is all 9 answers on the input line. EG 005 704 002-ENTER.\n\n");
     
     for ( y = 0; y < 9; ++y )
     {
         printf("Read in row# %d of the puzzle.\n", (y + 1) );
         printf("If there is no answer in a square, put a zero.\n");
         
         scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d", &answer[0], &answer[1], &answer[2], &answer[3], &answer[4], \
                                              &answer[5], &answer[6], &answer[7], &answer[8]);
                                              
         for ( x = 0; x < 9; ++x )
             if ( (answer[x] < 0) || (answer[x] > 9) )
             {
                  printf("answer[%d] = %d\n", x, answer[x]);
                  printf("\nERROR, answer not between 1 and 9. START ALL OVER!!!!\n");
                  errCode = 1;
                  return;
             }          
             
         if ( x != 9 )                              //IS THIS CORRECT?************
            continue;      
                
         //Reduce the checkTable to just the one answer; zero rest of candidates.\n");
         for ( x = 0; x < 9; ++x )
             if ( answer[x] > 0 )
             {
                  ++ansCount;
                  for ( z = 0; z < 9; ++z )
                      checkTable[z][y][x] = 0;
             
                  checkTable[(answer[x] - 1)][y][x] = answer[x];
                  
                  //Reduce the checkRemainderTable to one; preparing the way, for naked-single processing later. ****
                  checkRemainderTable[y][x] = 1;
                  startTable[y][x] = answer[x];
             }
     }
     
     if ( ansCount != numAnswers )
     {
        printf("\nYou made a mistake in the number of answers entered. START ALL OVER!!!\n");
        errCode = 1;
        return;
     }
     
     standardCheck(ansCount); 
     return;
}



