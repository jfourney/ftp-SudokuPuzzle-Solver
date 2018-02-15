/*  THIS PROGRAM SETS UP A PERMUTATION FILE FOR SUDOKU. THIS IS ALL POSSIBLE PERMUTATIONS
   OF THE FIRST ROW. THERE SHOULD BE 9! (362,880) ELEMENTS.
*/

#include <stdio.h>
#include <stddef.h>

//main Function ....................
int main (void)
{
    int x, sub = 0, Break = 0, checkSub[9], table[9];
    long long int count = 0;
    
    FILE *outputFile;
    
    if ( (outputFile = fopen("PermutationFileSudoku", "w")) == NULL )
    {
         printf("***OUTPUT FILE -PERMUTATIONFILESUDOKU- COULD NOT BE OPENED!!!\n");
         system("pause");
         return 1;
    } // ends if output....
    
    // 9 for statements..............
    for ( table[0] = 1; table[0] < 10; ++table[0] )
    {
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
        ++sub;
        for ( table[sub] = 1; table[sub] < 10; ++table[sub] )
        {
            for ( checkSub[sub] = 0; checkSub[sub] < sub; ++checkSub[sub] )
                if ( table[sub] == table[(checkSub[sub])] )
                {
                     ++Break;
                     break;
                } // ends if table[sub]..........ends for checkSub[sub]..........
                
            if ( Break )
            {
                 Break = 0;
                 continue;
            } // ends if Break.........
            
            for ( x = 0; x < 9; ++x )
                fprintf(outputFile, "%1d", table[x]);
                
            ++count;
                
        }
        --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; } --sub; }
        // 9 closing brackets..............
        
        fclose(outputFile);
        
        printf("PROGRAM IS COMPLETE!!!!\n");
        printf("NUMBER OF PERMUTATIONS = %lli !!!!!!\n", count);
        
        system("pause");
        
        return 0;
}
                
