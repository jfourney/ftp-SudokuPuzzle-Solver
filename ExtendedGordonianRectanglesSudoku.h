//Extended Gordonian Rectangles Processing for Sudoku....*********************
/*
//Function Declarations ******************************* 
void extendGordRectRow (void);
void extendGordRectColumn (void);
*/

//extendGordRectRow Function *******************************
void extendGordRectRow (void)
{
     int x, y, z, a, b, xx, yy, c, cCand, xxx,  cands, sub, New, qId, id, loc;
     int checkCands[3], nTRCands[3], nTRloc[3], nTRIdTable[9][9];
     int e = 0, f = 0, fLoc, aLoc, bLoc, fW, Row, yyy, yyyy, region, rr;
     
 /*    //debug purposes .............
     deBug();
 */    //debug purposes ..................
     
     //Initialize the nTRIdTable....**************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             nTRIdTable[y][x] = 0;
             
     //Set up the nTRIdTable...********************
     for ( y = 0; y < 9; ++y )
     {
         id = 0;
         
         for ( x = 0; x < 9; ++x )
         {
             New = 0;
             
             if ( !nTR[y][x] || nTRIdTable[y][x] )
                continue; //next x......
                
             //Is a new nTR................
             //Initialize nTRCands, nTRloc, and checkCands Tables............
             for ( a = 0; a < 3; ++a )
             {
                 nTRloc[a] =0;
                 nTRCands[a] = 0;
                 checkCands[a] = 0;
             } //ends for a...........
             
             ++New;
             ++id;
             sub = 0;
             loc = 0;
             cands = 0;
             
             nTRloc[0] = x;
             
             //Put cands into nTRCands........
             for ( z = 0; z < 9; ++z )
             {
                 if ( !checkTable[z][y][x] )
                    continue; //next z....
                    
                 //found a cand- enter into nTRCandsTable.....
                 nTRCands[cands] = (z + 1);
                 ++cands;
             } // ends for z = .............
             
             //Find the other 2 corresponding nTR cells, in this row.....
             for ( xx = (x + 1); xx < 9; ++xx )
             {
                 if ( (!nTR[y][xx]) || (nTRIdTable[y][xx]) )
                    continue;
                    
                 //found another nTR- enter cands into checkCands Table......
                 sub = 0;
                 
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( !checkTable[z][y][xx] )
                        continue; //next z..........
                        
                     checkCands[sub] = checkTable[z][y][xx];
                     ++sub;
                 } //ends for z = .................
                 
                 //check to see if cands are part of the current nTR's, or another
                 //set of nTR's..checkCands[0] or checkCands[1]-- would have to be
                 //equal to nTRCands[0] or nTRCands[1]; or both..... else you have
                 //a completely different set of nTR's...
                 
                 if ( (checkCands[0] != nTRCands[0]) && (checkCands[0] != nTRCands[1]) \
                   &&  (checkCands[1] != nTRCands[0]) && (checkCands[1] != nTRCands[1]) )
                       continue; //next xx.... different set of nTR's....
                       
                 //same set of nTR's involved............
                 ++loc;
                 nTRloc[loc] = xx;
                 
                 if ( cands != 3 )
                 {
                      for ( a = 0; a < 3; ++a )
                      {
                          if ( checkCands[a] )
                             cCand = checkCands[a];
                          else
                              continue;
                          
                          for ( c = 0; c < 2; ++c )
                          {
                              if (nTRCands[c] != cCand )
                                 continue; // next c....
                                 
                              //not a new cand..........
                              break;
                          } //ends for c = .............
                          
                          if ( c == 2 )
                          {
                             //new cand.....
                             nTRCands[2] = checkCands[a];
                             a = 3; //will end a........
                          } //ends if c...
                      } // ends for a = .......
                 } // ends if cands =............
             } //ends for xx =.............
             
             if ( !New )
                continue; // next x.............
                
             //If this set of nTR's passes preliminary qualifications for the
             //extended Gordonian Rectangle.. (checkRemainder == 2), for all
             //3 of the nTR cells.. if they qualify set id = id, else id = 4...
             
             for ( xxx = 0; xxx < 3; ++xxx )
             {
                 if ( checkRemainderTable[y][(nTRloc[xxx])] == 2 )
                    continue;
                    
                 //not a qualifier........
                 break;
             } // ends for xxx= ..............
             
             if ( xxx == 3 )
                qId = id;
             else
                 qId = 4;
                 
             for ( xxx = 0; xxx < 3; ++xxx )
                 nTRIdTable[y][(nTRloc[xxx])] = qId;
                 
         } //ends for x = ...........
     } //ends for y = ...................
     
     //nTRIdTable is Set up; with 1-3, for qualifiers; 4-nonqualifiers; 0- not nTR's......
     
     //Find a qualifying nTR....................
     for ( y = 0; y < 9; ++y )
         for ( id = 1; id < 4; ++id )
         {
             fW = 0;
             Row = 9;
             fLoc = 9;
             aLoc = 9;
             bLoc = 9;
             
             for ( x = 0; x < 9; ++x )
             {
                 if ( nTRIdTable[y][x] != id )
                    continue; //next x..............
                    
                 //found a corresponding nTR.......................
                 if ( (!nDC[y][x]) && (fW) )
                    break; //from x....  these nTR's won't work... next id....
                    
                 //check if possible fWing................
                 if ( (!nDC[y][x]) && (!fW) )
                 {
                      ++fW;
                      fLoc = x;
                      continue; //next x..........
                 } //ends if !nDC............
                 
                 //Is an nDC and an nTR..........................
                 region = regionalAnswerTable[y][x];
                 
                 //Find the corresponding nDC..............
                 for ( yy = 0; yy < 9; ++yy )
                 {
                     if ( yy == y )
                        continue; //next yy............
                        
                     rr = regionalAnswerTable[yy][x];
                     
                     if ( region != rr )
                        continue;
                        
                     if ( !nDC[yy][x] )
                        continue; //next yy....
                        
                     //found an nDC, is it the corresponding nDC?...............
                     for ( z = 0; z < 9; ++z )
                         if ( checkTable[z][yy][x] != checkTable[z][y][x] )
                            break; //from for z =..........
                            
                     if ( z != 9 )
                        continue; // next yy... not a corresponding nDC.....
                        
                     //corresponding nDC's at [y][x] and [yy][x]....
                     break;
                 } //ends for yy = ...................
                 
                 if ( Row == 9 )
                 {
                      Row = yy;
                      aLoc = x;
                      continue; //next x.........
                 } // ends if Row..........
                 
                 //This is the second nTR with nDC- the corresponding nDC's must
                 //be in the same row............
                 for ( yyy = 0; yyy < 9; ++yyy )
                 {
                     if ( yyy == y )
                        continue; //next yyy.........
                        
                     if ( !nDC[yyy][x] )
                        continue; //next yyy........
                        
                     //found nDC...is it corresponding nDC?.......
                     for ( z = 0; z < 9; ++z )
                         if ( checkTable[z][yyy][x] != checkTable[z][y][x] )
                            break;  //from for z = ..........
                            
                     if ( z == 9 )
                        //found corresponding nDC.....
                        break; //from for yyy = .........
                 } // ends for yyy = ..........
                 
                 //Check to see if corresponding nDC, is in the same row [yy]...
                 bLoc = x;
                 
                 for ( z = 0; z < 9; ++z )
                     if ( checkTable[z][Row][x] != checkTable[z][yyy][x] )
                        break; //from for z.....nDC's not in same rows......
                        
                 if ( z != 9 )
                 {
                      //nTR's won't qualify for extended Gordonian Rectangle...
                      //goto next id.....
                      x = 9;
                      continue; //next x....but will end the x's and go to next id...
                 }  //ends if z !=............
             } //ends for x = .............. 
             
             if ( (x == 10) || (bLoc == 9) )
                continue; //next id...............
                
             //Now need to check the fWing location-[Row][fLoc] to see if it qualifies....
             // 2 of the cands = cands at nTR[y][fLoc]..
                           
             for ( z = 0; z < 9; ++z )
                 if ( checkTable[z][y][fLoc] )
                    if ( !checkTable[z][Row][fLoc] )
                       break;  //from for z..... doesn't have both candidates...
                                  
             if ( z != 9 )
                continue; //next id..........
                
             //Found the fWing-- Zap the 2 NTRcands from [y][fLoc], at the fWing [Row][fLoc]...
             for ( z = 0; z < 9; ++z )
                 if ( checkTable[z][y][fLoc] )
                    {
                         checkTable[z][Row][fLoc] = 0;
                         --checkRemainderTable[Row][fLoc];
                         ++changes;
         printf("Zapped cand=%d at [%d][%d]..in extendGordRectRow..\t", (z + 1), Row, fLoc);
                    } // ends if cT ..//ends for z = ..........
                    
/*             if ( !checkRemainderTable[Row][fLoc] )
             {
                printf("SUDOKU PUZZLE DOES NOT HAVE A UNIQUE SOLUTION. QUIT PUZZLE.\n");
                printf("The Gordonian Vertex is at [%d][%d].in extendGordRectRow..\n", Row, fLoc);
                errCode = 1;
                
                system("pause");
                return;
             }
*/                    
             if ( changes > 0 )
                return;
     } //ends for id = .//ends for y =.............
     
     return;
} 
                  
