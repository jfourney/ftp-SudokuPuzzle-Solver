//One-Sided Gordonian Polygons with Six-Vertices Processing for Sudoku

/*
//Function Declarations **********************
void oneSidedGordPolygonsSix (void);
*/

//oneSidedGordPolygonsSix Function******************************
void oneSidedGordPolygonsSix (void)
{
     int x, y, z, a, b, c, q, xx, yy, rr, rrr, xxx, yyy, xxxx, yyyy, rrrr, region;
     int nDSumTable[9][9], nDCandSumTable[10][10], qualifiedCandsTable[8][3];
     int candsNDSumTable[8][9][9], difectas, trifectas;
     int qcSub, Sum, qual, qualifiers, nonNDCandsTable[8][9][9];
     
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
                 if ( nDCandSumTable[a][b] < 4 )
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
         
         //Initialize candsNDSumTable[8][9][9] and nonNDCandsTable.. **********************
         for ( q = 0; q < 8; ++q )
             for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                 {
                     candsNDSumTable[q][y][x] = 0;
                     nonNDCandsTable[q][y][x] = 0;
                 } // ends for x =.... for y =.... for q =..........
                     
         //Set up candsNDSumTable and nonNDCandsTable ***********************
         for ( q = 0; q < qcSub; ++q )
             for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                     if ( nDSumTable[y][x] > 0 )
                     {
                        if ( checkTable[(qualifiedCandsTable[q][1] - 1)][y][x] && \
                        checkTable[(qualifiedCandsTable[q][2] - 1)][y][x] )
                           candsNDSumTable[q][y][x] = nDSumTable[y][x];
                     }
                     else  if ( checkTable[(qualifiedCandsTable[q][1] - 1)][y][x] && \
                        checkTable[(qualifiedCandsTable[q][2] - 1)][y][x] )
                           nonNDCandsTable[q][y][x] = 1;
         //candsNDSumTable and nonNDCandsTable are set up... *************************
         
  /*       //debug purposes *******************************
         for ( q = 0; q < qcSub; ++q )
         {
             printf("Here's the candsNDSumTable and nonNDCandsTable for (%d,%d)...\n", qualifiedCandsTable[q][1], \
                            qualifiedCandsTable[q][2]);
                            
             for ( y = 0; y < 9; ++y )
             {
                 for ( x = 0; x < 9; ++x )
                     if ( nonNDCandsTable[q][y][x] == 1 )
                        printf(" 4 ");
                     else
                         printf(" %d ", candsNDSumTable[q][y][x]);
                     
                 printf("\n");
             } //ends for y = ...................
         }  // ends for q = ...................
 */        //debug purposes **********************************            
                     
         
         
         //Qualify the qualifiedCandsTable and if it meets all the qualifications,
         // process it...... **********************************
         for ( q = 0; q < qcSub; ++q )
         {
             difectas = 0; trifectas = 0; Sum = 0; qual = 0;
             
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
                          
                 } // ends for x = ...ends for y = *************
                 
             if ( Sum < 10 )
                ++qual;
                
             if ( trifectas < 2 )
                ++qual;
                
             if ( trifectas > 2 )
                if ( difectas < 2 )
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
                 {
                     candsNDSumTable[q][yy][xx] = 0;
                     nonNDCandsTable[q][yy][xx] = 0;
                 } // ends for xx = .... for yy = ...........
         } // ends for q = **************
         
/*         //debug purposes ****************
         printf("#Qualifiers = %d....\n", qualifiers);
*/         //debug purposes ***************
         
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
/*    //debug purposes
    printf("Anchor-1 at [%d][%d]...\t", y, x);
*/    //debug purposes                 
                     //found a trifecta- must have another trifecta, in the same row.. 
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
                     continue; //next x...no other anchor in the row....
/*    //debug purposes
    printf("Anchor-2 at [%d][%d]...\t", y, xx);
*/    //debug purposes                              
                     //Found both anchors, now find both wings.
                     for ( yy = 0; yy < 9; ++yy )
                     {
                         if ( yy == y )
                            continue; // next yy... **************
                            
                         if ( candsNDSumTable[q][yy][x] != 2 )
                            continue; // next yy.. ***********
                            
                         //found one wing, now find the other*************************
                         break;
                     } //ends for yy = ...*********
                     
                     if ( yy == 9 )
                        continue; // next x...***********
