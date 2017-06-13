#/bin/bash

#
# This code convert raw data from .fff (produced by seqtobinary.pl) to 
# text files in results/tout
#

mkdir -p results/tout results/roo

j=0
for ffile in `ls results/fout`; do
  Flir=$(exiftool -Flir:all "results/fout/$ffile")
  if [ $j == 0 ]; then
    Type=$(echo "$Flir" | grep "Raw Thermal Image Type" | cut -d: -f2)
    if [ "$Type" != " TIFF" ]
        then 
            echo "only for RawThermalImage=TIFF"
            exit 1
    fi
    
    #
    # parameters used to convert raw data to temperature later
    # 
    R1=$(echo "$Flir" | grep "Planck R1" | cut -d: -f2)
    R2=$(echo "$Flir" | grep "Planck R2" | cut -d: -f2)
    B=$(echo "$Flir" | grep "Planck B" | cut -d: -f2)
    O=$(echo "$Flir" | grep "Planck O" | cut -d: -f2)
    F=$(echo "$Flir" | grep "Planck F" | cut -d: -f2)
    Emissivity=$(echo "$Flir" | grep "Emissivity" | cut -d: -f2)
    ReflTemp=$(echo "$Flir" | grep "Reflected Apparent Temperature" | sed 's/[^0-9.-]*//g')

    echo R1 $R1 >  config
    echo R2 $R2 >> config
    echo B  $B  >> config
    echo O  $O  >> config
    echo F  $F  >> config
    echo Emissivity  $Emissivity  >> config
    echo ReflTemp $ReflTemp >> config
    #echo Time $Time >> config
  fi


  namepng=${ffile/fff/png}
  nameout=${ffile/fff/pgm}


  Time=$(echo "$Flir" | grep "Date/Time Original" | sed 's/Date\/Time\ Original//g' | sed 's/:/\ /' | sed 's/+01:00//')
  echo Time $Time > Time.txt

  #
  # converting .fff to png
  #
  exiftool -b -RawThermalImage results/fout/$ffile | convert - -compress none results/tout/$nameout
  
  cat Time.txt > tmp
  cat results/tout/$nameout >> tmp
  mv tmp results/tout/$nameout

  echo converting results/ffout/$ffile to results/tout/$nameout
  j=$((j+1))

  rm -f Time.txt
done
 
