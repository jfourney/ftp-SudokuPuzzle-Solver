//POPULAR SUDOKU GAME

//Header Files. ***************
#include <stdio.h>
#include <stdlib.h>
#include "HeaderSudoku.h"
#include "StartSudoku.h"
#include "StandardCheckSudoku.h"
#include "DebugSudoku.h"
#include "ProcessAnswerSudoku.h"
#include "SinglesSudoku.h"
#include "ExclusiveRegionSudoku.h"
#include "PointingPairSudoku.h"
#include "ResetNakedTablesSudoku.h"
#include "NakedDoublesSudoku.h"
#include "HiddenDoublesSudoku.h"
#include "NakedTriplesSudoku.h"
#include "HiddenTriplesSudoku.h"
#include "NakedQuadsSudoku.h"
#include "HiddenQuadsSudoku.h"
#include "NakedPentsSudoku.h"
#include "HiddenPentsSudoku.h"
#include "xWingsSudoku.h"
#include "xYWingSudoku.h"
#include "xYZWingSudoku.h"
#include "SwordfishSudoku.h"
#include "JellyfishSudoku.h"
#include "SquirmbagSudoku.h"
#include "GordonianRectanglesSudoku.h"
#include "OneSidedGordonianRectanglesSudoku.h"
#include "TwoSidedGordRectSudoku.h"
#include "SixSidedGordonianPolygonsSudoku.h"
#include "OneSidedGordPolygonsSixSudoku.h"
#include "ExtendedGordonianRectanglesSudoku.h"
#include "OneSidedExtendedGordRectsSudoku.h"
#include "BiValueSolutionsSudoku.h"
#include "BiLocationSolutionsSudoku.h"
//#include "CheckMultipleSudoku.h"
                                          
