// Hidden Doubles Processing for Sudoku. ****************

/*
//Function Declarations ************
void hiddenDoublesRow (void);
void hiddenDoublesColumn (void);
void hiddenDoublesRegion (void);
*/
//hiddenDoublesRow Function *****************************************************
void hiddenDoublesRow (void)
{
     int x,y,z,zz,xx,d,dd,dt,dCount, match, elementCount, hDR[9], sumTable[9], dualTable[9][2];
     
     for ( y = 0; y < 9; ++y )
     {
         //First initialize sumTable to zeroes. ***************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-Up sumTable- counts the number of times the candidates appear in row.***
         for ( z = 0; z < 9; ++z )
             for ( x = 0; x < 9; ++x )
                 if ( nDR[y][x] == 0 )
                    if ( checkTable[z][y][x] > 0 )
                       ++sumTable[z];
         //sumTable is set-up. ******************************
         //how many duals are in the row, ie 2-1's, or 2-4's, etc. ****************
         dCount = 0;
         for ( zz = 0; zz < 9; ++zz )
             if ( sumTable[zz] == 2 )
             {
                  hDR[dCount] = (zz + 1);   //hDR table holds the candidates that appear 
                  ++dCount;                //twice in the row. 
             }
             
         if ( dCount > 1 )
         {
            //There is more than one dual in the row. ***********
            //Set-Up a dual table: dualTable[hDR element#][2 x-locations of that hDR element.]..*****
            for ( d = 0; d < dCount; ++d )
            {
                elementCount = 0;
                for ( x = 0; x < 9; ++x )
                {
                    if ( checkTable[(hDR[d] - 1)][y][x] > 0 )
                    {
                         dualTable[d][elementCount] = x;
                         ++elementCount;
                    }
                    if ( elementCount > 1 )
                       break;
                }
            }
            
            //dualTable is set-up. ********************************** 
            for ( dt = 0; dt < (dCount - 1); ++dt )
                for ( dd = (dt + 1); dd < dCount; ++dd )
                    if ( dualTable[dt][0] == dualTable[dd][0] )
                       if ( dualTable[dt][1] == dualTable[dd][1] )
                       {
                            //hDR found- now need to process *********************
                            //turn it into a naked double.   *********************
                            nDR[y][(dualTable[dt][0])] = 1;
                            nDR[y][(dualTable[dt][1])] = 1;
                            
                            //all other z-elements(candidates) of the 2 HDR elements, need zapped.***
                            for ( xx = 0; xx < 2; ++xx )
                                for ( z = 0; z < 9; ++z )
                                    if ( z != (hDR[dt] - 1) )
                                       if ( z != (hDR[dd] - 1) )
                                          if ( checkTable[z][y][(dualTable[dt][xx])] > 0 )
                                          {
                                               //element(candidate) to zap. ****************
                                               checkTable[z][y][(dualTable[dt][xx])] = 0;
                                               --checkRemainderTable[y][(dualTable[dt][xx])];
                                               ++changes;
     printf("Zapped cand=%d at [%d][%d]- in HiddenDoublesRow...\t", (z + 1), y,  dualTable[dt][xx]); 
                                          }
                       } //end if ( dualT... ********
         } //end if (dCount ... *************
     } //end for ( y = ... *********
     
     return;
}
 
//hiddenDoublesColumn Function *****************************************************
void hiddenDoublesColumn (void)
{
     int x,y,z,zz,yy,d,dd,dt,dCount, match, elementCount, hDC[9], sumTable[9], dualTable[9][2];
     
     for ( x = 0; x < 9; ++x )
     {
         //First initialize sumTable to zeroes, and hDC Table to zeroes. **********************
         for ( z = 0; z < 9; ++z )
         {
             hDC[z] = 0;
             sumTable[z] = 0;
         }
         
         //Set-Up sumTable- counts the number of times the candidates appear in the column. *****
         for ( z = 0; z < 9; ++z )
             for ( y = 0; y < 9; ++y )
                 if ( nDC[y][x] == 0 )
                    if ( checkTable[z][y][x] > 0 )
                       ++sumTable[z];
         //sumTable is set-up. ******************************
         //how many duals are in the row, ie 2-1's, or 2-4's, etc. ****************
         dCount = 0;
         for ( zz = 0; zz < 9; ++zz )
             if ( sumTable[zz] == 2 )
             {
                  hDC[dCount] = (zz + 1);   //hDC table holds the answers that appear 
                  ++dCount;                //twice in the column. 
             }
             
         if ( dCount > 1 )
         {
            //There is more than one dual in the column. ***********
            //Set-Up a dual table: dualTable[hDC element#][2 y-locations of that hDC element.]..*****
            for ( d = 0; d < dCount; ++d )
            {
                elementCount = 0;
                for ( y = 0; y < 9; ++y )
                {
                    if ( checkTable[(hDC[d] - 1)][y][x] > 0 )
                    {
                         dualTable[d][elementCount] = y;
                         ++elementCount;
                    }
                    if ( elementCount > 1 )
                       break;
                }
            }
            
            //dualTable is set-up. ********************************** 
            for ( dt = 0; dt < (dCount - 1); ++dt )
                for ( dd = (dt + 1); dd < dCount; ++dd )
                    if ( dualTable[dt][0] == dualTable[dd][0] )
                       if ( dualTable[dt][1] == dualTable[dd][1] )
                       {
                            //printf("\nhDC[%d] = %d\n", dt, hDC[dt]);  //debug purposes
                            //printf("\nhDC[%d] = %d\n", dd, hDC[dd]);  //debug purposes
                            //hDC found- now need to process *********************
                            //turn it into a naked double.   *********************
                            nDC[(dualTable[dt][0])][x] = 1;
                            //printf("\nnDC[%d][%d] = %d\n", y, dualTable[dt][0], nDC[y][(dualTable[dt][0])]);  //debug purposes
                            nDC[(dualTable[dt][1])][x] = 1;
                            // printf("\nnDC[%d][%d] = %d\n", y, dualTable[dt][1], nDC[y][(dualTable[dt][1])]);  //debug purposes
                            //all other z-elements of the 2 HDR elements, need zapped.
                            for ( yy = 0; yy < 2; ++yy )
                                for ( z = 0; z < 9; ++z )
                                    if ( z != (hDC[dt] - 1) )
                                       if ( z != (hDC[dd] - 1) )
                                          if ( checkTable[z][(dualTable[dt][yy])][x] > 0 )
                                          {
                                               //element(candidate) to zap. ****************
                                               checkTable[z][(dualTable[dt][yy])][x] = 0;
                                               --checkRemainderTable[(dualTable[dt][yy])][x];
                                               ++changes;
         printf("Zapped cand=%d at [%d][%d]- in HiddenDoublesCol...\t", (z + 1), y,  dualTable[yy][dt]);
                                          }
                       } //end if ( dualT... ********
         } //end if (dCount ... *************
     } //end for ( x = ... *********
     
     return;
}

