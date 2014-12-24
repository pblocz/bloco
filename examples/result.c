
#include <stdio.h>
#include <iostream>
   #include <stdlib.h>
using namespace std;

   typedef struct {void* code; void* frame; } anon_t;

   void __aux0(anon_t f) {
((void (*) ( void* )) f.code)( f.frame );}
      void __anon0 ( void* _frame ) {
 void *frame = malloc(8);
*(void**)frame=_frame;
 ( ( int *) ((*(char**) frame) + 8) )[0] = ( ( int *) ((*(char**) frame) + 8) )[0] + ( ( int *) ((*(char**) frame) + 12) )[0] ;
 ( ( int *) ((*(char**) frame) + 12) )[0] = ( ( int *) ((*(char**) frame) + 12) )[0] + 1 ;
 }
 int main() { void* _frame=0;
void *frame = malloc(16);
*(void**)frame=_frame;
 ( ( int *) (((char*) frame) + 8) )[0] = 0 ;
 ( ( int *) (((char*) frame) + 12) )[0] = 0 ;
 ;
 while( ( ( int *) (((char*) frame) + 12) )[0] <= 100 ) {  __aux0 ( (anon_t) { __anon0 ,frame} ) ; } ;
 cout<<( ( int *) (((char*) frame) + 8) )[0] ;
}
