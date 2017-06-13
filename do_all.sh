#/bin/bash


indir=data/FOLD_INPUT_Seq_DIR
outdir=${indir}_root
mkdir -p $outdir

# Thermal Couple data containing T ambient
# T1 -- T4: tell which is for T ambient
TambientData=TC.root 
TambientVar=T3
while read file; do 

  if [[ "${file}" == "" ]]; then continue; fi
  if [[ ${file:0:1} == "#" ]]; then continue; fi

  fname=${file:11}

  echo 'running '${fname}''
  ./run.sh $indir/${file}.seq $TambientData $TambientVar


  rm -rf $outdir/${fname}
  mv results/roo $outdir/${fname}
  ls -ld $outdir/${fname}

done < list_seq.txt
