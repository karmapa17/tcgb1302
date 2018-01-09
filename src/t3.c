// t3.c - Planetary routines
/*********************************************************************************
Licence for TCGBK - Tsurphu Calendar software for "grub & byed rtsis"

Copyright (c) 2009-2013 Edward Henning

Permission is hereby granted, free of charge, to any person  obtaining a copy of
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
#include "tc.h"
#include "tc.ext"
#include "bcd.h"
#include "bcd.ext"

int rkang_frac;

static int merbye1[14] =
              {16, 15, 14, 13, 11, 7, 5, 0, 4, 11, 20, 28, 34, 16};
static int merbye2[14] =
              {28, 20, 11, 4, 0, 5, 7, 11, 13, 14, 15, 16, 16, 34};
static int merdom1[14] =
              {16, 32, 47, 61, 74, 85, 92, 97, 97, 93, 82, 62, 34, 0};
static int merdom2[14] =
              {34, 62, 82, 93, 97, 97, 92, 85, 74, 61, 47, 32, 16, 0};
static int venbye1[14] =
              {25, 25, 24, 24, 22, 22, 18, 15, 8, 6, 30, 99, 73, 25};
static int venbye2[14] =
              {99, 30, 6, 8, 15, 18, 22, 22, 24, 24, 25, 25, 25, 73};
static int vendom1[14] =
              {25, 50, 75, 99, 123, 145, 167, 185, 200, 208, 202, 172, 73, 0};
static int vendom2[14] =
              {73, 172, 202, 208, 200, 185, 167, 145, 123, 99, 75, 50, 25, 0};
static int marbye1[14] =
              {23, 23, 23, 21, 21, 18, 15, 11, 3, 11, 38, 80, 53, 24};
static int marbye2[14] =
              {80, 38, 11, 3, 11, 15, 18, 21, 21, 23, 23, 23, 24, 53};
static int mardom1[14] =
              {24, 47, 70, 93, 114, 135, 153, 168, 179, 182, 171, 133, 53, 0};
static int mardom2[14] =
              {53, 133, 171, 182, 179, 168, 153, 135, 114, 93, 70, 47, 24, 0};
static int jupbye1[14] =
              {10, 9, 8, 6, 6, 2, 1, 3, 6, 9, 11, 16, 7, 10};
static int jupbye2[14] =
              {16, 11, 9, 6, 3, 1, 2, 6, 6, 8, 9, 10, 10, 7};
static int jupdom1[14] =
              {10, 20, 29, 37, 43, 49, 51, 52, 49, 43, 34, 23, 7, 0};
static int jupdom2[14] =
              {7, 23, 34, 43, 49, 52, 51, 49, 43, 37, 29, 20, 10, 0};
static int satbye1[14] =
              {5, 5, 4, 4, 2, 2, 0, 2, 4, 5, 6, 8, 3, 6};
static int satbye2[14] =
              {8, 6, 5, 4, 2, 0, 2, 2, 4, 4, 5, 5, 6, 3};
static int satdom1[14] =
              {6, 11, 16, 20, 24, 26, 28, 28, 26, 22, 17, 11, 3, 0};
static int satdom2[14] =
              {3, 11, 17, 22, 26, 28, 28, 26, 24, 20, 16, 11, 6, 0};

static int plahaf[6] = {13,30,0,0,0,0};
static int merfac[5] = {16, 30, 0, 0, 0};
static int merbye[6] = {7,3,3,7,10,10};
static int merdom[6] = {10,17,20,17,10,0};
static int venfac[5] = {6, 0, 0, 0, 0};
static int venbye[6] = {4,1,1,4,5,5};
static int vendom[6] = {5,9,10,9,5,0};
static int marfac[5] = {9, 30, 0, 0, 0};
static int marbye[6] = {18,7,7,18,25,25};
static int mardom[6] = {25,43,50,43,25,0};
static int jupfac[5] = {12, 0, 0, 0, 0};
static int jupbye[6] = {9,3,3,9,11,11};
static int jupdom[6] = {11,20,23,20,11,0};
static int satfac[5] = {18, 0, 0, 0, 0};
static int satbye[6] = {15,6,6,15,22,22};
static int satdom[6] = {22,37,43,37,22,0};

// Periods of the planets, solar days

int mercyc = 8797L; 
int vencyc = 2247L;
int marcyc = 687L;
int jupcyc = 4332L;
int satcyc = 10766L;

// least significant radix:

int merfrac = 8797L;   
int venfrac = 749L;    
int marfrac = 229L;    
int jupfrac = 361L;
int satfrac = 5383L;

int dragkang[6];
int dragk[6];
int dald[6];
int nyindhru[6];

void clear_lowera (void);

//void clear_lowera (void) // This is only used for testing purposes now.
//  {
//    return;  // Tibetan methods use the full value.
//    lista[2] = 0L;
//    lista[3] = 0L;
//    lista[4] = 0L;
//    lista[5] = 0L;
//  }

void calc_dalbar ( int lst[5], int dat, int cyc,
                   int frac )
  {
    lst[0] = dat * 27L;
    lst[1] = 0L;
    lst[2] = 0L;
    lst[3] = 0L;
    lst[4] = 0L;
    lst[5] = 0L;
    div_g6 ( lst, cyc, frac, 1L );
  } // END - calc_dalbar ()

void do_daldag ( int pdaldag[], int pdalbar[], int pfac[],
                 int pbye[6], int pdom[6], int frac )
  {
    int dortst, test, trem, tquo;
    
    clear_a_b ();
    sub_gen ( lista, pdalbar, pfac, 27L, frac );
    test = lista[0] * 60L + lista[1];
    if ( test >= 13L * 60L + 30L )
      {
        dortst = 1L;         // Subtract half-circle - KTC 59
        test = test - 13L * 60L - 30L;
      }
    else
      dortst = 0L;           // No subtraction of half-circle

    clear_a_b ();
    trem = test % 135L;
    tquo = test / 135L;
    if ( tquo == 0 )
      tquo = 6;
    lista[0] = 0L;
    lista[1] = trem;
    lista[2] = pdalbar[2];
    lista[3] = pdalbar[3];
    lista[4] = pdalbar[4];
    lista[5] = 0L;
  
    mul_g6 ( lista, pbye[tquo - 1], frac, 1L );
    div_g6 ( lista, 135L, frac, 1L );

    listb[1] = pdom[tquo - 1];

// tquo is equal to actual index, except 0, replaced by 6

    if ( tquo == 3L || tquo == 4L || tquo == 5L ) // Then, subtract:
      sub_gen ( listc, listb, lista, 27L, frac );
    else
      add_gen ( listc, listb, lista, 27L, frac );

    if ( dortst == 0L )
      sub_gen ( pdaldag, pdalbar, listc, 27L, frac );
    else
      add_gen ( pdaldag, pdalbar, listc, 27L, frac );
  } // END - do_daldag ()

void do_plans ( int sz ) 
  {
    int i;

// MARS, DAL DAG. - KTC 57
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 623

    mar_gz = sz + maradd;
    mar_gz = mar_gz % 687L;
    calc_dalbar ( mardalbar, mar_gz, 687L, 229L );
    martl = conv2degs ( mardalbar, 229L, 1L );
    do_daldag ( mardaldag, mardalbar, marfac, marbye, mardom, 229L );

// JUPITER, DAL DAG. - KTC 61
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 625

    jup_gz = sz + jupadd;
    jup_gz = jup_gz % 4332L;
    calc_dalbar ( jupdalbar, jup_gz, 4332L, 361L );
    juptl = conv2degs ( jupdalbar, 361L, 1L );
    do_daldag ( jupdaldag, jupdalbar, jupfac, jupbye, jupdom, 361L );

// SATURN, DAL DAG. - KTC 61
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 633

    sat_gz = sz + satadd;
    sat_gz = sat_gz % 10766L;
    calc_dalbar ( satdalbar, sat_gz, 10766L, 5383L );
    sattl = conv2degs ( satdalbar, 5383L, 1L );
    do_daldag ( satdaldag, satdalbar, satfac, satbye, satdom, 5383L );

// MERCURY, RKANG BAR, - KTC 85
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 610

    mer_gz = sz * 100L + meradd;
    mer_gz = mer_gz % 8797L;
    calc_dalbar ( merkanbar, mer_gz, 8797L, 8797L );
    mertl = conv2degs ( merkanbar, 8797L, 1L );

// VENUS, RKANG BAR, - KTC 77
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 612

    ven_gz = sz * 10L + venadd;
    ven_gz = ven_gz % 2247L;
    calc_dalbar ( venkanbar, ven_gz, 2247L, 749L );
    ventl = conv2degs ( venkanbar, 749L, 1L );
  
// For Tsurphu system only:

        rkang_frac = 13L; 
        for ( i = 0; i < 5; ++i )
          {
            nyindhru[i] = nyibar_b[i];
            dragkang[i] = nyibar_b[i];
          }
        nyindhru[5] = 0L;  
        nyindhru[4] = ( nyindhru[4] * rkang_frac ) / sun_f;

//    printf ( "Dragkang factor: %d - Nyindhru: %d;%d,%d,%d,%d,%d\n", 
//              dragkres, nyindhru[0], nyindhru[1], nyindhru[2], 
//              nyindhru[3], nyindhru[4], nyindhru[5] );

// MERCURY DAL DAG. KTC 85
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 616

    do_daldag ( merdaldag, nyindhru, merfac, merbye, merdom, rkang_frac );

// VENUS DAL DAG. KTC 77/78
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 616

    do_daldag ( vendaldag, nyindhru, venfac, venbye, vendom, rkang_frac );

    marsdag (); // Uses dragkang - KTC 65
    jupdag (); // KTC 74
    satdag (); // KTC 75
    merdag (); // KTC 86    
    vendag (); // KTC 82

    sprintf ( outbuf, "\nMars sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	mar_gz, mardaldag[0], mardaldag[1], mardaldag[2], mardaldag[3], mardaldag[4],
        marmurdag[0], marmurdag[1], marmurdag[2], marmurdag[3], marmurdag[4] );
    sprintf ( outbuf, "Jupiter sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	jup_gz, jupdaldag[0], jupdaldag[1], jupdaldag[2], jupdaldag[3], jupdaldag[4],
        jupmurdag[0], jupmurdag[1], jupmurdag[2], jupmurdag[3], jupmurdag[4] );
    sprintf ( outbuf, "Saturn sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	sat_gz, satdaldag[0], satdaldag[1], satdaldag[2], satdaldag[3], satdaldag[4],
        satmurdag[0], satmurdag[1], satmurdag[2], satmurdag[3], satmurdag[4] );
    sprintf ( outbuf, "Mercury sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	mer_gz, merkanbar[0], merkanbar[1], merkanbar[2], merkanbar[3], merkanbar[4],
        mermurdag[0], mermurdag[1], mermurdag[2], mermurdag[3], mermurdag[4] );
    sprintf ( outbuf, "Venus sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	ven_gz, venkanbar[0], venkanbar[1], venkanbar[2], venkanbar[3], venkanbar[4],
        venmurdag[0], venmurdag[1], venmurdag[2], venmurdag[3], venmurdag[4] );
 
    if ( printinprog )
      {
        sprintf ( printstring, "MARS sgos zhag = %d - %d;%d,%d,%d,%d",
                mar_gz, mardaldag[0], mardaldag[1], mardaldag[2], mardaldag[3],
                mardaldag[4] );
        prin_str ( printstring );

        sprintf ( printstring, "JUPITER sgos zhag = %d - %d;%d,%d,%d,%d",
                jup_gz, jupdaldag[0], jupdaldag[1], jupdaldag[2], jupdaldag[3],
                jupdaldag[4] );
        prin_str ( printstring );

        sprintf ( printstring, "SATURN sgos zhag = %d - %d;%d,%d,%d,%d",
                sat_gz, satdaldag[0], satdaldag[1], satdaldag[2], satdaldag[3],
                satdaldag[4] );
        prin_str ( printstring );

        sprintf ( printstring, "MERCURY sgos zhag = %d - %d;%d,%d,%d,%d",
                mer_gz, merkanbar[0], merkanbar[1], merkanbar[2], merkanbar[3],
                merkanbar[4] );
        prin_str ( printstring );

        sprintf ( printstring, "VENUS sgos zhag = %d - %d;%d,%d,%d,%d",
                ven_gz, venkanbar[0], venkanbar[1], venkanbar[2], venkanbar[3],
                venkanbar[4] );
        prin_str ( printstring );

        sprintf ( printstring, "Mars myur dag = %d;%d,%d,%d,%d",
                marmurdag[0], marmurdag[1], marmurdag[2], marmurdag[3],
                marmurdag[4] );
        prin_str ( printstring );
 
        sprintf ( printstring, "Jupiter myur dag = %d;%d,%d,%d,%d",
                jupmurdag[0], jupmurdag[1], jupmurdag[2], jupmurdag[3],
                jupmurdag[4] );
        prin_str ( printstring );
  
        sprintf ( printstring, "Saturn myur dag = %d;%d,%d,%d,%d",
                satmurdag[0], satmurdag[1], satmurdag[2], satmurdag[3],
                satmurdag[4] );
        prin_str ( printstring );
     
        sprintf ( printstring, "Mercury myur dag = %d;%d,%d,%d,%d",
                mermurdag[0], mermurdag[1], mermurdag[2], mermurdag[3],
                mermurdag[4] );
        prin_str ( printstring );
 
        sprintf ( printstring, "Venus myur dag = %d;%d,%d,%d,%d",
                venmurdag[0], venmurdag[1], venmurdag[2], venmurdag[3],
                venmurdag[4] );
        prin_str ( printstring );

        sprintf ( printstring, "drag rkang factor: %d", dragkres );
        prin_str ( printstring );
      }
  } // END - do_plans ()

void marsdag ( void )
  {
    int test, tquo, trem, x;
    int dortst, conttest, i, d_bug2 = 0;
    for ( i = 0; i < 6; ++i )
      dragk[i] = dragkang[i];

    if ( mar_gz > 270 && mar_gz < 310 )
      d_bug2 = 1;

// Adjust the units for later combination:
    l2bcd ( bcda, dragk[4] );
    mulbcdl ( bcda, bcda, marfrac );
    modbcdl ( bcdb, bcda, rkang_frac );
    divbcdl ( bcda, bcda, rkang_frac );
    dragk[4] = bcd2l ( bcda );
    dragk[5] = bcd2l ( bcdb );

    clear_a_b ();
    sub_g6 ( lista, dragk, mardaldag, 27L, marfrac, rkang_frac ); 

    test = lista[0] * 60L + lista[1];
    if ( test >= 13L * 60L + 30L )
      {
        dortst = 1;   // Subtract half-circle
        sub_gen ( lista, lista, plahaf, 27L, rkang_frac );
      }
    else
      dortst = 0;     // No subtraction of half-circle

    tquo = lista[0];
    trem = lista[1];

// Checked against calculation tables in British Library and:
// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 644

    if ( !dortst ) //  = ma dor, rim pa, lugs 'byung.
      { 
        if ( tquo == 13L ) 
          conttest = 1;
        else
          conttest = 0;

        if ( tquo == 0L )
          tquo = 14; 

        x = marbye1[tquo - 1];   // Multiplier, looking down
        lista[0] = 0L;
//      clear_lowera (); // This removes the lower units from lista, for testing.
        mul_g6 ( lista, x, marfrac, rkang_frac );
        if ( conttest )
          mul_g6 ( lista, 2L, marfrac, rkang_frac );
 
// Now divide all the way through by 60:

        div_g6 ( lista, 60L, marfrac, rkang_frac );
        listb[1] = mardom1[tquo - 1]; // Totals, left hand list.
        listb[0] = listb[1] / 60L;
        listb[1] = listb[1] % 60L;
        listb[5] = 0L;

      // tquo is equal to actual index, except 0, replaced by 14

//                   rim snga     rim min snga

        if ( tquo == 10L || tquo == 11L || tquo == 12L || tquo == 13L ) // phyi rkang
          {
            // Then, subtract:
            sub_g6 ( listc, listb, lista, 27L, marfrac, rkang_frac );
            mar_d = 1; // lho
          }
        else // snga rkang
          {
            add_g6 ( listc, listb, lista, 27L, marfrac, rkang_frac );
            mar_d = 0; // shar
          }
      }
    else // IF DORTST, rim min, lugs ldog.
      {
        conttest = 0;                  
        if ( lista[0] == 0L )
          {
            if ( lista[1] < 30L )
              conttest = 1;
          }
        if ( lista[1] >= 30L )
          {
            ++tquo;        
            trem = lista[1] - 30L; 
          }
        else if ( lista[0] != 0L )
          trem = lista[1] + 30L;

        if ( tquo == 0 )
          tquo = 14;

        x = marbye2[tquo - 1];
        lista[0] = 0L;
        lista[1] = trem; 
//      clear_lowera (); // This removes the lower units from lista
        mul_g6 ( lista, x, marfrac, rkang_frac );
        if ( conttest ) 
          mul_g6 ( lista, 2L, marfrac, rkang_frac );

// Now divide all the way through by 60:

        div_g6 ( lista, 60L, marfrac, rkang_frac );
        listb[1] = mardom2[tquo - 1];
        listb[0] = listb[1] / 60L;
        listb[1] = listb[1] % 60L;

      // tquo is equal to actual index, except 0, replaced by 14

        if ( tquo == 4L || tquo == 5L || tquo == 6L || tquo == 7L ||
           tquo == 8L || tquo == 9L || tquo == 10L || tquo == 11L || tquo ==
           12L || tquo == 13L /** || tquo == 14L */ ) // Then, subtract: phyi rkang
          { 
            sub_g6 ( listc, listb, lista, 27L, marfrac, rkang_frac );
            mar_d = 3; // byang
          }
        else // snga rkang
          {
            add_g6 ( listc, listb, lista, 27L, marfrac, rkang_frac );
            mar_d = 2; // "nub"
          }
      }
    if ( dortst == 1 ) 
      sub_g6 ( marmurdag, mardaldag, listc, 27L, marfrac, rkang_frac );
    else
      add_g6 ( marmurdag, mardaldag, listc, 27L, marfrac, rkang_frac );
  } // END - marsdag ()

