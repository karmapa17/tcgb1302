wc = wcl386
flags = /c /cc /ms /W3 /3 /fpi /omax /zp1 /bt=NT

tcgbk.exe: t1.obj t2.obj t2a.obj t3.obj t4.obj t4a.obj t4b.obj t5.obj utils.obj tests.obj bcd.obj
    wlink system nt name tcgbk file t1, t2, t2a, t3, t4, t4a, t4b, t5, utils, tests, bcd

t1.obj: t1.c  tc.h tc.def bcd.h
        $(wc) $(flags) t1.c

t2.obj: t2.c  tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t2.c

t2a.obj: t2a.c  tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t2a.c

t3.obj: t3.c tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t3.c

t4.obj: t4.c tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t4.c

t4a.obj: t4a.c tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t4a.c

t4b.obj: t4b.c tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t4b.c

t5.obj: t5.c tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) t5.c

utils.obj: utils.c tc.h tc.def tc.ext bcd.h
        $(wc) $(flags) utils.c

tests.obj: tests.c tc.h
        $(wc) $(flags) tests.c

bcd.obj: bcd.c bcd.h
        $(wc) $(flags) bcd.c
