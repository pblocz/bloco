Programa:
	NumArgs in frame: 0
	Frame: factorial,arrayrial,a,c,b,var,
	function defition
		name: factorial
		return type:
		Ent
		arguments:
		tipo:
		Ent
		id: a
		tipo:
		Ent
		id: b
		code:
		Programa:
			NumArgs in frame: 2
			Frame: a,b,k,
			Declaración de tipo
				Ent
				Y variables:
			variable con id: k(0,2)
				Op: 43
					Type:
					Ent
					Value:
					cte: 1 type: Ent
					id: a decl(0,0) of type:
						Ent
			Op: 64
				Value:
				Op: 262
					Type:
					Ent
					Value:
					cte: 0 type: Ent
					id: a decl(0,0) of type:
						Ent
				Def:
					recibe:
					devuelve
					código
					Programa:
						NumArgs in frame: 0
						Frame: 
						Op: 61
							Type:
							Ent
							Value:
							id: k decl(1,2) of type:
								Ent
							Op: 42
								Type:
								Ent
								Value:
								id: k decl(1,2) of type:
									Ent
								Op: 45
									Type:
									Ent
									Value:
									id: a decl(1,0) of type:
										Ent
									cte: 1 type: Ent
	function defition
		name: arrayrial
		return type:
		Ent
		arguments:
		tipo:
		Ent
		id: a
		code:
		Programa:
			NumArgs in frame: 1
			Frame: a,b,i,
			Declaración de tipo
				array:
					Ent
				Y variables:
			variable con id: b(0,1)
				array def:
					Ent
