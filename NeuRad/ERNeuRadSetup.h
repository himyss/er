// -------------------------------------------------------------------------

// -----                        ERNeuRadSetup header file              -----

// -----                        V.Schetinin (sch_vitaliy@mail.ru)      -----

// -------------------------------------------------------------------------

#ifndef ERNEURADSETUP_H
#define ERNEURADSETUP_H

#include <vector>
#include "Rtypes.h"
#include "ERNeuRadDigiPar.h"

struct ERNeuRadBundle{
        Float_t fX;
        Float_t fY;
        ERNeuRadBundle(Float_t x, Float_t y){fX = x; fY = y;}
};

struct ERNeuRadFiber{
        Float_t fX;
        Float_t fY;
        ERNeuRadFiber(Float_t x, Float_t y){fX = x; fY = y;}
};

class ERNeuRadSetup {
    static ERNeuRadSetup* fInstance;
    static ERNeuRadDigiPar* fDigiPar;
    static std::vector<ERNeuRadBundle*> fBundles;
    static std::vector<std::vector<ERNeuRadFiber*> > fFibers;
    ERNeuRadSetup();
public:
    static ERNeuRadSetup* Instance();
    static Int_t   NofFibers();
    static Int_t   NofBundles();
    static Float_t FiberLength();
    static Float_t FiberWidth();
    static Float_t BundleX(Int_t iBundle);
    static Float_t BundleY(Int_t iBundle);
    static Float_t FiberX(Int_t iBundle, Int_t iFiber);
    static Float_t FiberY(Int_t iBundle, Int_t iFiber);
    static Float_t PMTQuantumEfficiency(Int_t iBundle, Int_t iFiber);
    static Float_t PMTGain(Int_t iBundle, Int_t iFiber);
    static Float_t Z(){return 2600;}
    static void    Print();
    ClassDef(ERNeuRadSetup,1)

};

#endif

