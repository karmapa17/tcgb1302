// t2.c - main routines for "grub rtsis", include epoch data

/*********************************************************************************
Licence for TCGBK - Tsurphu Calendar software for "grub & byed rtsis"

Copyright (c) 2009-2013 Edward Henning

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in the
Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so, subject
to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
************************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include "tc.h"
#include "tc.ext"
#include "bcd.h"
#include "bcd.ext"

// Local to this file only:

int  spz_c, spz_b, spz_f, spz_j;

int gzada[6];
int nyida[6];
int nyidm[6], gzadm[6], tsedm[6], nyilm[6];

int nyidmg[6] = { 2, 10, 58, 1, 17, 0 };
int gzadmg[6] = { 1, 31, 50, 0, 480, 0 };
int tsedmg[6] = { 0, 59, 3, 4, 16, 0 };
int nyilmg[6] = { 0, 4, 21, 5, 43, 0 }; // Each lunar day

int nyifac[6] = { 6, 45, 0, 0, 0, 0 };
int nyihaf[6] = { 13, 30, 0, 0, 0, 0 };
int nyibye[6] = { 4, 1, 1, 4, 6, 6};
int nyidom[6] = { 6, 10, 11, 10, 6, 0};

static int gzabye[14] = { 5, 5, 4, 3, 2, 1, -1, -2, -3,
                                                  -4, -5, -5, -5, 5};
static int gzadom[14] = { 5, 10, 15, 19, 22, 24, 25, 24, 22,
                                                   19, 15, 10, 5, 0};
                                                   
/**** Figures for Kongtrul Tshurphu epoch, year 1852 ****/

static int gda1[6] = { 2, 9, 24, 2, 304, 0 }; // OK
static int nda1[6] = { 0, 1, 22, 2, 22, 0 }; // OK

/**** Figures for Tantra epoch, year 806 ****/

static int gda2[6] = { 2, 25, 20, 2, 352, 0 }; // OK
static int nda2[6] = { 0, 29, 34, 5, 37, 0 }; // OK

// Routine to set main values for "grub rtsia":
// Equivalent "byed rtsis" routine removed

void set_grub ( void )
  {
    int  i;
    for ( i = 0; i < 6; ++i )
      nyidm[i] = nyidmg[i];
    for ( i = 0; i < 6; ++i )
      gzadm[i] = gzadmg[i];
    for ( i = 0; i < 6; ++i )
      tsedm[i] = tsedmg[i];
    for ( i = 0; i < 6; ++i )
      nyilm[i] = nyilmg[i];
    sun_f = 67;
    gza_f = 707;
  } // END - set_grub ()

// Routine to set epoch parameters

void set_epoch ( void )
  {
    char chr;
    int  i;

    epch = 1; // Set for default epoch, 1852
    if ( first_run )
      goto firstjump;

    printf ( "\n\nSelect from the following:\n\n" );
    printf ( "%s\n", e_str[0] );    
    printf ( "%s\n", e_str[1] );        

    do
      chr = getch ();
    while ( chr < '1' || chr > '2' );
    if ( chr >= '1' && chr <= '9' )
      epch = chr - '0';    
   
firstjump: 

    set_grub ();

    if ( epch == 1 ) // Kongtrul epoch
      {    
        for ( i = 0; i < 6; ++i )
          gzada[i] = gda1[i];
        for ( i = 0; i < 6; ++i )
          nyida[i] = nda1[i];
        epch_yr = 1852;
        eyr_a = 14;   // Intercalation index
        ril_a = 0; // OK
        ril_b = 72; // OK
        spz_b = 15;   // 64 fraction - OK
        spz_c = 704;   // 707 fraction - OK
        spz_f = 2;    // OK
        spz_j = 2397598;  // OK
        rahupart = 180; // 230 fraction for Rahu cycle // OK
        meradd = 3003; // OK
        venadd = 686; // OK
        maradd = 262; // OK
        jupadd = 2583; // OK
        satadd = 437; // OK
        dragkadd = 83343;    
      }
    else if ( epch == 2 ) // Tantra epoch, 806
      {    
        for ( i = 0; i < 6; ++i )
          gzada[i] = gda2[i];
        for ( i = 0; i < 6; ++i )
          nyida[i] = nda2[i];
        epch_yr = 806;
        eyr_a = 0;   // Intercalation index
        ril_a = 5; // OK
        ril_b = 112; // OK
        spz_b = 0;   // 64 fraction - OK
        spz_c = 0;   // 707 fraction - OK
        spz_f = 2;    // OK
        spz_j = 2015531;  // OK
        rahupart = 122; // 230 fraction for Rahu cycle // OK
        meradd = 1674; // OK
        venadd = 2163; // OK
        maradd = 167; // OK
        jupadd = 1732; // OK
        satadd = 5946; // OK
        dragkadd = 179201;
      }    
    set_epoch_b ();        
  } // END - set_epoch ()

