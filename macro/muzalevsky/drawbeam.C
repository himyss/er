void drawbeam(){

	TFile *fr = new TFile("kin.root", "READ");
	TTree *tr = (TTree*)fr->Get("tree");

	ERMCTrack *he6 = new ERMCTrack();

	tr->SetBranchAddress("he6.",&he6);

	tr->Draw("he6->GetEnergy() - he6->GetMass()", "");
	
	htemp = (TH1F*)gPad->GetPrimitive("htemp");
	htemp->GetXaxis()->SetTitle("E_{beam} (MeV)");
	htemp->SetTitle("beam energy");
}