/*    //debug purposes
    printf("Wing-1 at [%d][%d]...\t", yy, x);
*/    //debug purposes                                   
                     //Find the other wing at [yyy][xx]...(candsNDSumTable == 2...
                     for ( yyy = 0; yyy < 9; ++yyy )
                     {
                         if ( (yyy == y) || (yyy == yy) )
                            continue; // next yyy... *******
                                 
                         if ( candsNDSumTable[q][yyy][xx] != 2 )
                            continue; // next yyy... ****
                              
                         //found all 4 positions *******
                         break;
                     } // ends for yyy = ... ******
                          
                     if ( yyy == 9 )
                        continue; // next x... **********
/*    //debug purposes
    printf("Wing-2 at [%d][%d]...\t", yyy, xx);
*/    //debug purposes                              
                     //2 Anchors at: [y][x] and [y][xx]...........
                     //2 Wings at: [yy][x] and [yyy][xx]...........
                     
                     //Now, find gWings at [yy][xxx] and [yyy][xxx].........        
                     for ( xxx = 0; xxx < 9; ++xxx )
                          {
                              if ( (xxx == x) || (xxx == xx) )
                                 continue; // next xxx... *********
                                 
                              if ( !nonNDCandsTable[q][yy][xxx] )
                                 continue; //next xxx.........
                                 
                              //found a gWing- check [yyy][xxx] to see if gWing....
                              break;
                          } // ends for xxx= ... **********
                          
                          if ( xxx == 9 )
                             continue; // next x.... *********
/*    //debug purposes
    printf("gWing-1 at [%d][%d]...\t", yy, xxx);
*/    //debug purposes                                        
                          if ( !nonNDCandsTable[q][yyy][xxx] )
                                 continue; //next x.........
