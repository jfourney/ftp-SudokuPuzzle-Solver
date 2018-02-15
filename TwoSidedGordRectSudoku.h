//Two-Sided Gordonian Rectangle Processing for Sudoku....
/*
//Function Declarations ..........*******************
void twoSidedGordRectRow (void);
void twoSidedGordRectColumn (void);
*/

//twoSidedGordRectRow Function ************************
void twoSidedGordRectRow (void)
{
     int x, y, z, a, r, c, region, rr, yy, xx, u, uu, xCand, yCand, zCand;
     int doublesTable[9][9][2], triplesTable[9][9][3];
     
     //INITIALIZE DOUBLE AND TRIPLE TABLES...*************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x)
             for ( u = 0; u < 3; ++u )
                 if ( u == 2 )
                    triplesTable[y][x][2] = 0;
                 else
                     {
                         triplesTable[y][x][u] = 0;
                         doublesTable[y][x][u] = 0;
                     }  // ends for y = .... *************
                     
     //SET UP DOUBLES TABLE..................
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             if ( checkRemainderTable[y][x] != 2 )
                continue;
             if ( nDR[y][x] || nDC[y][x] || nDReg[y][x] )
                continue;
                
             u = 0;
             for ( z = 0; u < 2; ++z )
                 if ( checkTable[z][y][x] > 0 )
                 {
                    doublesTable[y][x][u] = (z + 1);
                    ++u;
                 } // ends if cT......ends for z......... ********
         }  // ends for x = ....for y......... *******************
         
     // set up triplesTable. *********************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 3 )
             {
                  u = 0;
                  for ( z = 0; u < 3; ++z )
                      if ( checkTable[z][y][x] > 0 )
                      {
                           triplesTable[y][x][u] = (z + 1);
                           ++u;
                      }
             }  // ends if cRT... ends for x....   ends for y.... **********
             
     //TABLES ARE SET UP.......................
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 8; ++x )
         {
             //find a dt element....
             if ( !doublesTable[y][x][0] )
                continue;
                
             //set up xCand and yCand with dt elements...
             xCand = doublesTable[y][x][0];
             yCand = doublesTable[y][x][1];
             region = regionalAnswerTable[y][x];
             
             //find a tt element, that contains dt elements, ahead in the row..***
             for ( xx = (x + 1); ( (xx < 9) && (regionalAnswerTable[y][xx] == region) ); ++xx )
             {
                 if ( !triplesTable[y][xx] )
                    continue;
                    
                 zCand = 0;
                 uu = 0;
                 
                 for ( u = 0; ( (u < 3) && (uu < 2) ); ++u )
                     if ( doublesTable[y][x][uu] != triplesTable[y][xx][u] )
                        if ( !zCand )
                           zCand = triplesTable[y][xx][u];
                        else
                            break;
                     else
                         ++uu;
                         
                 if ( u < 3 )
                    continue;  //next xx...............
                    
                 //found a qualifier in the row, and region......
                 //now find an equivalent to tt[y][xx] at [yy][x]....
                 for ( yy = 0; yy < 9; ++yy )
                 {
                     if ( yy == y )
                        continue; //next yy..............
                        
                     rr = regionalAnswerTable[yy][x];
                     
                     if ( rr == region )
                        continue; //next yy..........
                        
                     if ( !triplesTable[yy][x][0] )
                        continue; //next yy............
                        
                     //found a tt element, is it equal to tt[y][xx]......
                     for ( u = 0; u < 3; ++u )
                         if ( triplesTable[yy][x][u] != triplesTable[y][xx][u] )
                            break;
                            
                     if ( u < 3 )
                        continue; //next yy...............
                        
                     //found a tt qualifier at [yy][x]........
                     //now find dt equivalent at [yy][xx]...........
                     if ( !doublesTable[yy][xx] )
                        continue;
                        
                     //found dt element, are they the same elements as dt[y][x]...
                     for ( u = 0; u < 2; ++u )
                         if ( doublesTable[yy][xx][u] != doublesTable[y][x][u] )
                            break;
                            
                     if ( u < 2 )
                        continue; //next yy...............
                        
                     //ACHIEVED A 2-SIDED GORDONIAN RECTANGLE ROW..............
                     //zap all applicable candidates.................
                     
                     //zap zCands in region, col x, if row!=y......
                     for ( a = 0; a < 9; ++a )
                     {
                         r = regionalDispatchTable[region][a].row;
                         c = regionalDispatchTable[region][a].column;
                         
                         if ( c != x )
                            continue; //next a.....
                            
                         if ( r == y )
                            continue; //next a...........
                            
                         //zap zCands in this loc.....
                         if ( !checkTable[(zCand - 1)][r][c] );
                            continue;
                            
                         //have zCand to zap........
                         checkTable[(zCand - 1)][r][c] = 0;
                         --checkRemainderTable[r][c];
                         printf("Zapped zC=%d at [%d][%d]...in 2sidedGordRectRow.1...\t", \
                                zCand, r, c);
                         ++changes;
                     } //ends for a.........................
                     
                     //zap zCands in rr, col xx, if row!=yy......
                     for ( a = 0; a < 9; ++a )
                     {
                         r = regionalDispatchTable[rr][a].row;
                         c = regionalDispatchTable[rr][a].column;
                         
                         if ( c != xx )
                            continue; //next a.....
                            
                         if ( r == yy )
                            continue; //next a...........
                            
                         //zap zCands in this loc.....
                         if ( !checkTable[(zCand - 1)][r][c] );
                            continue;
                            
                         //have zCand to zap........
                         checkTable[(zCand - 1)][r][c] = 0;
                         --checkRemainderTable[r][c];
                         printf("Zapped zC=%d at [%d][%d]...in 2sidedGordRectRow.2...\t", \
                                zCand, r, c);
                         ++changes;
                     } //ends for a.........................
                     
                     if ( changes)
                        return;
                        
                 } //ends for yy..............
             }  //ends for xx.......
         }  //ends for x...for y..............
     return;
}
                        
                        
                     
 //twoSidedGordRectColumn Function ************************
