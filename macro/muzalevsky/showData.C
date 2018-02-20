void showData(){

	TFile* f = new TFile("full.root");
	TTree* t = (TTree*) f->Get("er");
	TClonesArray* tracks = new TClonesArray("ERMCTrack",20);
	t->SetBranchAddress("MCTrack", &tracks);

	TFile *f1 = new TFile("kin.root","RECREATE");
	TTree *tree = new TTree("tree","kin");

	ERMCTrack *n1 = new ERMCTrack();
	ERMCTrack *n2 = new ERMCTrack();
	ERMCTrack *h3 = new ERMCTrack();
	ERMCTrack *h5 = new ERMCTrack();
	ERMCTrack *he3 = new ERMCTrack();
	ERMCTrack *he6 = new ERMCTrack();
	ERMCTrack *h2 = new ERMCTrack();

	tree->Bronch("n1.", "ERMCTrack", &n1);
	tree->Bronch("n2.", "ERMCTrack", &n2);
	tree->Bronch("h3.", "ERMCTrack", &h3);
	tree->Bronch("h5.", "ERMCTrack", &h5);
	tree->Bronch("he3.", "ERMCTrack", &he3);
	tree->Bronch("he6.", "ERMCTrack", &he6);
	tree->Bronch("h2.", "ERMCTrack", &h2);


	Int_t pdg,mID,tID,h3ID,h5ID;
	Int_t nN,flag,nh3,nEvents,nh5,nhe3,nh2;
	nEvents = 0;
	for(Int_t i=0; i<t->GetEntries();i++){
	// for(Int_t i=0; i<10;i++){
		// cout << " next event " << endl; 
		nN = 0; // number of neutrons
		nh3 = 0;
		flag = 0; // flag ( if 1 fill the tree, 0  - not)
		nh5 = 0;
		nhe3 = 0;
		nh2=0;
		t->GetEntry(i);

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	if(pdg == 1000010050) {
	    		flag = 1; // if there is an H5 in steck this event is interesting
	    		nEvents ++ ;
	    		nh5++;
	    		h5 = track;
	    		h5ID = mID;
	    	}
	    } 
	    if(flag!=1 && nh5!=1) continue;

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();
	    	if(pdg == 1000010030) { // if i want to choose the right neutrons i need to know their motherID
	    		h3ID = mID; 
	    		nh3++;
	    		h3 = track;
	    	} 
	    } 
	    if(nh3!=1) continue;  // i want to read events with 1 h3 only

		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	mID = track->GetMotherId();

	    	if((pdg == 2112) && (mID == h3ID)) {
	    		nN++;
	    		// if(nN == 1) track->Get4Momentum(*n1);
	    		// if(nN == 2) track->Get4Momentum(*n2);
	    		if(nN == 1) n1 = track;
	    		if(nN == 2) n2 = track;
	    	}
	    	if((pdg == 1000020030) && (mID == h5ID)) he3 = track;

	    	if(pdg == 1000010020) {
	    		nh2++;
	    		h2 = track;
	    	}
	    	
	    	if(pdg == 1000020060) he6 = track;

		}
		if((nN == 2) && (nh2 == 1)) tree->Fill();
	} // t->GetEntries()

	// cout << nEvents;
	tree->Write();
	f1->Close();
	return;
}
	/*	t->GetEntry(1619);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;
		t->GetEntry(2519);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
	    cout << endl << "next event " << endl;
		t->GetEntry(3950);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;
		t->GetEntry(5847);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;
		t->GetEntry(6900);
		for (Int_t iTrack = 0; iTrack < tracks->GetEntriesFast(); iTrack++){
	    	ERMCTrack* track = (ERMCTrack*)tracks->At(iTrack);
	    	pdg = track->GetPdgCode();
	    	cout << pdg << endl;
	    } 
  		cout << endl << "next event " << endl;*/
