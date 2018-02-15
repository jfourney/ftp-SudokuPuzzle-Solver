// Debugging Files for Sudoku. *****************

//DON'T INCLUDE ANY HEADER FILES, FUNCTION DECLARATIONS, OR VARIABLE DECLARATIONS,
// DUE TO THE VERY STRICT DOUBLE INCLSION RULE.

/*
// Function Declarations *****************************************
void fprintCheckTable (void);
void printCheckRemainderTable (void);
void printAnswerTable (void);
void printDimTwoAnsTbl (void);
void printNDTables (void);
void printNTTables (void);
void printNQTables (void);
void printNPTables (void);
void fprintqualifiedXWingTable (void);
void deBug (void);
void printDoublesTable (void);
void fprintDoublesTriplesComboTable (void);
void fprintqualifiedSwordfishTable (void);
*/

//printCheckTable Function. *******************************************************
void fprintCheckTable (void)
{
     int x, y, z, r, c;
     
     //set up printCheckTable. **********************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 9; ++z )
             {
                 r = (3 * y) + (z / 3);
                 c = (3 * x) + (z % 3);
                 printCheckTable[r][c] = checkTable[z][y][x];
             }
             
     //Print the printCheckTable. ********************************************
     printf("Here's the checkTable, of CANDIDATES left for each cell.\n");
     
     for ( r = 0; r < 27; ++r )
     {
         if ( r % 3 == 0 )
            printf("___________________________________\n");
            
         for ( c = 0; c < 27; ++c )
         {    
              if ( printCheckTable[r][c] > 0 )
                    printf("%d", printCheckTable[r][c]);
              else
                 printf(" ");
                 
              if ( (c % 3) == 2 )
                 printf("|");
         }
                 
         printf("\n");
     }
     
     printf("___________________________________\n");
     
     return;
}

//printCheckRemainderTable Function. ********************************************
void printCheckRemainderTable (void)
{
     printf("Here's the checkRemainderTable, with total number of candidates for each cell.\n");
     
     int x, y;
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", checkRemainderTable[y][x]);
         
         printf("\n");
         
     }
     
     return;
}


//printAnswerTable Function. ******************************************************
void printAnswerTable (void)
{
     int x, y;
     
     //print answerTable. ************************************
     printf("Here's the answerTable.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", answerTable[y][x]);
             
         printf("\n");
     }
     

     
     return;
}

//printDimTwoAnsTbl Function. ******************************************************
void printDimTwoAnsTbl (void)
{
     int x, y;
     
     //print dim[2]AnswerTable. ************************************
     printf("Here's the dim[2] answerTable.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", dimAnswerTable[2][y][x]);
             
         printf("\n");
     }
     

     
     return;
}


//printNDTables Function. **************************************************
void printNDTables (void)
{
     int x, y/*, region, a, r, c*/;
     
     //nDR Table. *******************************
     printf("Here's the nDR table- nakedDoublesRow.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nDR[y][x]);
             
         printf("\n");
     }
     
     //nDC Table. *******************************
     printf("Here's the nDC table- nakedDoublesColumn.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nDC[y][x]);
             
         printf("\n");
     }
     
     //nDReg Table. *******************************
     printf("Here's the nDReg table- nakedDoublesRegion.\n");
         
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nDReg[y][x]);
             
         printf("\n");
     }  
     return;
}     

//printNTTables Function *******************************************
void printNTTables (void)
{
     int x, y, z;
     
     //printNTR Table *******************************
     printf("Here's the nTR Table- nakedTriplesRow.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nTR[y][x]);
             
         printf("\n");
     }
     
     //printNTC Table *******************************
     printf("Here's the nTC Table- nakedTriplesColumn.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nTC[y][x]);
             
         printf("\n");
     }
     
     //printNTReg Table *******************************
     printf("Here's the nTReg Table- nakedTriplesRegion.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nTReg[y][x]);
             
         printf("\n");
     }          
     
     return;
}

//printNQTables Function. **************************************************
void printNQTables (void)
{
     int x, y/*, region, a, r, c*/;
     
/*     //nQR Table. *******************************
     printf("Here's the nQR table- nakedQuadsRow.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nQR[y][x]);
             
         printf("\n");
     }
     
     //nQC Table. *******************************
     printf("Here's the nQC table- nakedQuadsColumn.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nQC[y][x]);
             
         printf("\n");
     }
     
*/     //nQReg Table. *******************************
     printf("Here's the nQReg table- nakedQuadsRegion.\n");
         
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nQReg[y][x]);
             
         printf("\n");
     }
     
       
     return;
}     

//printNPTables Function. **************************************************
void printNPTables (void)
{
     int x, y/*, region, a, r, c*/;
     
     //nPR Table. *******************************
     printf("Here's the nPR table- nakedPentsRow.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nPR[y][x]);
             
         printf("\n");
     }
     
     //nPC Table. *******************************
     printf("Here's the nPC table- nakedPentsColumn.\n");
     
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nPC[y][x]);
             
         printf("\n");
     }
     
     //nPReg Table. *******************************
     printf("Here's the nPReg table- nakedPentsRegion.\n");
         
     for ( y = 0; y < 9; ++y )
     {
         for ( x = 0; x < 9; ++x )
             printf(" %d ", nPReg[y][x]);
             
         printf("\n");
     }
     
       
     return;
}     

