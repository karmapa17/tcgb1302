// t2a.c - "byed rtsis" routines

int epch_mth_b, ical_ind_b;

extern int nyifac[]; 
extern int print_on, printinprog;
extern char printstring[120];
void start_print ( void );
void prin_str ( char * );
void addstrings ( char *, char * );

// Local to this file only:

int sol_cor[6];
int gzadab[6];
int nyidab[6];
// long int nyidm[6], gzadm[6], tsedm[6], nyilm[6];

static int nyidmb[6] = { 2, 10, 58, 2, 10, 0 };
static int gzadmb[6] = { 1, 31, 50, 0, 0, 0 };
static int tsedmb[6] = { 0, 59, 3, 4, 0, 0 };
static int nyilmb[6] = { 0, 4, 21, 5, 9, 0 };

/**** Figures for Kongtrul Epoch: Monday 19th April 1852. Julian day: 2397598 ****/

static int gdab1[6] = { 1, 49, 40, 0, 0, 0 };  
static int ndab1[6] = { 0, 24, 15, 2, 4, 0 };  

/**** Figures for original Tantra epoch, byed rtsis (1) ****/

static long int gdab2[6] = { 2, 30, 0, 0, 0, 0 };
static long int ndab2[6] = { 26, 58, 0, 0, 0, 0 };

/*** ROUTINE TO SET FOR BYED RTSIS ****/

void set_byed ( void )
  {
    sun_f_b = 13L;
    gza_f_b = 13L;   // This is correct for "byed rtsis", compatible with Sun 
  } // END - set_byed ()

/*** ROUTINE TO SET EPOCH PARAMETERS ****/

void set_epoch_b ( void )
  {
    int  i;
    set_byed ();
    if ( epch == 1 ) // Kongtrul
      {
        for ( i = 0; i < 6; ++i )
          gzadab[i] = gdab1[i];
        for ( i = 0; i < 6; ++i )
          nyidab[i] = ndab1[i];
        ical_ind_b = 14L;  // Intercalation index          
      }
    else if ( epch == 2 ) // Tantra
      {
        for ( i = 0; i < 6; ++i )
          gzadab[i] = gdab2[i];
        for ( i = 0; i < 6; ++i )
          nyidab[i] = ndab2[i];
        ical_ind_b = 0L;  // Intercalation index               
      }    
    epch_mth_b = 2L;
    dragkadd = 758L; // Not needed now
  } // END - set_epoch_b ()

// Function to calculate anomaly, "ril cha"
void rilchaf_b ( int x )
  {
    int   a, b;
    b = x + ril_b;
    a = 2L * x + ril_a + b / 126L;
    rilcha[1] = b % 126L;
    rilcha[0] = a % 28L;
  } // END - void rilchaf_b ( int x )

// Function to calculate monthly mean Sun, "nyi ma'i dhru ba".
void nyi_dru_b ( int x )
  {
    mul_gen ( nyidru_b, nyidmb, x, 27L, sun_f_b );
    add_gen ( nyidru_b, nyidru_b, nyidab, 27L, sun_f_b );
  } // END - nyi_dru_b ()

// Function to calculate monthly mean weekday, "gza'i dhru ba". 
void gza_dru_b ( int x )
  {
    mul_gen ( gzadru, gzadmb, x, 7L, gza_f );
    add_gen ( gzadru, gzadru, gzadab, 7L, gza_f );
  } // END - gza_dru_b ()

// Calculate solar longitude from beginning of month 
void nyi_lon_b ( int x )
  {
    mul_gen ( nyilon_b, nyilmb, x, 27L, sun_f_b );
  } // END - nyi_lon_b ()

// Calculate weekday change from beginning of month, "tshes kyi dhru ba"
void tse_dru_b ( int x )
  {
    mul_gen ( tsedru, tsedmb, x, 7L, gza_f );
  } // END - tse_dru_b ()

