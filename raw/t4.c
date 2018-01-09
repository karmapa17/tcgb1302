// t4.c - all routines and data for printing to disk a full calendar

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
#include <string.h>
#include <conio.h>
#include "tc.h"
#include "tc.ext"
#include "bcd.h"
#include "bcd.ext"

char gen_phrod_str[30];
char sreg_str[30];
char lmchg[70];
char byungphro_str[40];
char solar_term_str[60];

int nxt_monlong[6];
int fst_monlong[6], cur_monlong[6], scd_monlong[6], tt_monlong[6];

void prn_cal ( void )
  {
    int i, more, n, newmth, lhag, chad, nextchad, nextlhag;
    int intercal, delaymth, dgax;
    int yr_gender;    // 1 = female, odd; 0 = male, even
    int mt_gender;    // 1 = female, odd; 0 = male, even
    int mthnum; // Adjusted, without negative.
    int cur_year, last_year;
    int ltt, zla0, zla1;
    int lastjd = 0L;
    int curjd, nextjd; // Last and next JD calculations.
    int  lunmanx, sbyorba, byedpax;
    int  prv_lunmanx, fst_sbyorba, /**fst_byedpa,**/ fst_byedpax;
    int  fst_lunmanx;     
    int Cmonth;
    int tenbrelx;    
    int sd_clunmanx;
    int ld_parx; 
    int ld_smex, sd_smex;
    int yr_animx, mt_animx, ld_animx, sd_animx;
    int yr_elemx, mt_elemx, sd_elemx;
    int ZS_s, ZS_d, ZS_m;  // Zodiac signs, minutes, seconds;
    int e, g;
    int new_year;

    set_lang ();
    gza_short_flg = 0; // Flag for less accurate weekday adjustment
    cls ();
    printf ( "%s\n\n", e_str[epch-1] );
    printf ("Enter the starting year: ");
    scanf ("%d", &ty);
    printf ("\n");

    cur_year = ty;

    printf ("Enter the finish year: ");
    scanf ("%d", &last_year );
    printf ("\n");

donextyear:

    new_year = 1;
    ty = cur_year;
    tm = 1L;
    zeromthfg = 0;

    sprintf ( filenam, "tsa_%d.txt", ty );
  
    fptgt1 = fopen ( filenam, "w" );
    if ( fptgt1 == NULL )
      {
        printf ( "Error opening target file!\n" );
        getch ();
      }
      
// tt not yet set
// First, check to see if we are not at adjusted 12th month:

    zla_dag (ty, tm); // But only if moving one month at a time!

    zla0 = zladag[0];
    zla1 = zladag[1];

    adj_zla ();
    if ( adj_mth == 12L )
      {
        if ( !zeromthfg ) // Should always work
          ++tm;
      }
    else if ( adj_mth == -1L )
      {
        zladag[0] = zla0;
        zladag[1] = zla1;
        zeromthfg = 0;
      }
    n = 0;
    more = 1;
    newmth = 1;
    do   // START OF MONTH LOOP *******************************   
      {
        intercal = 0;
        if ( adj_mth == -1L )
          intercal = 1;
        delaymth = 0;
        if ( newmth )
          {
            if ( !zeromthfg )   // We need to use the same data, twice.
              zla_dag (ty, tm); // But only if moving one month at a time!
            adj_zla ();
            cur_mth = zladag[0];  // Needed for general day
            gza_dru (cur_mth);
            nyi_dru_b (cur_mth);            
            rilchaf ( cur_mth ); // MOVED, from gza_dag, NEW, 11/9/94

// DO WE HAVE NEW YEAR?
            if ( ( adj_mth == -1 || adj_mth == 1 ) && new_year )
              {
                if ( ty < 7L )
                  {
                    yr_animx = ( ty + 1200L - 7L ) % 12L;
                    yr_elemx = ( ( ty + 1200L ) / 2L - 3L ) % 5L;
                    yr_gender = ( ty + 1200L ) % 2; // 1 = female, odd; 0
                  }
                else
                  {
                    yr_animx = ( ty - 7L ) % 12L;
                    yr_elemx = ( ty / 2L - 3L ) % 5L;
                    yr_gender = ty % 2; // 1 = female, odd; 0 = male
                  }
                sprintf ( outbuf, "New Year: %d, %s-%s-%s\n", ty,
                                  cycelem1[ yr_elemx ],
                                  cycgendE[ yr_gender ],
                                  cycanim[ yr_animx ] );
                fprintf ( fptgt1, "%s", outbuf );
                new_year = 0;
              }
          } // END - if ( newmth )
            if ( adj_mth < 0L ) // Intercalary
              {
                intercal = 1;
                delaymth = 0;
              }
            else if ( adj_mth > 0L && ( zladag[1] == 0 || zladag[1] == 1 ) )
              {
                intercal = 0;
                delaymth = 1;
              }

        if ( adj_mth < 0L )
          mthnum = -adj_mth;
        else
          mthnum = adj_mth;

        mt_animx = ( mthnum + 10L ) % 12L;
            Cmonth = mthnum;
//      yr_gender - 1 = female, odd; 0 = male, even
// ORDER IS: "Fire", "Earth", "Iron", "Water", "Wood"
//             0        1       2        3       4
        e = yr_elemx; g = yr_gender;
        if ( ( e == 4 && g == 0 ) || ( e == 1 && g == 1 ) )
          mt_elemx = 0L + ( mthnum - 1L ) / 2L;
        if ( ( e == 4 && g == 1 ) || ( e == 2 && g == 0 ) )
          mt_elemx = 1L + ( mthnum - 1L ) / 2L;
        if ( ( e == 0 && g == 0 ) || ( e == 2 && g == 1 ) )
          mt_elemx = 2L + ( mthnum - 1L ) / 2L;
        if ( ( e == 1 && g == 0 ) || ( e == 3 && g == 1 ) )
          mt_elemx = 4L + ( mthnum - 1L ) / 2L;
        if ( ( e == 0 && g == 1 ) || ( e == 3 && g == 0 ) )
          mt_elemx = 3L + ( mthnum - 1L ) / 2L;

        if ( yr_gender == 0 ) // Male year, even CE number 
          {
            if ( mthnum == 11L || mthnum == 12L )
              mt_elemx = yr_elemx + ( mthnum + 1L ) / 2;
          }

        mt_elemx = mt_elemx % 5L;
        mt_gender = ( mthnum + 1 ) % 2; // There is no month zero

        if ( intercal )
          sprintf ( outbuf,
          "Tibetan Lunar Month: %d (Intercalary) - %s-%s-%s",
          -adj_mth, cycelem1[ mt_elemx ],
          cycgendE[ mt_gender ], cycanim[ mt_animx ] );

        else if ( delaymth )
          sprintf ( outbuf, "Tibetan Lunar Month: %d (Delayed) - %s-%s-%s",
          adj_mth, cycelem1[ mt_elemx ],
          cycgendE[ mt_gender ], cycanim[ mt_animx ] );
          
        else
          sprintf ( outbuf, "Tibetan Lunar Month: %d - %s-%s-%s",
          adj_mth, cycelem1[ mt_elemx ],
          cycgendE[ mt_gender ], cycanim[ mt_animx ] );

        printf ( "%s\n", outbuf );
        fprintf ( fptgt1, "%s\n\n", outbuf );  // Extra carriage return added here

        sprintf ( outbuf, "Month: %d;%d", zladag[0], zladag[1] );
        fprintf ( fptgt1, "%s\n", outbuf );        
        sprintf ( outbuf, "Anomaly: %d;%d", rilcha[0], rilcha[1] );
        fprintf ( fptgt1, "%s\n", outbuf );        

        tse_dru (0L);
        nyi_lon_b (0L);        
        add_gen (tsebar, gzadru, tsedru, 7L, gza_f);
        add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b );        
        nyi_dag_b (nyibar_b); // MUST BE DONE FIRST      
        gza_dag (tsebar);
        tt = 0L;
        spi_zagf ();

        sprintf ( outbuf, "Mean Weekday: %d;%d,%d,%d,%d",
                          gzadru[0], gzadru[1], gzadru[2], gzadru[3], gzadru[4] );
        fprintf ( fptgt1, "%s\n", outbuf );   
        sprintf ( outbuf, "Mean Sun: %d;%d,%d,%d,%d",
                          nyidru_b[0], nyidru_b[1], nyidru_b[2], nyidru_b[3], nyidru_b[4] );                          
        fprintf ( fptgt1, "%s\n\n", outbuf );

        tt = 1L;
        ltt = 1L;
        
// START OF DAY LOOP - START OF DAY LOOP - START OF DAY LOOP **********************
        do
          {  
            tt = ltt;
            nextlhag = 0;
            lhag = 0;
            chad = 0;
            nextchad = 0;
            tse_dru (tt);
            nyi_lon_b (tt);            
            add_gen (tsebar, gzadru, tsedru, 7L, gza_f);
            add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b );            
            nyi_dag_b (nyibar_b); // Must be done before gza_dag            
            for ( i = 0; i < 6; ++i )
              nyidag[i] = nyidag_b[i];            
            gza_dag (tsebar);
            spi_zagf ();

// Work out previous and next days to determine CHAD or LHAG
            curjd = juldat;
            tt = ltt - 1L;
            tse_dru (tt);
            nyi_lon_b (tt);            
            add_gen (tsebar, gzadru, tsedru, 7L, gza_f);
            add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b );            
            nyi_dag_b (nyibar_b); // Must be done before gza_dag            
            for ( i = 0; i < 6; ++i )
              nyidag[i] = nyidag_b[i];            
            gza_dag (tsebar);
            spi_zagf ();
            lastjd = juldat;
            for ( i = 0; i < 5; ++i )
              monlong[i] = 0L;
            monlong[1] = 54L;  // 1/30th of a revolution
            mul_gen ( monlong, monlong, tt, 27L, sun_f );
            add_gen ( monlong, monlong, nyidag, 27L, sun_f );
            for ( i = 0; i < 6; ++i )
              {
                prv_nyidag[i] = nyidag[i];
                prv_gzadag[i] = gzadag[i];
                prv_monlong[i] = monlong[i];
              }

            tt = ltt + 1L;
            tse_dru (tt);
            nyi_lon_b (tt);            
            add_gen (tsebar, gzadru, tsedru, 7L, gza_f);
            add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b );            
            nyi_dag_b (nyibar_b); // Must be done before gza_dag            
            for ( i = 0; i < 6; ++i )
              nyidag[i] = nyidag_b[i];            
            gza_dag (tsebar);
            spi_zagf ();
            nextjd = juldat;

            // Save for later, in case we have a LHAG day:
            
            for ( i = 0; i < 5; ++i )
              monlong[i] = 0L;
            monlong[1] = 54L;  // 1/30th of a revolution
            mul_gen ( monlong, monlong, tt, 27L, sun_f );
            add_gen ( monlong, monlong, nyidag, 27L, sun_f );
            for ( i = 0; i < 6; ++i )
              {
                nxt_nyidag[i] = nyidag[i];
                nxt_gzadag[i] = gzadag[i];
                nxt_monlong[i] = monlong[i];
              }            

