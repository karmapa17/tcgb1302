// t5.c - all routines and data for printing to disk a full calendar
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

extern int   /*  nxt_nyidag[6], nxt_gzadag[6],*/ nxt_monlong[6];
extern int fst_monlong[6], cur_monlong[6], scd_monlong[6], tt_monlong[6];

void prn_cal2 ( int cy )
  {
    int i, more, n, newmth, lhag, chad, nextchad, nextlhag;
    int dgax; //, lunmx;
    int intercal, delaymth;
    int yr_gender;    // 1 = female, odd; 0 = male, even
    int mt_gender;    // 1 = female, odd; 0 = male, even
    int mthnum; // Adjusted, without negative.
    int cur_year; 
    int ltt, zla0, zla1;
    int lastjd = 0L;
    int curjd, nextjd; // Last and next JD calculations.
    int  lunmanx, sbyorba, byedpax;
    int  prv_lunmanx, fst_sbyorba, fst_byedpax;
    int fst_lunmanx; 
    int Cmonth;
    int tenbrelx;
    int sd_clunmanx;
    int ld_parx;
    int ld_smex, sd_smex;
    int yr_animx, mt_animx, ld_animx, sd_animx;
    int yr_elemx, mt_elemx, sd_elemx;
    int e, g, x5, x6;
    int new_year;

    set_lang ();
    gza_short_flg = 0; // Flag for less accurate weekday adjustment

    cur_year = cy;

    new_year = 1;
    ty = cur_year;
    tm = 1L;
    zeromthfg = 0;

    sprintf ( filenam, "ts2_%d.txt", ty );
    fptgt = fopen ( filenam, "w" );
    if ( fptgt == NULL )
      {
        printf ( "Error opening target file!\n" );
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
                sprintf ( outbuf, "\nNew Year: %d, %s-%s-%s\n", ty,
                                  cycelem1T[ yr_elemx ],
                                  cycgendT[ yr_gender ],
                                  cycanimT[ yr_animx ] );
                fprintf ( fptgt, "%s", outbuf );
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
          -adj_mth, cycelem1T[ mt_elemx ],
          cycgendT[ mt_gender ], cycanimT[ mt_animx ] );

        else if ( delaymth )
          sprintf ( outbuf, "Tibetan Lunar Month: %d (Delayed) - %s-%s-%s",
          adj_mth, cycelem1T[ mt_elemx ],
          cycgendT[ mt_gender ], cycanimT[ mt_animx ] );
          
        else
          sprintf ( outbuf, "Tibetan Lunar Month: %d - %s-%s-%s",
          adj_mth, cycelem1T[ mt_elemx ],
          cycgendT[ mt_gender ], cycanimT[ mt_animx ] );

        printf ( "%s\n", outbuf );
        fprintf ( fptgt, "\n%s\n", outbuf );

        sprintf ( outbuf, "Month: %d;%d", zladag[0], zladag[1] );
        fprintf ( fptgt, "\n%s\n", outbuf );
        sprintf ( outbuf, "Anomaly: %d;%d", rilcha[0], rilcha[1] );
        fprintf ( fptgt, "%s\n", outbuf );

        tse_dru (0L);
        nyi_lon_b (0L);        
        add_gen (tsebar, gzadru, tsedru, 7L, gza_f);
        add_gen (nyibar_b, nyidru_b, nyilon_b, 27L, sun_f_b );        
        nyi_dag_b (nyibar_b); // MUST BE DONE FIRST        
        for ( i = 0; i < 6; ++i )
          nyidag[i] = nyidag_b[i];
        gza_dag (tsebar);
        tt = 0L;
        spi_zagf ();

        x6 = gzadru[4] * 13;
        x5 = x6 / 707;
        x6 = x6 - x5 * 707;
        sprintf ( outbuf, "Mean Weekday: %d;%d,%d,%d,%d,%d",
                          gzadru[0], gzadru[1], gzadru[2], gzadru[3], x5, x6 );        
        fprintf ( fptgt, "%s\n", outbuf );        
        x6 = nyidru[4] * 13;
        x5 = x6 / 67;
        x6 = x6 - x5 * 67;        
        sprintf ( outbuf, "Mean Sun: %d;%d,%d,%d,%d",
                          nyidru_b[0], nyidru_b[1], nyidru_b[2], nyidru_b[3], x5, x6 );
        fprintf ( fptgt, "%s\n\n", outbuf );
       
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
// LINE 1 - Omitted            
                sprintf ( outbuf, "%d. Omitted. %s",
                          tt, dgaT[dgax] );
// Should include "gza'" for end of lunar day, plus solar longitude.???
                fprintf ( fptgt, "%s\n\n", outbuf );

                sprintf ( outbuf,
                    "No: %d;%d,%d %d;%d,%d",
                     gzadag[0], gzadag[1], gzadag[2],
                     nyidag[0], nyidag[1], nyidag[2] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );            

                if ( tt == 15 || tt == 30 )
                  {
                    do_plans ( spizag - 1L );                
                    sprintf ( outbuf, "Planets (%d):", spizag - 1L );
                    fprintf ( fptgt, "\n%s\n", outbuf );
                    prn_plans2 ();                
                    do_rahu ( cur_mth, tt );                     
                    prn_rahu2 (tt);                     
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

// Now calculate yoga, sbyor ba: -- First of duplicated day

        add_gen ( fst_sbyorlong, fst_monlong, nyidag, 27L, sun_f ); 
        fst_sbyorba = fst_sbyorlong[0];

// Now calculate karana, sbyed pa:  

        fst_byedpax = calc_byedpa ( fst_monlong, nyidag );
        juldat = juldat - 1L;
        jul2date ( juldat ); // This is normally done by spi_zagf

// Solar day data: - calculating for first of duplicated day

        sd_animx = ( juldat - 2L ) % 12L;
        sd_elemx = ( ( juldat - 3L ) / 2L ) % 5L;
        sd_clunmanx = ( juldat - 17L ) % 28L;
        sd_smex = ( juldat - 2L ) % 9L + 1L; 

// For general and special "'phrod":

        gen_phrod ( fst_lunmanx, doweek, fst_monlong[1] );

// For 'phrod chen/sbyor:
        get_phrochen ( &phrodx, doweek, prv_lunmanx, prv_monlong[1] );
              
               // LINE 1. - First of duplicated day
               //                   a   b   c   d    
                sprintf ( outbuf, "%d: %s. %s. d) %s",
                          tt, dgaT[dgax], 
                          dayoweekT[ doweek ],
                          lunmanP[ fst_lunmanx ] );
                fprintf ( fptgt, "%s\n", outbuf );
                
                sprintf ( outbuf, "e) %s-%s",
                          fourelemT[ dowkelem[ doweek ] ], // e
                          fourelemT[ lunmanelem[ fst_lunmanx ] ] ); // e
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                
                
                sprintf ( outbuf, "f) %s", phrodchen[phrodx] ); // f
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                                

                // LINE 2. First of duplicated day - g h
                
                sprintf ( outbuf, "g) %s", lmchg );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

                sprintf ( outbuf, "h) %s", gen_phrod_str );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                
                
                // LINE 3 First of duplicated day
                sprintf ( outbuf, "i) %s", yogaP[fst_sbyorba] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                sprintf ( outbuf, "j) %s", tenbrelT[tenbrelx] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                                

                sprintf ( outbuf, "k) %s", bishti_str );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                
                
                // LINE 4. First of duplicated day
                //                 l                
                sprintf ( outbuf, "l) %s %s %d",
                          cycanimT[ ld_animx ], cycpar[ ld_parx ], ld_smex );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                          

                // LINE 5. First of duplicated day
                //                    m
                if ( chk_sadag ( mthnum, tt ) )
                  {
                    sprintf ( outbuf, "m) %s", sadag_str );
                    fprintf ( fptgt, "\x20\x20%s\n", outbuf );
                  }                                
                
                // LINE 6. First of duplicated day - tshes kyi gnam sgo (N) namgo_str
                
                sprintf ( outbuf, "n) %s", namgo_str );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                // LINE 7. First of duplicated day - o, p
                sprintf ( outbuf, "o) %s-%s", cycelem1T[ sd_elemx ], cycanimT[ sd_animx ] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );
                
                sprintf ( outbuf, "p) %s", ClunmanK[ sd_clunmanx ] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                
                
                // LINE 6. First of duplicated day                
                
                sprintf ( outbuf,
                    "No: %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d",
                       ( prv_gzadag[0] + 1L ) % 7L, 60L, 0L,
                       fst_monlong[0], fst_monlong[1], fst_monlong[2],
                       nyidag[0], nyidag[1], nyidag[2],
                       fst_sbyorlong[0], fst_sbyorlong[1], fst_sbyorlong[2],
                       ZS_s, ZS_d, ZS_m );                       
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

                // LINE 7. First of duplicated day
                  
                sprintf ( outbuf, "%02d.%02d.%4d", wd, wm, wy );                          
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

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
            mak_lmchange_string ( cur_monlong, scd_monlong, doweek );
                // LINE 1. second of duplicated 
                sprintf ( outbuf, "%d: %s. %s.",                
                          tt, 
                          dayoweekT[ doweek ],
                          lunmanP[ lunmanx ] ); // f
                fprintf ( fptgt, "%s\n", outbuf );
                
                sprintf ( outbuf, "e) %s-%s",                
                          fourelemT[ dowkelem[ doweek ] ], // e
                          fourelemT[ lunmanelem[ lunmanx ] ] ); 
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                sprintf ( outbuf, "f) %s", phrodchen[phrodx] ); // f
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                                
                
                // LINE 2. second of duplicated - g h
                
                sprintf ( outbuf, "g) %s", lmchg );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                sprintf ( outbuf, "h) %s", gen_phrod_str );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                // LINE 3. second of duplicated                 
                //                              i                     
                sprintf ( outbuf, "i) %s", yogaP[sbyorba] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );    
                
                // LINE 4. second of duplicated -- o p 

                sprintf ( outbuf, "o) %s-%s", cycelem1T[ sd_elemx ], cycanimT[ sd_animx ] );                
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                sprintf ( outbuf, "p) %s", ClunmanK[ sd_clunmanx ] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                                

                // LINE 5. Second of duplicated 
                
                sprintf ( outbuf,
                      "No: %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d",
                          gzadag[0], gzadag[1], gzadag[2],
                          cur_monlong[0], cur_monlong[1], cur_monlong[2],
                          nyidag[0], nyidag[1], nyidag[2],
                          sbyorlong[0], sbyorlong[1], sbyorlong[2],
                          ZS_s, ZS_d, ZS_m ); 
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

                sprintf ( outbuf, "%02d.%02d.%4d", wd, wm, wy );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

                if ( tt == 15 || tt == 30 )
                  {
                    do_plans ( spizag ); //-- second of duplicated
                    sprintf ( outbuf, "Planets (%d):", spizag );
                    fprintf ( fptgt, "\n%s\n", outbuf );
                    prn_plans2 ();                    
                    do_rahu ( cur_mth, tt );                     
                    prn_rahu2 (tt);                     
                  }
                } // END OF if ( lhag )
              else  // No lhag - normal day 
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
                sprintf ( outbuf, "%d: %s. %s. %s. \n  e) %s-%s \n  f) %s",
                          tt, dgaT[dgax],
                          dayoweekT[ doweek ],
                          lunmanP[ lunmanx ],
                          fourelemT[ dowkelem[ doweek ] ], // e
                          fourelemT[ lunmanelem[ lunmanx ] ], // e
                          phrodchen[phrodx] ); // f
                fprintf ( fptgt, "%s\n", outbuf );
                
                // LINE 2. NORMAL DAY - g h     
                
                sprintf ( outbuf, "g) %s \n  h) %s", lmchg, gen_phrod_str );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                

                // LINE 3 NORMAL DAY                 
                //                              i                      j                
                sprintf ( outbuf, "i) %s \n\x20\x20j) %s \n\x20\x20k) %s", yogaP[sbyorba], tenbrelT[tenbrelx], bishti_str );
                if ( bishti_str[0] > 0 ) // k
                  strcat ( outbuf, bishti_str );                    
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                
                
                // LINE 4. NORMAL DAY 
                //                 l
                sprintf ( outbuf, "l) %s %s %d",
                          cycanimT[ ld_animx ], cycpar[ ld_parx ], ld_smex );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                          

                // LINE 5. NORMAL DAY - m
                
               if ( chk_sadag ( mthnum, tt ) )
                 {
                   sprintf ( outbuf, "m) %s", sadag_str );
                   fprintf ( fptgt, "\x20\x20%s\n", outbuf );
                 }       
                 
                // LINE 6. NORMAL DAY - tshes kyi gnam sgo (N)                          

                sprintf ( outbuf, "n) %s", namgo_str );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                               
               
                // LINE 7. NORMAL DAY - o, p
                
                sprintf ( outbuf, "o) %s-%s \n\x20\x20p) %s",
                            cycelem1T[ sd_elemx ],
                            cycanimT[ sd_animx ],
                            ClunmanK[ sd_clunmanx ] );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );                
               
                // LINE 8. NORMAL DAY                
               
                sprintf ( outbuf,
                  "No: %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d %d;%d,%d",
                          gzadag[0], gzadag[1], gzadag[2],
                          cur_monlong[0], cur_monlong[1], cur_monlong[2],
                          nyidag[0], nyidag[1], nyidag[2],
                          sbyorlong[0], sbyorlong[1], sbyorlong[2],
                          ZS_s, ZS_d, ZS_m );
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

                sprintf ( outbuf, "%02d.%02d.%4d", wd, wm, wy );                          
                fprintf ( fptgt, "\x20\x20%s\n", outbuf );

                if ( tt == 15 || tt == 30 )
                  {
                    do_plans ( spizag );                
                    sprintf ( outbuf, "Planets (%d):", spizag );
                    fprintf ( fptgt, "\n%s\n", outbuf );
                    prn_plans2 ();                
                    do_rahu ( cur_mth, tt );                     
                    prn_rahu2 (tt);                     
                  }                  
              } // End of normal day, no "lhag"
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
            // Check removed - no longer needed.
              more = 0; // We have finished.
          }
      } while ( more );       // End of month loop

    fclose ( fptgt );
  } // END - prn_cal2 ()
  