// Calculate true solar longitude, "nyi dag". 
void nyi_dag_b ( int *a1 )
  {
    int test, tquo, trem;

    clrlst (zerlst);
    sub_gen ( nyiwor_b, a1, nyifac, 27L, sun_f_b );
    test = 60L * nyiwor_b[0] + nyiwor_b[1];
    if ( test < 810L )
      nyidor = 0;
    else
      {
        nyidor = 1;
        sub_gen ( nyiwor_b, nyiwor_b, nyihaf, 27L, sun_f_b);
        test = 60L * nyiwor_b[0] + nyiwor_b[1];
      }
    trem = test % 135; // Interpolation variable
    tquo = test / 135; // Index for table
    if ( tquo == 0 )
      tquo = 6;

    clear_a_b ();

    lista[2] = ( trem * 60L + nyiwor_b[2] ) * nyibye[tquo - 1];
    lista[3] = nyiwor_b[3] * nyibye[tquo - 1];
    lista[4] = nyiwor_b[4] * nyibye[tquo - 1];

    div_g6 ( lista, 135L, sun_f_b, 1L );

    clrlst (zerlst);
    add_gen ( lista, zerlst, lista, 27L, sun_f_b );

    listb[1] = nyidom[tquo - 1];
    if ( tquo == 3L || tquo == 4L || tquo == 5L ) // Then, subtract:
      sub_gen ( listc, listb, lista, 27L, sun_f_b );
    else
      add_gen ( listc, listb, lista, 27L, sun_f_b );

    if ( nyidor == 0 )
      sub_gen ( nyidag_b, a1, listc, 27L, sun_f_b );
    else
      add_gen ( nyidag_b, a1, listc, 27L, sun_f_b );
  } // END - nyi_dag_b ()

// Function to calculate true weekday, "gza' dag"

void gza_dag_b ( int *a1 )
  {
    int tot, trem, chasha, rilpo;
    int gzawor[5];

    clrlst (list1);
    clrlst (list2);
    clrlst (zerlst);
    rilpo = rilcha[0] + tt; // Index into table
    trem = rilpo % 14;  // Interpolation variable
    if ( trem == 0 )
      trem = 14;
    list2[1] = gzadom[trem - 1];
    gza_short_flg = 0;
    if ( gza_short_flg ) // Flag for less accurate weekday adjustment	
			 // This is more compatible with the Tantra method		 
      {			 // See also in TC.DEF and TC4.C
        chasha = rilcha[1] * gzabye[trem - 1] * 360L * gza_f; 
       // Maximum value = 125 * 5 * 254520 = 159075000 - OK
        tot = chasha / 126L;
      }
    else // This is more normal in Tibetan systems,
      {  // but not described in the original Tantra
        l2bcd ( bcda, ( 30L * rilcha[1] + tt ) * gzabye[trem - 1] );
        mulbcdl ( bcda, bcda, 360L * gza_f );
        divbcdl ( bcda, bcda, 3780L );
        tot = bcd2l (bcda);
      }
    if ( tot < 0 )
      {
        list1[4] = -tot;
        add_gen ( list1, list1, zerlst, 7L, gza_f );
        sub_gen ( list3, list2, list1, 7L, gza_f );
      }
    else
      {
        list1[4] = tot;
        add_gen ( list1, list1, zerlst, 7L, gza_f );
        add_gen ( list3, list2, list1, 7L, gza_f );
      }

    if (( rilpo / 14 ) % 2 == 0 )
      add_gen ( gzawor, a1, list3, 7L, gza_f);
    else
      sub_gen ( gzawor, a1, list3, 7L, gza_f);

    if ( nyidor == 0 ) // Solar correction now is applied:
      sub_gen ( gzadag, gzawor, sol_cor, 7L, sun_f_b );
    else
      add_gen ( gzadag, gzawor, sol_cor, 7L, sun_f_b );
  } // END - gza_dag_b ()
  
