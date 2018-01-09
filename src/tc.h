// T1.C:

void cal_cyc ( void );
void new_yer ( void );

// T2.C:

void set_grub ( void );
void set_epoch ( void );
void do_rahu ( int, int );
void zla_dag ( int, int );
void adj_zla ( void );
void rilchaf ( int );
void spi_zagf ( void );
int gregd2jul ( int, int, int ); // MOVE ??
void jul2date ( int ); // MOVE ??
void nyi_dru ( int );
void gza_dru ( int );
void nyi_lon ( int );
void tse_dru ( int );
void nyi_dag ( int * );
void gza_dag ( int * );

// T2A.C

void set_byed ( void );
void set_epoch_b ( void );
void nyi_dru_b ( int );
void nyi_lon_b ( int );
void nyi_dag_b ( int * );

// T3.C - Planet routines.

void calc_dalbar ( int *, int, int, int );
void do_daldag ( int *, int *, int *, int *, int *, int );
void do_plans ( int );
void marsdag ( void );
void jupdag ( void );
void satdag ( void );
void merdag ( void ); // Mercury myur dag
void vendag ( void ); // Venus myur dag

// T4.C: Routines for printing calendars:

void prn_cal ( void );
void prn_plans ( void );
void prn_rahu ( int );
int chk_spec ( int, int );

// T4A.C: Overflow from t4.c

void set_lang ( void );
void zatse_phro ( int *, int *, int, int, int, int );
void chk_tsephro ( char *, int, int, int, int );
void byung_phro ( char *, int, int, int );
void mak_lmchange_string ( int *, int *, int );
int chk_solar_term ( int *, int *, char * );
void get_phrochen ( int *, int, int, int );
int calc_byedpa ( int *, int * );
void gen_phrod ( int, int, int );
int get_tenbrel ( int, int );
void get_bishti_str ( int );
void chk_namgo ( int );

// T4B.C

int chk_sadag ( int, int );
int chk_sadag2 ( int m, int t );

// T5.C:

void prn_cal2 ( int );
void prn_plans2 ( void );
void prn_rahu2 ( int );
void lm2signs ( int *, int *, int *, int * );

// UTILS.C:

void prn_lst6 ( int * );
void prn_lst7 ( int * );
void prn_lstd ( int *, int, int );
void mul_g6 ( int *, int, int, int );
void mul_g7 ( int *, int, int, int, int );
void div_g6 ( int *, int, int, int );
void sub_g6 ( int *, int *, int *, int, int, int );
void add_g6 ( int *, int *, int *, int, int, int );
void add_g7 ( int *, int *, int *, int, int, int,
              int );
void mul_gen ( int *, int *, int, int, int );
int exp_lst ( int *, int );
double conv2degs ( int *, int, int );
double solar_long ( int, double );
double conv2degs1 ( int *, int, int );
void add_gen ( int *, int *, int *, int, int );
void sub_gen ( int *, int *, int *, int, int );
void prn_lst ( int * );
void clrlst ( int * );
void clrlst6 ( int * );
void clear_a_b ( void );
void clear_a_b6 ( void );
void testbcd ( void );

void UTET ( int, int, int, int, int, int, double *, double * );
double AINT ( double );
double get_deltaT ( double );
double modfeh ( double, double );

void cls ( void );
int prfldat ( int, int, int, unsigned char * );
void printat ( int, int, char * );
void start_print ( void );
void prin_str ( char * );
void addstrings ( char *, char * );

// TESTS.C:

void set_errfl ( void );
void wrt_errfl ( void );
void clos_errfl ( void );
void srch_cyc ( void );