// ROUTINE TO CALCULATE POSITIONS OF RAHU

void do_rahu ( int m, int tt ) // KTC 96
  {
    int t, mth;

    mth = ( m + rahupart ) % 230;
    t = ( ( m + rahupart ) % 230 ) * 30 + 15;
    rahutsa[0] = 0;
    rahutsa[1] = 0;
    rahutsa[2] = 14;
    rahutsa[3] = 0;
    rahutsa[4] = 12;

    mul_gen ( rahutsa, rahutsa, t, 27, 23 );
    clear_a_b ();
    lista[0] = 27;
    sub_gen ( rahudong, lista, rahutsa, 27, 23 );
    listb[0] = 13;
    listb[1] = 30;
    add_gen ( rahujug, rahudong, listb, 27, 23 );

    rahutsa[0] = 0;
    rahutsa[1] = 0;
    rahutsa[2] = 14;
    rahutsa[3] = 0;
    rahutsa[4] = 12;
    mul_gen ( rahutsa, rahutsa, t + 15, 27, 23 ); // For new Moon.
    clear_a_b ();
    lista[0] = 27;
    sub_gen ( rahudong30, lista, rahutsa, 27, 23 );
    listb[0] = 13;
    listb[1] = 30;
    add_gen ( rahujug, rahudong, listb, 27, 23 );

    sprintf ( printstring,
    "Rahu month: %d, gdong, 15th: %d;%d,%d,%d,%d - 30th: %d;%d,%d,%d,%d",
      mth, rahudong[0], rahudong[1], rahudong[2], rahudong[3], rahudong[4],
      rahudong30[0], rahudong30[1], rahudong30[2], rahudong30[3], rahudong30[4] );
    if ( printinprog )
      prin_str ( printstring );
  } // END - do_rahu ()

// Function to calculate true month, "zla ba rnam par dag pa"
void zla_dag ( int y, int m ) // KTC 15
  {
    int   yr, a, b; // c;
    yr = y - epch_yr;
    a = 12 * yr + m - 3;
    if ( a >= 0 )
      {
        b = 2 * a + eyr_a;
        zladag[1] = b % 65;
        zladag[0] = a + b / 65;
      }
    else
      {
        zladag[1] = 0;
        zladag[0] = 0;
      }
  } // END - zla_dag ()

// Adjust month number, if needed
void adj_zla ( void )
  {
    if ( zladag[1] == 0 || zladag[1] == 1 )
      {
        if ( !zeromthfg )
          {
            zeromthfg = 1;
            adj_mth = -tm;
            zladag[0] = zladag[0] - 1;
          }
        else
          {
            zeromthfg = 0;
            adj_mth = tm;
            zladag[0] = zladag[0] + 1;
          }
      }
    else
      {
        adj_mth = tm;
        if ( adj_mth == 0 )
          adj_mth = 12;
      }
  } // END - adj_zla ()

// Function to calculate lunar anomaly, "ril cha"
void rilchaf ( int x ) // KTC 21
  {
    int   a, b;
    b = x + ril_b;
    a = 2 * x + ril_a + b / 126;
    rilcha[1] = b % 126;
    rilcha[0] = a % 28;
  } // END - void rilchaf ( int x )

// Function to calculate general day, "spyi zhag"
// Calculates Julian for the integer Julian day count at noon UT
// on weekday of "gza' dag". Put into juldat.
void spi_zagf ( void ) // KTC 46
  {
    int b, c;
    spizag = cur_mth * 30 + tt;
    c = spizag + spz_c;
    spz_frac_c = c % 707;
    b = spizag + spz_b;
    b = b + c / 707;
    spz_frac_b = b % 64;
    spizag = spizag - b / 64;
    c = ( spizag + spz_f ) % 7;
    b = gzadag[0];
    if ( c != b )
      {
        if ( c > 4 && b < 2 )
          b += 7;
        else if ( b > 4 && c < 2 )
          c += 7;
        spizag = spizag + b - c;
      }
    if ( b - c > 2 )
      {
        printf ( "\n2 - ERROR IN GENERAL DAY ROUTINE: %d\n", b - c );
        getch ();
      }
    juldat = spizag + spz_j;
    jul2date ( juldat );
  } // END - spi_zagf ();