//extendGordRectColumn Function *******************************
void extendGordRectColumn (void)
{
     int x, y, z, a, b, xx, yy, c, cCand, yyy,  cands, New, qId, id, sub, loc;
     int checkCands[3], nTCCands[3], nTCloc[3], nTCIdTable[9][9];
     int e = 0, f = 0, fLoc, aLoc, bLoc, fW, Col, xxx, xxxx, region, rr;
     //Initialize the nTRIdTable....**************
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             nTCIdTable[y][x] = 0;
             
     //Set up the nTCIdTable...********************
     for ( x = 0; x < 9; ++x )
     {
         id = 0;
         
         for ( y = 0; y < 9; ++y )
         {
             New = 0;
             
             if ( !nTC[y][x] || nTCIdTable[y][x] )
                continue; //next y......
                
             //Is a new nTC................
             //Initialize nTCCands, nTCloc, and checkCands Tables............
             for ( a = 0; a < 3; ++a )
             {
                 nTCloc[a] =0;
                 nTCCands[a] = 0;
                 checkCands[a] = 0;
             } //ends for a...........
             
             ++New;
             ++id;
             sub = 0;
             loc = 0;
             cands = 0;
             
             nTCloc[0] = y;
             
             //Put cands into nTCCands........
             for ( z = 0; z < 9; ++z )
             {
                 if ( !checkTable[z][y][x] )
                    continue; //next z....
                    
                 //found a cand- enter into nTCCandsTable.....
                 nTCCands[cands] = (z + 1);
                 ++cands;
             } // ends for z = .............
             
             //Find the other 2 corresponding nTC cells, in this column.....
             for ( yy = (y + 1); yy < 9; ++yy )
             {
                 if ( (!nTC[yy][x]) || (nTCIdTable[yy][x]) )
                    continue;
                    
                 //found another nTC- enter cands into checkCands Table......
                 sub = 0;
                 
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( !checkTable[z][yy][x] )
                        continue; //next z..........
                        
                     checkCands[sub] = checkTable[z][yy][x];
                     ++sub;
                 } //ends for z = .................
                 
                 //check to see if cands are part of the current nTC's, or another
                 //set of nTC's..checkCands[0] or checkCands[1]-- would have to be
                 //equal to nTCCands[0] or nTCCands[1]; or both..... else you have
                 //a completely different set of nTC's...
                 
                 if ( (checkCands[0] != nTCCands[0]) && (checkCands[0] != nTCCands[1]) \
                   &&  (checkCands[1] != nTCCands[0]) && (checkCands[1] != nTCCands[1]) )
                       continue; //next yy.... different set of nTC's....
                       
                 //same set of nTC's involved............
                 ++loc;
                 nTCloc[loc] = yy;
                 
                 if ( cands != 3 )
                 {
                      for ( a = 0; a < 3; ++a )
                      {
                          if ( checkCands[a] )
                             cCand = checkCands[a];
                          else
                              continue;
                          
                          for ( c = 0; c < 2; ++c )
                          {
                              if (nTCCands[c] != cCand )
                                 continue; // next c....
                                 
                              //not a new cand..........
                              break;
                          } //ends for c = .............
                          
                          if ( c == 2 )
                          {
                             //new cand.....
                             nTCCands[2] = checkCands[a];
                             a = 3; //will end a........
                          } //ends if c...
                      } // ends for a = .......
                 } // ends if cands =............
             } //ends for yy =.............
             
             if ( !New )
                continue; // next y.............
                
             //If this set of nTC's passes preliminary qualifications for the
             //extended Gordonian Rectangle.. (checkRemainder == 2), for all
             //3 of the nTC cells.. if they qualify set id = id, else id = 4...
             
             for ( yyy = 0; yyy < 3; ++yyy )
             {
                 if ( checkRemainderTable[(nTCloc[yyy])][x] == 2 )
                    continue;
                    
                 //not a qualifier........
                 break;
             } // ends for xxx= ..............
             
             if ( yyy == 3 )
                qId = id;
             else
                 qId = 4;
                 
             for ( yyy = 0; yyy < 3; ++yyy )
                 nTCIdTable[(nTCloc[yyy])][x] = qId;
                 
         } //ends for y = ...........
     } //ends for x = ...................
     
     //nTCIdTable is Set up; with 1-3, for qualifiers; 4-nonqualifiers; 0- not nTC's......
     
     //Find a qualifying nTC....................
     for ( x = 0; x < 9; ++x )
         for ( id = 1; id < 4; ++id )
         {
             fW = 0;
             Col = 9;
             fLoc = 9;
             aLoc = 9;
             bLoc = 9;
             
             for ( y = 0; y < 9; ++y )
             {
                 if ( nTCIdTable[y][x] != id )
                    continue; //next y..............
                    
                 //found a corresponding nTC.......................
                 if ( (!nDR[y][x]) && (fW) )
                    break; //from y....  these nTC's won't work... next id....
                    
                 //check if possible fWing................
                 if ( (!nDR[y][x]) && (!fW) )
                 {
                      ++fW;
                      fLoc = y;
                      continue; //next y..........
                 } //ends if !nDR............
                 
                 //Is an nDR and an nTC..........................
                 region = regionalAnswerTable[y][x];
                 
                 //Find the corresponding nDR..............
                 for ( xx = 0; xx < 9; ++xx )
                 {
                     if ( xx == x )
                        continue; //next xx............
                        
                     rr = regionalAnswerTable[y][xx];
                     
                     if ( region != rr )
                        continue;
                        
                     if ( !nDR[y][xx] )
                        continue; //next xx....
                        
                     //found an nDR, is it the corresponding nDR?...............
                     for ( z = 0; z < 9; ++z )
                         if ( checkTable[z][y][xx] != checkTable[z][y][x] )
                            break; //from for z =..........
                            
                     if ( z != 9 )
                        continue; // next xx... not a corresponding nDR.....
                        
                     //corresponding nDR's at [y][x] and [y][xx]....
                     break;
                 } //ends for xx = ...................
                 
                 if ( Col == 9 )
                 {
                      Col = xx;
                      aLoc = y;
                      continue; //next y.........
                 } // ends if Col..........
                 
                 //This is the second nTC with nDR- the corresponding nDR's must
                 //be in the same column............
                 for ( xxx = 0; xxx < 9; ++xxx )
                 {
                     if ( xxx == x )
                        continue; //next xxx.........
                        
                     if ( !nDR[y][xxx] )
                        continue; //next xxx........
                        
                     //found nDR...is it corresponding nDR?.......
                     for ( z = 0; z < 9; ++z )
                         if ( checkTable[z][y][xxx] != checkTable[z][y][x] )
                            break;  //from for z = ..........
                            
                     if ( z == 9 )
                        //found corresponding nDR.....
                        break; //from for xxx = .........
                 } // ends for xxx = ..........
                 
                 //Check to see if corresponding nDR, is in the same col [xx]...
                 bLoc = y;
                 
                 for ( z = 0; z < 9; ++z )
                     if ( checkTable[z][y][Col] != checkTable[z][y][xxx] )
                        break; //from for z.....nDR's not in same cols......
                        
                 if ( z != 9 )
                 {
                      //nTC's won't qualify for extended Gordonian Rectangle...
                      //goto next id.....
                      y = 9;
                      continue; //next y....but will end the y's and go to next id...
                 }  //ends if z !=............
             } //ends for y = .............. 
             
             if ( (y == 10) || (bLoc == 9) )
                continue; //next id...............
                
             //Now need to check the fWing location-[fLoc][Col] to see if it qualifies....
             // 2 of the cands = cands at nTC[fLoc][x]..
             
                
             for ( z = 0; z < 9; ++z )
                 if ( checkTable[z][fLoc][x] )
                    if ( !checkTable[z][fLoc][Col] )
                       break; //from for z.... doesn't have both cands......
                       
             if ( z != 9 )
                continue; //next id..........
                
             //Found the fWing-- Zap the 2 NTCCands from [fLoc][x], at the fWing [fLoc][Col]...
             for ( z = 0; z < 9; ++z )
                 if ( checkTable[z][fLoc][x] )
                    {
                         checkTable[z][fLoc][Col] = 0;
                         --checkRemainderTable[fLoc][Col];
                         ++changes;
         printf("Zapped cand=%d at [%d][%d]..in extendGordRectCol..\t", (z + 1), fLoc, Col);
                    } // ends if cT ..//ends for z = ..........
                    
             if ( !checkRemainderTable[fLoc][Col] )
             {
                printf("SUDOKU PUZZLE DOES NOT HAVE A UNIQUE SOLUTION. QUIT PUZZLE.\n");
                printf("The Gordonian Vertex is at [%d][%d].in extendGordRectCol..\n", fLoc, Col);
                errCode = 1;
                
                system("pause");
                return;
             } //ends if cRT..........
                    
             if ( changes > 0 )
                return;
     } //ends for id = .//ends for x =.............
     
     return;
} 
                                                     
             
