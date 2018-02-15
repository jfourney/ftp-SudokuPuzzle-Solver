// Hidden Quads Processing for Sudoku. ************************

/*
void hiddenQuadsRow (void);
void hiddenQuadsColumn (void);
void hiddenQuadsRegion (void);
*/

//hiddenQuadsRow Function ***********************************************************
void hiddenQuadsRow (void)
{
     int x, y, z, t, tt, ttt, tttt, xx, u, uu, loc, xCount, uCount, uniqueAdded[2];
     int sumTable[9], xCandTable[9], xLocTable[9][4], uniqueLocTable[4];
     
     for ( y = 0; y < 9; ++y )
     {
         //Initialize sumTable. *********************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-up sumTable, and count qualified candidates for x-tables. **************
         // to be qualified- at least 4 candidates, that only occur 2-4 times in row. (2-1's,3-4's,2-8's). ***
         //sumTable counts the number of times each candidate appears in the row. *********************
         
         xCount = 0;
         
         for ( z = 0; z < 9; ++z )
         {
             for ( x = 0; x < 9; ++x )
                 if ( checkTable[z][y][x] > 0 )
                    if ( nDR[y][x] == 0 )
                       if ( nTR[y][x] == 0 )
                         if (nQR[y][x] == 0 )
                          ++sumTable[z];  // ends for x = ... ********* 
                          
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 5 )
                   ++xCount;
         }  // ends for z = ..... ***********************
         
         // Eliminate xCount < 4, because you need 4 seperate candidates, 2-4 times each. ********
         if ( xCount < 4 )
            continue;   // next y. ********************
            
         // Initialize x-tables. ********************************
         for ( x = 0; x < 9; ++x )
         {
             xCandTable[x] = 0;
             for ( xx = 0; xx < 4; ++xx )
                 xLocTable[x][xx] = 9;  //must initialize to 9, 9 is unique from eligible locations****
         }  // ends for x = ......... ******************************
         
         //Set-Up x-tables. **********************************************
         
         //xCandTable set-up.
         uCount = 0;
         
         for ( z = 0; uCount < xCount; ++z )
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 5 )
                {
                     xCandTable[uCount] = (z + 1);
                     ++uCount;
                }
         // ends for z = .... xCandTable is set up. ******************
         
         //xLocTable set-up. **********************
         u = 0;
         
         for ( z = 0; u < xCount; ++z )
             if ( xCandTable[u] == (z + 1) )
             {
                  uu = 0;
                  for ( x = 0; uu < sumTable[z]; ++x )
                  {
                      if ( checkTable[z][y][x] > 0 )
                         if ( nDR[y][x] == 0 )
                           if ( nTR[y][x] == 0 )
                            if ( nQR[y][x] == 0 )                             
                            {
                                 xLocTable[u][uu] = x;
                                 ++uu;
                            }
                  }  //ends for x = ..... ****************
                  
                  ++u;
             }  // ends if xCandT...**********
         //ends for z... x-tables are set up. *************************
         
                    
            
  /*        //for debug purposes, print x-tables for each row........
          for ( x = 0; x < xCount; ++x )
          {
              printf("Row#%d,", y );
              printf("xCand[%d]=%d,", x, xCandTable[x]);
              printf("xLoc[%d]=%d,%d,%d,%d\n", x, xLocTable[x][0], xLocTable[x][1], xLocTable[x][2], \
                                              xLocTable[x][3]);
          }     //  for debug purposes only  *******************
  */          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE X-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the X-tables to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (xCount - 3); ++t )
         {
             //Initialize uniqueLocTable to nine's.*******************
             for ( u = 0; u < 4; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements from element t, into uniqueLocTable. *****************
             for ( u = 0; u < (sumTable[(xCandTable[t] - 1)]); ++u )
                 uniqueLocTable[u] = xLocTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (xCount - 2); ++tt )
             {
                 //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                 uCount = sumTable[(xCandTable[t] - 1)];
                 
                 if ( uCount < 4 )
                 {
                    for ( u = uCount; u < 4; ++u )
                        uniqueLocTable[u] = 9;
                        
                    for ( u = 0; u < 2; ++u )                        
                        uniqueAdded[u] = 0;      
                 }  // ends for uC.... *********
                                     
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueLocTable[(uCount - 1)] = loc;
                          ++uniqueAdded[0];
                     }
                     else
                         // Over the limit- doesn't qualify for link table.. *****************
                         break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
   /*                 // debug purposes ******************************************
                    printf("2F y=%d, t=%d, tt=%d, ", y, t, tt );
                    printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
   */                 // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("2S y=%d, t=%d, tt=%d, ", y, t, tt );
                 printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
  */               // debug purposes ******************************************************
                 
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO FIRST. *********
                 for ( ttt = (tt + 1); ttt < (xCount - 1); ++ttt )
                 {
                   //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                   uCount = (sumTable[(xCandTable[t] - 1)] + uniqueAdded[0]);
                 
                   if ( uCount < 4 )
                   {
                     for ( u = uCount; u < 4; ++u ) 
                      uniqueLocTable[u] = 9;    // ends if uC... **********
                      
                     uniqueAdded[1] = 0;
                   }  // end if uC... *****
                                                                    
                   for ( u = 0; u < (sumTable[(xCandTable[ttt] - 1)]); ++u )
                  {
                     loc = xLocTable[ttt][u];
                     
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
                     
                     if ( uCount < 5 )
                     {
                        //enter in uniqueTable- continue ******
                        uniqueLocTable[(uCount - 1)] = loc;
                        ++uniqueAdded[1];
                     }
                     else
                         // Over the limit- doesn't qualify for link table.. *****************
                         break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
 /*                   // debug purposes ******************************************
                    printf("3F y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                    printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
 */                   // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
   /*              // debug purposes ******************************************
                 printf("3S y=%d, t=%d, tt=%d, ttt=%d, ", y, t, tt, ttt );
                 printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
   */              // debug purposes ******************************************************
         
    

            
                 //Begin search for possible 4th element of linkedTable. **********************
                 for ( tttt = (ttt + 1); tttt < xCount; ++tttt )
                 {
                      //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                      uCount = (sumTable[(xCandTable[t] - 1)] + uniqueAdded[0] + uniqueAdded[1]);
                 
                      if ( uCount < 4 )
                         for ( u = uCount; u < 4; ++u )
                            uniqueLocTable[u] = 9;
                        
                            
                     for ( u = 0; u < (sumTable[(xCandTable[tttt] - 1)]); ++u )
                     {
                         loc = xLocTable[tttt][u];
                 
                         for ( uu = 0; uu < 4; ++uu )
                             if ( uniqueLocTable[uu] != loc )
                                continue;  // next uu. *******
                             else
                             {
                                 loc = 9;
                                 break;  //next . *******
                             } // ends for ( uu = ... ***********
                         
                         if ( loc == 9 )
                            continue;  // next u ... *******************
                        
                         // have a unique location.. *********
                         ++uCount;
                         
                         if ( uCount < 5 )
                           //enter in uniqueTable- continue ******
                           uniqueLocTable[(uCount - 1)] = loc;
                         else
                           // Over the limit- doesn't qualify for link table.. *****************
                           break;
                           
                         if ( uCount != 4 )
                         {
                              printf("uCount < 4.. Major error.. Will Have to Quit..");
                              system("pause");
                         } 
                         
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 4 )
                {
    /*               // debug purposes ******************************************
                   printf("4F y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                   printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
                   printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                      uniqueLocTable[3]);
    */               // debug purposes ******************************************************
                   continue;    //unable to link 4th element to 3rd. Need to try a different fourth element,
                   // next tttt. **********
                }    
              
         
                  
                // a hiddenQuadsRow has been achieved. Process the hTR. ***************
         
  /*              // debug purposes ******************************************
                printf("4S y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
                printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
                printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                  uniqueLocTable[3]);
  */              // debug purposes ******************************************************
         
                //Put all 4 elements t, tt, ttt and tttt int the nQR table. ****************
                nQR[y][(uniqueLocTable[0])] = 1;
                nQR[y][(uniqueLocTable[1])] = 1;
                nQR[y][(uniqueLocTable[2])] = 1;
                nQR[y][(uniqueLocTable[3])] = 1;
         
                //Zap all other candidates, in these 4 squares. *********************
                // REMEMBER, xCandTable[t] = 1st candidate, [tt]= 2nd candidate, [ttt]= 3rd candidate,
                //[tttt]= 4th candidate... *************
                
                for ( u = 0; u < 4; ++u )
                {
                    x = uniqueLocTable[u];
                    
                    for ( z = 0; z < 9; ++z )
                        if ( z != (xCandTable[t] - 1) )
                           if ( z != (xCandTable[tt] - 1) )
                              if ( z != (xCandTable[ttt] - 1) )
                                 if ( z != (xCandTable[tttt] - 1) )
                                     if ( checkTable[z][y][x] > 0 )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
                    printf("\nZapped xC=%d at [%d][%d]- in HidQuadRow...\n", (z + 1), y, x);   // debug purposes
                                     } //end if cT... ******
                }  // end for u = .... **********
                
                if ( changes == 0 )
                   hiddenQuadsRow();
                   
                return; //return to main.. ...
         
               }  // ends tttt... **********  
              } // ends ttt... ************
         
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*              // debug purposes ******************************************
         printf("E  y=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", y, t, tt, ttt, tttt );
         printf("xCount=%d, uCount=%d, loc=%d, ", xCount, uCount, loc);
         printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                            uniqueLocTable[3]);
 **/        // debug purposes ******************************************************
         
         
   } //end for ( y = ... *********   
   return;
}
             
