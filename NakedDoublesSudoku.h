// Naked Doubles Processing for Sudoku. ********************

/*
//Function Declarations **********
void nakedDoublesRow (void);
void nakedDoublesColumn (void);
void nakedDoublesRegion (void);
*/
//nakedDoublesRow Function. *******************************************************
void nakedDoublesRow (void)
{
     int x, y, z, xx, xxx, elementMatch, match[2];
     
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 8; ++x )
         {
             //Find first nakedDouble candidate, put in match[0]. **************
             if ( (checkRemainderTable[y][x] == 2) & (nDR[y][x] == 0) )
             {
                  elementMatch = 0;
                  
                  for ( z = 0; ((z < 9) & (elementMatch < 2)); ++z )
                      if ( checkTable[z][y][x] > 0 )
                      {
                           match[elementMatch] = checkTable[z][y][x];
                           ++elementMatch;
                      }
             }
             else
                 continue;
                 
             //Check to find a match to your match candidate, just found. *************
             for ( xx = (x + 1); xx < 9; ++xx )
                 if ( checkRemainderTable[y][xx] == 2 )
                    if ( checkTable[(match[0] - 1)][y][xx] > 0 )
                       if ( checkTable[(match[1] - 1)][y][xx] > 0 )
                       {
                            //nakedDouble found. ************************************
                            nDR[y][x] = 1; nDR[y][xx] = 1;  //nakedDouble elements*******
                            //zero out all the matches in the row, except the nakedDoubles. *********
                            //reduce the remainders accordingly. ****************************
                            for ( xxx = 0; xxx < 9; ++xxx )
                                if ( (xxx != x) & (xxx != xx) )
                                {
                                   if ( checkTable[(match[0] - 1)][y][xxx] > 0 )
                                   {
                                      checkTable[(match[0] - 1)][y][xxx] = 0;
                                      --checkRemainderTable[y][xxx];
                                      ++changes;
         printf("Zapped cand=%d at [%d][%d]- in NakedDoubleRow...\t", (match[0] - 1), y,  xxx);
                                   }
                                   
                                   if ( checkTable[(match[1] - 1)][y][xxx] > 0 )
                                   {
                                      checkTable[(match[1] - 1)][y][xxx] = 0;
                                      --checkRemainderTable[y][xxx];
                                      ++changes;
         printf("Zapped cand=%d at [%d][%d]- in NakedDoubleRow...\t", (match[1] - 1), y,  xxx);
                                   }
                                }
                                
                            break;
                       }
         }
         
     return;
}    
    

//nakedDoublesColumn Function. *******************************************************
void nakedDoublesColumn (void)
{
     int x, y, z, yy, yyy, elementMatch, match[2];
     
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 8; ++y )
         {
             //Find first nakedDouble candidate, put in match[0]. **************
             if ( (checkRemainderTable[y][x] == 2) & (nDC[y][x] == 0) )
             {
                  elementMatch = 0;
                  
                  for ( z = 0; ((z < 9) & (elementMatch < 2)); ++z )
                      if ( checkTable[z][y][x] > 0 )
                      {
                           match[elementMatch] = checkTable[z][y][x];
                           ++elementMatch;
                      }
             }
             else
                 continue;
                 
             //Check to find a match to your match candidate, just found. *************
             for ( yy = (y + 1); yy < 9; ++yy )
                 if ( checkRemainderTable[yy][x] == 2 )
                    if ( checkTable[(match[0] - 1)][yy][x] > 0 )
                       if ( checkTable[(match[1] - 1)][yy][x] > 0 )
                       {
                            //nakedDouble found. ************************************
                            nDC[y][x] = 1; nDC[yy][x] = 1;
   //debug purposes**       printf("\nnDC[%d][%d] = %d---nDC[%d][%d] = %d\n", y, x, nDC[y][x], yy, x, nDC[yy][x]);
                            //zero out all the matches in the column, except the nakedDoubles. *********
                            //reduce the remainders accordingly. ****************************
                            for ( yyy = 0; yyy < 9; ++yyy )
                                if ( (yyy != y) & (yyy != yy) )
                                {
                                   if ( checkTable[(match[0] - 1)][yyy][x] > 0 )
                                   {
                                      checkTable[(match[0] - 1)][yyy][x] = 0;
                                      --checkRemainderTable[yyy][x];
                                      ++changes;
           printf("Zapped cand=%d at [%d][%d]- in NakedDoubleCol...\t", (match[0] - 1), yyy,  x);
                                   }
                                   
                                   if ( checkTable[(match[1] - 1)][yyy][x] > 0 )
                                   {
                                      checkTable[(match[1] - 1)][yyy][x] = 0;
                                      --checkRemainderTable[yyy][x];
                                      ++changes;
           printf("Zapped cand=%d at [%d][%d]- in NakedDoubleCol...\t", (match[1] - 1), yyy,  x);
                                   }
                                }
                                
                            break;
                       }
         }
         
     return;
}    
    

