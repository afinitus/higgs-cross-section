//plotting
using namespace RooFit;
using namespace std;

void plotAll(float value, int fold_value){
  float which_study = value;
  int fold = fold_value;

  string rootName1;
  string rootName2;
  string rootName3;
  string compare;
  string data1;
  string data2;
  string data3;
  string fit1;
  string fit2;
  int min_spur, min_ds, min_sds;
  int max_spur, max_ds, max_sds;
    
      if(which_study == 1){
		  rootName1 = "norm";  
	      rootName2 = "smooth";
		  compare = "dists";
		  data1 = "Normal";
		  data2 = "Smooth";
		  min_spur = -15;
          max_spur = 15;
  }
    
  else if(which_study == 2){
        rootName1 = "MC";
		rootName2 = "ML";
		rootName3 = "truth";
		compare = Form("MCvML_%iFold", fold);
		data1 = "MC";
		data2 = "ML";
		data3 = "truth";
		min_spur = -20;
        max_spur = 20;
		min_ds = 10;
		max_ds = 20;
		min_sds = -2;
		max_sds = 2;
  }

	vector<TString> bkg_names;
	bkg_names.push_back("Bern3");
	bkg_names.push_back("Bern4");
	bkg_names.push_back("Bern5");
	bkg_names.push_back("ExpPoly2");
	bkg_names.push_back("Exponential");
	bkg_names.push_back("Dijet");
	bkg_names.push_back("ExpPoly3");