void prn_plans2 ( void )
  {
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, marmurdag );
    sprintf ( outbuf, "\nMars, dal: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    mardaldag[0], mardaldag[1], mardaldag[2], mardaldag[3], mardaldag[4],
    marmurdag[0], marmurdag[1], marmurdag[2], marmurdag[3], marmurdag[4], plandirT[mar_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt, "%s", outbuf );        
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, jupmurdag );
    sprintf ( outbuf, "Jupiter, dal: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    jupdaldag[0], jupdaldag[1], jupdaldag[2], jupdaldag[3], jupdaldag[4],
    jupmurdag[0], jupmurdag[1], jupmurdag[2], jupmurdag[3], jupmurdag[4], plandirT[jup_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt, "%s", outbuf );                
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, satmurdag );
    sprintf ( outbuf, "Saturn, dal: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    satdaldag[0], satdaldag[1], satdaldag[2], satdaldag[3], satdaldag[4],
    satmurdag[0], satmurdag[1], satmurdag[2], satmurdag[3], satmurdag[4], plandirT[sat_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt, "%s", outbuf );                
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, mermurdag );
    sprintf ( outbuf, "Mercury, dal: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    merkanbar[0], merkanbar[1], merkanbar[2], merkanbar[3], merkanbar[4],
    mermurdag[0], mermurdag[1], mermurdag[2], mermurdag[3], mermurdag[4], plandirT[mer_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt, "%s", outbuf );                
    lm2signs ( &ZS_s, &ZS_d, &ZS_m, venmurdag );
    sprintf ( outbuf, "Venus, dal: %d;%d,%d,%d,%d - myur: %d;%d,%d,%d,%d %s %d;%d,%d\n", 
    venkanbar[0], venkanbar[1], venkanbar[2], venkanbar[3], venkanbar[4],
    venmurdag[0], venmurdag[1], venmurdag[2], venmurdag[3], venmurdag[4], plandirT[ven_d], ZS_s, ZS_d, ZS_m );      
    fprintf ( fptgt, "%s", outbuf );        
 } // END - prn_plans2 
 
