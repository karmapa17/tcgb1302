// t4a.c - routines for calendar symbolic information
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tc.h"
#include "tc.ext"
#include "bcd.h"
#include "bcd.ext"

extern int yan_kwong_flg;
extern int zin_phung_flg;
extern int klu_bzlog_flg;
extern int klu_thebs_flg;
extern int nyi_nag_flg;

extern char gen_phrod_str[];
extern char sreg_str[];
extern char lmchg[];
extern char byungphro_str[];
extern char solar_term_str[];

// Routine to check for special days, festivals, anniversaries, etc.
// Many are currently commented out. Uncomment if needed.
int chk_spec ( int m, int t )
{
    switch ( m )
      {
        case 1:
          if ( t == 1L )
            {
              sprintf ( outbuf, "%s",
                "From 1st to 15th, Demonstration of Miracles." );
              return (1);
            }
//        else if ( t == 14L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Milarepa." );
//            return (1);
//          }
//        else if ( t == 15L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Marpa." );
//            return (1);
//          }
        break;
//      case 2:
//        if ( t == 26L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Taranatha." );
//            return (1);
//          }
//      break;
        case 3:
//        if ( t == 3L )
//          {
//            sprintf ( outbuf, "%s", "Anniversary of Karma Pakshi." );
//            return (1);
//          }
          if ( t == 15L )
            {
              sprintf ( outbuf, "%s", "Revelation of the Kalacakra Tantra." );
              return (1);
            }
        break;
        case 4:
          // 7 for Phugpa, 8 for Tsurphu
          if ( t == 8L )
            {
              sprintf ( outbuf, "%s", "Birth of the Buddha." );
              return (1);
            }
          else if ( t == 15L )
            {
              sprintf ( outbuf, "%s",
                "Enlightenment and Parinirvana of the Buddha." );
              return (1);
            }
//       else if ( t == 29L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Mipham." );
//            return (1);
//          }
        break;
//      case 5:
//        if ( t == 10L )
//          {
//            sprintf ( outbuf, "%s", "Birth of Guru Rinpoche." );
//            return (1);
//          }
//        if ( t == 15L )
//          {
//            sprintf ( outbuf, "%s", "World Local Deities Day." );
//            return (1);
//          }
//      break;
        case 6:
          if ( t == 4L )
            {
              sprintf ( outbuf, "%s", "Turning of the Wheel of the Dharma." );
              return (1);
            }
          else if ( t == 15L )
            {
              sprintf ( outbuf, "%s",
                        "The Buddha's entry into the womb of his mother." );
              return (1);
            }
        break;
//      case 8:
//        if ( t == 19L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Dilgo Khyentse Rinpoche." );
//            return (1);
//          }
//        else if ( t == 23L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Karmapa Mikyo Dorje." );
//            return (1);
//          }
//      break;
        case 9:
//        if ( t == 16L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of 16th Karmapa." );
//            return (1);
//          }
          if ( t == 22L )
            {
              sprintf ( outbuf, "%s",
                "Descent of the Buddha from the realm of the gods." );
              return (1);
            }
        break;
//      case 10:
//        if ( t == 10L )
//          {
//            sprintf ( outbuf, "%s",
//              "White Tara day." );
//            return (1);
//          }
//        else if ( t == 25L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Tshongkhapa." );
//            return (1);
//          }
//      break;
//      case 11:
//        if ( t == 3L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of First Karmapa." );
//            return (1);
//          }
//        else if ( t == 6L )
//          {
//            sprintf ( outbuf, "%s",
//              "Nine bad omens." );
//            return (1);
//          }
//        else if ( t == 7L )
//          {
//            sprintf ( outbuf, "%s",
//              "Ten auspicious omens." );
//            return (1);
//          }
//        else if ( t == 26L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Jamgon Kongtrul." );
//            return (1);
//          }
//        break;
//      case 12:
//        if ( t == 18L )
//          {
//            sprintf ( outbuf, "%s",
//              "Anniversary of Longchen Rabjampa." );
//            return (1);
//          }
//        else if ( t == 29L )
//          {
//            sprintf ( outbuf, "%s",
//              "Mahakala Rituals." );
//            return (1);
//          }
//      break;
        default:
          ;
        break;
      }
//    printf ( "chk_spc, returning zero...\n" );
    return (0);
}

