//Reset the Naked Subset Tables *****************

/*
//Function Declarations *****************************
void resetNakedTables (void);
*/

//resetNakedTables Function *******************************
void resetNakedTables (void)
{
     int x, y;
     
     for ( y = 0; y < 9; ++y )
         for ( x = 0; x < 9; ++x )
         {
             //resetNDTable
             nDR[y][x] = 0;
             nDC[y][x] = 0;
             nDReg[y][x] = 0;
             
             //resetNTTable
             nTR[y][x] = 0;
             nTC[y][x] = 0;
             nTReg[y][x] = 0;
             
             //resetNQTable
             nQR[y][x] = 0;
             nQC[y][x] = 0;
             nQReg[y][x] = 0;
             
             //resetNPTable
             nPR[y][x] = 0;
             nPC[y][x] = 0;
             nPReg[y][x] = 0;
             
         } //ends for x = .................
         
     return;
}   

