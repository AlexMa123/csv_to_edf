# csv_to_edf
change csv file that get from VSCaptureMPWaveMIB program to edf file

## How to use:


### 1. make
```bash
mkdir bin
mkdir obj
make
```
after make, you can find CSV_to_EDF in bin/CSV_to_EDF



### 2. use bin/CSV_to_EDF
CSV_to_EDF [input csv file] [output csv file]

>if you haven't give these two par, the program will set input_file be "./NOM_ECG_ELEC_POTL_IIWaveExport.csv" and set output_file be "./NOM_ECG_ELEC_POTL_IIWaveExport.edf" by default
