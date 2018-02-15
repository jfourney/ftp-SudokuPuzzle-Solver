// Naked Quads Processing for Sudoku. *******************

/*
// Function Declarations **************************************************
void nakedQuadsRow (void);
void nakedQuadsColumn (void);
void nakedQuadsRegion (void);
*/

//nakedQuadsRow Function ******************************************************
void nakedQuadsRow (void)
{
     int x, y, z, xx, u, uu, t, tt, ttt, tttt, cand, uCount, xCount, uniqueAdded[2];
     int xRemTable[9], xCandTable[9][4], xLocTable[9], uniqueCandTable[4];
     
     
     for ( y = 0; y < 9; ++y )
     {
         //Initialize X-tables. *******************************************
         for ( x = 0; x < 9; ++x )
         {
             xRemTable[x] = 0;
             xLocTable[x] = 0;
             
             for ( xx = 0; xx < 4; ++xx )
                 xCandTable[x][xx] = 0;
         }
         
         //Fill X-tables with qualifying elements; x-locations that have a checkRemainder
         //  of 2 thru 4. Also, don't include nDR's, nTR's, or nQR's for qualification.
         
         xCount = 0;
         
         for ( x = 0; x < 9; ++x )
             if ( nDR[y][x] == 0 )
                if ( nTR[y][x] == 0 )
                  if ( nQR[y][x] == 0 )
                   if ( checkRemainderTable[y][x] > 1 )
                      if ( checkRemainderTable[y][x] < 5 )
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

         //Exclude all nakedTripleRow Processing, if X-table < 4 elements. goto next row (y). ****
         if ( xCount < 4 )
            continue;
            
            
/*          //for debug purposes, print x-tables for each row........
          for ( x = 0; x < xCount; ++x )
          {
              printf("Row#%d,", y );
              printf("xRem[%d]=%d,", x, xRemTable[x]);
              printf("xLoc[%d]=%d,", x, xLocTable[x]);
              printf("xCand[%d]=%d,%d,%d,%d\n", x, xCandTable[x][0], xCandTable[x][1], xCandTable[x][2],\
                                                   xCandTable[x][3]);
          }     //  for debug purposes only  *******************
*/          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE X-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the X-tables; to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (xCount - 3); ++t )
         {
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 4; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (xRemTable[t]); ++u )
                 uniqueCandTable[u] = xCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (xCount - 2); ++tt )
             {
                 //if uCount < 4, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[0]. ***************
                                  
                 uCount = xRemTable[t];
                 
                 if ( uCount < 4 )
                 {
                    for ( u = uCount; u < 4; ++u )
                        uniqueCandTable[u] = 0;
                        
                    for ( u = 0; u < 2; ++u )
                        uniqueAdded[u] = 0;
                 } //ends if uC.....      
                    
                 for ( u = 0; u < (xRemTable[tt]); ++u )
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[0];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
        /*            // debug purposes ******************************************
                    printf("2F y=%d, t=%d, tt=%d, ", y, t, tt );
                    printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3]);
        */            // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
     /*            // debug purposes ******************************************
                 printf("2S y=%d, t=%d, tt=%d, ", y, t, tt );
                 printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3]);
     */            // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO SECOND. *********
                for ( ttt = (tt + 1); ttt < (xCount - 1); ++ttt )
                {
                 //if uCount < 4, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (xRemTable[t] + uniqueAdded[0]);
                 
                 if ( uCount < 4 )
                    uniqueCandTable[3] = 0;  //uCount must be 3, at this point..***
                        
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[3] = cand;
                          ++uniqueAdded[1];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
   /*                 // debug purposes ******************************************
                    printf("3F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                    printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3]);
   */                 // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 3rd ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
   /*              // debug purposes ******************************************
                 printf("3S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                 printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3]);
   */              // debug purposes ******************************************************
                 
                 //Begin search for possible 4th element of linkedTable. **********************
                 for ( tttt = (ttt + 1); tttt < xCount; ++tttt )
                 {
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     uCount = (xRemTable[t] + uniqueAdded[0] + uniqueAdded[1]);
             
                     for ( u = 0; u < xRemTable[tttt]; ++u )
                     {
                         cand = xCandTable[tttt][u];
                 
                         for ( uu = 0; uu < 4; ++uu )
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
             
             
         
                if (uCount > 4 )
                {
    /*               // debug purposes ******************************************
                   printf("4F y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                   printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                   uniqueCandTable[3]);
    */               // debug purposes ******************************************************
                   continue;    //unable to link 4th element to 3rd. Need to try a different third element,
                }    
              
         
                  
                // a nakedQuadsRow has been achieved. Process the nQR. ***************
         
   /**             // debug purposes ******************************************
                printf("4S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                  uniqueCandTable[3]);
    */            // debug purposes ******************************************************
         
                //Put all 4 elements t, tt, ttt, and tttt into the nQR table. ****************
                nQR[y][(xLocTable[t])] = 1;
                nQR[y][(xLocTable[tt])] = 1;
                nQR[y][(xLocTable[ttt])] = 1;
                nQR[y][(xLocTable[tttt])] = 1;
         
                //Zap all other occurances of these 4 unique candidates, from the other 5 cells in the row. ****
                for ( z = 0; z < 9; ++z )
                    for ( x = 0; x < 9; ++x )
                        if ( x != (xLocTable[t]) )
                           if ( x != (xLocTable[tt]) )
                             if ( x != (xLocTable[ttt]) )
                              if ( x != (xLocTable[tttt]) )
                              {
                                 for ( u = 0; u < 4; ++u )
                                     if ( checkTable[z][y][x] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
         printf("Zapped xC=%d at [%d][%d]- in NakQuadRow...\t", (z + 1), y, x);   // debug purposes     
                                     } //end if cT... ******
                              }  // end if xLoc... **********
                              
                   if ( changes )
                      return;
                              
               } //ends tttt..... **********
                
              } // ends ttt... ************
         
              
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*        // debug purposes ******************************************
         printf("E  y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
         printf("xCount=%d, uCount=%d, cand=%d, ", xCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                           uniqueCandTable[3]);
 */        // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             
//nakedQuadsColumn Function ******************************************************
void nakedQuadsColumn (void)
{
     int x, y, z, yy, u, uu, t, tt, ttt, tttt, cand, uCount, yCount, uniqueAdded[2];
     int yRemTable[9], yCandTable[9][4], yLocTable[9], uniqueCandTable[4];
     
     for ( x = 0; x < 9; ++x )
     {
         //Initialize Y-tables. *******************************************
         for ( y = 0; y < 9; ++y )
         {
             yRemTable[y] = 0;
             yLocTable[y] = 0;
             
             for ( yy = 0; yy < 4; ++yy )
                 yCandTable[y][yy] = 0;
         }
         
         //Fill Y-tables with qualifying elements; y-locations that have a checkRemainder
         //  of 2 thru 4. Also, don't include nDC's, nTC's, or nQC's for qualification.
         
         yCount = 0;
         
         for ( y = 0; y < 9; ++y )
             if ( nDC[y][x] == 0 )
                if ( nTC[y][x] == 0 )
                  if ( nQC[y][x] == 0 )
                   if ( checkRemainderTable[y][x] > 1 )
                      if ( checkRemainderTable[y][x] < 5 )
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
                      }
          

          
                    
         //Y-tables are set-up. *****************************************************

         //Exclude all nakedTripleColumn Processing, if Y-table < 4 elements. goto next column (x). ****
         if ( yCount < 4 )
            continue;
            
            
/*          //for debug purposes, print y-tables for each column........
          for ( y = 0; y < yCount; ++y )
          {
              printf("Col#%d,", x );
              printf("yRem[%d]=%d,", y, yRemTable[y]);
              printf("yLoc[%d]=%d,", y, yLocTable[y]);
              printf("yCand[%d]=%d,%d,%d,%d.\n", y, yCandTable[y][0], yCandTable[y][1], yCandTable[y][2],\
                                                   yCandTable[y][3]);
          }     //  for debug purposes only  *******************
*/        
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE Y-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the Y-tables; to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (yCount - 3); ++t )
         {
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 4; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (yRemTable[t]); ++u )
                 uniqueCandTable[u] = yCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (yCount - 2); ++tt )
             {
                 //if uCount < 4, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[0]. ***************
                                  
                 uCount = yRemTable[t];
                 
                 if ( uCount < 4 )
                 {
                    for ( u = uCount; u < 4; ++u )
                        uniqueCandTable[u] = 0;
                        
                    for ( u = 0; u < 2; ++u )
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[0];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
/*                    // debug purposes ******************************************
                    printf("2F x=%d, t=%d, tt=%d, ", x, t, tt );
                    printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3]);
*/                    // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
                 // debug purposes ******************************************
/*                 printf("2S x=%d, t=%d, tt=%d, ", x, t, tt );
                 printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3]);
*/                 // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO SECOND. *********
                 for ( ttt = (tt + 1); ttt < (yCount - 1); ++ttt )
                 {
                 //if uCount < 4, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (yRemTable[t] + uniqueAdded[0]);
                 
                 if ( uCount < 4 )
                    uniqueCandTable[3] = 0;  //uCount must be 3, at this point..***
                        
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[3] = cand;
                          ++uniqueAdded[1];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
/*                    // debug purposes ******************************************
                    printf("3F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                    printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3]);
*/                    // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 3rd ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
/*                 // debug purposes ******************************************
                 printf("3S x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                 printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3]);
*/                 // debug purposes ******************************************************
                 
                 //Begin search for possible 4th element of linkedTable. **********************
                 for ( tttt = (ttt + 1); tttt < yCount; ++tttt )
                 {
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     uCount = (yRemTable[t] + uniqueAdded[0] + uniqueAdded[1]);
             
                     for ( u = 0; u < yRemTable[tttt]; ++u )
                     {
                         cand = yCandTable[tttt][u];
                 
                         for ( uu = 0; uu < 4; ++uu )
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
             
             
         
                if (uCount > 4 )
                {
/*                   // debug purposes ******************************************
                   printf("4F x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
                   printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                   uniqueCandTable[3]);
*/                   // debug purposes ******************************************************
                   continue;    //unable to link 4th element to 3rd. Need to try a different third element,
                }    
              
         
                  
                // a nakedQuadsColumn has been achieved. Process the nQC. ***************
         
/*                // debug purposes ******************************************
                printf("4S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                  uniqueCandTable[3]);
*/                // debug purposes ******************************************************
         
                //Put all 4 elements t, tt, ttt, and tttt into the nQC table. ****************
                nQC[(yLocTable[t])][x] = 1;
                nQC[(yLocTable[tt])][x] = 1;
                nQC[(yLocTable[ttt])][x] = 1;
                nQC[(yLocTable[tttt])][x] = 1;
         
                //Zap all other occurances of these 4 unique candidates, from the other 5 cells in the column. ****
                for ( z = 0; z < 9; ++z )
                    for ( y = 0; y < 9; ++y )
                        if ( y != (yLocTable[t]) )
                           if ( y != (yLocTable[tt]) )
                             if ( y != (yLocTable[ttt]) )
                              if ( y != (yLocTable[tttt]) )
                              {
                                 for ( u = 0; u < 4; ++u )
                                     if ( checkTable[z][y][x] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
          printf("Zapped xC=%d at [%d][%d]- in nakQuadCol...\t", (z + 1), y, x);   // debug purposes
                                     } //end if cT... ******
                              }  // end if xLoc... **********
                   
                    if ( changes )
                      return;
               
               } // ends tttt ............... ******* 
                
              } // ends ttt... ************
         
              
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
/*         // debug purposes ******************************************
         printf("E  x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
         printf("yCount=%d, uCount=%d, cand=%d, ", yCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                           uniqueCandTable[3]);
*/         // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             
//nakedQuadsRegion Function ******************************************************
void nakedQuadsRegion (void)
{
     int x, y, z, xx, u, uu, t, tt, ttt, tttt, cand, uCount, regCount, uniqueAdded[2];
     int regRemTable[9], regCandTable[9][4], regLocTable[9], uniqueCandTable[4];
     int region, a, r, c;
     
     
     for ( region = 0; region < 9; ++region )
     {
         //Initialize Reg-tables. *******************************************
         for ( a = 0; a < 9; ++a )
         {
             regRemTable[a] = 0;
             regLocTable[a] = 0;
             
             for ( xx = 0; xx < 4; ++xx )
                 regCandTable[a][xx] = 0;
         }
         
         //Fill Reg-tables with qualifying elements; a-locations that have a checkRemainder
         //  of 2 thru 4. Also, don't include nDReg's, nTReg's, or nQReg's for qualification.
         
         regCount = 0;
         
         for ( a = 0; a < 9; ++a )
         {
             r = regionalDispatchTable[region][a].row;
             c = regionalDispatchTable[region][a].column;
             
             if ( nDReg[r][c] == 0 )
                if ( nTReg[r][c] == 0 )
                  if ( nQReg[r][c] == 0 )
                   if ( checkRemainderTable[r][c] > 1 )
                      if ( checkRemainderTable[r][c] < 5 )
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
                      }
          
          }  // ends for a = ........ *********
          
                    
         //Reg-tables are set-up. *****************************************************

         //Exclude all nakedTripleRow Processing, if X-table < 4 elements. goto next row (y). ****
         if ( regCount < 4 )
            continue;
            
            
/*          //for debug purposes, print reg-tables for each region........
          for ( xx = 0; xx < regCount; ++xx )
          {
              printf("Reg#%d,", region );
              printf("regRem[%d]=%d,", xx, regRemTable[xx]);
              printf("regLoc[%d]=%d,", xx, regLocTable[xx]);
              printf("regCand[%d]=%d,%d,%d,%d.\n", xx, regCandTable[xx][0], regCandTable[xx][1], regCandTable[xx][2],\
                                                   regCandTable[xx][3]);
          }     //  for debug purposes only  *******************
*/          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE REG-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the Reg-tables; to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (regCount - 3); ++t )
         {
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 4; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (regRemTable[t]); ++u )
                 uniqueCandTable[u] = regCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (regCount - 2); ++tt )
             {
                 //if uCount < 4, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[0]. ***************
                                  
                 uCount = regRemTable[t];
                 
                 if ( uCount < 4 )
                 {
                    for ( u = uCount; u < 4; ++u )
                        uniqueCandTable[u] = 0;
                        
                    for ( u = 0; u < 2; ++u )
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[(uCount - 1)] = cand;
                          ++uniqueAdded[0];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
  /*                  // debug purposes ******************************************
                    printf("2F reg=%d, t=%d, tt=%d, ", region, t, tt );
                    printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
 /*                // debug purposes ******************************************
                 printf("2S reg=%d, t=%d, tt=%d, ", region, t, tt );
                 printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3]);
 */                // debug purposes ******************************************************
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO SECOND. *********
                 for ( ttt = (tt + 1); ttt < (regCount - 1); ++ttt )
                 {
                 //if uCount < 4, put unique candidate(s) into uniqueCandTable, 
                 //add to unique addedTable[1]. ***************
                                  
                 uCount = (regRemTable[t] + uniqueAdded[0]);
                 
                 if ( uCount < 4 )
                    uniqueCandTable[3] = 0;  //uCount must be 3, at this point..***
                        
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[3] = cand;
                          ++uniqueAdded[1];
                     }
                     else                     
                          // Over the limit- doesn't qualify for link table.. *****************
                          break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
  /*                  // debug purposes ******************************************
                    printf("3F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                    printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                         uniqueCandTable[3]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS 3rd ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("3S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                 printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                      uniqueCandTable[3]);
  */               // debug purposes ******************************************************
                 
                 //Begin search for possible 4th element of linkedTable. **********************
                 for ( tttt = (ttt + 1); tttt < regCount; ++tttt )
                 {
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     uCount = (regRemTable[t] + uniqueAdded[0] + uniqueAdded[1]);
             
                     for ( u = 0; u < regRemTable[tttt]; ++u )
                     {
                         cand = regCandTable[tttt][u];
                 
                         for ( uu = 0; uu < 4; ++uu )
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
             
             
         
                if (uCount > 4 )
                {
  /*                 // debug purposes ******************************************
                   printf("4F reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
                   printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                   uniqueCandTable[3]);
  */                 // debug purposes ******************************************************
                   continue;    //unable to link 4th element to 3rd. Need to try a different third element,
                }    
              
         
                  
                // a nakedQuadsRegion has been achieved. Process the nQReg. ***************
         
 /*               // debug purposes ******************************************
                printf("4S reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
                printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                                  uniqueCandTable[3]);
 */               // debug purposes ******************************************************
         
                //Put all 4 elements t, tt, ttt, and tttt into the nQR table. ****************
                r = regionalDispatchTable[region][(regLocTable[t])].row;
                c = regionalDispatchTable[region][(regLocTable[t])].column;
                nQReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[tt])].row;
                c = regionalDispatchTable[region][(regLocTable[tt])].column;
                nQReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[ttt])].row;
                c = regionalDispatchTable[region][(regLocTable[ttt])].column;
                nQReg[r][c] = 1;
                
                r = regionalDispatchTable[region][(regLocTable[tttt])].row;
                c = regionalDispatchTable[region][(regLocTable[tttt])].column;
                nQReg[r][c] = 1;
                
         
                //Zap all other occurances of these 4 unique candidates, from the other 5 cells in the row. ****
                for ( z = 0; z < 9; ++z )
                    for ( a = 0; a < 9; ++a )
                    {
                        r = regionalDispatchTable[region][a].row;
                        c = regionalDispatchTable[region][a].column;
                
                        if ( a != (regLocTable[t]) )
                           if ( a != (regLocTable[tt]) )
                             if ( a != (regLocTable[ttt]) )
                              if ( a != (regLocTable[tttt]) )
                              {
                                 for ( u = 0; u < 4; ++u )
                                     if ( checkTable[z][r][c] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][r][c] = 0;
                                        --checkRemainderTable[r][c];
                                        ++changes;
           printf("Zapped regC=%d at [%d][%d]- in NakQuadReg...\t", (z + 1), r, c);   // debug purposes
                                     } //end if cT... ******
                              }  // end if xLoc... **********
                   } // ends for a = ...... **********
                
                  if ( changes )
                      return;
               
               }  // ends tttt... ************************ 
                
              } // ends ttt... ************
         
              
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*        // debug purposes ******************************************
         printf("E  reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
         printf("regCount=%d, uCount=%d, cand=%d, ", regCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d,%d.\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2], \
                                           uniqueCandTable[3]);
 */        // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             