//hiddenDoublesRegion Function *****************************************************
void hiddenDoublesRegion (void)
{
     int x,y,z,zz,aa,a,r,c,d,dd,dt,region,dCount, match, elementCount,hDReg[9], sumTable[9], dualTable[9][2];
     
     for ( region = 0; region < 9; ++region )
     {
         //First initialize sumTable to zeroes. ***************************
         for ( z = 0; z < 9; ++z )
             sumTable[z] = 0;
             
         //Set-Up sumTable- counts the number of times the candidates appear in the region *****
         for ( z = 0; z < 9; ++z )
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 if ( nDReg[r][c] == 0 )
                    if ( checkTable[z][r][c] > 0 )
                       ++sumTable[z];
             }
         //sumTable is set-up. ******************************
         //how many duals are in the region, ie 2-1's, or 2-4's, etc. ****************
         dCount = 0;
         for ( zz = 0; zz < 9; ++zz )
             if ( sumTable[zz] == 2 )
             {
                  hDReg[dCount] = (zz + 1);   //hDReg table holds the answers that appear 
                  ++dCount;                //twice in the region. 
             }
             
         if ( dCount > 1 )
         {
            //There is more than one dual in the region. ***********
            //Set-Up a dual table: dualTable[hDReg element#][2 a-locations of that hDReg element.]..*****
            for ( d = 0; d < dCount; ++d )
            {
                elementCount = 0;
                for ( a = 0; a < 9; ++a )
                {
                    r = regionalDispatchTable[region][a].row;
                    c = regionalDispatchTable[region][a].column;
                    if ( checkTable[(hDReg[d] - 1)][r][c] > 0 )
                    {
                         dualTable[d][elementCount] = a;
                         ++elementCount;
                    }
                    if ( elementCount > 1 )
                       break;
                }
            }
            
            //dualTable is set-up. ********************************** 
            for ( dt = 0; dt < (dCount - 1); ++dt )
                for ( dd = (dt + 1); dd < dCount; ++dd )
                    if ( dualTable[dt][0] == dualTable[dd][0] )
                       if ( dualTable[dt][1] == dualTable[dd][1] )
                       {
                            //hDReg found- now need to process *********************
                            //turn it into a naked double.   *********************
                            r = regionalDispatchTable[region][(dualTable[dt][0])].row;
                            c = regionalDispatchTable[region][(dualTable[dt][0])].column;
                            nDReg[r][c] = 1;
                            r = regionalDispatchTable[region][(dualTable[dt][1])].row;
                            c = regionalDispatchTable[region][(dualTable[dt][1])].column;
                            nDReg[r][c] = 1;
                            
                            //all other z-elements of the 2 HDReg elements, need zapped.
                            for ( aa = 0; aa < 2; ++aa )
                            {
                                r = regionalDispatchTable[region][(dualTable[dt][aa])].row;
                                c = regionalDispatchTable[region][(dualTable[dt][aa])].column;
                                for ( z = 0; z < 9; ++z )
                                    if ( z != (hDReg[dt] - 1) )
                                       if ( z != (hDReg[dd] - 1) )
                                          if ( checkTable[z][r][c] > 0 )
                                          {
                                               //element(candidate) to zap. ****************
                                               checkTable[z][r][c] = 0;
                                               --checkRemainderTable[r][c];
                                               ++changes;
                printf("Zapped cand=%d at [%d][%d]- in HiddenDoublesReg...\t", (z + 1), r,  c);
                                          }
                            } //end for ( aa ... *****
                       } //end if ( dualT... ********
         } //end if (dCount ... *************
     } //end for ( y = ... *********
     
     return;
}
