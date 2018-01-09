// t1.c - main control routines
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

FILE *repfil;

void chk_bcd ( void );

void cal_cyc ( void ) // Main routine
  {
    int more, n, newmth, i, x;
    int juldat_m;
    double jdf_m, jdf_t, nyibarf;
    double obs_long = 91.0; // Observer longitude, set for Lhasa.
    char chr;
    restart: cls ();
    printf ( "%s\n", e_str[epch-1] );
    printf ("Enter the starting date, month and year: ");
    scanf ("%d %d %d", &tt, &tm, &ty);
    printf ("\n");
    n = 0;
    more = 1;
    newmth = 1;
    while (more)
      {
        if ( newmth )
          {
            if ( !zeromthfg )   // We need to use the same data, twice.
              zla_dag (ty, tm);  // KTC 16
            adj_zla ();
            cur_mth = zladag[0];
            gza_dru (cur_mth);  // KTC 18
            nyi_dru (cur_mth);  // KTC 22
            nyi_dru_b (cur_mth);  // KTC 22            
            rilchaf ( cur_mth ); // KTC 21
          }

backtoprint:
        cls ();
        printf ( "%s\n", e_str[epch-1] );

        if ( printinprog )
          {
            sprintf ( printstring, "\n%s\n", e_str[epch-1] );
            prin_str ( printstring );
          }

        printf ("\nThe ZLA-DAG is: %d;%d, ", zladag[0], zladag[1]);
        printf ("Month = %d, ", tm );
        printf ("Year = %d\n", ty );

        if ( printinprog )
          {
            sprintf ( printstring,
              "The ZLA-DAG is: %d;%d, Month = %d, Year = %d",
               zladag[0], zladag[1], tm, ty );
            prin_str ( printstring );
          }

        printf ("DATE is: %d / %d / %d,  ", tt, tm, ty);

        x = adj_mth;
        if ( x < 0 )
          x = -x;
        x = x - 2;
        if ( x < 0 )
          x = x + 12;

        printf ( "Corrected Month = %d, %s\n", adj_mth, lunmont[x] );

        if ( printinprog )
          {
            sprintf ( printstring,
              "DATE is: %d / %d / %d - Corrected Month = %d, %s\n",
               tt, tm, ty, adj_mth, lunmont[x] );
            prin_str ( printstring );
          }

        tse_dru (tt);
        nyi_lon (tt);
        nyi_lon_b (tt);        
        add_gen (tsebar, gzadru, tsedru, 7L, gza_f ); // KTC 23
        add_gen (nyibar, nyidru, nyilon, 27L, sun_f ); // KTC 23
        add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b ); // KTC 23     
        nyibarl = exp_lst ( nyibar, sun_f ); // These are for time of day
        tsebarl = exp_lst ( tsebar, gza_f ); // and western comparisons
        nyibarf = 360.0 * (double) nyibarl /
                  (double) ( 27L * 60L * 60L * 6L * sun_f );
        tsebarl = tsebarl - tsebar[0] * 60L * 60L * 6L * gza_f;
        nyi_dag (nyibar);  // Must be done before gza_dag - KTC 31
       
        nyi_dag_b (nyibar_b);  // Must be done before gza_dag - KTC 31        
        gza_dag (tsebar);  // KTC 24
        do_rahu ( cur_mth, tt );  // in T2.C - KTC 96
        printf ( "%s\n", printstring ); // Prints Rahu data
        
        spi_zagf ();   // In T2.C - calculates juldat. KTC 46

// Julian calculated is for the integer Julian day count at noon
// GMT on weekday of "gza' dag". In juldat.

        printf ( "ril cha = %d;%d\n", rilcha[0], rilcha[1] );

        if ( printinprog )
          {
            sprintf ( printstring, "ril cha = %d;%d",
                      rilcha[0], rilcha[1] );
            prin_str ( printstring );
          }

        printf ("The gza-bar is: ");
        prn_lst ( tsebar );

        if ( printinprog )
          {
            sprintf ( printstring, "The gza-bar is: %d;%d,%d,%d,%d",
              tsebar[0], tsebar[1], tsebar[2], tsebar[3], tsebar[4] );
            prin_str ( printstring );
          }

        printf ("The (grub) nyi-bar is: ");
        prn_lstd ( nyibar, sun_f, 1L );
        printf ("The (byed) nyi-bar is: ");
        prn_lstd ( nyibar_b, sun_f_b, 1L );        

        if ( printinprog )
          {
            sprintf ( printstring, "The (grub) nyi-bar is: %d;%d,%d,%d,%d",
              nyibar[0], nyibar[1], nyibar[2], nyibar[3], nyibar[4] );
            prin_str ( printstring );
            sprintf ( printstring, "The (byed) nyi-bar is: %d;%d,%d,%d,%d",
              nyibar_b[0], nyibar_b[1], nyibar_b[2], nyibar_b[3], nyibar_b[4] );
            prin_str ( printstring );            
          }

        printf ("The gza-dag is: ");
        prn_lst ( gzadag );

        if ( printinprog )
          {
            sprintf ( printstring, "The gza-dag is: %d;%d,%d,%d,%d",
              gzadag[0], gzadag[1], gzadag[2], gzadag[3], gzadag[4] );
            prin_str ( printstring );
          }

        printf ("The (grub) nyi-dag is: ");
        prn_lstd ( nyidag, sun_f, 1L );
        printf ("The (byed) nyi-dag is: ");
        prn_lstd ( nyidag_b, sun_f_b, 1L );        

        if ( printinprog )
          {
            sprintf ( printstring, "The nyi-dag is: %d;%d,%d,%d,%d",
              nyidag[0], nyidag[1], nyidag[2], nyidag[3], nyidag[4] );
            prin_str ( printstring );
            sprintf ( printstring, "The (byed) nyi-dag is: %d;%d,%d,%d,%d",
              nyidag_b[0], nyidag_b[1], nyidag_b[2], nyidag_b[3], nyidag_b[4] );
            prin_str ( printstring );            
          }

// Now, calculate Moon at lunar day and daybreak:
        clrlst (mondag);
        clrlst (monsar);
        mondag[1] = 54L; // separation in one lunar day.
        mul_gen ( mondag, mondag, tt, 27L, sun_f );
        add_gen ( mondag, nyidag, mondag, 27L, sun_f ); // KTC 42
        for ( i = 0; i < 6; ++i )
          monsar[i] = gzadag[i];
        monsar[0] = 0L;
        monsar[5] = ( monsar[5] * sun_f ) / gza_f;
        sub_gen ( monsar, mondag, monsar, 27L, sun_f); // KTC 43

        sprintf ( printstring,
                  "Moon, Lunar day: %d;%d,%d,%d,%d,%d - \
Daybreak: %d;%d,%d,%d,%d,%d.",
                mondag[0], mondag[1], mondag[2], mondag[3], mondag[4],
                mondag[5], monsar[0], monsar[1], monsar[2], monsar[3],
                monsar[4], monsar[5] );

        printf ( "%s\n", printstring );
        if ( printinprog )
          prin_str ( printstring );

        printf ("General day factors: %d, %d\n", spz_frac_b, spz_frac_c );

        if ( printinprog )
          {
            sprintf ( printstring, "General day factors: %d, %d",
                                   spz_frac_b, spz_frac_c );
            prin_str ( printstring );
          }

        do_plans ( spizag );   // In T3.C
        
    printf ( "Mars sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	mar_gz, mardaldag[0], mardaldag[1], mardaldag[2], mardaldag[3], mardaldag[4],
        marmurdag[0], marmurdag[1], marmurdag[2], marmurdag[3], marmurdag[4] );
    printf ( "Jupiter sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	jup_gz, jupdaldag[0], jupdaldag[1], jupdaldag[2], jupdaldag[3], jupdaldag[4],
        jupmurdag[0], jupmurdag[1], jupmurdag[2], jupmurdag[3], jupmurdag[4] );
    printf ( "Saturn sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	sat_gz, satdaldag[0], satdaldag[1], satdaldag[2], satdaldag[3], satdaldag[4],
        satmurdag[0], satmurdag[1], satmurdag[2], satmurdag[3], satmurdag[4] );
    printf ( "Mercury sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	mer_gz, merkanbar[0], merkanbar[1], merkanbar[2], merkanbar[3], merkanbar[4],
        mermurdag[0], mermurdag[1], mermurdag[2], mermurdag[3], mermurdag[4] );
    printf ( "Venus sgos zhag = %d: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d\n", 
	ven_gz, venkanbar[0], venkanbar[1], venkanbar[2], venkanbar[3], venkanbar[4],
        venmurdag[0], venmurdag[1], venmurdag[2], venmurdag[3], venmurdag[4] );        

        printf ( "SPYI ZHAG = %d. ", spizag );
        printf ( "Julian day = %d. ", juldat );
        printf ( "Western date = %s, %d/%d/%d\n",
                  dayoweek[ doweek ], wd, wm, wy);

        if ( printinprog )
          {
            sprintf ( printstring,
    "SPYI ZHAG = %d. Julian day = %d. Western date = %s, %d/%d/%d",
              spizag, juldat, dayoweek[ doweek ], wd, wm, wy);
            prin_str ( printstring );
          }

// To calculate exact Julian day for TRUE lunar day (tithi):
// Julian day at 5.00 LMST:

        jdf_t = (double) juldat - obs_long / 360.0 - 7.0 / 24.0;

// Now add time of true tithi:

        jdf_t = jdf_t + gzadag[1] / 60.0 + gzadag[2] / 3600.0 + gzadag[3] /
                21600.0 + gzadag[4] / ( 21600.0 * (double) gza_f );

// NOW CALCULATE FOR MEAN TITHI:

        if ( tsebar[0] == gzadag[0] )
          juldat_m = juldat;
        else if ( tsebar[0] == gzadag[0] - 1L || tsebar[0] == gzadag[0] + 6L )
          juldat_m = juldat - 1L;
        else if ( tsebar[0] == gzadag[0] + 1L || tsebar[0] == gzadag[0] - 6L )
          juldat_m = juldat + 1L;
        else
          {
            printf ( "Serious problem with GZA! - bar: %d, dag: %d\n",
                      tsebar[0], gzadag[0] );
          }

// Julian day at 5.00 LMST:

        jdf_m = (double) juldat_m - obs_long / 360.0 - 7.0 / 24.0;

// Now add for time of mean tithi:

        jdf_m = jdf_m + tsebar[1] / 60.0 + tsebar[2] / 3600.0 + tsebar[3] /
                21600.0 + tsebar[4] / ( 21600.0 * (double) gza_f );

        printf ( "Julian tithi time, mean: %f, true: %f\n", jdf_m, jdf_t );

        if ( printinprog )
          {
            sprintf ( printstring, "Julian tithi time, mean: %f, true: %f\n",
                                   jdf_m, jdf_t );
            prin_str ( printstring );
          }

        printinprog = 0;  // turn off printing to report.dat
       
// Change for Win32 console app:

        printf ( "\nNew date, Tshespa/lunar day, Month, Year, Report, Previous lunar day, Exit\n\n" );

        printf ("\n");

        if ( chr == 'N' || chr == 'n' )
          goto restart;
        if ( chr == 'R' || chr == 'r' )
          {
            if ( !print_on )
              {
                start_print ();
                print_on = 1;
              }
            printinprog = 1;
            goto backtoprint;
          }
        if ( chr == 'E' || chr == 'e' )
          more = 0;
        else if ( chr == 'T' || chr == 't' )
          {
            ++tt;
            newmth = 0;
            if ( tt == 31L )
              {
                newmth = 1;
                tt = 1;
                if ( !zeromthfg )
                  ++tm;
                if ( tm > 12 )
                  {
                    ++ty;
                    tm = 1;
                  }
              }
          }
        else if ( chr == 'P' || chr == 'p' )  // Previous day
          {
            --tt;
            newmth = 0;
            if ( tt == -1L )
              {
                newmth = 1;
                tt = 29;
                if ( !zeromthfg )
                  --tm;
                if ( tm == 0L )
                  {
                    --ty;
                    tm = 12;
                  }
              }
          }
        else if ( chr == 'M' || chr == 'm' )
          {
            newmth = 1;
            if ( ! zeromthfg )
              ++tm;
            if ( tm > 12 )
              {
                ++ty;
                tm = 1;
               }
          }
        else if ( chr == 'Y' || chr == 'y' )
          {
            ++ty;
            newmth = 1;
            zeromthfg = 0;
          }
      }
  } // END - cal_cyc ()
