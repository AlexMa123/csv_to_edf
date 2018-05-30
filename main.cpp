/****************************************************************
 *  this file is used to change csv file getted from moniter
 *  to edf+
 *
 ****************************************************************/
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "edflib.h"

using std::string;
using std::ifstream;
int read_file(string filename, string output_file){

    int day, month, year, second, min, hour;

    int hdl = edfopen_file_writeonly(output_file.c_str(), EDFLIB_FILETYPE_EDFPLUS, 1);

    if(hdl < 0){
        printf("error: edfopen_file_writeonly()\n");
        return (1);
    }

    if(edf_set_samplefrequency(hdl, 0, 500)){
        printf("error: edf_set_samplefrequency()\n");
        return 1;
    }// 500 is freq

    if(edf_set_physical_maximum(hdl, 0, 10000.0)){
        printf("error: edf_set_physical_maximum()\n");
        return 1;
    }

    if(edf_set_physical_minimum(hdl, 0, 7000.0)){
        printf("error: edf_set_physical_minimum()\n");
        return 1;
    }
    if(edf_set_digital_maximum(hdl, 0, 32767))
    {
        printf("error: edf_set_digital_maximum()\n");

        return(1);
    }
    if(edf_set_digital_minimum(hdl, 0, -32767))
    {
        printf("error: edf_set_digital_minimum()\n");

        return(1);
    }


    if(edf_set_label(hdl, 0, "ECG")){
        printf("error: edf_set_label()\n");
        return 1;
    }

    if(edf_set_physical_dimension(hdl, 0, "mV")){
        printf("error: edf_set_physical_dimension()\n");
        return 1;
    }

    ifstream f(filename);
    double *buf = new double[500];
    string line;
    getline(f, line);
    day    = atoi(&line[3]);
    month  = atoi(&line[6]);
    year   = atoi(&line[9]);
    hour   = atoi(&line[14]);
    min    = atoi(&line[17]);
    second = atoi(&line[20]);

    if(edf_set_startdatetime(hdl, year, month, day, hour, min, second)){
        printf("error: edf_set_startdatetime()\n");
        delete[] buf;
        return (1);
    }
    f.seekg(0, std::ios::beg);
    int i = 0;
    while(getline(f, line)){
        int pos = line.find(",");
        double value = atof(&line[pos+1]);
        buf[i++] = value;
        if(i == 500){

            if(edfwrite_physical_samples(hdl, buf))
            {
                printf("error: edfwrite_physical_samples()\n");
                delete[] buf;
                return(1);
            }

            i = 0;
        }
    }
    delete[] buf;
    edfclose_file(hdl);
    return 0;
}


int main(int argc, char *argv[])
{
    string input_file = "NOM_ECG_ELEC_POTL_IIWaveExport.csv";
    string output_file = "NOM_ECG_ELEC_POTL_IIWaveExport.edf";
    if(argc == 2){
        string filename1 = argv[1];
        if(filename1[filename1.find(".")+1] == 'c')
            input_file = filename1;
        else if(filename1[filename1.find(".")+1] == 'e')
            output_file = filename1;
        else{
            printf("it should be a csv file or edf file!!!\n");
            return 1;
        }
    }
    if(argc == 3){
        input_file = argv[1];
        output_file = argv[2];
    }

    int val = read_file(input_file, output_file);
    return val;
}
