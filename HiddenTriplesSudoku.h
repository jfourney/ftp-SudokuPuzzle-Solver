// Hidden Triples Processing for Sudoku. ************************

/*
void hiddenTriplesRow (void);
void hiddenTriplesColumn (void);
void hiddenTriplesRegion (void);
*/

//hiddenTriplesRow Function ***********************************************************
void hiddenTriplesRow (void)
{
     int x, y, z, t, tt, ttt = 0, xx, u, uu, loc, eCount, uCount;
     int sumTable[9], xCandTable[9], xLocTable[9][3], uniqueLocTable[3];
     //NOTE, I SHOULD CHANGE xCandTable TO xCandTable. ************
     for ( y = 0; y < 9; ++y )
     {
         //Initialize sumTable. *********************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-up sumTable, and count qualified candidates for x-tables. **************
         // to be qualified- at least 3 candidates, that only occur 2-3 times in row. (2-1's,3-4's,2-8's). ***
         //sumTable counts the number of times each candidate appears in the row. *********************
         
         eCount = 0;
         
         for ( z = 0; z < 9; ++z )
         {
             for ( x = 0; x < 9; ++x )
                 if ( checkTable[z][y][x] > 0 )
                    if ( nDR[y][x] == 0 )
                       if ( nTR[y][x] == 0 )
                          ++sumTable[z];  // ends for x = ... ********* 
                          
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 4 )
                   ++eCount;
         }  // ends for z = ..... ***********************
         
         // Eliminate eCount < 3, because you need 3 seperate candidates, 2-3 times each. ********
         if ( eCount < 3 )
            continue;   // next y. ********************
            
         // Initialize x-tables. ********************************
         for ( x = 0; x < 9; ++x )
         {
             xCandTable[x] = 0;
             for ( xx = 0; xx < 3; ++xx )
                 xLocTable[x][xx] = 9;  //must initialize to 9, 9 is unique from eligible locations****
         }  // ends for x = ......... ******************************
         
         //Set-Up x-tables. **********************************************
         
         //xCandTable set-up.
         uCount = 0;
         
         for ( z = 0; uCount < eCount; ++z )
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 4 )
                {
                     xCandTable[uCount] = (z + 1);
                     ++uCount;
                }
         // ends for z = .... xCandTable is set up. ******************
         
         //xLocTable set-up. **********************
         u = 0;
         
         for ( z = 0; u < eCount; ++z )
             if ( xCandTable[u] == (z + 1) )
             {
                  uu = 0;
                  for ( x = 0; uu < sumTable[z]; ++x )
                  {
                      if ( checkTable[z][y][x] > 0 )
                         if ( nDR[y][x] == 0 )
                            if ( nTR[y][x] == 0 )
                            {
                                 xLocTable[u][uu] = x;
                                 ++uu;
                            }
                  }  //ends for x = ..... ****************
                  
                  ++u;
             }  // ends if xCandT...**********
         //ends for z... x-tables are set up. *************************
         
                    
            
     /*     //for debug purposes, print x-tables for each row........
          for ( x = 0; x < eCount; ++x )
          {
              printf("Row#%d,", y );
              printf("xCand[%d]=%d,", x, xCandTable[x]);
              printf("xLoc[%d]=%d,%d,%d\n", x, xLocTable[x][0], xLocTable[x][1], xLocTable[x][2] );
          }     //  for debug purposes only  *******************
     */       
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE X-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, and the X-tables (which get zeroed out, when not eligible for processing),
         // to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (eCount - 2); ++t )
         {
             //check to see if x-table element t, has been zeroed out. ***********************
             if ( xCandTable[t] == 0 )
                continue;
             
             //Initialize uniqueLocTable to nine's.*******************
             for ( u = 0; u < 3; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements from element t, into uniqueLocTable. *****************
             for ( u = 0; u < (sumTable[(xCandTable[t] - 1)]); ++u )
                 uniqueLocTable[u] = xLocTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (eCount - 1); ++tt )
             {
                 //check to see if element tt zeroed out of x-table
                 if ( xCandTable[tt] == 0 )
                    continue;                     // next tt. **********
                    
                 //if uCount < 3, put unique location into uniqueLocTable, 
                                  
                 uCount = sumTable[(xCandTable[t] - 1)];
                 
                 if ( uCount < 3 )
                    uniqueLocTable[2] = 9;
                    
                 for ( u = 0; u < (sumTable[(xCandTable[tt] - 1)]); ++u )
                 {
                     loc = xLocTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue;  // next uu. *******
                         else
                         {
                             loc = 9;
                             break; // next u. *****
                         }  // end for ( uu =... ********
                         
                     if ( loc == 9 )
                        continue;  // next u ... *********
                        
                     // have a unique location. *************
                     ++uCount;
                     
                     if ( uCount == 3 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueLocTable[2] = loc;
                          continue;  // next u.. ********
                     }
                     
                     // Over the limit- doesn't qualify for link table.. *****************
                     break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 3 )
                 {
     /*               // debug purposes ******************************************
                    printf("2F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                    printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */               // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
     /*            // debug purposes ******************************************
                 printf("2S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                 printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */            // debug purposes ******************************************************
         

            
                 //Begin search for possible 3rd element of linkedTable. **********************
                 for ( ttt = (tt + 1); ttt < eCount; ++ttt )
                 {
                     //check to see if element zeroed out of x-table. ********************
                     if ( xCandTable[ttt] == 0 )
                     continue;    // next ttt *****************
                
                     //check to make sure that no locations in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
             
                     for ( u = 0; u < (sumTable[(xCandTable[ttt] - 1)]); ++u )
                     {
                         loc = xLocTable[ttt][u];
                 
                         for ( uu = 0; uu < 3; ++uu )
                             if ( uniqueLocTable[uu] != loc )
                                continue;  // next uu. *******
                             else
                             {
                                 loc = 9;
                                 break;  //next . *******
                             } // ends for ( uu = ... ***********
                         
                         if ( loc == 9 )
                            continue;  // next u ... *******************
                        
                         // Over the limit.... *********
                         ++uCount;
                         break;
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 3 )
                {
     /*              // debug purposes ******************************************
                   printf("3F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                   printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                   printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */              // debug purposes ******************************************************
                   continue;    //unable to link 3rd element to 2nd. Need to try a different second element,
                   // next next tt. **********
                }    
              
         
                  
                // a hiddenTriplesRow has been achieved. Process the hTR. ***************
         
        /*        // debug purposes ******************************************
                printf("3S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
        */        // debug purposes ******************************************************
         
                //Put all 3 elements t, tt, and ttt int the nTR table. ****************
                nTR[y][(uniqueLocTable[0])] = 1;
                nTR[y][(uniqueLocTable[1])] = 1;
                nTR[y][(uniqueLocTable[2])] = 1;
         
                //Zap all other candidates, in these 3 squares. *********************
                // REMEMBER, xCandTable[t] = 1st candidate, [tt]= 2nd candidate, [ttt]= 3rd candidate.
                
                for ( u = 0; u < 3; ++u )
                {
                    x = uniqueLocTable[u];
                    
                    for ( z = 0; z < 9; ++z )
                        if ( z != (xCandTable[t] - 1) )
                           if ( z != (xCandTable[tt] - 1) )
                              if ( z != (xCandTable[ttt] - 1) )
                                     if ( checkTable[z][y][x] > 0 )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
            printf("Zapped xC=%d at [%d][%d]- in HidTripRow...\t", (z + 1), y, x);   // debug purposes                    
                                     } //end if cT... ******
                }  // end for u = .... **********
         
                //Zero out all three x-table elements, of those in the linkedTable (t, tt, and ttt). *********
                // don't subtract from eCount......... Then, continue back  to for ( t .. ************ 
         
                //element t. ****************
                xCandTable[t] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    xLocTable[t][xx] = 9;

                //element tt. ****************
                xCandTable[tt] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    xLocTable[tt][xx] = 9;
             
                //element ttt. ****************
                xCandTable[ttt] = 0;
                for ( xx = 0; xx < 3; ++xx )
                    xLocTable[ttt][xx] = 9;
         
                break;
         
                //ALL DONE PROCESSING THE NTR.
                //START WITH A NEW T. *********
              } // ends ttt... ************
         
              if ( uCount == 3 )
                 break;
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
    /*           // debug purposes ******************************************
         printf("E  y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
         printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
         printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
    */     // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             

         
         
//hiddenTriplesColumn Function ***********************************************************
void hiddenTriplesColumn (void)
{
     int x, y, z, t, tt, ttt = 0, yy, u, uu, loc, eCount, uCount;
     int sumTable[9], yCandTable[9], yLocTable[9][3], uniqueLocTable[3];
     //SHOULD CHANGE THE NAME OF yCandTable to yCandTable. ********************
      
     for ( x = 0; x < 9; ++x )
     {
         //Initialize sumTable. *********************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-up sumTable, and count qualified candidates for y-tables. **************
         // to be qualified- at least 3 candidates, that only occur 2-3 times in row. (2-1's,3-4's,2-8's). ***
         eCount = 0;
         
         for ( z = 0; z < 9; ++z )
         {
             for ( y = 0; y < 9; ++y )
                 if ( checkTable[z][y][x] > 0 )
                    if ( nDC[y][x] == 0 )
                       if ( nTC[y][x] == 0 )
                          ++sumTable[z];  // ends for y = ... ********* 
                          
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 4 )
                   ++eCount;
         }  // ends for z = ..... ***********************
         
         // Eliminate eCount < 3, because you need 3 seperate candidates, 2-3 times each. ********
         if ( eCount < 3 )
            continue;   // next y. ********************
            
         // Initialize y-tables. ********************************
         for ( y = 0; y < 9; ++y )
         {
             yCandTable[y] = 0;
             for ( yy = 0; yy < 3; ++yy )
                 yLocTable[y][yy] = 9;  //must initialize to 9, 9 is unique from eligible locations. ****
         }  // ends for y = ......... ******************************
         
         //Set-Up y-tables. **********************************************
         
         //yCandTable set-up.
         uCount = 0;
         
         for ( z = 0; uCount < eCount; ++z )
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 4 )
                {
                     yCandTable[uCount] = (z + 1);
                     ++uCount;
                }
         // ends for z = .... yCandTable is set up. ******************
         
         //yLocTable set-up. **********************
         u = 0;
         
         for ( z = 0; u < eCount; ++z )
             if ( yCandTable[u] == (z + 1) )
             {
                  uu = 0;
                  for ( y = 0; uu < sumTable[z]; ++y )
                  {
                      if ( checkTable[z][y][x] > 0 )
                         if ( nDC[y][x] == 0 )
                            if ( nTC[y][x] == 0 )
                            {
                                 yLocTable[u][uu] = y;
                                 ++uu;
                            }
                  }  //ends for y = ..... ****************
                  
                  ++u;
             }  // ends if yCandT...**********
         //ends for z... y-tables are set up. *************************
         
                    
            
   /*       //for debug purposes, print y-tables for each column........
          for ( y = 0; y < eCount; ++y )
          {
              printf("Col#%d,", x );
              printf("yCand[%d]=%d,", y, yCandTable[y]);
              printf("yLoc[%d]=%d,%d,%d\n", y, yLocTable[y][0], yLocTable[y][1], yLocTable[y][2] );
          }     //  for debug purposes only  *******************
   */         
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE Y-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, and the Y-tables (which get zeroed out, when not eligible for processing),
         // to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (eCount - 2); ++t )
         {
             //check to see if y-table element t, has been zeroed out. ***********************
             if ( yCandTable[t] == 0 )
                continue;
             
             //Initialize uniqueLocTable to nine's.*******************
             for ( u = 0; u < 3; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements from element t, into uniqueLocTable. *****************
             for ( u = 0; u < (sumTable[(yCandTable[t] - 1)]); ++u )
                 uniqueLocTable[u] = yLocTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (eCount - 1); ++tt )
             {
                 //check to see if element tt zeroed out of y-table
                 if ( yCandTable[tt] == 0 )
                    continue;                     // next tt. **********
                    
                 //if uCount < 3, put unique location into uniqueLocTable, 
                                  
                 uCount = sumTable[(yCandTable[t] - 1)];
                 
                 if ( uCount < 3 )
                    uniqueLocTable[2] = 9;
                    
                 for ( u = 0; u < (sumTable[(yCandTable[tt] - 1)]); ++u )
                 {
                     loc = yLocTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue;  // next uu. *******
                         else
                         {
                             loc = 9;
                             break; // next u. *****
                         }  // end for ( uu =... ********
                         
                     if ( loc == 9 )
                        continue;  // next u ... *********
                        
                     // have a unique location. *************
                     ++uCount;
                     
                     if ( uCount == 3 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueLocTable[2] = loc;
                          continue;  // next u.. ********
                     }
                     
                     // Over the limit- doesn't qualify for link table.. *****************
                     break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 3 )
                 {
   /*                 // debug purposes ******************************************
                    printf("2F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                    printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
   */                 // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
   /*              // debug purposes ******************************************
                 printf("2S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                 printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
   */              // debug purposes ******************************************************
         

            
                 //Begin search for possible 3rd element of linkedTable. **********************
                 for ( ttt = (tt + 1); ttt < eCount; ++ttt )
                 {
                     //check to see if element zeroed out of y-table. ********************
                     if ( yCandTable[ttt] == 0 )
                     continue;    // next ttt *****************
                
                     //check to make sure that no locations in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
             
                     for ( u = 0; u < (sumTable[(yCandTable[ttt] - 1)]); ++u )
                     {
                         loc = yLocTable[ttt][u];
                 
                         for ( uu = 0; uu < 3; ++uu )
                             if ( uniqueLocTable[uu] != loc )
                                continue;  // next uu. *******
                             else
                             {
                                 loc = 9;
                                 break;  //next . *******
                             } // ends for ( uu = ... ***********
                         
                         if ( loc == 9 )
                            continue;  // next u ... *******************
                        
                         // Over the limit.... *********
                         ++uCount;
                         break;
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 3 )
                {
   /*                // debug purposes ******************************************
                   printf("3F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                   printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                   printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
   */                // debug purposes ******************************************************
                   continue;    //unable to link 3rd element to 2nd. Need to try a different second element,
                   // next next tt. **********
                }    
              
         
                  
                // a hiddenTriplesColumn has been achieved. Process the hTC. ***************
         
   /*             // debug purposes ******************************************
                printf("3S x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
   */             // debug purposes ******************************************************
         
                //Put all 3 elements t, tt, and ttt int the nTC table. ****************
                nTC[(uniqueLocTable[0])][x] = 1;
                nTC[(uniqueLocTable[1])][x] = 1;
                nTC[(uniqueLocTable[2])][x] = 1;
         
                //Zap all other candidates, in these 3 squares. *********************
                // REMEMBER, yCandTable[t] = 1st candidate, [tt]= 2nd candidate, [ttt]= 3rd candidate.
                
                for ( u = 0; u < 3; ++u )
                {
                    y = uniqueLocTable[u];
                    
                    for ( z = 0; z < 9; ++z )
                        if ( z != (yCandTable[t] - 1) )
                           if ( z != (yCandTable[tt] - 1) )
                              if ( z != (yCandTable[ttt] - 1) )
                                     if ( checkTable[z][y][x] > 0 )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
                printf("Zapped xC=%d at [%d][%d]- in HidTripsCol...\t", (z + 1), y, x);   // debug purposes   
                                     } //end if cT... ******
                }  // end for u = .... **********
         
                //Zero out all three y-table elements, of those in te linkedTable (t, tt, and ttt). *********
                // don't subtract from eCount......... Then, continue back  to for ( t .. ************ 
         
                //element t. ****************
                yCandTable[t] = 0;
                for ( yy = 0; yy < 3; ++yy )
                    yLocTable[t][yy] = 9;

                //element tt. ****************
                yCandTable[tt] = 0;
                for ( yy = 0; yy < 3; ++yy )
                    yLocTable[tt][yy] = 9;
             
                //element ttt. ****************
                yCandTable[ttt] = 0;
                for ( yy = 0; yy < 3; ++yy )
                    yLocTable[ttt][yy] = 9;
         
                break;
         
                //ALL DONE PROCESSING THE NTC.
                //START WITH A NEW T. *********
              } // ends ttt... ************
         
              if ( uCount == 3 )
                 break;
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
   /*            // debug purposes ******************************************
         printf("E  x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
         printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
         printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
   */      // debug purposes ******************************************************
         
         
   } //end for ( x = ... *********   
   return;
}
             

         
//hiddenTriplesRegion Function ***********************************************************
void hiddenTriplesRegion (void)
{
     int x, y, z, t, tt, ttt = 0, region, a, r, c, aa, u, uu, loc, eCount, uCount;
     int sumTable[9], regCandTable[9], regLocTable[9][3], uniqueLocTable[3];
     // SHOULD HAVE NAMED regCandTable, regCandTable. *********************
     
     for ( region = 0; region < 9; ++region )
     {
         //Initialize sumTable. *********************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-up sumTable, and count qualified candidates for x-tables. **************
         // to be qualified- at least 3 candidates, that only occur 2-3 times in row. (2-1's,3-4's,2-8's). ***
         eCount = 0;
         
         for ( z = 0; z < 9; ++z )
         {
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 
                 if ( checkTable[z][r][c] > 0 )
                    if ( nDReg[r][c] == 0 )
                       if ( nTReg[r][c] == 0 )
                          ++sumTable[z];  // ends for x = ... ********* 
             } //ends for a = ... *******
                        
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 4 )
                   ++eCount;
         }  // ends for z = ..... ***********************
         
         // Eliminate eCount < 3, because you need 3 seperate candidates, 2-3 times each. ********
         if ( eCount < 3 )
            continue;   // next y. ********************
            
         // Initialize reg-tables. ********************************
         for ( a = 0; a < 9; ++a )
         {
             regCandTable[a] = 0;
             for ( aa = 0; aa < 3; ++aa )
                 regLocTable[a][aa] = 9;  //must initialize to 9, 9 is unique from eligible locations. ****
         }  // ends for a = ......... ******************************
         
         //Set-Up reg-tables. **********************************************
         
         //regCandTable set-up.
         uCount = 0;
         
         for ( z = 0; uCount < eCount; ++z )
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 4 )
                {
                     regCandTable[uCount] = (z + 1);
                     ++uCount;
                }
         // ends for z = .... regCandTable is set up. ******************
         
         //regLocTable set-up. **********************
         u = 0;
         
         for ( z = 0; u < eCount; ++z )
             if ( regCandTable[u] == (z + 1) )
             {
                  uu = 0;
                  for ( a = 0; uu < sumTable[z]; ++a )
                  {
                      r = regionalDispatchTable[region][a].row;
                      c = regionalDispatchTable[region][a].column;
                      if ( checkTable[z][r][c] > 0 )
                         if ( nDReg[r][c] == 0 )
                            if ( nTReg[r][c] == 0 )
                            {
                                 regLocTable[u][uu] = a;
                                 ++uu;
                            }
                  }  //ends for a = ..... ****************
                  
                  ++u;
             }  // ends if regCandT...**********
         //ends for z... reg-tables are set up. *************************
         
                    
            
   /*       //for debug purposes, print reg-tables for each region........
          for ( a = 0; a < eCount; ++a )
          {
              printf("Reg#%d,", region );
              printf("regCand[%d]=%d,", a, regCandTable[a]);
              printf("regLoc[%d]=%d,%d,%d\n", a, regLocTable[a][0], regLocTable[a][1], regLocTable[a][2] );
          }     //  for debug purposes only  *******************
     */       
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE REG-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, and the Reg-tables (which get zeroed out, when not eligible for processing),
         // to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (eCount - 2); ++t )
         {
             //check to see if x-table element t, has been zeroed out. ***********************
             if ( regCandTable[t] == 0 )
                continue;
             
             //Initialize uniqueLocTable to nine's.*******************
             for ( u = 0; u < 3; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements from element t, into uniqueLocTable. *****************
             for ( u = 0; u < (sumTable[(regCandTable[t] - 1)]); ++u )
                 uniqueLocTable[u] = regLocTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (eCount - 1); ++tt )
             {
                 //check to see if element tt zeroed out of reg-table
                 if ( regCandTable[tt] == 0 )
                    continue;                     // next tt. **********
                    
                 //if uCount < 3, put unique location into uniqueLocTable, 
                                  
                 uCount = sumTable[(regCandTable[t] - 1)];
                 
                 if ( uCount < 3 )
                    uniqueLocTable[2] = 9;
                    
                 for ( u = 0; u < (sumTable[(regCandTable[tt] - 1)]); ++u )
                 {
                     loc = regLocTable[tt][u];
                     
                     for ( uu = 0; uu < uCount; ++uu )
                         if ( loc != uniqueLocTable[uu] )
                            continue;  // next uu. *******
                         else
                         {
                             loc = 9;
                             break; // next u. *****
                         }  // end for ( uu =... ********
                         
                     if ( loc == 9 )
                        continue;  // next u ... *********
                        
                     // have a unique location. *************
                     ++uCount;
                     
                     if ( uCount == 3 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueLocTable[2] = loc;
                          continue;  // next u.. ********
                     }
                     
                     // Over the limit- doesn't qualify for link table.. *****************
                     break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 3 )
                 {
     /*               // debug purposes ******************************************
                    printf("2F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                    printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */               // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     //next tt. **************
                 }   //ends if uCount.. **********            
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
     /*            // debug purposes ******************************************
                 printf("2S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                 printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */            // debug purposes ******************************************************
         

            
                 //Begin search for possible 3rd element of linkedTable. **********************
                 for ( ttt = (tt + 1); ttt < eCount; ++ttt )
                 {
                     //check to see if element zeroed out of reg-table. ********************
                     if ( regCandTable[ttt] == 0 )
                     continue;    // next ttt *****************
                
                     //check to make sure that no locations in prospective element are unique;*****
                     //  otherwise continue to next ttt. ****************************************
             
                     for ( u = 0; u < (sumTable[(regCandTable[ttt] - 1)]); ++u )
                     {
                         loc = regLocTable[ttt][u];
                 
                         for ( uu = 0; uu < 3; ++uu )
                             if ( uniqueLocTable[uu] != loc )
                                continue;  // next uu. *******
                             else
                             {
                                 loc = 9;
                                 break;  //next . *******
                             } // ends for ( uu = ... ***********
                         
                         if ( loc == 9 )
                            continue;  // next u ... *******************
                        
                         // Over the limit.... *********
                         ++uCount;
                         break;
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 3 )
                {
     /*              // debug purposes ******************************************
                   printf("3F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                   printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                   printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */              // debug purposes ******************************************************
                   continue;    //unable to link 3rd element to 2nd. Need to try a different second element,
                   // next next tt. **********
                }    
              
         
                  
                // a hiddenTriplesRegion has been achieved. Process the hTReg. ***************
         
     /*           // debug purposes ******************************************
                printf("3S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
                printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
     */           // debug purposes ******************************************************
         
                //Put all 3 elements t, tt, and ttt int the nTC table. ****************
                
                a = uniqueLocTable[0];
                r = regionalDispatchTable[region][a].row;
                c = regionalDispatchTable[region][a].column;
                nQReg[r][c] = 1;
                
                a = uniqueLocTable[1];
                r = regionalDispatchTable[region][a].row;
                c = regionalDispatchTable[region][a].column;
                nQReg[r][c] = 1;
                
                a = uniqueLocTable[2];
                r = regionalDispatchTable[region][a].row;
                c = regionalDispatchTable[region][a].column;
                nQReg[r][c] = 1;
                   
                //Zap all other candidates, in these 3 squares. *********************
                // REMEMBER, regCandTable[t] = 1st candidate, [tt]= 2nd candidate, [ttt]= 3rd candidate.
                
                for ( u = 0; u < 3; ++u )
                {
                    a = uniqueLocTable[u];
                    r = regionalDispatchTable[region][a].row;
                    c = regionalDispatchTable[region][a].column;
                    
                    for ( z = 0; z < 9; ++z )
                        if ( z != (regCandTable[t] - 1) )
                           if ( z != (regCandTable[tt] - 1) )
                              if ( z != (regCandTable[ttt] - 1) )
                                     if ( checkTable[z][r][c] > 0 )
                                     {
                                        checkTable[z][r][c] = 0;
                                        --checkRemainderTable[r][c];
                                        ++changes;
         printf("Zapped regC=%d at [%d][%d]- in HidTripsReg...\t", (z + 1), r, c);   // debug purposes       
                                     } //end if cT... ******
                }  // end for u = .... **********
         
                //Zero out all three reg-table elements, of those in te linkedTable (t, tt, and ttt). *********
                // don't subtract from eCount......... Then, continue back  to for ( t .. ************ 
         
                //element t. ****************
                regCandTable[t] = 0;
                for ( aa = 0; aa < 3; ++aa )
                    regLocTable[t][aa] = 9;

                //element tt. ****************
                regCandTable[tt] = 0;
                for ( aa = 0; aa < 3; ++aa )
                    regLocTable[tt][aa] = 9;
             
                //element ttt. ****************
                regCandTable[ttt] = 0;
                for ( aa = 0; aa < 3; ++aa )
                    regLocTable[ttt][aa] = 9;
         
                break;
         
                //ALL DONE PROCESSING THE NTReg.
                //START WITH A NEW T. *********
              } // ends ttt... ************
         
              if ( uCount == 3 )
                 break;
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
   /*            // debug purposes ******************************************
         printf("E  reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
         printf("eCount=%d, uCount=%d, loc=%d, ", eCount, uCount, loc);
         printf("uniqueLoc=%d,%d,%d;;\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2]);
   */      // debug purposes ******************************************************
         
         
   } //end for ( region = ... *********   
   return;
}
             

         
