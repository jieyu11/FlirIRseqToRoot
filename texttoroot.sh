#/bin/bash

mkdir -p results/roo

make clean
make
if [ ! $? ]; then
  break
fi

nfile=$(ls -l results/tout/seq_n*.pgm | wc -l)
if [[ ${nfile} -le 0 ]]; then
  echo no file found in results/tout/
  break
else
  echo number of files ${nfile}
fi

j=0

#specify the Emissivity value if needed: -E value in [0.000, 1.000], default: from .seq file
#the transmittance is set by: -Tau value in [0.000,1.000] default: 1.000
#the temperature of atmosphere is set: -Tatm value in C. default: 20.
#the temperature of reflection is set: -Tref value in C. default: from .seq file
 
#EmissivityUser=0.99
EmissivityUser=0.9
for ((jfile=1; jfile<=${nfile}; jfile++)); do
  remain=$(($jfile % 100))
  if [[ $remian -eq 0 ]]; then
    echo 'Using Emissivity = '$EmissivityUser'. Working on now: '$jfile'th file.'
  fi

  ffile=seq_n${jfile}.pgm 

  nameroo=${ffile/pgm/root}
  if [[ "$1" == "" ]]; then
    ./dana -E $EmissivityUser -In results/tout/$ffile -Out results/roo/$nameroo
  elif [[ "$2" == "" ]]; then
    ./dana -E $EmissivityUser -In results/tout/$ffile -Out results/roo/$nameroo -TatmFromFile $1
  else
    ./dana -E $EmissivityUser -In results/tout/$ffile -Out results/roo/$nameroo -TatmFromFile $1 -TatmVariable $2
  fi

  ls -l results/roo/$nameroo
  j=$((j+1))
done
 