// Recalculate for current tithi: 

            tt = ltt;
            tse_dru (tt);
            nyi_lon_b (tt);            
            add_gen (tsebar, gzadru, tsedru, 7L, gza_f);
            add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b );            
            nyi_dag_b (nyibar_b); // Must be done before gza_dag            
            for ( i = 0; i < 6; ++i )
              nyidag[i] = nyidag_b[i];            
            gza_dag (tsebar);
            spi_zagf ();
            if ( curjd == lastjd + 2L )
              lhag = 1;
            if ( nextjd == curjd + 2L )
              nextlhag = 1;
            if ( curjd == lastjd )
              chad = 1;
            if ( curjd == nextjd )
              nextchad = 1;

// Calculate lunar mansion at daybreak:
// add solar longitude to tithi * factor. Then subtract hours, etc., from gzadag

        clear_a_b ();
        for ( i = 0; i < 5; ++i )
          monlong[i] = 0L;
        monlong[1] = 54L;  // 1/30th of a revolution
        mul_gen ( monlong, monlong, tt, 27L, sun_f );
        add_gen ( monlong, monlong, nyidag, 27L, sun_f );
        for ( i = 0; i < 6; ++i )
          tt_monlong[i] = monlong[i];
        listb[0] = 0L;
        for ( i = 1; i < 5; ++i )
          listb[i] = gzadag[i];
        listb[4] = ( sun_f * listb[4] ) / gza_f;
    
