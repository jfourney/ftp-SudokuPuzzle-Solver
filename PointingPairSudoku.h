// Pointing Pair Processing for Sudoku. ****************

/*
//Function Declarations ****************
void pointingPairRow (void);
void pointingPairColumn (void);
*/

//THESE ARE ALSO REDFERRED TO AS LOCKED CANDIDATES. ****
//pointingPairRow Function. ***********************************
void pointingPairRow (void)
{
     int x, y, z, region, elementMatch, a, r, rr, c;
     
     for ( region = 0; region < 9; ++region )
         for ( z = 0; z < 9; ++z )
         {
             elementMatch = 0;
             
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 
                 if ( checkTable[z][r][c] > 0 )
                 {
                      if ( elementMatch == 0 )
                      {
                           rr = r;
                           ++elementMatch;
                      }
                      else
                          if ( r != rr )
                          {
                             elementMatch = 0;
                             break;
                          }
                 }  // ends if cT...
             }   // ends for a....
             if ( elementMatch > 0 )
             {
                //PointingPairRow candidate does exist.*************
                
                y = rr;
                
                for ( x = 0; x < 9; ++x )
                    if ( regionalAnswerTable[y][x] != region )
                       if ( checkTable[z][y][x] > 0 )
                       {
                            checkTable[z][y][x] = 0;
                            --checkRemainderTable[y][x];
                            ++changes;
             printf("Zapped cand=%d at [%d][%d]- in PointingPairRow...\t", (z + 1), y,  x);
                       }
             }  // ends if eM ..
         }  // ends for z......
     
     return;
}


//THESE ARE ALSO REDFERRED TO AS LOCKED CANDIDATES. ****
//pointingPairColumn Function. ***********************************
void pointingPairColumn (void)
{
     int x, y, z, region, elementMatch, a, r, cc, c;
     
     for ( region = 0; region < 9; ++region )
         for ( z = 0; z < 9; ++z )
         {
             elementMatch = 0;
             
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 
                 if ( checkTable[z][r][c] > 0 )
                 {
                      if ( elementMatch == 0 )
                      {
                           cc = c;
                           ++elementMatch;
                      }
                      else
                          if ( c != cc )
                          {
                             elementMatch = 0;
                             break;
                          }
                 }  // ends if cT...
             }   // ends for a....
             if ( elementMatch > 0 )
             {
                //PointingPairColumn candidate does exist.*************
                
                x = cc;
                
                for ( y = 0; y < 9; ++y )
                    if ( regionalAnswerTable[y][x] != region )
                       if ( checkTable[z][y][x] > 0 )
                       {
                            checkTable[z][y][x] = 0;
                            --checkRemainderTable[y][x];
                            ++changes;
             printf("Zapped cand=%d at [%d][%d]- in PointingPairCol...\t", (z + 1), y,  x);
                       }
             }  //ends if eM...
         }  // ends for z...
     
     return;
}


