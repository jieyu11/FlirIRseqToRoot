#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "TTree.h"
#include "TFile.h"
#include "IRcamera.h"
using namespace std;

double IRcamera::raw_to_temperature(double val_raw){

  if (para_Emissivity <0){cout<<"check the parameters"<<endl; return 0.;}

  double RawAtom = para_R1 / (para_R2 * ( exp( para_B / (para_AtomTemp + 273.15) ) - para_F ) ) - para_O;
  double RawRefl = para_R1 / (para_R2 * ( exp( para_B / (para_ReflTemp + 273.15) ) - para_F ) ) - para_O;
  double RawObj  = ( val_raw - para_Transmissivity * (1 - para_Emissivity) * RawRefl - (1 - para_Transmissivity) * RawAtom ) / ( para_Emissivity * para_Transmissivity);
  double TinC = para_B / log ( para_R1 / ( para_R2*( RawObj + para_O) ) + para_F) - 273.15;

  return TinC;

}
bool IRcamera::storeToTree(string s_input, string s_output, const DateTime * pDT){

  TFile * f0 = new TFile(s_output.c_str(), "recreate");
  TTree * t0 = new TTree("atree", "a tree of temperature data");
  TTree * t1 = new TTree("btree", "a tree of camera information");
  int year, month, date, hour, minute;
  float second;
  int index;
  int xpos, ypos;
  float temperature;
  float Tambient;
  t0->Branch("xpos", &xpos, "xpos/I");
  t0->Branch("ypos", &ypos, "ypos/I");
  t0->Branch("temperature", &temperature, "temperature/F");

  t1->Branch("Tambient", &Tambient, "Tambient/F");
  t1->Branch("index", &index, "index/I");
  t1->Branch("year", &year, "year/I");
  t1->Branch("month", &month, "month/I");
  t1->Branch("date", &date, "date/I");
  t1->Branch("hour", &hour, "hour/I");
  t1->Branch("minute", &minute, "minute/I");
  t1->Branch("second", &second, "second/F");
  index = 0;
  size_t xk0 = s_input.find("_n");
  size_t xk1 = s_input.find(".");
  if (xk0!=string::npos && xk1!=string::npos && xk0+2<xk1){
    index = (int) atof(s_input.substr(xk0+2, xk1-xk0-2).c_str() );
    //DEBUG:
    //cout<<"time label : "<<index<<endl;
  }

  int iline = 0, counter =0;
  ifstream infile(s_input.c_str());
  string line;
  while (std::getline(infile, line))
  {
    iline++;
    if (line.size() <=0) continue;

    if (iline == 1){
      if (line.substr(0,4) != "Time"){ cout<<"file should start with Time : "<<endl;return false;}

      //line = "Time 2015:11:03 18:08:27.799"
      //cout<<"--------------------------------line: "<<line<<endl;
      //
      
      line = line.substr(5);

      //line = "2015:11:03 18:08:27.799"
      size_t k=line.find(":");
      year = (int) atof(line.substr(0,k).c_str() );
      month = (int) atof(line.substr(k+1,2).c_str() );
      date = (int) atof(line.substr(k+4,2).c_str() );

      k=line.find(" ");
      line = line.substr(k+1);
      //line = "18:08:27.799"
      k=line.find(":");
      hour = (int) atof(line.substr(0,k).c_str() );
      minute = (int) atof(line.substr(k+1,2).c_str() );
      second = atof(line.substr(k+4).c_str() );

      //DEBUG:
      //cout<<"Time "<<year<<":"<<month<<":"<<date<<" "<<hour<<":"<<minute<<":"<<second<<endl;

      if(pDT){
        dataDateTime adt = dataDateTime(year, month, date, hour, minute, int(second));
        float Tfound = pDT -> getTemperature(adt);
        if(Tfound > -998.)
        {
          para_AtomTemp = Tfound;
          cout<<"reverting the T ambient to: "<<para_AtomTemp<<endl;
        }else{
          cout<<year <<" "<< month <<" "<< date << " "<< hour << " " <<minute << " "<< int(second)<<endl;
          cout<<" date NOT found !!!!"<<endl;
        }
      }
      Tambient = para_AtomTemp;
      t1 -> Fill();
    }

    // ------------------
    // skip first 4 lines
    // ------------------
    if (iline <=4) continue;

    double val_raw;
    string ssub[1000] = {""};
    size_t k=line.find(" ");
    int js = 0;
    while (k!=string::npos){
      ssub[js] = line.substr(0,k);
      line = line.substr(k+1);
      k=line.find(" ");

      xpos = counter % NXPixels; // 640;
      ypos = counter / NXPixels; // 640;
      val_raw = atof(ssub[js].c_str());
      temperature = raw_to_temperature(val_raw);

      t0->Fill();

      js++;
      counter++;
    }
  }

  //DEBUG:
  //cout<<"total "<<counter<<", last x "<<xpos<<" y "<<ypos<<endl;
  t0->Write();
  t1->Write();
  delete t0;
  delete t1;
  delete f0;
  return true;
}