// This gives longitude at daybreak:
        sub_gen ( monlong, monlong, listb, 27L, sun_f );
        lunmanx = monlong[0];

// Solar day data: - picks up again here similar to SLC. 

        sd_animx = ( juldat - 2L ) % 12L;
        sd_elemx = ( ( juldat - 3L ) / 2L ) % 5L;
        sd_clunmanx = ( juldat - 17L ) % 28L;
        sd_smex = ( juldat - 2L ) % 9L + 1L; 

// Lunar day data:

// If Chinese month is number 1, Trigram is Li, index = 1
        ld_parx = ( Cmonth - 1L ) * 30L + tt;
        ld_parx = ld_parx % 8L;
// If Chinese month is number 1, "sme ba" is 1
        ld_smex = ( Cmonth - 1L ) * 30L + tt;
        ld_smex = ld_smex % 9L;
        if ( ld_smex == 0L )
          ld_smex = 9L;
// If Chinese month is number 1, Animal is Tiger, index = 11
        ld_animx = ( Cmonth - 1L ) * 30L + tt + 10L;
        ld_animx = ld_animx % 12L;

        dgax = ( tt - 1 ) % 5;
// rten 'brel:                  
        tenbrelx = get_tenbrel ( mthnum, tt );       
        get_bishti_str ( tt ); 
        chk_namgo ( tt );


        if ( chad )   // This is for omitted lunar day 
          {
            sprintf ( outbuf, "%d. Omitted. %s", tt, dgaT[dgax] );                      
// Should include "gza'" for end of lunar day, plus solar longitude. ???
            fprintf ( fptgt1, "%s\n", outbuf );
            
            sprintf ( outbuf,
                    "%d;%d,%d %d;%d,%d",
                     gzadag[0], gzadag[1], gzadag[2],
                     nyidag[0], nyidag[1], nyidag[2] );
              fprintf ( fptgt1, "\x20\x20%s\n", outbuf );            

            if ( tt == 15 || tt == 30 )
              {
                do_plans ( spizag );     
                prn_plans ();
                do_rahu ( cur_mth, tt );  
                prn_rahu (tt); 
              }            
          }
        else  // If normal or duplicated: 
          {
// NYIDAG is not changed after here, so we can now calculate zodiacal sign:
// Zodiac signs, degrees, minutes -  ZS_s, ZS_d, ZS_m;
            lm2signs ( &ZS_s, &ZS_d, &ZS_m, nyidag ); // Was nyibar
            if ( lhag )  // If this is the first of two weekdays. 
              {
                // Put here any special calculations for extra day 
                // At this point, the gzadag, nyidag & monlong are correct for
                // the second of the two days with same tithi. We need for the
                // first. Previous tithi ended just before start of day we need.
                // prv_monlong is the moon longitude at beginning of current lunar day. 
                clear_a_b (); 
                listb[0] = 1L;
                for ( i = 1; i < 5; ++i )
                  lista[i] = prv_gzadag[i]; // Previous lunar day
                sub_gen ( listb, listb, lista, 7L, gza_f );
                l2bcd ( bcdx0, sun_f );
                mulbcdl ( bcdx0, bcdx0, listb[4] );
                divbcdl ( bcdx1, bcdx0, gza_f );
                listb[4] = bcd2l ( bcdx1 ); 
                add_gen ( fst_monlong, prv_monlong, listb, 27L, sun_f );
// This is now the moon longitude at daybreak of first duplicated day
                fst_lunmanx = fst_monlong[0]; 

                listb[0] = 0L;
                for ( i = 1; i < 5; ++i )
                  listb[i] = gzadag[i];
                l2bcd ( bcdx0, sun_f );
                mulbcdl ( bcdx0, bcdx0, listb[4] );
                divbcdl ( bcdx1, bcdx0, gza_f );
                listb[4] = bcd2l ( bcdx1 ); 
                sub_gen ( cur_monlong, tt_monlong, listb, 27L, sun_f );
// This is now the moon longitude at daybreak of second duplicated day
                lunmanx = cur_monlong[0]; 

// Now, for end of second duplicated day.
// First, if lunar day is not omitted - it can happen -- see, eg., phugpa 6th of 9th month 1457

                if ( nxt_gzadag[0] != gzadag[0] )
                  {
                    listb[0] = 0L;
                    for ( i = 1; i < 5; ++i )
                      listb[i] = nxt_gzadag[i];
                    l2bcd ( bcdx0, sun_f );
                    mulbcdl ( bcdx0, bcdx0, listb[4] );
                    divbcdl ( bcdx1, bcdx0, gza_f );
                    listb[4] = bcd2l ( bcdx1 ); 
                    sub_gen ( scd_monlong, nxt_monlong, listb, 27L, sun_f );
// This is now the moon longitude at end of second duplicated day
                  }
                else // if following lunar day IS omitted
                  {  
                    clear_a_b ();                
                    listb[0] = 1L;
                    for ( i = 1; i < 5; ++i )
                      lista[i] = nxt_gzadag[i];
                    sub_gen ( listb, listb, lista, 7L, gza_f );
//              listb[4] = ( sun_f * listb[4] ) / gza_f;                
                    l2bcd ( bcdx0, sun_f );
                    mulbcdl ( bcdx0, bcdx0, listb[4] );
                    divbcdl ( bcdx1, bcdx0, gza_f );
                    listb[4] = bcd2l ( bcdx1 ); 
                    add_gen ( scd_monlong, nxt_monlong, listb, 27L, sun_f );
// This is now the moon longitude at end of second duplicated day
                  }

                mak_lmchange_string ( fst_monlong, cur_monlong, doweek );

                prv_lunmanx = prv_monlong[0];        
                
// prv_monlong - Moon longitude at beginning of current lunar day. OK
// fst_monlong - Moon longitude at daybreak of first duplicated day
// cur_monlong - Moon longitude at daybreak of second duplicated day
// monlong - Moon longitude at end of current lunar day
// scd_monlong - Moon longitude at end of second duplicated day
// nxt_monlong - Moon longitude at end of next lunar day 

// Now calculate yoga, sbyor ba:
         
        add_gen ( fst_sbyorlong, fst_monlong, nyidag, 27L, sun_f );          
        fst_sbyorba = fst_sbyorlong[0];                    

// Now calculate karana, sbyed pa:  

        fst_byedpax = calc_byedpa ( fst_monlong, nyidag );
        juldat = juldat - 1L;
        jul2date ( juldat ); // This is normally done by spi_zagf

// Solar day data:

        sd_animx = ( juldat - 2L ) % 12L;
        sd_elemx = ( ( juldat - 3L ) / 2L ) % 5L;
        sd_clunmanx = ( juldat - 17L ) % 28L;
        sd_smex = ( juldat - 2L ) % 9L + 1L; 

// For general and special "'phrod":

        gen_phrod ( fst_lunmanx, doweek, fst_monlong[1] );

// For 'phrod chen/sbyor:
        get_phrochen ( &phrodx, doweek, prv_lunmanx, prv_monlong[1] );        
                
                // LINE 1. - First of duplicated day
                sprintf ( outbuf, "%d: %s. %s/%s. %s-%s; %d %s %d",
                          tt,
                          dayoweek[ doweek ],
                          lunmanS[ fst_lunmanx ], lunmanT[ fst_lunmanx ],
                          fourelem[ dowkelem[ doweek ] ],
                          fourelem[ lunmanelem[ fst_lunmanx ] ],
                          wd, wmonths[ (wm-1L) ], wy);
                fprintf ( fptgt1, "%s\n", outbuf );

                // LINE 2. First of duplicated day
                sprintf ( outbuf, "%s/%s, %s/%s, %s, %s %d",
                          yogaS[ fst_sbyorba ], yogaT[ fst_sbyorba ],
                          byedS[ fst_byedpax ], byedT[ fst_byedpax ],
                          cycanim[ ld_animx ],
                          cycpar[ ld_parx ], ld_smex );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );

                // LINE 3. First of duplicated day
                sprintf ( outbuf,
                    "%d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d",
                       ( prv_gzadag[0] + 1L ) % 7L, 60L, 0L,
                       fst_monlong[0], fst_monlong[1], fst_monlong[2],
                       nyidag[0], nyidag[1], nyidag[2],
                       fst_sbyorlong[0], fst_sbyorlong[1], fst_sbyorlong[2],
                       ZS_s, ZS_d, ZS_m );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );                

                // LINE 4. First of duplicated day
                    sprintf ( outbuf, "Solar: %s-%s. %s" ,
                              cycelem1[ sd_elemx ],
                              cycanim[ sd_animx ],
                              Clunman[ sd_clunmanx ] );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );
                