//nakedDoublesRegion Function. *******************************************************
void nakedDoublesRegion (void)
{
     int x, y, z, r, c, region, a, aa, aaa, elementMatch, match[2];
     
     for ( region = 0; region < 9; ++region )
         for ( a = 0; a < 8; ++a )
         {
             r = regionalDispatchTable[region][a].row;
             c = regionalDispatchTable[region][a].column;
             //Find first nakedDouble candidate, put in match[0]. **************
             if ( (checkRemainderTable[r][c] == 2) & (nDReg[r][c] == 0) )
             {
                  elementMatch = 0;
                  
                  for ( z = 0; ((z < 9) & (elementMatch < 2)); ++z )
                      if ( checkTable[z][r][c] > 0 )
                      {
                           match[elementMatch] = checkTable[z][r][c];
                           ++elementMatch;
                      }
             }
             else
                 continue;
                 
             //Check to find a match to your match candidate, just found. *************
             for ( aa = (a + 1); aa < 9; ++aa )
             {
                 r = regionalDispatchTable[region][aa].row;
                 c = regionalDispatchTable[region][aa].column;
                 
                 if ( checkRemainderTable[r][c] == 2 )
                    if ( checkTable[(match[0] - 1)][r][c] > 0 )
                       if ( checkTable[(match[1] - 1)][r][c] > 0 )
                       {
                            //nakedDouble found. ************************************
                            nDReg[r][c] = 1;
                            r = regionalDispatchTable[region][a].row;
                            c = regionalDispatchTable[region][a].column;
                            nDReg[r][c] = 1;
                            //zero out all the matches in the row, except the nakedDoubles. *********
                            //reduce the remainders accordingly. ****************************
                            for ( aaa = 0; aaa < 9; ++aaa )
                                if ( (aaa != a) & (aaa != aa) )
                                {
                                   r = regionalDispatchTable[region][aaa].row;
                                   c = regionalDispatchTable[region][aaa].column;
                                     
                                   if ( checkTable[(match[0] - 1)][r][c] > 0 )
                                   {
                                      checkTable[(match[0] - 1)][r][c] = 0;
                                      --checkRemainderTable[r][c];
                                      ++changes;
         printf("Zapped cand=%d at [%d][%d]- in NakedDoubleReg...\t", (match[0] - 1), r,  c);
                                   }
                                   
                                   if ( checkTable[(match[1] - 1)][r][c] > 0 )
                                   {
                                      checkTable[(match[1] - 1)][r][c] = 0;
                                      --checkRemainderTable[r][c];
                                      ++changes;
         printf("Zapped cand=%d at [%d][%d]- in NakedDoubleReg...\t", (match[1] - 1), r,  c);
                                   }
                                }
                            break;
                       }
             }
         }
         
     return;
}    
    
