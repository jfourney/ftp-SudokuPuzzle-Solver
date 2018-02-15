//Jellyfish Processing for Sudoku. **************

/*
//Function Declarations ***********************
void jellyfishRow (void);
void jellyfishColumn (void);
*/
//jellyfishRow Function. ************************
void jellyfishRow (void)
{
     int x, y, z, yy, yyy, xx, u, uu, t, tt, ttt, tttt, loc, uniqueLocTable[4], sumTable[9][4];
     int uCount, jCount, yCount, uniqueAdded[3], xLocTable[9], yLocTable[9][4], xThere;
     int qualifiedJellyfishTable[9][9][9];
     //sumTable holds the y-location of the z-candidate.
     
     //Kind of confusing. Collecting info on columns, to complete a jellyfishRow. ***
     
     //Initialize the qualifiedJellyfishTable..
     
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             for ( z = 0; z < 9; ++z )
                 qualifiedJellyfishTable[z][y][x] = 0;
                 
     //Set up the qualifiedJellyfishTable, with elements that qualify, (2 or 3 of a
     //certain candidate, in the column). ****************
     for ( x = 0; x < 9; ++x )
     {
         //Initialize the sumTable for each column. ********************
         for ( z = 0; z < 9; ++z )
             for ( yy = 0; yy < 4; ++yy )
                 sumTable[z][yy] = 9; //must be 9, no location 9, on the board...
                 
         //Set up sumTable, and if it qualifies, enter it into the qualifiedJellyfishTable.
         for ( z = 0; z < 9; ++z )
         {
             yy = 0;
             
             for ( y = 0; y < 9; ++y )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      ++yy;
                      
                      if ( yy == 5 )
                         break;
                         
                      sumTable[z][(yy - 1)] = y;
                 } // ends if cT...for y........
                 
             if ( yy == 5 )
                continue;  //next z.......
                
             if ( yy < 2 )   //if ( yy == 0 )
                continue; //next z...........
                
             //2 or 3 sumTable Elements, in column; qualified for qualifiedJellyfishTable..
             for ( yyy = 0; yyy < yy; ++yyy )
                 qualifiedJellyfishTable[z][(sumTable[z][yyy])][x] = (z + 1);
                 
         } // ends for z= ...............
     } // ends for x.............
     
     //qualifiedJellyfishTable, for Row processing, is set up......
     for ( z = 0; z < 9; ++z )
     {
 //        system("pause"); // debug purposes***********
         //Check to see, if at least 3 columns qualify for y-tables...
         
         //First, initialize y-tables............
         for ( x = 0; x < 9; ++x )
         {
             xLocTable[x] = 9;
             
             for ( yy = 0; yy < 4; ++yy )
                 yLocTable[x][yy] = 9;
         } //ends for x = ..............
         
         // Set up y-tables, at least 4 must qualify, to qualify for JellyfishRow...
         jCount = 0;
         
         for ( x = 0; x < 9; ++x )
         {
             yCount = 0;
             
             for ( y = 0; y < 9; ++y )
                 if ( qualifiedJellyfishTable[z][y][x] > 0 )
                 {
                      yLocTable[jCount][yCount] = y;
                      ++yCount;
                 } // ends if qST... for y =.........
                 
             if ( yCount > 0 )
             {
                  xLocTable[jCount] = x;
                  ++jCount;
             } // ends if yC.........
         } // ends for x =.............
             
         // Eliminate qualifiers < 4.................
         if ( jCount < 4 )
            continue;
                
         //Qualifiers for JellyfishRow Processing................
/*         //debug purposes ************---Print Y-TABLES.....**********
         for ( xx = 0; xx < jCount; ++xx )
             printf("cand=%d, xLoc[%d]=%d, yLoc[%d]=%d,%d,%d,%d.\n", (z + 1), xx, xLocTable[xx], xx, \
             yLocTable[xx][0], yLocTable[xx][1], yLocTable[xx][2], yLocTable[xx][3]);
*/         //debug purposes **************
         
         //START LINKED TABLE PROCESSING. ************************************
         for ( t = 0; t < (jCount - 3); ++t )
         {
             // Initialize uniqueLocTable to 9's.....
             for ( u = 0; u < 4; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements of yLocTable < 9, into uniqueLocTable*************
             for ( u = 0; u < 4; ++u )
                 if ( yLocTable[t][u] < 9 )
                    uniqueLocTable[u] = yLocTable[t][u];
                 else
                     break; // from u =..... // ends for u =...........
             
             uniqueAdded[0] = u;
             
             //DONE WITH PLACING FIRST ELEMENT INTO LINKED TABLE...
             
             //BEGIN SEARCH FOR A SECOND ELEMENT......................
             for ( tt = (t + 1); tt < (jCount - 2); ++tt )
             {
                 // if uCount < 4, put uniqueLocations into uniqueLoc...
                 uCount = uniqueAdded[0];
                 
                 for ( u = uCount; u < 4; ++u )
                          uniqueLocTable[u] = 9;
                          
                 uniqueAdded[1] = 0;
                                  
                 for ( u = 0; (u < 4) && (yLocTable[tt][u] < 9); ++u )
                 {
                     loc = yLocTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue; // next uu..........
                         else
                         {
                             loc = 9;
                             break;  // ultimately next u.......
                         } // ends if l... for uu = ...........
                         
                     if ( loc == 9 )
                        continue; // next u...............
                        
                     // have a unique location................
                     ++uCount;
                     
                     if ( uCount > 4 )
                        break;  // from u............
                        
                     // Enter into uniqueLocTable, add to uniqueAdded[1].....
                     uniqueLocTable[(uCount - 1)] = loc;
                     
                     ++uniqueAdded[1];
                 } // ends for u = ...........*****************
                 
                 if ( uCount > 4 )
                 {
 /*                     //debug purposes ***********************
                      printf("2F x=%d, t=%d, tt=%d, ", xLocTable[tt], t, tt);
                      printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                      printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                     //debug purposes ******************
                      
                      // 2nd element failed to link; try another 2nd......
                      continue; // next tt................
                 } // ends if uC...............
                 
                 //SUCCESSFULLY LINKED 2ND ELEMENT, IN LINKED TABLE................
  /*               //debug purposes ***********************
                 printf("2S x=%d, t=%d, tt=%d, ", xLocTable[tt], t, tt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
  */               //debug purposes ******************
                 
                 
             //BEGIN SEARCH FOR A THIRD ELEMENT......................
             for ( ttt = (tt + 1); ttt < (jCount - 1); ++ttt )
             {
                 // if uCount < 4, put uniqueLocations into uniqueLoc...
                 uCount = (uniqueAdded[0] + uniqueAdded[1]);
                 
                 for ( u = uCount; u < 4; ++u )
                     uniqueLocTable[u] = 9;
                          
                 uniqueAdded[2] = 0;
                                  
                 for ( u = 0; (u < 4) && (yLocTable[ttt][u] < 9); ++u )
                 {
                     loc = yLocTable[ttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue; // next uu..........
                         else
                         {
                             loc = 9;
                             break;  // ultimately next u.......
                         } // ends if l... for uu = ...........
                         
                     if ( loc == 9 )
                        continue; // next u...............
                        
                     // have a unique location................
                     ++uCount;
                     
                     if ( uCount > 4 )
                        break;  // from u............
                        
                     // Enter into uniqueLocTable, add to uniqueAdded[2].....
                     uniqueLocTable[(uCount - 1)] = loc;
                     
                     ++uniqueAdded[2];
                 } // ends for u = ...........*****************
                 
                 if ( uCount > 4 )
                 {
  /*                    //debug purposes ***********************
                      printf("3F x=%d, t=%d, tt=%d, ttt=%d, ", xLocTable[ttt], t, tt, ttt);
                      printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                      printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
  */                    //debug purposes ******************
                      
                      // 3rd element failed to link; try another 3rd......
                      continue; // next ttt................
                 } // ends if uC...............
                 
                 //SUCCESSFULLY LINKED 3RD ELEMENT, IN LINKED TABLE................
    /*             //debug purposes ***********************
                 printf("3S x=%d, t=%d, tt=%d, ttt=%d, ", xLocTable[tt], t, tt, ttt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
    */             //debug purposes ******************
                 
                 
                 
                 //BEGIN SEARCH FOR 4TH ELEMENT TO LINKED TABLE..........
                 
               for ( tttt = (ttt + 1); tttt < jCount; ++tttt )
               {
                 // if uCount < 4, put uniqueLocations into uniqueLoc...
                 uCount = (uniqueAdded[0] + uniqueAdded[1] + uniqueAdded[2]);
                 
                 //debug purposes
                 if ( uCount > 4 )
                 {
                      printf("PROBLEM WITH UNIQUEADDED'S.. UCOUNT > 4... \n");
                      system("pause");
                 } // ends if uC
                 //debug purposes
                 
                 for ( u = uCount; u < 4; ++u )
                        uniqueLocTable[u] = 9;
                                               
                 for ( u = 0; (u < 4) && (yLocTable[tttt][u] < 9); ++u )
                 {
                     loc = yLocTable[tttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue; // next uu..........
                         else
                         {
                             loc = 9;
                             break;  // ultimately next u.......
                         } // ends if l... for uu = ...........
                         
                     if ( loc == 9 )
                        continue; // next u...............
                        
                     // have a unique location................
                     ++uCount;
                     
                     if ( uCount > 4 )
                        break;  // from u............
                        
                     // Enter into uniqueLocTable........
                     uniqueLocTable[(uCount - 1)] = loc;
                     
                 } // ends for u = ...........*****************
                 
                 if ( (uCount > 4) || (uCount < 4) )
                 {
   /*                   //debug purposes ***********************
                      printf("4F x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", xLocTable[tttt], t, tt, ttt, tttt);
                      printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                      printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
   */                   //debug purposes ******************
                      
                      // 4th element failed to link; try another 4th......
                      continue; // next tttt................
                 } // ends if uC...............
                 
                 //SUCCESSFULLY LINKED 4TH ELEMENT, IN LINKED TABLE................
                 
 /*                //CHECK TO MAKE SURE THAT EACH CANDIDATE APPEARS AT LEAST IN TWO, OF THE 3 ROWS...
                 //uniqueLoc[0]:
                 xThere = 0;
                 
                 if ( checkTable[z][(uniqueLocTable[0])][(xLocTable[t])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[0])][(xLocTable[tt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[0])][(xLocTable[ttt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[0])][(xLocTable[tttt])] > 0 )
                    ++xThere;
                    
                 if ( xThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required rows, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d xLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], xLocTable[t], xLocTable[tt], \
                         xLocTable[ttt], xLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[0] CHECK.....
                 
                 //uniqueLoc[1]:
                  xThere = 0;
                 
                 if ( checkTable[z][(uniqueLocTable[1])][(xLocTable[t])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[1])][(xLocTable[tt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[1])][(xLocTable[ttt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[1])][(xLocTable[tttt])] > 0 )
                    ++xThere;
                    
                 if ( xThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required rows, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d xLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], xLocTable[t], xLocTable[tt], \
                         xLocTable[ttt], xLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[1] CHECK.....
                 
                  //uniqueLoc[2]:
                  xThere = 0;
                 
                 if ( checkTable[z][(uniqueLocTable[2])][(xLocTable[t])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[2])][(xLocTable[tt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[2])][(xLocTable[ttt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[2])][(xLocTable[tttt])] > 0 )
                    ++xThere;
                    
                 if ( xThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required rows, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d xLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], xLocTable[t], xLocTable[tt], \
                         xLocTable[ttt], xLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[2] CHECK.....
                 
                 //uniqueLoc[3]:
                  xThere = 0;
                 
                 if ( checkTable[z][(uniqueLocTable[3])][(xLocTable[t])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[3])][(xLocTable[tt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[3])][(xLocTable[ttt])] > 0 )
                    ++xThere;
                 if ( checkTable[z][(uniqueLocTable[3])][(xLocTable[tttt])] > 0 )
                    ++xThere;
                    
                 if ( xThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required rows, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d xLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], xLocTable[t], xLocTable[tt], \
                         xLocTable[ttt], xLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[3] CHECK.....
 */                
 /*                //debug purposes ***********************
                 printf("4S x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", xLocTable[tttt], t, tt, ttt, tttt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                //debug purposes ******************
                 
                 // A JELLYFISHROW, HAS BEEN ACHIEVED....
                 // ZAP ALL OTHER OCCURANCES OF THE Z-CANDIDATE (Z+1), IN THE 4 ROWS
                 // DETERMINED BY THE UNIQUE LOC TABLE, EXCEPT WHERE X = XLOCTABLE[T],
                 // [TT], [TTT], OR [TTTT]....................
                 
                 for ( u = 0; u < 4; ++u )
                 {
                     y = uniqueLocTable[u];
                     
                     for ( x = 0; x < 9; ++x )
                         if ( x != xLocTable[t] )
                         if ( x != xLocTable[tt] )
                         if ( x != xLocTable[ttt] )
                         if ( x != xLocTable[tttt] )
                            if ( checkTable[z][y][x] > 0 )
                            {
                                 checkTable[z][y][x] = 0;
                                 --checkRemainderTable[y][x];
                                 ++changes;
                                 
                                 //debug purposes ***********************
                     printf("Zapped xC=%d at [%d][%d]- in JellyRow...\t", (z + 1), y, x);
                                 //debug purposes**************************
                            }  // ends if cT.... for x= ................
                 } // ends for u = ............. ******************
                 
                 if ( changes > 0 )
                    return;
                } //ends tttt.....************    
               } // ends ttt..... ************
             } // ends tt........... ***************
         } // ends t............... ***************
         
 /*        //debug purposes ***********************
                 printf("E x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", xLocTable[tt], t, tt, ttt, tttt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                //debug purposes ******************
                          
     } // ends for z = ........... ***************8
     
     return;
}
         
         
//jellyfishColumn Function. ************************
void jellyfishColumn (void)
{
     int x, y, z, xx, xxx, yy, u, uu, t, tt, ttt, tttt, loc, uniqueLocTable[4], sumTable[9][4];
     int uCount, jCount, xCount, uniqueAdded[3], yLocTable[9], xLocTable[9][4], yThere;
     int qualifiedJellyfishTable[9][9][9];
     //sumTable holds the x-location of the z-candidate.
     
     //Kind of confusing. Collecting info on rows, to complete a jellyfishColumn. ***
     
     //Initialize the qualifiedJellyfishTable..
     
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             for ( z = 0; z < 9; ++z )
                 qualifiedJellyfishTable[z][y][x] = 0;
                 
     //Set up the qualifiedJellyfishTable, with elements that qualify, (2-4 of a
     //certain candidate, in the row). ****************
     for ( y = 0; y < 9; ++y )
     {
         //Initialize the sumTable for each row. ********************
         for ( z = 0; z < 9; ++z )
             for ( xx = 0; xx < 4; ++xx )
                 sumTable[z][xx] = 9; //must be 9, no location 9, on the board...
                 
         //Set up sumTable, and if it qualifies, enter it into the qualifiedJellyfishTable.
         for ( z = 0; z < 9; ++z )
         {
             xx = 0;
             
             for ( x = 0; x < 9; ++x )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      ++xx;
                      
                      if ( xx == 5 )
                         break;
                         
                      sumTable[z][(xx - 1)] = x;
                 } // ends if cT...for x........
                 
             if ( xx == 5 )
                continue;  //next z.......
                
             if ( xx < 2 )   //if ( xx == 0 )
                continue; //next z...........
                
             //2 or 3 sumTable Elements, in row; qualified for qualifiedJellyfishTable..
             for ( xxx = 0; xxx < xx; ++xxx )
                 qualifiedJellyfishTable[z][y][(sumTable[z][xxx])] = (z + 1);
                 
         } // ends for z= ...............
     } // ends for y.............
     
     
     //qualifiedJellyfishTable, for Column processing, is set up......
     for ( z = 0; z < 9; ++z )
     {
//         system("pause"); // debug purposes***********
         //Check to see, if at least 3 rows qualify for x-tables...
         
         //First, initialize x-tables............
         for ( y = 0; y < 9; ++y )
         {
             yLocTable[y] = 9;
             
             for ( xx = 0; xx < 4; ++xx )
                 xLocTable[y][xx] = 9;
         } //ends for y = ..............
         
         // Set up x-tables, at least 3 must qualify, to qualify for JellyfishColumn...
         jCount = 0;
         
         for ( y = 0; y < 9; ++y )
         {
             xCount = 0;
             
             for ( x = 0; x < 9; ++x )
                 if ( qualifiedJellyfishTable[z][y][x] > 0 )
                 {
                      xLocTable[jCount][xCount] = x;
                      ++xCount;
                 } // ends if qST... for x =.........
                 
             if ( xCount > 0 )
             {
                  yLocTable[jCount] = y;
                  ++jCount;
             } // ends if xC.........
         } // ends for y =.............
             
         // Eliminate qualifiers < 3.................
         if ( jCount < 4 )
            continue;
                
         //Qualifiers for JellyfishRow Processing................
/*         //debug purposes ************---Print X-TABLES.....**********
         for ( yy = 0; yy < jCount; ++yy )
             printf("cand=%d, yLoc[%d]=%d, xLoc[%d]=%d,%d,%d,%d.\n", (z + 1), yy, yLocTable[yy], yy, \
             xLocTable[yy][0], xLocTable[yy][1], xLocTable[yy][2], xLocTable[yy][3]);
*/         //debug purposes **************
         
         //START LINKED TABLE PROCESSING. ************************************
         for ( t = 0; t < (jCount - 3); ++t )
         {
             // Initialize uniqueLocTable to 9's.....
             for ( u = 0; u < 4; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements of yLocTable < 9, into uniqueLocTable*************
             for ( u = 0; u < 4; ++u )
                 if ( xLocTable[t][u] < 9 )
                    uniqueLocTable[u] = xLocTable[t][u];
                 else
                     break; // from u =..... // ends for u =...........
              
             uniqueAdded[0] = u;
             
             //DONE WITH PLACING FIRST ELEMENT INTO LINKED TABLE...
             
             //BEGIN SEARCH FOR A SECOND ELEMENT......................
             for ( tt = (t + 1); tt < (jCount - 2); ++tt )
             {
                 // if uCount < 4, put uniqueLocations into uniqueLoc...
                 uCount = uniqueAdded[0];
                 
                 for ( u = uCount; u < 4; ++u )
                     uniqueLocTable[u] = 9;
                          
                 uniqueAdded[1] = 0;
                                
                 for ( u = 0; (u < 4) && (xLocTable[tt][u] < 9); ++u )
                 {
                     loc = xLocTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue; // next uu..........
                         else
                         {
                             loc = 9;
                             break;  // ultimately next u.......
                         } // ends if l... for uu = ...........
                         
                     if ( loc == 9 )
                        continue; // next u...............
                        
                     // have a unique location................
                     ++uCount;
                     
                     if ( uCount > 4 )
                        break;  // from u............
                        
                     // Enter into uniqueLocTable, add to uniqueAdded[1].....
                     uniqueLocTable[(uCount - 1)] = loc;
                     
                     ++uniqueAdded[1];
                 } // ends for u = ...........*****************
                 
                 if ( uCount > 4 )
                 {
/*                      //debug purposes ***********************
                      printf("2F y=%d, t=%d, tt=%d, ", yLocTable[tt], t, tt);
                      printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                      printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
*/                      //debug purposes ******************
                      
                      // 2nd element failed to link; try another 2nd......
                      continue; // next tt................
                 } // ends if uC...............
                 
                 //SUCCESSFULLY LINKED 2ND ELEMENT, IN LINKED TABLE................
 /*                //debug purposes ***********************
                 printf("2S y=%d, t=%d, tt=%d, ", yLocTable[tt], t, tt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                //debug purposes ******************
                 
                 
             //BEGIN SEARCH FOR A THIRD ELEMENT......................
             for ( ttt = (tt + 1); ttt < (jCount - 1); ++ttt )
             {
                 // if uCount < 4, put uniqueLocations into uniqueLoc...
                 uCount = (uniqueAdded[0] + uniqueAdded[1]);
                 
                 for ( u = uCount; u < 4; ++u )
                     uniqueLocTable[u] = 9;
                          
                 uniqueAdded[2] = 0;
                                
                 for ( u = 0; (u < 4) && (xLocTable[ttt][u] < 9); ++u )
                 {
                     loc = xLocTable[ttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue; // next uu..........
                         else
                         {
                             loc = 9;
                             break;  // ultimately next u.......
                         } // ends if l... for uu = ...........
                         
                     if ( loc == 9 )
                        continue; // next u...............
                        
                     // have a unique location................
                     ++uCount;
                     
                     if ( uCount > 4 )
                        break;  // from u............
                        
                     // Enter into uniqueLocTable, add to uniqueAdded[1].....
                     uniqueLocTable[(uCount - 1)] = loc;
                     
                     ++uniqueAdded[2];
                 } // ends for u = ...........*****************
                 
                 if ( uCount > 4 )
                 {
 /*                     //debug purposes ***********************
                      printf("3F y=%d, t=%d, tt=%d, ttt=%d, ", yLocTable[ttt], t, tt, ttt);
                      printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                      printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                     //debug purposes ******************
                      
                      // 3rd element failed to link; try another 3rd......
                      continue; // next tt................
                 } // ends if uC...............
                 
                 //SUCCESSFULLY LINKED 3RD ELEMENT, IN LINKED TABLE................
 /*                //debug purposes ***********************
                 printf("3S y=%d, t=%d, tt=%d, ttt=%d, ", yLocTable[ttt], t, tt, ttt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                //debug purposes ******************
                 
                 
                 
               //BEGIN SEARCH FOR 4TH ELEMENT TO LINKED TABLE..........
                 
               for ( tttt = (ttt + 1); tttt < jCount; ++tttt )
               {
                 // if uCount < 4, put uniqueLocations into uniqueLoc...
                 uCount = (uniqueAdded[0] + uniqueAdded[1] + uniqueAdded[2]);
                 
                 for ( u = uCount; u < 4; ++u )
                     uniqueLocTable[u] = 9;
                                               
                 for ( u = 0; (u < 4) && (xLocTable[tttt][u] < 9); ++u )
                 {
                     loc = xLocTable[tttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue; // next uu..........
                         else
                         {
                             loc = 9;
                             break;  // ultimately next u.......
                         } // ends if l... for uu = ...........
                         
                     if ( loc == 9 )
                        continue; // next u...............
                        
                     // have a unique location................
                     ++uCount;
                     
                     if ( uCount > 4 )
                        break;  // from u............
                        
                     // Enter into uniqueLocTable........
                     uniqueLocTable[(uCount - 1)] = loc;
                     
                 } // ends for u = ...........*****************
                 
                 if ( (uCount > 4) || (uCount < 4) )
                 {
 /**                     //debug purposes ***********************
                      printf("4F y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", yLocTable[tt], t, tt, ttt, tttt);
                      printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                      printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
  */                    //debug purposes ******************
                      
                      // 4th element failed to link; try another 4th......
                      continue; // next ttt................
                 } // ends if uC...............
                 
                 //SUCCESSFULLY LINKED 4TH ELEMENT, IN LINKED TABLE................
                 
/*                 //CHECK TO MAKE SURE THAT EACH CANDIDATE APPEARS AT LEAST IN TWO, OF THE 4 COLUMNS...
                 //uniqueLoc[0]:
                 yThere = 0;
                 
                 if ( checkTable[z][(yLocTable[t])][(uniqueLocTable[0])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tt])][(uniqueLocTable[0])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[ttt])][(uniqueLocTable[0])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tttt])][(uniqueLocTable[0])] > 0 )
                    ++yThere;
                                 
                 if ( yThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required columns, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d yLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], yLocTable[t], yLocTable[tt], \
                         yLocTable[ttt], yLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[0] CHECK.....
                 
                 //uniqueLoc[1]:
                 yThere = 0;
                 
                 if ( checkTable[z][(yLocTable[t])][(uniqueLocTable[1])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tt])][(uniqueLocTable[1])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[ttt])][(uniqueLocTable[1])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tttt])][(uniqueLocTable[1])] > 0 )
                    ++yThere;
                                 
                 if ( yThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required columns, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d yLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], yLocTable[t], yLocTable[tt], \
                         yLocTable[ttt], yLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[1] CHECK.....
                 
                 //uniqueLoc[2]:
                 yThere = 0;
                 
                 if ( checkTable[z][(yLocTable[t])][(uniqueLocTable[2])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tt])][(uniqueLocTable[2])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[ttt])][(uniqueLocTable[2])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tttt])][(uniqueLocTable[2])] > 0 )
                    ++yThere;
                                 
                 if ( yThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required columns, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d yLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], yLocTable[t], yLocTable[tt], \
                         yLocTable[ttt], yLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[2] CHECK.....
                 
                 //uniqueLoc[3]:
                 yThere = 0;
                 
                 if ( checkTable[z][(yLocTable[t])][(uniqueLocTable[3])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tt])][(uniqueLocTable[3])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[ttt])][(uniqueLocTable[3])] > 0 )
                    ++yThere;
                 if ( checkTable[z][(yLocTable[tttt])][(uniqueLocTable[3])] > 0 )
                    ++yThere;
                                 
                 if ( yThere < 2 )
                 {
                      printf("The candidate wasn't in at least 2 of the 4 required columns, to qualify.\n");
                      printf("cand=%d, uniqueLoc=%d,%d,%d,%d yLoc=%d,%d,%d,%d.\n", (z + 1), uniqueLocTable[0], \
                         uniqueLocTable[1], uniqueLocTable[2], uniqueLocTable[3], yLocTable[t], yLocTable[tt], \
                         yLocTable[ttt], yLocTable[tttt]);
                      continue; // next tttt...
                 }  // ends uniqueLoc[3] CHECK.....
 */                
 /*                //debug purposes ***********************
                 printf("4S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", yLocTable[tt], t, tt, ttt, tttt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                //debug purposes ******************
                 
                 // A JELLYFISHCOLUMN, HAS BEEN ACHIEVED....
                 // ZAP ALL OTHER OCCURANCES OF THE Z-CANDIDATE (Z+1), IN THE 4 ROWS
                 // DETERMINED BY THE UNIQUE LOC TABLE, EXCEPT WHERE X = XLOCTABLE[T],
                 // [TT], [TTT], OR [TTTT]....................
                 
                 for ( u = 0; u < 4; ++u )
                 {
                     x = uniqueLocTable[u];
                     
                     for ( y = 0; y < 9; ++y )
                         if ( y != yLocTable[t] )
                         if ( y != yLocTable[tt] )
                         if ( y != yLocTable[ttt] )
                         if ( y != yLocTable[tttt] )
                            if ( checkTable[z][y][x] > 0 )
                            {
                                 checkTable[z][y][x] = 0;
                                 --checkRemainderTable[y][x];
                                 ++changes;
                                 
                                 //debug purposes ***********************
                                 printf("Zapped yC=%d at [%d][%d]- in JellyCol ...\t", (z + 1), y, x);
                                 //debug purposes**************************
                            }  // ends if cT.... for x= ................
                 } // ends for u = ............. ******************
                 
                 if ( changes > 0 )
                    return;
                } // ends tttt......******    
               } // ends ttt..... ************
             } // ends tt........... ***************
         } // ends t............... ***************
         
 /*                //debug purposes ***********************
                 printf("E y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", yLocTable[tt], t, tt, ttt, tttt);
                 printf("cand=%d, jCount=%d, uCount=%d, loc=%d, ", (z + 1), jCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d.\n", uniqueLocTable[0], uniqueLocTable[1], \
                                                      uniqueLocTable[2], uniqueLocTable[3]);
 */                //debug purposes ******************
                          
     } // ends for z = ........... ***************8
     
     return;
}
         
         

                 
                 
                 
                 
                 
                 
                                      
          
                
                      
         
         
         
      
