#include <fstream>
#include "TCanvas.h"

using namespace std;

void drawh5(){
		
	ERMCTrack *n1 = new ERMCTrack();
	ERMCTrack *n2 = new ERMCTrack();
	ERMCTrack *h3 = new ERMCTrack();
	ERMCTrack *h5 = new ERMCTrack();
	ERMCTrack *he3 = new ERMCTrack();
	ERMCTrack *he6 = new ERMCTrack();
	ERMCTrack *h2 = new ERMCTrack();

	TFile *fr = new TFile("kin.root", "READ");
	TTree *tr = (TTree*)fr->Get("tree");

	tr->SetBranchAddress("n1.",&n1);
	tr->SetBranchAddress("n2.",&n2);
	tr->SetBranchAddress("h3.",&h3);
	tr->SetBranchAddress("h5.",&h5);
	tr->SetBranchAddress("he3.",&he3);
	tr->SetBranchAddress("he6.",&he6);
	tr->SetBranchAddress("h2.",&h2);

	// TH1F *n1E = new TH1F("n1E","n1 kinenergy",1000,0,100);
	// TH1F *n2E = new TH1F("n2E","n2 kinenergy",1000,0,100);
	// TH1F *h3E = new TH1F("h3E","h3 kinenergy",1000,0,100);
	// TH1F *h5E = new TH1F("h5E","h5 kinenergy",1000,0,100);
	// TH1F *he3E = new TH1F("he3E","he3 kinenergy",1000,0,100);
	// TH1F *he6E = new TH1F("he6E","he6 kinenergy",1000,0,100);
	// TH1F *h2E = new TH1F("h2E","h2 kinenergy",1000,0,100);

	// TH1F *n1Thet = new TH1F("n1Thet","n1 theta lab",1000,0,100);
	// TH1F *n2Thet = new TH1F("n2Thet","n2 theta lab",1000,0,100);
	// TH1F *h3Thet = new TH1F("h3Thet","h3 theta lab",1000,0,100);
	// TH1F *h5Thet = new TH1F("h5Thet","h5 theta lab",1000,0,100);
	// TH1F *he3Thet = new TH1F("he3Thet","he3 theta lab",1000,0,100);
	// TH1F *he6Thet = new TH1F("he6Thet","he6 theta lab",1000,0,100);
	// TH1F *h2Thet = new TH1F("h2Thet","h2 theta lab",1000,0,100);

	// TH1F *n1ThetСМ = new TH1F("n1ThetСМ","n1 theta CM",1000,0,100);
	// TH1F *n2ThetСМ = new TH1F("n2ThetСМ","n2 theta CM",1000,0,100);
	// TH1F *h3ThetСМ = new TH1F("h3ThetСМ","h3 theta CM",1000,0,100);
	// TH1F *h5ThetСМ = new TH1F("h5ThetСМ","h5 theta CM",1000,0,100);
	// TH1F *he3ThetСМ = new TH1F("he3ThetСМ","he3 theta CM",1000,0,100);

	// TH1F *n1M= new TH1F("n1M","n1 mass",1000,0,100);
	// TH1F *n2M = new TH1F("n2M","n2 mass",1000,0,100);
	// TH1F *h3M = new TH1F("h3M","h3 mass",1000,0,100);
	// TH1F *h5M = new TH1F("h5M","h5 mass",1000,0,100);
	// TH1F *he3M = new TH1F("he3M","he3 mass",1000,0,100);
	// TH1F *he6M = new TH1F("he6M","he6 mass",1000,0,100);
	// TH1F *h2M = new TH1F("h2M","h2 mass",1000,0,100);

	/*TLorentzVector *fn1 = new TLorentzVector();
	TLorentzVector *fn2 = new TLorentzVector();
	TLorentzVector *fh3 = new TLorentzVector();
	TLorentzVector *fh5 = new TLorentzVector();
	TLorentzVector *fhe3 = new TLorentzVector();
	TLorentzVector *fhe6 = new TLorentzVector();
	TLorentzVector *fh2 = new TLorentzVector();

	TLorentzVector *fn1CM = new TLorentzVector();
	TLorentzVector *fn2CM = new TLorentzVector();
	TLorentzVector *fh3CM = new TLorentzVector();
	TLorentzVector *fh5CM = new TLorentzVector();
	TLorentzVector *fhe3CM = new TLorentzVector();*/
	TCut cHeLocus = "(h3->GetTheta())*TMath::RadToDeg() < 32 && (h3->GetEnergy() - h3->GetMass()) < 20";

	TLorentzVector fn1,fn2,fh3,fh5,fhe3,fhe6,fh2,fn1CM,fn2CM,fh3CM,fh5CM,fhe3CM;
	TLorentzVector temp,tempCM;
	TVector3 bVect;
//c1
	// pad
	TH1F *h5EX = new TH1F("h5EX","h5 spectrum",500,0,180);
	TH1F *he6T = new TH1F("he6T","beam energy",500,0,400);
	TH1F *he6Theta = new TH1F("he6Theta","beam direction: theta",500,0,180);
	TH1F *he6Phi = new TH1F("he6Phi","beam direction: phi",500,0,180);

	TH2F *he3Theta2 = new TH2F("he3Theta2","he3 theta vs CM",500,0,180,500,0,40); //cd2 
	TH2F *h5Theta2 = new TH2F("h5Theta2","h5 theta vs CM",500,0,180,500,0,40);

	TH2F *he3t_thetCM = new TH2F("he3t_thetCM","he3 t vs thetaCM",500,0,180,500,0,100); // cd3
	TH2F *h5t_thetCM = new TH2F("h5t_thetCM","h5 t vs thetaCM",500,0,180,500,0,100);

	TH1F *he3ThetaCM = new TH1F("he3ThetaCM","he3 theta CM",70,0,180); // cd4

	TH2F *he3_h5_theta = new TH2F("he3_h5_theta","h5 t he3",500,0,24,500,0,40); //cd5

	TH2F *he3t_thet = new TH2F("he3t_thet","he3 t vs theta",500,0,40,500,0,100);
	TH2F *h5t_thet = new TH2F("h5t_thet","h5 t vs theta",500,0,40,500,0,150);


//c2
	TH2F *he3Theta2cut = new TH2F("he3Theta2cut","he3 theta vs CM cut",500,0,180,500,0,40); //cd2 
	TH2F *h5Theta2cut = new TH2F("h5Theta2cut","h5 theta vs CM cut",500,0,180,500,0,40);


	// for(Int_t i=0; i<tr->GetEntries();i++){
	for(Int_t i=0; i<10;i++){
		tr->GetEntry(i);

		fh5 = h5->GetVector();
		fhe6 = he6->GetVector();
		fh2 = h2->GetVector();
		temp = h2->GetVector();
		bVect = fh2.BoostVector();
		temp.Boost(-bVect);
		cout << temp.E() << " "<< h2->GetMass() << endl;

		fn1CM = n1->GetVector();
		fn2CM = n2->GetVector();
		fh3CM = h3->GetVector();
		fh5CM = h5->GetVector();
		fhe3CM = he3->GetVector();

		fn1CM.Boost(-fh5.BoostVector());
		fn2CM.Boost(-fh5.BoostVector());
		fh3CM.Boost(-fh5.BoostVector());
		fhe3CM.Boost(-(fh2 + fhe6).BoostVector());
		fh5CM.Boost(-(fh2 + fhe6).BoostVector());

		fn1CM.SetTheta(TMath::Pi() - fn1CM.Theta());
		fhe3CM.SetTheta(TMath::Pi() - fhe3CM.Theta());

		// fh5CM.SetTheta(TMath::Pi() - fh5CM.Theta());

		// h5EX->Fill(h5->GetMass() - n1->GetMass() - n2->GetMass() - h3->GetMass()); // h5 spectrum
		he6T->Fill(1000*(he6->GetEnergy() - he6->GetMass()));
		// he6Theta->Fill(fhe6.Theta()*TMath::RadToDeg());
		// he6Phi->Fill(fhe6.Phi()*TMath::RadToDeg());

		he3ThetaCM->Fill(fhe3CM.Theta()*TMath::RadToDeg());
		he3Theta2->Fill(fhe3CM.Theta()*TMath::RadToDeg(),he3->GetTheta()*TMath::RadToDeg());
		h5Theta2->Fill(fh5CM.Theta()*TMath::RadToDeg(),h5->GetTheta()*TMath::RadToDeg());

		he3t_thetCM->Fill(fhe3CM.Theta()*TMath::RadToDeg(),1000*(he3->GetEnergy() - he3->GetMass())/3.);
		h5t_thetCM->Fill(fh5CM.Theta()*TMath::RadToDeg(),1000*(h5->GetEnergy() - h5->GetMass())/5.);
		he3_h5_theta->Fill(h5->GetTheta()*TMath::RadToDeg(),he3->GetTheta()*TMath::RadToDeg());

		he3t_thet->Fill(he3->GetTheta()*TMath::RadToDeg(),1000*(he3->GetEnergy() - he3->GetMass())/3.);
		h5t_thet->Fill(fh5.Theta()*TMath::RadToDeg(),1000*(h5->GetEnergy() - h5->GetMass())/5.);

		if((h3->GetTheta())*TMath::RadToDeg() < 32 && (h3->GetEnergy() - h3->GetMass()) < 20) {
			he3Theta2cut->Fill(fhe3CM.Theta()*TMath::RadToDeg(),he3->GetTheta()*TMath::RadToDeg());
			h5Theta2cut->Fill(fh5CM.Theta()*TMath::RadToDeg(),h5->GetTheta()*TMath::RadToDeg());
		}

	}
	

	// draw		
	const Int_t ww = 1400;
	const Int_t wh = 1000;

	TH1F *htemp;

	TCanvas *cInt = new TCanvas("cInt", "Standard LISE++ output", ww, wh);
	cInt->Divide(3,2);

	cInt->cd(1);

	TPad *padInput = (TPad*)gPad;

	padInput->Divide(2,2);
	padInput->cd(1);
	tr->Draw("1000*(h5->GetMass() - h3->GetMass() - n1->GetMass() - n2->GetMass())");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{T} (MeV)");
	htemp->SetTitle("5H spectrum");

	padInput->cd(2);
	tr->SetLineColor(kBlack);
	// tr->Draw("(he6.fEnergy - he6.fMass)/6.", "");
	he6T->Draw();
	// htemp = (TH1F*)gPad->GetPrimitive("htemp");
	he6T->GetXaxis()->SetTitle("E_{beam} (MeV)");
	he6T->SetTitle("beam energy");

	padInput->cd(3);
	tr->Draw("he6->GetTheta()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{beam} (rad)");
	htemp->SetTitle("beam direction");

	padInput->cd(4);
	tr->Draw("he6->GetPhi()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Phi_{beam} (rad)");
	htemp->SetTitle("beam direction");
	cInt->cd(2);
	he3Theta2->SetMarkerColor(kBlue);
	he3Theta2->Draw();
	h5Theta2->SetMarkerColor(kRed);
	h5Theta2->Draw("same");
	he3Theta2->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3Theta2->GetYaxis()->SetTitle("\\Theta_{lab} (deg)");
	he3Theta2->SetTitle("binary reaction: no cut");	

	cInt->cd(3);
	he3t_thetCM->SetMarkerColor(4);
	he3t_thetCM->Draw();
	h5t_thetCM->SetMarkerColor(2);
	h5t_thetCM->Draw("same");
	he3t_thetCM->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3t_thetCM->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	he3t_thetCM->SetTitle("binary reaction: no cut");

	cInt->cd(4);
	he3ThetaCM->SetLineColor(1);
	he3ThetaCM->Draw();
	he3ThetaCM->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3ThetaCM->SetTitle("input reaction angle");

	cInt->cd(5);
	tr->SetMarkerColor(kBlack);
	tr->Draw("he3->GetTheta()*TMath::RadToDeg():h5->GetTheta()*TMath::RadToDeg()", "");
	// he3_h5_theta->SetMarkerColor(kRed);
	// he3_h5_theta->Draw("same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab}(5H) (deg)");
	htemp->GetYaxis()->SetTitle("\\Theta_{lab}(3He) (deg)");
	htemp->SetTitle("binary reaction: no cut");

// 	cInt->cd(5);
// //	tr->Draw("kin.GetHM() - 4690.362", "");
// 	tr->SetMarkerColor(kBlack);
// 	tr->Draw("he3->GetTheta()*TMath::RadToDeg():h5->GetTheta()*TMath::RadToDeg()", "");
// 	htemp = (TH1F*)gPad->GetPrimitive("htemp");
// 	htemp->GetXaxis()->SetTitle("\\Theta_{lab}(5H) (deg)");
// 	htemp->GetYaxis()->SetTitle("\\Theta_{lab}(3He) (deg)");
// 	htemp->SetTitle("binary reaction: no cut");

	cInt->cd(6);
	tr->SetMarkerColor(kBlue);
	tr->Draw("1000*(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("1000*(h5->GetEnergy() - h5->GetMass())/5:h5->GetTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("binary reaction: no cut");




	TCanvas *c1 = new TCanvas("c1", "Standard LISE++ output", ww, wh);
	c1->Divide(3,2);

	c1->cd(1);
	he3Theta2->SetMarkerColor(kBlue);
	he3Theta2->Draw();
	h5Theta2->SetMarkerColor(kBlue);
	h5Theta2->Draw("same");
	he3Theta2->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	he3Theta2->GetYaxis()->SetTitle("\\Theta_{lab} (deg)");
	he3Theta2->SetTitle("binary reaction: no cut");

	he3Theta2cut->SetMarkerColor(kGreen);
	he3Theta2cut->Draw();
	h5Theta2cut->SetMarkerColor(kGreen);
	h5Theta2cut->Draw("same");

	c1->cd(2);
	tr->SetMarkerColor(kBlue);
	tr->Draw("1000*(n1->GetEnergy() - n1->GetMass()):n1->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("1000*(n2->GetEnergy() - n2->GetMass()):n2->GetTheta()*TMath::RadToDeg()", "", "same");
//	tr->Draw("kin.GetTritonT()/3.:kin.GetTritonTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("neutrons");

	c1->cd(3);
	tr->SetMarkerColor(kBlack);
	tr->Draw("1000*(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", "", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("triton");

	c1->cd(4);
	tr->SetMarkerColor(kBlue);
	tr->Draw("1000*(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("1000*(h5->GetEnergy() - h5->GetMass())/5.:h5->GetTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("binary reaction: cut");

	tr->SetMarkerColor(kGreen);
	tr->Draw("1000*(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", cHeLocus,"");
	tr->Draw("1000*(h5->GetEnergy() - h5->GetMass())/5.:h5->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");


	c1->cd(5);
	tr->SetMarkerColor(kBlack);
	tr->Draw("1000*(n1->GetEnergy() - n1->GetMass()):n1->GetTheta()*TMath::RadToDeg()", "", "");
	tr->Draw("1000*(n2->GetEnergy() - n2->GetMass()):n2->GetTheta()*TMath::RadToDeg()", "", "same");
	tr->SetMarkerColor(kGreen);
	tr->Draw("1000*(n1->GetEnergy() - n1->GetMass()):n1->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("1000*(n2->GetEnergy() - n2->GetMass()):n2->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("neutrons: green cut");

	c1->cd(6);
	tr->SetMarkerColor(kBlack);
	tr->Draw("1000*(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kGreen);
	tr->Draw("1000*(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("triton: green cut");

	/*cInt->Print("output.pdf");
	cInt->Print("output.pdf[");
	cInt->Print("output.pdf");
	c1->Print("output.pdf");
	c1->Print("output.pdf]");*/


}