#ifndef IRCAMERA_H
#define IRCAMERA_H

#include <string>
#include "DateTime.h"

#define NXPixels 640
class IRcamera{
  public: 
    IRcamera(){
      para_R1 = -1.;
      para_R2 = -1.; 
      para_B = -1.; 
      para_O = -1.;
      para_F =  -1.;
      para_Emissivity = -1.;
      para_ReflTemp = -1.; 
      para_AtomTemp = 22.;
      para_Transmissivity = 1.000;
    }
    ~IRcamera(){}
    double raw_to_temperature(double val_raw);
    bool storeToTree(std::string s_input, std::string s_output = "out.root", const DateTime * pDT = NULL);


    double getR1(){ return para_R1;}
    double getR2(){ return para_R2;}
    double getB(){ return para_B;}
    double getO(){ return para_O;}
    double getF(){ return para_F;}
    double getEmissivity(){ return para_Emissivity;}
    double getReflTemp(){ return para_ReflTemp;}
    double getAtomTemp(){ return para_AtomTemp;}
    double getTransmissivity(){ return para_Transmissivity;}

    void setR1(double m_R1){ para_R1 = m_R1;}
    void setR2(double m_R2){ para_R2 = m_R2;}
    void setB(double m_B){ para_B = m_B;}
    void setO(double m_O){ para_O = m_O;}
    void setF(double m_F){ para_F = m_F;}
    void setEmissivity(double m_Emissivity){ para_Emissivity = m_Emissivity;}
    void setReflTemp(double m_ReflTemp){ para_ReflTemp = m_ReflTemp;}
    void setAtomTemp(double m_AtomTemp){ para_AtomTemp = m_AtomTemp;}
    void setTransmissivity(double m_Transmissivity){ para_Transmissivity = m_Transmissivity;}
  private:

    // see page 16 of:
    //https://graftek.biz/system/files/137/original/FLIR_AX5_GenICam_ICD_Guide_052013.pdf?1376925336
    double para_R1;
    double para_R2;
    double para_B;
    double para_O;
    double para_F;
    double para_Emissivity;
    double para_ReflTemp;
    double para_AtomTemp;
    double para_Transmissivity;
};


#endif

