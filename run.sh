#/bin/bash

if [[ "$1" =~ ".seq" ]]; then 
  echo ------ doing: $0 $1
else
  echo do: $0 Rec_test.seq
  break
fi

mkdir -p results/fout

echo '------ seq to binary' 
./seqtobinary.pl $1
echo '------ binary to text'
source binarytorawtext.sh

#$2: thermal couple data for ambient temperature
#$3: thermal varialbe: T1 or T2 or T3 or T4
source texttoroot.sh $2 $3
if [[ "$2" != "" ]]; then
  echo 'thermal couple data: '$2''
fi
if [[ "$3" != "" ]]; then
  echo 'thermal couple variable: '$3''
fi


rm -rf results/tout results/fout
