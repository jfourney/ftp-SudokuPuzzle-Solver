//RUNNING A PRINT TEST...
 #include <stdio.h>
 #include <stddef.h>
 
 int main (void)
 {
     int billions = 0;
     long long int regCount = 0;
     
     printf("THIS PROGRAM COULD TAKE A LITTLE WHILE...\n");
     
     while ( (billions < 7) || (regCount < 123456789) )
     {
           ++regCount;
           
           if ( regCount == 1000000000 )
           {
                ++billions;
                regCount = 0;
                printf("%i BILLION SOLUTIONS SO FAR....\n", billions);
           } // ends if regCount....
     } // ends while billions .....
     
     printf("%i BILLION %lli solutions ....\n", billions, regCount);
     
     system("pause");
     system("pause");
     
     return 0;
 }
