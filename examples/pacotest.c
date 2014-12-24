 int main() { void* _frame=0;
void *frame = malloc(20);
*(void**)frame=_frame;
 ( ( int * *) (((char*) frame) + 8) )[0] = malloc(4* ( 10 ) ) ;
 ;
 ( ( int *) (((char*) frame) + 16) )[0] = 0 ;
 ;
 ( ( int * *) (((char*) frame) + 8) )[0] [ 0 ] = 1 ;
 ( ( int * *) (((char*) frame) + 8) )[0] [ 1 ] = ( ( int * *) (((char*) frame) + 8) )[0] [ 0 ] + 1 ;
 ( ( int *) (((char*) frame) + 16) )[0] = ( ( int * *) (((char*) frame) + 8) )[0] [ 1 ] ;
 ( ( int *) (((char*) frame) + 16) )[0] ;
}
