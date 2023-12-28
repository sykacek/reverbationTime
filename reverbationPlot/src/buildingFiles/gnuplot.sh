#! /usr/bin/gnuplot

set terminal png

do for[t in system("ls ../out/data/*.dat | cut -d/ -f4")]{
#    print ''.t
    set output '../out/images/'.t.'.png'
    set title 'Graf závislosti hladiny akustického tlaku na čase'
    set xlabel 'čas [s]'
    set ylabel 'hladina akustického tlaku [dB]'
    plot '../out/data/'.t w l title 'soubor '.t

}