// LINE 5.
            if ( !delaymth && chk_spec ( mthnum, tt ) )
              {
                fprintf ( fptgt1, "  %s\n", outbuf );
              }
            if ( chk_sadag2 ( mthnum, tt ) )
              fprintf ( fptgt1, "\x20\x20\x20\x20%s\n", sadag_str2 );              

// Now do second of duplicated lunar day 

            juldat = juldat + 1L;  // This is readjustment!
            jul2date ( juldat );

// Solar day data:   

            sd_animx = ( juldat - 2L ) % 12L;
            sd_elemx = ( ( juldat - 3L ) / 2L ) % 5L;
            sd_clunmanx = ( juldat - 17L ) % 28L;
            sd_smex = ( juldat - 2L ) % 9L + 1L;  
            
// sbyor ba:

            add_gen ( sbyorlong, cur_monlong, nyidag, 27L, sun_f ); 
            sbyorba = sbyorlong[0];            
              
// Now calculate karana, sbyed pa:
            byedpax = calc_byedpa ( cur_monlong, nyidag );

            gen_phrod ( lunmanx, doweek, cur_monlong[1] );       
            lm2signs ( &ZS_s, &ZS_d, &ZS_m, nyidag ); // Needs to be done again                          
            mak_lmchange_string ( cur_monlong, scd_monlong, doweek ); // details calculated above       

                // LINE 1. second of duplicated 
                sprintf ( outbuf, "%d: %s. %s/%s. %s-%s; %d %s %d",
                          tt,
                          dayoweek[ doweek ],
                          lunmanS[ lunmanx ], lunmanT[ lunmanx ],
                          fourelem[ dowkelem[ doweek ] ],
                          fourelem[ lunmanelem[ lunmanx ] ],
                          wd, wmonths[ (wm-1L) ], wy);
                fprintf ( fptgt1, "%s\n", outbuf );

                // LINE 2.  Second of duplicated day
                sprintf ( outbuf, "%s/%s, %s/%s, %s, %s %d",
                          yogaS[ sbyorba ], yogaT[ sbyorba ],
                          byedS[ byedpax ], byedT[ byedpax ],
                          cycanim[ ld_animx ],
                          cycpar[ ld_parx ], ld_smex );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );

                // LINE 3. Second of duplicated
                sprintf ( outbuf,
                      "%d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d",
                          gzadag[0], gzadag[1], gzadag[2],
                          cur_monlong[0], cur_monlong[1], cur_monlong[2],
                          nyidag[0], nyidag[1], nyidag[2],
                          sbyorlong[0], sbyorlong[1], sbyorlong[2],
                          ZS_s, ZS_d, ZS_m );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );                                  

                // LINE 4. Second of duplicated
                sprintf ( outbuf, "Solar: %s-%s. %s" ,
                          cycelem1[ sd_elemx ],
                          cycanim[ sd_animx ],
                          Clunman[ sd_clunmanx ] );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );
                
                if ( tt == 15 || tt == 30 )
                  {
                    do_plans ( spizag );     
                    prn_plans ();
                    do_rahu ( cur_mth, tt );  
                    prn_rahu (tt);
                  }

                } // END OF if ( lhag )
              else  // NO LHAG - NORMAL DAY 
                {
//  CALCULATE LUNAR MANSION AT SUNRISE, AND END OF SOLAR DAY:  

                clear_a_b ();                
                listb[0] = 0L;
                for ( i = 1; i < 5; ++i )
                  listb[i] = gzadag[i];
                l2bcd ( bcdx0, sun_f );
                mulbcdl ( bcdx0, bcdx0, listb[4] );
                divbcdl ( bcdx1, bcdx0, gza_f );
                listb[4] = bcd2l ( bcdx1 ); 
                sub_gen ( cur_monlong, tt_monlong, listb, 27L, sun_f );
                lunmanx = cur_monlong[0];                 
// This is now the moon longitude at daybreak of current day             

// NOW, CALCULATE FOR END OF CURRENT, NORMAL, SOLAR DAY:

                clear_a_b ();                
                listb[0] = 1L;
                for ( i = 1; i < 5; ++i )
                  lista[i] = gzadag[i]; // Previous lunar day
                sub_gen ( listb, listb, lista, 7L, gza_f );
                l2bcd ( bcdx0, sun_f );
                mulbcdl ( bcdx0, bcdx0, listb[4] );
                divbcdl ( bcdx1, bcdx0, gza_f );
                listb[4] = bcd2l ( bcdx1 ); 
                add_gen ( scd_monlong, tt_monlong, listb, 27L, sun_f );
                mak_lmchange_string ( cur_monlong, scd_monlong, doweek );                

// CALCULATE SBYORBA: -- normal day

        add_gen ( sbyorlong, cur_monlong, nyidag, 27L, sun_f );
        sbyorba = sbyorlong[0];               
      
// NOW CALCULATE BYED PA:

        byedpax = calc_byedpa ( cur_monlong, nyidag );
                    
        gen_phrod ( lunmanx, doweek, cur_monlong[1] );           
    
// For 'phrod chen/sbyor:
        get_phrochen ( &phrodx, doweek, lunmanx, cur_monlong[1] );
    
                // LINE 1. NORMAL DAY 
                sprintf ( outbuf, "%d: %s. %s/%s. %s-%s; %d %s %d",
                          tt,
                          dayoweek[ doweek ],
                          lunmanS[ lunmanx ], lunmanT[ lunmanx ],
                          fourelem[ dowkelem[ doweek ] ],
                          fourelem[ lunmanelem[ lunmanx ] ],
                          wd, wmonths[ (wm-1L) ], wy);
                fprintf ( fptgt1, "%s\n", outbuf );

                // LINE 2. NORMAL DAY 
                sprintf ( outbuf, "%s/%s, %s/%s, %s, %s %d",
                          yogaS[ sbyorba ], yogaT[ sbyorba ],
                          byedS[ byedpax ], byedT[ byedpax ],
                          cycanim[ ld_animx ],
                          cycpar[ ld_parx ], ld_smex );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );

                // LINE 3. NORMAL DAY 

                sprintf ( outbuf,
                  "%d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d",
                          gzadag[0], gzadag[1], gzadag[2],
                          cur_monlong[0], cur_monlong[1], cur_monlong[2],
                          nyidag[0], nyidag[1], nyidag[2],
                          sbyorlong[0], sbyorlong[1], sbyorlong[2],
                          ZS_s, ZS_d, ZS_m );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf ); //-- NEEDED ???

                // LINE 4. Normal day 
                sprintf ( outbuf, "Solar: %s-%s. %s" ,
                              cycelem1[ sd_elemx ],
                              cycanim[ sd_animx ],
                              Clunman[ sd_clunmanx ] );
                fprintf ( fptgt1, "\x20\x20%s\n", outbuf );