/*    //debug purposes
    printf("gWing-2 at [%d][%d]...\t", yyy, xxx);
*/    //debug purposes                                             
                          //Found both gWings at: [yy][xxx] and [yyy][xxx].....
                          //Do they both only have the same zCandidate, along with the ND..
                          if ( (checkRemainderTable[yy][xxx] != 3) || \
                                (checkRemainderTable[yyy][xxx] != 3) )
                               continue; // next x...........
                               
                          for ( z = 0; z < 9; ++z )
                          {
                              if ( (z == (qualifiedCandsTable[q][1] - 1)) || \
                                   (z == (qualifiedCandsTable[q][2] - 1)) ) 
                                 continue; // next z.......
                                 
                              if ( checkTable[z][yy][xxx] && checkTable[z][yyy][xxx] )
                                 break; // found zCandidate for gWing......
                          } //ends for z =...............
                          
                          if ( z == 9 )
                             continue; //next x................
                             
                          //gWing zCandidate found; zap from rest of column [xxx].........
                          for ( yyyy = 0; yyyy < 9; ++yyyy )
                          {
                              if ( (yyyy == yy) || (yyyy == yyy) )
                                 continue; //next yyyy............
                                 
                              if ( !checkTable[z][yyyy][xxx] )
                                 continue;
                                 
                              //found a zCandidate at [yyyy][xxx]...Zap it..........
                              checkTable[z][yyyy][xxx] = 0;
                              --checkRemainderTable[yyyy][xxx];
                              ++changes;
         printf("Zapped zC=%d at [%d][%d] in oneSided GordPolygon6-Row...\t", \
                 (z + 1), yyyy, xxx);                  
                          } //ends for yyyy................
                          
                          if ( changes > 0 )  
                             return;
                     } // ends for x =.....//ends for y = ************
                 
                 //Start all over with y and x, for column processing..........
            for ( y = 0; y < 9; ++y )
                 for ( x = 0; x < 9; ++x )
                 {
                     if ( candsNDSumTable[q][y][x] < 3 )
                        continue; // next x...
/*    //debug purposes
    printf("Anchor-1 at [%d][%d]...\t", y, x);
*/    //debug purposes                              
                     //found a trifecta- must have another trifecta, in the same column.. 
                     for ( yy = 0; yy < 9; ++yy )
                     {
                         if ( yy == y )
                            continue; // next yy....
                            
                         if ( candsNDSumTable[q][yy][x] < 3 )
                            continue; // next yy....
                            
                         //trifecta found at [yy][x]- one in the column...
                         break; // from for yy = ... **************
                     } //ends for yy = .. *************** 
                     
                     if ( yy == 9 )
                     continue; //next x...no other anchor in the column....
/*    //debug purposes
    printf("Anchor-2 at [%d][%d]...\t", yy, x);
*/    //debug purposes                                
                     //Found both anchors, now find both wings.
                     //Anchors at: [y][x] and [yy][x]...............
                     for ( xx = 0; xx < 9; ++xx )
                     {
                         if ( xx == x )
                            continue; // next xx... **************
                            
                         if ( candsNDSumTable[q][y][xx] != 2 )
                            continue; // next xx.. ***********
                                        
                         //found one wing, now find the other*************************
                         break;
                     } //ends for xx = ...*********
                     
                     if ( xx == 9 )
                        continue; // next x...***********
/*     //debug purposes
    printf("Wing-1 at [%d][%d]...\t", y, xx);
*/    //debug purposes                      
                     //Find the other wing at [yy][xxx]...(candsNDSumTable == 2...
                     for ( xxx = 0; xxx < 9; ++xxx )
                     {
                         if ( xxx == x )
                            continue; // next xxx... *******
                                 
                         if ( candsNDSumTable[q][yy][xxx] != 2 )
                            continue; // next xxx... ****
                              
                         //found all 4 positions *******
                         break;
                     } // ends for xxx = ... ******
                          
                     if ( xxx == 9 )
                        continue; // next x... **********
/*    //debug purposes
    printf("Wing-2 at [%d][%d]...\t", yy, xxx);
*/    //debug purposes                                       
                     //2 Anchors at: [y][x] and [yy][x]...........
                     //2 Wings at: [y][xx] and [yy][xxx]...........
                     
                     //Now, find gWings at [yyy][xx] and [yyy][xxx].........        
                     for ( yyy = 0; yyy < 9; ++yyy )
                          {
                              if ( (yyy == y) || (yyy == yy) )
                                 continue; // next yyy... *********
                                 
                              if ( !nonNDCandsTable[q][yyy][xx] )
                                 continue; //next yyy........
                                 
                              //found a gWing- check [yyy][xxx] to see if gWing....
                              break;
                          } // ends for yyy= ... **********
                          
                          if ( yyy == 9 )
                             continue; // next x.... *********
 /*   //debug purposes
    printf("gWing-1 at [%d][%d]...\t", yyy, xx);
 */   //debug purposes                                               
                          if ( !nonNDCandsTable[q][yyy][xxx] )
                                 continue; //next x.........
/*    //debug purposes
    printf("gWing-2 at [%d][%d]...\t", yyy, xxx);
*/    //debug purposes                                                  
                          //Found both gWings at: [yyy][xx] and [yyy][xxx].....
                          //Do they both only have the same zCandidate, along with the ND..
                          if ( (checkRemainderTable[yyy][xx] != 3) || \
                                (checkRemainderTable[yyy][xxx] != 3) )
                               continue; // next x...........
                               
                          for ( z = 0; z < 9; ++z )
                          {
                              if ( (z == (qualifiedCandsTable[q][1] - 1)) || \
                                   (z == (qualifiedCandsTable[q][2] - 1)) ) 
                                 continue; // next z.......
                                 
                              if ( checkTable[z][yyy][xx] && checkTable[z][yyy][xxx] )
                                 break; // found zCandidate for gWing......
                          } //ends for z =...............
                          
                          if ( z == 9 )
                             continue; //next x................
                             
                          //gWing zCandidate found; zap from rest of row [yyy].........
                          for ( xxxx = 0; xxxx < 9; ++xxxx )
                          {
                              if ( (xxxx == xx) || (xxxx == xxx) )
                                 continue; //next xxxx............
                                 
                              if ( !checkTable[z][yyy][xxxx] )
                                 continue;
                                 
                              //found a zCandidate at [yyy][xxxx]...Zap it..........
                              checkTable[z][yyy][xxxx] = 0;
                              --checkRemainderTable[yyy][xxxx];
                              ++changes;
         printf("Zapped zC=%d at [%d][%d] in oneSided GordPolygon6-Col...\t", \
                 (z + 1), yyy, xxxx);                  
                          } //ends for xxxx................
                          
                          if ( changes > 0 )  
                             return;
                     } // ends for x =.....//ends for y = ************
     } // ends for q =................
         
     return;
}