void set_lang ( void )
{
    int i;
/**************
    for ( i = 0; i < 8; ++i )
      cycpar[i] = cycparE[i];
    for ( i = 0; i < 27; ++i )
      lunmanP[i] = lunmanS[i];
    for ( i = 0; i < 27; ++i )
      yogaP[i] = yogaS[i];
    for ( i = 0; i < 11; ++i )
      byedP[i] = byedS[i];
*******************/

/***************/
    for ( i = 0; i < 27; ++i )
      lunmanP[i] = lunmanT[i];
    for ( i = 0; i < 27; ++i )
      yogaP[i] = yogaT[i];
    for ( i = 0; i < 11; ++i )
      byedP[i] = byedT[i];
/**************/
}

int chk_solar_term ( int *gza, int *nyib, char *t_str ) // NOT CURRENTLY USED
//         chk_solar_term ( gzadag, nyibar, solar_term_str );
{
    int sundb1, sundb2; // Mean sun at daybreak, begin and end
    int sunmid;
    int x; //, y;
    int s1, r, s2, s2t, s2t1, s2t2, s2t3;
    int s2long, s2long1, s2long2, s2long3;
    int f; // fraction of day at lunar day. out of 21600
// To nearest dbugs, sun moves 0;4,26,2 -  1598/21600

    f = ( gzadag[1] * 60L + gzadag[2] ) * 6L + gzadag[3];
    sundb1 = (( nyib[0] * 60L + nyib[1] ) * 60L + nyib[2] ) * 6L + nyib[3];
    sunmid = sundb1;
    sundb1 = sundb1 - ( f * 1598L ) / 21600L;
    sundb2 = sundb1 + 1598L;

// Now, find where we are in solar terms. First is actually 3 sgang:

    if ( sundb1 < 11340L )
      sundb1 = sundb1 + 583200L;
    x = sundb1 - 11340L;
    s1 = x / 24300L;
    r = x - ( s1 * 24300L );

    printf ( "Term index = %d, remainder = %d\n", s1, r );

// If index is zero and remainder positive, we have passed "3 sgang"
// It appears that the remainder is never zero.

    if ( sundb2 < 11340L )
      sundb2 = sundb2 + 583200L;
    x = sundb2 - 11340L;
    s2 = x / 24300L;
    r = x - ( s2 * 24300L );

    printf ( "Second term index = %d, remainder = %d\n", s2, r );

// Convert to solar terms, "1 dbugs" = 1, etc.

    s1 = s1 + 6L;
    if ( s1 > 24L )
      s1 = s1 - 24L;
    s2 = s2 + 6L;
    if ( s2 > 24L )
      s2 = s2 - 24L;

    if ( s1 == s2 )
      return (0); // No solar term

// Now, find the time of the term.
// between each solar term, 24300 "dbugs"
// Solar daily motion = 1598 dbugs

    s2long = ( s2 - 6L ) * 24300L + 11340;
    if ( s2long < 0L )
      s2long = s2long + 583200L;
    printf ( "Step 1, S2long = %d\n", s2long );

    if ( s2long < 0L )
      s2long = s2long + 583200L;
    else if ( s2 == 1L )
      s2long = s2long + 583200L;

    if ( sundb1 > s2long ) // It must have been incremented, so do the same:
      s2long = s2long + 583200L;

    s2t = ( 21600L * ( s2long - sundb1 ))/ 1598L;
    s2t2 = s2t / 6L;
    s2t3 = s2t - s2t2 * 6L;
    s2t1 = s2t2 / 60L;
    s2t2 = s2t2 - s2t1 * 60L;

// solar_term_str[60];

    if ( s2long < 0L )
      s2long = s2long + 583200L;
    s2long = ( s2long + 3L ) / 6L;
    s2long2 = s2long / 60L;
    s2long3 = s2long % 60L;
    s2long1 = s2long2 / 60L;
    s2long2 = s2long2 % 60L;

    x = ( 1L + s2 ) / 2L;

    if ( s2 % 2L ) // If index odd, then "dbugs"
      {
        sprintf ( solar_term_str, "%d,%d,%d %d dbugs %d;%d,%d",
                  s2t1, s2t2, s2t3, x, s2long1, s2long2, s2long3 );
      }
    else // "sgang"
      {
        sprintf ( solar_term_str, "%d,%d,%d %d sgang %d;%d,%d",
                  s2t1, s2t2, s2t3, x, s2long1, s2long2, s2long3 );
      }
    return (1); // solar term found
}

