//One-Sided Extended Gordonian Rectangles Processing for Sudoku. ************
/*
//Function Declarations ***************************************
void oneSidedExtendGordRectRow (void);
void oneSidedExtendGordRectColumn (void);
*/

//oneSidedExtendGordRectRow Function ******************************************
void oneSidedExtendGordRectRow (void)
{
     int x, y, z, c, cc, a, b, xx, xxx, yy, yyy, region, rr;
     int candsA[2], candsB[2], candsC[2], commonCand, zCand, corrRow;
     
     for ( y = 0; y < 8; ++y )
         for ( x = 0; x < 8; ++x )
         {
             //Find candsA.....................
             
             if ( checkRemainderTable[y][x] != 2 )
                continue;  //next x...............
                
             if ( nDR[y][x] )
                continue; //next x.............
             
             if ( !nDC[y][x] )
                continue; //next x..........
                
             //found nDC- now find corresponding nDC.........
             //first put cands in candsA............
             c = 0;
             
             for ( z = 0; z < 9; ++z )
             {
                 if ( !checkTable[z][y][x] )
                    continue; //next z...........
                    
                 candsA[c] = checkTable[z][y][x];
                 ++c;
             } //ends for z = .................
             
             region = regionalAnswerTable[y][x];
             
             for ( yy = (y + 1); yy < 9; ++yy )
             {
                 if ( checkRemainderTable[yy][x] != 2 )
                    continue;  //next yy...............
                    
                 rr = regionalAnswerTable[yy][x];
                 
                 if ( region != rr )
                    continue;
                 
                 if ( nDR[yy][x] )
                    continue; //next yy...........
                    
                 if ( !nDC[yy][x] )
                    continue; //next yy............
                    
                 //found nDC- is it corresponding?............
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( checkTable[z][yy][x] != candsA[0] )
                        continue; //next z......
                        
                     break; //from z.... found corr. nDC.....
                 } //ends for z...................
                 
                 if ( z == 9 )
                    continue; //next yy.... not corr. nDC..........
                    
                 //Is a corresponding nDC- (corrRow = yy)..........
                 corrRow = yy;
                 break;
             } //ends for yy................
             
             if ( yy == 9 )
                continue; //next x....no corresponding nDC- won't qualify..
                //corr. nDC already processed previously in the program...
                
             //Found candsA-- now find candsB..................
             for ( xx = (x + 1); xx < 9; ++xx )
             {
                 if ( checkRemainderTable[y][xx] != 2 )
                    continue;  //next xx...............
                 
                 if ( nDR[y][xx] )
                    continue; //next xx..........
                    
                 if ( !nDC[y][xx] )
                    continue; //next xx...............
                    
                 //found another nDC in row--put cands in candsB............
                 c = 0;
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( !checkTable[z][y][xx] )
                        continue; //next z..........
                        
                     candsB[c] = checkTable[z][y][xx];
                     ++c;
                 } //ends for z =........................
                 
                 //candsB is set up- check if common cand..........
                 commonCand = 0;
                 
                 for ( a = 0; a < 2; ++a )
                     for ( b = 0; b < 2; ++b )
                         if ( candsA[a] == candsB[b] )
                            commonCand = candsA[a];  //ends for a...ends for b...
                            
                 if ( !commonCand )
                    continue; //next xx.... not a qualifier.......
                    
                 //Found qualifying nDC in the row- is corr. nDC in corrRow.....
                 if ( !nDC[corrRow][xx] )
                    continue; //next xx........
                    
                 //could be qualifier for candsB- check cand to see if corr nDC..
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( checkTable[z][corrRow][xx] != candsB[0] )
                        continue;
                        
                     break; //from z.....found corr. nDC....
                 } //ends for z.............
                 
                 if ( z == 9 )
                    continue; //next xx... not a qualifier.......
                    
                 //Found both candsA, and candsB--set up what you'll need for candsC...
                 for ( a = 0; a < 2; ++a )
                 {
                     if ( candsA[a] != commonCand )
                        candsC[0] = candsA[a];
                        
                     if ( candsB[a] != commonCand )
                        candsC[1] = candsB[a];
                 } //ends for a................
                 
                 //Find candsC-- (checkRemainder=3) w/ candsC..............
                 for ( xxx = 0; xxx < 9; ++xxx )
                 {
                     if ( checkRemainderTable[y][xxx] != 3 )
                        continue; //next xxx...................
                        
                     if ( (!checkTable[(candsC[0] - 1)][y][xxx]) || \
                          (!checkTable[(candsC[1] - 1)][y][xxx]) )
                        continue; //next xxx...............
                        
                     //Found a candsC qualifier for row- check corr. candsC at corrRow..
                     for ( z = 0; z < 9; ++z )
                         if ( checkTable[z][corrRow][xxx] != checkTable[z][y][xxx] )
                            break; //from for z..........
                            
                     if ( z != 9 )
                        continue; //next xxx........
                        
                     //Found the oneSidedExtendedGordRectRow- with fWings at:
                     // [y][xxx] and [yyy][xxx]..................
                     
                     //Find zCand......................
                     for ( z = 0; z < 9; ++z )
                     {
                         if ( (z != (candsC[0] - 1)) && (z != (candsC[1] - 1)) )
                            if ( !checkTable[z][y][xxx] )
                               continue; //next z..........
                               
                         //found zCand.............
                         zCand = checkTable[z][y][xxx];
                         break; //from for z...............
                     } //ends forz.............
                     
                     //debug purposes..........
                     if ( (z == 9) || (!zCand) )
                     {
                          printf("Problem finding zCand, in oneSidedExtendGordRectRow! Quit Game!\n");
                          system("pause");
                          return;
                     } //ends if z............
                     //debug purposes...........
                     
                     //Found a true one-sided extended gord Rect Row..........
                     //Zap zCand from all the other cells at [xxx]-- except [y] and [corrRow]...
                     
/*                     //debug purposes................
                     printf("FOUND A TRUE ONE-SIDED EXTENDEDED GORD RECT ROW....\n");
                     for ( cc = 0; cc < 2; ++cc )
                     {
                         printf("cA[%d]=%d, cB[%d]=%d, cC[%d]=%d, ", cc, candsA[cc], \
                            cc, candsB[cc], cc, candsC[cc]);
                     } //ends for cc.....
                     printf("zC=%d, y=%d, yy=%d, commonCand=%d, corrRow=%d, x=%d, ",\
                       zCand, y, yy, commonCand, corrRow, x);
                     printf("yyy=%d, xx=%d, xxx=%d...\n", yyy, xx, xxx);
                      
                     deBug();
                     system("pause");
*/                     //debug purposes...............
                     
                     for ( yyy = 0; yyy < 9; ++yyy )
                     {
                         if ( (yyy == y) || (yyy == corrRow) )
                            continue; //next yyy.............
                            
                         if ( !checkTable[(zCand - 1)][yyy][xxx] )
                            continue; //next yyy........
                            
                         //found a zCand to zap..................
                         checkTable[(zCand - 1)][yyy][xxx] = 0;
                         --checkRemainderTable[yyy][xxx];
                         ++changes;
         printf("Zapped zC=%d at [%d][%d]--in oneSideExtendGordRectRow..\t", zCand, yyy, xxx);
                     } //ends for yyy..................
                     
                     //debug purposes...........
                     system("pause");
                     //debug purposes...........
                     
                     if ( changes > 0 )
                        return;
                 } //ends for xxx.........
             } //ends for xx............
         } //ends for x.... ends for y.............
     return;
}
                     
 //oneSidedExtendGordRectColumn Function ******************************************
