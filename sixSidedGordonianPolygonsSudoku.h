//Six-Sided Gordonian Polygons Processing for Sudoku

/*
//Function Declarations **********************
void sixSidedGordPolygons (void);
*/

//sixSidedGordPolygons Function******************************
void sixSidedGordPolygons (void)
{
     int x, y, z, a, b, c, q, xx, yy, rr, rrr, xxx, yyy, rrrr, region;
     int nDSumTable[9][9], nDCandSumTable[10][10], qualifiedCandsTable[8][3];
     int candsNDSumTable[8][9][9], unifectas, difectas, trifectas;
     int qcSub, Sum, qual, qualifiers;
     
/*     //debug purposes.................
     deBug();
 */    //debug purposes..................
     
     //Add the nDTables together into an nDSumTable.****************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             nDSumTable[y][x] = (nDR[y][x] + nDC[y][x] + nDReg[y][x]);
             
     //Initialize the nDCandSumTable[10][10] ********************
     for ( a = 0; a < 10; ++a )
         for ( b = 0; b < 10; ++b )
             nDCandSumTable[a][b] = 0;
             
     //Set up nDCandSumTable **********************************
     a = 0; b = 0;
     
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             for ( z = 0; z < 9; ++z )
                 if ( nDSumTable[y][x] && checkTable[z][y][x] )
                 {
                      a = (z + 1);
                      break; //from for z =..*********
                 } // ends if nDS ***********ends for z = **********
                 
             for ( z = (z + 1); z < 9; ++z )
                 if ( checkTable[z][y][x] )
                 {
                      b = (z + 1);
                      ++nDCandSumTable[a][b];
                      break; //from z = (z + 1)... ***************
                 } //ends if cT... ends for z = (z + 1)....
         } //ends for x = .... ends for y = .... **************
         
         //nDCandTable is set up....The only qualifiers would be cand pairs
         //with a sum >= 5.......
         
         // qualifiedCandsTable[Qualifier][3]----[0]-sum of nD's for the cand pair..
         // [1]-cand1,   [2]-cand2;;;;;;;;
         
         //Initialize qualifiedCandsTable[8][3]... ******************
         for ( c = 0; c < 8; ++c )
             for ( q = 0; q < 3; ++q )
                 qualifiedCandsTable[c][q] = 0;
                 
         //Set up qualifiedCandsTable. ****************************
         qcSub = 0;
         
         for ( a = 0; a < 9; ++a )
             for ( b = (a + 1); b < 10; ++b )
                 if ( nDCandSumTable[a][b] < 5 )
                    nDCandSumTable[a][b] = 0;
                 else
                 {
                     //qualifier found ****************
                     qualifiedCandsTable[qcSub][0] = nDCandSumTable[a][b];
                     qualifiedCandsTable[qcSub][1] = a;
                     qualifiedCandsTable[qcSub][2] = b;
                     ++qcSub;
                 } //ends if nDCand.... ends for b = ....ends for a = ....******
                 
 /*        //debug purposes *******************************
         printf("Here's the nDCandSumTable[10][10]....\n");
         
         for ( a = 0; a < 10; ++a )
         {
             for ( b = 0; b < 10; ++b )
                 printf(" %d ", nDCandSumTable[a][b]);
                 
             printf("\n");
         } // ends for a = ...........
 */        //debug purposes ***************************
                 
         if ( qcSub == 0 )
            return;  // no qualifiers ***********
            
         // candsNDSumTable[Qualifier][y][x]--holds the sum of the nD's for a
         //particular cell....
         
         //Initialize candsNDSumTable[8][9][9].. **********************
         for ( q = 0; q < 8; ++q )
             for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                     candsNDSumTable[q][y][x] = 0;
                     
         //Set up candsNDSumTable ***********************
         for ( q = 0; q < qcSub; ++q )
             for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                     if ( nDSumTable[y][x] > 0 )
                        if ( checkTable[(qualifiedCandsTable[q][1] - 1)][y][x] && \
                        checkTable[(qualifiedCandsTable[q][2] - 1)][y][x] )
                           candsNDSumTable[q][y][x] = nDSumTable[y][x];
         //candsNDSumTable is set up... *************************
         
