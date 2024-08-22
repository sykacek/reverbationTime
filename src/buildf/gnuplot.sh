#! /usr/bin/gnuplot

set terminal png

do for[t in system("ls output/data/*.dat | cut -d/ -f3")] {
#    print ''.t
    set output 'output/images/'.t.'.png'
    set title 'Sound Pressure Level - time'
    set xlabel 't [s]'
    set ylabel 'SPL [dB]'
    plot 'output/data/'.t w l title 'file '.t
}