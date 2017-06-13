# to run, please first install ExifTool and ImageMagick in Section 1.
# Rec_test.seq is an example output from Flir IR camera.
./run.sh Rec_test.seq

# it will produce the root files in Results/roo
# it consists three steps:
# 1) ./seqtobinary.pl Rec_test.seq: convert Rec_test.seq into binary files (figure) frame by frame
# 2) source binarytorawtext.sh:     convert binary files (per frame) into text files (raw value)
# 3) source texttoroot.sh:          convert text files into root format, meanwhile calculate temperature from raw data values
#
###############################################################
#Section 1. ExifTool installation and basic information
#
#  ExifTool to download:
#  http://www.sno.phy.queensu.ca/~phil/exiftool/
#  
#  In a few cases later, the command ‘convert’ is needed and one needs to install ImageMagick in two steps:
#  1. install MacPorts here: https://www.macports.org/install.php
#  2. install ImageMagick here: http://cactuslab.com/imagemagick/
#  
#  Exiftool forum: http://u88.n24.queensu.ca/exiftool/forum/index.php#c1
#
#  After this step, one can run the code to produce .root files.
#  Following sections provide more details on how it is done.
#
###############################################################
#Section 2. ExifTool basic commands
#
#  To get the meta-data information directly from raw data produced by FLIR software (*.seq), one can use ExifTool in command lines, for example:
#  $: exiftool -Emissivity Rec_test.seq
#  
#  which produces:
#  $: Emissivity                      : 0.95
#  
#  
#  To get more information:
#  $: exiftool -FLIR:all Rec_test.seq
#  
#  which produces something like:
#  --------------------------------------------------
#  Creator Software                : ExaminIR
#  Emissivity                      : 0.95
#  Object Distance                 : 1.00 m
#  ……
#  ……
#  Raw Thermal Image               : (Binary data 614604 bytes, use -b option to extract)
#  Peak Spectral Sensitivity       : 10.1 um
#  --------------------------------------------------
#  
#  
#  For more information on tags usable for FLIR output (*.seq or image files like *.png), one can find them here:
#  http://www.sno.phy.queensu.ca/~phil/exiftool/TagNames/FLIR.html
#  
#  
#  The most interesting tag for us may be the one outputs the binary file for a image from .seq: -RawThermalImage with the help of -b, for example:
#  $: exiftool -RawThermalImage -b  Rec_test.seq > a_example.dat
#  
#  Here, it extracts the first image in Rec_test.seq into a_example.dat.
#  
#  
###############################################################
#Section 3: Convert Raw Binary Data to Text Files
#  With exiftool, one can convert image in *.seq to *.pgm file, which contains the A/D counts (raw values), using:
#  
#  $: exiftool -b -RawThermalImage Rec_test.seq | convert - -compress none raw.pgm
#  
#  
#  Now, we can read raw.pgm with any text reader (e.g. vim). However, the numbers there are raw values that each camera sensor “sees” and records. 
#  They need some function (Planck’s Law) to convert them to temperature that we are interested in. 
#  We can find the formula to convert raw value to Temperature on page 16,
#  in: https://graftek.biz/system/files/137/original/FLIR_AX5_GenICam_ICD_Guide_052013.pdf?1376925336
#  
#  Temperature (in Kelvin) = B / log(R / (S - O) + F)
#  where, R = R1/R2;
#  
#  The parameters B, R1, R1, O and F are obtained in section 2.
#  S is the raw value.
#  
#  
#  The parameters used in the formula mentioned in the link above are either provided by FLIR data 
#  (e.g. wavelength range: 7.5 - 13 μm accepted by the camera) or by user (e.g. Emissivity value)
#  
#  In the above link, the author has created a code to convert the raw number to a temperature in C, 
#  which matches the calculation using FLIR software.
#  
#  
###############################################################
#Section 4: Splitting Images in Sequence File
#  Splitting images in *.seq files requires the information of actual image time. 
#  One can first check that the information of the time is there in the .seq using:
#  
#  
#  $: exiftool -date* Rec_test.seq
#  
#  It will show something like: 
#  Date/Time Original              : 2015:11:03 18:08:27.799+01:00
#  
#  To check the magic bits of the format above, one needs to do:
#  $: hexdump -n16 -C Rec_test.seq 
#  
#  We just have to modify the magic bits in seqtobinary.pl with the one obtained from this code.
#  For our Flir camera it is:
#  $pat="\x46\x46\x46\x00\x52\x65\x73\x65\x61\x72\x63\x68\x49\x52";
#  
#  Notice, it is specific to each camera.
#