/*
void fprintqualifiedXWingTable (void)
{
     int x, y, z, r, c;
     
     //set up printqualifiedXWingTable. **********************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 9; ++z )
             {
                 r = (3 * y) + (z / 3);
                 c = (3 * x) + (z % 3);
                 printqualifiedXWingTable[r][c] = qualifiedXWingTable[z][y][x];
             }
             
     //Print the printqualifiedXWingTable. ********************************************
     printf("Here's the qualifiedXWingTable, of CANDIDATES for each cell.\n");
     
     for ( r = 0; r < 27; ++r )
     {
         if ( r % 3 == 0 )
            printf("___________________________________\n");
            
         for ( c = 0; c < 27; ++c )
         {    
              if ( printqualifiedXWingTable[r][c] > 0 )
                    printf("%d", printqualifiedXWingTable[r][c]);
              else
                 printf(" ");
                 
              if ( (c % 3) == 2 )
                 printf("|");
         }
                 
         printf("\n");
     }
     
     printf("___________________________________\n");
     
     return;
}


//printDoublesTable Function **********************************
void printDoublesTable (void)
{
     int x, y, z;
     
          
     for ( y = 0; y < 9; ++y )
     {
         printf("___________________________\n");
         
         for ( x = 0; x < 9; ++x )
             if ( doublesTable[y][x][0] > 0 )
                printf("|%d%d", doublesTable[y][x][0], doublesTable[y][x][1]);
             else
                 printf("|  ");
                 
         printf("|\n");
     } // ends for y = ... *************
     
     printf("___________________________\n");
     
     return;
}


//printDoublesTriplesComboTable Function. *******************************************************
void fprintDoublesTriplesComboTable (void)
{
     int x, y, z, r, c;
     
     //set up printDoublesTriplesComboTable. **********************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 9; ++z )
             {
                 r = (3 * y) + (z / 3);
                 c = (3 * x) + (z % 3);
                 
                 if ( doublesTable[y][x][0] > 0 ) 
                    printDoublesTriplesComboTable[r][c] = checkTable[z][y][x];
                    
                 if ( triplesTable[y][x][0] > 0 )
                    printDoublesTriplesComboTable[r][c] = checkTable[z][y][x];
                     
             }
             
     //Print the printDoublesTriplesComboTable. ********************************************
     printf("Here's the DoublesTriplesComboTable, of qualified CANDIDATES for each cell.\n");
     
     for ( r = 0; r < 27; ++r )
     {
         if ( r % 3 == 0 )
            printf("___________________________________\n");
            
         for ( c = 0; c < 27; ++c )
         {    
              if ( printDoublesTriplesComboTable[r][c] > 0 )
                    printf("%d", printDoublesTriplesComboTable[r][c]);
              else
                 printf(" ");
                 
              if ( (c % 3) == 2 )
                 printf("|");
         }
                 
         printf("\n");
     }
     
     printf("___________________________________\n");
     
     return;
}

void fprintqualifiedSwordfishTable (void)
{
     int x, y, z, r, c;
     
     //set up printqualifiedSwordfishTable. **********************************************
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
             for ( z = 0; z < 9; ++z )
             {
                 r = (3 * y) + (z / 3);
                 c = (3 * x) + (z % 3);
                 printqualifiedSwordfishTable[r][c] = qualifiedSwordfishTable[z][y][x];
             }
             
     //Print the printqualifiedSwordfishTable. ********************************************
     printf("Here's the qualifiedSwordfishTable, of CANDIDATES for each cell.\n");
     
     for ( r = 0; r < 27; ++r )
     {
         if ( r % 3 == 0 )
            printf("___________________________________\n");
            
         for ( c = 0; c < 27; ++c )
         {    
              if ( printqualifiedSwordfishTable[r][c] > 0 )
                    printf("%d", printqualifiedSwordfishTable[r][c]);
              else
                 printf(" ");
                 
              if ( (c % 3) == 2 )
                 printf("|");
         }
                 
         printf("\n");
     }
     
     printf("___________________________________\n");
     
     
     return;
}

*/

//deBug Function. *********************************************
void deBug (void)
{
     
     /*// Print regionalAnswerTable. *****************************************
     int region, a, r, c;
     printf("Here's the regionalDispatchTable- lists region of corresponding table element.\n");
     
     for ( region = 0; region < 9; ++region )
     {
         for ( a = 0; a < 9; ++a )
             printf(" %d ", regionalAnswerTable[region][a]);
             
         printf("\n");
     }
     
     //Print regionalDispatchTable. ************************************************
     printf("Here's the regionalDispatchTable- list of table elements in each region.\n");
     
     for ( region = 0; region < 9; ++region )
     {
         printf("            REGION # %d is elements:\n");
         
         for ( a = 0; a < 9; ++a )
         {
             r = regionalDispatchTable[region][a].row;
             c = regionalDispatchTable[region][a].column;
             
             printf("%d,%d ", r, c);
         }
         
         printf("\n");
     }   */
     
//     printNDTables();
//     printNTTables();
//     printNQTables();
//       printNPTables();
     fprintCheckTable();
     printCheckRemainderTable();
     printAnswerTable();
     printDimTwoAnsTbl();
     printf("dim=%d, errCode=%d, holdY=%d, holdX=%d, changes=%d...\n", dimension, \
            errCode, holdY, holdX, changes);
     
     return;
}