void twoSidedGordRectColumn (void)
{
     int x, y, z, a, r, c, region, rr, yy, xx, u, uu, xCand, yCand, zCand;
     int doublesTable[9][9][2], triplesTable[9][9][3];
     
     //INITIALIZE DOUBLE AND TRIPLE TABLES...*************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x)
             for ( u = 0; u < 3; ++u )
                 if ( u == 2 )
                    triplesTable[y][x][2] = 0;
                 else
                     {
                         triplesTable[y][x][u] = 0;
                         doublesTable[y][x][u] = 0;
                     }  // ends for y = .... *************
                     
     //SET UP DOUBLES TABLE..................
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             if ( checkRemainderTable[y][x] != 2 )
                continue;
             if ( nDR[y][x] || nDC[y][x] || nDReg[y][x] )
                continue;
                
             u = 0;
             for ( z = 0; u < 2; ++z )
                 if ( checkTable[z][y][x] > 0 )
                 {
                    doublesTable[y][x][u] = (z + 1);
                    ++u;
                 } // ends if cT......ends for z......... ********
         }  // ends for x = ....for y......... *******************
         
     // set up triplesTable. *********************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 3 )
             {
                  u = 0;
                  for ( z = 0; u < 3; ++z )
                      if ( checkTable[z][y][x] > 0 )
                      {
                           triplesTable[y][x][u] = (z + 1);
                           ++u;
                      }
             }  // ends if cRT... ends for x....   ends for y.... **********
             
     //TABLES ARE SET UP.......................
     for ( x = 0; x < 9; ++x )
         for ( y= 0; y < 8; ++y )
         {
             //find a dt element....
             if ( !doublesTable[y][x][0] )
                continue;
                
             //set up xCand and yCand with dt elements...
             xCand = doublesTable[y][x][0];
             yCand = doublesTable[y][x][1];
             region = regionalAnswerTable[y][x];
             
             //find a tt element, that contains dt elements, ahead in the row..***
             for ( yy = (y + 1); ( (yy < 9) && (regionalAnswerTable[yy][x] == region) ); ++yy )
             {
                 if ( !triplesTable[y][xx] )
                    continue;
                    
                 zCand = 0;
                 uu = 0;
                 
                 for ( u = 0; ( (u < 3) && (uu < 2) ); ++u )
                     if ( doublesTable[y][x][uu] != triplesTable[yy][x][u] )
                        if ( !zCand )
                           zCand = triplesTable[yy][x][u];
                        else
                            break;
                     else
                         ++uu;
                         
                 if ( u < 3 )
                    continue;  //next yy...............
                    
                 //found a qualifier in the column, and region......
                 //now find an equivalent to tt[yy][x] at tt[y][xx]....
                 for ( xx = 0; xx < 9; ++xx )
                 {
                     if ( xx == x )
                        continue; //next xx..............
                        
                     rr = regionalAnswerTable[y][xx];
                     
                     if ( rr == region )
                        continue; //next xx..........
                        
                     if ( !triplesTable[y][xx][0] )
                        continue; //next xx............
                        
                     //found a tt element, is it equal to tt[yy][x]......
                     for ( u = 0; u < 3; ++u )
                         if ( triplesTable[y][xx][u] != triplesTable[yy][x][u] )
                            break;
                            
                     if ( u < 3 )
                        continue; //next yy...............
                        
                     //found a tt qualifier at [y][xx]........
                     //now find dt equivalent at [yy][xx]...........
                     if ( !doublesTable[yy][xx] )
                        continue;
                        
                     //found dt element, are they the same elements as dt[y][x]...
                     for ( u = 0; u < 2; ++u )
                         if ( doublesTable[yy][xx][u] != doublesTable[y][x][u] )
                            break;
                            
                     if ( u < 2 )
                        continue; //next yy...............
                        
                     //ACHIEVED A 2-SIDED GORDONIAN RECTANGLE ROW..............
                     //zap all applicable candidates.................
                     
                     //zap zCands in region, col x, if row!=y......
                     for ( a = 0; a < 9; ++a )
                     {
                         r = regionalDispatchTable[region][a].row;
                         c = regionalDispatchTable[region][a].column;
                         
                         if ( r != y )
                            continue; //next a.....
                            
                         if ( c == x )
                            continue; //next a...........
                            
                         //zap zCands in this loc.....
                         if ( !checkTable[(zCand - 1)][r][c] );
                            continue;
                            
                         //have zCand to zap........
                         checkTable[(zCand - 1)][r][c] = 0;
                         --checkRemainderTable[r][c];
                         printf("Zapped zC=%d at [%d][%d]...in 2sidedGordRectCol.1...\t", \
                                zCand, r, c);
                         ++changes;
                     } //ends for a.........................
                     
                     //zap zCands in rr, col xx, if row!=yy......
                     for ( a = 0; a < 9; ++a )
                     {
                         r = regionalDispatchTable[rr][a].row;
                         c = regionalDispatchTable[rr][a].column;
                         
                         if ( r != yy )
                            continue; //next a.....
                            
                         if ( c == xx )
                            continue; //next a...........
                            
                         //zap zCands in this loc.....
                         if ( !checkTable[(zCand - 1)][r][c] );
                            continue;
                            
                         //have zCand to zap........
                         checkTable[(zCand - 1)][r][c] = 0;
                         --checkRemainderTable[r][c];
                         printf("Zapped zC=%d at [%d][%d]...in 2sidedGordRectCol.2...\t", \
                                zCand, r, c);
                         ++changes;
                     } //ends for a.........................
                     
                     if ( changes)
                        return;
                        
                 } //ends for xx..............
             }  //ends for yy.......
         }  //ends for y...for x..............
     return;
}
                        
                        
                                             
                     
                     
                        
             
             
             
