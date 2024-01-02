#! /usr/bin/gnuplot

set terminal png

do for[t in system("ls ../out/data/*.dat | cut -d/ -f4")]{
#    print ''.t
    set output '../out/images/'.t.'.png'
    set title 'Sound Pressure Level - time'
    set xlabel 't [s]'
    set ylabel 'SPL [dB]'
    plot '../out/data/'.t w l title 'soubor '.t

}
