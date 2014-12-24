 #include <stdio.h>
   #include <stdlib.h>
typedef struct {void* code; void* frame; } anon_t;

int factorial (void* _frame , int a , int b ) {
 void *frame = malloc(20);
 *(void**)frame=_frame;
 ((int*)(((char*) frame) + 8))[0] = a;
 ((int*)(((char*) frame) + 12))[0] = b;
 ( ( int *) (((char*) frame) + 16) )[0] = 1 + ( ( int *) (((char*) frame) + 8) )[0] ;
 ;
}
int arrayrial (void* _frame , int a ) {
 void *frame = malloc(16);
 *(void**)frame=_frame;
 ((int*)(((char*) frame) + 8))[0] = a;
 ( ( int *) (((char*) frame) + 12) )[0] = 0 + 2 ;
 ;
}
void __aux0(anon_t f) {
  ((void (*) ( void* )) f.code)( f.frame);}
  void __anon0 ( void* _frame ) {
   void *frame = malloc(8);
   *(void**)frame=_frame;
   ( ( int *) ((*(char**) frame) + 16) )[0] = 1 ;
 }
 void __anon1 ( void* _frame ) {
   void *frame = malloc(8);
   *(void**)frame=_frame;
   ( ( int *) ((*(char**) frame) + 16) )[0] = 23 ;
 }
 void __aux1(anon_t f) {
  ((void (*) ( void* )) f.code)( f.frame);}
  void __anon2 ( void* _frame ) {
   void *frame = malloc(12);
   *(void**)frame=_frame;
   ( ( int *) (((char*) frame) + 8) )[0] = ( ( int *) ((*(char**) frame) + 8) )[0] * 2 ;
   ;
   ( ( int *) ((*(char**) frame) + 12) )[0] = ( ( int *) (((char*) frame) + 8) )[0] ;
 }
 int __aux2(anon_t f, int f1) {
  return ((int (*) ( void*, int )) f.code)( f.frame, f1);}
  int __anon3 ( void* _frame , int i ) {
   void *frame = malloc(12);
   *(void**)frame=_frame;
   ((int*)(((char*) frame) + 8))[0] = i;
   return ( ( int *) (((char*) frame) + 8) )[0] * ( ( int *) ((*(char**) frame) + 12) )[0] ;
 }
 int main() { void* _frame=0;
  void *frame = malloc(20);
  *(void**)frame=_frame;
  ( ( int *) (((char*) frame) + 8) )[0] = 5 + 2 ;
  ( ( int *) (((char*) frame) + 12) )[0] = 3 ;
  ;
  ;
  __aux0 ( ( ( ( int *) (((char*) frame) + 8) )[0] != 7 ? (anon_t) { __anon0 ,frame} : (anon_t) { __anon1 ,frame} ) ) ;
  __aux1 ( (anon_t) { __anon2 ,frame} ) ;
  ( ( int *) (((char*) frame) + 12) )[0] =  __aux2 ( (anon_t) { __anon3 ,frame} , 10 ) ;

  printf("a: %d\nb: %d\nc: %d\n",
   ( ( int *) (((char*) frame) + 8) )[0] ,
   ( ( int *) (((char*) frame) + 16) )[0] ,
   ( ( int *) (((char*) frame) + 12) )[0] );
}
