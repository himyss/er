#include "ERNeuRadDigiPar.h"

#include "FairParamList.h"
#include "FairDetParIo.h"
#include "FairParIo.h"
#include "FairGenericParAsciiFileIo.h"
#include "FairGenericParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include<iostream>

#include "TString.h"
#include "TMath.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

// -----   Standard constructor   ------------------------------------------
ERNeuRadDigiPar::ERNeuRadDigiPar(const char* name,
    const char* title,
    const char* context)
  : FairParGenericSet(name, title, context),
    fPMTQuantumEfficiency(new TArrayF(64)),
    fPMTGain(new TArrayF(64)),
    fFiberLength(0.),
    fNofFibers(-1),
    fNofBundles(-1)
{
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
ERNeuRadDigiPar::~ERNeuRadDigiPar()
{
  clear();

}
// -------------------------------------------------------------------------


// -----   Public method clear   -------------------------------------------
void ERNeuRadDigiPar::clear()
{
  status = kFALSE;
  resetInputVersions();
}
// -------------------------------------------------------------------------

// -----   Public method print ---------------------------------------
void ERNeuRadDigiPar::print()
{
  Int_t rowNofFibers = (Int_t)TMath::Sqrt(fNofFibers);
  
  std::cout << "*****************************************" << std::endl;
  std::cout << "          ERNeuRadDigiPar                " << std::endl;
  std::cout << "*****************************************" << std::endl;
  std::cout << "   ERNeuRadFiberLength: " <<  fFiberLength <<  std::endl;
  std::cout << "   ERNeuRadFiberWidth: " <<  fFiberWidth <<  std::endl;
  std::cout << "   ERNeuRadNofBundles: " <<  fNofBundles <<  std::endl;
  std::cout << "   ERNeuRadNofFibers: " <<  fNofFibers <<  std::endl;
  std::cout << "   ERNeuRadPMTQuantumEfficiency: " <<  std::endl;
  for (Int_t iFiber = 0; iFiber < rowNofFibers; iFiber++){
    std::cout << "     ";
    for (Int_t jFiber = 0; jFiber < rowNofFibers; jFiber++)
      std::cout <<(*fPMTQuantumEfficiency)[iFiber*rowNofFibers + jFiber] << "\t";
     std::cout << std::endl;
  }
  std::cout << "*****************************************" << std::endl;
  
  std::cout << "   ERNeuRadPMTGain: " <<  std::endl;
  for (Int_t iFiber = 0; iFiber < rowNofFibers; iFiber++){
    std::cout << "     ";
    for (Int_t jFiber = 0; jFiber < rowNofFibers; jFiber++)
      std::cout <<(*fPMTGain)[iFiber*rowNofFibers + jFiber] << "\t";
     std::cout << std::endl;
  }
  std::cout << "*****************************************" << std::endl;
  
}
//------------------------------------------------------
void ERNeuRadDigiPar::putParams(FairParamList* l)
{ 

  //   print();
  cout << " I am in ERNeuRadDigiPar::putParams " << endl;
  /*if (!l) { return; }
  l->add("FairTutorialDet2DigiStations", ftutdetdigiparstation);
  l->add("FairTutorialDet2DigiSectorsPerStation", ftutdetdigiparsector);
  Int_t count_sectors = 0;
  for ( Int_t i=0; i< ftutdetdigiparstation; i++) {
    count_sectors+=ftutdetdigiparsector[i];
  }
  Int_t array_size = (count_sectors * 10 + ftutdetdigiparstation * 3);
  cout << "Array Size: " << array_size << endl;
  /*   Float_t zwischen[array_size];
     for ( Int_t i=0; i< array_size; i++) {
       zwischen[i] = ftutdetdigipar.GetAt(i);
     }
   */
   /*
  ftutdetdigipar->Set(array_size);
  l->add("FairTutorialDet2DigiPar",*ftutdetdigipar);
  */
}

//------------------------------------------------------

Bool_t ERNeuRadDigiPar::getParams(FairParamList* l)
{
  if (!l) { return kFALSE; }
  
  if ( ! l->fill("ERNeuRadFiberLength", &fFiberLength) ) { return kFALSE; }
  
  if ( ! l->fill("ERNeuRadFiberWidth", &fFiberWidth) ) { return kFALSE; }

  if ( ! l->fill("ERNeuRadNofBundles", &fNofBundles) ) { return kFALSE; }
  
  if ( ! l->fill("ERNeuRadNofFibers", &fNofFibers) ) { return kFALSE; }
  
  fPMTQuantumEfficiency->Set(fNofFibers);
  fPMTGain->Set(fNofFibers);
  if ( ! l->fill("ERNeuRadPMTQuantumEfficiency", fPMTQuantumEfficiency) ) { return kFALSE; }
  if ( ! l->fill("ERNeuRadPMTGain", fPMTGain) ) { return kFALSE; }
  
  return kTRUE;
}
//------------------------------------------------------
Bool_t ERNeuRadDigiPar::init(FairParIo* input){
	std::cout << input->getFilename() << std::endl;
  if ( TString(input->getFilename()).Contains(".digi")){
    FairGenericParAsciiFileIo* p=new FairGenericParAsciiFileIo(((FairParAsciiFileIo*)input)->getFile());
	return p->init(this);
  }
  if ( TString(input->getFilename()).Contains(".root")){ 
    FairGenericParRootFileIo* p=new FairGenericParRootFileIo(((FairParRootFileIo*)input)->getParRootFile());
	return p->init(this);
  }
  return kFALSE;
}
//------------------------------------------------------

ClassImp(ERNeuRadDigiPar)
