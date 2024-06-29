{
  // This example shows how to read out data from a ntuple.
  TFile *f = TFile::Open("input.root");  // AI - you should modify this so that you open the correct file
  TTree* output = (TTree*)f->Get("output") ; // Change the name of TTree from output to output, and this means you need to change all the instances in this script

  int nevt = output->GetEntries();
  cout << " The total number of entries in the TTree is "<< nevt << endl;


  vector<double> *ph_pt; // declare a vector to load ph_pt values from the TTree
  output->SetBranchAddress( "ph_pt", &ph_pt ); // load the value of the branch ph_pt from the TTree output
  // the first argument is a string, and it is the name of the branch in the TTree
  // the second argument is the vector double we declared a few lines above, and I choose to use the same name for convenience

  vector<double> *ph_eta;
  output->SetBranchAddress( "ph_eta", &ph_eta ); // load the value of the branch ph_eta from the TTree output


  TH1F* h_ph_pt = new TH1F("h_ph_pt","h_ph_pt",50,0,100); // by now, you should know how to declare a histogram, a TH1F object, and the meaning of all these entries

  TH1F* h_ph_eta = new TH1F("h_ph_eta","h_ph_eta", 10,-5,5);
  
  for( int i = 0 ; i < nevt ; i ++ )
    {
      output->GetEntry(i);

      const int size_of_photon_vector =  (*ph_pt).size();
      //      cout << "number of entries in the ph_pt vector is " << size_of_photon_vector << endl;
      //
      if ( (*ph_pt).size() != (*ph_eta).size() ) cout << "the sizes of photon pt and eta vectors are different "<< endl;

      /* some dummy selection */
      if( size_of_photon_vector > 0 )
	{
	  // only keep events with at least one photon
	  
	  // if there is at least one photon
	  //cout <<  (*ph_pt)[0] << endl;

	  h_ph_pt -> Fill( (*ph_pt)[0] ); // this gives the value in the first element

	 
	  if( (*ph_pt)[0] > 20 ){
	    h_ph_eta -> Fill( (*ph_eta)[0] );
	  }// this block of code is a dummy selection - if the pt of the photon is greater than 20 GeV, then fill the histogram of photon eta.
	}

      
      
      
      if( i > 2000 ) break; // just for debug purpose we stop after processing 200 entries. when your code is ready, remove or comment out this line
    }

  cout << " lets see what's printed here " <<   h_ph_pt->GetEntries() << " " << h_ph_pt -> Integral() << endl;


  h_ph_pt->Draw();

  TCanvas *c_1 = new TCanvas(); // declare a tcanvas
  h_ph_pt->Draw();
  c_1->SaveAs("photon_pt_distribution.pdf");


  TCanvas *c_2 = new TCanvas(); // declare a tcanvas
  h_ph_pt -> GetXaxis() -> SetTitle(" Photon p_{T} [GeV]"); // Get the Axis of the TH1/histogram and then set its title
  h_ph_pt -> GetYaxis() -> SetTitle(" Number of Entries"); // Get the Y Axis of the TH1/histogram and then set its title
  
  h_ph_pt->Draw();
  c_2->SaveAs("photon_pt_distribution_2.pdf");



  TCanvas *c_3 = new TCanvas(); // declare a tcanvas
  h_ph_pt -> GetXaxis() -> SetTitle(" Photon p_{T} [GeV]"); // Get the Axis of the TH1/histogram and then set its title
  h_ph_pt -> GetYaxis() -> SetTitle(" Number of Entries"); // Get the Y Axis of the TH1/histogram and then set its title

  double maximum_of_h = h_ph_pt -> GetMaximum(); // this gives you the maximum of the histogramCV
  
  h_ph_pt -> GetYaxis() -> SetRangeUser(0,1.2*maximum_of_h); // this sets the numerial range of Y axis, and you should be able to do it for the x axis as well.   
  
  h_ph_pt->Draw();
  c_3->SaveAs("photon_pt_distribution_3.pdf");
  c_3->SaveAs("photon_pt_distribution_3.png");
  c_3->SaveAs("photon_pt_distribution_3.eps");
  c_3->SaveAs("photon_pt_distribution_3.C");
  // in your terminal, try to open each of these four versions of the plot and see what is different.
  // for .pdf, .png, and .eps, you can just do "display filename"
  // for .C file, you need to do root -l photon_pt_distribution_3.C
  // the .C version of the plot directly constructs the final plot with Root. It provides great flexibility to introduce cosmetic changes after the plot is made.



  TCanvas *c_4 = new TCanvas(); // declare a tcanvas
  h_ph_eta -> GetXaxis() -> SetTitle(" Photon #eta [GeV]"); // Get the Axis of the TH1/histogram and then set its title
  h_ph_eta -> GetYaxis() -> SetTitle(" Number of Entries"); // Get the Y Axis of the TH1/histogram and then set its title

  maximum_of_h = h_ph_eta -> GetMaximum(); // this gives you the maximum of the histogramCV
  
  h_ph_eta -> GetYaxis() -> SetRangeUser(0,1.2*maximum_of_h); // this sets the numerial range of Y axis, and you should be able to do it for the x axis as well.   

  h_ph_eta->SetLineColor(2); // check how you change the color, width of a histogram
  h_ph_eta->SetLineWidth(2); // check how you change the color, width of a histogram
  
  h_ph_eta->Draw();
  h_ph_eta->Draw("Esame"); // try to comment out this line and see what's different in the plot
  c_4->SaveAs("photon_eta_distribution_4.pdf");



  TFile f2("outputfile.root","recreate");  // this line will create a new file in your current directory named outputfile.root

  // at this point, you opened a root file to write
  // the following lines show how you can tree a root object to the file
  h_ph_pt->Write();
  h_ph_eta->Write(); // we have filled these two histograms and now we save them in the output root file because we may need these histograms later
  f2.Close();

  
  
}