// LINE 5.
            if ( !delaymth && chk_spec ( mthnum, tt ) )
              {
                fprintf ( fptgt1, "  %s\n", outbuf );
              }
            if ( chk_sadag2 ( mthnum, tt ) )
              fprintf ( fptgt1, "\x20\x20\x20\x20%s\n", sadag_str2 );              
                          
            if ( tt == 15 || tt == 30 )
              {
                do_plans ( spizag );     
                prn_plans ();
                do_rahu ( cur_mth, tt );  
                prn_rahu (tt);
              }                                            

                } // End of normal day, no "lhag" -- to here

// LINE 5a, Normal day or duplicated  

          } // End of normal or duplicated; ie. not omitted. 
              
            ++ltt;  
            newmth = 0;
            lastjd = juldat;
          } while ( ltt <= 30 ); // End of day loop 

        newmth = 1;
        if ( !zeromthfg )
          ++tm;
        if ( tm > 12L )
          {
            ++ty;
            tm = 1L;
          }
        if ( adj_mth == 12L )
          {
            // First check for following intercalary:
            // Check removed; no longer needed.
            more = 0; // We have finished.
          }
      } while ( more );       // End of month loop

    if ( full_print )   
      prn_cal2 ( cur_year );

    fclose ( fptgt1 );  
    if ( cur_year < last_year )
      {
        ++cur_year;
        goto donextyear;
      }
  } // END - prn_cal ()
  
