#include <fstream>
#include "TCanvas.h"

using namespace std;

void showKinH5()
{
	TFile *fr = new TFile("kin.root", "READ");
	TTree *tr = (TTree*)fr->Get("tree");
	// cout << kin.GetHCMS().Mag() << " wtf " << endl;

	/*TLorentzVector *n1 = new TLorentzVector();
	TLorentzVector *n2 = new TLorentzVector();
	TLorentzVector *h5 = new TLorentzVector();
	TLorentzVector *h3 = new TLorentzVector();
	TLorentzVector *he3 = new TLorentzVector();
	TLorentzVector *he6 = new TLorentzVector();*/

	ERMCTrack *n1 = new ERMCTrack();
	ERMCTrack *n2 = new ERMCTrack();
	ERMCTrack *h3 = new ERMCTrack();
	ERMCTrack *h5 = new ERMCTrack();
	ERMCTrack *he3 = new ERMCTrack();
	ERMCTrack *he6 = new ERMCTrack();
	ERMCTrack *h2 = new ERMCTrack();

	tr->SetBranchAddress("n1.",&n1);
	tr->SetBranchAddress("n2.",&n2);
	tr->SetBranchAddress("h3.",&h3);
	tr->SetBranchAddress("h5.",&h5);
	tr->SetBranchAddress("he3.",&he3);
	tr->SetBranchAddress("he6.",&he6);
	tr->SetBranchAddress("h2.",&h2);

	// cout << r1->GetH5CMS().P() << " " << endl;
	// cout << h5.Mag() << " mass of h5?? " << endl;
	ifstream t1;
	/*for(Int_t i=0; i < r1->GetNumberOfOutputs(); i++){
		cout << endl << "d_3He" << endl;  
		cout << r1-> GetOutName(i) << " name of the " << i << " particle";
		cout << endl;
	}
	for(Int_t i=0; i < r2->GetNumberOfOutputs(); i++){
		cout << endl << "Hdecay" << endl;  
		cout << r2-> GetOutName(i) << " name of the " << i << " particle";
		cout << endl;
	}

*/
	// cout << r1->GetOutName(1) << " this is particle 1 " << endl;

	// cout << r1->GetNumberOfOutputs() << endl;
	// GetOutName(Int_t index);
	// TCut cGS = "(d_3He->GetH5CMS().Mag() - 2809.432 - 2*939.565)<2.6";
	TCut cHeLocus = "(h3->GetTheta())*TMath::RadToDeg() < 32 && (h3->GetEnergy() - h3->GetMass()) < 20";
	// TCut cHeLocus = "(3_He->GetTheta())*TMath::RadToDeg() < 15 && 3_He->GetT() < 20";
	// TCut cHeLocus = "kin.GetHeTheta()*TMath::RadToDeg() < 15 && kin.GetHeT() < 20";
	const Int_t ww = 1400;
	const Int_t wh = 1000;

	TH1F *htemp;

	TCanvas *cInt = new TCanvas("cInt", "Standard LISE++ output", ww, wh);
	cInt->Divide(3,2);

	cInt->cd(1);

	TPad *padInput = (TPad*)gPad;

	padInput->Divide(2,2);
	padInput->cd(1);
	tr->Draw("h5->GetMass() - h3->GetMass() - n1->GetMass() - n2->GetMass()");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{T} (MeV)");
	htemp->SetTitle("5H spectrum");

	padInput->cd(2);
	tr->SetLineColor(kBlack);
	tr->Draw("he6->GetEnergy() - he6->GetMass()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{beam} (MeV)");
	htemp->SetTitle("beam energy");

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
tr->Draw("he6->GetEnergy() - he6->GetMass()", "");

	/*cInt->cd(4);
	tr->SetLineColor(kBlack);
	tr->Draw("((he3->GetVector()).Boost(he6->GetVector().BoostVector())).Theta()");
	// tr->Draw("d_3He->GetThetaCM()*TMath::RadToDeg()");
	// gPad->SetLogy();
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	htemp->SetTitle("input reaction angle");


	cInt->cd(2);
	tr->SetMarkerColor(kBlue);
	// tr->Draw("3_He->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", "");
	tr->Draw("he3->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", ""); // график, какой у вратислава (с вычетом из 180)
	tr->SetMarkerColor(kRed);
	tr->Draw("5_H->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	htemp->GetYaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("binary reaction: no cut");	


	cInt->cd(3);
	tr->SetMarkerColor(kBlue);
	tr->Draw("3_He->GetT()/3.:(d_3He->GetThetaCM())*TMath::RadToDeg()", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("5_H->GetT()/5.:(d_3He->GetThetaCM())*TMath::RadToDeg()","", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->SetTitle("binary reaction: no cut");*/

	cInt->cd(5);
//	tr->Draw("kin.GetHM() - 4690.362", "");
	tr->SetMarkerColor(kBlack);
	tr->Draw("he3->GetTheta()*TMath::RadToDeg():h5->GetTheta()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab}(5H) (deg)");
	htemp->GetYaxis()->SetTitle("\\Theta_{lab}(3He) (deg)");
	htemp->SetTitle("binary reaction: no cut");


	cInt->cd(6);
	tr->SetMarkerColor(kBlue);
	tr->Draw("(h3->GetEnergy() - h3->GetMass())/3:he3->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("(h5->GetEnergy() - h5->GetMass())/5:h5->GetTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("binary reaction: no cut");


	////////////////////////////////////////
	//// canvas with 3-body results
	////////////////////////////////////////
	TCanvas *c1 = new TCanvas("c1", "Standard LISE++ output", ww, wh);
	c1->Divide(3,2);
/*
	c1->cd(1);
	tr->SetMarkerColor(kBlue);
	tr->Draw("3_He->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", ""); // график, какой у вратислава (с вычетом из 180)
	tr->SetMarkerColor(kRed);
	tr->Draw("5_H->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", "", "same");


//
	tr->SetMarkerColor(kGreen);
	tr->Draw("5_H->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("3_He->GetTheta()*TMath::RadToDeg():(d_3He->GetThetaCM())*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	htemp->GetYaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("green cut: thetaLab(3He) < 32 deg && Tlab(3He) < 20 MeV");*/

	c1->cd(2);
	tr->SetMarkerColor(kBlue);
	tr->Draw("n1->GetEnergy() - n1->GetMass():n1->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("n2->GetEnergy() - n2->GetMass():n2->GetTheta()*TMath::RadToDeg()", "", "same");
//	tr->Draw("kin.GetTritonT()/3.:kin.GetTritonTheta()*TMath::RadToDeg()", "", "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("neutrons");

	c1->cd(3);
	tr->SetMarkerColor(kBlack);
	tr->Draw("(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", "", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("triton");

	c1->cd(4);
	tr->SetMarkerColor(kBlue);
	tr->Draw("(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", "");
	tr->SetMarkerColor(kRed);
	tr->Draw("(h5->GetEnergy() - h5->GetMass())/5.:h5->GetTheta()*TMath::RadToDeg()", "", "same");

	/*tr->SetMarkerColor(kGreen);
	tr->Draw("(he3->GetEnergy() - he3->GetMass())/3.:he3->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("(h5->GetEnergy() - h5->GetMass())/5.:h5->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("green cut: thetaLab(3He) < 32 deg && Tlab(3He) < 20 MeV");*/



	c1->cd(5);
	tr->SetMarkerColor(kBlack);
	tr->Draw("n1->GetEnergy() - n1->GetMass():n1->GetTheta()*TMath::RadToDeg()", "", "");
	tr->Draw("n2->GetEnergy() - n2->GetMass():n2->GetTheta()*TMath::RadToDeg()", "", "same");
	tr->SetMarkerColor(kGreen);
	tr->Draw("n1->GetEnergy() - n1->GetMass():n1->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("n2->GetEnergy() - n2->GetMass():n2->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("neutrons: green cut");

	c1->cd(6);
	tr->SetMarkerColor(kBlack);
	tr->Draw("(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", "", "");
	tr->SetMarkerColor(kGreen);
	tr->Draw("(h3->GetEnergy() - h3->GetMass())/3.:h3->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("T_{lab} (MeV/A)");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("triton: green cut");




	TCanvas *c3 = new TCanvas("c3", "Standard LISE++ output", ww, wh);

	c3->Divide(2,2);
	c3->cd(1);
	tr->Draw("h5->GetMass() - h3->GetMass() - n1->GetMass() - n2->GetMass()");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{T} (MeV)");
	htemp->SetTitle("5H spectrum");

	c3->cd(2);
	tr->SetLineColor(kBlack);
	tr->Draw("he6->GetEnergy() - he6->GetMass()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{beam} (MeV)");
	htemp->SetTitle("beam energy");

	c3->cd(3);
	tr->Draw("he6->GetTheta()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{beam} (rad)");
	htemp->SetTitle("beam direction Theta");

	c3->cd(4);
	tr->Draw("he6->GetPhi()*TMath::RadToDeg()", "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Phi_{beam} (rad)");
	htemp->SetTitle("beam direction Phi");
return;
}
/*
	TCanvas *c2 =  new TCanvas("c2", "CMS of 5H", ww, wh);
	c2->Divide(4,2);

	c2->cd(1);
	TPad *padInputChoice = (TPad*)gPad;
	padInputChoice->Divide(1,2);

	padInputChoice->cd(1);
//	tr->Draw("kin.GetHeTheta()*TMath::RadToDeg():kin.GetHTheta()*TMath::RadToDeg()", "");
//	tr->Draw("kin.GetHCMS().Mag() - 4690.36244");
	tr->Draw("d_3He->GetH5CMS().Mag() - 2809.432 - 2*939.565");
	tr->SetLineColor(kRed);
	tr->Draw("d_3He->GetH5CMS().Mag() - 2809.432 - 2*939.565", cGS, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{T} (MeV)");
	htemp->SetTitle("5H energy spectrum");

	padInputChoice->cd(2);
	tr->Draw("(d_3He->GetThetaCM())*TMath::RadToDeg()", "");
	tr->SetLineColor(kGreen);
	tr->Draw("(d_3He->GetThetaCM())*TMath::RadToDeg()", cHeLocus, "same");
	gPad->SetLogy();
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("\\Theta_{CM} (deg)");
	htemp->SetTitle("input reaction angle: green cut");

	c2->cd(2);
	tr->SetLineColor(kBlack);
	tr->Draw("Hdecay->GetTritonCMS().P()");
	tr->SetLineColor(kRed);
	tr->Draw("Hdecay->GetTritonCMS().P()", cGS, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("p_{5H CM}(^{3}H) (MeV/c)");
	htemp->SetTitle("CMS of 5H: no cut");
//	htemp->SetName("beam direction");


	c2->cd(3);
	tr->SetLineColor(kBlack);
	tr->Draw("Hdecay->GetN1CMS().P()");
	tr->SetLineColor(kRed);
	tr->Draw("Hdecay->GetN1CMS().P()", cGS, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("p_{5H CM}(n_{1}) (MeV/c)");
	htemp->SetTitle("CMS of 5H: no cut");

	c2->cd(4);
	tr->SetLineColor(kBlack);
	tr->Draw("Hdecay->GetN2CMS().P()");
	tr->SetLineColor(kRed);
	tr->Draw("Hdecay->GetN2CMS().P()", cGS, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("p_{5H CM}(n_{2}) (MeV/c)");
	htemp->SetTitle("CMS of 5H: no cut");



	c2->cd(5);
	tr->SetMarkerColor(kBlue);
//	tr->Draw("kin.GetHeT()/3.:kin.GetHeTheta()*TMath::RadToDeg()", "");
	tr->Draw("3_He.fImpulse.P()/3.:3_He->GetTheta()*TMath::RadToDeg()","");
	tr->SetMarkerColor(kRed);
//	tr->Draw("kin.GetHT()/5.:kin.GetHTheta()*TMath::RadToDeg()", "", "same");
	tr->Draw("5_H.fImpulse.P()/5.:5_H->GetTheta()*TMath::RadToDeg()", "", "same");


	tr->SetMarkerColor(kGreen);
	tr->Draw("3_He.fImpulse.P()/3.:3_He->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	tr->Draw("5_H.fImpulse.P()/5.:5_H->GetTheta()*TMath::RadToDeg()", cHeLocus, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetYaxis()->SetTitle("|p|_{lab} (MeV.A^{-1}.c^{-1})");
	htemp->GetXaxis()->SetTitle("\\Theta_{lab} (deg)");
	htemp->SetTitle("kinematics: green cut");


	c2->cd(6);
	tr->SetLineColor(kGreen);
	tr->Draw("Hdecay->GetTritonCMS().P()", cHeLocus, "");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("p_{5H CM}(^{3}H) (MeV/c)");
	htemp->SetTitle("CMS of 5H: green cut");

	c2->cd(7);
//	tr->SetLineColor(kBlack);
	tr->Draw("Hdecay->GetN1CMS().P()", cHeLocus);
//	tr->SetLineColor(kRed);
//	tr->Draw("kin.GetN1CMS().P()", cGS, "same");
//	tr->SetLineColor(kRed);
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("p_{5H CM}(n_{1}) (MeV/c)");
	htemp->SetTitle("CMS of 5H: green cut");

	c2->cd(8);
//	tr->SetLineColor(kBlack);
	tr->Draw("Hdecay->GetN2CMS().P()", cHeLocus);
//	tr->SetLineColor(kRed);
//	tr->Draw("kin.GetN2CMS().P()", cGS, "same");
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("p_{5H CM}(n_{2}) (MeV/c)");
	htemp->SetTitle("CMS of 5H: green cut");

	TCanvas *c3 =  new TCanvas("c3", "test", ww, wh);
	c3->Divide(2,2);
	TLorentzVector n1,n2,n3,n4,h7,h3,suma;
	Double_t mh7,m;
	// for(Int_t i=0;i<tr->GetEntries();i++){
	for(Int_t i=0;i<5;i++){
		tr->GetEntry(i);
		n1 = np1->Get4Vector();
		n2 = np2->Get4Vector();
		h7 = nh5->Get4Vector();
		h3 = nh3->Get4Vector();

		TVector3 bVect = h7.BoostVector();
		h3.Boost(-bVect);
		n1.Boost(-bVect);
		n2.Boost(-bVect);
		n3.Boost(-bVect);
		n4.Boost(-bVect);
		m = h3.E() + n1.E() + n2.E();
		mh7 = 6567.69;
		cout << mh7-m << endl;
		// hn1->Fill(mh7-m);
	}
	c3->cd(1);*/
/*

	TCanvas *c3 =  new TCanvas("c3", "test", ww, wh);
	c3->Divide(2,2);
	c3->cd(1);
	tr->Draw("n1->GetTheta()*TMath::RadToDeg()");
	c3->cd(2);
	tr->Draw("n2->GetTheta()*TMath::RadToDeg()");
	c3->cd(3);
	
	TF1 *fitCos = new TF1("fitCos","[0]*sin(x*[1])",0.,180.); 
	fitCos->SetParLimits(1,0.,0.1);
	fitCos->SetParLimits(0,200.,700.);
	TLorentzVector n1,n2,h5,h3,suma;
	Double_t tcmn1,tcmn2;
	TH1F *hn1 = new TH1F("hn1","theta n1",50,0.,180.);
	TH1F *hn2 = new TH1F("hn2","theta n2",50,0.,180.);
	for(Int_t i=0;i<tr->GetEntries();i++){
	// for(Int_t i=0;i<3;i++)
		tr->GetEntry(i);
		n1 = np1->Get4Vector();
		n2 = np2->Get4Vector();
		h5 = nh5->Get4Vector();
		h3 = nh3->Get4Vector();
		// suma = h3 + n1 + n2;
		// cout << suma.Px() << " " << suma.Py() << " " << suma.Pz() << " " << suma.E() << endl;
		// cout << h5.Px() << " " << h5.Py() << " " << h5.Pz() << " " << h5.E() << endl;
		TVector3 bVect = h5.BoostVector();
		n1.Boost(-bVect);
		n2.Boost(-bVect);
		tcmn1 = n1.Theta()*TMath::RadToDeg();
		tcmn2 = n2.Theta()*TMath::RadToDeg();
		// cout<< tcmn1 << "  " << tcmn2 << endl;
		hn1->Fill(tcmn1);
		hn2->Fill(tcmn2);
	}
	hn1->Draw();
	hn1->Fit("fitCos");
	c3->cd(4);
	hn2->Draw();
	hn2->Fit("fitCos");

//	return;

	cInt->Print("output.pdf");
	cInt->Print("output.pdf[");
	cInt->Print("output.pdf");
	c1->Print("output.pdf");
	c2->Print("output.pdf");
	c2->Print("output.pdf]");

}
*/