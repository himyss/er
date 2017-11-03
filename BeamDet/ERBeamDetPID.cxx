#include "ERBeamDetPID.h"

#include <vector>
#include <iostream>
using namespace std;

#include "TVector3.h"
#include "TMath.h"

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include <iostream>

#include "ERDetectorList.h"
#include "ERBeamDetSetup.h"

// ----------------------------------------------------------------------------
ERBeamDetPID::ERBeamDetPID()
  : FairTask("ER BeamDet particle finding scheme")
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
ERBeamDetPID::ERBeamDetPID(Int_t verbose)
  : FairTask("ER BeamDet particle finding scheme ", verbose)
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
ERBeamDetPID::~ERBeamDetPID()
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void ERBeamDetPID::SetParContainers()
{

}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
InitStatus ERBeamDetPID::Init()
{
  // Get input array
  FairRootManager* ioman = FairRootManager::Instance();
  if ( ! ioman ) Fatal("Init", "No FairRootManager");
  
  fBeamDetToFDigi1 = (TClonesArray*) ioman->GetObject("BeamDetToFDigi1");
  fBeamDetToFDigi2 = (TClonesArray*) ioman->GetObject("BeamDetToFDigi2");
  fBeamDetTrack  = (ERBeamDetTrack*) ioman->GetObject("BeamDetTrack.");

  // Register output object fProjectile
  fProjectile = (ERBeamDetParticle*)new ERBeamDetParticle();

  ioman->Register("BeamDetParticle.", "BeamDet Particle", fProjectile, kTRUE);

  fBeamDetSetup = ERBeamDetSetup::Instance();
  fBeamDetSetup->SetParContainers();
  fBeamDetSetup->GetGeoParamsFromParContainer();
     
  return kSUCCESS;
}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void ERBeamDetPID::Exec(Option_t* opt)
{ 
  Reset();
  if (!fBeamDetTrack || !fBeamDetToFDigi1->At(0) || !fBeamDetToFDigi2->At(0))
  {
    cout  << "ERBeamDetPID: No track" << endl;
    return;
  }

  Double_t ToF1, ToF2, ToF;
  Double_t dE1, dE2, dE;
  Double_t probability;

  Double_t beta;
  Double_t gamma;
  /*TParticlePDG* particle = TDatabasePDG::Instance()->GetParticle(fPID);
  if ( ! particle ) {
      cout << "ERIonGenerator: Ion " << fPID
      << " not found in database!" << endl;
      return ;
    }*/
  //Double_t mass = 26.2716160;//particle->Mass();
  Double_t p, energy;

  ERBeamDetToFDigi* digi;

  digi = (ERBeamDetToFDigi*)fBeamDetToFDigi1->At(0);
  ToF1 = digi->GetTime();
  dE1 = digi->Edep();
  cout << "dE1 = " << dE1 << " ToF1 = " << ToF1 << endl;
  digi = (ERBeamDetToFDigi*)fBeamDetToFDigi2->At(0);
  ToF2 = digi->GetTime();
  dE2 = digi->Edep();
  cout << "dE2 = " << dE2 << " ToF2 = " << ToF2 << endl;

  dE = dE1 + dE2;
  cout << "dE = " << dE << " Gev; " << " ToF1 = " << ToF1 << " ns;" << " ToF2 = " << ToF2 << " ns;" << endl;
  ToF = ToF2 - ToF1 + fOffsetToF;
  cout << "dE = " << dE << " Gev; " << " ToF = " << ToF << " ns;" << endl;

  if(ToF <= fToF1 || ToF >= fToF2 || dE <= fdE1 || dE >= fdE2){
    probability = 0;
  }
  else {
    probability = 1;
  }

  if(probability < fProbabilityThreshold) {
    std::cout << "Probability " << probability << " less then threshold " << fProbabilityThreshold << std::endl;
    FairRun* run = FairRun::Instance();
    run->MarkFill(kFALSE);
    return ;
  }

  beta = fBeamDetSetup->DistanceBetweenToF() * 1e-2 / (ToF * 1e-9) / TMath::C();
  if(beta <= 0 || beta >= 1) {
    std::cout << "Wrong beta " << beta << std::endl;
    FairRun* run = FairRun::Instance();
    run->MarkFill(kFALSE);
    return ;
  }

  gamma = 1. / TMath::Sqrt(1.- beta*beta);
  p = beta * gamma * fIonMass;

  Double_t px, py, pz;

  px = p * TMath::Sin(fBeamDetTrack->GetVector().Theta()) * TMath::Cos(fBeamDetTrack->GetVector().Phi());
  py = p * TMath::Sin(fBeamDetTrack->GetVector().Theta()) * TMath::Sin(fBeamDetTrack->GetVector().Phi());
  pz = p * TMath::Cos(fBeamDetTrack->GetVector().Theta());

  energy = fIonMass * gamma;
  std::cout << "PID: " << fPID << "; px: " << px << "; py: " << py << "; pz: " << pz 
            << " energy: " << energy << "; probability " << probability << std::endl;

  AddParticle(fPID, TLorentzVector(px, py, pz, energy), probability);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void ERBeamDetPID::Reset()
{
  if (fProjectile) {
    fProjectile->Clear();
  }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void ERBeamDetPID::Finish()
{   
  
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
ERBeamDetParticle* ERBeamDetPID::AddParticle(Int_t pid, TLorentzVector fourMomentum, Double_t probability)
{
 fProjectile->AddParameters(pid, fourMomentum, probability); 
}
//-----------------------------------------------------------------------------
ClassImp(ERBeamDetPID)