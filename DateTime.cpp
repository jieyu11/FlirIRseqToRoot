#define DATATIME_CPP
#include "TFile.h"
#include "TTree.h"
#include "DateTime.h"

using std::string;
using std::cout;
using std::endl;
bool DateTime::readDateTime(string sfilename, string svar){
  TFile *fdt = new TFile(sfilename.c_str(), "read");
  if(!fdt) return false;
  int year;
  int month;
  int date;
  int hour;
  int minute;
  int second;
  float Tambt;
  TTree * t0 = (TTree *) fdt ->Get("atree");
  if(!t0) return false;

  t0->SetBranchAddress("year", &year);
  t0->SetBranchAddress("month", &month);
  t0->SetBranchAddress("date", &date);
  t0->SetBranchAddress("hour", &hour);
  t0->SetBranchAddress("minute", &minute);
  t0->SetBranchAddress("second", &second);
  t0->SetBranchAddress(svar.c_str(), &Tambt);
  int nentry = t0 -> GetEntries();
  for(int ie = 0; ie<nentry; ie++){
    t0->GetEntry(ie);
    datetimeMap.insert( std::make_pair(dataDateTime(year, month, date, hour, minute, second), Tambt) );

    // print output
    if(ie ==0) cout<<"date, time range [ "<<endl;
    if(ie ==0 || ie==nentry-1){
      cout<<year <<" "<< month <<" "<< date << " "<< hour << " " <<minute << " "<< int(second)<<endl;
    }
    if(ie ==0) cout<<","<<endl;
    if(ie ==nentry-1) cout<<"]"<<endl;
  }
  return true;
}