/*         //debug purposes *******************************
         for ( q = 0; q < qcSub; ++q )
         {
             printf("Here's the candsNDSumTable for (%d,%d)...\n", qualifiedCandsTable[q][1], \
                            qualifiedCandsTable[q][2]);
                            
             for ( y = 0; y < 9; ++y )
             {
                 for ( x = 0; x < 9; ++x )
                     printf(" %d ", candsNDSumTable[q][y][x]);
                     
                 printf("\n");
             } //ends for y = ...................
         }  // ends for q = ...................
*/         //debug purposes **********************************            
                     
         
         
         //Qualify the qualifiedCandsTable and if it meets all the qualifications,
         // process it...... **********************************
         for ( q = 0; q < qcSub; ++q )
         {
             unifectas = 0; difectas = 0; trifectas = 0; Sum = 0; qual = 0;
             
             for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                 {
                     if ( !candsNDSumTable[q][y][x] )
                        continue;
                        
                     Sum += candsNDSumTable[q][y][x];
                     
                     if ( candsNDSumTable[q][y][x] == 3 )
                        ++trifectas;
                     else if ( candsNDSumTable[q][y][x] == 2 )
                             ++difectas;
                          else ++unifectas;
                 } // ends for x = ...ends for y = *************
                 
             if ( Sum < 12 )
                ++qual;
                
             if ( trifectas < 2 )
                ++qual;
                
             if ( trifectas > 2 )
             {
                  if ( !difectas || !unifectas )
                     ++qual;
             }
             else if ( difectas < 3 )
                     ++qual;
                     
             if ( !qual )
             {
                ++qualifiers; 
                continue;  // next q... have a qualifier.... ***********
             } // ends if !q... *******************
             
             //Not a qualifier, set tables to zero for that q... ***********
             for ( xx = 0; xx < 3; ++xx )
                 qualifiedCandsTable[q][xx] = 0;
                 
             for ( yy = 0; yy < 9; ++yy )
                 for ( xx = 0; xx < 9; ++xx )
                     candsNDSumTable[q][yy][xx] = 0;
         } // ends for q = **************
         
 /*        //debug purposes ****************
         printf("#Qualifiers = %d....\n", qualifiers);
 */        //debug purposes ***************
         
         if ( !qualifiers )
            return;  // no qualifiers... *************
            
         
            
         //Have a (qualifier) number of possible qualifiers (cand pairs)..
         for ( q = 0; q < qcSub; ++q )
         {
             if ( !qualifiedCandsTable[q][0] )
                continue; //one that didn't pass probation ***********
                
             for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                 {
                     if ( candsNDSumTable[q][y][x] < 3 )
                        continue; // next x...
                     
                     //found a trifecta- is it the Main Anchor?
                     //must find a corresponding trifecta in the row and column,
                     //one of which is in the same region, as this trifecta...
                     for ( xx = 0; xx < 9; ++xx )
                     {
                         if ( xx == x )
                            continue; // next xx....
                            
                         if ( candsNDSumTable[q][y][xx] < 3 )
                            continue; // next xx....
                            
                         //trifecta found at [y][xx]- one in the row...
                         break; // from for xx = ... **************
                     } //ends for xx = .. *************** 
                     
                     if ( xx == 9 )
                     continue; //next x...not a main anchor....
                     
                     for ( yy = 0; yy < 9; ++yy )
                     {
                         if ( yy == y )
                            continue; // next yy... **************
                            
                         if ( candsNDSumTable[q][yy][x] < 3 )
                            continue; // next yy.. ***********
                            
                         //found all 3 anchors*************************
                         break;
                     } //ends for yy = ...*********
                     
                     if ( yy == 9 )
                        continue; // next x...***********
                        
                     //Found main anchor- [y][x]
                     //2 wing anchors at [y][xx] and [yy][x]...
                     //Determine which wing anchors, and where....
                     
                     region = regionalAnswerTable[y][x];
                     rr = regionalAnswerTable[y][xx];
                     rrr = regionalAnswerTable[yy][x];
                     
                     if ( (rr != region) && (rrr != region) )
                        continue; //next x.....not the main anchor.........
                        
                     //if (rr == region)
                     //   [y][xx]- RB wing anchor...
                     //   [yy][x]- C wing anchor...
                     //   ;
                     //else if (rrr == region)
                     //     [yy][x]- CB wing anchor...
                     //     [y][xx]- R wing anchor....
                     //     ;
                     
                     //Found the Main Anchor- Determine the outer anchor wings....
                     if ( rr == region )
                     {
                          //Find the CB outer wing at [yyy][xx]...(candsNDSumTable == 2...
                          for ( yyy = 0; yyy < 9; ++yyy )
                          {
                              if ( yyy == y )
                                 continue; // next yyy... *******
                                 
                              if ( candsNDSumTable[q][yyy][xx] != 2 )
                                 continue; // next yyy... ****
                              
                              //found CB outer wing... *******
                              break;
                          } // ends for yyy = ... ******
                          
                          if ( yyy == 9 )
                             continue; // next x... **********
                             
                          //find the R outer wing at [yy][xxx]
                          //same column as gWing, same region as gWing...
                          for ( xxx = 0; xxx < 9; ++xxx )
                          {
                              if ( xxx == x )
                                 continue; // next xxx... *********
                                 
                              if ( candsNDSumTable[q][yy][xxx] != 1 )
                                 continue;
                                 
                              //found all 5 qualifying points...
                              break;
                          } // ends for xxx= ... **********
                          
                          if ( xxx == 9 )
                             continue; // next x.... *********
                             
                          //Now look at gWing....
                          //same row as CB outer wing [yyy].....
                          //same column as R outer wing [xxx]....
                          
                          //Does gWing contain both z-cands in question?.....
                          if ( !checkTable[(qualifiedCandsTable[q][1] - 1)][yyy][xxx] || \
                           !checkTable[(qualifiedCandsTable[q][2] - 1)][yyy][xxx] )
                             continue; // next x... gWing didn't contain both z-cands....
                             
                          //gWing contains both zCandidates..........
                          //Main Anchor-[y][x].. RB wing anchor-[y][xx]- C wing anchor-[yy][x]
                          //CB outer wing-[yyy][xx]...R outer wing-[yy][xxx].....
                          //gWing at [yyy][xxx]......
                          
                          //Zap both zCands at gWing [yyy][xxx]....
                          checkTable[(qualifiedCandsTable[q][1] - 1)][yyy][xxx] = 0;
                          --checkRemainderTable[yyy][xxx];
                          ++changes;
         printf("Zapped zC=%d at [%d][%d] in 6-sided GordPolygon-3...\t", \
                 qualifiedCandsTable[q][1], yyy, xxx);                  
                 
                           checkTable[(qualifiedCandsTable[q][2] - 1)][yyy][xxx] = 0;
                          --checkRemainderTable[yyy][xxx];
                          ++changes;
         printf("Zapped zC=%d at [%d][%d] in 6-sided GordPolygon-3...\t", \
                 qualifiedCandsTable[q][2], yyy, xxx);
                 
                          return;
                 } // ends if rr == region ..... ************
                 
                 // rrr == region.................
                 if ( rrr == region )
                     {
                          //Find the RB outer wing at [yy][xxx]...(candsNDSumTable == 2...
                          for ( xxx = 0; xxx < 9; ++xxx )
                          {
                              if ( xxx == x )
                                 continue; // next xxx... *******
                                 
                              if ( candsNDSumTable[q][yy][xxx] != 2 )
                                 continue; // next xxx... ****
                              
                              //found RB outer wing... *******
                              break;
                          } // ends for xxx = ... ******
                          
                          if ( xxx == 9 )
                             continue; // next x... **********
                             
                          //find the C outer wing at [yyy][xx]
                          //same column as gWing, same region as gWing...
                          for ( yyy = 0; yyy < 9; ++yyy )
                          {
                              if ( yyy == y )
                                 continue; // next yyy... *********
                                 
                              if ( candsNDSumTable[q][yyy][xx] != 1 )
                                 continue; //next yyy .... ********
                                 
                              //found all 5 qualifying points...
                              break;
                          } // ends for yyy= ... **********
                          
                          if ( yyy == 9 )
                             continue; // next x.... *********
                             
                          //Now look at gWing....
                          //same row as RB outer wing [yyy].....
                          //same column as C outer wing [xxx]....
                          
                          //Does gWing contain both z-cands in question?.....
                          if ( !checkTable[(qualifiedCandsTable[q][1] - 1)][yyy][xxx] || \
                           !checkTable[(qualifiedCandsTable[q][2] - 1)][yyy][xxx] )
                             continue; // next x... gWing didn't contain both z-cands....
                             
                          //gWing contains both zCandidates..........
                          //Main Anchor-[y][x].. CB wing anchor-[y][x]- R wing anchor-[y][xx]
                          //RB outer wing-[yy][xxx]...C outer wing-[yyy][xx].....
                          //gWing at [yyy][xxx]......
                          
                          //Zap both zCands at gWing [yyy][xxx]....
                          checkTable[(qualifiedCandsTable[q][1] - 1)][yyy][xxx] = 0;
                          --checkRemainderTable[yyy][xxx];
                          ++changes;
         printf("Zapped zC=%d at [%d][%d] in 6-sided GordPolygon-3...\t", \
                 qualifiedCandsTable[q][1], yyy, xxx);                  
                 
                           checkTable[(qualifiedCandsTable[q][2] - 1)][yyy][xxx] = 0;
                          --checkRemainderTable[yyy][xxx];
                          ++changes;
         printf("Zapped zC=%d at [%d][%d] in 6-sided GordPolygon-3...\t", \
                 qualifiedCandsTable[q][2], yyy, xxx);
                 
                          return;
                      } // ends if rrr == region ..... ******             
                 } //ends for x = ... ends for y = ....*******
                 
                 //Start all over with y and x, to check for 2 anchor approach......... 
                 //First, search for an anchor, then inner wing with other anchor....
            for ( y = 0; y < 9; ++y )
                for ( x = 0; x < 9; ++x )
                {
                    if ( candsNDSumTable[q][y][x] != 3 )
                       continue;  //next x......
                       
                    //found an anchor at [y][x].....
                    for ( xx = 0; xx < 9; ++xx )
                    {
                        if ( xx == x )
                           continue;  //next x....
                           
                        if ( candsNDSumTable[q][y][xx] != 2 )
                           continue;  //next x....
                           
                        //found a difecta- either inner or outer wing at [y][xx]...
                        break;
                    } //ends for xx...................
                    
                    if ( xx == 9 )
                       continue;  //next x..... not a qualifier.......
                       
                    for ( yy = 0; yy < 9; ++yy )
                    {
                        if ( yy == y )
                           continue;   //next yy.............
                           
                        if ( candsNDSumTable[q][yy][xx] != 3 )
                           continue; // next yy................
                           
                        //found the other anchor at [yy][xx]....
                        break;
                    } //ends for yy ..................
                    
                    if ( yy == 9 )
                       continue; //next x....
                    //even though you found an anchor and an outer wing- continue
                    //otherwise, you will end up duplicating this set of cands...
                    
                    //Find the outer wings......
                    for ( xxx = 0; xxx < 9; ++xxx )
                    {
                        if ( xxx == xx )
                           continue; //next xxx..............
                           
                        if ( candsNDSumTable[q][yy][xxx] != 2 )
                           continue; //next xxx..............
                           
                        //found one outer wing at [yy][xxx].........
                        break;
                    } //ends for xxx...............
                    
                    if ( xxx == 9 )
                       continue; //next x...............
                       
                    for ( yyy = 0; yyy < 9; ++yyy )
                    {
                        if ( yyy == y )
                           continue; //next yyy...........
                           
                        if ( candsNDSumTable[q][yyy][x] != 2 )
                           continue; //next yyy............
                           
                        //found other outer wing at [yyy][x]........
                        break;
                    } //ends for yyy................
                    
                    if ( yyy == 9 )
                       continue;  //next x..............
                       
                    //Found all 5 points:  Anchors at [y][x] and [yy][xx]....
                    // Inner Wing at [y][xx]... Outer Wings at [yy][xxx] and [yyy][x]...
                    
                    // The gWing would be at [yyy][xxx]............
                    
                    //Does gWing contain both z-cands in question?.....
                    if ( !checkTable[(qualifiedCandsTable[q][1] - 1)][yyy][xxx] || \
                     !checkTable[(qualifiedCandsTable[q][2] - 1)][yyy][xxx] )
                         continue; // next x... gWing didn't contain both z-cands....
                     
                    //gWing contains both zCandidates...............    
                    //Zap both zCands at gWing [yyy][xxx]....
                          checkTable[(qualifiedCandsTable[q][1] - 1)][yyy][xxx] = 0;
                          --checkRemainderTable[yyy][xxx];
                          ++changes;
         printf("Zapped zC=%d at [%d][%d] in 6-sided GordPolygon-2...\t", \
                 qualifiedCandsTable[q][1], yyy, xxx);                  
                 
                           checkTable[(qualifiedCandsTable[q][2] - 1)][yyy][xxx] = 0;
                          --checkRemainderTable[yyy][xxx];
                          ++changes;
         printf("Zapped zC=%d at [%d][%d] in 6-sided GordPolygon-2...\t", \
                 qualifiedCandsTable[q][2], yyy, xxx);
                    
/*                    //debug purposes.........
                    deBug();
*/                    //debug purposes
                    
                    return;
                 } //ends for x =.... ends for y = .........
         } //ends for q = .................
         
         return;
}
                         
                    
                    
                    
                           
                              
                     
                     
         
            
                     
         
                 
             
     
