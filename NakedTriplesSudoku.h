// Naked Triples Processing for Sudoku. *******************

/*
// Function Declarations **************************************************
void nakedTriplesRow (void);
void nakedTriplesColumn (void);
void nakedTriplesRegion (void);
*/

//nakedTriplesRow Function ******************************************************
void nakedTriplesRow (void)
{
     int x, y, z, xx, u, uu, t, tt, ttt, cand, uCount, eCount;
     int xRemTable[9], xCandTable[9][3], xLocTable[9], uniqueCandTable[3];
     
     for ( y = 0; y < 9; ++y )
     {
         //Initialize X-tables. *******************************************
         for ( x = 0; x < 9; ++x )
         {
             xRemTable[x] = 0;
             xLocTable[x] = 0;
             
             for ( xx = 0; xx < 3; ++xx )
                 xCandTable[x][xx] = 0;
         }
         
         //Fill X-tables with qualifying elements; x-locations that have a checkRemainder
         //  of either 2 or 3. Also, don't include nDR's or nTR's for qualification.
         
         eCount = 0;
         
         for ( x = 0; x < 9; ++x )
             if ( nDR[y][x] == 0 )
                if ( nTR[y][x] == 0 )
                   if ( checkRemainderTable [y][x] > 1 )
                      if ( checkRemainderTable[y][x] < 4 )
                      {
                           //This is a qualified element for the X-tables.***************
                           xRemTable[eCount] = checkRemainderTable[y][x];
                           xLocTable[eCount] = x;
                           
                           //Put qualified candidates into the X-table.
                           uCount = 0;
                           
                           for ( z = 0; uCount < checkRemainderTable[y][x]; ++z )
                               if ( checkTable[z][y][x] > 0 )
                               {
                                    xCandTable[eCount][uCount] = checkTable[z][y][x];
                                    ++uCount;
                               }
                               
                               ++eCount;
                      }
          

          
                    
         //X-tables are set-up. *****************************************************

         //Exclude all nakedTripleRow Processing, if X-table < 3 elements. goto next row (y). ****
         if ( eCount < 3 )
            continue;
            
            
/*          //for debug purposes, print x-tables for each row........
          for ( x = 0; x < eCount; ++x )
          {
              printf("Row#%d,", y );
              printf("xRem[%d]=%d,", x, xRemTable[x]);
              printf("xLoc[%d]=%d,", x, xLocTable[x]);
              printf("xCand[%d]=%d,%d,%d\n", x, xCandTable[x][0], xCandTable[x][1], xCandTable[x][2] );
          }     //  for debug purposes only  *******************
  */          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE X-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, and the X-tables (which get zeroed out, when not eligible for processing),
         // to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (eCount - 2); ++t )
         {
             //check to see if x-table element t, has been zeroed out. ***********************
             if ( xRemTable[t] == 0 )
                continue;
             
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 3; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (xRemTable[t]); ++u )
                 uniqueCandTable[u] = xCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (eCount - 1); ++tt )
             {
                 //check to see if element tt zeroed out of x-table
                 if ( xRemTable[tt] == 0 )
                    continue;                     // next tt. **********
                    
                 //if uCount < 3, put unique candidate into uniqueCandTable, 
                                  
                 uCount = xRemTable[t];
                 
                 if ( uCount < 3 )
                    uniqueCandTable[2] = 0;
                    
                 for ( u = 0; u < (xRemTable[tt]); ++u )
                 {
                     cand = xCandTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have one unique candidate. *************
                     ++uCount;
                     
                     if ( uCount == 3 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[2] = cand;
                          continue;
                     }
                     
                     // Over the limit- doesn't qualify for link table.. *****************
                     break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 3 )
                 {
         /*           // debug purposes ******************************************
                    printf("2F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                    printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
         */           // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
           /*      // debug purposes ******************************************
                 printf("2S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                 printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
           */      // debug purposes ******************************************************
         

            
                 //Begin search for possible 3rd element of linkedTable. **********************
                 for ( ttt = (tt + 1); ttt < eCount; ++ttt )
                 {
                     //check to se if element zeroed out of x-table. ********************
                     if ( xRemTable[ttt] == 0 )
                     continue;    // next ttt *****************
                
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     uCount = 3;
                     
                     for ( u = 0; u < xRemTable[ttt]; ++u )
                     {
                         cand = xCandTable[ttt][u];
                 
                         for ( uu = 0; uu < 3; ++uu )
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
             
             
         
                if (uCount > 3 )
                {
           /*        // debug purposes ******************************************
                   printf("3F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                   printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
           */        // debug purposes ******************************************************
                   continue;    //unable to link 3rd element to 2nd. Need to try a different second element,
                }    
              
         
                  
           /*     // a nakedTripleRow has been achieved. Process the nTR. ***************
         
                // debug purposes ******************************************
                printf("3S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
           */     // debug purposes ******************************************************
         
                //Put all 3 elements t, tt, and ttt into the nTR table. ****************
                nTR[y][(xLocTable[t])] = 1;
                nTR[y][(xLocTable[tt])] = 1;
                nTR[y][(xLocTable[ttt])] = 1;
         
                //Zap all other occurances of these 3 unique candidates, from the other 6 cells in the row. ****
                for ( z = 0; z < 9; ++z )
                    for ( x = 0; x < 9; ++x )
                        if ( x != (xLocTable[t]) )
                           if ( x != (xLocTable[tt]) )
                              if ( x != (xLocTable[ttt]) )
                              {
                                 for ( u = 0; u < 3; ++u )
                                     if ( checkTable[z][y][x] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
              printf("Zapped xC=%d at [%d][%d]- in NakTripsRow...\t", (z + 1), y, x);   // debug purposes 
                                     } //end if cT... ******
                              }  // end if xLoc... **********
         
                //Zero out all three x-table elements, of those in the linkedTable (t, tt, and ttt). *********
                // don't subtract from eCount......... Then, continue back  to for ( t .. ************ 
         
                //element t. ****************
                xRemTable[t] = 0;
                xLocTable[t] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    xCandTable[t][xx] = 0;

                //element tt. ****************
                xRemTable[tt] = 0;
                xLocTable[tt] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    xCandTable[tt][xx] = 0;
             
                //element ttt. ****************
                xRemTable[ttt] = 0;
                xLocTable[ttt] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    xCandTable[ttt][xx] = 0;
         
                break;
         
                //ALL DONE PROCESSING THE NTR.
                //START WITH A NEW T. *********
              } // ends ttt... ************
         
              if ( uCount == 3 )
                 break;
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
      /*         // debug purposes ******************************************
         printf("E  y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
         printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
      */   // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             

//nakedTriplesColumn Function ******************************************************
void nakedTriplesColumn (void)
{
     int x, y, z, yy, u, uu, t, tt, ttt, cand, uCount, eCount;
     int yRemTable[9], yCandTable[9][3], yLocTable[9], uniqueCandTable[3];
          
     for ( x = 0; x < 9; ++x )
     {
         //Initialize Y-tables. *******************************************
         for ( y = 0; y < 9; ++y )
         {
             yRemTable[y] = 0;
             yLocTable[y] = 0;
             
             for ( yy = 0; yy < 3; ++yy )
                 yCandTable[y][yy] = 0;
         }
         
         //Fill Y-tables with qualifying elements; y-locations that have a checkRemainder
         //  of either 2 or 3. Also, don't include nDC's or nTC's for quqlification.
         
         eCount = 0;
         
         for ( y = 0; y < 9; ++y )
             if ( nDC[y][x] == 0 )
                if ( nTC[y][x] == 0 )
                   if ( checkRemainderTable [y][x] > 1 )
                      if ( checkRemainderTable[y][x] < 4 )
                      {
                           //This is a qualified element for the Y-tables.***************
                           yRemTable[eCount] = checkRemainderTable[y][x];
                           yLocTable[eCount] = y;
                           
                           //Put qualified candidates into the Y-table.
                           uCount = 0;
                           
                           for ( z = 0; uCount < checkRemainderTable[y][x]; ++z )
                               if ( checkTable[z][y][x] > 0 )
                               {
                                    yCandTable[eCount][uCount] = checkTable[z][y][x];
                                    ++uCount;
                               }
                               
                               ++eCount;
                      }
          

          
                    
         //Y-tables are set-up. *****************************************************

         //Exclude all nakedTripleColumn Processing, if Y-table < 3 elements. goto next column (x). ****
         if ( eCount < 3 )
            continue;
            
            
  /*        //for debug purposes, print y-tables for each column........
          for ( y = 0; y < eCount; ++y )
          {
              printf("Col#%d,", x );
              printf("yRem[%d]=%d,", y, yRemTable[y]);
              printf("yLoc[%d]=%d,", y, yLocTable[y]);
              printf("yCand[%d]=%d,%d,%d\n", y, yCandTable[y][0], yCandTable[y][1], yCandTable[y][2] );
          }     //  for debug purposes only  *******************
    */        
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE Y-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, and the Y-tables (which get zeroed out, when not eligible for processing),
         // to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (eCount - 2); ++t )
         {
             //check to see if x-table element t, has been zeroed out. ***********************
             if ( yRemTable[t] == 0 )
                continue;
             
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 3; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (yRemTable[t]); ++u )
                 uniqueCandTable[u] = yCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (eCount - 1); ++tt )
             {
                 //check to see if element tt zeroed out of y-table
                 if ( yRemTable[tt] == 0 )
                    continue;                     // next tt. **********
                    
                 //if uCount < 3, put unique candidate into uniqueCandTable, 
                                  
                 uCount = yRemTable[t];
                 
                 if ( uCount < 3 )
                    uniqueCandTable[2] = 0;
                    
                 for ( u = 0; u < (yRemTable[tt]); ++u )
                 {
                     cand = yCandTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have one unique candidate. *************
                     ++uCount;
                     
                     if ( uCount == 3 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[2] = cand;
                          continue;
                     }
                     
                     // Over the limit- doesn't qualify for link table.. *****************
                     break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 3 )
                 {
          /*          // debug purposes ******************************************
                    printf("2F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                    printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
          */          // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
       /*          // debug purposes ******************************************
                 printf("2S x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                 printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
       */          // debug purposes ******************************************************
         

            
                 //Begin search for possible 3rd element of linkedTable. **********************
                 for ( ttt = (tt + 1); ttt < eCount; ++ttt )
                 {
                     //check to see if element zeroed out of x-table. ********************
                     if ( yRemTable[ttt] == 0 )
                     continue;    // next ttt *****************
                
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     
                     uCount = 3;
             
                     for ( u = 0; u < yRemTable[ttt]; ++u )
                     {
                         cand = yCandTable[ttt][u];
                 
                         for ( uu = 0; uu < 3; ++uu )
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
             
             
         
                if (uCount > 3 )
                {
      /*             // debug purposes ******************************************
                   printf("3F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                   printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
      */             // debug purposes ******************************************************
                   continue;    //unable to link 3rd element to 2nd. Need to try a different second element,
                }    
              
         
                  
                // a nakedTripleColumn has been achieved. Process the nTR. ***************
         
    /*            // debug purposes ******************************************
                printf("3S x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
    **/            // debug purposes ******************************************************
         
                //Put all 3 elements t, tt, and ttt into the nTC table. ****************
                nTC[(yLocTable[t])][x] = 1;
                nTC[(yLocTable[tt])][x] = 1;
                nTC[(yLocTable[ttt])][x] = 1;
         
                //Zap all other occurances of these 3 unique candidates, from the other 6 cells in the column. ****
                for ( z = 0; z < 9; ++z )
                    for ( y = 0; y < 9; ++y )
                        if ( y != (yLocTable[t]) )
                           if ( y != (yLocTable[tt]) )
                              if ( y != (yLocTable[ttt]) )
                              {
                                 for ( u = 0; u < 3; ++u )
                                     if ( checkTable[z][y][x] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
            printf("Zapped xC=%d at [%d][%d]- in NakTrips Col....\t", (z + 1), y, x);   // debug purposes 
                                     } //end if cT... ******
                              }  // end if yLoc... **********
         
                //Zero out all three y-table elements, of those in the linkedTable (t, tt, and ttt). *********
                // don't subtract from eCount......... Then, continue back  to for ( t .. ************ 
         
                //element t. ****************
                yRemTable[t] = 0;
                yLocTable[t] = 0;
                for ( yy = 0; yy < 3; ++yy )
                    yCandTable[t][yy] = 0;

                //element tt. ****************
                yRemTable[tt] = 0;
                yLocTable[tt] = 0;
                for ( yy = 0; yy < 3; ++yy )
                    yCandTable[tt][yy] = 0;
             
                //element ttt. ****************
                yRemTable[ttt] = 0;
                yLocTable[ttt] = 0;
                for ( yy = 0; yy < 3; ++yy )
                    yCandTable[ttt][yy] = 0;
         
                break;
         
                //ALL DONE PROCESSING THE NTC.
                //START WITH A NEW T. *********
              } // ends ttt... ************
         
              if ( uCount == 3 )
                 break;
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*         // debug purposes ******************************************
         printf("E  x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
         printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
         system("pause");
 */        // debug purposes ******************************************************
         
         
   } //end for ( x = ... *********   
   return;
}
             
             
//nakedTriplesRegion Function ******************************************************
void nakedTriplesRegion (void)
{
     int x, y, z, region, xx, a, r, c, u, uu, t, tt, ttt, cand, uCount, eCount;
     int regRemTable[9], regCandTable[9][3], regLocTable[9], uniqueCandTable[3];
     // NOTE: SHOULD HAVE NAMED regCandTable, regCandTable. ***********
     // ALSO, SHOULD HAVE NAMED uniqueCandTable, uniqueCandTable. *************
     for ( region = 0; region < 9; ++region )
     {
         //Initialize Reg-tables. *******************************************
         for ( a = 0; a < 9; ++a )
         {
             regRemTable[a] = 0;
             regLocTable[a] = 0;
             
             for ( xx = 0; xx < 3; ++xx )
                 regCandTable[a][xx] = 0;
         }
         
         //Fill Reg-tables with qualifying elements; a-locations that have a checkRemainder
         //  of either 2 or 3. Also, don't include nDReg's or nTReg's for qualification.
         
         eCount = 0;
         
         for ( a = 0; a < 9; ++a )
         {
             r = regionalDispatchTable[region][a].row;
             c = regionalDispatchTable[region][a].column;
             if ( nDReg[r][c] == 0 )
                if ( nTReg[r][c] == 0 )
                   if ( checkRemainderTable[r][c] > 1 )
                      if ( checkRemainderTable[r][c] < 4 )
                      {
                           //This is a qualified element for the Reg-tables.***************
                           regRemTable[eCount] = checkRemainderTable[r][c];
                           regLocTable[eCount] = a;
                           
                           //Put qualified candidates into the Reg-table.
                           uCount = 0;
                           
                           for ( z = 0; uCount < checkRemainderTable[r][c]; ++z )
                               if ( checkTable[z][r][c] > 0 )
                               {
                                    regCandTable[eCount][uCount] = checkTable[z][r][c];
                                    ++uCount;
                               }
                               
                               ++eCount;
                      }
         }  // end for a.... **************

          
                    
         //Reg-tables are set-up. *****************************************************

         //Exclude all nakedTripleReg Processing, if Reg-table < 3 elements. goto next region (region). ****
         if ( eCount < 3 )
            continue;
            
            
     /*     //for debug purposes, print reg-tables for the region........
          for ( xx = 0; xx < eCount; ++xx )
          {
              printf("Reg#%d,", region );
              printf("regRem[%d]=%d,", xx, regRemTable[xx]);
              printf("regLoc[%d]=%d,", xx, regLocTable[xx]);
              printf("regCand[%d]=%d,%d,%d\n", xx, regCandTable[xx][0], regCandTable[xx][1], regCandTable[xx][2] );
          }     //  for debug purposes only  *******************
       */     
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE Reg-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, and the X-tables (which get zeroed out, when not eligible for processing),
         // to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (eCount - 2); ++t )
         {
             //check to see if reg-table element t, has been zeroed out. ***********************
             if ( regRemTable[t] == 0 )
                continue;
             
             //Initialize uniqueCandTable to zeroes.*******************
             for ( u = 0; u < 3; ++u )
                 uniqueCandTable[u] = 0;
                 
             //Put elements from element t, into uniqueCandTable. *****************
             for ( u = 0; u < (regRemTable[t]); ++u )
                 uniqueCandTable[u] = regCandTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (eCount - 1); ++tt )
             {
                 //check to see if element tt zeroed out of x-table
                 if ( regRemTable[tt] == 0 )
                    continue;                     // next tt. **********
                    
                 //if uCount < 3, put unique candidate into uniqueCandTable, 
                                  
                 uCount = regRemTable[t];
                 
                 if ( uCount < 3 )
                    uniqueCandTable[2] = 0;
                    
                 for ( u = 0; u < (regRemTable[tt]); ++u )
                 {
                     cand = regCandTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( cand != uniqueCandTable[uu] )
                            continue;
                         else
                         {
                             cand = 0;
                             break;
                         }  // end for ( uu =... ********
                         
                     if ( cand == 0 )
                        continue;  // next u ... *********
                        
                     // have one unique candwer. *************
                     ++uCount;
                     
                     if ( uCount == 3 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueCandTable[2] = cand;
                          continue;
                     }
                     
                     // Over the limit- doesn't qualify for link table.. *****************
                     break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 3 )
                 {
       /*             // debug purposes ******************************************
                    printf("2F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                    printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                    printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
       */             // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
         /*        // debug purposes ******************************************
                 printf("2S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                 printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                 printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
         */        // debug purposes ******************************************************
         

            
                 //Begin search for possible 3rd element of linkedTable. **********************
                 for ( ttt = (tt + 1); ttt < eCount; ++ttt )
                 {
                     //check to see if element zeroed out of region-table. ********************
                     if ( regRemTable[ttt] == 0 )
                        continue;    // next ttt *****************
                
                     //check to make sure that no candidates in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
                     
                     uCount = 3;
             
                     for ( u = 0; u < regRemTable[ttt]; ++u )
                     {
                         cand = regCandTable[ttt][u];
                 
                         for ( uu = 0; uu < 3; ++uu )
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
             
             
         
                if (uCount > 3 )
                {
         /*          // debug purposes ******************************************
                   printf("3F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                   printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                   printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
         */          // debug purposes ******************************************************
                   continue;    //unable to link 3rd element to 2nd. Need to try a different second element,
                }    
              
         
                  
                // a nakedTripleRegion has been achieved. Process the nTReg. ***************
         
         /*       // debug purposes ******************************************
                printf("3S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
                printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
         */       // debug purposes ******************************************************
         
                //Put all 3 elements t, tt, and ttt into the nTReg table. ****************
                r = regionalDispatchTable[region][(regLocTable[t])].row;
                c = regionalDispatchTable[region][(regLocTable[t])].column;
                nTReg[r][c] = 1;
                r = regionalDispatchTable[region][(regLocTable[tt])].row;
                c = regionalDispatchTable[region][(regLocTable[tt])].column;
                nTReg[r][c] = 1;
                r = regionalDispatchTable[region][(regLocTable[ttt])].row;
                c = regionalDispatchTable[region][(regLocTable[ttt])].column;
                nTReg[r][c] = 1;
         
                //Zap all other occurances of these 3 unique candidates, from the other 6 cells in the region. ****
                for ( z = 0; z < 9; ++z )
                    for ( a = 0; a < 9; ++a )
                    {
                        r = regionalDispatchTable[region][a].row;
                        c = regionalDispatchTable[region][a].column;
                        if ( a != (regLocTable[t]) )
                           if ( a != (regLocTable[tt]) )
                              if ( a != (regLocTable[ttt]) )
                              {
                                 for ( u = 0; u < 3; ++u )
                                     if ( checkTable[z][r][c] == uniqueCandTable[u] )
                                     {
                                        checkTable[z][r][c] = 0;
                                        --checkRemainderTable[r][c];
                                        ++changes;
           printf("Zapped regC=%d at [%d][%d]- in NakTripsReg...\t", (z + 1), r, c);   // debug purposes 
                                     } //end if cT... ******
                              }  // end if xLoc... **********
                    }  // end for a... ******
                //Zero out all three reg-table elements, of those in the linkedTable (t, tt, and ttt). *********
                // don't subtract from eCount......... Then, continue back  to for ( t .. ************ 
         
                //element t. ****************
                regRemTable[t] = 0;
                regLocTable[t] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    regCandTable[t][xx] = 0;

                //element tt. ****************
                regRemTable[tt] = 0;
                regLocTable[tt] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    regCandTable[tt][xx] = 0;
             
                //element ttt. ****************
                regRemTable[ttt] = 0;
                regLocTable[ttt] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    regCandTable[ttt][xx] = 0;
         
                break;
         
                //ALL DONE PROCESSING THE NTReg.
                //START WITH A NEW T. *********
              } // ends ttt... ************
         
              if ( uCount == 3 )
                 break;
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
     /*          // debug purposes ******************************************
         printf("E  reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
         printf("eCount=%d, uCount=%d, cand=%d, ", eCount, uCount, cand);
         printf("uniqueCand=%d,%d,%d;;\n", uniqueCandTable[0], uniqueCandTable[1], uniqueCandTable[2]);
     */    // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}

