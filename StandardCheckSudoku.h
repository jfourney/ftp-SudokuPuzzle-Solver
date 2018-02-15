// THIS FUNCTION CHECKS TO SEE IF TRADITIONAL STANDARDS OF SUDOKU ARE MET.
// THERE ARE SUPPOSED TO BE NO MORE THAN 30 SOLUTIONS GIVEN, TO START.
// ALSO, THE PUZZLE IS SUPPOSED TO BE SYMMETRICAL.

/*
//Function Declarations **************
void standardCheck (int ansCount);
*/

// standardCheck Function ******************
void standardCheck (int ansCount)
{
     int x, y, z, yy, xx, vert = 1, horiz = 1, diag = 1, antiDiag = 1, ninety = 1;
     int oneEighty = 1, twoSeventy = 1;
     
     //Check to see if 30 or less answers. *******************
     if ( ansCount > 32 )
     {
          printf("THIS PUZZLE DOES NOT MEET MOST SUDOKU STANDARDS,");
          printf("BECAUSE THERE ARE MORE THAN 32 SOLUTIONS AT THE START OF THE GAME.\n");
          
          system("pause");
     }
     else  if ( ansCount > 30 )
     {
          printf("THIS PUZZLE DOES NOT MEET TRADITIONAL STANDARDS,");
          printf("BECAUSE THERE ARE MORE THAN 30 SOLUTIONS AT THE START OF THE GAME.\n");
          
          system("pause");
     } //ends if else aC.................. 
     
     // Check to see if Vertical Reflection exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !vert )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = y; 
             xx = (8 - x);
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       vert = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      vert = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     // Check to see if Horizontal Reflection exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !horiz )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = (8 - y); 
             xx = x;
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       horiz = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      horiz = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     // Check to see if Diagonal Reflection exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !diag )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = x; 
             xx = y;
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       diag = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      diag = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     // Check to see if Anti-diagonal Reflection exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !antiDiag )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = (8 - x); 
             xx = (8 - y);
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       antiDiag = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      antiDiag = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     // Check to see if 90-degree Rotational Symmetry exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !ninety )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = x; 
             xx = (8 - y);
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       ninety = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      ninety = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     // Check to see if 180-degree Rotational Symmetry exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !oneEighty )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = (4 - y) + 4; 
             xx = (4 - x) + 4;
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       oneEighty = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      oneEighty = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     // Check to see if 270-degree Rotational Symmetry exists*****
     for ( y = 0; y < 9; ++y )
     {
         if ( !twoSeventy )
            break;
            
         for ( x = 0; x < 9; ++x )
         {
             yy = (8 - x); 
             xx = y;
             
             if ( startTable[y][x] )
             {
                  if ( !startTable[yy][xx] )
                  {
                       twoSeventy = 0;
                       break;
                  } // ends if sT yy .....
             }
             else
                 if ( startTable[yy][xx] )
                 {
                      twoSeventy = 0;
                      break;
                 } //  ends if else sT yy.........
         } // ends for x.......... *************
     } // ends for y ...........  ************
     
     //Check to see if puzzle exhibits any standard symmetry whatsoever. ***********   
     if ( !(vert || horiz || diag || antiDiag || ninety || oneEighty || twoSeventy) )
     {
        printf("THIS PUZZLE DOES NOT MEET MORE TRADITIONAL SUDOKU STANDARDS,");
        printf("BECAUSE IT IS NOT SYMMETRICAL!\n");
              
        system("pause");
        return;
     }  //ends if !v... *********
     
     //Check for full-dihedral symmetry.*******************************
     if ( vert && horiz && diag && antiDiag && ninety && oneEighty && twoSeventy )
     {
        printf("THIS PUZZLE EXHIBITS FULL-DIHEDRAL SYMMETRY!\n");
              
        system("pause");
        return;
     }  //ends if v... *********
     
     //Check for Vertical +/or Horizontal Reflection.*******************************
     if ( vert && horiz )
     {
        printf("THIS PUZZLE EXHIBITS VERTICAL + HORIZONTAL REFLECTION!\n");
              
        system("pause");
        goto DIAGONAL;
     }  //ends if v... *********
     
     if ( vert )
     {
        printf("THIS PUZZLE EXHIBITS VERTICAL REFLECTION!\n");
              
        system("pause");
     }
     else if ( horiz )
          {
             printf("THIS PUZZLE EXHIBITS HORIZONTAL REFLECTION!\n");
              
             system("pause");
          } //ends if else vert.........
          
          
     DIAGONAL:
     //Check for Diagonal +/or Anti-diagonal Reflection.*******************************
     if ( diag && antiDiag )
     {
        printf("THIS PUZZLE EXHIBITS DIAGONAL + ANTI-DIAGONAL REFLECTION!\n");
              
        system("pause");
        goto ROTATIONAL;
     }  //ends if diag... *********
     
     if ( diag )
     {
        printf("THIS PUZZLE EXHIBITS DIAGONAL REFLECTION!\n");
              
        system("pause");
     }
     else if ( antiDiag )
          {
             printf("THIS PUZZLE EXHIBITS ANTI-DIAGONAL REFLECTION!\n");
              
             system("pause");
          } //ends if else diag.........
            
     ROTATIONAL:
     //Check for Rotational Symmetries (full, 90, 180, or 270).*******************************
     if ( ninety && oneEighty && twoSeventy )
     {
        printf("THIS PUZZLE EXHIBITS FULL ROTATIONAL SYMMETRY!\n");
              
        system("pause");
        return;
     }  //ends if ninety... *********
     
     if ( ninety  )
     {
        printf("THIS PUZZLE EXHIBITS 90-DEGREE ROTATIONAL SYMMETRY!\n");
              
        system("pause");
     }  //ends if ninety... *********
     
     if ( oneEighty )
     {
        printf("THIS PUZZLE EXHIBITS TRADITIONAL STANDARD SYMMETRY (180 rotational)!\n");
              
        system("pause");
     }  //ends if oneEighty... *********
     
     if ( twoSeventy )
     {
        printf("THIS PUZZLE EXHIBITS 270-DEGREE ROTATIONAL SYMMETRY!\n");
              
        system("pause");
        
     }  //ends if twoSeventy... *********
         
         
     return;
}
 
             
         
