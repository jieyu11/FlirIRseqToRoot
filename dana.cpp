#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
#include "DateTime.h"
#include "IRcamera.h"

using namespace std;
int main(int argc, char* argv[])
{

  /* 
   * initial values for parameters
   * see page 16 of below for details:
   * https://graftek.biz/system/files/137/original/FLIR_AX5_GenICam_ICD_Guide_052013.pdf?1376925336
   */
  double m_R1 = -1.;
  double m_R2 = -1.; 
  double m_B = -1.; 
  double m_O = -1.;
  double m_F =  -1.;
  double m_Emissivity = -1.;
  double m_ReflTemp = -1.; 
  double m_AtomTemp = 22.;
  double m_Transmissivity = 1.000;
 

  ifstream infile("config");
  while (infile)
  {
    if (infile.eof()) break;
    string name_para; double val_para;
    infile >> name_para >> val_para;
    if (name_para=="R1") m_R1 = val_para;
    else if (name_para=="R2") m_R2 = val_para;
    else if (name_para=="B") m_B = val_para;
    else if (name_para=="O") m_O = val_para;
    else if (name_para=="F") m_F = val_para;
    else if (name_para=="Emissivity") m_Emissivity = val_para;
    else if (name_para=="ReflTemp") m_ReflTemp = val_para;
  }

  if( fabs(m_R1+1) < 0.0001 || fabs(m_R2+1) < 0.0001 || fabs(m_B+1) < 0.0001 || 
      fabs(m_O+1) < 0.0001 || fabs(m_F+1) < 0.0001 || fabs(m_Emissivity+1) < 0.0001){
    cout << " check the parameters in config. "<<endl;
    return 2;
  }

  bool getTatmFromFile = false;
  string s_input = "";
  string s_output = "";
  string s_TatmIn = "", s_TatmVar = "T3";
  for (int it=1; it<argc; it++){
    if     (string(argv[it]) == "-E"){ m_Emissivity = atof(argv[it+1]); it++; }
    else if(string(argv[it]) == "-Tau"){ m_Transmissivity = atof(argv[it+1]); it++; }
    else if(string(argv[it]) == "-Tatm"){ m_AtomTemp = atof(argv[it+1]); it++; }
    else if(string(argv[it]) == "-TatmFromFile"){ s_TatmIn = string(argv[it+1]); getTatmFromFile = true; it++; }
    else if(string(argv[it]) == "-TatmVariable"){ s_TatmVar = string(argv[it+1]); it++; }
    else if(string(argv[it]) == "-Tref"){ m_ReflTemp = atof(argv[it+1]); it++; }
    else if(string(argv[it]) == "-In"){ s_input = string(argv[it+1]); it++; }
    else if(string(argv[it]) == "-Out"){ s_output = string(argv[it+1]); it++; }
    else {cout<<"Format: ./dana (-E 0.97) (-Tau 0.995) (-Tatm 20.0) (-Tref 20.0) -In input_file -Out out.root"<<endl; return 2;}
  }
  if (s_input == "" || s_output == "") return 3;
  if (s_TatmIn == "" && getTatmFromFile) return 4;

  DateTime * pDT = NULL;
  if(getTatmFromFile){
    pDT = new DateTime();
    cout<<"Reading ambient T from "<<s_TatmIn<<" using variable: "<<s_TatmVar<<endl;
    pDT -> readDateTime(s_TatmIn, s_TatmVar);
  }

  IRcamera * pIR = new IRcamera();
  pIR -> setR1( m_R1 );
  pIR -> setR2( m_R2 );
  pIR -> setB( m_B );
  pIR -> setO( m_O );
  pIR -> setF( m_F );
  pIR -> setEmissivity( m_Emissivity );
  pIR -> setReflTemp( m_ReflTemp );
  pIR -> setAtomTemp( m_AtomTemp );
  pIR -> setTransmissivity( m_Transmissivity );
 
  pIR -> storeToTree(s_input, s_output, pDT);
  return 0;
}