void mak_lmchange_string ( int *f_ml, int *s_ml, int dow )
{
    int i;
    int fst_ml[6], scd_ml[6];
    int lm1, lm2, lmx;
    int chga, chgb, nxtlm;

    if ( f_ml[0] == s_ml[0] )
      {
        lmchg[0] = '\0';
        return;
      }

    for ( i = 0; i < 6; ++i )
      {
        fst_ml[i] = f_ml[i];
        scd_ml[i] = s_ml[i];
      }

    nxtlm = scd_ml[0];
    if ( scd_ml[0] == 0L )
      scd_ml[0] = 27L;

    scd_ml[0] = scd_ml[0] - fst_ml[0];
    fst_ml[0] = 0L;

// reduce to "dbugs":

    lm1 = ( fst_ml[1] * 60L + fst_ml[2] ) * 6L + fst_ml[3];
    lm2 = ( ( scd_ml[0] * 60L + scd_ml[1] ) * 60L + scd_ml[2] ) * 6L + scd_ml[3];
    lmx = s_ml[0];

// Time to lunar mansion change:

    chgb = ( 60L * ( 60L * 60L * 6L - lm1 ) ) / ( lm2 - lm1 );
    chga = chgb / 5L;
    chgb = chgb - chga * 5L + 1L;

    get_phrochen ( &phrodx2, dow, lmx, 0L );

    sprintf ( lmchg, "%s gi %d nas %s. %s-%s, %s", cycanimT[chga], chgb, lunmanT[nxtlm], // nxtlm,
               fourelemT[ dowkelem[ dow ]], fourelemT[ lunmanelem[ lmx ]], phrodchen[phrodx2] );
}

int calc_byedpa ( int * mlong, int * ndag )
{
    int byedpa, x;
    clear_a_b ();
    sub_gen ( lista, mlong, ndag, 27L, sun_f ); // AT SUNRISE FOR MOON ONLY
    byedpa = lista[0] * 60 + lista[1];
    byedpa = byedpa / 27;
    if ( byedpa == 0L )
      x = 7;
    else if ( byedpa == 57 )
      x = 8;
    else if ( byedpa == 58 )
      x = 9;
    else if ( byedpa == 59 )
      x = 10;
    else
      x = ( byedpa - 1 ) % 7;
    return ( x );
}

void byung_phro ( char *b_str, int doweek, int lm, int monlong1 )
{ // Could do with another source for these
    *b_str = '\0';
    switch ( doweek ) // This is unfinished, and wrong - there are only ten!!! ???
      {
        case 0L:
          if ( lm == 19L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 14L ) strcat ( b_str, byungphrod[1] );
          if ( lm == 15L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 19L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 24L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 12L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 3L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 1L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 23L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 10L ) strcat ( b_str, byungphrod[10] );
          break;
        case 1L:
          if ( lm == 9L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 18L ) strcat ( b_str, byungphrod[1] );
          if ( lm == 18L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 9L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 3L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 4L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 25L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 15L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 2L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 22L ) strcat ( b_str, byungphrod[10] );
          break;
        case 2L:
          if ( lm == 15L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 21L && monlong1 >= 30L )
            strcat ( b_str, byungphrod[1] ); //second half only
          if ( lm == 22L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 15L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 14L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 17L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 8L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 17L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 11L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 15L ) strcat ( b_str, byungphrod[10] );
          break;
        case 3L:
          if ( lm == 5L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 25L ) strcat ( b_str, byungphrod[1] );
          if ( lm == 25L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 5L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 7L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 2L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 14L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 26L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 8L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 16L ) strcat ( b_str, byungphrod[10] );
          break;
        case 4L:
          if ( lm == 18L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 2L ) strcat ( b_str, byungphrod[1] );
          if ( lm == 2L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 18L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 16L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 19L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 17L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 12L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 19L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 17L ) strcat ( b_str, byungphrod[10] );
          break;
        case 5L:
          if ( lm == 11L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 6L ) strcat ( b_str, byungphrod[1] );
          if ( lm == 7L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 24L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 25L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 23L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 11L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 3L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 4L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 21L && monlong1 < 30L )
            strcat ( b_str, byungphrod[10] );
          break;
        case 6L:
          if ( lm == 3L ) strcat ( b_str, byungphrod[0] );
          if ( lm == 10L ) strcat ( b_str, byungphrod[1] );
          if ( lm == 10L ) strcat ( b_str, byungphrod[2] );
          if ( lm == 3L ) strcat ( b_str, byungphrod[3] );
          if ( lm == 4L ) strcat ( b_str, byungphrod[4] );
          if ( lm == 0L ) strcat ( b_str, byungphrod[5] );
          if ( lm == 2L ) strcat ( b_str, byungphrod[7] );
          if ( lm == 6L ) strcat ( b_str, byungphrod[8] );
          if ( lm == 7L ) strcat ( b_str, byungphrod[9] );
          if ( lm == 3L ) strcat ( b_str, byungphrod[10] );
          break;
      }
}

