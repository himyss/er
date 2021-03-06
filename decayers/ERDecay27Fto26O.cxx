#include "ERDecay27Fto26O.h"

#include "TVirtualMC.h"
#include "TLorentzVector.h"
#include "TMCProcess.h"

#include "FairRunSim.h"
#include<iostream>

using namespace std;

//#include "ERTarget.h"
#include "ERMCEventHeader.h"      //for ERMCEventHeader

ERDecay27Fto26O::ERDecay27Fto26O():
  fTargetReactionFinish(kFALSE),
  fTargetReactZ(0.),
  fSecondaryIonPDG(-1)
{
  fRnd = new TRandom3();
  FairRunSim* run = FairRunSim::Instance();
  FairIon* SecondIon = new FairIon("ExpertSecondIon",8,26, 8); //26O
  run->AddNewIon(SecondIon);
}

ERDecay27Fto26O::~ERDecay27Fto26O(){

}

Bool_t ERDecay27Fto26O::Stepping(){
  //Определяемся с текущим положением.
  if (gMC->TrackPid() == 1000090270 && !fTargetReactionFinish && TString(gMC->CurrentVolName()).Contains("target")){
    gMC->SetMaxStep(0.01);
	TLorentzVector curPos;
	gMC->TrackPosition(curPos);
	if (curPos.Z() > fTargetReactZ){
		std::cout << "Start reation in target. Defined pos: " << fTargetReactZ << ", current pos: " << curPos.Z() << endl;
		FairRunSim* run = FairRunSim::Instance();
		//Create new ion
	    fSecondIon = TDatabasePDG::Instance()->GetParticle("ExpertSecondIon");
	    if ( ! fSecondIon ) {
	        std::cerr  << "-W- ERDecay27Fto26O: Ion ExpertSecondIon not found in database!" << endl;
	        return kFALSE;
	    }
		TLorentzVector curMomentum;
		gMC->TrackMomentum(curMomentum);
  
	  	//Импульс первого иона в момент распада
	  	Double_t momentum =  TMath::Sqrt(curMomentum.X()*curMomentum.X() + curMomentum.Y()*curMomentum.Y() + curMomentum.Z()*curMomentum.Z());
	  	//Импульс второго иона
	  	momentum *= fSecondIon->Mass()/gMC->TrackMass();

		Double_t fullEnergy = TMath::Sqrt(fSecondIon->Mass()*fSecondIon->Mass() + momentum*momentum);
		//Расчет гамма фактора
		Double_t betaCM = (fullEnergy-fSecondIon->Mass())/fullEnergy;
		Double_t gammaCM = TMath::Sqrt( 1. / ( 1. - betaCM*betaCM) );

		TParticlePDG* thisPart =
				TDatabasePDG::Instance()->GetParticle(fSecondIon->GetName());
	  
  		fSecondaryIonPDG = fSecondIon->PdgCode();

	  	std::cout << "-I- ERDecay27Fto26O: Generating ion of type "
	       << fSecondIon->GetName() << " (PDG code " << fSecondaryIonPDG << ")" << endl;
	  	std::cout << "    Momentum (" << curMomentum.X() << ", " <<  curMomentum.Y() << ", " <<  curMomentum.Z()
	       << ") Gev from vertex (" << curPos.X() << ", " << curPos.Y()
	       << ", " << curPos.Z() << ") cm" << endl;
    
		Int_t newTrackNb;
  
		gMC->GetStack()->PushTrack(1, 0, fSecondaryIonPDG,
                   curMomentum.X(),curMomentum.Y(), curMomentum.Z(),
                   fullEnergy, curPos.X(), curPos.Y(), curPos.Z(),
                   gMC->TrackTime(), 0., 0., 0.,
                   kPDecay, newTrackNb, fSecondIon->Mass(), 0);
	  	//Stop first ion
	  	gMC->StopTrack();
	  	fTargetReactionFinish = kTRUE;
	}
  }
  return kTRUE;
}

void ERDecay27Fto26O::BeginEvent(){
  fTargetReactionFinish = kFALSE;
  //Double_t targetThickness = ERTarget::Thickness();
  fTargetReactZ = fRnd->Uniform()*2.;
  FairRunSim* run = FairRunSim::Instance();
  ERMCEventHeader* header = (ERMCEventHeader*)run->GetMCEventHeader();
  header->SetTargetReactionPos(fTargetReactZ);
  fSecondaryIonPDG = -1;
}

void ERDecay27Fto26O::FinishEvent(){

}

ClassImp(ERDecay27Fto26O)