//hiddenQuadsColumn Function ***********************************************************
void hiddenQuadsColumn (void)
{
     int x, y, z, t, tt, ttt, tttt, yy, u, uu, loc, yCount, uCount, uniqueAdded[2];
     int sumTable[9], yCandTable[9], yLocTable[9][4], uniqueLocTable[4];
     
     for ( x = 0; x < 9; ++x )
     {
         //Initialize sumTable. *********************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-up sumTable, and count qualified candidates for y-tables. **************
         // to be qualified- at least 4 candidates, that only occur 2-4 times in Column. (2-1's,3-4's,2-8's). ***
         //sumTable counts the number of times each candidate appears in the Column. *********************
         
         yCount = 0;
         
         for ( z = 0; z < 9; ++z )
         {
             for ( y = 0; y < 9; ++y )
                 if ( checkTable[z][y][x] > 0 )
                    if ( nDC[y][x] == 0 )
                       if ( nTC[y][x] == 0 )
                         if (nQC[y][x] == 0 )
                          ++sumTable[z];  // ends for y = ... ********* 
                          
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 5 )
                   ++yCount;
         }  // ends for z = ..... ***********************
         
         // Eliminate yCount < 4, because you need 4 seperate candidates, 2-4 times each. ********
         if ( yCount < 4 )
            continue;   // next y. ********************
            
         // Initialize y-tables. ********************************
         for ( y = 0; y < 9; ++y )
         {
             yCandTable[y] = 0;
             for ( yy = 0; yy < 4; ++yy )
                 yLocTable[y][yy] = 9;  //must initialize to 9, 9 is unique from eligible locations****
         }  // ends for y = ......... ******************************
         
         //Set-Up y-tables. **********************************************
         
         //yCandTable set-up.
         uCount = 0;
         
         for ( z = 0; uCount < yCount; ++z )
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 5 )
                {
                     yCandTable[uCount] = (z + 1);
                     ++uCount;
                }
         // ends for z = .... yCandTable is set up. ******************
         
         //yLocTable set-up. **********************
         u = 0;
         
         for ( z = 0; u < yCount; ++z )
             if ( yCandTable[u] == (z + 1) )
             {
                  uu = 0;
                  for ( y = 0; uu < sumTable[z]; ++y )
                  {
                      if ( checkTable[z][y][x] > 0 )
                         if ( nDC[y][x] == 0 )    // these 3 statements unnecessary..
                           if ( nTC[y][x] == 0 )    // 
                            if ( nQC[y][x] == 0 )      //                       
                            {
                                 yLocTable[u][uu] = y;
                                 ++uu;
                            }
                  }  //ends for y = ..... ****************
                  
                  ++u;
             }  // ends if yCandT...**********
         //ends for z... y-tables are set up. *************************
         
                    
            
  /*        //for debug purposes, print y-tables for each Column........
          for ( y = 0; y < yCount; ++y )
          {
              printf("Col#%d,", x );
              printf("yCand[%d]=%d,", y, yCandTable[y]);
              printf("yLoc[%d]=%d,%d,%d,%d\n", y, yLocTable[y][0], yLocTable[y][1], yLocTable[y][2], \
                                              yLocTable[y][3]);
          }     //  for debug purposes only  *******************
  */          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE Y-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the Y-tables to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (yCount - 3); ++t )
         {
             //Initialize uniqueLocTable to nine's.*******************
             for ( u = 0; u < 4; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements from element t, into uniqueLocTable. *****************
             for ( u = 0; u < (sumTable[(yCandTable[t] - 1)]); ++u )
                 uniqueLocTable[u] = yLocTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (yCount - 2); ++tt )
             {
                 //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                 uCount = sumTable[(yCandTable[t] - 1)];
                 
                 if ( uCount < 4 )
                 {
                    for ( u = uCount; u < 4; ++u )
                        uniqueLocTable[u] = 9;
                    
                    for ( u = 0; u < 2; ++u )     
                        uniqueAdded[u] = 0;      
                 }  // ends if uC.... *********
                                     
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueLocTable[(uCount - 1)] = loc;
                          ++uniqueAdded[0];
                     }
                     else
                         // Over the limit- doesn't qualify for link table.. *****************
                         break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
  /*                  // debug purposes ******************************************
                    printf("2F x=%d, t=%d, tt=%d, ", x, t, tt );
                    printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("2S x=%d, t=%d, tt=%d, ", x, t, tt );
                 printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
  */               // debug purposes ******************************************************
                 
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO FIRST. *********
                 for ( ttt = (tt + 1); ttt < (yCount - 1); ++ttt )
                 {
                   //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                   uCount = (sumTable[(yCandTable[t] - 1)] + uniqueAdded[0]);
                 
                   if ( uCount < 4 )
                   {
                     for ( u = uCount; u < 4; ++u ) 
                      uniqueLocTable[u] = 9;    
                      
                     uniqueAdded[1] = 0;
                   }  // end if uC... *****
                                                                                    
                   for ( u = 0; u < (sumTable[(yCandTable[ttt] - 1)]); ++u )
                  {
                     loc = yLocTable[ttt][u];
                     
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
                     
                     if ( uCount < 5 )
                     {
                       //enter in uniqueTable****
                       uniqueLocTable[(uCount - 1)] = loc;
                       ++uniqueAdded[1];
                     }
                     else
                         // Over the limit- doesn't qualify for link table.. *****************
                         break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
  /*                  // debug purposes ******************************************
                    printf("3F x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                    printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
  */                  // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("3S x=%d, t=%d, tt=%d, ttt=%d, ", x, t, tt, ttt );
                 printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
  */               // debug purposes ******************************************************
         
    

            
                 //Begin search for possible 4th element of linkedTable. **********************
                 for ( tttt = (ttt + 1); tttt < yCount; ++tttt )
                 {
                     uCount = (sumTable[(yCandTable[t] - 1)] + uniqueAdded[0] + uniqueAdded[1]);
                     //if uCount < 4, put unique location(s) into uniqueLocTable, 
                     
                      if ( uCount < 4 )
                         for ( u = uCount; u < 4; ++u )
                            uniqueLocTable[u] = 9;
             
                     for ( u = 0; u < (sumTable[(yCandTable[tttt] - 1)]); ++u )
                     {
                         loc = yLocTable[tttt][u];
                         
                         
                         
                         for ( uu = 0; uu < 4; ++uu )
                             if ( uniqueLocTable[uu] != loc )
                                continue;  // next uu. *******
                             else
                             {
                                 loc = 9;
                                 break;  //next . *******
                             } // ends for ( uu = ... ***********
                         
                         if ( loc == 9 )
                            continue;  // next u ... *******************
                            
                         // have a unique location.. *********
                         ++uCount;
                         
                         if ( uCount < 5 )
                           //enter in uniqueTable- continue ******
                           uniqueLocTable[(uCount - 1)] = loc;
                         else
                           // Over the limit- doesn't qualify for link table.. *****************
                           break;
                           
                         if ( uCount != 4 )
                         {
                              printf("uCount < 4.. Major error.. Will Have to Quit..");
                              system("pause");
                         } 
                        
                         
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 4 )
                {
     /*              // debug purposes ******************************************
                   printf("4F x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
                   printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
                   printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                      uniqueLocTable[3]);
     */              // debug purposes ******************************************************
                   continue;    //unable to link 4th element to 3rd. Need to try a different fourth element,
                   // next tttt. **********
                }    
              
         
                  
                // a hiddenTriplesColumn has been achieved. Process the hTR. ***************
         
     /*           // debug purposes ******************************************
                printf("4S x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
                printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
                printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                  uniqueLocTable[3]);
     */           // debug purposes ******************************************************
         
                //Put all 4 elements t, tt, ttt and tttt int the nQR table. ****************
                nQC[(uniqueLocTable[0])][x] = 1;
                nQC[(uniqueLocTable[1])][x] = 1;
                nQC[(uniqueLocTable[2])][x] = 1;
                nQC[(uniqueLocTable[3])][x] = 1;
         
                //Zap all other candidates, in these 4 cells. *********************
                // REMEMBER, yCandTable[t] = 1st candidate, [tt]= 2nd candidate, [ttt]= 3rd candidate,
                //[tttt]= 4th candidate... *************
                
                for ( u = 0; u < 4; ++u )
                {
                    y = uniqueLocTable[u];
                    
                    for ( z = 0; z < 9; ++z )
                        if ( z != (yCandTable[t] - 1) )
                           if ( z != (yCandTable[tt] - 1) )
                              if ( z != (yCandTable[ttt] - 1) )
                                 if ( z != (yCandTable[tttt] - 1) )
                                     if ( checkTable[z][y][x] > 0 )
                                     {
                                        checkTable[z][y][x] = 0;
                                        --checkRemainderTable[y][x];
                                        ++changes;
                    printf("\nZapped yC=%d at [%d][%d]- in HidQuadCol...\n", (z + 1), y, x);   // debug purposes
                                     } //end if cT... ******
                }  // end for u = .... **********
                
                if ( changes == 0 )
                   hiddenQuadsColumn();
                   
                return; //return to main.. ...
         
               }  // ends tttt... **********  
              } // ends ttt... ************
         
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
  /*             // debug purposes ******************************************
         printf("E  x=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", x, t, tt, ttt, tttt );
         printf("yCount=%d, uCount=%d, loc=%d, ", yCount, uCount, loc);
         printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                            uniqueLocTable[3]);
  */       // debug purposes ******************************************************
         
         
   } //end for ( x = ... *********   
   return;
}
             
