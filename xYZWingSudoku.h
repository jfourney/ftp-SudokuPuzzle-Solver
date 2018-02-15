// xYZWing processing for Sudoku. ************************************

/*
//Function Declarations. ***************************
void xYZWingRowRegion (void);
void xYZWingColumnRegion (void);
*/

//xYZWingRowRegion Function *********************************
void xYZWingRowRegion (void)
{
     int x, y, z, t, tt, a, aa, r, c, rr, rrr, ccc, region, u, uu;
     int xCandidate, yCandidate, zCandidate;
     int doublesTable[9][9][2]; // dt[y][x][z+1] *************
     int triplesTable[9][9][3];
     
     // SET UP A DOUBLE TABLE, AND A TRIPLE TABLE- AFTER INITIALIZATION. *******
     // THEY'RE GLOBAL TABLES, FOR DEBUG PURPOSES OF PRINTING. *********
     
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
     // set up doublesTable. ******************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             if ( checkRemainderTable[y][x] == 2 )
             {
                u = 0;
                for ( z = 0; u < 2; ++z )
                    if ( checkTable[z][y][x] > 0 )
                    {
                       doublesTable[y][x][u] = (z + 1);
                       ++u;
                    }
             }  // ends if nDR ..  ends for y = .... *******************
                
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
             
  /*           // debug purposes **********
             fprintDoublesTriplesComboTable();
             system("pause");
  */           // debug purposes  **********
             
     //Link a triple, as the stem cell, into the linkTable.. *************
     for ( y = 0; y < 9; ++y )
         for ( t = 0; t < 9; ++t )
         {
             if ( triplesTable[y][t][0] == 0 )
                continue; // next t...*************
                    
             // LOOK IN THE ROW, FOR A DOUBLE THAT HAS TWO OF THE CANDIDATES,
             // OF THE STEM CELL [Y][T]. ******* THEY WILL BE THE X AND Z 
             //CANDIDATES, BUT WE DON'T KNOW WHICH, YET.
             
             for ( tt = 0; tt < 9; ++tt )
             {
                 if ( doublesTable[y][tt][0] == 0 )
                    continue;    //next tt..
                    
                 yCandidate = 0;
                 uu = 0;
                 
                 //BOTH TABLES HAVE THEIR ELEMENTS IN LOW TO HIGH SEQUENCE(IN ORDER).
                 //[Y][T]=XYZ.. [Y][TT]= XZ.. REG'S= YZ...
                 
                 for ( u = 0; ( (u < 3) && (uu < 2) ); ++u )
                     if ( doublesTable[y][tt][uu] != triplesTable[y][t][u] )
                     {
                          if ( yCandidate == 0 )
                             yCandidate = triplesTable[y][t][u];  //yCandidate, not at [y][tt]..
                          else
                              break;  // from for u = ... ************
                     } 
                     else
                         ++uu;  
                 // ends if dT .........  ends for u ... ************
                 
                 if ( u < 3 )
                    continue;  // next tt... ************  [y][tt], not a qualified row branch cell.
                    
                 // found a qualified candidate in the row.. ***********
                 // make sure the stem cell, and the row branch cell,
                 // not in the same region.**********
                 
                 region = regionalAnswerTable[y][t];
                 rr = regionalAnswerTable[y][tt];
                 
                 if ( region == rr )
                    continue;  // next tt.... ***********
                    
                 // check the region of the stem cell [y][t]- to see if there is a
                 // double with the yCandidate, and another of the triplesTable
                 // candidates. If so, that candidate will be the zCandidate, 
                 // and the third element, an xCandidate.. ******************
                 
    /*             //debug purposes
                 printf("xYZWRReg-row: yC=%d,y=%d,t=%d,tt=%d.\n", yCandidate, y, t, tt);
                 printf("trip[0]=%d,trip[1]=%d,trip[2]=%d,", triplesTable[y][t][0], \
                            triplesTable[y][t][1], triplesTable[y][t][2]);
    */             // debug purposes
                 
                 for ( a = 0; a < 9; ++a )
                 {
                     r = regionalDispatchTable[region][a].row;
                     c = regionalDispatchTable[region][a].column;
                     
                     if ( r == y )
                        continue;  // next a .. *********
                        
                     if ( doublesTable[r][c][0] == 0 )
                        continue; // next a... ************
                        
                     // check to see if [r][c] holds the yCandidate, else next tt.. *
                     if ( checkTable[(yCandidate - 1)][r][c] == 0 )
                        continue;   // next a... ****************[r][c], must hold the yCandidate..
                        
    /*                 //debug purpose
                     printf("HI,");
    */                 //debug purposes
                        
                     zCandidate = 0;
                     
                     for ( u = 0; u < 2; ++u )
                         if ( doublesTable[r][c][u] != yCandidate ) //[r][c]- holds the YZ candidates.
                            zCandidate = doublesTable[r][c][u];  // ends for u = ..
                            
                     for ( u = 0; u < 3; ++u )
                         if ( zCandidate == triplesTable[y][t][u] )
                            break;
                            
                     if ( u == 3 )
                        continue;  // next a.. ******** didn't hold the zCandidate...
                        
      /*               //debug purposes
                     printf("zC=%d.\n", zCandidate);
      */               //debug purposes
                        
                     for ( u = 0; u < 2; ++u )
                         if ( doublesTable[y][tt][u] != zCandidate )
                         {
                            xCandidate = doublesTable[y][tt][u];  //[y][tt]- holds the XZcandidates..
                            break;
                         } // ends for u ... *******
                         
                     // have an xYYZWingRowRegion achieved. ***********
                     //XYZ- STEM CELL AT [Y][T]...
                     //XZ- ROW BRANCH CELL AT [Y][TT]...
                     //YZ- REGION BRANCH CELL AT [R][C]....
                     
      /*               // debug purposes  *****
                     printf("xYZWingRowRegion achieved at [%d][%d].\n", y, t);
                     printf("xC=%d, yC=%d, zC=%d, ", xCandidate, yCandidate, zCandidate);
                     printf("y=%d, t=%d, tt=%d, r=%d, c=%d.\n", y, t, tt, r, c);
      */               // debug purposes ************
                     
                     
                     //ZAP ZCANDIDATES AT R = Y; FOR THE REGION OF THE STEM CELL
                     // [Y][T] .....already assigned to variable, region...
                     
                     for ( aa = 0; aa < 9; ++aa )
                     {
                         rrr = regionalDispatchTable[region][aa].row;
                         ccc = regionalDispatchTable[region][aa].column;
                         
                         if ( rrr != y )
                            continue;   // next aa.... ***************
                            
                         if ( ccc == t )
                            continue; // next aa ... *************
                            
                         // zap zCandidates here... *********
                         if ( checkTable[(zCandidate - 1)][rrr][ccc] > 0 )
                         {
                              //zap element ***********
                              checkTable[(zCandidate - 1)][rrr][ccc] = 0;
                              --checkRemainderTable[rrr][ccc];
                              ++changes;
             printf("Zapped xC=%d at [%d][%d]- in xYZWingRowReg...\t", zCandidate, rrr, ccc);   // debug purposes 
                         }  //ends if cT... ********
                     }  // ends for aa ... *************
                     
                     if ( changes > 0 )
                        return;
                 }  // ends for a... *******} 
             }  // ends for tt... ****
         }  // ends for t.. ***
     // ends for y... **********
     
     return;
}