size:
					cte: 2 type: 
			Declaración de tipo
				Ent
				Y variables:
			variable con id: i(0,2)
				Op: 43
					Type:
					Ent
					Value:
					cte: 0 type: Ent
					cte: 2 type: Ent
			Op: 61
				Type:
				Ent
				Value:
				id: i decl(0,2) of type:
					Ent
				Op: 43
					Type:
					Ent
					Value:
					id: a decl(0,0) of type:
						Ent
					Op: 63
						Type:
						Ent
						Value:
						Op: 262
							Type:
							Ent
							Value:
							id: i decl(0,2) of type:
								Ent
							cte: 0 type: Ent
						cte: 5 type: Ent
						cte: 2 type: Ent
			Op: 61
				Type:
				Ent
				Value:
				Op: 91
					Type:
					Ent
					Value:
					id: b decl(0,1) of type:
						array:
							Ent
					cte: 0 type: Ent
				cte: 1 type: Ent
			Op: 61
				Type:
				Ent
				Value:
				Op: 91
					Type:
					Ent
					Value:
					id: b decl(0,1) of type:
						array:
							Ent
					cte: 1 type: Ent
				Op: 43
					Type:
					Ent
					Value:
					Op: 91
						Type:
						Ent
						Value:
						id: b decl(0,1) of type:
							array:
								Ent
						cte: 0 type: Ent
					cte: 1 type: Ent
			Op: 114
				Type:
				Ent
				Value:
				id: i decl(0,2) of type:
					Ent
	Declaración de tipo
		Ent
		Y variables:
	variable con id: a(0,2)
		Op: 43
			Type:
			Ent
			Value:
			cte: 5 type: Ent
			cte: 2 type: Ent
	variable con id: c(0,3)
		cte: 3 type: Ent
	Declaración de tipo
		Ent
		Y variables:
	variable con id: b(0,4)
	Op: 40
		Value:
		Op: 63
			Type:
			funcion
				recibe
				devuelve
			Value:
			Op: 262
				Type:
				Ent
				Value:
				id: a decl(0,2) of type:
					Ent
				cte: 7 type: Ent
			Def:
				recibe:
				devuelve
				código
				Programa:
					NumArgs in frame: 0
					Frame: 
					Op: 61
						Type:
						Ent
						Value:
						id: b decl(1,4) of type:
							Ent
						cte: 1 type: Ent
			Def:
				recibe:
				devuelve
				código
				Programa:
					NumArgs in frame: 0
					Frame: 
					Op: 61
						Type:
						Ent
						Value:
						id: b decl(1,4) of type:
							Ent
						cte: 23 type: Ent
	Op: 40
		Value:
		Def:
			recibe:
			devuelve
			código
			Programa:
				NumArgs in frame: 0
				Frame: j,
				Declaración de tipo
					Ent
					Y variables:
				variable con id: j(0,0)
					Op: 42
						Type:
						Ent
						Value:
						id: a decl(1,2) of type:
							Ent
						cte: 2 type: Ent
				Op: 61
					Type:
					Ent
					Value:
					id: c decl(1,3) of type:
						Ent
					id: j decl(0,0) of type:
						Ent
	Declaración de tipo
		funcion
			recibe
			Ent
						devuelve
			Ent
		Y variables:
	variable con id: var(0,5)
		Def:
			recibe:
			tipo:
			Ent
			id: i
			devuelve
			Ent
			código
			Programa:
				NumArgs in frame: 1
				Frame: i,
				Op: 114
					Type:
					Ent
					Value:
					Op: 42
						Type:
						Ent
						Value:
						id: i decl(0,0) of type:
							Ent
						id: c decl(1,3) of type:
							Ent
	Op: 61
		Type:
		Ent
		Value:
		id: c decl(0,3) of type:
			Ent
		Op: 40
			Type:
			Ent
			Value:
			id: var decl(0,5) of type:
				funcion
					recibe
					Ent
										devuelve
					Ent
			cte: 10 type: Ent
	id: a decl(0,2) of type:
		Ent
	id: b decl(0,4) of type:
		Ent
	id: c decl(0,3) of type:
		Ent
 #include <stdio.h>
   #include <stdlib.h>
   typedef struct {void* code; void* frame; } anon_t;

    void __aux0(anon_t f) {
((void (*) ( void* )) f.code)( f.frame );}
      void __anon0 ( void* _frame ) {
 void *frame = malloc(8);
*(void**)frame=_frame;
 ( ( int *) ((*(char**) frame) + 16) )[0] = ( ( int *) ((*(char**) frame) + 16) )[0] * ( ( int *) ((*(char**) frame) + 8) )[0] - 1 ;
 }
    int factorial (void* _frame , int a , int b ) {
 void *frame = malloc(20);
*(void**)frame=_frame;
((int*)(((char*) frame) + 8))[0] = a;
((int*)(((char*) frame) + 12))[0] = b;
 ( ( int *) (((char*) frame) + 16) )[0] = 1 + ( ( int *) (((char*) frame) + 8) )[0] ;
 ;
 while( 0 != ( ( int *) (((char*) frame) + 8) )[0] ) {  __aux0 ( (anon_t) { __anon0 ,frame} ) ; } ;
 }
      int arrayrial (void* _frame , int a ) {
 void *frame = malloc(24);
*(void**)frame=_frame;
((int*)(((char*) frame) + 8))[0] = a;
 ( ( int * *) (((char*) frame) + 12) )[0] = malloc(4* ( 2 ) ) ;
 ;
 ( ( int *) (((char*) frame) + 20) )[0] = 0 + 2 ;
 ;
 ( ( int *) (((char*) frame) + 20) )[0] = ( ( int *) (((char*) frame) + 8) )[0] + ( ( ( int *) (((char*) frame) + 20) )[0] != 0 ? 5 : 2 ) ;
 ( ( int * *) (((char*) frame) + 12) )[0] [ 0 ] = 1 ;
 ( ( int * *) (((char*) frame) + 12) )[0] [ 1 ] = ( ( int * *) (((char*) frame) + 12) )[0] [ 0 ] + 1 ;
 return ( ( int *) (((char*) frame) + 20) )[0] ;
 }
   void __aux1(anon_t f) {
((void (*) ( void* )) f.code)( f.frame);}
      void __anon1 ( void* _frame ) {
 void *frame = malloc(8);
*(void**)frame=_frame;
 ( ( int *) ((*(char**) frame) + 16) )[0] = 1 ;
 }
      void __anon2 ( void* _frame ) {
 void *frame = malloc(8);
*(void**)frame=_frame;
 ( ( int *) ((*(char**) frame) + 16) )[0] = 23 ;
 }
   void __aux2(anon_t f) {
((void (*) ( void* )) f.code)( f.frame);}
      void __anon3 ( void* _frame ) {
 void *frame = malloc(12);
*(void**)frame=_frame;
 ( ( int *) (((char*) frame) + 8) )[0] = ( ( int *) ((*(char**) frame) + 8) )[0] * 2 ;
 ;
 ( ( int *) ((*(char**) frame) + 12) )[0] = ( ( int *) (((char*) frame) + 8) )[0] ;
 }
      int __anon4 ( void* _frame , int i ) {
 void *frame = malloc(12);
*(void**)frame=_frame;
((int*)(((char*) frame) + 8))[0] = i;
 return ( ( int *) (((char*) frame) + 8) )[0] * ( ( int *) ((*(char**) frame) + 12) )[0] ;
 }
   int __aux3(anon_t f, int f1) {
return ((int (*) ( void* , int )) f.code)( f.frame, f1);}
 int main() { void* _frame=0;
void *frame = malloc(36);
*(void**)frame=_frame;
 ( ( int *) (((char*) frame) + 8) )[0] = 5 + 2 ;
 ( ( int *) (((char*) frame) + 12) )[0] = 3 ;
 ;
 ;
  __aux1 ( ( ( ( int *) (((char*) frame) + 8) )[0] != 7 ? (anon_t) { __anon1 ,frame} : (anon_t) { __anon2 ,frame} ) ) ;
  __aux2 ( (anon_t) { __anon3 ,frame} ) ;
 ( ( anon_t *) (((char*) frame) + 20) )[0] = (anon_t) { __anon4 ,frame} ;
 ;
 ( ( int *) (((char*) frame) + 12) )[0] =  __aux3 ( ( ( anon_t *) (((char*) frame) + 20) )[0] , 10 ) ;
 ( ( int *) (((char*) frame) + 8) )[0] ;
 ( ( int *) (((char*) frame) + 16) )[0] ;
 ( ( int *) (((char*) frame) + 12) )[0] ;
}