//hiddenQuadsRegion Function ***********************************************************
void hiddenQuadsRegion (void)
{
     int x, y, z, t, tt, ttt, tttt, xx, u, uu, loc, regCount, uCount, uniqueAdded[2];
     int sumTable[9], regCandTable[9], regLocTable[9][4], uniqueLocTable[4];
     int region, a, aa, r, c;
     
     for ( region = 0; region < 9; ++region )
     {
         //Initialize sumTable. *********************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-up sumTable, and count qualified candidates for reg-tables. **************
         // to be qualified- at least 4 candidates, that only occur 2-4 times in region. (2-1's,3-4's,2-8's). ***
         //sumTable counts the number of times each candidate appears in the region. *********************
         
         regCount = 0;
         
         for ( z = 0; z < 9; ++z )
         {
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 
                 if ( checkTable[z][r][c] > 0 )
                    if ( nDReg[r][c] == 0 )
                       if ( nTReg[r][c] == 0 )
                         if (nQReg[r][c] == 0 )
                          ++sumTable[z];   
             } // ends for a = .. ****
                          
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 5 )
                   ++regCount;
         }  // ends for z = ..... ***********************
         
         // Eliminate regCount < 4, because you need 4 seperate candidates, 2-4 times each. ********
         if ( regCount < 4 )
            continue;   // next y. ********************
            
         // Initialize reg-tables. ********************************
         for ( a = 0; a < 9; ++a )
         {
             regCandTable[a] = 0;
             for ( aa = 0; aa < 4; ++aa )
                 regLocTable[a][aa] = 9;  //must initialize to 9, 9 is unique from eligible locations****
         }  // ends for a = ......... ******************************
         
         //Set-Up reg-tables. **********************************************
         
         //regCandTable set-up.
         uCount = 0;
         
         for ( z = 0; uCount < regCount; ++z )
             if ( sumTable[z] > 1 )
                if ( sumTable[z] < 5 )
                {
                     regCandTable[uCount] = (z + 1);
                     ++uCount;
                }
         // ends for z = .... regCandTable is set up. ******************
         
         //regLocTable set-up. **********************
         u = 0;
         
         for ( z = 0; u < regCount; ++z )
             if ( regCandTable[u] == (z + 1) )
             {
                  uu = 0;
                  for ( a = 0; uu < sumTable[z]; ++a )
                  {
                      r = regionalDispatchTable[region][a].row;
                      c = regionalDispatchTable[region][a].column;
                      
    /*                  if ( a > 9 )
                      {
                           printf("a > 9. Problem, to debug.");
                           system("pause");
                      }
    */                  
                      if ( checkTable[z][r][c] > 0 )
                         if ( nDReg[r][c] == 0 )     //3 statements unnecessary... 
                           if ( nTReg[r][c] == 0 )      //
                            if ( nQReg[r][c] == 0 )       //                      
                            {
                                 regLocTable[u][uu] = a;
                                 ++uu;
                            }
                  }  //ends for a = ..... ****************
                  
                  ++u;
             }  // ends if regCandT...**********
         //ends for z... reg-tables are set up. *************************
         
                    
            
  /*        //for debug purposes, print reg-tables for each region........
          for ( a = 0; a < regCount; ++a )
          {
              printf("Region#%d,", region );
              printf("regCand[%d]=%d,", a, regCandTable[a]);
              printf("regLoc[%d]=%d,%d,%d,%d\n", a, regLocTable[a][0], regLocTable[a][1], regLocTable[a][2], \
                                              regLocTable[a][3]);
          }     //  for debug purposes only  *******************
  */          
         //THIS EXCLUDES ALL NON-QUALIFYING ELEMENTS, FOR THE REG-TABLES.
         
         //Start LinkedTable Processing.     Note, there is no actual linkTable. We just use
         // t,tt, ttt, tttt and the REG-tables to simulate the effect of an actual linkTable.
                  
         for ( t = 0; t < (regCount - 3); ++t )
         {
             //Initialize uniqueLocTable to nine's.*******************
             for ( u = 0; u < 4; ++u )
                 uniqueLocTable[u] = 9;
                 
             //Put elements from element t, into uniqueLocTable. *****************
             for ( u = 0; u < (sumTable[(regCandTable[t] - 1)]); ++u )
                 uniqueLocTable[u] = regLocTable[t][u];
                 
             //Done with placing first element into linkedTable. ******************
             
             //BEGIN SEARCH FOR A SECOND ELEMENT TO LINK TO FIRST. *********
             for ( tt = (t + 1); tt < (regCount - 2); ++tt )
             {
                 //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                 uCount = sumTable[(regCandTable[t] - 1)];
                 
                 if ( uCount < 4 )
                 {
                    for ( u = uCount; u < 4; ++u )
                        uniqueLocTable[u] = 9;
                        
                    for ( u = 0; u < 2; ++u )                        
                        uniqueAdded[u] = 0;      
                 }  // ends for uC.... *********
                                     
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
                     
                     if ( uCount < 5 )
                     {
                          //enter in uniqueTable- continue ******
                          uniqueLocTable[(uCount - 1)] = loc;
                          ++uniqueAdded[0];
                     }
                     else
                         // Over the limit- doesn't qualify for link table.. *****************
                         break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
   /*                 // debug purposes ******************************************
                    printf("2F reg=%d, t=%d, tt=%d, ", region, t, tt );
                    printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
   */                 // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE FIRST. TRY ANOTHER SECOND. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 2ND ELEMENT IN LINKED TABLE. **********************
                              
   /*              // debug purposes ******************************************
                 printf("2S reg=%d, t=%d, tt=%d, ", region, t, tt );
                 printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
   */              // debug purposes ******************************************************
                 
                 
                 //BEGIN SEARCH FOR A THIRD ELEMENT TO LINK TO FIRST. *********
                 for ( ttt = (tt + 1); ttt < (regCount - 1); ++ttt )
                 {
                   //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                   uCount = (sumTable[(regCandTable[t] - 1)] + uniqueAdded[0]);
                 
                   if ( uCount < 4 )
                   {
                     for ( u = uCount; u < 4; ++u ) 
                      uniqueLocTable[u] = 9;    // ends if uC... **********
                      
                     uniqueAdded[1] = 0;
                   }  // end if uC... *****
                                                                    
                   for ( u = 0; u < (sumTable[(regCandTable[ttt] - 1)]); ++u )
                  {
                     loc = regLocTable[ttt][u];
                     
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
                     
                     if ( uCount < 5 )
                     {
                        //enter in uniqueTable- continue ******
                        uniqueLocTable[(uCount - 1)] = loc;
                        ++uniqueAdded[1];
                     }
                     else
                         // Over the limit- doesn't qualify for link table.. *****************
                         break;
                 }  //ends for ( u =...  ***********
                           
                 if ( uCount > 4 )
                 {
    /*                // debug purposes ******************************************
                    printf("3F reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                    printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
                    printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
    */                // debug purposes ******************************************************
         
                    // UNABLE TO LINK THIS ELEMENT TO THE SECOND. TRY ANOTHER THIRD. *******
                    continue;     //next tt. **************
                 }               
                    

                    
                 //SUCCESSFULLY LINKED 3RD ELEMENT IN LINKED TABLE. **********************
                              
  /*               // debug purposes ******************************************
                 printf("3S reg=%d, t=%d, tt=%d, ttt=%d, ", region, t, tt, ttt );
                 printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
                 printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                    uniqueLocTable[3]);
  */               // debug purposes ******************************************************
         
    

            
                 //Begin search for possible 4th element of linkedTable. **********************
                 for ( tttt = (ttt + 1); tttt < regCount; ++tttt )
                 {
                      //if uCount < 4, put unique location(s) into uniqueLocTable, 
                                  
                      uCount = (sumTable[(regCandTable[t] - 1)] + uniqueAdded[0] + uniqueAdded[1]);
                 
                      if ( uCount < 4 )
                         for ( u = uCount; u < 4; ++u )
                            uniqueLocTable[u] = 9;
                        
                            
                     for ( u = 0; u < (sumTable[(regCandTable[tttt] - 1)]); ++u )
                     {
                         loc = regLocTable[tttt][u];
                 
                         for ( uu = 0; uu < 4; ++uu )
                             if ( uniqueLocTable[uu] != loc )
                                continue;  // next uu. *******
                             else
                             {
                                 loc = 9;
                                 break;  //next . *******
                             } // ends for ( uu = ... ***********
                         
                         if ( loc == 9 )
                            continue;  // next u ... *******************
                        
                         // have a unique location.. *********
                         ++uCount;
                         
                         if ( uCount < 5 )
                           //enter in uniqueTable- continue ******
                           uniqueLocTable[(uCount - 1)] = loc;
                         else
                           // Over the limit- doesn't qualify for link table.. *****************
                           break;
                           
                         if ( uCount != 4 )
                         {
                              printf("uCount < 4.. Major error.. Will Have to Quit..");
                              system("pause");
                         } 
                         
                     }  // ends for ( u =... ***********
             
             
         
                if (uCount > 4 )
                {
    /*               // debug purposes ******************************************
                   printf("4F reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
                   printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
                   printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                      uniqueLocTable[3]);
    */               // debug purposes ******************************************************
                   continue;    //unable to link 4th element to 3rd. Need to try a different fourth element,
                   // next tttt. **********
                }    
              
         
                  
                // a hiddenQuadsRegion has been achieved. Process the hTR. ***************
         
/*                // debug purposes ******************************************
                printf("4S reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
                printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
                printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                                  uniqueLocTable[3]);
*/                // debug purposes ******************************************************
         
                //Put all 4 elements t, tt, ttt and tttt int the nQR table. ****************
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
                
                a = uniqueLocTable[3];
                r = regionalDispatchTable[region][a].row;
                c = regionalDispatchTable[region][a].column;
                nQReg[r][c] = 1;
                
                
         
                //Zap all other candidates, in these 4 squares. *********************
                // REMEMBER, regCandTable[t] = 1st candidate, [tt]= 2nd candidate, [ttt]= 3rd candidate,
                //[tttt]= 4th candidate... *************
                
                for ( u = 0; u < 4; ++u )
                {
                    a = uniqueLocTable[u];
                    r = regionalDispatchTable[region][a].row;
                    c = regionalDispatchTable[region][a].column;
                    
                    for ( z = 0; z < 9; ++z )
                        if ( z != (regCandTable[t] - 1) )
                           if ( z != (regCandTable[tt] - 1) )
                              if ( z != (regCandTable[ttt] - 1) )
                                 if ( z != (regCandTable[tttt] - 1) )
                                     if ( checkTable[z][r][c] > 0 )
                                     {
                                        checkTable[z][r][c] = 0;
                                        --checkRemainderTable[r][c];
                                        ++changes;
                    printf("\nZapped regC=%d at [%d][%d]- in HidQuadReg...\n", (z + 1), y, x);   // debug purposes
                                     } //end if cT... ******
                }  // end for u = .... **********
                
                if ( changes == 0 )
                   hiddenQuadsRegion();
                   
                return; //return to main.. 
         
               }  // ends tttt... **********  
              } // ends ttt... ************
         
            }  // end tt ... ******
        
         
         }  // end for ( t = ..... ***********
      
 /*              // debug purposes ******************************************
         printf("E  reg=%d, t=%d, tt=%d, ttt=%d, tttt=%d, ", region, t, tt, ttt, tttt );
         printf("regCount=%d, uCount=%d, loc=%d, ", regCount, uCount, loc);
         printf("uniqueLoc=%d,%d,%d,%d\n", uniqueLocTable[0], uniqueLocTable[1], uniqueLocTable[2], \
                                            uniqueLocTable[3]);
 */        // debug purposes ******************************************************
         
         
   } //end for ( region = ... *********   
   return;
}
             