void jupdag ( void )
  {
    int test, tquo, trem, x;
    int dortst, conttest, i;
    for ( i = 0; i < 6; ++i )
      dragk[i] = dragkang[i];

// Adjust the units for later combination: 
    l2bcd ( bcda, dragk[4] );
    mulbcdl ( bcda, bcda, jupfrac );
    modbcdl ( bcdb, bcda, rkang_frac );
    divbcdl ( bcda, bcda, rkang_frac );
    dragk[4] = bcd2l ( bcda );
    dragk[5] = bcd2l ( bcdb ); 

    clear_a_b ();

    sub_g6 ( lista, dragk, jupdaldag, 27L, jupfrac, rkang_frac ); 

    test = lista[0] * 60L + lista[1];
    if ( test >= 13L * 60L + 30L )
      {
        dortst = 1;
        sub_gen ( lista, lista, plahaf, 27L, rkang_frac );
      }
    else
      dortst = 0;

    tquo = lista[0];
    trem = lista[1];

// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 645
    if ( !dortst ) //  = ma dor, rim pa, lugs 'byung.
      { 
        if ( tquo == 13L )
          conttest = 1;
        else
          conttest = 0;
        if ( tquo == 0L )
          tquo = 14;    
        x = jupbye1[tquo - 1];
        lista[0] = 0L;
        mul_g6 ( lista, x, jupfrac, rkang_frac );
        if ( conttest )
          mul_g6 ( lista, 2L, jupfrac, rkang_frac );

// Now divide all the way through by 60:

        div_g6 ( lista, 60L, jupfrac, rkang_frac );

      listb[1] = jupdom1[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;
      listb[5] = 0L;

// tquo is equal to actual index, except 0, replaced by 14
//                   rim snga     rim min snga

      if ( tquo == 8L || tquo == 9L || tquo == 10L || tquo == 11L ||
           tquo == 12L || tquo == 13L ) // Then, subtract: rim, phyi rkang
        {   
          sub_g6 ( listc, listb, lista, 27L, jupfrac, rkang_frac );
          jup_d = 1;          
        }
      else // rim, snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, jupfrac, rkang_frac );
          jup_d = 0;          
        }  
      }
    else // If DORTST, rim min, lugs ldog.
      {                                 
        conttest = 0;                   
        if ( lista[0] == 0L )
          {
            if ( lista[1] < 30L )
              conttest = 1;
          }
        if ( lista[1] >= 30L )
          {
            ++tquo;          
            trem = lista[1] - 30L; 
          }
        else if ( lista[0] != 0L )
          trem = lista[1] + 30L;
      if ( tquo == 0 )
        tquo = 14;

      x = jupbye2[tquo - 1];
      lista[0] = 0L;
      lista[1] = trem;
      mul_g6 ( lista, x, jupfrac, rkang_frac );
      if ( conttest )  
        mul_g6 ( lista, 2L, jupfrac, rkang_frac );
   
// Now divide all the way through by 60:

      div_g6 ( lista, 60L, jupfrac, rkang_frac );
      listb[1] = jupdom2[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;

// tquo is equal to actual index, except 0, replaced by 14
//                   rim snga     rim min snga

      if ( tquo == 6L || tquo == 7L || tquo == 8L || tquo == 9L || tquo == 10L
           || tquo == 11L || tquo == 12L || tquo == 13L ) // Then, subtract: rim min, phyi rkang
        {
          sub_g6 ( listc, listb, lista, 27L, jupfrac, rkang_frac );
          jup_d = 3;          
        }
      else // rim min snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, jupfrac, rkang_frac );
          jup_d = 2;          
        }
      }
    if ( dortst == 1 )  
      sub_g6 ( jupmurdag, jupdaldag, listc, 27L, jupfrac, rkang_frac );
    else
      add_g6 ( jupmurdag, jupdaldag, listc, 27L, jupfrac, rkang_frac );
  } // END - jupdag ()