// VKP, 1,148
void get_phrochen ( int *px, int doweek, int lunmanx, int monlong1 )
{
    int x;
    x = lunmanx;
    if ( x > 21 )
      ++x;
    else if ( x == 21 )
      {
        if ( monlong1 >= 30L )
          x = 22;
      }
    else if ( x > 21 )
      ++x;
    *px = 4 * ( doweek - 1 );
    if ( doweek == 0 )
    *px = 24;
    *px = x - *px;
    if ( *px < 0 )
      *px = *px + 28;
}

void zatse_phro ( int *zapro, int *tsepro, int gza, int tshe, int lm , int monlong1 ) // This is for the five gzaphrod[]
{ // Not finished - still needs work
    *zapro = 0; *tsepro = 0;
    switch ( gza )
      {
        case 0L:
          if ( lm == 3L ) *zapro = 1L;
          else if ( lm == 12L ) *zapro = 2L;
          else if ( lm == 19L ) *zapro = 3L;
          if ( tshe == 6L || tshe == 7L || tshe == 21L || tshe == 22L )
            *tsepro = 1L;
          break;
        case 1L:
          if ( lm == 12L ) *zapro = 1L;
          else if ( lm == 16L ) *zapro = 2L;
          else if ( lm == 9L ) *zapro = 3L;
          if ( tshe == 11L || tshe == 12L || tshe == 26L || tshe == 27L )
            *tsepro = 1L;
          break;
        case 2L:
          if ( lm == 21L && monlong1 < 30L ) *zapro = 1L;  // first half only!
          else if ( lm == 2L ) *zapro = 2L;
          else if ( lm == 15L ) *zapro = 3L;
          if ( tshe == 10L || tshe == 11L || tshe == 25L || tshe == 26L )
            *tsepro = 1L;
          break;
        case 3L:
          if ( lm == 0L ) *zapro = 1L;
          else if ( lm == 23L ) *zapro = 2L;
          else if ( lm == 5L ) *zapro = 3L;
          if ( tshe == 9L || tshe == 10L || tshe == 24L || tshe == 25L )
            *tsepro = 1L;
          break;
        case 4L:
          if ( lm == 16L ) *zapro = 1L;
          else if ( lm == 0L ) *zapro = 2L;
          else if ( lm == 18L ) *zapro = 3L;
          if ( tshe == 2L || tshe == 3L || tshe == 17L || tshe == 18L )
            *tsepro = 1L;
          break;
        case 5L:
          if ( lm == 7L ) *zapro = 1L;
          else if ( lm == 4L ) *zapro = 2L;
          else if ( lm == 22L ) *zapro = 3L;
          if ( tshe == 5L || tshe == 6L || tshe == 20L || tshe == 21L )
            *tsepro = 1L;
          break;
        case 6L:
          if ( lm == 26L ) *zapro = 1L;
          else if ( lm == 3L ) *zapro = 4L;
          if ( tshe == 1L || tshe == 2L || tshe == 16L || tshe == 17L )
            *tsepro = 1L;
          break;
      }
}

void chk_tsephro ( char *str, int phro1, int phro2, int gza1, int gza2 )
{ // sreg_str, tsephro1, tsephro2, gzadag[1], gzadag[2]
    int ts_chga, ts_chgb;
    *str = '\0';
    if ( phro1 == 0L && phro2 == 0L )
      return;

// First get time of lunar day change:

   ts_chgb = gza1;
   if ( gza2 > 30L )
     ++gza1;
   if ( gza1 > 60L )
     gza1 = 60L;
   ts_chga = ts_chgb / 5L;
   ts_chgb = ts_chgb - ts_chga * 5L + 1L;

    if ( phro1 == 1L && phro2 == 0L )
      {
        sprintf ( sreg_str, "sreg tshes %s gi %d bar", cycanimT[ts_chga], ts_chgb );
      }
    else if ( phro1 == 0L && phro2 == 1L )
      {
        sprintf ( sreg_str, "%s gi %d nas sreg tshes", cycanimT[ts_chga], ts_chgb );
      }
    else if ( phro1 == 1L && phro2 == 1L )
      {
        sprintf ( sreg_str, "sreg tshes" );
      }
}

