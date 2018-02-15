// Header file for the Sudoku Project. ******************

// FUNCTION DECLARATIONS ********************************************************
void setupTables (void);
void beginGame (void);
void standardCheck (int ansCount);
int main (void);
void nakedSingles (void);
void processAnswer (int y, int x);
void zeroRegion (int y, int x);
void zeroRow (int y, int x);
void zeroColumn (int y, int x);
void hiddenSinglesRow (void);
void hiddenSinglesColumn (void);
void fprintCheckTable (void);
void printCheckRemainderTable (void);
void printAnswerTable (void);
void printDimTwoAnsTbl (void);
void printNDTables (void);
void printNTTables (void);
void printNQTables (void);
void printNPTables (void);
//void fprintqualifiedXWingTable (void);
//void printDoublesTable (void);
//void fprintDoublesTriplesComboTable (void);
//void fprintqualifiedSwordfishTable (void);
void deBug (void);
void resetNakedTables (void);
void hiddenSinglesRegion (void);
void nakedDoublesRow (void);
void nakedDoublesColumn (void);
void nakedDoublesRegion (void);
void exclusiveRegionRow (void);
void exclusiveRegionColumn (void);
void pointingPairRow (void);
void pointingPairColumn (void);
void hiddenDoublesRow (void);
void hiddenDoublesColumn (void);
void hiddenDoublesRegion (void);
void nakedTriplesRow (void);
void nakedTriplesColumn (void);
void nakedTriplesRegion (void);
void hiddenTriplesRow (void);
void hiddenTriplesColumn (void);
void hiddenTriplesRegion (void);
void nakedQuadsRow (void);
void nakedQuadsColumn (void);
void nakedQuadsRegion (void);
void hiddenQuadsRow (void);
void hiddenQuadsColumn (void);
void hiddenQuadsRegion (void);
void nakedPentsRow (void);
void nakedPentsColumn (void);
void nakedPentsRegion (void);
void hiddenPentsRow (void);
void hiddenPentsColumn (void);
void hiddenPentsRegion (void);
void xWingRow (void);
void xWingColumn (void);
void xYWingRowColumn (void);
void xYWingRowRegion (void);
void xYWingColumnRegion (void);
void xYZWingRowRegion (void);
void xYZWingColumnRegion (void);
void swordfishRow (void);
void swordfishColumn (void);
void jellyfishRow (void);
void jellyfishColumn (void);
void squirmbagRow (void);
void squirmbagColumn (void);
void gordonianRectangles (void);
void oneSidedGordRectRow (void);
void oneSidedGordRectColumn (void);
void twoSidedGordRectRow (void);
void twoSidedGordRectColumn (void);
void sixSidedGordPolygons (void);
void oneSidedGordPolygonsSix (void);
void extendGordRectRow (void);
void extendGordRectColumn (void);
void oneSidedExtendGordRectRow (void);
void oneSidedExtendGordRectColumn (void);
void setupBiValueTable (void);
void biValueSolutions (void);
void setupBiLocationTable (void);
void biLocationSolutions (void);
//void saveTables (void);
//void setupMultipleTable (void);
//void checkMultiple (void);
//void checkMultAnsTable (int y, int x);
//void compareAnsTables (void);

// GLOBAL VARIABLES **************************************************************
int startTable[9][9];
int answerTable[9][9];
int checkTable[9][9][9];
int checkRemainderTable[9][9];
int regionalAnswerTable[9][9];
int printCheckTable[27][27];
//int qualifiedXWingTable[9][9][9], printqualifiedXWingTable[27][27];
//int printDoublesTriplesComboTable[27][27];
int nDR[9][9], nDC[9][9], nDReg[9][9];
int nTR[9][9], nTC[9][9], nTReg[9][9];
int nQR[9][9], nQC[9][9], nQReg[9][9];
int nPR[9][9], nPC[9][9], nPReg[9][9]; 
//int doublesTable[9][9][2]; // dt[y][x][z+1] *************
//int triplesTable[9][9][3];
//int qualifiedSwordfishTable[9][9][9], printqualifiedSwordfishTable[27][27];
struct point
{
       int row;
       int column;
} regionalDispatchTable[9][9], elementPoint;

int answersSolved, changes, errCode, firstTime;

//Grid Coloring Variables, etc... *************************
int dimension, holdY, holdX = -1, holdZ, valueA, valueB;
int biValue, biLocation = 1, aBLT, bBLT, cBLT, fABLT, fBBLT, fCBLT;
int fABLT = 9, fBBLT = 9;

int dimAnswerTable[3][9][9];
int dimCheckTable[3][9][9][9];
int dimCheckRemainderTable[3][9][9];
int dimAnswersSolved[3];
int firstBLT[9][9][9][3];  //holds location of connected pair- only the first connected pair kept in table.
                                //[0]-row, [1]- column, [2]- region...
int biLocationTable[9][9][9][3]; //holds location of the connected pair..[0]-row, [1]-column, [2]-region...
int biValueTable[9][9][2];  //holds the biValues in [0] and [1]..

//CHECK FOR MULTIPLE SOLUTIONS............
//int multipleTable[81][13], multAnsTable[9][9], multiple, stop;