//xYZWingColumnRegion Function *********************************
void xYZWingColumnRegion (void)
{
     int x, y, z, t, tt, a, aa, r, c, rr, rrr, ccc, region, u, uu;
     int xCandidate, yCandidate, zCandidate;
     int doublesTable[9][9][2]; // dt[y][x][z+1] *************
     int triplesTable[9][9][3];
     
     // SET UP A DOUBLE TABLE, AND A TRIPLE TABLE- AFTER INITIALIZATION. *******
         
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y)
             for ( u = 0; u < 3; ++u )
                 if ( u == 2 )
                    triplesTable[y][x][2] = 0;
                 else
                     {
                         triplesTable[y][x][u] = 0;
                         doublesTable[y][x][u] = 0;
                     }  // ends for y = .... *************
     // set up doublesTable. ******************
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             if ( checkRemainderTable[y][x] == 2 )
             {
                u = 0;
                for ( z = 0; u < 2; ++z )
                    if ( checkTable[z][y][x] > 0 )
                    {
                       doublesTable[y][x][u] = (z + 1);
                       ++u;
                    }
             }  // ends if nDC ..  ends for x = .... *******************
                
     // set up triplesTable. *********************************
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             if ( checkRemainderTable[y][x] == 3 )
             {
                  u = 0;
                  for ( z = 0; u < 3; ++z )
                      if ( checkTable[z][y][x] > 0 )
                      {
                           triplesTable[y][x][u] = (z + 1);
                           ++u;
                      }
             }  // ends if cRT... ends for y....   ends for x.... **********
             
     //Link a triple, as the stem cell, into the linkTable.. *************
     for ( x = 0; x < 9; ++x )
         for ( t = 0; t < 9; ++t )
         {
             if ( triplesTable[t][x][0] == 0 )
                continue;  // next t.... ***************
                    
             // LOOK IN THE COLUMN, FOR A DOUBLE THAT HAS TWO OF THE CANDIDATES,
             // OF THE STEM CELL [T][X]. ******* THEY WILL BE THE X AND Z 
             //CANDIDATES, BUT WE DON'T KNOW WHICH, YET.
             
             for ( tt = 0; tt < 9; ++tt )
             {
                 if ( doublesTable[tt][x][0] == 0 )
                    continue;
                    
                 yCandidate = 0;
                 uu = 0;
                 
                 for ( u = 0; ( (u < 3) && (uu < 2) ); ++u )
                     if ( doublesTable[tt][x][uu] != triplesTable[t][x][u] )
                     {
                          if ( yCandidate == 0 )
                             yCandidate = triplesTable[t][x][u];
                          else
                              break;  // from for u = ... ************
                     } 
                     else
                         ++uu;  
                   // ends if dT .........  ends for u ... ************
                 
                 if ( u < 3 )
                    continue;  // next tt... ************
                    
                 // found a qualified candidate in the column.. ***********
                 // make sure the stem cell, and the column branch cell,
                 // not in the same region.**********
                 
                 region = regionalAnswerTable[t][x];
                 rr = regionalAnswerTable[tt][x];
                 
                 if ( region == rr )
                    continue;  // next tt.... ***********
                    
                 // check the region of the stem cell [y][t]- to see if there is a
                 // double with the yCandidate, and another of the triplesTable
                 // candidates. If so, that candidate will be the zCandidate, 
                 // and the third element, an xCandidate.. ******************
                 
 /*                //debug purposes
                 printf("xYZWCReg-col: yC=%d,x=%d,t=%d,tt=%d,", yCandidate, x, t, tt);
                 printf("trip[0]=%d,trip[1]=%d,trip[2]=%d.\n", triplesTable[t][x][0], \
                            triplesTable[t][x][1], triplesTable[t][x][2]);
 */                // debug purposes
                 
                 for ( a = 0; a < 9; ++a )
                 {
                     r = regionalDispatchTable[region][a].row;
                     c = regionalDispatchTable[region][a].column;
                     
                     if ( c == x )
                        continue;  // next a .. *********
                        
                     if ( doublesTable[r][c][0] == 0 )
                        continue; // next a... ************
                        
                     // check to see if [r][c] holds the yCandidate, else next tt.. *
                     if ( checkTable[(yCandidate - 1)][r][c] == 0 )
                        continue;   // next a... ****************
                        
  /*                   //debug purpose
                     printf("HI,");
  */                   //debug purposes
                        
                     zCandidate = 0;
                     
                     for ( u = 0; u < 2; ++u )
                         if ( doublesTable[r][c][u] != yCandidate )
                            zCandidate = doublesTable[r][c][u];  // ends for u = ..
                            
                     for ( u = 0; u < 3; ++u )
                         if ( zCandidate == triplesTable[t][x][u] )
                            break;
                            
                     if ( u == 3 )
                        continue;  // next a.. ********
                        
    /*                 //debug purposes
                     printf("zC=%d.\n", zCandidate);
    */                 //debug purposes
                        
                     for ( u = 0; u < 2; ++u )
                         if ( doublesTable[tt][x][u] != zCandidate )
                         {
                            xCandidate = doublesTable[tt][x][u];
                            break;
                         } // ends for u ... *******
                         
                     // have an xYYZWingColumnRegion achieved. ***********
                     //XYZ- STEM CELL AT [T][X]...
                     //XZ- ROW BRANCH CELL AT [TT][X]...
                     //YZ- REGION BRANCH CELL AT [R][C]....
                     
     /*                // debug purposes  *****
                     printf("xYZWingColumnRegion achieved at [%d][%d].\n", t, x);
                     printf("xC=%d, yC=%d, zC=%d, ", xCandidate, yCandidate, zCandidate);
                     printf("x=%d, t=%d, tt=%d, r=%d, c=%d.\n", x, t, tt, r, c);
     */                // debug purposes ************
                     
                     //ZAP ZCANDIDATES AT C = X; FOR THE REGION OF THE STEM CELL
                     // [T][X] .....already assigned to variable, region...
                     
                     for ( aa = 0; aa < 9; ++aa )
                     {
                         rrr = regionalDispatchTable[region][aa].row;
                         ccc = regionalDispatchTable[region][aa].column;
                         
                         if ( ccc != x )
                            continue;   // next aa.... ***************
                            
                         if ( rrr == t )
                            continue; // next aa ... *************
                            
                         // zap zCandidates here... *********
                         if ( checkTable[(zCandidate - 1)][rrr][ccc] > 0 )
                         {
      /*                        //debug purposes....
                              printf("DEBUGGING IN XYZWING-COLUMN-REGION...\n");
                              printf("xC=%d, yC=%d, zC=%d, ", xCandidate, yCandidate, zCandidate);
                              printf("reg=%d, rr=%d, t=%d, tt=%d, x=%d, ", region, rr, t, tt, x);
                              printf("trip[0]=%d, trip[1]=%d, trip[2]=%d..\n", triplesTable[t][x][0], \
                                 triplesTable[t][x][1], triplesTable[t][x][2]);
                              deBug();
      */                        //debug purposes.....
                              
                              //zap element ***********
                              checkTable[(zCandidate - 1)][rrr][ccc] = 0;
                              --checkRemainderTable[rrr][ccc];
                              ++changes;
        printf("Zapped xC=%d at [%d][%d]- in xYZWingColReg...\t", zCandidate, rrr, ccc);   // debug purposes 
                         }  //ends if cT... ********
                     }  // ends for aa ... *************
                     
                     if ( changes > 0 )
                        return;
                 }  // ends for a... *******} 
             }  // ends for tt... ****
         }  // ends for t.. ***
     // ends for x... **********
     
     return;
}



                 
                     
                 
