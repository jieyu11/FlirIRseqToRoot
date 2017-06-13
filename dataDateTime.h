#ifndef DATADATETIME_H
#define DATADATETIME_H
#include <unordered_map>
#include <iostream>
#include <stdlib.h>

class dataDateTime{

  private:

  public:
    int m_year;
    int m_month;
    int m_date;
    int m_hour;
    int m_minute;
    int m_second;

  public:
    dataDateTime(){}
    ~dataDateTime(){}
    dataDateTime(int year, int month, int date, int hour, int minute, int second) : 
      m_year(year),  m_month(month),  m_date(date),  m_hour(hour),  m_minute(minute),  m_second(second){}

    bool operator==(const dataDateTime &adt) const {  
      if((adt.m_year == m_year ) &&
          (adt.m_month == m_month ) &&
          (adt.m_date == m_date ) &&
          (adt.m_hour == m_hour ) &&
          (adt.m_minute == m_minute ) &&
          (adt.m_second == m_second ) ) return true;
      else return false;
    }
};
#endif