void gen_phrod ( int lm, int dow, int frac )
{
    gen_phrod_str[0] = 0;
    if ( dow == 0 )
      {
        switch ( lm )
          {
            case 3: strcpy ( gen_phrod_str, "'grub sbyor" ); break;
            case 12: strcpy ( gen_phrod_str, "'chi sbyor" ); break;
            case 19: strcpy ( gen_phrod_str, "sreg sbyor zung sbyor" ); break;
            case 22: strcpy ( gen_phrod_str, "bdud nyi" ); break;
            case 14: strcpy ( gen_phrod_str, "bdud rgyal bkris nyi" ); break;
            case 1: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 26: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 10: strcpy ( gen_phrod_str, "mi 'phrod nyi" ); break;
            case 23: strcpy ( gen_phrod_str, "bdud nyi 'phel nyi" ); break;
          }
      }
    else if ( dow == 1 )
      {
        switch ( lm )
          {
            case 12: strcpy ( gen_phrod_str, "'grub sbyor" ); break;
            case 16: strcpy ( gen_phrod_str, "'chi sbyor" ); break;
            case 9: strcpy ( gen_phrod_str, "sreg sbyor zung sbyor" ); break;
            case 2: strcpy ( gen_phrod_str, "bdud nyi" ); break;
            case 18: strcpy ( gen_phrod_str, "bdud rgyal" ); break;
            case 15: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 23: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 17: case 22: strcpy ( gen_phrod_str, "mi 'phrod nyi" ); break;
            case 25: strcpy ( gen_phrod_str, "bkris nyi" ); break;
            case 3: strcpy ( gen_phrod_str, "'phel nyi" ); break;
          }
      }
    else if ( dow == 2 )
      {
        switch ( lm )
          {

            case 20: strcpy ( gen_phrod_str, "'chi sbyor" ); break;
            case 15: strcpy ( gen_phrod_str, "sreg sbyor mi 'phrod nyi" ); break;
            case 11: strcpy ( gen_phrod_str, "bdud nyi" ); break;
            case 21: if ( frac >= 30L ) strcpy ( gen_phrod_str, "'grub sbyor bdud rgyal" );
                     else strcpy ( gen_phrod_str, "'grub sbyor" ); break;
            case 17: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 25: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 10: strcpy ( gen_phrod_str, "zung sbyor" ); break;
            case 8: strcpy ( gen_phrod_str, "bkris nyi" ); break;
            case 14: strcpy ( gen_phrod_str, "'phel nyi" ); break;
          }
      }
    else if ( dow == 3 )
      {
        switch ( lm )
          {
            case 0: strcpy ( gen_phrod_str, "'grub sbyor" ); break;
            case 23: strcpy ( gen_phrod_str, "'chi sbyor" ); break;
            case 5: strcpy ( gen_phrod_str, "sreg sbyor zung sbyor" ); break;
            case 8: strcpy ( gen_phrod_str, "bdud nyi" ); break;
            case 25: strcpy ( gen_phrod_str, "bdud rgyal" ); break;
            case 26: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 24: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 16: strcpy ( gen_phrod_str, "mi 'phrod nyi" ); break;
            case 10: strcpy ( gen_phrod_str, "bkris nyi" ); break;
            case 7: strcpy ( gen_phrod_str, "'phel nyi" ); break;
          }
      }
    else if ( dow == 4 )
      {
        switch ( lm )
          {
            case 16: strcpy ( gen_phrod_str, "'grub sbyor 'phel nyi" ); break;
            case 0: strcpy ( gen_phrod_str, "'chi sbyor" ); break;
            case 18: strcpy ( gen_phrod_str, "sreg sbyor zung sbyor" ); break;
            case 19: strcpy ( gen_phrod_str, "bdud nyi" ); break;
            case 2: strcpy ( gen_phrod_str, "bdud rgyal" ); break;
            case 12: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 1: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 17: strcpy ( gen_phrod_str, "mi 'phrod nyi bkris nyi" ); break;
          }
      }
    else if ( dow == 5 )
      {
        switch ( lm )
          {
            case 7: strcpy ( gen_phrod_str, "'grub sbyor" ); break;
            case 4: strcpy ( gen_phrod_str, "'chi sbyor bdud nyi" ); break;
            case 22: strcpy ( gen_phrod_str, "sreg sbyor" ); break;
            case 6: strcpy ( gen_phrod_str, "bdud rgyal" ); break;
            case 3: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 16: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 21: if (frac<30L) strcpy ( gen_phrod_str, "mi 'phrod nyi" ); break;
            case 10: strcpy ( gen_phrod_str, "zung sbyor" ); break;
            case 11: strcpy ( gen_phrod_str, "bkris nyi" ); break;
            case 25: strcpy ( gen_phrod_str, "'phel nyi" ); break;
          }
      }
    else if ( dow == 6 )
      {
        switch ( lm )
          {
            case 26: strcpy ( gen_phrod_str, "'grub sbyor" ); break;
            case 8: strcpy ( gen_phrod_str, "'chi sbyor" ); break;
            case 3: strcpy ( gen_phrod_str, "sreg sbyor mi 'phrod nyi" ); break;
            case 7: strcpy ( gen_phrod_str, "bdud nyi" ); break;
            case 10: strcpy ( gen_phrod_str, "bdud rgyal" ); break;
            case 6: strcpy ( gen_phrod_str, "'jig nyi" ); break;
            case 9: strcpy ( gen_phrod_str, "mi mthun nyi" ); break;
            case 4: strcpy ( gen_phrod_str, "zung sbyor 'phel nyi" ); break;
            case 2: strcpy ( gen_phrod_str, "bkris nyi" ); break;
          }
      }
}

