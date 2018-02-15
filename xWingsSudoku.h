// X-WING PROCESSING FOR SUDOKU. ***************

/*
//FUNCTION DECLARATIONS. **************************
void xWingRow (void);
void xWingColumn (void);
*/

//xWingRow Processing. *********************************
void xWingRow (void)
{
     int x, y, z, yy, yyy, xx, xxx;
     int sumTable[9][2];
     int qualifiedXWingTable[9][9][9];
     
     //KIND OF CONFUSING, BECAUSE YOU COLLECT INFORMATION ON CANDIDATES
     // IN THE COLUMN, TO PROCESS THE X-WINGS IN THE ROW.
     
     //INITIALIZE THE qualifiedSumTable[z][y][x], that will hold the candidate,
     // in question for the xWingRow. *******************************
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             for ( z = 0; z < 9; ++z )
                 qualifiedXWingTable[z][y][x] = 0;
                 
     //SET-UP THE qualifiedXWingTable, with the sumTable elements that qualify**
     //(have only 2 of a certain candidate, in a particular colum). ************
     for ( x = 0; x < 9; ++x )
     {
         //Initialize the sumTable for each column. ******************
         for ( z = 0; z < 9; ++z )
             for ( yy = 0; yy < 2; ++yy )
                 sumTable[z][yy] = 9;
                 
         //SET-UP THE sumTable, and if it qualifies, enter it into the
         //qualifiedXWingTable.
         for ( z = 0; z < 9; ++z )
         {
             yy = 0;
             for ( y = 0; y < 9; ++y )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      ++yy;
                      if ( yy == 3 )
                         break;  // ultimately will break to next z. *******
                         
                      sumTable[z][(yy - 1)] = y;
                 } //ends for y = ... ***********
                 
             if ( yy == 3 )
                continue;   //next z. ************
                
             if ( yy < 2 )
                continue;  //next z. ***********
                
             //The 2 sumTable elements qualified for the qualifiedXWingTable. *****
             for ( yyy = 0; yyy < 2; ++yyy )
                 qualifiedXWingTable[z][(sumTable[z][yyy])][x] = (z + 1);
         }  //ends for z = ... ***********************
     }  // ends for x = ... ************
     
/*     // debug purposes **********************
     fprintqualifiedXWingTable();
     system ("pause");     
*/     //debug purposes *******************
     
     //qualifiedXWingTable is set up. It contains all the information needed,
     // to complete the task of finding actual xWR's...
     for ( y = 0; y < 8; ++y )
         for ( x = 0; x < 8; ++x )
             for ( z = 0; z < 9; ++z )
             {
                 if ( qualifiedXWingTable[z][y][x] > 0 )
                    // one qualifier found; need a second in the same row. ****
                    for ( xx = (x + 1); xx < 9; ++xx )
                    {
                        if (qualifiedXWingTable[z][y][xx] == 0 )
                           continue;  //next xx *********
                           
                        //have a qualifier in the row, now need to check the
                        //corresponding columns, to see if they're a match in 
                        //the columns, to form an xWR..........
                        for ( yy = (y + 1); yy < 9; ++yy )
                        {
                            if ( qualifiedXWingTable[z][yy][x] == 0 )
                               continue;  //next yy. *********
                               
                            if ( qualifiedXWingTable[z][yy][xx] == 0 )
                               break;  //next xx. *********???????
                               
                            //have an xWR confirmed, which are the 4 elements:
                            //[z][y][x],    [z][y][xx]      and
                            //[z][yy][x],  [z][yy][xx].....
                            
        /*                    //debug purposes ***********
                            printf("\nHave an xWR at [%d][%d][%d], [%d][%d][%d]\
                            and [%d][%d][%d], [%d][%d][%d]..\n", z,y,x,z,y,xx,z,yy,x,z,yy,xx);
        */                    //debug purposes **************
                            
                            // Process the xWR. ***********************
                            for ( xxx = 0; xxx < 9; ++xxx )
                                if ( xxx != x )
                                   if ( xxx != xx )
                                   {
                                        //any candidates here would be zapped. 
                                        if ( checkTable[z][y][xxx] > 0 )
                                        {
                                             checkTable[z][y][xxx] = 0;
                                             --checkRemainderTable[y][xxx];
                                             ++changes;
                  printf("Zapped xC=%d at [%d][%d]- in xWingRow...\t", (z + 1), y, xxx);   // debug purposes 
                                        }
                                        
                                        if ( checkTable[z][yy][xxx] > 0 )
                                        {
                                             checkTable[z][yy][xxx] = 0;
                                             --checkRemainderTable[yy][xxx];
                                             ++changes;
                printf("Zapped xC=%d at [%d][%d]- in xWingRow...\t", (z + 1), yy, xxx);   // debug purposes 
                                        }
                                        
                                   } //ends if xx = ... ***********
                        }  // ends for yy = .... *********************
                    } //ends for xx = .... *******************
             } //ends for z = ... ***********************
     return;
}
                                        
                                        
//xWingColumn Processing. *********************************
void xWingColumn (void)
{
     int x, y, z, yy, yyy, xx, xxx;
     int sumTable[9][2];
     int qualifiedXWingTable[9][9][9];
     
     //KIND OF CONFUSING, BECAUSE YOU COLLECT INFORMATION ON CANDIDATES
     // IN THE ROW, TO PROCESS THE X-WINGS IN THE ROW.
     
     //INITIALIZE THE qualifiedSumTable[z][y][x], that will hold the candidate,
     // in question for the xWingColumn. *******************************
     for ( x = 0; x < 9; ++x )
         for ( y = 0; y < 9; ++y )
             for ( z = 0; z < 9; ++z )
                 qualifiedXWingTable[z][y][x] = 0;
                 
     //SET-UP THE qualifiedXWingTable, with the sumTable elements that qualify**
     //(have only 2 of a certain candidate, in a particular colum). ************
     for ( y = 0; y < 9; ++y )
     {
         //Initialize the sumTable for each column. ******************
         for ( z = 0; z < 9; ++z )
             for ( xx = 0; xx < 2; ++xx )
                 sumTable[z][xx] = 9;
                 
         //SET-UP THE sumTable, and if it qualifies, enter it into the
         //qualifiedXWingTable.
         for ( z = 0; z < 9; ++z )
         {
             xx = 0;
             for ( x = 0; x < 9; ++x )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      ++xx;
                      if ( xx == 3 )
                         break;  // ultimately will break to next z. *******
                         
                      sumTable[z][(xx - 1)] = x;
                 } //ends for x = ... ***********
                 
             if ( xx == 3 )
                continue;   //next z. ************
                
             if ( xx < 2 )
                continue;  //next z. ***********
                
             //The 2 sumTable elements qualified for the qualifiedXWingTable. *****
             for ( xxx = 0; xxx < 2; ++xxx )
                 qualifiedXWingTable[z][y][(sumTable[z][xxx])] = (z + 1);
         }  //ends for z = ... ***********************
     }  // ends for x = ... ************
     
