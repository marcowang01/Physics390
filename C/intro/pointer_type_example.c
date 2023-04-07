#include <stdio.h>

//
// for ascii char codes, see: https://www.gaijin.at/en/infos/ascii-ansi-character-table
// ascii chars are 8b, ansi multichar chars are 16b 
//


void
main() { 

  printf("----------------------------------------\n");

  //  char mystr[] = "Þí¾ï"; // using 'multichar chars'
  char mystr[] = "{|}~"; 
  printf( "char string: %s\n", mystr);
  printf( "size string: %d\n", sizeof(mystr));

  printf( "individual characters: \n");
  for( int i=0; i<sizeof(mystr)-1; i++ )
    printf("\taddr: %u\tchar:%c \n", &(mystr[i]),mystr[i]);


  char * strptr = mystr;
  printf( "from char pointer: \n"); 
  for( int i=0; i<sizeof(mystr)-1; i++ )
    printf("\tptr: %u\tchar: %c\n", strptr+i,*(strptr+i));

  printf("----------------------------------------\n");
  printf( "short size: %d\n", sizeof(short));

  short * shtptr = mystr;
  printf( "from short pointer: \n"); 
  for( int i=0; i<(sizeof(mystr)-1)/sizeof(short); i++ )
    printf("\tptr: %u\tshort: %x\n", shtptr+i,*(shtptr+i));


  printf("----------------------------------------\n");
  printf( "unsigned size: %d\n", sizeof(unsigned));

  unsigned * uptr = mystr;
  printf( "from unsigned pointer: \n"); 
  for( int i=0; i<(sizeof(mystr)-1)/sizeof(unsigned); i++ )
    printf("\tptr: %u\tunsigned: %x\n", uptr+i,*(uptr+i));


}
