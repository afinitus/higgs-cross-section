void example( int seed , int SorB ){

  // This example shows how to generate random numbers, save the data in a TTree object. 
  // The ROOT file containing a TTree object is called a "ntuple"

  TTree fOutputTree("Hgg","Hgg") ;
  TFile fOuputFile("ntuple.root","recreate") ; 


  cout << " seed " << seed << " S or B " << SorB << endl;
  double mgg;
  fOutputTree.Branch("mgg", &mgg , "mgg/D") ;

  gRandom->SetSeed(seed);

  for( int i = 0 ; i < 1 ; i ++ )
    {
      if(SorB == 1) 
	mgg = gRandom->Gaus( 125, 2);
      else 
	mgg = 100+gRandom->Exp(50);

      //      cout << "the generated mass value " << mgg << endl;
      fOutputTree.Fill();
    }


  fOutputTree.Write();
  fOuputFile.Close();

}