int gregd2jul ( int D, int M, int Y )
{
  int JD;
  int calndar;  // Gregorian = 1.

// In change from Julian to Gregorian calendars, in 1582, Oct 4th was followed
// by Oct 15th

  if ( Y > 1582 )
    calndar = 1;
  else if ( Y < 1582 )
    calndar = 0;
  else
    {
      if ( M > 10 )
        calndar = 1;
      else if ( M < 10 )
        calndar = 0;
      else
        {
          if ( D >= 15 )
            calndar = 1;
          else
            calndar = 0;
        }
    }
  if ( calndar )  // Gregorian:
    {
// The following is from ESAA, 1992, p. 604.

  JD = D + ( 1461 * ( Y + 4800 + ( M - 14 ) / 12 ) ) / 4
         + ( 367 * ( M - 2 - 12 * ( ( M - 14 ) / 12 ) ) ) / 12
         - ( 3 * ( ( Y + 4900 + ( M - 14 ) / 12 ) / 100 ) ) / 4 - 32075;

    }
  else  // Julian:
    {
      JD = 367 * Y - ( 7 * ( Y + 5001 + ( M - 9 ) / 7 )) / 4
           + ( 275 * M ) / 9 + D + 1729777;
    }

  return ( JD );
} // END - gregd2jul ()

void jul2date ( int jd )
  {
    int l, n, j, k, i;

// This algorithm is from photcopied notes, from James Neely.
// Also, checked with ESAA, 1992, p. 604
// Calculates date, at noon on which the Julian date starts.
// Julian 0 starts Greenwich mean noon on 1st Jan 4713 BC, Julian proleptic
// calendar.
// In change from Julian to Gregorian calendars, in 1582, Oct 4th was followed
// by Oct 15th

// First, get day of week:

  doweek = jd - 7 * (( jd + 1 ) / 7 ) + 2;
  if ( doweek == 7 )
    doweek = 0;
  if ( doweek > 7 )
    {
      printf ( "ERROR IN DAY OF WEEK ROUTINE:\n" );
      getch ();
    }

  if ( jd >= 2299161 )  // Gregorian calendar:
    { // This has been tested between March 1, 1600 and Jan 31, 2100
    l = jd + 68569;
    n = ( 4 * l ) / 146097;
    l = l - ( 146097 * n + 3 ) / 4;

//  wy = 4000L * ( l + 1L ) / 1461001L;

    l2bcd ( bcda, 4000 );
    mulbcdl ( bcda, bcda, l + 1 );
    divbcdl ( bcda, bcda, 1461001 );
    wy = bcd2l ( bcda );

    l = l - ( 1461 * wy ) / 4 + 31;
    wm = ( 80 * l ) / 2447;
    wd = l - ( 2447 * wm ) / 80;
    l = wm / 11;
    wm = wm + 2 - 12 * l;
    wy = 100 * ( n - 49 ) + wy + l;
// j = month, k = day, i = year
    }
  else // Julian calendar
    {
      j = jd + 1402;
      k = ( j - 1 ) / 1461;
      l = j - 1461 * k;
      n = ( l - 1 ) / 365 - l / 1461;
      i = l - 365 * n + 30;
      j = ( 80 * i ) / 2447;
      wd = i - ( 2447 * j ) / 80;
      i = j / 11;
      wm = j + 2 - 12 * i;
      wy = 4 * k + n + i - 4716;
    }
  } // END - jul2date ()

// Function to calculate month mean Sun, "nyi ma'i dhru ba".
void nyi_dru ( int x )
  {
    mul_gen ( nyidru, nyidm, x, 27, sun_f );
    add_gen ( nyidru, nyidru, nyida, 27, sun_f );
  } // END - nyi_dru ()

// Function to calculate month mean weekday, "gza'i dhru ba".

void gza_dru ( int x )
  {
    mul_gen ( gzadru, gzadm, x, 7, gza_f );
    add_gen ( gzadru, gzadru, gzada, 7, gza_f );
  } // END - gza_dru ()

// Function to calculate lunar day solar longitude, "nyi ma'i longs spyod".
void nyi_lon ( int x )
  {
    mul_gen ( nyilon, nyilm, x, 27, sun_f );
  } // END - nyi_lon ()

