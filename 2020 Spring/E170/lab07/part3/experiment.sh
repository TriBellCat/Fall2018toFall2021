#!/bin/bash
i=1
size=256
if [ -f ./results.txt ]
then
        rm results.txt
fi
touch results.out
echo "Algorithm   Array size    FLOPS" >> results.txt
for i in 1 2
do
for size in {256..2048..256}
do
./matrix_math $i $size 2>&1 | tee temp.txt

perl -ni -e 'print unless $. <= 3' temp.txt

flops=$(awk '{last=match($0,"....E+..")
                s=substr($0,last)
                print s}' temp.txt)
echo -e "    " $i "       " $size " \t" $flops >> results.txt

rm temp.txt
done
done
