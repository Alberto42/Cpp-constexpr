#!/usr/bin/env bash
for i in {601..604}
do
    echo -n "****************************************************************************Test numer "
    echo  $i
    g++ -std=c++17 bakery.h pie.h cake.h bakery_test.cc -DTEST_NUM=$i -o Test
    ./Test
#    if [ -s output ]
#        then echo "brak bledu kompilacji"
#    else
#        echo "blad kompilacji"
#    fi
done