int get_tenbrel ( int m, int t )
{
    int sx, td;
    sx = m - 12;
    if ( sx < 0 )
      sx = sx + 12;
    if ( t <= 15 )
      {
        if ( t <= 12 )
          td = sx + ( t - 1 );
        else
          td = sx + ( t - 11 );
      }
    else
      {
        if ( t <= 27 )
          td = sx - ( t - 16 );
        else
          td = sx - ( t - 2 );
      }
    while ( td < 0 )
      td = td + 12;
    while ( td > 11 )
      td = td - 12;
    return ( td );
}

void get_bishti_str ( int tt )
{
    bishti_str[0] = 0;
    if ( tt == 4 )
      strcpy ( bishti_str, "bishti E." );
    else if ( tt == 8 )
      strcpy ( bishti_str, "bishti S." );
    else if ( tt == 11 )
      strcpy ( bishti_str, "bishti W." );
    else if ( tt == 15 )
      strcpy ( bishti_str, "bishti N." );
    else if ( tt == 18 )
      strcpy ( bishti_str, "bishti SE." );
    else if ( tt == 22 )
      strcpy ( bishti_str, "bishti SW." );
    else if ( tt == 25 )
      strcpy ( bishti_str, "bishti NW." );
    else if ( tt == 29 )
      strcpy ( bishti_str, "bishti NE." );
}

void chk_namgo ( int tt ) // n
{
    namgo_str[0] = 0;
    if ( tt == 1 || tt == 11 || tt == 21 )
      strcpy ( namgo_str, "mgron" );
    else if ( tt == 2 || tt == 12 || tt == 22 )
      strcpy ( namgo_str, "tshong" );
    else if ( tt == 3 || tt == 13 || tt == 23 )
      strcpy ( namgo_str, "bu" );
    else if ( tt == 4 || tt == 14 || tt == 24 )
      strcpy ( namgo_str, "dmag" );
    else if ( tt == 5 || tt == 15 || tt == 25 )
      strcpy ( namgo_str, "gnyen" );
    else if ( tt == 6 || tt == 16 || tt == 26 )
      strcpy ( namgo_str, "mkhar" );
    else if ( tt == 7 || tt == 17 || tt == 27 )
      strcpy ( namgo_str, "bag" );
    else if ( tt == 8 || tt == 18 || tt == 28 )
      strcpy ( namgo_str, "dur" );
    else if ( tt == 9 || tt == 19 || tt == 29 )
      strcpy ( namgo_str, "shid" );
    else if ( tt == 10 || tt == 20 || tt == 30 )
      strcpy ( namgo_str, "spyi" );
}