void prn_rahu2 ( int tt )
  {
    if ( tt == 15 )
      {
        sprintf ( outbuf, "Rahu, gdong: %d;%d,%d,%d,%d", 
        rahudong[0], rahudong[1], rahudong[2], rahudong[3], rahudong[4] );
        if ( cal_print ) // Flag to indicate calendar printing.        
          fprintf ( fptgt, "%s\n\n", outbuf );        
      }
    else if ( tt == 30 )      
      {
        sprintf ( outbuf, "Rahu, gdong: %d;%d,%d,%d,%d", 
        rahudong30[0], rahudong30[1], rahudong30[2], rahudong30[3], rahudong30[4] );      
        if ( cal_print ) // Flag to indicate calendar printing.        
          fprintf ( fptgt, "%s\n\n", outbuf );        
      }                      
  } // END - prn_rahu2 ()
  
void lm2signs ( int * s, int * d, int * m, int *a1 )
  {
    *m = ( ( a1[0] * 60L + a1[1] ) * 60L + a1[2] ) * 6L + a1[3];
    l2bcd ( bcdx0, *m );
    mulbcdl ( bcdx0, bcdx0, 21600L );
    divbcdl ( bcdx1, bcdx0, 583200L ); // 27*60*60*6
    *m = bcd2l ( bcdx1 );
    *d = *m / 60L;
    *m = *m % 60L;
    *s = *d / 30L;
    *d = *d % 30L;
  } // END - lm2signs ()
  