void satdag ( void )
  {
    int test, tquo, trem, x;
    int dortst, conttest, i;
    for ( i = 0; i < 6; ++i )
      dragk[i] = dragkang[i];

// Adjust the units for later combination: 
    l2bcd ( bcda, dragk[4] );
    mulbcdl ( bcda, bcda, satfrac );
    modbcdl ( bcdb, bcda, rkang_frac );
    divbcdl ( bcda, bcda, rkang_frac );
    dragk[4] = bcd2l ( bcda );
    dragk[5] = bcd2l ( bcdb );

    clear_a_b ();
    sub_g6 ( lista, dragk, satdaldag, 27L, satfrac, rkang_frac );

    test = lista[0] * 60L + lista[1];
    if ( test >= 13L * 60L + 30L )
      {
        dortst = 1;
        sub_gen ( lista, lista, plahaf, 27L, rkang_frac );
      }
    else
      dortst = 0;

    tquo = lista[0];
    trem = lista[1];

// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 647
    if ( !dortst ) //  = ma dor, rim pa, lugs 'byung.
      { 
        if ( tquo == 13L ) 
          conttest = 1;
        else
          conttest = 0;
        if ( tquo == 0L )
          tquo = 14;
        x = satbye1[tquo - 1];
        lista[0] = 0L;
        mul_g6 ( lista, x, satfrac, rkang_frac );
        if ( conttest )
          mul_g6 ( lista, 2L, satfrac, rkang_frac );

// Now divide all the way through by 60:

        div_g6 ( lista, 60L, satfrac, rkang_frac );

      listb[1] = satdom1[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;
      listb[5] = 0L;

      // tquo is equal to actual index, except 0, replaced by 14

      if ( tquo == 8L || tquo == 9L || tquo == 10L || tquo == 11L ||
           tquo == 12L || tquo == 13L ) // Then, subtract: rim, phyi rkang
        {
          sub_g6 ( listc, listb, lista, 27L, satfrac, rkang_frac );
          sat_d = 1;          
        }
      else // rim min, snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, satfrac, rkang_frac );
          sat_d = 0;          
        }
      }
    else // If DORTST, rim min, lugs ldog.
      {                                 
        conttest = 0;               
        if ( lista[0] == 0L )
          {
            if ( lista[1] < 30L )
              conttest = 1;
          }
        if ( lista[1] >= 30L )
          {
            ++tquo;    
            trem = lista[1] - 30L; 
          }
        else if ( lista[0] != 0L )
          trem = lista[1] + 30L;
      if ( tquo == 0 )
        tquo = 14;

      x = satbye2[tquo - 1];
      lista[0] = 0L;
      lista[1] = trem;
      mul_g6 ( lista, x, satfrac, rkang_frac );
      if ( conttest ) 
        mul_g6 ( lista, 2L, satfrac, rkang_frac );

// Now divide all the way through by 60:
      div_g6 ( lista, 60L, satfrac, rkang_frac );

      listb[1] = satdom2[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;
// tquo is equal to actual index, except 0, replaced by 14
      if ( tquo == 6L || tquo == 7L || tquo == 8L || tquo == 9L || tquo == 10L
           || tquo == 11L || tquo == 12L || tquo == 13L ) // Then, subtract: rim min, phyi rkang
        {
          sub_g6 ( listc, listb, lista, 27L, satfrac, rkang_frac );
          sat_d = 3;          
        }
      else // rim min snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, satfrac, rkang_frac );
          sat_d = 2;
        }
      }
    if ( dortst == 1 ) 
      sub_g6 ( satmurdag, satdaldag, listc, 27L, satfrac, rkang_frac );
    else
      add_g6 ( satmurdag, satdaldag, listc, 27L, satfrac, rkang_frac );
  } // END - satdag ()