/*     // debug purposes **********************
     fprintqualifiedXWingTable();
     system ("pause");     
*/     //debug purposes *******************
     
     //qualifiedXWingTable is set up. It contains all the information needed,
     // to complete the task of finding actual xWC's...
     for ( x = 0; x < 8; ++x )
         for ( y = 0; y < 8; ++y )
             for ( z = 0; z < 9; ++z )
             {
                 if ( qualifiedXWingTable[z][y][x] > 0 )
                    // one qualifier found; need a second in the same column. ****
                    for ( yy = (y + 1); yy < 9; ++yy )
                    {
                        if (qualifiedXWingTable[z][yy][x] == 0 )
                           continue;  //next yy *********
                           
                        //have a qualifier in the column, now need to check the
                        //corresponding rows, to see if they're a match in 
                        //the rows, to form an xWC..........
                        for ( xx = (x + 1); xx < 9; ++xx )
                        {
                            if ( qualifiedXWingTable[z][y][xx] == 0 )
                               continue;  //next xx. *********
                               
                            if ( qualifiedXWingTable[z][yy][xx] == 0 )
                               break;  //next yy. *********???????
                               
                            //have an xWC confirmed, which are the 4 elements:
                            //[z][y][x],      [z][y][xx],
                            //           and                              
                            //[z][yy][x]      [z][yy][xx].....
                            
        /*                    //debug purposes ***********
                            printf("\nHave an xWC at [%d][%d][%d], [%d][%d][%d]\
                            and [%d][%d][%d], [%d][%d][%d]..\n", z,y,x,z,yy,x,z,y,xx,z,yy,xx);
        */                    //debug purposes **************
                            
                            // Process the xWC. ***********************
                            for ( yyy = 0; yyy < 9; ++yyy )
                                if ( yyy != y )
                                   if ( yyy != yy )
                                   {
                                        //any candidates here would be zapped. 
                                        if ( checkTable[z][yyy][x] > 0 )
                                        {
                                             checkTable[z][yyy][x] = 0;
                                             --checkRemainderTable[yyy][x];
                                             ++changes;
             printf("Zapped yC=%d at [%d][%d]- in xWWingCol...\t", (z + 1), yyy, x);   // debug purposes   
                                        }
                                        
                                        if ( checkTable[z][yyy][xx] > 0 )
                                        {
                                             checkTable[z][yyy][xx] = 0;
                                             --checkRemainderTable[yyy][xx];
                                             ++changes;
           printf("Zapped yC=%d at [%d][%d]- in xWingCol...\t", (z + 1), yyy, xx);   // debug purposes 
                                        }
                                        
                                   } //ends if yy = ... ***********
                        }  // ends for xx = .... *********************
                    } //ends for yy = .... *******************
             } //ends for z = ... ***********************
     return;
}
                                        
                                                                                
                       
     

 
