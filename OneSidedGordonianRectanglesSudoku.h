//One-Sided Gordonian Rectangles Processing for Sudoku. *****

/*
//Function Declarations **************************
void oneSidedGordRectRow (void);
void oneSidedGordRectColumn (void);
*/

//oneSidedGordRectRow Function ***************************
void oneSidedGordRectRow (void)
{
     int x, y, z, region, a, r, c, gND[2], xx, rr, yy, zCand, xxx, gCount;
     
     gND[0] = 0;
     gND[1] = 0;
     
     //Search for the BasePoints, are corresponding nDR and NDReg, but not nDC....
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             if ( !nDR[y][x] || !nDReg[y][x] || nDC[y][x] )
                continue; // next x.....
                
             //found possible base point...
             region = regionalAnswerTable[y][x];
             
             gCount = 0;
             
             for ( z = 0; gCount < 2; ++z )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      gND[gCount] = checkTable[z][y][x];
                      ++gCount;
                 } // ends if cT... for z =.....
                 
             //find the corresponding nDR.....************
             for ( xx = 0; xx < 9; ++xx )
             {
                 if ( xx == x )
                    continue; // next xx.........
                    
                 if ( !nDR[y][xx] )
                    continue; //next xx.....
                    
                 //Is an nDR...is it the corresponding nDR??? ******
                 if ( !checkTable[(gND[0] - 1)][y][xx] )
                    continue; //next xx...not the corresponding nDR...
                    
                 //Is the corresponding nDR...is it in the same region???...
                 break; //from xx.... *************************
             } //ends for xx = ...**********
             
             if ( xx == 9 )
             continue;  //next x........
             
             //have possible BasePoints, if in the same region.....
             rr = regionalAnswerTable[y][xx];
             
             if ( region != rr )
                continue;  // next x........NOT BASE POINTS.....
             
             //BasePoints have been established at [y][x] and [y][xx].......
             
             //Search yy at [x] and [xx], to see if oneSidedGordRect........
             for ( yy = 0; yy < 9; ++yy )
             {
                 if ( yy == y )
                    continue; //next yy.........
                    
                 if ( (checkRemainderTable[yy][x] != 3) || (checkRemainderTable[yy][xx] != 3) )
                    continue; // next yy..............
                    
                 //Check to see if both [yy][x] and [yy][xx], have the same candidates....
                 for ( z = 0; z < 9; ++z)
                     if ( (checkTable[z][yy][x]) != (checkTable[z][yy][xx]) )
                        break; //not the gordonianPoints...
                        
                 if ( z < 9 )
                    continue; //next yy........
                    
                 //Are the gordonianPoints, if they contain gND[0] and gND[1].....
                 if ( (!checkTable[(gND[0] - 1)][yy][x]) || (!checkTable[(gND[1] - 1)][yy][x]) )
                    continue; //next yy...............
                    
                 //Are gordonianPoints--determine zCandidate to zap from rest of row yy.....
                 for ( z = 0; z < 9; ++z )
                     if ( (z != (gND[0] - 1))  &&  (z != (gND[1] - 1)) )
                        if ( checkTable[z][yy][x] > 0 )
                        {
                             zCand = checkTable[z][yy][x];
                             break; // from for z = ....
                        } //ends if cT... for z = ...... *********
                        
                 //Zap zCandidates from row yy..........
                 for ( xxx = 0; xxx < 9; ++xxx )
                 {
                     if ( (xxx == x) || (xxx == xx) )
                        continue; //next xxx.........
                        
                     if ( checkTable[(zCand - 1)][yy][xxx] > 0 )
                     {
                          checkTable[(zCand - 1)][yy][xxx] = 0;
                          --checkRemainderTable[yy][xxx];
                          ++changes;
         printf("Zapped cand=%d at [%d][%d]..in oneSideGordRectRow...\t", zCand, yy, xxx);
                     }// ends if cT.....
                 } // ends for xxx..... ***
                 
                 if ( changes > 0 )
                    return; // go back to main... to LOOP....
             } // ends for yy = .........
         } // ends for x = ...... ***********ends for y = ........
         
     return;
}
                          
             
//oneSidedGordRectColumn Function ***************************
void oneSidedGordRectColumn (void)
{
     int x, y, z, region, a, r, c, gND[2], xx, rr, yy, zCand, yyy, gCount;
     
     gND[0] = 0;
     gND[1] = 0;
     
     //Search for the BasePoints, are corresponding nDC and NDReg, but not nDR....
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
         {
             if ( !nDC[y][x] || !nDReg[y][x] || nDR[y][x] )
                continue; // next y.....
                
             //found possible base point...
             region = regionalAnswerTable[y][x];
             
             gCount = 0;
             
             for ( z = 0; gCount < 2; ++z )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      gND[gCount] = checkTable[z][y][x];
                      ++gCount;
                 } // ends if cT... for z =.....
                 
             //find the corresponding nDC.....************
             for ( yy = 0; yy < 9; ++yy )
             {
                 if ( yy == y )
                    continue; // next yy.........
                    
                 if ( !nDC[yy][x] )
                    continue; //next yy.....
                    
                 //Is an nDC...is it the corresponding nDC??? ******
                 if ( !checkTable[(gND[0] - 1)][yy][x] )
                    continue; //next yy...not the corresponding nDC...
                    
                 //Is the corresponding nDC...is it in the same region???...
                 break; //from yy.... *************************
             } //ends for yy = ...**********
             
             if ( yy == 9 )
             continue;  //next y........
             
             //have possible BasePoints, if in the same region.....
             rr = regionalAnswerTable[yy][x];
             
             if ( region != rr )
                continue;  // next y........NOT BASE POINTS.....
             
             //BasePoints have been established at [y][x] and [yy][x].......
             
             //Search xx at [y] and [yy], to see if oneSidedGordRect........
             for ( xx = 0; xx < 9; ++xx )
             {
                 if ( xx == x )
                    continue; //next xx.........
                    
                 if ( (checkRemainderTable[y][xx] != 3) || (checkRemainderTable[yy][xx] != 3) )
                    continue; // next xx..............
                    
                 //Check to see if both [y][xx] and [yy][xx], have the same candidates....
                 for ( z = 0; z < 9; ++z)
                     if ( (checkTable[z][y][xx]) != (checkTable[z][yy][xx]) )
                        break; //not the gordonianPoints...
                        
                 if ( z < 9 )
                    continue; //next xx........
                    
                 //Are the gordonianPoints, if they contain gND[0] and gND[1].....
                 if ( (!checkTable[(gND[0] - 1)][y][xx]) || (!checkTable[(gND[1] - 1)][y][xx]) )
                    continue; //next xx...............
                    
                 //Are gordonianPoints--determine zCandidate to zap from rest of column xx.....
                 for ( z = 0; z < 9; ++z )
                     if ( (z != (gND[0] - 1))  &&  (z != (gND[1] - 1)) )
                        if ( checkTable[z][y][xx] > 0 )
                        {
                             zCand = checkTable[z][y][xx];
                             break; // from for z = ....
                        } //ends if cT... for z = ...... *********
                        
                 //Zap zCandidates from column xx..........
                 for ( yyy = 0; yyy < 9; ++yyy )
                 {
                     if ( (yyy == y) || (yyy == yy) )
                        continue; //next yyy.........
                        
                     if ( checkTable[(zCand - 1)][yyy][xx] > 0 )
                     {
                          checkTable[(zCand - 1)][yyy][xx] = 0;
                          --checkRemainderTable[yyy][xx];
                          ++changes;
         printf("Zapped cand=%d at [%d][%d]..in oneSideGordRectCol...\t", zCand, yyy, xx);
                     }// ends if cT.....
                 } // ends for yyy..... ***
                 
                 if ( changes > 0 )
                    return; // go back to main... to LOOP....
             } // ends for xx = .........
         } // ends for y = ...... ***********ends for x = ........
         
     return;
}
                          
             
