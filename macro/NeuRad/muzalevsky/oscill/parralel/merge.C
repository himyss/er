void merge()
{
   	TChain ch("cbmsim");

	ch.Add("/home/muzalevsky/work/dataER/simNeuRad/6000_3.2_noCross/analyze2_0_300new.root");
    ch.Add("/home/muzalevsky/work/dataER/simNeuRad/6000_3.2_noCross/analyze1_0_300new.root");

	ch.Merge("/home/muzalevsky/work/dataER/simNeuRad/6000_3.2_noCross/analyzenew_0_300.root");
} 
