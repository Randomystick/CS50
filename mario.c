#include <cs50.h>
#include <stdio.h>

int main(void) {
    int number;
    do {
        number = get_int("Enter: ");
    } while (!(number >= 1 && number <= 8));
    
    switch(number) {
      case 8 :
         printf("       #  #\n      ##  ##\n     ###  ###\n    ####  ####\n   #####  #####\n  ######  ######\n #######  #######\n########  ########\n" );
            break;
      case 7 :
         printf("      #  #\n     ##  ##\n    ###  ###\n   ####  ####\n  #####  #####\n ######  ######\n#######  #######\n" );
            break;
      case 6 :
         printf("     #  #\n    ##  ##\n   ###  ###\n  ####  ####\n #####  #####\n######  ######\n" );
            break;
      case 5 :
         printf("    #  #\n   ##  ##\n  ###  ###\n ####  ####\n#####  #####\n" );
            break;
      case 4 :
         printf("   #  #\n  ##  ##\n ###  ###\n####  ####\n");
            break;
      case 3 :
         printf("  #  #\n ##  ##\n###  ###\n" );
            break;
      case 2 :
         printf(" #  #\n##  ##\n");
            break;
      case 1 :
         printf("#  #\n");
            break;
   }
    return 0;
}