void merdag ( void ) // Mercury myur dag
  {
    int test, tquo, trem, x;
    int dortst, conttest, i;

    for ( i = 0; i < 6; ++i )
      dald[i] = merdaldag[i];

// Adjust the units for later combination: 
    l2bcd ( bcda, dald[4] );
    mulbcdl ( bcda, bcda, merfrac );
    modbcdl ( bcdb, bcda, rkang_frac );
    divbcdl ( bcda, bcda, rkang_frac );
    dald[4] = bcd2l ( bcda );
    dald[5] = bcd2l ( bcdb );

    clear_a_b ();
    sub_g6 ( lista, merkanbar, dald, 27L, merfrac, rkang_frac ); 

    test = lista[0] * 60L + lista[1];
    if ( test >= 13L * 60L + 30L )
      {
        dortst = 1;
        sub_gen ( lista, lista, plahaf, 27L, rkang_frac );
      }
    else
      dortst = 0;
    tquo = lista[0];
    trem = lista[1];

// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 644
    if ( !dortst ) //  = ma dor, rim pa, lugs 'byung.
      { 
      if ( tquo == 13L ) 
        conttest = 1;
      else
        conttest = 0;
      if ( tquo == 0L )
        tquo = 14;
      x = merbye1[tquo - 1];
      lista[0] = 0L;
//    clear_lowera (); // This removes the lower units from lista
      mul_g6 ( lista, x, merfrac, rkang_frac );
      if ( conttest )
        mul_g6 ( lista, 2L, merfrac, rkang_frac );

// Now divide all the way through by 60:

      div_g6 ( lista, 60L, merfrac, rkang_frac );
      listb[1] = merdom1[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;
      listb[5] = 0L;

      // tquo is equal to actual index, except 0, replaced by 14

      if ( tquo == 9L || tquo == 10L || tquo == 11L ||
           tquo == 12L || tquo == 13L ) // Then, subtract: rim pa, phyi rkang
        {
          sub_g6 ( listc, listb, lista, 27L, merfrac, rkang_frac );
          mer_d = 1;          
        }
      else  // rim pa, snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, merfrac, rkang_frac );
          mer_d = 0;          
        }
      }
    else // If DORTST, rim min, lugs ldog.
      {                                 
        conttest = 0;                   
        if ( lista[0] == 0L )
          {
            if ( lista[1] < 30L )
              conttest = 1;
          }
        if ( lista[1] >= 30L )
          {
            ++tquo;   
            trem = lista[1] - 30L; 
          }
        else if ( lista[0] != 0L )
          trem = lista[1] + 30L;

      if ( tquo == 0 )
        tquo = 14;

      x = merbye2[tquo - 1];
      lista[0] = 0L;
      lista[1] = trem;
      mul_g6 ( lista, x, merfrac, rkang_frac );
      if ( conttest )  
        mul_g6 ( lista, 2L, merfrac, rkang_frac );
// Now divide all the way through by 60:
      div_g6 ( lista, 60L, merfrac, rkang_frac );
      listb[1] = merdom2[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;

      // tquo is equal to actual index, except 0, replaced by 14

      if ( tquo == 5L || tquo == 6L || tquo == 7L || tquo == 8L || tquo == 9L
           || tquo == 10L || tquo == 11L || tquo == 12L || tquo == 13L ) // Then, subtract: rim min phyi
        {
          sub_g6 ( listc, listb, lista, 27L, merfrac, rkang_frac );
          mer_d = 3;          
        }
      else // rim min, snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, merfrac, rkang_frac );
          mer_d = 2;
        }
      }

    if ( dortst == 1 ) 
      sub_g6 ( mermurdag, dald, listc, 27L, merfrac, rkang_frac );
    else
      add_g6 ( mermurdag, dald, listc, 27L, merfrac, rkang_frac );
  } // END - merdag ()

