int factorial ( int:a, int:b) {
	int:k=1+a;
	(0!=a) @ { k=k*(a-1); };
}

int arrayrial (int:a) {
    int[]:b=int[2]; //[a+1];
    int:i=0 + 2;

    i = a + (i!=0 ? 5 : 2);
	b[0]=1;
	b[1]=b[0]+1;
    r i;
}

int:a = 5 + 2, c=3; //, b=6;
int:b;

(a!=7 ? { b=1; } : { b=23; })();

//arrayrial(a);

{ int:j = a*2; c=j; }();

//b = a;
//arrayrial(a);

//(int:i) { r i+c*2; };
int (int) : var = int (int:i) { r (i*c); };

//c = int (int:i) { r (i*c); } (10);
c = var (10);

a;
b;
c;
