// Singles Processing for Sudoku. ***********************************

/*
//Function Declarations. ********************
void nakedSingles (void);
void hiddenSinglesRow (void);
void hiddenSinglesColumn (void);
void hiddenSinglesRegion (void);
*/
//nakedSingles FUNCTION *************************************************************
void nakedSingles (void)
{
     int x, y;
     
     //Is a checkRemainderTable element <= 1? ***********************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 1 )
             {
                  processAnswer(y, x);
                  if ( errCode )
                     return;
                     
  //                printf("procA, "); //debug purposes
             } //ends if cRT...      
             else
                 if ( (checkRemainderTable[y][x] < 0) || ((checkRemainderTable[y][x] == 0) && (answerTable[y][x] == 0))   )
                 {
                      if ( !dimension )
                         printf("\nFATAL ERROR. WILL NEED TO QUIT GAME. \n");
                         
                      printf("checkRemainderTable[%d][%d] < 1.\n", y, x);
                      errCode = 1;
                      return;
                 } //ends if cRT........
     
     return;
}


//hiddenSinglesRow Function *****************************************************
void hiddenSinglesRow (void)
{
     int x, y, z, sum, zz;
     
     for ( y = 0; y < 9; ++y )
         for ( z = 0; z < 9; ++z )
         {
             //sum up checkTable x[0]-x[8]- count the number of times each candidate appears in the row. ***
             sum = 0;
             
             for ( x = 0; x < 9; ++x )
                 sum = (sum +(checkTable[z][y][x] / (z + 1)));
                 
             if ( sum == 1 )
                //turn into nakedSingle *****************
                for ( x = 0; x < 9; ++x )
                    if ( checkTable[z][y][x] > 0 )
                    {
                         //reduce checkTable z-elements to just the one answer, zero rest. ****************
                         for ( zz = 0; zz < 9; ++zz )
                             checkTable[zz][y][x] = 0;
                             
                         checkTable[z][y][x] = (z + 1);
                         //reduce checkRemainderTable element to one. **************************
                         checkRemainderTable[y][x] = 1;
                         //add to changes. ***************************
                         ++changes;
                         
             printf("HiddenSinglesRow--cand = %d--, found at [%d][%d]...\t", (z + 1), y, x);
                         
                         break;
                    }
                    
         }     //ends for z... **************************
     return;
}

//hiddenSinglesColumn Function ***************************************************
void hiddenSinglesColumn (void)
{
     int x, y, z, sum, zz;
     
     for ( x = 0; x < 9; ++x )
         for ( z = 0; z < 9; ++z )
         {
             //sum up checkTable y[0]-y[8]...- count number of times candidate appears in column*****
             sum = 0;
             
             for ( y = 0; y < 9; ++y )
                 sum = (sum + (checkTable[z][y][x] / (z + 1)));
                 
             //if sum == 1, turn into nakedSingle. **************************************
             if ( sum == 1 )
                for ( y = 0; y < 9; ++y )
                    if ( checkTable[z][y][x] > 0 )
                    {
                         //reduce the checkTable z-element to just the one answer. ****************
                         for ( zz = 0; zz < 9; ++zz )
                             checkTable[zz][y][x] = 0;
                             
                         checkTable[z][y][x] = (z + 1);
                         //reduce checkRemainderTable element to one. *******************
                         checkRemainderTable[y][x] = 1;
                         //add to changes. *********************************************
                         ++changes;
                         
             printf("HiddenSinglesCol--cand = %d--, found at [%d][%d]...\t", (z + 1), y, x);
                         
                         break;
                    }
                    
         }    //ends for z.... **********************
     
     return;
}

//hiddenSinglesRegion Function. *************************************************
void hiddenSinglesRegion (void)
{
     int x, y, z, sum, zz, r, c, region, a;
     
     for ( region = 0; region < 9; ++region )
         for ( z = 0; z < 9; ++z )
         {
             sum = 0;
             
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 //sum up checkTable a[0]-a[8] - count the number of times candidate appears in region*****
                 sum += (checkTable[z][r][c] / (z + 1));
             }
             
             if ( sum == 1 )
                //turn into nakedSingle. *********************
                for ( a = 0; a < 9; ++a )
                {
                    r = regionalDispatchTable[region][a].row;
                    c = regionalDispatchTable[region][a].column;
                    
                    if ( checkTable[z][r][c] > 0 )
                    {
                         //reduce checkTable z-elements to just the one answer, zero rest. ***********
                         for ( zz= 0; zz < 9; ++zz )
                             checkTable[zz][r][c] = 0;
                             
                         checkTable[z][r][c] = (z + 1);
                         //reduce checkRemainderTable element to 1. ************
                         checkRemainderTable[r][c] = 1;
                         //add to changes. ********************
                         ++changes;
                         
             printf("HiddenSinglesReg--cand = %d--, found at [%d][%d]...\t", (z + 1), r, c);
                         
                         break;
                    }
                }
         }
      return;
}
     

