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

// extern
int d_bug;
int full_print;
int cal_print;
int first_run;

int     zladag[2], tt, tm, ty, nyidor, tmth;
int     zlasho1, zlasho2;
int     ltt, ltm, lty;
int     nyidru[], nyilon[], nyibar[], gzadru[], tsedru[], tsebar[];
int     nyiwor[], nyidag[], rilcha[], gzadag[];
int     sun_f_b, gza_f_b;
int     nyidru_b[], nyilon_b[], nyibar_b[];
int     nyiwor_b[], nyidag_b[];
int     nyibarl, tsebarl;
int     nxt_nyidag[], nxt_gzadag[];
int     prv_nyidag[], prv_gzadag[];
int     prv_sbyorlong[6], fst_sbyorlong[6], sbyorlong[6];
int     spz_frac_b, spz_frac_c;
int     nyi_cnt; // Count of days for solar longitude calculation;
int     rahutsa[6], rahudong[6], rahudong30[6], rahujug[6];
int     rahupart; // 230 fraction for Rahu cycle
double rahurealf;
int     zerlst[6];
int     cur_mth;   /*** Current month number, full form ***/
int     cur_tsh;   /*** Current Tithi ***/
int     ch_lh[6];
int     lst_dy, cur_dy;
int  zeromthfg;  // Flag for zero fractional part in month;
int scndzero;  // New flag for zero fractional part of month.
int     spizag, spizag15, spizag30;
int   juldat;  /** Julian day number **/
int   wd, wm, wy;  /** Western dates **/
int   doweek;      // Day of the week
int   epch_yr, eyr_a, ril_a, ril_b;
int  epch;
int  gza_short_flg;
int  gza_f;
int  sun_f;

int    lista[], listb[], listc[];
int    monlong[];
int    prv_monlong[];
int    list1[], list2[], list3[];
int    adj_mth;

int phrodx, phrodx2;
int yan_kwong_flg, zin_phung_flg;
int klu_bzlog_flg, klu_thebs_flg, nyi_nag_flg;

// Planet figures
int meradd;  // Figures to be added for planets for the
int venadd;  // nyin zhag dal ba. These are days of cycle.
int maradd;
int jupadd;
int satadd;
int dragkadd;  // This is added for drag po'iu rkang 'dzin.
int dragkres;  // Result for day in question -- NEW 3/12/2009
int mar_gz, jup_gz, sat_gz, mer_gz, ven_gz; // Particular days.

int merkanbar[];
int merkandag[];

int venkanbar[];
int venkandag[];

int mardalbar[];
int jupdalbar[];
int satdalbar[];

int merdaldag[];
int mermurdag[];
int vendaldag[];
int venmurdag[];
int mardaldag[];
int marmurdag[];
int jupdaldag[];
int jupmurdag[];
int satdaldag[];
int satmurdag[];

// Indices for planetary direction:
int mer_d;
int ven_d;
int mar_d;
int jup_d;
int sat_d;

int ZS_s, ZS_d, ZS_m;  // Zodiac signs, minutes, seconds;

char filenam[];
FILE *fptgt, *fptgt1, *fptgt2;
char outbuf[];
int print_on, printinprog;
char printstring[];

int zhallo[7];
int byedlo[6];
int byedskar[4];
int byedkyon[5];

int cycadd01;

// Floating point data - Tibetan equivalents:
double suntl;
double montl;
double mertl;
double ventl;
double martl;
double juptl;
double sattl;
double rahtl;

// String variables:
char *e_str[];

char *dayoweek[7];
char *dayoweekT[7];
char *lunmanP[27];
char *lunmanT[27];
char *lunmont[12];
char *lunmanS[27];
int lunmanelem[27];
char *fourelem[4];
char *fourelemT[4];
int dowkelem[7];
char *dgaT[5];
char *yogaP[];
char *yogaT[];
char *yogaS[];
char *byedP[];
char *byedT[];
char *byedS[];
char *cycanim[];
char *cycanimT[];
char *cycelem[];
char *cycelem1[];
char *cycelemT[];
char *cycelem1T[];
char *cycgendE[2];
char *cycgendT[2];
char *cycpar[];
char *cycparT[];
char *cycparE[];
char *cycstems[];
char *cycbranch[];
char *Clunman[];
char *ClunmanK[];
char *wmonths[];
char *byungphrod[];
char *phrodchen[];
char *tenbrelT[];
char *plandirT[];
char *plandirE[];
char bishti_str[];
char namgo_str[];
int sadag_str_len;
char sadag_str[];
char sadag_str2[];
