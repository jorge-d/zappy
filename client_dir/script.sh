#!/bin/sh

i=0

while [ $i -lt 10 ]
do
    xterm -e "php ./start.php -h 10.200.24.25 -p 4242 -n toto" &
    i=`echo $i+1 | bc`
done