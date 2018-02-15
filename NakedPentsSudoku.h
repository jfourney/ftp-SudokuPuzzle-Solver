// Naked Pents Processing for Sudoku. *******************

/*
// Function Declarations **************************************************
void nakedPentsRow (void);
void nakedPentsColumn (void);
void nakedPentsRegion (void);
*/

//nakedPentsRow Function ******************************************************
void nakedPentsRow (void)
{
     int x, y, z, xx, u, uu, t, tt, ttt, tttt, ttttt, cand, uCount, xCount, uniqueAdded[3];
     int xRemTable[9], xCandTable[9][5], xLocTable[9], uniqueCandTable[5];
     
     
     for ( y = 0; y < 9; ++y )
     {
         //Initialize X-tables. *******************************************
         for ( x = 0; x < 9; ++x )
         {
             xRemTable[x] = 0;
             xLocTable[x] = 0;
             
             for ( xx = 0; xx < 5; ++xx )
                 xCandTable[x][xx] = 0;
         }
         
         //Fill X-tables with qualifying elements; x-locations that have a checkRemainder
         //  of 2 thru 5. Also, don't include nDR's, nTR's, nQR's or nPR's for qualification.
         
         xCount = 0;
         
         for ( x = 0; x < 9; ++x )
             if ( nDR[y][x] == 0 )
                if ( nTR[y][x] == 0 )
                  if ( nQR[y][x] == 0 )
                   if ( nPR[y][x] == 0 )
                   if ( checkRemainderTable[y][x] > 1 )
                      if ( checkRemainderTable[y][x] < 6 )
                      {
                           //This is a qualified element for the X-tables.***************
                           xRemTable[xCount] = checkRemainderTable[y][x];
                           xLocTable[xCount] = x;
                           
                           //Put qualified candidates into the X-table.
                           uCount = 0;
                           
                           for ( z = 0; uCount < checkRemainderTable[y][x]; ++z )
                               if ( checkTable[z][y][x] > 0 )
                               {
                                    xCandTable[xCount][uCount] = checkTable[z][y][x];
                                    ++uCount;
                               }
                               
                               ++xCount;
                      }
          

          
                    
         //X-tables are set-up. *****************************************************

         //Exclude all nakedPentsRow Processing, if X-table < 5 elements. goto next row (y). ****
         if ( xCount < 5 )
            continue;
            
            
/*          //for debug purposes, print x-tables for each row........
          for ( x = 0; x < xCount; ++x )
          {
              printf("Row#%d,", y );
              printf("xRem[%d]=%d,", x, xRemTable[x]);
              printf("xLoc[%d]=%d,", x, xLocTable[x]);
              printf("xCand[%d]=%d,%d,%d,%d,%d\n", x, xCandTable[x][0], xCandTable[x][1], xCandTable[x][2],\
                                                   xCandTable[x][3], xCandTable[x][4]);
          }     //  for debug purposes only  *******************
*/          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE X-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt, ttttt and the X-tables; to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (xCount - 4); ++t )
         {
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 5; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (xRemTable[t]); ++u )
                 uniqueCandTable[u] = xCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (xCount - 3); ++tt )
             {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[0]. ***************
                                  
                 uCount = xRemTable[t];
                 
                 if ( uCount < 5 )
                 {
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;
                        
                    for ( u = 0; u < 3; ++u )
                        uniqueAdded[u] = 0;
                 } //ends if uC.....      
                    
                 for ( u = 0; u < xRemTable[tt]; ++u )
                 {
                     cand = xCandTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[0];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
 /*                   // debug purposes ******************************************
                    printf("2F y=%d, t=%d, tt=%d, ", y, t, tt );
                    printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
 */                   // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
   /*              // debug purposes ******************************************
                 printf("2S y=%d, t=%d, tt=%d, ", y, t, tt );
                 printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
   */              // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO SECOND. *********
                for ( ttt = (tt + 1); ttt < (xCount - 2); ++ttt )
                {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (xRemTable[t] + uniqueAdded[0]);
                 
                 if ( uCount < 5 )
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;  
                                               
                 uniqueAdded[1] = 0;      
                    
                 for ( u = 0; u < (xRemTable[ttt]); ++u )
                 {
                     cand = xCandTable[ttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[1];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
  /*                  // debug purposes ******************************************
                    printf("3F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                    printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 3rd ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("3S y=%d, t=%d, tt=%d, ttt=%d,  ", y, t, tt, ttt );
                 printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
  */               // debug purposes ******************************************************
                 
                  //BEGIN SEARCH FOR A FOURTH ELEMENT TO LINK TO SECOND. *********
                for ( tttt = (ttt + 1); tttt < (xCount - 1); ++tttt )
                {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (xRemTable[t] + uniqueAdded[0] + uniqueAdded[1]);
                 
                 if ( uCount < 5 )
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;  
                                               
                 uniqueAdded[2] = 0;      
                    
                 for ( u = 0; u < (xRemTable[tttt]); ++u )
                 {
                     cand = xCandTable[tttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[2];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
 /*                   // debug purposes ******************************************
                    printf("4F y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                    printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
 */                   // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 4th ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 4TH ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("4S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                 printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
  */               // debug purposes ******************************************************
                 
                 
                 
                 
                 //Begin search for possible 5th element of linkedTable. **********************
                 for ( ttttt = (tttt + 1); ttttt < xCount; ++ttttt )
                 {
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttttt. ****************************************
                     uCount = (xRemTable[t] + uniqueAdded[0] + uniqueAdded[1] + uniqueAdded[2]);
             
                     for ( u = 0; u < xRemTable[ttttt]; ++u )
                     {
                         cand = xCandTable[ttttt][u];
                 
                         for ( uu = 0; uu < 5; ++uu )
                             if ( uniqueCandTable[uu] != cand )
                                continue;
                             else
                             {
                                 cand = 0;
                                 break;
                             } // ends for ( uu = ... ***********
                         
                         if ( cand == 0 )
                            continue;  // next u ... *******************
                        
                         // Over the limit.... *********
                         ++uCount;
                         break;
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 5 )
                {
   /*                // debug purposes ******************************************
                   printf("5F y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d, ", y, t, tt, ttt, tttt, ttttt );
                   printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                   uniqueCandTable[3], uniqueCandTable[4]);
  */                 // debug purposes ******************************************************
                   continue;    //unable to link 5th element to 4th. Need to try a different fourth element,
                }    
              
         
                  
                // a nakedPentsRow has been achieved. Process the nPR. ***************
         
  /*              // debug purposes ******************************************
                printf("5S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d, ", y, t, tt, ttt, tttt, ttttt );
                printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                  uniqueCandTable[3], uniqueCandTable[4]);
  */              // debug purposes ******************************************************
         
                //Put all 5 elements t, tt, ttt, tttt and ttttt into the nPR table. ****************
                nPR[y][(xLocTable[t])] = 1;
                nPR[y][(xLocTable[tt])] = 1;
                nPR[y][(xLocTable[ttt])] = 1;
                nPR[y][(xLocTable[tttt])] = 1;
                nPR[y][(xLocTable[ttttt])] = 1;
                
                //Zap all other occurances of these 5 unique candidates, from the other 4 cells in the row. ****
                for ( z = 0; z < 9; ++z )
                    for ( x = 0; x < 9; ++x )
                        if ( x != (xLocTable[t]) )
                           if ( x != (xLocTable[tt]) )
                             if ( x != (xLocTable[ttt]) )
                              if ( x != (xLocTable[tttt]) )
                              if ( x != (xLocTable[ttttt]) )
                              {
                                 for ( u = 0; u < 4; ++u )
                                     if ( checkTable[z][y][x] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
          printf("Zapped xC=%d at [%d][%d]- in NakPentsRow...\t", (z + 1), y, x);   // debug purposes
                                     } //end if cT... ******
                              }  // end if xLoc... **********
                 
                      if ( changes )
                      return;
                      
                } // ends ttttt ..... **********
                } //ends tttt..... **********
                
              } // ends ttt... ************
         
              
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
         // debug purposes ******************************************
 /*        printf("E  y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d ", y, t, tt, ttt, tttt, ttttt );
         printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                           uniqueCandTable[3], uniqueCandTable[4]);
 */        // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             
//nakedPentsColumn Function ******************************************************
void nakedPentsColumn (void)
{
     int x, y, z, yy, u, uu, t, tt, ttt, tttt, ttttt, cand, uCount, yCount, uniqueAdded[3];
     int yRemTable[9], yCandTable[9][5], yLocTable[9], uniqueCandTable[5];
     
     for ( x = 0; x < 9; ++x )
     {
         //Initialize Y-tables. *******************************************
         for ( y = 0; y < 9; ++y )
         {
             yRemTable[y] = 0;
             yLocTable[y] = 0;
             
             for ( yy = 0; yy < 5; ++yy )
                 yCandTable[y][yy] = 0;
         }
         
         //Fill Y-tables with qualifying elements; y-locations that have a checkRemainder
         //  of 2 thru 5. Also, don't include nDC's, nTC's, nQC's or nPC's for qualification.
         
         yCount = 0;
         
         for ( y = 0; y < 9; ++y )
             if ( nDC[y][x] == 0 )
                if ( nTC[y][x] == 0 )
                  if ( nQC[y][x] == 0 )
                   if ( nPC[y][x] == 0 )
                   if ( checkRemainderTable[y][x] > 1 )
                      if ( checkRemainderTable[y][x] < 6 )
                      {
                           //This is a qualified element for the Y-tables.***************
                           yRemTable[yCount] = checkRemainderTable[y][x];
                           yLocTable[yCount] = y;
                           
                           //Put qualified candidates into the Y-table.
                           uCount = 0;
                           
                           for ( z = 0; uCount < checkRemainderTable[y][x]; ++z )
                               if ( checkTable[z][y][x] > 0 )
                               {
                                    yCandTable[yCount][uCount] = checkTable[z][y][x];
                                    ++uCount;
                               }
                               
                               ++yCount;
                      }  //ends if cT...************
          

          
                    
         //Y-tables are set-up. *****************************************************

         //Exclude all nakedPentsColumn Processing, if Y-table < 5 elements. goto next column (x). ****
         if ( yCount < 5 )
            continue;
            
            
  /*        //for debug purposes, print y-tables for each column........
          for ( y = 0; y < yCount; ++y )
          {
              printf("Col#%d,", x );
              printf("yRem[%d]=%d,", y, yRemTable[y]);
              printf("yLoc[%d]=%d,", y, yLocTable[y]);
              printf("yCand[%d]=%d,%d,%d,%d,%d.\n", y, yCandTable[y][0], yCandTable[y][1], yCandTable[y][2],\
                                                   yCandTable[y][3], yCandTable[y][4]);
          }     //  for debug purposes only  *******************
  */      
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE Y-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt, ttttt and the Y-tables; to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (yCount - 4); ++t )
         {
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 5; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (yRemTable[t]); ++u )
                 uniqueCandTable[u] = yCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (yCount - 3); ++tt )
             {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[0]. ***************
                                  
                 uCount = yRemTable[t];
                 
                 if ( uCount < 5 )
                 {
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;
                        
                    for ( u = 0; u < 3; ++u )
                        uniqueAdded[u] = 0;
                 }  //ends if uC... *******      
                    
                 for ( u = 0; u < (yRemTable[tt]); ++u )
                 {
                     cand = yCandTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[0];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
  /*                  // debug purposes ******************************************
                    printf("2F x=%d, t=%d, tt=%d, ", x, t, tt );
                    printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
 /*                // debug purposes ******************************************
                 printf("2S x=%d, t=%d, tt=%d, ", x, t, tt );
                 printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
 */                // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO SECOND. *********
                 for ( ttt = (tt + 1); ttt < (yCount - 2); ++ttt )
                 {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (yRemTable[t] + uniqueAdded[0]);
                 
                 if ( uCount < 5 )
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;  
                        
                 uniqueAdded[1] = 0;      
                    
                 for ( u = 0; u < (yRemTable[ttt]); ++u )
                 {
                     cand = yCandTable[ttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[1];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
  /*                  // debug purposes ******************************************
                    printf("3F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                    printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                        uniqueCandTable[3], uniqueCandTable[4]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 3rd ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("3S x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                 printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
  */               // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A FOURTH ELEMENT TO LINK TO THIRD. *********
                 for ( tttt = (ttt + 1); tttt < (yCount - 1); ++tttt )
                 {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (yRemTable[t] + uniqueAdded[0] + uniqueAdded[1]);
                 
                 if ( uCount < 5 )
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;  
                        
                 uniqueAdded[2] = 0;      
                    
                 for ( u = 0; u < (yRemTable[tttt]); ++u )
                 {
                     cand = yCandTable[tttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[2];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
    /*                // debug purposes ******************************************
                    printf("4F x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
                    printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                        uniqueCandTable[3], uniqueCandTable[4]);
    */                // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 4th ELEMENT TO THE THIRD. TRY ANOTHER FOURTH. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 4TH ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("4S x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
                 printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
  */               // debug purposes ******************************************************
                 
                 
                 
                 //Begin search for possible 5th element of linkedTable. **********************
                 for ( ttttt = (tttt + 1); ttttt < yCount; ++ttttt )
                 {
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttttt. ****************************************
                     uCount = (yRemTable[t] + uniqueAdded[0] + uniqueAdded[1] + uniqueAdded[2]);
             
                     for ( u = 0; u < yRemTable[ttttt]; ++u )
                     {
                         cand = yCandTable[ttttt][u];
                 
                         for ( uu = 0; uu < 5; ++uu )
                             if ( uniqueCandTable[uu] != cand )
                                continue;
                             else
                             {
                                 cand = 0;
                                 break;
                             } // ends for ( uu = ... ***********
                         
                         if ( cand == 0 )
                            continue;  // next u ... *******************
                        
                         // Over the limit.... *********
                         ++uCount;
                         break;
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 5 )
                {
  /*                 // debug purposes ******************************************
                   printf("5F x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d, ", x, t, tt, ttt, tttt, ttttt );
                   printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                   uniqueCandTable[3], uniqueCandTable[4]);
  */                 // debug purposes ******************************************************
                   continue;    //unable to link 5th element to 4th. Need to try a different fifth element,
                }    
              
         
                  
                // a nakedPentsColumn has been achieved. Process the nPC. ***************
         
  /*              // debug purposes ******************************************
                printf("5S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d ", y, t, tt, ttt, tttt, ttttt );
                printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                  uniqueCandTable[3], uniqueCandTable[4]);
  */              // debug purposes ******************************************************
         
                //Put all 5 elements t, tt, ttt, tttt and ttttt into the nPC table. ****************
                nPC[(yLocTable[t])][x] = 1;
                nPC[(yLocTable[tt])][x] = 1;
                nPC[(yLocTable[ttt])][x] = 1;
                nPC[(yLocTable[tttt])][x] = 1;
                nPC[(yLocTable[ttttt])][x] = 1;
                  
                //Zap all other occurances of these 5 unique candidates, from the other 4 cells in the column. ****
                for ( z = 0; z < 9; ++z )
                    for ( y = 0; y < 9; ++y )
                        if ( y != (yLocTable[t]) )
                           if ( y != (yLocTable[tt]) )
                             if ( y != (yLocTable[ttt]) )
                              if ( y != (yLocTable[tttt]) )
                              if ( y != (yLocTable[ttttt]) )
                              {
                                 for ( u = 0; u < 5; ++u )
                                     if ( checkTable[z][y][x] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
               printf("Zapped yC=%d at [%d][%d]- in NakPentsCol...\t", (z + 1), y, x);   // debug purposes 
                                     } //end if cT... ******
                              }  // end if yLoc... **********
                 
                      if ( changes )
                      return;
                      
                } //ends ttttt..... *********************
               } // ends tttt ............... ******* 
                
              } // ends ttt... ************
         
              
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*        // debug purposes ******************************************
         printf("E  x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d, ", x, t, tt, ttt, tttt, ttttt );
         printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                           uniqueCandTable[3], uniqueCandTable[4]);
 */        // debug purposes ******************************************************
         
         
   } //end for ( x = ... *********   
   return;
}
             
//nakedPentsRegion Function ******************************************************
void nakedPentsRegion (void)
{
     int x, y, z, xx, u, uu, t, tt, ttt, tttt, ttttt, cand, uCount, regCount, uniqueAdded[3];
     int regRemTable[9], regCandTable[9][5], regLocTable[9], uniqueCandTable[5];
     int region, a, r, c;
     
     
     for ( region = 0; region < 9; ++region )
     {
         //Initialize Reg-tables. *******************************************
         for ( a = 0; a < 9; ++a )
         {
             regRemTable[a] = 0;
             regLocTable[a] = 0;
             
             for ( xx = 0; xx < 5; ++xx )
                 regCandTable[a][xx] = 0;
         } //ends for a.... ********
         
         //Fill Reg-tables with qualifying elements; a-locations that have a checkRemainder
         //  of 2 thru 5. Also, don't include nDReg's, nTReg's, or nQReg's for qualification.
         
         regCount = 0;
         
         for ( a = 0; a < 9; ++a )
         {
             r = regionalDispatchTable[region][a].row;
             c = regionalDispatchTable[region][a].column;
             
             if ( nDReg[r][c] == 0 )
                if ( nTReg[r][c] == 0 )
                  if ( nQReg[r][c] == 0 )
                   if ( nPReg[r][c] == 0 )
                   if ( checkRemainderTable[r][c] > 1 )
                      if ( checkRemainderTable[r][c] < 6 )
                      {
                           //This is a qualified element for the Reg-tables.***************
                           regRemTable[regCount] = checkRemainderTable[r][c];
                           regLocTable[regCount] = a;
                           
                           //Put qualified candidates into the Reg-table.
                           uCount = 0;
                           
                           for ( z = 0; uCount < checkRemainderTable[r][c]; ++z )
                               if ( checkTable[z][r][c] > 0 )
                               {
                                    regCandTable[regCount][uCount] = checkTable[z][r][c];
                                    ++uCount;
                               }
                               
                               ++regCount;
                      }// ends if cRT. *********
          
          }  // ends for a = ........ *********
          
                    
         //Reg-tables are set-up. *****************************************************

         //Exclude all nakedPentsRegion Processing, if X-table < 5 elements. goto next row (y). ****
         if ( regCount < 5 )
            continue;
            
            
/*          //for debug purposes, print reg-tables for each region........
          for ( xx = 0; xx < regCount; ++xx )
          {
              printf("Reg#%d,", region );
              printf("regRem[%d]=%d,", xx, regRemTable[xx]);
              printf("regLoc[%d]=%d,", xx, regLocTable[xx]);
              printf("regCand[%d]=%d,%d,%d,%d,%d.\n", xx, regCandTable[xx][0], regCandTable[xx][1], regCandTable[xx][2], \
                                                   regCandTable[xx][3], regCandTable[xx][4]);
          }     //  for debug purposes only  *******************
  */        
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE REG-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the Reg-tables; to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (regCount - 4); ++t )
         {
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 5; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (regRemTable[t]); ++u )
                 uniqueCandTable[u] = regCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (regCount - 3); ++tt )
             {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[0]. ***************
                                  
                 uCount = regRemTable[t];
                 
                 if ( uCount < 5 )
                 {
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;
                        
                    for ( u = 0; u < 3; ++u )
                        uniqueAdded[u] = 0; 
                 }  // ends if uC.... ****************                             
                    
                 for ( u = 0; u < (regRemTable[tt]); ++u )
                 {
                     cand = regCandTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[0];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
   /*                 // debug purposes ******************************************
                    printf("2F reg=%d, t=%d, tt=%d, ", region, t, tt );
                    printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
   */                 // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("2S reg=%d, t=%d, tt=%d, ", region, t, tt );
                 printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
  */               // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO SECOND. *********
                 for ( ttt = (tt + 1); ttt < (regCount - 2); ++ttt )
                 {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (regRemTable[t] + uniqueAdded[0]);
                 
                 if ( uCount < 5 )
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;  
                        
                 uniqueAdded[1] = 0;      
                    
                 for ( u = 0; u < (regRemTable[ttt]); ++u )
                 {
                     cand = regCandTable[ttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[1];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
  /*                  // debug purposes ******************************************
                    printf("3F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                    printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 3rd ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("3S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                 printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
  */               // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A FOURTH ELEMENT TO LINK TO THIRD. *********
                 for ( tttt = (ttt + 1); tttt < (regCount - 1); ++tttt )
                 {
                 //if uCount < 5, put unique candidate(s) into uniqueCandTable, 
                 //add to uniqueAdded[2]. ***************
                                  
                 uCount = (regRemTable[t] + uniqueAdded[0] + uniqueAdded[1]);
                 
                 if ( uCount < 5 )
                    for ( u = uCount; u < 5; ++u )
                        uniqueCandTable[u] = 0;  
                        
                 uniqueAdded[2] = 0;      
                    
                 for ( u = 0; u < (regRemTable[tttt]); ++u )
                 {
                     cand = regCandTable[tttt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;  // next uu.. *******
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have a unique candidate. *************
                     ++uCount;
                     
                     if ( uCount < 6 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[2];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 5 )
                 {
    /**                // debug purposes ******************************************
                    printf("4F reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
                    printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3], uniqueCandTable[4]);
     */               // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 4th ELEMENT TO THE THIRD. TRY ANOTHER FOURTH. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 4TH ELEMENT IN LINKED TABLE. **********************
                              
   /*              // debug purposes ******************************************
                 printf("4S reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
                 printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3], uniqueCandTable[4]);
   */              // debug purposes ******************************************************
                 
                 
                 
                 //Begin search for possible 5th element of linkedTable. **********************
                 for ( ttttt = (tttt + 1); ttttt < regCount; ++ttttt )
                 {
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     uCount = (regRemTable[t] + uniqueAdded[0] + uniqueAdded[1] + uniqueAdded[2]);
             
                     for ( u = 0; u < regRemTable[ttttt]; ++u )
                     {
                         cand = regCandTable[ttttt][u];
                 
                         for ( uu = 0; uu < 5; ++uu )
                             if ( uniqueCandTable[uu] != cand )
                                continue;
                             else
                             {
                                 cand = 0;
                                 break;
                             } // ends for ( uu = ... ***********
                         
                         if ( cand == 0 )
                            continue;  // next u ... *******************
                        
                         // Over the limit.... *********
                         ++uCount;
                         break;
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 5 )
                {
  /*                 // debug purposes ******************************************
                   printf("5F reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d ", region, t, tt, ttt, tttt, ttttt );
                   printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d,%d, %d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                   uniqueCandTable[3], uniqueCandTable[4]);
  **/                 // debug purposes ******************************************************
                   continue;    //unable to link 5th element to 4th. Need to try a different fourth element,
                }    
              
         
                  
                // a nakedPentsRegion has been achieved. Process the nPReg. ***************
         
    /*            // debug purposes ******************************************
                printf("5S reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d, ", region, t, tt, ttt, tttt, ttttt );
                printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                  uniqueCandTable[3], uniqueCandTable[4]);
    */            // debug purposes ******************************************************
         
                //Put all 5 elements t, tt, ttt, tttt and ttttt into the nPR table. ****************
                r = regionalDispatchTable[region][(regLocTable[t])].row;
                c = regionalDispatchTable[region][(regLocTable[t])].column;
                nPReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[tt])].row;
                c = regionalDispatchTable[region][(regLocTable[tt])].column;
                nPReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[ttt])].row;
                c = regionalDispatchTable[region][(regLocTable[ttt])].column;
                nPReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[tttt])].row;
                c = regionalDispatchTable[region][(regLocTable[tttt])].column;
                nPReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[ttttt])].row;
                c = regionalDispatchTable[region][(regLocTable[ttttt])].column;
                nPReg[r][c] = 1;
                
         
                //Zap all other occurances of these 5 unique candidates, from the other 4 cells in the row. ****
                for ( z = 0; z < 9; ++z )
                    for ( a = 0; a < 9; ++a )
                    {
                        r = regionalDispatchTable[region][a].row;
                        c = regionalDispatchTable[region][a].column;
                
                        if ( a != (regLocTable[t]) )
                           if ( a != (regLocTable[tt]) )
                             if ( a != (regLocTable[ttt]) )
                              if ( a != (regLocTable[tttt]) )
                               if ( a != (regLocTable[ttttt]) )
                              {
                                 for ( u = 0; u < 5; ++u )
                                     if ( checkTable[z][r][c] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][r][c] = 0;
                                        --checkRemainderTable[r][c];
                                        ++changes;
             printf("Zapped regC=%d at [%d][%d]- in NakPentsReg...\t", (z + 1), r, c);   // debug purposes
                                     } //end if cT... ******
                              }  // end if xLoc... **********
                   } // ends for a = ...... **********
                
                   if ( changes )
                      return;
                      
                } //ends ttttt... *************************
               }  // ends tttt... ************************ 
                
              } // ends ttt... ************
         
              
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*        // debug purposes ******************************************
         printf("E  reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ttttt=%d, ", region, t, tt, ttt, tttt, tttt );
         printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                           uniqueCandTable[3], uniqueCandTable[4]);
 */        // debug purposes ******************************************************
         
         
   } //end for ( region = ... *********   
   return;
}
             

