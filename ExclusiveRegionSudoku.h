// Exclusive Region Processing for Sudoku. ****************

/*
//Function Declarations ****************
void exclusiveRegionRow (void);
void exclusiveRegionColumn (void);
*/

//THESE ARE ALSO REDFERRED TO AS LOCKED CANDIDATES, BUT I FEEL eRR, IS MORE SPECIFIC.. ****
//exclusiveRegionRow Function. ***********************************
void exclusiveRegionRow (void)
{
     int x, y, z, region, elementMatch, a, r, c;
     
     for ( y = 0; y < 9; ++y )
         for ( z = 0; z < 9; ++z )
         {
             elementMatch = 0;
             
             for ( x = 0; x < 9; ++x )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      if ( elementMatch == 0 )
                      {
                           region = regionalAnswerTable[y][x];
                           ++elementMatch;
                      }
                      else
                          if (regionalAnswerTable[y][x] != region )
                          {
                             elementMatch = 0;
                             break;
                          }
                 }
                 
             if ( elementMatch > 0 )
                //ExclusiveRegionRow candidate does exist.*************
                for ( a = 0; a < 9; ++a )
                {
                    r = regionalDispatchTable[region][a].row;
                    c = regionalDispatchTable[region][a].column;
                    
                    if ( r != y )
                       if ( checkTable[z][r][c] > 0 )
                       {
                            checkTable[z][r][c] = 0;
                            --checkRemainderTable[r][c];
                            ++changes;
             printf("Zapped cand=%d at [%d][%d]- in exclusiveRegionRow[LockedCandidates]..\t", (z + 1), r, c);
                       }
                }
         }
     
     return;
}

//THESE ARE ALSO REFERRED TO AS LOCKED CANDIDATES, BUT I FEEL eRC, IS MORE SPECIFIC. *********     
//exclusiveRegionColumn Function. ***********************************
void exclusiveRegionColumn (void)
{
     int x, y, z, region, elementMatch, a, r, c;
     
     for ( x = 0; x < 9; ++x )
         for ( z = 0; z < 9; ++z )
         {
             elementMatch = 0;
             
             for ( y = 0; y < 9; ++y )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      if ( elementMatch == 0 )
                      {
                           region = regionalAnswerTable[y][x];
                           ++elementMatch;
                      }
                      else
                          if ( regionalAnswerTable[y][x] != region )
                          {
                             elementMatch = 0;
                             break;
                          }
                 }
                 
             if ( elementMatch > 0 )
                //ExclusiveRegionColumn candidate does exist.*************
                for ( a = 0; a < 9; ++a )
                {
                    r = regionalDispatchTable[region][a].row;
                    c = regionalDispatchTable[region][a].column;
                    
                    if ( c != x )
                       if ( checkTable[z][r][c] > 0 )
                       {
                            checkTable[z][r][c] = 0;
                            --checkRemainderTable[r][c];
                            ++changes;
             printf("Zapped cand=%d at [%d][%d]- in exclusiveRegionCol[LockedCandidates]..\t", (z + 1), r, c);
                       }
                }
         }
     
     return;
}
     
