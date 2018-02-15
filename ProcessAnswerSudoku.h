// Answer Processing for Sudoku. ******************************

/*
//Function Declarations...
void processAnswer (int y, int x);
void zeroRegion (int y, int x);
void zeroRow (int y, int x);
void zeroColumn (int y, int x);
*/

//processAnswer Function *******************************************************************
void processAnswer (int y, int x)
 {
      int z;
      
      //set remainderTable element to 0, set answerTable element to answer, set answersSoved up by 1. ***********
      checkRemainderTable[y][x] = 0;
      ++answersSolved;
      ++changes;
      
      for ( z = 0; z < 9; ++z )
          if ( checkTable[z][y][x] > 0 )
          {
               answerTable[y][x] = checkTable[z][y][x];
               checkTable[z][y][x] = 0;
               goto END;
          }
      //Error occured. ***************************
      if ( !dimension )
      {
         printf("\nFATAL ERROR. checkTable[z][%i][%i] already = 0.\n", y, x);
         printf("WILL NEED TO QUIT GAME.\n");
      } //ends if !dim.........
      else
          printf("THAT VALUE CREATED AN IMPOSSIBILITY AT [%d][%d]...\n", y, x);
      
      errCode = 1;
      
      return;
            
      END:
      //SET REGIONAL POSSIBILITIES TO 0. ****************************************
      zeroRegion(y, x);
      
      //SET ROW POSSIBILITIES TO 0 *****************************************************
      zeroRow(y, x);
      
      //SET COLUMN POSSIBILITIES TO 0. *************************************************
      zeroColumn(y, x);
      
      
      
      return;
}
           
//zeroRegion Function. ************************************************************************
void zeroRegion (int y, int x)
{
     int region, z;
     
     region = regionalAnswerTable[y][x];
     
     // 9 elements in region. *************************************
     for ( z = 0; z < 9; ++z )
     {
         elementPoint.row = regionalDispatchTable[region][z].row;
         elementPoint.column = regionalDispatchTable[region][z].column;
         
         if ( checkTable[(answerTable[y][x] - 1)][elementPoint.row][elementPoint.column] != 0 )
         {
              //zero out element in checkTable, reduce checkRemainderTable by 1, add to changes (if remainder = 1). *****
              checkTable[(answerTable[y][x] - 1)][elementPoint.row][elementPoint.column] = 0;
              
              --checkRemainderTable[elementPoint.row][elementPoint.column];
              ++changes;
 //NEED TO HAVE ERROR CHECKING IN CASE REMAINDER = 1, AND IT'S THE SAME AS THE ANSWER, OR SOMETHING........**********                
         }
     }
     
     return;
}

//zeroRow FUNCTION. ************************************************************************************************
void zeroRow (int y, int x)
{
     int c;
     
     // 9 elements in row. ************************************************
     for ( c = 0; c < 9; ++c )
         if ( checkTable[(answerTable[y][x] - 1)][y][c] != 0 )
         {
              //zero out elements in checkTable, reduce checkRemainderTable element by 1, add to changes (if remainder = 1).***
              checkTable[(answerTable[y][x] - 1)][y][c] = 0;
              --checkRemainderTable[y][c];
              ++changes;
         }
     
     return;
}

//zeroColumn Function. *******************************************************************
void zeroColumn (int y, int x)
{
     int r;
     
     // 9 elements in column. ***********************************************************
     for ( r = 0; r < 9; ++r )
         if ( checkTable[(answerTable[y][x] - 1)][r][x] != 0 )
         {
              //zero out elements in checkTable, reduce checkRemainderTable element by 1, add to changes (if remainder = 1).***
              checkTable[(answerTable[y][x] - 1)][r][x] = 0;
              --checkRemainderTable[r][x];
              ++changes;
         }
         
     return;
}
     