// Function to calculate lunar day mean weekday, "tshes kyi dhru ba".
void tse_dru ( int x )
  {
    mul_gen ( tsedru, tsedm, x, 7, gza_f );
  } // END - tse_dru ()

// Function to calculate true solar longitude, "nyi dag".
void nyi_dag ( int *a1 )
  {
    int test, tquo, trem;

    sub_gen ( nyiwor, a1, nyifac, 27, sun_f ); // KTC 31
    test = 60 * nyiwor[0] + nyiwor[1];
    if ( test < 810 )
      nyidor = 0;
    else
      {
        nyidor = 1;
        sub_gen ( nyiwor, nyiwor, nyihaf, 27, sun_f);
        test = 60 * nyiwor[0] + nyiwor[1];
      }
    trem = test % 135;
    tquo = test / 135;
    if ( tquo == 0 )
      tquo = 6;

    clear_a_b ();

    lista[2] = ( trem * 60 + nyiwor[2] ) * nyibye[tquo - 1];
    lista[3] = nyiwor[3] * nyibye[tquo - 1];
    lista[4] = nyiwor[4] * nyibye[tquo - 1];

    div_g6 ( lista, 135, sun_f, 1 );

    clrlst (zerlst);
    add_gen ( lista, zerlst, lista, 27, sun_f );

    listb[1] = nyidom[tquo - 1];
    if ( tquo == 3 || tquo == 4 || tquo == 5 ) // Then, subtract:
      sub_gen ( listc, listb, lista, 27, sun_f );
    else
      add_gen ( listc, listb, lista, 27, sun_f );

    if ( nyidor == 0 )
      sub_gen ( nyidag, a1, listc, 27, sun_f );
    else
      add_gen ( nyidag, a1, listc, 27, sun_f );
  } // END - nyi_dag ()

// Function to calculate true weekday, "gza' dag".
void gza_dag ( int *a1 )
  {
    int tot, trem, chasha, rilpo;
    int gzawor[5];

    clrlst (list1);
    clrlst (list2);
    clrlst (zerlst);
    rilpo = rilcha[0] + tt;
    trem = rilpo % 14;
    if ( trem == 0 )
      trem = 14;
    list2[1] = gzadom[trem - 1];
    gza_short_flg = 0; // KTC 26  --- debug
    if ( gza_short_flg ) // Flag for less accurate weekday adjustment
      {
        chasha = rilcha[1] * gzabye[trem - 1] * 254520; //60*6*707
        // Maximum value = 125 * 5 * 254520 = 159075000 - OK
        tot = chasha / 126;
      }
    else
      {
        l2bcd ( bcda, ( 30 * rilcha[1] + tt ) * gzabye[trem - 1] );
        mulbcdl ( bcda, bcda, 360 * gza_f );
        divbcdl ( bcda, bcda, 3780 );
        tot = bcd2l (bcda);
      }
    if ( tot < 0 ) // KTC 24
      {
        list1[4] = -tot;
        add_gen ( list1, list1, zerlst, 7, gza_f );
        sub_gen ( list3, list2, list1, 7, gza_f );
      }
    else
      {
        list1[4] = tot;
        add_gen ( list1, list1, zerlst, 7, gza_f );
        add_gen ( list3, list2, list1, 7, gza_f );
      }
    if (( rilpo / 14 ) % 2 == 0 )  // For the semi-true weekday // More debug code:
      {
        add_gen ( gzawor, a1, list3, 7, gza_f);
      }
    else
      {
        sub_gen ( gzawor, a1, list3, 7, gza_f);
      }

    l2bcd ( bcda, gzawor[4] );
    mulbcdl ( bcda, bcda, sun_f_b );    
    divbcdl ( bcda, bcda, gza_f );
    gzawor[4] = bcd2l ( bcda );

//  The above replaces:
//  gzawor[4] = ( sun_f * gzawor[4] ) / gza_f;

    if ( nyidor == 0 )
      sub_gen ( gzadag, gzawor, listc, 7, sun_f_b );
    else
      add_gen ( gzadag, gzawor, listc, 7, sun_f_b );

// Convert back the lowest fractional part:

    l2bcd ( bcda, gzadag[4] );
    mulbcdl ( bcda, bcda, gza_f );
    divbcdl ( bcda, bcda, sun_f_b );
    gzadag[4] = bcd2l ( bcda );
  } // END - gza_dag ()
  