void prn_plans ( void )
  {
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, marmurdag );  
    sprintf ( outbuf, "\nMars, slow: %d;%d,%d,%d,%d - fast: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    mardaldag[0], mardaldag[1], mardaldag[2], mardaldag[3], mardaldag[4],
    marmurdag[0], marmurdag[1], marmurdag[2], marmurdag[3], marmurdag[4], plandirE[mar_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt1, "%s", outbuf );        
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, jupmurdag );
    sprintf ( outbuf, "Jupiter, slow: %d;%d,%d,%d,%d - fast: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    jupdaldag[0], jupdaldag[1], jupdaldag[2], jupdaldag[3], jupdaldag[4],
    jupmurdag[0], jupmurdag[1], jupmurdag[2], jupmurdag[3], jupmurdag[4], plandirE[jup_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt1, "%s", outbuf );                
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, satmurdag );
    sprintf ( outbuf, "Saturn, slow: %d;%d,%d,%d,%d - fast: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    satdaldag[0], satdaldag[1], satdaldag[2], satdaldag[3], satdaldag[4],
    satmurdag[0], satmurdag[1], satmurdag[2], satmurdag[3], satmurdag[4], plandirE[sat_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt1, "%s", outbuf );                
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, mermurdag );
    sprintf ( outbuf, "Mercury, slow: %d;%d,%d,%d,%d - fast: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    merkanbar[0], merkanbar[1], merkanbar[2], merkanbar[3], merkanbar[4],
    mermurdag[0], mermurdag[1], mermurdag[2], mermurdag[3], mermurdag[4], plandirE[mer_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt1, "%s", outbuf );                
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, venmurdag );
    sprintf ( outbuf, "Venus, slow: %d;%d,%d,%d,%d - fast: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    venkanbar[0], venkanbar[1], venkanbar[2], venkanbar[3], venkanbar[4],
    venmurdag[0], venmurdag[1], venmurdag[2], venmurdag[3], venmurdag[4], plandirE[ven_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt1, "%s", outbuf );        
 } // END - prn_plans 
 
void prn_rahu ( int tt )
  {
    if ( tt == 15 )
      {
        sprintf ( outbuf, "Rahu, head: %d;%d,%d,%d,%d", 
        rahudong[0], rahudong[1], rahudong[2], rahudong[3], rahudong[4] );
        if ( cal_print ) // Flag to indicate calendar printing.        
          fprintf ( fptgt1, "%s\n\n", outbuf );        
      }
    else if ( tt == 30 )      
      {
        sprintf ( outbuf, "Rahu, head: %d;%d,%d,%d,%d", 
        rahudong30[0], rahudong30[1], rahudong30[2], rahudong30[3], rahudong30[4] );      
        if ( cal_print ) // Flag to indicate calendar printing.        
          fprintf ( fptgt1, "%s\n\n", outbuf );        
      }                    
  } // END - prn_rahu ()
  