void vendag ( void ) // Venus myur dag
  {
    int test, tquo, trem, x;
    int dortst, conttest, i;

    for ( i = 0; i < 6; ++i )
      dald[i] = vendaldag[i];

// Adjust the units for later combination: 
    l2bcd ( bcda, dald[4] );
    mulbcdl ( bcda, bcda, venfrac );
    modbcdl ( bcdb, bcda, rkang_frac );
    divbcdl ( bcda, bcda, rkang_frac );
    dald[4] = bcd2l ( bcda );
    dald[5] = bcd2l ( bcdb );

    clear_a_b ();
    sub_g6 ( lista, venkanbar, dald, 27L, venfrac, rkang_frac ); 

    test = lista[0] * 60L + lista[1];
    if ( test >= 13L * 60L + 30L )
      {
        dortst = 1;
        sub_gen ( lista, lista, plahaf, 27L, rkang_frac );
      }
    else
      dortst = 0;
    tquo = lista[0];
    trem = lista[1];

// Checked against tables by "dbyangs can grub pa'i rdo rje", p. 645
    if ( !dortst ) //  = ma dor, rim pa, lugs 'byung.
      { 
      if ( tquo == 13L ) 
        conttest = 1;
      else
        conttest = 0;

      if ( tquo == 0L )
        tquo = 14;   

      x = venbye1[tquo - 1];
      lista[0] = 0L;
      mul_g6 ( lista, x, venfrac, rkang_frac );
      if ( conttest )
        mul_g6 ( lista, 2L, venfrac, rkang_frac );

      // Now divide all the way through by 60:

      div_g6 ( lista, 60L, venfrac, rkang_frac );

      listb[1] = vendom1[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;
      listb[5] = 0L;
      // tquo is equal to actual index, except 0, replaced by 14
      if ( tquo == 10L || tquo == 11L || tquo == 12L || tquo == 13L )
                                                     // Then, subtract: rim pa, phyi rkang
        {                                                     
          sub_g6 ( listc, listb, lista, 27L, venfrac, rkang_frac );
          ven_d = 1;
        }
      else // rim pa, snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, venfrac, rkang_frac );
          ven_d = 0;
        }
      }
    else // If DORTST, rim min, lugs ldog.
      {                               
        conttest = 0;                   
        if ( lista[0] == 0L )
          {
            if ( lista[1] < 30L )
              conttest = 1;
          }
        if ( lista[1] >= 30L )
          {
            ++tquo;             
            trem = lista[1] - 30L; 
          }
        else if ( lista[0] != 0L )
          trem = lista[1] + 30L;
      if ( tquo == 0 )
        tquo = 14;
      x = venbye2[tquo - 1];
      lista[0] = 0L;
      lista[1] = trem;
      mul_g6 ( lista, x, venfrac, rkang_frac );
      if ( conttest )  
        mul_g6 ( lista, 2L, venfrac, rkang_frac );
// Now divide all the way through by 60:
      div_g6 ( lista, 60L, venfrac, rkang_frac );
      listb[1] = vendom2[tquo - 1];
      listb[0] = listb[1] / 60L;
      listb[1] = listb[1] % 60L;
// tquo is equal to actual index, except 0, replaced by 14
      if ( tquo == 4L || tquo == 5L || tquo == 6L || tquo == 7L || tquo == 8L
           || tquo == 9L || tquo == 10L || tquo == 11L || tquo == 12L ||
                                           tquo == 13L ) // Then, subtract: rim min, phyi rkang
        {
          sub_g6 ( listc, listb, lista, 27L, venfrac, rkang_frac );
          ven_d = 3;
        }
      else // rim min, snga rkang
        {
          add_g6 ( listc, listb, lista, 27L, venfrac, rkang_frac );
          ven_d = 2;
        }
      }
    if ( dortst == 1 )  
      sub_g6 ( venmurdag, dald, listc, 27L, venfrac, rkang_frac );
    else
      add_g6 ( venmurdag, dald, listc, 27L, venfrac, rkang_frac );
  } // END - vendag ()
  
