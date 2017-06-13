#ifndef DATATIME_H
#define DATATIME_H
#include <unordered_map>
#include <iostream>
#include <stdlib.h>
#include "dataDateTime.h"
#include "hasherDateTime.h"
#include <string>

class DateTime{
  public:
    DateTime(){}
    ~DateTime(){
      if(!datetimeMap.empty()) datetimeMap.clear();
    }

    /*
     * read date and time from file
     */
    bool readDateTime(std::string sfilename, std::string svar);

    /*
     * check the existence of date time
     */
   bool checkDT(const dataDateTime & dt) const
   {
    if( datetimeMap.find(dt) == datetimeMap.end()) return false;
    else return true;
   }

   /*
    * get temperature through date time
    */
   float getTemperature(const dataDateTime & dt) const
   {
    if( datetimeMap.find(dt) == datetimeMap.end()) return -999.;
    else return datetimeMap.at(dt); // No viable overloaded operator[] for type
   }

  private:

    std::unordered_map<dataDateTime, float, hasherDateTime> datetimeMap;
};

#endif
