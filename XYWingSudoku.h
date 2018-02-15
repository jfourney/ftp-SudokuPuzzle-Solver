//XYWing Processing for Sudoku. ***************************

/*
//Function Declarations ***********************************
void xYWingRowColumn (void);
void xYWingRowRegion (void);
void xYWingColumnRegion (void);
*/


//xYWingRowColumn Function ****************************************************
void xYWingRowColumn (void)
{
     int x, y, z, zCount, u, uu, uuu, yy, t, tt, cand, xCandidate, zCandidate, yCandidate, uniqueCandTable[3];
     int doublesTable[9][9][2]; // dt[y][x][z+1] *************
     
     //Initialize doublesTable to zero. *******************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 2; ++z )
                 doublesTable[y][x][z] = 0;
     
     //Set-Up doublesTable ******************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 2 )
                if ( (nDR[y][x] == 0) && (nDC[y][x] == 0) )
                {
                   zCount = 0;
                   for ( z = 0; zCount < 2; ++z )
                        if ( checkTable[z][y][x] > 0 )
                        {
                           doublesTable[y][x][zCount] = (z + 1);
                           ++zCount;
                        }  // ends if cT ... ********
                }  // ends if nDR ... **********
     //doublesTable is SET UP... ******************************************
     
/*     // debug purposes
     //fprintCheckTable();
     printf("Here's the doublesTable for xYWingRowColumn. no nDR's, no nDC's.\n");
     printDoublesTable();
*/     // debug purposes
     
     for ( y = 0; y < 9; ++y )
         for ( t = 0; t < 8; ++t )
         {
             if ( doublesTable[y][t][0] == 0 )
                continue;   // next t.... ***********
                
             // have first element of linkTable. Put in uniqueTable. ***********
             for ( u = 0; u < 2; ++u )
                 uniqueCandTable[u] = doublesTable[y][t][u];
                 
             // try to link a second element, in the row, to the linkTable.... *
             for ( tt = (t + 1); tt < 9; ++tt )
             {
                 if ( doublesTable[y][tt][0] == 0 )
                    continue;   // next tt... ****************
                    
                 //FOUND A CANDIDATE FOR 2ND ELEMENT OF LINKTABLE. ONE, AND ONLY
                 //ONE, OUT OF THE TWO CANDIDATES, MUST BE UNIQUE. THE UNIQUE 
                 // CANDIDATE HERE (ZCANDIDATE), YOU'LL END UP ZAPPING AT
                 // LOCATION YY,TT (IF THERE IS ONE). THE UNIQUE CANDIDATE FROM
                 // THE FIRST SET(YCANDIDATE), AND THE ZCANDIDATE, IS WHAT YOU
                 //WILL BE SEARCHING FOR IN COLUMN-T.
                 
                 for ( u = 0; u < 2; ++u )
                 {
                     cand = uniqueCandTable[u];
                     for ( uu = 0; uu < 2; ++uu )
                         if ( doublesTable[y][tt][uu] == cand )
                         {
                              // have a link ********************************
                              yCandidate = uniqueCandTable[u];
                              if ( u == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              xCandidate = uniqueCandTable[uuu];
                              
                              if ( uu == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              zCandidate = doublesTable[y][tt][uuu];
                              cand = 0;
                              break;   // from for uu = ...... **************
                         }  //ends for uu = ... ******************
                         
                         if ( cand == 0 )
                            break;  // from for u = ***********************
                 }  // ends for u = .......********************************
                 
                 if ( cand != 0 )
                    continue;  // next tt .... ****************************
                    
                 // have a successful link in the row- now check column for
                 // doublesTable[yy][t][0-1] == xCandidate, zCandidate... ****
                 
                 for ( yy = 0; yy < 9; ++yy )
                 {
                     if ( yy == y )
                        continue;  //next yy
                        
                     if ( (doublesTable[yy][t][0] == xCandidate) || \
                          (doublesTable[yy][t][0] == zCandidate) )
                          if ( (doublesTable[yy][t][1] == xCandidate ) || \
                               (doublesTable[yy][t][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingRowColumn achieved..
                                                             
                               
                               if ( checkTable[(zCandidate - 1)][yy][tt] > 0 )
                               {
                                    //zap element, etc... **********
                                    checkTable[(zCandidate - 1)][yy][tt] = 0;
                                    --checkRemainderTable[yy][tt];
                                    ++changes;
          printf("Zapped xC=%d at [%d][%d]- in xYWingRowCol.1..\t", (z + 1), yy, tt);   // debug purposes 
                             
      /*                               // debug purposes **************
                                    printf("xYWingRowColumn-t achieved.\n");
      */                              // debug purposes  ******************
                                    
                                    return;
                               }  // ends if cT .... *****
                          }  // ends if dt ..... ***********
                 }  //ends for yy = ..... *************
                 
                 //FOR TT PROCESSING: WHERE STEM CELL IS AT [Y][TT], NOT AT [Y][T].
                 // have a successful link in the row- now check column for
                 // doublesTable[yy][tt][0-1] == xCandidate, zCandidate... ****
                 
                 for ( yy = 0; yy < 9; ++yy )
                 {
                     if ( yy == y )
                        continue;  //next yy.....
                        
                     if ( (doublesTable[yy][tt][0] == xCandidate) || \
                          (doublesTable[yy][tt][0] == zCandidate) )
                          if ( (doublesTable[yy][tt][1] == xCandidate ) || \
                               (doublesTable[yy][tt][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingRowColumn achieved..
                               
                               
                               
                               //ZAP XCANDIDATE AT [YY][TT]-- REALLY THE XCANDIDATE
                               //BECOMES THE ZCANDIDATE, AND THE ZCANDIDATE BECOMES
                               //THE XCANDIDATE... ********************************
                               
                               if ( checkTable[(xCandidate - 1)][yy][t] > 0 )
                               {
                                    //zap element, etc... **********
                                    checkTable[(xCandidate - 1)][yy][t] = 0;
                                    --checkRemainderTable[yy][t];
                                    ++changes;
             printf("Zapped xC=%d at [%d][%d]- in xYWingRowCol.2..\t", (z + 1), yy, t);   // debug purposes 
                                    
                                    return;
         /*                           // debug purposes **************
                                    printf("xYWingRowColumn-tt achieved.\n");
         */                           // debug purposes  ******************
                                    
                               }  // ends if cT .... *****
                          }  // ends if dt ..... ***********
                 } //ends for yy = ..... *************
                 
                 
             }  // ends for tt = .... **************
         }  // ends for t = .... ************************
     // ends for y = ..... ***********************
/*     
     for ( y = 8; y > 0; --y )
         for ( t = 0; t < 8; ++t )
         {
             if ( doublesTable[y][t][0] == 0 )
                continue;   // next t.... ***********
                
             // have first element of linkTable. Put in uniqueTable. ***********
             for ( u = 0; u < 2; ++u )
                 uniqueCandTable[u] = doublesTable[y][t][u];
                 
             // try to link a second element, in the row, to the linkTable.... *
             for ( tt = (t + 1); tt < 9; ++tt )
             {
                 if ( doublesTable[y][tt][0] == 0 )
                    continue;   // next tt... ****************
                    
                 //FOUND A CANDIDATE FOR 2ND ELEMENT OF LINKTABLE. ONE, AND ONLY
                 //ONE, OUT OF THE TWO CANDIDATES, MUST BE UNIQUE. THE UNIQUE 
                 // CANDIDATE HERE (ZCANDIDATE), YOU'LL END UP ZAPPING AT
                 // LOCATION YY,TT (IF THERE IS ONE). THE UNIQUE CANDIDATE FROM
                 // THE FIRST SET(YCANDIDATE), AND THE ZCANDIDATE, IS WHAT YOU
                 //WILL BE SEARCHING FOR IN COLUMN-T.
                 
                 for ( u = 0; u < 2; ++u )
                 {
                     cand = uniqueCandTable[u];
                     for ( uu = 0; uu < 2; ++uu )
                         if ( doublesTable[y][tt][uu] == cand )
                         {
                              // have a link ********************************
                              yCandidate = uniqueCandTable[u];
                              
                              if ( u == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              xCandidate = uniqueCandTable[uuu];
                              
                              if ( uu == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              zCandidate = doublesTable[y][tt][uuu];
                              cand = 0;
                              break;   // from for uu = ...... **************
                         }  //ends for uu = ... ******************
                         
                         if ( cand == 0 )
                            break;  // from for u = ***********************
                 }  // ends for u = .......********************************
                 
                 if ( cand != 0 )
                    continue;  // next tt .... ****************************
                    
                 // have a successful link in the row- now check column for
                 // doublesTable[yy][t][0-1] == xCandidate, zCandidate... ****
                 
                 for ( yy = (y - 1); yy > 0; --yy )
                     if ( (doublesTable[yy][t][0] == xCandidate) || \
                          (doublesTable[yy][t][0] == zCandidate) )
                          if ( (doublesTable[yy][t][1] == xCandidate ) || \
                               (doublesTable[yy][t][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingRowColumn achieved..
                                                             
                               
                               if ( checkTable[(zCandidate - 1)][yy][tt] > 0 )
                               {
                                    //zap element, etc... **********
                                    checkTable[(zCandidate - 1)][yy][tt] = 0;
                                    --checkRemainderTable[yy][tt];
                                    ++changes;
            printf("Zapped xC=%d at [%d][%d]- in xYWingRowCol.3..\t", (z + 1), yy, tt);   // debug purposes 
                             
           //                          // debug purposes **************
           //                         printf("xYWingRowColumn-t- achieved.\n");
           //                         // debug purposes  ******************
                                    
                                    return;
                               }  // ends if cT .... *****
                          }  // ends if dt ..... ***********
                 //ends for yy = ..... *************
                 
                 // have a successful link in the row- now check column for
                 // doublesTable[yy][tt][0-1] == xCandidate, zCandidate... ****
                 // Actually, the xCandidate becomes the zCandidate, and vice versa.
                 // But for brevity, we'll zap the xCandidate at [yy][t]...*****
                 
                 for ( yy = (y - 1); yy > 0; --yy )
                     if ( (doublesTable[yy][tt][0] == xCandidate) || \
                          (doublesTable[yy][tt][0] == zCandidate) )
                          if ( (doublesTable[yy][tt][1] == xCandidate ) || \
                               (doublesTable[yy][tt][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingRowColumn achieved..
                               
                               
                               
                               
                               if ( checkTable[(xCandidate - 1)][yy][t] > 0 )
                               {
                                    //zap element, etc... **********
                                    checkTable[(xCandidate - 1)][yy][t] = 0;
                                    --checkRemainderTable[yy][t];
                                    ++changes;
            printf("Zapped xC=%d at [%d][%d]- in xYWingRowCol.4..\t", (z + 1), y, x);   // debug purposes 
                                    
                                    
         //                           // debug purposes **************
         //                           printf("xYWingRowColumn-tt- achieved.\n");
         //                           // debug purposes  ******************
                                    return;
                               }  // ends if cT .... *****
                          }  // ends if dt ..... ***********
                 //ends for yy = ..... *************
                 
                 
             }  // ends for tt = .... **************
         }  // ends for t = .... ************************
     // ends for y = ..... ***********************
*/     
     return;
}
                             
//xYWingRowRegion Function ****************************************************
void xYWingRowRegion (void)
{
     int region, a, aa, r, rr, ccc, rrr, c;
     int x, y, z, zCount, u, uu, uuu, t, tt, cand, xCandidate, yCandidate, zCandidate, uniqueCandTable[3];
     int doublesTable[9][9][2]; // dt[y][x][z+1] *************
     
     //Initialize doublesTable to zero. *******************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 2; ++z )
                 doublesTable[y][x][z] = 0;
     
     //Set-Up doublesTable ******************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 2 )
                if ( nDR[y][x] == 0  )
                {
                   zCount = 0;
                   for ( z = 0; zCount < 2; ++z )
                        if ( checkTable[z][y][x] > 0 )
                        {
                           doublesTable[y][x][zCount] = (z + 1);
                           ++zCount;
                        }  // ends if cT ... ********
                }  // ends if nDR ... **********
     //doublesTable is SET UP... ******************************************
     
 /*    // debug purposes
     system("pause");
     fprintCheckTable();
     printf("Here's the doublesTable for xYWingRowRegion. no nDR's, no nDReg's.\n");
     printDoublesTable();
 */    // debug purposes
     
     for ( y = 0; y < 8; ++y )
         for ( t = 0; t < 8; ++t )
         {
             if ( doublesTable[y][t][0] == 0 )
                continue;   // next t.... ***********
                
             // have first element of linkTable. Put in uniqueTable. ***********
             for ( u = 0; u < 2; ++u )
                 uniqueCandTable[u] = doublesTable[y][t][u];
                 
             // try to link a second element, in the row, to the linkTable.... *
             for ( tt = (t + 1); tt < 9; ++tt )
             {
                 if ( doublesTable[y][tt][0] == 0 )
                    continue;   // next tt... ****************
                    
                 //FOUND A CANDIDATE FOR 2ND ELEMENT OF LINKTABLE. ONE, AND ONLY
                 //ONE, OUT OF THE TWO CANDIDATES, MUST BE UNIQUE. THE UNIQUE 
                 // CANDIDATE HERE (ZCANDIDATE), YOU'LL END UP ZAPPING AT
                 // LOCATION r,TT (IF THERE IS ONE). THE UNIQUE CANDIDATE FROM
                 // THE FIRST SET(YCANDIDATE), AND THE ZCANDIDATE, IS WHAT YOU
                 //WILL BE SEARCHING FOR IN COLUMN-T.
                 
                 for ( u = 0; u < 2; ++u )
                 {
                     cand = uniqueCandTable[u];
                     for ( uu = 0; uu < 2; ++uu )
                         if ( doublesTable[y][tt][uu] == cand )
                         {
                              // have a link ********************************
                              yCandidate = uniqueCandTable[u];
                              if ( u == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              xCandidate = uniqueCandTable[uuu];
                              
                              if ( uu == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              zCandidate = doublesTable[y][tt][uuu];
                              cand = 0;
                              break;   // from for uu = ...... **************
                         }  //ends for uu = ... ******************
                         
                         if ( cand == 0 )
                            break;  // from for u = ***********************
                 }  // ends for u = .......********************************
                 
                 if ( cand != 0 )
                    continue;  // next tt .... ****************************
                    
                 // have a successful link in the row- now check region for
                 // doublesTable[r][c][0-1] == xCandidate, yCandidate... ****
                 
                 region = regionalAnswerTable[y][t];
                 rr = regionalAnswerTable[y][tt];
                 
                 if ( region == rr )
                    continue;   // next tt... ************
                    
  /*               //debug purposes
                 printf("reg=%d, rr=%d..\t", region, rr);
  */               //debug purposes...
                 
                 for ( a = 0; a < 9; ++a )
                 {
                     r = regionalDispatchTable[region][a].row;
                     c = regionalDispatchTable[region][a].column;
                     if ( r == y )
                        continue;  // next a.. ************
                        
                     if ( (doublesTable[r][c][0] == xCandidate) || \
                          (doublesTable[r][c][0] == zCandidate) )
                          if ( (doublesTable[r][c][1] == xCandidate ) || \
                               (doublesTable[r][c][1] == zCandidate ) )
                          {
                               //linked an element in the region, for xYWing.
                               //xYWingRowRegion achieved..
                               
                               //NOTE: OUR TERMINOLOGY. XY(STEM CELL) = [Y][T] 
                               // YZ(ROW BRANCH CELL) = [Y][TT]
                               // XZ(REGION BRANCH CELL) = [R][C].... ********
                               
                               // ZAP ZCANDIDATES, SAME REGION, SAME ROW AS STEM CELL [Y][T]..
                               // region already is set at [y][t] region...
                               
    /*                           //debug purposes.....................
                               printf("xYWingRowRegion achieved.tproc...y=%d, t=%d, tt=%d, r=%d, c=%d, xCand=%d, yCand=%d, \
                               zCand=%d,region=%d, rr=%d...\n", y, t, tt, r, c, xCandidate, yCandidate, zCandidate, \
                               region, rr);
                               deBug();
                               system("pause");
    */                           //debug purposes......................
                                                              
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[region][aa].row;
                                   ccc = regionalDispatchTable[region][aa].column;
                                   
                                   if ( rrr != y )
                                      continue;  // next aa.. *****
                                      
                                   if ( ccc == t )
                                      continue;  // next aa...******
                                      
                                   if ( checkTable[(zCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(zCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
          printf("Zapped xC=%d at [%d][%d]- in xYWingRowReg.1..\t", zCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               // ZAP ZCANDIDATES FROM ROW R(REGION BRANCH CELL'S ROW)-
                               // FOR THE REGION OF [Y][TT]- (THE ROW BRANCH CELL)...
                               
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[rr][aa].row;
                                   ccc = regionalDispatchTable[rr][aa].column;
                                   
                                   if ( rrr != r )
                                      continue;  // next aa.. *****
                                      
                                   if ( checkTable[(zCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(zCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
        printf("Zapped xC=%d at [%d][%d]- in xYWingRowReg.2..\t", zCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               if ( changes > 0 )
                                  return;
                                  
                                                               
   /*                                 // debug purposes **************
                                    printf("xYWingRowRegion-t achieved.\n");
   */                                 // debug purposes  ******************
                                    
                                    
                               
                          }  // ends if dt ..... ***********
                 }  //ends for a = ..... *************
                 // TT-PROCESSING: WHERE THE STEM CELL IS [Y][TT], NOT [Y][T]...
                 // have a successful link in the row- now check region for
                 // doublesTable[r][c][0-1] == xCandidate, yCandidate... ****
                 
                 region = regionalAnswerTable[y][tt];
                 rr = regionalAnswerTable[y][t];
                 
                 if ( region == rr )
                    continue;   // next tt... ************
                    
                 for ( a = 0; a < 9; ++a )
                 {
                     r = regionalDispatchTable[region][a].row;
                     c = regionalDispatchTable[region][a].column;
                     if ( r == y )
                        continue;  // next a.. ************
                        
                     if ( (doublesTable[r][c][0] == xCandidate) || \
                          (doublesTable[r][c][0] == zCandidate) )
                          if ( (doublesTable[r][c][1] == xCandidate ) || \
                               (doublesTable[r][c][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingRowColumn achieved..
                               
                               // TT PROCESSING: [Y][TT] IS THE STEM CELL..
                               // YZ- STEM CELL..IS [Y][TT]....
                               // XY- ROW BRANCH CELL.. IS [Y][T]....
                               // XZ- REGION BRANCH CELL.. IS [R][C].....
                               
                               // ZAP XCANDIDATES FROM SAME REGION, SAME ROW, AS THE
                               // STEM CELL [Y][TT]..  region is already set here..
                               
         /*                      //debug purposes.....................
                               printf("xYWingRowRegion achieved.ttproc...y=%d, t=%d, tt=%d, r=%d, c=%d, xCand=%d, yCand=%d, \
                               zCand=%d,region=%d, rr=%d...\n", y, t, tt, r, c, xCandidate, yCandidate, zCandidate, \
                               region, rr);
                               deBug();
                               system("pause");
         */                      //debug purposes......................
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[region][aa].row;
                                   ccc = regionalDispatchTable[region][aa].column;
                                   
                                   if ( rrr != y )
                                      continue;  // next aa.. *****
                                      
                                   if ( ccc == tt )
                                      continue;  // next aa...******
                                      
                                   if ( checkTable[(xCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(xCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
           printf("Zapped xC=%d at [%d][%d]- in xYWingRowReg.3..\t", xCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               // ZAP XCANDIDATES FROM ROW R(REGION BRANCH CELL'S ROW)-
                               // FOR THE REGION OF [Y][T]- (THE ROW BRANCH CELL)...
                               
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[rr][aa].row;
                                   ccc = regionalDispatchTable[rr][aa].column;
                                   
                                   if ( rrr != r )
                                      continue;  // next aa.. *****
                                      
                                   if ( checkTable[(xCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(xCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
            printf("Zapped xC=%d at [%d][%d]- in xYWingRowReg.4..\t", xCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               if ( changes > 0 )
                                  return;
                                  
                                                               
                               
                                                                  
     /*                               // debug purposes **************
                                    printf("xYWingRowRegion-tt achieved.\n");
     */                               // debug purposes  ******************
                                    
                                    
                          }  // ends if dt ..... ***********
                 }  //ends for a = ..... *************
                 
                 
             }  // ends for tt = .... **************
         }  // ends for t = .... ************************
     // ends for y = ..... ***********************
     
     return;
}
                             
//xYWingColumnRegion Function ****************************************************
void xYWingColumnRegion (void)
{
     int region, a, r, rr, c, aa, rrr, ccc;
     int x, y, z, zCount, u, uu, uuu, t, tt, cand, xCandidate, yCandidate, zCandidate, uniqueCandTable[3];
     int doublesTable[9][9][2]; // dt[y][x][z+1] *************
     
     //Initialize doublesTable to zero. *******************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 2; ++z )
                 doublesTable[y][x][z] = 0;
     
     //Set-Up doublesTable ******************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 2 )
                if ( nDC[y][x] == 0 )
                {
                   zCount = 0;
                   for ( z = 0; zCount < 2; ++z )
                        if ( checkTable[z][y][x] > 0 )
                        {
                           doublesTable[y][x][zCount] = (z + 1);
                           ++zCount;
                        }  // ends if cT ... ********
                }  // ends if nDR ... **********
     //doublesTable is SET UP... ******************************************
     
/*     // debug purposes
     system("pause");
     fprintCheckTable();
     printf("Here's the doublesTable for xYWingColumnRegion. no nDC's, no nDReg's.\n");
     printDoublesTable();
*/     // debug purposes
     
     for ( x = 0; x < 8; ++x )
         for ( t = 0; t < 8; ++t )
         {
             if ( doublesTable[t][x][0] == 0 )
                continue;   // next t.... ***********
                
             
             // have first element of linkTable. Put in uniqueTable. ***********
             for ( u = 0; u < 2; ++u )
                 uniqueCandTable[u] = doublesTable[t][x][u];
                 
             // try to link a second element, in the row, to the linkTable.... *
             for ( tt = (t + 1); tt < 9; ++tt )
             {
                 if ( doublesTable[tt][x][0] == 0 )
                    continue;   // next tt... ****************
                    
                 //FOUND A CANDIDATE FOR 2ND ELEMENT OF LINKTABLE. ONE, AND ONLY
                 //ONE, OUT OF THE TWO CANDIDATES, MUST BE UNIQUE. THE UNIQUE 
                 // CANDIDATE HERE (ZCANDIDATE), YOU'LL END UP ZAPPING AT
                 // LOCATION TT,C (IF THERE IS ONE). THE UNIQUE CANDIDATE FROM
                 // THE FIRST SET(YCANDIDATE), AND THE ZCANDIDATE, IS WHAT YOU
                 //WILL BE SEARCHING FOR IN COLUMN-T.
                 
                 for ( u = 0; u < 2; ++u )
                 {
                     cand = uniqueCandTable[u];
                     for ( uu = 0; uu < 2; ++uu )
                         if ( doublesTable[tt][x][uu] == cand )
                         {
                              // have a link ********************************
                              yCandidate = uniqueCandTable[u];
                              if ( u == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              xCandidate = uniqueCandTable[uuu];
                              
                              if ( uu == 0 )
                                 uuu = 1;
                              else
                                  uuu = 0;
                              zCandidate = doublesTable[tt][x][uuu];
                              cand = 0;
                              break;   // from for uu = ...... **************
                         }  //ends for uu = ... ******************
                         
                         if ( cand == 0 )
                            break;  // from for u = ***********************
                 }  // ends for u = .......********************************
                 
                 if ( cand != 0 )
                    continue;  // next tt .... ****************************
                    
                 // have a successful link in the column- now check region for
                 // doublesTable[r][c][0-1] == xCandidate, xCandidate... ****
                 
                 region = regionalAnswerTable[t][x];
                 rr = regionalAnswerTable[tt][x];
                 
                 if ( region == rr )
                    continue;  // next tt ... ****************
                 
                 for ( a = 0; a < 9; ++a )
                 {
                     r = regionalDispatchTable[region][a].row;
                     c = regionalDispatchTable[region][a].column;
                     if ( c == x )
                        continue;  // next a.. ************
                        
                     if ( (doublesTable[r][c][0] == xCandidate) || \
                          (doublesTable[r][c][0] == zCandidate) )
                          if ( (doublesTable[r][c][1] == xCandidate ) || \
                               (doublesTable[r][c][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingColumnRegion achieved..
                                                            
                               //NOTE: OUR TERMINOLOGY. XY(STEM CELL) = [T][X] 
                               // YZ(COLUMN BRANCH CELL) = [TT][X]
                               // XZ(REGION BRANCH CELL) = [R][C].... ********
                               
                               // ZAP ZCANDIDATES, SAME REGION, SAME COLUMN AS STEM CELL [T][X]..
                               // region already is set at [t][x] region...
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[region][aa].row;
                                   ccc = regionalDispatchTable[region][aa].column;
                                   
                                   if ( ccc != x )
                                      continue;  // next aa.. *****
                                      
                                   if ( rrr == t )
                                      continue;  // next aa...******
                                      
                                   if ( checkTable[(zCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(zCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
            printf("Zapped xC=%d at [%d][%d]- in xYWingColReg.1..\t", zCandidate, y, x);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               // ZAP ZCANDIDATES FROM COLUMN C(REGION BRANCH CELL'S COLUMN)-
                               // FOR THE REGION OF [TT][X]- (THE COLUMN BRANCH CELL)...
                               
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[rr][aa].row;
                                   ccc = regionalDispatchTable[rr][aa].column;
                                   
                                   if ( ccc != c )
                                      continue;  // next aa.. *****
                                      
                                   if ( checkTable[(zCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(zCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
            printf("Zapped xC=%d at [%d][%d]- in xYWingColReg.2..\t", zCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               if ( changes > 0 )
                                  return;
                                  
                                                               
                               
                                                                 
  /*                                  // debug purposes **************
                                    printf("xYWingColumnRegion-t achieved.\n");
                                    printf("x=%d,t=%d,tt=%d,r=%d,c=%d\n",x,t,tt,r,c);
                                    system("pause");
  */                                  // debug purposes  ******************
                                    
                                    
                          }  // ends if dt ..... ***********
                 }  //ends for a = ..... *************
                 
                 
                 //TT-PROCESSING: WHERE THE STEM CELL IS [TT][C] OR [TT][X]..
                 // have a successful link in the column- now check region for
                 // doublesTable[r][c][0-1] == xCandidate, xCandidate... ****
                 
                 region = regionalAnswerTable[tt][x];
                 rr = regionalAnswerTable[t][x];
                 
                 if ( region == rr )
                    continue;  // next tt ... ****************
                 
                 for ( a = 0; a < 9; ++a )
                 {
                     r = regionalDispatchTable[region][a].row;
                     c = regionalDispatchTable[region][a].column;
                     if ( c == x )
                        continue;  // next a.. ************
                        
                     if ( (doublesTable[r][c][0] == xCandidate) || \
                          (doublesTable[r][c][0] == zCandidate) )
                          if ( (doublesTable[r][c][1] == xCandidate ) || \
                               (doublesTable[r][c][1] == zCandidate ) )
                          {
                               //linked an element in the column, for xYWing.
                               //xYWingColumnRegion achieved..
                               
                               // TT PROCESSING: [TT][X] IS THE STEM CELL..
                               // YZ- STEM CELL..IS [TT[X]....
                               // XY- COLUMN BRANCH CELL.. IS [T][X]....
                               // XZ- REGION BRANCH CELL.. IS [R][C].....
                               
                               // ZAP XCANDIDATES FROM SAME REGION, SAME COLUMN, AS THE
                               // STEM CELL [TT][X]..  region is already set here..
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[region][aa].row;
                                   ccc = regionalDispatchTable[region][aa].column;
                                   
                                   if ( ccc != x )
                                      continue;  // next aa.. *****
                                      
                                   if ( rrr == tt )
                                      continue;  // next aa...******
                                      
                                   if ( checkTable[(xCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(xCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
           printf("Zapped xC=%d at [%d][%d]- in xYWingColReg.3..\t", xCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               // ZAP XCANDIDATES FROM COLUMN C(REGION BRANCH CELL'S ROW)-
                               // FOR THE REGION OF [T][X]- (THE COLUMN BRANCH CELL)...
                               
                               
                               for ( aa = 0; aa < 9; ++aa )
                               {
                                   rrr = regionalDispatchTable[rr][aa].row;
                                   ccc = regionalDispatchTable[rr][aa].column;
                                   
                                   if ( ccc != c )
                                      continue;  // next aa.. *****
                                      
                                   if ( checkTable[(xCandidate - 1)][rrr][ccc] > 0 )
                                   {
                                      //zap element, etc... **********
                                      checkTable[(xCandidate - 1)][rrr][ccc] = 0;
                                      --checkRemainderTable[rrr][ccc];
                                      ++changes;
        printf("Zapped xC=%d at [%d][%d]- in xYWingColReg.4..\t", xCandidate, rrr, ccc);   // debug purposes 
                                   } // ends if cT.. *****
                               } // ends for aa = ... *******
                               
                               if ( changes > 0 )
                                  return;
                                  
                                                               
                               
                                                            
    /*                                // debug purposes **************
                                    printf("xYWingColumnRegion achieved.\n");
                                    printf("x=%d,t=%d,tt=%d,r=%d,c=%d\n",x,t,tt,r,c);
    */                                // debug purposes  ******************
                                    
                                   
                          }  // ends if dt ..... ***********
                 }  //ends for a = ..... *************
                 
                 
             }  // ends for tt = .... **************
         }  // ends for t = .... ************************
     // ends for y = ..... ***********************
     
     //system("pause");   // debug purposes
     return;
}
                             