// MAIN FUNCTION **********************************************************************
int main (void)
{
//    const char yes = 'y', YES = 'Y';
//    char character[4];
//    int y, x;      
    //BEGIN GAME FUNCTIONS **********************************************************
    
    printf("             ********************************************\n");
    printf("             ********************************************\n");
    printf("             ** THIS SOFTWARE WAS PROUDLY PRODUCED BY: **\n");
    printf("             **         JFF SOFTWARE                   **\n");
    printf("             **         519 Iowa Ave.                  **\n");
    printf("             **         Council Bluffs, Iowa           **\n");
    printf("             **              51503-5050                **\n");
    printf("             **                                        **\n");
    printf("             **     author + coder: John Fourney       **\n");
    printf("             **                                        **\n");
    printf("             ********************************************\n");
    printf("             ********************************************\n");
    
    setupTables();
    beginGame();
    
    if ( errCode == 1 )
    {
         printf("\nYou need to QUIT GAME, NOW!!\n");
         goto END;
    }
    
        
    // GAME SECTION *******************************************************************
    
    //NAKED SINGLES SECTION ********************************************************
    LOOP:
    if ( errCode )
       goto ENDGAME;
         
    if ( changes > 0 )
       //zero out naked subset tables
       resetNakedTables();
    
    
    do
    {                             
            changes = 0;
            nakedSingles();
            
            if ( errCode == 1)
               if ( !dimension )
                  goto ENDGAME;
               else
               {
                   changes = 0;
                   
                   if ( dimension > 2 )
                      goto BILOCATION;
                   else
                       goto BIVALUE;
               }  // ends if !dim ..else....
               
    }
    while ( changes != 0 );
    
    if ( answersSolved == 81 )
    {
 //      ++multiple;
       goto ENDGAME;
    } // ends if answers......
    
   //hiddenSinglesRow Processing *****************************************************
   //printf("hSR, ");   //debug purposes
   hiddenSinglesRow();
   
   if ( changes > 0 )
      goto LOOP;
    
   //hiddenSinglesColumn Processing ****************************************************
   //printf("hSC, ");    //debug purposes
   hiddenSinglesColumn();
    
   if ( changes > 0 )
      goto LOOP;
    
   //hiddenSinglesRegion Processing ********************************************
   //printf("hSReg, ");    //debug purposes
   hiddenSinglesRegion();
   
   if ( changes > 0 )
      goto LOOP; 
    
   //nakedDoublesRow Processing. ******************************************
   //printf("nDR, ");    //debug purposes
   nakedDoublesRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //nakedDoublesColumn Processing. **********************************************
   //printf("nDC, ");   //debug purposes
   nakedDoublesColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   //nakedDoublesRegion Processing. *****************************************
   //printf("nDReg, ");    //debug purposes
   nakedDoublesRegion();
   
   if ( changes > 0 )
      goto LOOP;
      
   //exclusiveRegionRow Processing. *******************************
   //printf("eRR, ");    //debug purposes
   exclusiveRegionRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //exclusiveRegionColumn Processing. ***************************************
   //printf("eRC, ");    //debug purposes
   exclusiveRegionColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   //pointingPairRow Processing. *******************************
   //printf("pPR, ");    //debug purposes
   pointingPairRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //pointingPairColumn Processing. ***************************************
   //printf("pPC, ");    //debug purposes
   pointingPairColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   //hiddenDoublesRow Processing **************************************************
   //printf("hDR, ");      //debug purposes
   hiddenDoublesRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //hiddenDoublesColumn Processing **************************************************
   //printf("hDC, ");      //debug purposes
   hiddenDoublesColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   //hiddenDoublesRegion Processing **************************************************
   //printf("hDReg, ");      //debug purposes
   hiddenDoublesRegion();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   //nakedTriplesRow Processing. ****************************************************
   //printf("nTR, ");     // debug purposes
   nakedTriplesRow();
   
   if ( changes > 0 )
   goto LOOP;
                      
    
   //nakedTriplesColumn Processing. ****************************************************
   //printf("nTC, ");     // debug purposes
   nakedTriplesColumn();
      
   if ( changes > 0 )
   goto LOOP;
   
   //nakedTriplesRegion Processing. ****************************************************
   //printf("nTReg, ");     // debug purposes
   nakedTriplesRegion();
   
   if ( changes > 0 )
   goto LOOP;
   
   //hiddenTriplesRow Processing. ****************************************************
   //printf("hTR, ");     // debug purposes
   hiddenTriplesRow();
   
   if ( changes > 0 )
   goto LOOP;
                      
    
   //hiddenTriplesColumn Processing. ****************************************************
   //printf("hTC, ");     // debug purposes
   hiddenTriplesColumn();
      
   if ( changes > 0 )
   goto LOOP;
   
  
   //hiddenTriplesRegion Processing. ****************************************************
   //printf("hTReg, ");     // debug purposes
   hiddenTriplesRegion();
   
   if ( changes > 0 )
   goto LOOP;
   
   //nakedQuadsRow Processing. ***************************
   //printf("nQR, ");     // debug purposes
   nakedQuadsRow();
   
   if ( changes > 0 )
   goto LOOP;
   
   //nakedQuadsColumn Processing. ***************************
   //printf("nQC, ");     // debug purposes
   nakedQuadsColumn();
   
   if ( changes > 0 )
   goto LOOP;
   
   //nakedQuadsRegion Processing. ***************************
   //printf("nQReg, ");     // debug purposes
   nakedQuadsRegion();
   
   if ( changes > 0 )
   goto LOOP;
   
   
   //hiddenQuadsRow Processing. ***************************
   //printf("hQR, ");     // debug purposes
   hiddenQuadsRow();
   
   if ( changes > 0 )
   goto LOOP;
   
   //hiddenQuadsColumn Processing. ***************************
   //printf("hQC, ");     // debug purposes
   hiddenQuadsColumn();
   
   if ( changes > 0 )
   goto LOOP;
   
   //hiddenQuadsRegion Processing. ***************************
   //printf("hQReg, ");     // debug purposes
   hiddenQuadsRegion();
   
   if ( changes > 0 )
   goto LOOP;
   
   //nakedPentsRow Processing. ***************************
   //printf("nPR, ");     // debug purposes
   nakedPentsRow();
   
   if ( changes > 0 )
   goto LOOP;
   
   //nakedPentsColumn Processing. ***************************
   //printf("nPC, ");     // debug purposes
   nakedPentsColumn();
   
   if ( changes > 0 )
   goto LOOP;
   
   //nakedPentsRegion Processing. ***************************
   //printf("nPReg, ");     // debug purposes
   nakedPentsRegion();
   
   if ( changes > 0 )
   goto LOOP;   
 
   //hiddenPentsRow Processing. ***************************
   //printf("hPR, ");     // debug purposes
   hiddenPentsRow();
   
      
   if ( changes > 0 )
   goto LOOP;
   
   //hiddenPentsColumn Processing. ***************************
   //printf("hPC, ");     // debug purposes
   hiddenPentsColumn();
   
   if ( changes > 0 )
   goto LOOP;
   
   //hiddenPentsRegion Processing. ***************************
   //printf("hPReg, ");     // debug purposes
   hiddenPentsRegion();
   
   if ( changes > 0 )
   goto LOOP;   

            
   //xWingRow Processing. ***************************************************
   //printf("xWR, ");   // debug purposes
   xWingRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //xWingColumn Processing. ***************************************************
   //printf("xWC, ");   // debug purposes
   xWingColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   //xYWingRowColumn Processing ****************************************************
   //printf("xYWRC, ");   //debug purposes ********************************
   xYWingRowColumn();
   
   if ( changes > 0 )
      goto LOOP;
         
   //xYWingRowRegion Processing ****************************************************
   //printf("xYWRReg, ");   //debug purposes ********************************
   xYWingRowRegion();
   
   if ( changes > 0 )
      goto LOOP;
      
   //xYWingColumnRegion Processing ****************************************************
   //printf("xYWCReg, ");   //debug purposes ********************************
   xYWingColumnRegion();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   
      
      
   //xYZWingRowRegion Processing. ***************************************
   //printf("xYZWRReg, ");
   xYZWingRowRegion ();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   //xYZWingColumnRegion Processing. ***************************************
   //printf("xYZWCReg, ");
   xYZWingColumnRegion ();
   
   if ( changes > 0 )
      goto LOOP;
   
   //swordfishRow Processing. ***************************************
   //printf("sfR, ");
   swordfishRow();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   //swordfishColumn Processing. ***************************************
   //printf("sfC, ");
   swordfishColumn();
   
   if ( changes > 0 )
      goto LOOP;
   
   
   //jellyfishRow Processing. ***************************************
   //printf("jfR, ");
   jellyfishRow();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   //jellyfishColumn Processing. ***************************************
   //printf("jfC, ");
   jellyfishColumn();
   
   if ( changes > 0 )
      goto LOOP;
   
   
   //squirmbagRow Processing. ***************************************
   //printf("sbR, ");
   squirmbagRow();
   
   if ( changes > 0 )
      goto LOOP;
      
      
   //squirmbagColumn Processing. ***************************************
   //printf("sbC, ");
   squirmbagColumn();
   
   //system("pause");  //debug purposes....
   
   if ( changes > 0 )
      goto LOOP;
   
   if ( !firstTime )
   {
      printf("\n\nFROM THIS POINT ON; THERE IS AN ASSUMPTION MADE, THAT THERE IS ONLY ONE \
         UNIQUE SOLUTION TO THE PUZZLE. IF THERE IS MORE THAN ONE SOLUTION, WE MAY EXPERIENCE \
         TECHNICAL DIFFICULTIES....\n\n");
      
//      saveTables();   
      system("pause");
      ++firstTime;
   } //ends if !firstTime.........
        
   //gordonianRectangles Processing. ******************************
   //printf("gR, ");  // debug purposes ************
   gordonianRectangles();
   
   if ( changes > 0 )
      goto LOOP;
      
   //oneSidedGordRectRow Processing. *********************
   //printf("oSGRR, ");  // debug purposes ************
   oneSidedGordRectRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //oneSidedGordRectColumn Processing. *********************
   //printf("oSGRC, ");  // debug purposes ************
   oneSidedGordRectColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   //TwoSidedGordRectRow Processing. *********************
   //printf("2SGRR, ");  // debug purposes ************
   twoSidedGordRectRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //twoSidedGordRectColumn Processing. *********************
   //printf("2SGRC, ");  // debug purposes ************
   twoSidedGordRectColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
  
      
   //sixSidedGordPolygons Processing *************************
   //printf("sSGP, ");
   sixSidedGordPolygons();
   
   if ( changes > 0 )
      goto LOOP;
 
   //oneSidedGordPolygonsSix Processing *************************
   //printf("oSGPS, ");
   oneSidedGordPolygonsSix();
   
   if ( changes > 0 )
      goto LOOP;
      
   //extendGordRectRow Processing ********************
   //printf("eGRR, ");  //debug purposes
   extendGordRectRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //extendGordRectColumn Processing ********************
   //printf("eGRC, ");  //debug purposes
   extendGordRectColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   //oneSidedExtendGordRectRow Processing ******************
   //printf("oSEGRR, ");
   oneSidedExtendGordRectRow();
   
   if ( changes > 0 )
      goto LOOP;
      
   //oneSidedExtendGordRectColumn Processing ******************
   //printf("oSEGRC, ");
   oneSidedExtendGordRectColumn();
   
   if ( changes > 0 )
      goto LOOP;
      
   
   if ( firstTime == 1 )
   {
      printf("WE ARE NOW USING GRID COLORING TECHNIQUES, TO SOLVE THE PUZZLE!\n");
      system("pause");
      ++firstTime;
   } // ends if firstTime..........
   
   if ( biValue == 1 )
      goto BIVALUE;
   
   //biLocationSolutions Processing *********************************   
   BILOCATION:
   //printf("bLS, ");  //debug purposes
   biLocationSolutions();
   
   if ( changes )
      goto LOOP;
      
   //biValueSolutions Processing *********************
   BIVALUE:
   //printf("bVS, ");  //debug purposes
   biValueSolutions();
   
   if ( changes )
      goto LOOP;
      
   if ( biLocation == 1 )
      goto BILOCATION;
    
/*   //debug purposes  
   printf("End Reached successfully.\n");
   system("pause");   
*/

    errCode = 0;
        
    ENDGAME:

    if ( errCode )
    {
         printf("\nFATAL ERROR FOUND! UNABLE TO SOLVE PUZZLE!\n");
         deBug();
         system("pause");
         
         return 0;
    } // ends if errCode..................
    
//    if ( !dimAnswersSolved[2] )
//       if ( multiple == 1 )
       if ( !firstTime )
       {
         printf("\nGAME SOLVED! GOOD JOB!.....HAS ONE UNIQUE SOLUTION....\n");
         printAnswerTable();
         system("pause");
         
         return 0;
       } // ends if multiple == 1...ends if !dimAS[2].....

    if ( answersSolved == 81 )
    {
       printf("\nA SOLUTION WAS FOUND!!!!!...\n");
       printAnswerTable();
    }
    else
    {
        printf("\nOnly %d solutions found.\n", answersSolved);
        deBug();
    } // ends if answersSolved ....else.........
    
/*    //CHECK TO SEE IF THEY'RE WILLING TO WAIT DAYS FOR CONFIRMATION OF UNIQUE SOLUTION, ETC...
    if ( answersSolved == 81 )
       printf("\n\n\n\nDO YOU NEED TO CHECK FOR MULTIPLE SOLUTIONS???\n");
    else
       printf("\n\n\n\nDO YOU NEED FURTHER CHECKING FOR A SOLUTION????\n");
       
    printf("\n\nFURTHER CHECKING COULD TAKE DAYS TO COMPLETE!!!\n");
    printf("\n\nIF YOU'RE WANTING TO WAIT THAT LONG, ENTER Y, or N!!!\n");
    
//    scanf("%d", &wait);
    scanf("%s", character);
    
    
//    if ( wait != 1 )
    if ( (character[0] != 'y') && (character[0] != 'Y') )
       goto END;
        
    for ( x = 0; x < 25; ++x )
        printf("\n");
    
    if ( answersSolved == 81 )
       printf("CHECKING ALL POSSIBLE COMBINATIONS, TO SEE IF THERE ARE MULTIPLE SOLUTIONS!!\n\n\t\t\tPLEASE WAIT!!!!!\n");
    else
        printf("CHECKING ALL POSSIBLE COMBINATIONS, FOR A SOLUTION TO THE PUZZLE!!!\n\n\t\t\tPLEASE WAIT!!!!!!\n");
          
    // START CHECKING ALL POSSIBLE COMBINATIONS FOR MULTIPLE SOLUTION, ETC....
    checkMultiple();
    
    if ( !multiple )
    {
         printf("\nONLY %d ANSWERS FOUND!\n", answersSolved);
         deBug();
         system("pause");
         
         return 0;
    } // ends if !multiple ................
    
    // if found first solution w/ checkMult, and don't want to check for multiple solution.......
    if ( stop )
       goto END;
    
    if ( multiple == 1 )
    {
         printf("\nGAME SOLVED! GOOD JOB!.....HAS ONE UNIQUE SOLUTION....\n");
         printAnswerTable();
         system("pause");
         
         return 0;
    } // ends if multiple == 1........
    
    //MULTIPLE SOLUTIONS ARE INVOLVED........
    printf("\nONE SOLUTION FOR THE PUZZLE IS:\n");
    printAnswerTable();
    
    printf("ANOTHER SOLUTION FOR THE PUZZLE IS:\n");
    
    for ( y = 0; y < 9; ++y )
    {
        for ( x = 0; x < 9; ++x )
            printf(" %d ", multAnsTable[y][x]);
            
        printf("\n");
    } // ends for y................
    
    printf("THIS BREAKS A MAJOR RULE OF SUDOKU!\n");
    printf("A PUZZLE SHOULD HAVE ONLY ONE UNIQUE SOLUTION!!!!\n");
*/    
    END:
    system("pause");
   
    return 0;
}
            
        
