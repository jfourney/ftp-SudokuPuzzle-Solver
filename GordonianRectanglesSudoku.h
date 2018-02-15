//Gordonian Rectangles Processing.... ****************

/*
//Function Declarations **************
void gordonianRectangles (void);
*/

//gordonianRectangles Function *****************************
void gordonianRectangles (void)
{
     int x, y, z, xx, yy, region, a, r, c, gy, gx, gCount, gND[2];
     
     gND[0] = 0;
     gND[1] = 0;
     
     //Search for the ANCHOR point, with the trifecta, nDR, nDC, nDReg.....
     for ( y = 0; y < 9; ++y )
         for ( x = 0;x < 9; ++x )
         {
             if ( !nDR[y][x] || !nDC[y][x] || !nDReg[y][x] )  //if not all 3 at once...
                continue; //next x...  not the ANCHOR point....
                
             //found a trifecta....
             gCount = 0;
             
             for ( z = 0; gCount < 2; ++z )
                 if ( checkTable[z][y][x] > 0 )
                 {
                      gND[gCount] = checkTable[z][y][x];
                      ++gCount;
                 } //ends if cT... ends for z = .....  //gND table is set up...
                 
             //Find the corresponding nDReg to the anchor...
             gy = 9;
             gx = 9;
             
             region = regionalAnswerTable[y][x];
             
             for ( a = 0; a < 9; ++a )
             {
                 r = regionalDispatchTable[region][a].row;
                 c = regionalDispatchTable[region][a].column;
                 
                 if ( (r == y) && (c == x) )
                    continue;
                 
                 if ( !nDReg[r][c] )     //not an nDReg...
                    continue;  // next a.....
                    
                 // is an nDReg... is it the corresponding nDReg?..... ***********
                 if ( !checkTable[(gND[0] - 1)][r][c] )  //not the corresponding nDReg..
                    continue; //next a.... *******
                    
                 //Is the corresponding nDReg........
                 //is it in the same row, or column?.... ********
                 
                 if ( r == y )
                    gx =c;   //found the ROW BRANCH.....
                 else if ( c == x )
                         gy = r; //found the COLUMN BRANCH....
                         
                 break;  // from for a = .... ******
             } // ends for a = ....... ********
             
             if ( (gy == 9) && (gx == 9) )   // not the same row, or column for the nDReg..
                continue; // next x....   (not a Gordonian Rectangle... )...
                
             if ( gx != 9 )  //find the COLUMN BRANCH (gy), (The corresponding nDC )....
                for ( yy = 0; yy < 9; ++yy )
                {
                    if ( yy == y )
                       continue; // next yy...
                       
                    if ( !nDC[yy][x] )  //not an nDC..
                       continue; // next yy....
                       
                    //is an nDC... is it the corresponding nDC?... ********
                    if ( !checkTable[(gND[0] - 1)][yy][x] ) // not the corresponding nDC...
                       continue; // next yy....
                       
                    //Is the corresponding nDC....
                    gy = yy;
                    
                    break; //from for yy = ...... ******
                } // ends for yy = .... ************
             else
                 for ( xx = 0; xx < 9; ++xx )
                {
                    if ( xx == x )
                       continue; // next xx...
                       
                    if ( !nDR[y][xx] )  //not an nDR..
                       continue; // next xx....
                       
                    //is an nDR... is it the corresponding nDR?... ********
                    if ( !checkTable[(gND[0] - 1)][y][xx] ) // not the corresponding nDR...
                       continue; // next xx....
                       
                    //Is the corresponding nDR....
                    gx = xx;
                    
                    break; //from for xx = ...... ******
                } // ends for xx = .... ************  ends if gx... ***
             
             //FOUND THE GORDONIAN VERTEX..[GY][GX]...IF THE GORDONIAN VERTEX IS A CORRESPONDING
             //NDR (ETC), THERE IS NOT A UNIQUE SOLUTION... BREAKING A MAJOR RULE OF SUDOKU,
             //THAT ALMOST EVERYONE WOULD AGREE UPON...THERE WOULD BE AT LEAST 2 SOLUTIONS...
             
             if ( nDR[gy][gx] && checkTable[(gND[0] - 1)][gy][gx] )
                continue;
   /*          {
                  // not a unique solution.......
                  printf("\nTHERE IS NOT A UNIQUE SOLUTION TO THIS SUDOKU PUZZLE!\n \
                  THIS BREAKS A MAJOR RULE OF SUDOKU!\nYOU NEED TO END THE GAME!\n...");
                  printf("The Gordonian Vertex is at [%d][%d]...\n", gy, gx);
                  deBug();
                  system("pause");
             } // ends if nDR....
   */          
             //Check to see if GORDONIAN VERTEX contains both gND candidates...
             if ( !checkTable[(gND[0] - 1)][gy][gx] || !checkTable[(gND[1] - 1)][gy][gx] )
                //not a gordonian rectangle....
                continue; // next x.... ***********
                
             //A GORDONIAN RECTANGLE HAS BEEN ACHIEVED- ZAP GORDONIAN CANDIDATES..
             
             //Zap both gND[0], and gND[1], from the gordonian vertex...
             checkTable[(gND[0] - 1)][gy][gx] = 0;
             --checkRemainderTable[gy][gx];
             ++changes;
             printf("cand=%d Zapped at [%d][%d]..in gordRect..\t", gND[0], gy, gx); 
                
             checkTable[(gND[1] - 1)][gy][gx] = 0;
             --checkRemainderTable[gy][gx];
             ++changes;
             printf("cand=%d Zapped at [%d][%d]..in gordRect..\t", gND[1], gy, gx);
             
             return;
         }  // ends for x = ..... *********ends for y...
         
     return;
} 
                
                
                  