void oneSidedExtendGordRectColumn (void)
{
     int x, y, z, c, a, b, xx, xxx, yy, yyy, region, rr;
     int candsA[2], candsB[2], candsC[2], commonCand, zCand, corrCol;
     
     for ( x = 0; x < 8; ++x )
         for ( y = 0; y < 8; ++y )
         {
             //Find candsA.....................
             
             if ( checkRemainderTable[y][x] != 2 )
                continue;  //next y...............
                
             if ( nDC[y][x] )
                continue; //next y.............
             
             if ( !nDR[y][x] )
                continue; //next y..........
                
             //found nDR- now find corresponding nDR.........
             //first put cands in candsA............
             c = 0;
             
             for ( z = 0; z < 9; ++z )
             {
                 if ( !checkTable[z][y][x] )
                    continue; //next z...........
                    
                 candsA[c] = checkTable[z][y][x];
                 ++c;
             } //ends for z = .................
             
             region = regionalAnswerTable[y][x];
             
             for ( xx = (x + 1); xx < 9; ++xx )
             {
                 if ( checkRemainderTable[y][xx] != 2 )
                    continue;  //next xx...............
                    
                 rr = regionalAnswerTable[y][xx];
                 
                 if ( region != rr )
                    continue;
                 
                 if ( nDC[y][xx] )
                    continue; //next xx...........
                    
                 if ( !nDR[y][xx] )
                    continue; //next xx............
                    
                 //found nDR- is it corresponding?............
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( checkTable[z][y][xx] != candsA[0] )
                        continue; //next z......
                        
                     break; //from z.... found corr. nDR.....
                 } //ends for z...................
                 
                 if ( z == 9 )
                    continue; //next xx.... not corr. nDR..........
                    
                 //Is a corresponding nDR- (corrCol = xx)..........
                 corrCol = xx;
                 break;
             } //ends for xx................
             
             if ( xx == 9 )
                continue; //next y....no corresponding nDR- won't qualify..
                //corr. nDR already processed previously in the program...
                
             //Found candsA-- now find candsB..................
             for ( yy = (y + 1); yy < 9; ++yy )
             {
                 if ( checkRemainderTable[yy][x] != 2 )
                    continue;  //next yy...............
                 
                 if ( nDC[yy][x] )
                    continue; //next yy..........
                    
                 if ( !nDR[yy][x] )
                    continue; //next yy...............
                    
                 //found another nDR in row--put cands in candsB............
                 c = 0;
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( !checkTable[z][yy][x] )
                        continue; //next z..........
                        
                     candsB[c] = checkTable[z][yy][x];
                     ++c;
                 } //ends for z =........................
                 
                 //candsB is set up- check if common cand..........
                 commonCand = 0;
                 
                 for ( a = 0; a < 2; ++a )
                     for ( b = 0; b < 2; ++b )
                         if ( candsA[a] == candsB[b] )
                            commonCand = candsA[a];  //ends for a...ends for b...
                            
                 if ( !commonCand )
                    continue; //next yy.... not a qualifier.......
                    
                 //Found qualifying nDR in the col- is corr. nDR in corrCol.....
                 if ( !nDR[yy][corrCol] )
                    continue; //next yy........
                    
                 //could be qualifier for candsB- check cand to see if corr nDR..
                 for ( z = 0; z < 9; ++z )
                 {
                     if ( checkTable[z][yy][corrCol] != candsB[0] )
                        continue;
                        
                     break; //from z.....found corr. nDR....
                 } //ends for z.............
                 
                 if ( z == 9 )
                    continue; //next yy... not a qualifier.......
                    
                 //Found both candsA, and candsB--set up what you'll need for candsC...
                 for ( a = 0; a < 2; ++a )
                 {
                     if ( candsA[a] != commonCand )
                        candsC[0] = candsA[a];
                        
                     if ( candsB[a] != commonCand )
                        candsC[1] = candsB[a];
                 } //ends for a................
                 
                 //Find candsC-- (checkRemainder=3) w/ candsC..............
                 for ( yyy = 0; yyy < 9; ++yyy )
                 {
                     if ( checkRemainderTable[yyy][x] != 3 )
                        continue; //next yyy...................
                        
                     if ( (!checkTable[(candsC[0] - 1)][yyy][x]) || \
                          (!checkTable[(candsC[1] - 1)][yyy][x]) )
                        continue; //next yyy...............
                        
                     //Found a candsC qualifier for row- check corr. candsC at corrRow..
                     for ( z = 0; z < 9; ++z )
                         if ( checkTable[z][yyy][corrCol] != checkTable[z][yyy][x] )
                            break; //from for z..........
                            
                     if ( z != 9 )
                        continue; //next yyy........
                        
                     //Found the oneSidedExtendedGordRectRow- with fWings at:
                     // [yyy][x] and [yyy][xxx]..................
                     
                     //Find zCand......................
                     for ( z = 0; z < 9; ++z )
                     {
                         if ( (z != (candsC[0] - 1)) && (z != (candsC[1] - 1)) )
                            if ( !checkTable[z][yyy][x] )
                               continue; //next z..........
                               
                         //found zCand.............
                         zCand = checkTable[z][yyy][x];
                         break; //from for z...............
                     } //ends for z.............
                     
                     //debug purposes..........
                     if ( (z == 9) || (!zCand) )
                     {
                          printf("Problem finding zCand, in oneSidedExtendGordRectCol! Quit Game!\n");
                          system("pause");
                          return;
                     } //ends if z............
                     //debug purposes...........
                     
                     //Found a true one-sided extended gord Rect Col..........
                     //Zap zCand from all the other cells at [yyy]-- except [x] and [corrCol]...
                     for ( xxx = 0; xxx < 9; ++xxx )
                     {
                         if ( (xxx == x) || (xxx == corrCol) )
                            continue; //next xxx.............
                            
                         if ( !checkTable[(zCand - 1)][yyy][xxx] )
                            continue; //next yyy........
                            
                         //found a zCand to zap..................
                         checkTable[(zCand - 1)][yyy][xxx] = 0;
                         --checkRemainderTable[yyy][xxx];
                         ++changes;
         printf("Zapped zC=%d at [%d][%d]--in oneSideExtendGordRectCol..\t", zCand, yyy, xxx);
                     } //ends for yyy..................
                     
                     if ( changes > 0 )
                        return;
                 } //ends for yyy.........
             } //ends for yy............
         } //ends for y.... ends for x.............
     return;
}
                                         
                           
                 
