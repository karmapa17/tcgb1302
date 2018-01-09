#define BCDMAX 20 // was 24

void l2bcd ( signed char *, int );
int bcd2l ( signed char * );
void addbcd ( signed char *, signed char *, signed char * );
int compabsbcd ( signed char *, signed char * );
void subbcd ( signed char *, signed char *, signed char * );
void mulbcdl ( signed char *, signed char *, int );
void divbcdl ( signed char *, signed char *, int );
void modbcdl ( signed char *, signed char *, int );

// These are for intermediate calculations only:
signed char bcdx0[BCDMAX];
signed char bcdx1[BCDMAX];
signed char bcdx2[BCDMAX];
signed char bcdx3[BCDMAX];
signed char bcdx4[BCDMAX];
signed char bcdx5[BCDMAX];
signed char bcdx6[BCDMAX];
signed char bcary[BCDMAX];
