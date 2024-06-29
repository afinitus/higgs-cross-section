//NEWEST PLOTTING SPUR TOOL

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
  //if (rootfile == "smooth.txt" || rootfile == "smooth_gr40.txt" || rootfile == "smooth_le18.txt" || rootfile == "smooth_b1840.txt" || rootfile == "smooth_inc_half.txt" || rootfile == "smooth_pre.txt" || rootfile == "smooth_ori.txt"){
  if(which_study == 1){
		  rootName1 = "norm";  
	      rootName2 = "smooth";
		  compare = "dists";
		  data1 = "Normal";
		  data2 = "Smooth";
		  min_spur = -15;
          max_spur = 15;
  }
  //else if (rootfile == "MC.txt"){ //Monte Carlo method also ML
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

    //define bkg names
	vector<TString> bkg_names;
	bkg_names.push_back("Bern3");
	bkg_names.push_back("Bern4");
	bkg_names.push_back("Bern5");
	bkg_names.push_back("ExpPoly2");
	bkg_names.push_back("Exponential");
	bkg_names.push_back("Dijet");
	bkg_names.push_back("ExpPoly3");

	//equations used:
	vector<TString> eq;
	eq.push_back("N#sum^{3}_{i=0}a_{i}B_{in}");
	eq.push_back("N#sum^{4}_{i=0}a_{i}B_{in}");
	eq.push_back("N#sum^{5}_{i=0}a_{i}B_{in}");
	eq.push_back("exp#left(a_{0}#left(#frac{x-100}{100}#right) + a_{1}#left(#frac{x-100}{100}#right)^{2}#right)");
	eq.push_back("e^{a_{0}mass}");
	eq.push_back("mass^{a_{0}}(1 - mass)^{a_{1}}");
	eq.push_back("exp#left(a_{0}#left(#frac{x-100}{100}#right) + a_{1}#left(#frac{x-100}{100}#right)^{2} + a_{2}#left(#frac{x-100}{100}#right)^{3}#right)");

	//string compare = "dists_gr40_newSmoothing";
	//string compare = "25_bin_exp2";
	//string compare = "dists_newS_10P";
	//string compare = "dists_all_50P";
	//string compare = "dists_cut_gr40";
	//string compare = "dists_inclusive_half_newSS";
	//string compare = "dists_exclusive_10P";

//open TFILES
int size = 9;
double mean_val[size];
double count = 121.0;
for (int j = 0; j < size; j++) {
	mean_val[j] = count;
    count = count + 1;
    //cout << "sig" << j << ": " << sigmeanVal[j] << endl;
}
//array to hold bias, impact
double bias[size][bkg_names.size()];
double impact[size][bkg_names.size()];
//SS
double mean_smooth[size][bkg_names.size()];
double mean_norm[size][bkg_names.size()];
double mean_tru[size][bkg_names.size()];
double width_smooth[size][bkg_names.size()];
double width_norm[size][bkg_names.size()];
double width_tru[size][bkg_names.size()];

double mean_smoothErr[size][bkg_names.size()];
double mean_normErr[size][bkg_names.size()];
double mean_truErr[size][bkg_names.size()];
double width_smoothErr[size][bkg_names.size()];
double width_normErr[size][bkg_names.size()];
double width_truErr[size][bkg_names.size()];
//delta S
double mean_smooth_ds[size][bkg_names.size()];
double mean_norm_ds[size][bkg_names.size()];
double mean_tru_ds[size][bkg_names.size()];
double width_smooth_ds[size][bkg_names.size()];
double width_norm_ds[size][bkg_names.size()];
double width_tru_ds[size][bkg_names.size()];

double mean_smoothErr_ds[size][bkg_names.size()];
double mean_normErr_ds[size][bkg_names.size()];
double mean_truErr_ds[size][bkg_names.size()];
double width_smoothErr_ds[size][bkg_names.size()];
double width_normErr_ds[size][bkg_names.size()];
double width_truErr_ds[size][bkg_names.size()];

//S devied by delta S , S/dS
double mean_smooth_sds[size][bkg_names.size()];
double mean_norm_sds[size][bkg_names.size()];
double mean_tru_sds[size][bkg_names.size()];
double width_smooth_sds[size][bkg_names.size()];
double width_norm_sds[size][bkg_names.size()];
double width_tru_sds[size][bkg_names.size()];

double mean_smoothErr_sds[size][bkg_names.size()];
double mean_normErr_sds[size][bkg_names.size()];
double mean_truErr_sds[size][bkg_names.size()];
double width_smoothErr_sds[size][bkg_names.size()];
double width_normErr_sds[size][bkg_names.size()];
double width_truErr_sds[size][bkg_names.size()];


//chi2 arrays
double bias2[size][bkg_names.size()];
double impact2[size][bkg_names.size()];
double mean_smooth2[size][bkg_names.size()];
double mean_norm2[size][bkg_names.size()];
double width_smooth2[size][bkg_names.size()];
double width_norm2[size][bkg_names.size()];

double mean_smooth2Err[size][bkg_names.size()];
double mean_norm2Err[size][bkg_names.size()];
double width_smooth2Err[size][bkg_names.size()];
double width_norm2Err[size][bkg_names.size()];

//array to hold bias, impact for max SS
	double bias3[bkg_names.size()];
	double impact3[bkg_names.size()];
	double mean_smooth3[bkg_names.size()];
	double mean_norm3[bkg_names.size()];
	double mean_truth3[bkg_names.size()];
	double width_smooth3[bkg_names.size()];
	double width_norm3[bkg_names.size()];
	double width_truth3[bkg_names.size()];

	double mean_smooth3Err[bkg_names.size()];
	double mean_norm3Err[bkg_names.size()];
	double mean_truth3Err[bkg_names.size()];
	double width_smooth3Err[bkg_names.size()];
	double width_norm3Err[bkg_names.size()];
	double width_truth3Err[bkg_names.size()];

	// arrays for max s/ds
    double bias4[bkg_names.size()];
	double impact4[bkg_names.size()];
	double mean_smooth4[bkg_names.size()];
	double mean_norm4[bkg_names.size()];
	double mean_truth4[bkg_names.size()];
	double width_smooth4[bkg_names.size()];
	double width_norm4[bkg_names.size()];
	double width_truth4[bkg_names.size()];

	double mean_smooth4Err[bkg_names.size()];
	double mean_norm4Err[bkg_names.size()];
	double mean_truth4Err[bkg_names.size()];
	double width_smooth4Err[bkg_names.size()];
	double width_norm4Err[bkg_names.size()];
	double width_truth4Err[bkg_names.size()];

 TH1D* spur;
 TH1D* spur_smooth;
 TH1D* spur_truth;

 TH1D* spur_ds;
 TH1D* spur_smooth_ds;
 TH1D* spur_truth_ds;

 TH1D* spur_sds;
 TH1D* spur_smooth_sds;
 TH1D* spur_truth_sds;

 TH1D* chiSq;
 TH1D* chiSq_smooth;
for(int k = 0; k < size; k++){

	//if (mean_val[k] != 125.0) continue;
	for(int i = 0; i < bkg_names.size(); i++){
		if (bkg_names[i] == "Dijet") { continue; }
		//if (bkg_names[i] != "ExpPoly2") continue; 

	TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data()));
	TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names[i].Data()));
	TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names[i].Data()));

		//get histo: 
		spur = (TH1D*) f1->Get(Form("spur_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_smooth = (TH1D*) f2->Get(Form("spur_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_truth = (TH1D*) f3->Get(Form("spur_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));

		spur_ds = (TH1D*) f1->Get(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_smooth_ds = (TH1D*) f2->Get(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_truth_ds = (TH1D*) f3->Get(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));

		spur_sds = (TH1D*) f1->Get(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_smooth_sds = (TH1D*) f2->Get(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_truth_sds = (TH1D*) f3->Get(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		//rename
                spur -> SetName("spur");
                spur_smooth -> SetName("spur_smooth");
				spur_truth -> SetName("spur_truth");

				spur_ds -> SetName("spur_ds");
                spur_smooth_ds -> SetName("spur_smooth_ds");
				spur_truth_ds -> SetName("spur_truth_ds");

				spur_sds -> SetName("spur_sds");
                spur_smooth_sds -> SetName("spur_smooth_sds");
				spur_truth_sds -> SetName("spur_truth_sds");

		double width, mean, width_2, mean_2, width_error, mean_error, width_2_error, mean_2_error;

		//For spurious signal
		width = spur->GetRMS();
		mean = spur->GetMean();
		width_2 = spur_smooth->GetRMS();
		mean_2 = spur_smooth->GetMean();

		width_error = spur->GetRMSError();
		mean_error = spur->GetMeanError();
		width_2_error = spur_smooth->GetRMSError();
		mean_2_error = spur_smooth->GetMeanError();

		RooRealVar mean_ss("mean_ss", "", -1, -10, 10);
		RooRealVar width_ss("width_ss", "", 5, 0, 10);
		RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min_spur, max_spur);
		RooGaussian gauss_SS("gauss_SS","gauss", *spurious_signal,mean_ss,width_ss);
		
		RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,spur);
		gauss_SS.fitTo(*ss);

		RooRealVar mean_ss_smooth("mean_ss_smooth", "", -1, -10, 10);
		RooRealVar width_ss_smooth("width_ss_smooth", "", 5, 0, 10);
		RooGaussian gauss_SS_smooth("gauss_SS_smooth","gauss", *spurious_signal,mean_ss_smooth,width_ss_smooth);

		RooDataHist* ss_smooth = new RooDataHist("ss_smooth", "Spurious Signal Smooth Data", *spurious_signal,spur_smooth);
		gauss_SS_smooth.fitTo(*ss_smooth);

		RooRealVar mean_truth("mean_truth", "", -1, -10, 10);
		RooRealVar width_truth("width_truth", "", 5, 0, 10);
		RooGaussian gauss_truth("gauss_truth","gauss", *spurious_signal,mean_truth,width_truth);

		RooDataHist* ss_truth = new RooDataHist("ss_truth", "Spurious Signal Smooth Data", *spurious_signal,spur_truth);
		gauss_truth.fitTo(*ss_truth);
		
		RooPlot* spurframe = spurious_signal->frame();
		ss->plotOn(spurframe, Name("ss"));
		ss_smooth->plotOn(spurframe, Name("ss_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		ss_truth->plotOn(spurframe, Name("ss_truth"),MarkerColor(kGreen), LineColor(kGreen));

		gauss_SS.plotOn(spurframe, Name("gauss_SS"));
		gauss_SS_smooth.plotOn(spurframe, Name("gauss_SS_smooth"), LineColor(kRed));
		gauss_truth.plotOn(spurframe, Name("gauss_truth"), LineColor(kYellow));

		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s plot & Mean Val: %3.0f", bkg_names[i].Data(), mean_val[k]));
		spurframe->GetXaxis()->SetTitle("Spurious Signal");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
        l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
		l->AddEntry("ss", Form("Data %s", data1.c_str()), "LEP");
        l->AddEntry("ss_smooth", Form("Data %s", data2.c_str()), "LEP");
		l->AddEntry("ss_truth", Form("Data %s", data3.c_str()), "LEP");
        l->AddEntry("gauss_SS", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_ss.getVal(), width_ss.getError(), mean_ss.getVal(), mean_ss.getError()), "L");
    	l->AddEntry("gauss_SS_smooth", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_ss_smooth.getVal(), width_ss_smooth.getError(), mean_ss_smooth.getVal(), mean_ss_smooth.getError()), "L");
		l->AddEntry("gauss_truth", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_truth.getVal(), width_truth.getError(),mean_truth.getVal(), mean_truth.getError()), "L");
		l->Draw();

		//calculation for bias
		// bias[k][i] = abs((mean_ss.getVal() - mean_ss_smooth.getVal())/mean_ss.getVal());
		// impact[k][i] = abs(width_ss_smooth.getVal()/width_ss.getVal());
		// mean_smooth[k][i] = mean_ss_smooth.getVal();
		// mean_norm[k][i] = mean_ss.getVal();
		// width_smooth[k][i] = width_ss_smooth.getVal();
		// width_norm[k][i] = width_ss.getVal();

		bias[k][i] = abs((mean - mean_2)/mean);
		impact[k][i] = abs(width_2/width);
		
		mean_smooth[k][i] = mean_ss_smooth.getVal();
		mean_norm[k][i] = mean_ss.getVal();
		mean_tru[k][i] = mean_truth.getVal();

		width_smooth[k][i] = width_ss.getVal();
		width_norm[k][i] = width_ss_smooth.getVal();
		width_tru[k][i] = width_truth.getVal();

		mean_smoothErr[k][i] = mean_ss_smooth.getError();
		mean_normErr[k][i] = mean_ss.getError();
		mean_truErr[k][i] = mean_truth.getError();

		width_smoothErr[k][i] = width_ss_smooth.getError();
		width_normErr[k][i] = width_ss.getError();
		width_truErr[k][i] = width_truth.getError();

		system(Form("mkdir -vp distributions/%s", compare.c_str()));
		c2 -> SaveAs(Form("distributions/%s/%s_SS_%3.0f.png", compare.c_str(), bkg_names[i].Data(), mean_val[k]));
	}
}


//my code for graphs
TH1D* spur_121;
TH1D* spur_123;
TH1D* spur_125;
TH1D* spur_127;
TH1D* spur_129;
char* fname = "tables.txt";
FILE *fp = fopen(fname, "w");
for(int i = 0; i < bkg_names.size(); i++){
    if (i == 5) {
        continue;
    }
	TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data()));

	spur_121 = (TH1D*) f1->Get(Form("spur_%s_121",bkg_names[i].Data()));
	spur_123 = (TH1D*) f1->Get(Form("spur_%s_123",bkg_names[i].Data()));
	spur_125 = (TH1D*) f1->Get(Form("spur_%s_125",bkg_names[i].Data()));
	spur_127 = (TH1D*) f1->Get(Form("spur_%s_127",bkg_names[i].Data()));
	spur_129 = (TH1D*) f1->Get(Form("spur_%s_129",bkg_names[i].Data()));

	spur_121->SetName("spur_121");
	spur_123->SetName("spur_123");
	spur_125->SetName("spur_125");
	spur_127->SetName("spur_127");
	spur_129->SetName("spur_129");

	RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min_spur, max_spur);
	
	RooRealVar mean_ss_121("mean_ss", "", -1, -10, 10);
	RooRealVar width_ss_121("width_ss", "", 5, 0, 10);
	RooGaussian gauss_SS_121("gauss_SS","gauss", *spurious_signal,mean_ss_121,width_ss_121);

	RooRealVar mean_ss_123("mean_ss", "", -1, -10, 10);
	RooRealVar width_ss_123("width_ss", "", 5, 0, 10);
	RooGaussian gauss_SS_123("gauss_SS","gauss", *spurious_signal,mean_ss_123,width_ss_123);

	RooRealVar mean_ss_125("mean_ss", "", -1, -10, 10);
	RooRealVar width_ss_125("width_ss", "", 5, 0, 10);
	RooGaussian gauss_SS_125("gauss_SS","gauss", *spurious_signal,mean_ss_125,width_ss_125);

	RooRealVar mean_ss_127("mean_ss", "", -1, -10, 10);
	RooRealVar width_ss_127("width_ss", "", 5, 0, 10);
	RooGaussian gauss_SS_127("gauss_SS","gauss", *spurious_signal,mean_ss_127,width_ss_127);
	
	RooRealVar mean_ss_129("mean_ss", "", -1, -10, 10);
	RooRealVar width_ss_129("width_ss", "", 5, 0, 10);
	RooGaussian gauss_SS_129("gauss_SS","gauss", *spurious_signal,mean_ss_129,width_ss_129);

	RooDataHist* ss_121 = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal, spur_121);
	gauss_SS_121.fitTo(*ss_121);
	
	RooDataHist* ss_123 = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal, spur_123);
	gauss_SS_123.fitTo(*ss_123);	

	RooDataHist* ss_125 = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal, spur_125);
	gauss_SS_125.fitTo(*ss_125);

	RooDataHist* ss_127 = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal, spur_127);
	gauss_SS_127.fitTo(*ss_127);

	RooDataHist* ss_129 = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal, spur_129);
	gauss_SS_129.fitTo(*ss_129);
	
	RooPlot* spurframe = spurious_signal->frame();
	ss_121->plotOn(spurframe, Name("ss_121"),MarkerColor(kBlue), LineColor(kBlue));
	gauss_SS_121.plotOn(spurframe, Name("gauss_SS_121"), MarkerColor(kBlue), LineColor(kBlue));

	ss_123->plotOn(spurframe, Name("ss_123"),MarkerColor(kYellow), LineColor(kYellow));
	gauss_SS_123.plotOn(spurframe, Name("gauss_SS_123"), MarkerColor(kYellow), LineColor(kYellow));

	ss_125->plotOn(spurframe, Name("ss_125"),MarkerColor(kRed), LineColor(kRed));
	gauss_SS_125.plotOn(spurframe, Name("gauss_SS_125"), MarkerColor(kRed), LineColor(kRed));

	ss_127->plotOn(spurframe, Name("ss_127"),MarkerColor(kBlack), LineColor(kBlack));
	gauss_SS_127.plotOn(spurframe, Name("gauss_SS_127"), MarkerColor(kBlack), LineColor(kBlack));

	ss_129->plotOn(spurframe, Name("ss_129"), MarkerColor(kGreen), LineColor(kGreen));
	gauss_SS_129.plotOn(spurframe, Name("gauss_SS_129"), MarkerColor(kGreen), LineColor(kGreen));

	TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
	spurframe->SetTitle(Form("%s plot & Mean Val: %s", bkg_names[i].Data(), "121, 123, 125, 127, 129"));
	spurframe->GetXaxis()->SetTitle("Spurious Signal");
	spurframe->GetYaxis()->SetTitle("N_Samples");
	spurframe->Draw();

	TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
	l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
	l->SetLineColor(kWhite);
	l->SetTextSize(0.03);
	l->AddEntry("ss", Form("Data %s", data1.c_str()), "LEP");
	l->AddEntry("gauss_SS_121", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", "121 MC", width_ss_121.getVal(), width_ss_121.getError(), mean_ss_121.getVal(), mean_ss_121.getError()), "L");
	l->AddEntry("gauss_SS_123", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", "123 MC", width_ss_123.getVal(), width_ss_123.getError(), mean_ss_123.getVal(), mean_ss_123.getError()), "L");
	l->AddEntry("gauss_SS_125", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", "125 MC", width_ss_125.getVal(), width_ss_125.getError(), mean_ss_125.getVal(), mean_ss_125.getError()), "L");
	l->AddEntry("gauss_SS_127", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", "127 MC", width_ss_127.getVal(), width_ss_127.getError(), mean_ss_127.getVal(), mean_ss_127.getError()), "L");
	l->AddEntry("gauss_SS_129", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", "129 MC", width_ss_129.getVal(), width_ss_129.getError(), mean_ss_129.getVal(), mean_ss_129.getError()), "L");
	l->Draw();
	
	system(Form("mkdir -vp distributions/%s", compare.c_str()));
	c2->SaveAs(Form("distributions/%s/%s_COMPARINGPLOTS.png", compare.c_str(), bkg_names[i].Data()));
	char* dist[] = {"Bern3", "Bern4", "Bern5", "ExpPoly2", "Exponential", "Dijet", "ExpPoly3"};
	if (i == 0 || i == 1 || i == 2) {
		fprintf(fp, "%s      Mean  ± MeanErr Width  ±  WidthErr\n", dist[i]);
	}
    if (i == 3) {
		fprintf(fp, "%s   Mean ±  MeanErr  Width  ±  WidthErr\n", dist[i]);
	}
    if (i == 4) {
		fprintf(fp, "%s Mean ± MeanErr  Width ± WidthErr\n", dist[i]);
	}
    if (i == 6) {
		fprintf(fp, "%s    Mean ± MeanErr  Width ± WidthErr\n", dist[i]);
	}
	fprintf(fp, "121 GeV  %.4f ± %.4f  %.4f ± %.4f\n", mean_ss_121.getVal(), mean_ss_121.getError(), width_ss_121.getVal(), width_ss_121.getError());
	fprintf(fp, "123 GeV  %.4f ± %.4f  %.4f ± %.4f\n", mean_ss_123.getVal(), mean_ss_123.getError(), width_ss_123.getVal(), width_ss_123.getError());
	fprintf(fp, "125 GeV  %.4f ± %.4f  %.4f ± %.4f\n", mean_ss_125.getVal(), mean_ss_125.getError(), width_ss_125.getVal(), width_ss_125.getError());
	fprintf(fp, "127 GeV  %.4f ± %.4f  %.4f ± %.4f\n", mean_ss_127.getVal(), mean_ss_127.getError(), width_ss_127.getVal(), width_ss_127.getError());
	fprintf(fp, "129 GeV  %.4f ± %.4f  %.4f ± %.4f\n", mean_ss_129.getVal(), mean_ss_129.getError(), width_ss_129.getVal(), width_ss_129.getError());
	fprintf(fp, "--------------------------------------------------\n");
}
fclose(fp);





//Delta S
for(int k = 0; k < size; k++){
	//if (mean_val[k] != 125.0) continue;
	for(int i = 0; i < bkg_names.size(); i++){
		if (bkg_names[i] == "Dijet") { continue; }
		//if (bkg_names[i] != "ExpPoly2") continue; 

	TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data()));
	TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names[i].Data()));
	TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names[i].Data()));

		//get histo: 
		spur_ds = (TH1D*) f1->Get(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_smooth_ds = (TH1D*) f2->Get(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_truth_ds = (TH1D*) f3->Get(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		//rename
				spur_ds -> SetName("spur_ds");
                spur_smooth_ds -> SetName("spur_smooth_ds");
				spur_truth_ds -> SetName("spur_truth_ds");

		double width_ds, mean_ds, width_2ds, mean_2ds, width_3ds, mean_3ds;
		double width_error_ds, mean_error_ds, width_2_error_ds, mean_2_error_ds, width_3_error_ds, mean_3_error_ds;
		//For spurious signal
		width_ds = spur_ds->GetRMS();
		mean_ds = spur_ds->GetMean();
		width_2ds = spur_smooth_ds->GetRMS();
		mean_2ds = spur_smooth_ds->GetMean();
		width_3ds = spur_truth_ds->GetRMS();
		mean_3ds = spur_truth_ds->GetMean();

		width_error_ds = spur_ds->GetRMSError();
		mean_error_ds = spur_ds->GetMeanError();
		width_2_error_ds = spur_smooth_ds->GetRMSError();
		mean_2_error_ds = spur_smooth_ds->GetMeanError();
		width_3_error_ds = spur_truth_ds->GetRMSError();
		mean_3_error_ds = spur_truth_ds->GetMeanError();

		RooRealVar mean_ss("mean_ss", "", -1, -10, 10);
		RooRealVar width_ss("width_ss", "", 5, 0, 10);
		RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min_ds, max_ds);
		RooGaussian gauss_SS("gauss_SS","gauss", *spurious_signal,mean_ss,width_ss);
		
		RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,spur_ds);
		//gauss_SS.fitTo(*ss);

		RooRealVar mean_ss_smooth("mean_ss_smooth", "", -1, -10, 10);
		RooRealVar width_ss_smooth("width_ss_smooth", "", 5, 0, 10);
		RooGaussian gauss_SS_smooth("gauss_SS_smooth","gauss", *spurious_signal,mean_ss_smooth,width_ss_smooth);

		RooDataHist* ss_smooth = new RooDataHist("ss_smooth", "Spurious Signal Smooth Data", *spurious_signal,spur_smooth_ds);
		//gauss_SS_smooth.fitTo(*ss_smooth);

		RooRealVar mean_truth("mean_truth", "", -1, -10, 10);
		RooRealVar width_truth("width_truth", "", 5, 0, 10);
		RooGaussian gauss_truth("gauss_truth","gauss", *spurious_signal,mean_truth,width_truth);

		RooDataHist* ss_truth = new RooDataHist("ss_truth", "Spurious Signal Smooth Data", *spurious_signal,spur_truth_ds);
		//gauss_truth.fitTo(*ss_truth);
		
		RooPlot* spurframe = spurious_signal->frame();
		ss->plotOn(spurframe, Name("ss"));
		ss_smooth->plotOn(spurframe, Name("ss_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		ss_truth->plotOn(spurframe, Name("ss_truth"),MarkerColor(kGreen), LineColor(kGreen));

		//gauss_SS.plotOn(spurframe, Name("gauss_SS"));
		//gauss_SS_smooth.plotOn(spurframe, Name("gauss_SS_smooth"), LineColor(kRed));
		//gauss_truth.plotOn(spurframe, Name("gauss_truth"), LineColor(kYellow));

		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s plot (deltaS), %3.0f Mean", bkg_names[i].Data(), mean_val[k]));
		spurframe->GetXaxis()->SetTitle("Delta S");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
        l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
		l->AddEntry("ss", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_ds, width_error_ds, mean_ds, mean_error_ds), "LEP");
        l->AddEntry("ss_smooth", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_2ds, width_2_error_ds, mean_2ds, mean_2_error_ds), "LEP");
		l->AddEntry("ss_truth", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_3ds, width_3_error_ds, mean_3ds, mean_3_error_ds), "LEP");

        //l->AddEntry("gauss_SS", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_ss.getVal(), width_ss.getError(), mean_ss.getVal(), mean_ss.getError()), "L");
    	//l->AddEntry("gauss_SS_smooth", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_ss_smooth.getVal(), width_ss_smooth.getError(), mean_ss_smooth.getVal(), mean_ss_smooth.getError()), "L");
		//l->AddEntry("gauss_truth", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_truth.getVal(), width_truth.getError(),mean_truth.getVal(), mean_truth.getError()), "L");
		l->Draw();

		mean_smooth_ds[k][i] = mean_2ds;
		mean_norm_ds[k][i] = mean_ds;
		mean_tru_ds[k][i] = mean_3ds;

		width_smooth_ds[k][i] = width_2ds;
		width_norm_ds[k][i] = width_ds;
		width_tru_ds[k][i] = width_3ds;

		mean_smoothErr_ds[k][i] = mean_2_error_ds;
		mean_normErr_ds[k][i] = mean_error_ds;
		mean_truErr_ds[k][i] = mean_3_error_ds;

		width_smoothErr_ds[k][i] = width_2_error_ds;
		width_normErr_ds[k][i] = width_error_ds;
		width_truErr_ds[k][i] = width_3_error_ds;

		system(Form("mkdir -vp distributions/%s", compare.c_str()));
		c2 -> SaveAs(Form("distributions/%s/%s_dS_%3.0f.png", compare.c_str(), bkg_names[i].Data(), mean_val[k]));
	}
}
// ------ S/dS ------- //
for(int k = 0; k < size; k++){
	//if (mean_val[k] != 125.0) continue;
	for(int i = 0; i < bkg_names.size(); i++){
		if (bkg_names[i] == "Dijet") { continue; }
		//if (bkg_names[i] != "ExpPoly2") continue; 

	TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data()));
	TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names[i].Data()));
	TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names[i].Data()));

		//get histo: 
		spur_sds = (TH1D*) f1->Get(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_smooth_sds = (TH1D*) f2->Get(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		spur_truth_sds = (TH1D*) f3->Get(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		//rename
				spur_sds -> SetName("spur_sds");
                spur_smooth_sds -> SetName("spur_smooth_sds");
				spur_truth_sds -> SetName("spur_truth_sds");

		double width_sds, mean_sds, width_2sds, mean_2sds, width_3sds, mean_3sds;
		double width_error_sds, mean_error_sds, width_2_error_sds, mean_2_error_sds, width_3_error_sds, mean_3_error_sds;
		//For spurious signal
		width_sds = spur_sds->GetRMS();
		mean_sds = spur_sds->GetMean();
		width_2sds = spur_smooth_sds->GetRMS();
		mean_2sds = spur_smooth_sds->GetMean();
		width_3sds = spur_truth_sds->GetRMS();
		mean_3sds = spur_truth_sds->GetMean();

		width_error_sds = spur_sds->GetRMSError();
		mean_error_sds = spur_sds->GetMeanError();
		width_2_error_sds = spur_smooth_sds->GetRMSError();
		mean_2_error_sds = spur_smooth_sds->GetMeanError();
		width_3_error_sds = spur_truth_sds->GetRMSError();
		mean_3_error_sds = spur_truth_sds->GetMeanError();

		RooRealVar mean_ss("mean_ss", "", -1, -10, 10);
		RooRealVar width_ss("width_ss", "", 5, 0, 10);
		RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min_sds, max_sds);
		RooGaussian gauss_SS("gauss_SS","gauss", *spurious_signal,mean_ss,width_ss);
		
		RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,spur_sds);
		//gauss_SS.fitTo(*ss);

		RooRealVar mean_ss_smooth("mean_ss_smooth", "", -1, -10, 10);
		RooRealVar width_ss_smooth("width_ss_smooth", "", 5, 0, 10);
		RooGaussian gauss_SS_smooth("gauss_SS_smooth","gauss", *spurious_signal,mean_ss_smooth,width_ss_smooth);

		RooDataHist* ss_smooth = new RooDataHist("ss_smooth", "Spurious Signal Smooth Data", *spurious_signal,spur_smooth_sds);
		//gauss_SS_smooth.fitTo(*ss_smooth);

		RooRealVar mean_truth("mean_truth", "", -1, -10, 10);
		RooRealVar width_truth("width_truth", "", 5, 0, 10);
		RooGaussian gauss_truth("gauss_truth","gauss", *spurious_signal,mean_truth,width_truth);

		RooDataHist* ss_truth = new RooDataHist("ss_truth", "Spurious Signal Smooth Data", *spurious_signal,spur_truth_sds);
		//gauss_truth.fitTo(*ss_truth);
		
		RooPlot* spurframe = spurious_signal->frame();
		ss->plotOn(spurframe, Name("ss"));
		ss_smooth->plotOn(spurframe, Name("ss_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		ss_truth->plotOn(spurframe, Name("ss_truth"),MarkerColor(kGreen), LineColor(kGreen));

		//gauss_SS.plotOn(spurframe, Name("gauss_SS"));
		//gauss_SS_smooth.plotOn(spurframe, Name("gauss_SS_smooth"), LineColor(kRed));
		//gauss_truth.plotOn(spurframe, Name("gauss_truth"), LineColor(kYellow));

		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s plot (S/deltaS), %3.0f Mean", bkg_names[i].Data(), mean_val[k]));
		spurframe->GetXaxis()->SetTitle("Error (S/dS)");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
        l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
		l->AddEntry("ss", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_sds, width_error_sds, mean_sds, mean_error_sds), "LEP");
        l->AddEntry("ss_smooth", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_2sds, width_2_error_sds, mean_2sds, mean_2_error_sds), "LEP");
		l->AddEntry("ss_truth", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_3sds, width_3_error_sds, mean_3sds, mean_3_error_sds), "LEP");
        
		//l->AddEntry("gauss_SS", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_ss.getVal(), width_ss.getError(), mean_ss.getVal(), mean_ss.getError()), "L");
    	//l->AddEntry("gauss_SS_smooth", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_ss_smooth.getVal(), width_ss_smooth.getError(), mean_ss_smooth.getVal(), mean_ss_smooth.getError()), "L");
		//l->AddEntry("gauss_truth", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_truth.getVal(), width_truth.getError(),mean_truth.getVal(), mean_truth.getError()), "L");
		l->Draw();

		/*mean_smooth_sds[k][i] = mean_ss_smooth.getVal();
		mean_norm_sds[k][i] = mean_ss.getVal();
		mean_tru_sds[k][i] = mean_truth.getVal();

		width_smooth_sds[k][i] = width_ss.getVal();
		width_norm_sds[k][i] = width_ss_smooth.getVal();
		width_tru_sds[k][i] = width_truth.getVal();

		mean_smoothErr_sds[k][i] = mean_ss_smooth.getError();
		mean_normErr_sds[k][i] = mean_ss.getError();
		mean_truErr_sds[k][i] = mean_truth.getError();

		width_smoothErr_sds[k][i] = width_ss_smooth.getError();
		width_normErr_sds[k][i] = width_ss.getError();
		width_truErr_sds[k][i] = width_truth.getError();*/

		mean_smooth_sds[k][i] = mean_2sds;
		mean_norm_sds[k][i] = mean_sds;
		mean_tru_sds[k][i] = mean_3sds;

		width_smooth_sds[k][i] = width_2sds;
		width_norm_sds[k][i] = width_sds;
		width_tru_sds[k][i] = width_3sds;

		mean_smoothErr_sds[k][i] = mean_2_error_sds;
		mean_normErr_sds[k][i] = mean_error_sds;
		mean_truErr_sds[k][i] = mean_3_error_sds;

		width_smoothErr_sds[k][i] = width_2_error_sds;
		width_normErr_sds[k][i] = width_error_sds;
		width_truErr_sds[k][i] = width_3_error_sds;

		system(Form("mkdir -vp distributions/%s", compare.c_str()));
		c2 -> SaveAs(Form("distributions/%s/%s_SdS_%3.0f.png", compare.c_str(), bkg_names[i].Data(), mean_val[k]));
	}
}
	
/*for(int k = 0; k > size; k++){
	if (mean_val[k] != 125.0) continue;
	for(int i = 0; i < bkg_names.size(); i++){
		//if (bkg_names[i] == "Dijet") { continue; }
		//if (bkg_names[i] != "ExpPoly2") continue;
		TFile* f1 = TFile::Open(Form("norm_rootFiles/norm_all_%s.root", bkg_names[i].Data()));

	//TFile* f2 = TFile::Open(Form("%3.0f_smooth.root", mean_val[k]));
	TFile* f2 = TFile::Open(Form("smooth_rootFiles/smooth_all_%s.root", bkg_names[i].Data()));

		//if (bkg_names[i] == "Dijet") { continue; }
		//get histo:
		chiSq = (TH1D*) f1->Get(Form("chiSq_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		chiSq_smooth = (TH1D*) f2->Get(Form("chiSq_%s_%3.0f",bkg_names[i].Data(), mean_val[k]));
		//rename
		chiSq -> SetName("chiSq");
        chiSq_smooth -> SetName("chiSq_smooth");

		double width_c2;
		double mean_c2;
		double width_c2_smooth;
		double mean_c2_smooth;
		double width_c2_error;
		double mean_c2_error;
		double width_c2_smooth_error;
		double mean_c2_smooth_error;

		width_c2 = chiSq->GetRMS();
		mean_c2 = chiSq->GetMean();
		width_c2_smooth = chiSq_smooth->GetRMS();
		mean_c2_smooth = chiSq_smooth->GetMean();

		width_c2_error = chiSq->GetRMS();
		mean_c2_error = chiSq->GetMean();
		width_c2_smooth_error = chiSq_smooth->GetRMS();
		mean_c2_smooth_error = chiSq_smooth->GetMean();

		//regular vars
		//RooRealVar mean_chi("mean_chi", "",  5, -1, 3);
		//RooRealVar width_chi("width_chi", "", 5, -1, 3);
		//smooth vars
		//RooRealVar mean_chi_smooth("mean_chi_smooth", "", 5, -1, 3);
		//RooRealVar width_chi_smooth("width_chi_smooth", "", 5, -1, 3);
		//x axis
		RooRealVar* chi_squared = new RooRealVar("chi_squared", "", -1, 2);

		//gaussians
		//RooGaussian gauss_chi2("gauss_chi2","gauss", *chi_squared,mean_chi,width_chi);
		//RooGaussian gauss_chi2_smooth("gauss_chi2_smooth","gauss", *chi_squared,mean_chi_smooth,width_chi_smooth);

		//roo histos and root fits
		RooDataHist* chi2 = new RooDataHist("chi2", "Chi-Squared", *chi_squared,chiSq);
		//gauss_chi2.fitTo(*chi2);

		RooDataHist* chi2_smooth = new RooDataHist("chi2_smooth", "Chi-Squared Smooth Data", *chi_squared, chiSq_smooth);
		//gauss_chi2_smooth.fitTo(*chi2_smooth);

		//plot stuff
		RooPlot* chiframe = chi_squared->frame();
		chi2->plotOn(chiframe, Name("chi2"));
		chi2_smooth->plotOn(chiframe, Name("chi2_smooth"), MarkerColor(kOrange), LineColor(kOrange));
		//gauss_chi2.plotOn(chiframe, Name("gauss_chi2"));
		//gauss_chi2_smooth.plotOn(chiframe, Name("gauss_chi2_smooth"),LineColor(kRed));
		
		//create canvas - legend - and save
		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		chiframe->SetTitle(Form("%s plot & Mean Val: %3.0f", bkg_names[i].Data(), mean_val[k]));
		chiframe->GetXaxis()->SetTitle("Chi-Squared");
		chiframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		chiframe->Draw();
 
		auto l = new TLegend(0.6,0.6,0.99,0.99);
   		l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.04);
		l->AddEntry("chi2", Form("Data Normal, Width: %.2f, Mean: %.2f", width_c2, mean_c2), "LEP");
		l->AddEntry("chi2_smooth", Form("Data Smooth, Width: %.2f, Mean: %.2f", width_c2_smooth, mean_c2_smooth), "LEP");
		//l->AddEntry("gauss_chi2", Form("Fit Normal, Width: %.2f, Mean: %.2f", width_chi.getVal(), mean_chi.getVal()), "L");
        //l->AddEntry("gauss_chi2_smooth", Form("Fit Smooth, Width: %.2f, Mean: %.2f", width_chi_smooth.getVal(), mean_chi_smooth.getVal()), "L");
		l->Draw();

		bias2[k][i] = abs((mean_c2 - mean_c2_smooth)/mean_c2);
		impact2[k][i] = abs(width_c2_smooth/width_c2);
		mean_smooth2[k][i] = mean_c2_smooth;
		mean_norm2[k][i] = mean_c2;
		width_smooth2[k][i] = width_c2_smooth;
		width_norm2[k][i] = width_c2;

		//system(Form("mkdir -vp distributions/%s", compare.c_str()));
		c2 -> SaveAs(Form("distributions/%s/%s_chi2_%3.0f.png",compare.c_str(), bkg_names[i].Data(), mean_val[k]));
        }
	}*/

/*
		//plot three gaussians together with mean val at 121, 125, and 129:
		TH1D* spurA;
		TH1D* spurB;
		TH1D* spurC;
		//TH1D* chiSq;

        TH1D* spurD_smooth;
		TH1D* spurE_smooth;
		TH1D* spurF_smooth;
        //TH1D* chiSq_smooth;

		for(int i = 0; i < bkg_names.size(); i++){
		//open root file and define it
		TFile* f1 = TFile::Open(Form("norm_rootFiles/norm_all_%s.root", bkg_names[i].Data()));
		TFile* f2 = TFile::Open(Form("smooth_rootFiles/smooth_all_%s.root", bkg_names[i].Data()));

		//get contents (root histograms 121, 125, 129 GeV mean) histos from root files

		//get histo: 
		spurA = (TH1D*) f1->Get(Form("spur_%s_121",bkg_names[i].Data()));
		spurB = (TH1D*) f1->Get(Form("spur_%s_125",bkg_names[i].Data()));
		spurC = (TH1D*) f1->Get(Form("spur_%s_129",bkg_names[i].Data()));
		spurD_smooth = (TH1D*) f2->Get(Form("spur_%s_121",bkg_names[i].Data()));
		spurE_smooth = (TH1D*) f2->Get(Form("spur_%s_125",bkg_names[i].Data()));
		spurF_smooth = (TH1D*) f2->Get(Form("spur_%s_129",bkg_names[i].Data()));
		//rename
                spurA -> SetName("spurA");
				spurB -> SetName("spurB");
				spurC -> SetName("spurC");
                spurD_smooth -> SetName("spurD_smooth");
				spurE_smooth -> SetName("spurE_smooth");
				spurF_smooth -> SetName("spurF_smooth");

		RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", -15, 15);
		
		RooRealVar meanA_ss("meanA_ss", "", -1, -10, 10);
		RooRealVar widthA_ss("widthA_ss", "", 5, 0, 10);
		RooGaussian gaussA_SS("gaussA_SS","gauss", *spurious_signal,meanA_ss,widthA_ss);
		RooRealVar meanB_ss("meanB_ss", "", -1, -10, 10);
		RooRealVar widthB_ss("widthB_ss", "", 5, 0, 10);
		RooGaussian gaussB_SS("gaussB_SS","gauss", *spurious_signal,meanB_ss,widthB_ss);
		RooRealVar meanC_ss("meanC_ss", "", -1, -10, 10);
		RooRealVar widthC_ss("widthC_ss", "", 5, 0, 10);
		RooGaussian gaussC_SS("gaussC_SS","gauss", *spurious_signal,meanC_ss,widthC_ss);
		
		RooDataHist* ssA = new RooDataHist("ssA", "Spurious Signal Data", *spurious_signal,spurA);
		gaussA_SS.fitTo(*ssA);
		RooDataHist* ssB = new RooDataHist("ssB", "Spurious Signal Data", *spurious_signal,spurB);
		gaussB_SS.fitTo(*ssB);
		RooDataHist* ssC = new RooDataHist("ssC", "Spurious Signal Data", *spurious_signal,spurC);
		gaussC_SS.fitTo(*ssC); //the problem was here for 3G plot (ssA instead of ssC)

		RooRealVar meanD_ss_smooth("meanD_ss_smooth", "", -1, -10, 10);
		RooRealVar widthD_ss_smooth("widthD_ss_smooth", "", 5, 0, 10);
		RooGaussian gaussD_SS_smooth("gaussD_SS_smooth","gauss", *spurious_signal,meanD_ss_smooth,widthD_ss_smooth);
		RooRealVar meanE_ss_smooth("meanE_ss_smooth", "", -1, -10, 10);
		RooRealVar widthE_ss_smooth("widthE_ss_smooth", "", 5, 0, 10);
		RooGaussian gaussE_SS_smooth("gaussE_SS_smooth","gauss", *spurious_signal,meanE_ss_smooth,widthE_ss_smooth);
		RooRealVar meanF_ss_smooth("meanF_ss_smooth", "", -1, -10, 10);
		RooRealVar widthF_ss_smooth("widthF_ss_smooth", "", 5, 0, 10);
		RooGaussian gaussF_SS_smooth("gaussF_SS_smooth","gauss", *spurious_signal,meanF_ss_smooth,widthF_ss_smooth);
		
		RooDataHist* ssD_smooth = new RooDataHist("ssD_smooth", "Spurious Signal Smooth Data", *spurious_signal,spurD_smooth);
		gaussD_SS_smooth.fitTo(*ssD_smooth);
		RooDataHist* ssE_smooth = new RooDataHist("ssE_smooth", "Spurious Signal Smooth Data", *spurious_signal,spurE_smooth);
		gaussE_SS_smooth.fitTo(*ssE_smooth);
		RooDataHist* ssF_smooth = new RooDataHist("ssF_smooth", "Spurious Signal Smooth Data", *spurious_signal,spurF_smooth);
		gaussF_SS_smooth.fitTo(*ssF_smooth);

		RooPlot* spurframe1 = spurious_signal->frame();
		RooPlot* spurframe2 = spurious_signal->frame();
		RooPlot* spurframe3 = spurious_signal->frame();
		
		
		/*ssA->plotOn(spurframe1, Name("ssA"));
		ssB->plotOn(spurframe2, Name("ssB"));
		ssC->plotOn(spurframe3, Name("ssC"));

		ssD_smooth->plotOn(spurframe1, Name("ssD_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		ssE_smooth->plotOn(spurframe2, Name("ssE_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		ssF_smooth->plotOn(spurframe3, Name("ssF_smooth"),MarkerColor(kOrange), LineColor(kOrange));*/
		
		/*gaussA_SS.plotOn(spurframe1, Name("gaussA_SS"), LineColor(kBlack));
		gaussB_SS.plotOn(spurframe1, Name("gaussB_SS"), LineColor(kYellow));
		gaussC_SS.plotOn(spurframe1, Name("gaussC_SS"), LineColor(kGreen));
		gaussD_SS_smooth.plotOn(spurframe1, Name("gaussD_SS_smooth"), LineColor(kRed));
		gaussE_SS_smooth.plotOn(spurframe1, Name("gaussE_SS_smooth"), LineColor(kBlue));
		gaussF_SS_smooth.plotOn(spurframe1, Name("gaussF_SS_smooth"), LineColor(kOrange));

		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe1->SetTitle(Form("%s plot of 3 mean values", bkg_names[i].Data()));
		spurframe1->GetXaxis()->SetTitle("Spurious Signal");
		spurframe1->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe1->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
                l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
        l->AddEntry("gaussA_SS", Form("Fit Normal (121), Width: %.2f, Mean: %.2f", widthA_ss.getVal(),meanA_ss.getVal()), "L");
		l->AddEntry("gaussB_SS", Form("Fit Normal (125), Width: %.2f, Mean: %.2f", widthB_ss.getVal(),meanB_ss.getVal()), "L");
		l->AddEntry("gaussC_SS", Form("Fit Normal (129), Width: %.2f, Mean: %.2f", widthC_ss.getVal(),meanC_ss.getVal()), "L");

    	l->AddEntry("gaussD_SS_smooth", Form("Fit Smooth (121), Width: %.2f, Mean: %.2f",widthD_ss_smooth.getVal(),meanD_ss_smooth.getVal()), "L");
		l->AddEntry("gaussE_SS_smooth", Form("Fit Smooth (125), Width: %.2f, Mean: %.2f",widthE_ss_smooth.getVal(),meanE_ss_smooth.getVal()), "L");
		l->AddEntry("gaussF_SS_smooth", Form("Fit Smooth (129), Width: %.2f, Mean: %.2f",widthF_ss_smooth.getVal(),meanF_ss_smooth.getVal()), "L");
		
		l->Draw();

		system(Form("mkdir -vp %s", compare.c_str()));
		c2 -> SaveAs(Form("distributions/%s/%s_SS_3G.png", compare.c_str(), bkg_names[i].Data()));
	}*/

	//----------MAX PLOTTING---------//

	TH1D* error;
	TH1D* total_error;
	TH1D* error_smooth;
	TH1D* error_truth;
	TH1D* total_error_smooth;
	TH1D* total_error_truth;

	for(int i = 0; i < bkg_names.size(); i++){

	if(bkg_names[i] == "Dijet") continue;
	//open TFILES
	TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data())); 
	TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names[i].Data()));
	TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names[i].Data()));
		//get histo: 
		spur = (TH1D*) f1->Get(Form("maxSpur_%s", bkg_names[i].Data()));
		spur_smooth = (TH1D*) f2->Get(Form("maxSpur_%s", bkg_names[i].Data()));
		spur_truth = (TH1D*) f3->Get(Form("maxSpur_%s", bkg_names[i].Data()));
		//rename
                spur -> SetName("spur");
                spur_smooth -> SetName("spur_smooth");
				spur_truth -> SetName("spur_truth");

		double width_ss;
		double mean_ss;
		double width_ss_smooth;
		double mean_ss_smooth;
		double width_truth;
		double mean_truth;

		double width_ss_error;
		double mean_ss_error;
		double width_ss_smooth_error;
		double mean_ss_smooth_error;
		double width_truth_error;
		double mean_truth_error;

		width_ss = spur->GetRMS();
		mean_ss = spur->GetMean();
		width_ss_smooth = spur_smooth->GetRMS();
		mean_ss_smooth = spur_smooth->GetMean();
		width_truth = spur_truth->GetRMS();
		mean_truth = spur_truth->GetMean();

		width_ss_error = spur->GetRMSError();
		mean_ss_error = spur->GetMeanError();
		width_ss_smooth_error = spur_smooth->GetRMSError();
		mean_ss_smooth_error = spur_smooth->GetMeanError();
		width_truth_error = spur_truth->GetRMSError();
		mean_truth_error = spur_truth->GetMeanError();

		RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", -5, 30);
		RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,spur);
		RooDataHist* ss_smooth = new RooDataHist("ss_smooth", "Spurious Signal Smooth Data", *spurious_signal,spur_smooth);
		RooDataHist* ss_truth = new RooDataHist("ss_truth", "Spurious Signal Smooth Data", *spurious_signal,spur_truth);
		
		RooPlot* spurframe = spurious_signal->frame();
		ss->plotOn(spurframe, Name("ss"));
		ss_smooth->plotOn(spurframe, Name("ss_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		ss_truth->plotOn(spurframe, Name("ss_truth"),MarkerColor(kGreen), LineColor(kGreen));

		TCanvas *c2 = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		spurframe->GetXaxis()->SetTitle("Maximum Spurious Signal");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
        l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
		l->AddEntry("ss", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_ss, width_ss_error, mean_ss, mean_ss_error), "LEP");
        l->AddEntry("ss_smooth", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_ss_smooth, width_ss_smooth_error, mean_ss_smooth, mean_ss_smooth_error), "LEP");
		l->AddEntry("ss_truth", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_truth, width_truth_error, mean_truth, mean_truth_error), "LEP");
		l->Draw();

		bias3[i] = abs((mean_ss - mean_ss_smooth)/mean_ss);
		impact3[i] = abs(width_ss_smooth/width_ss);
		mean_smooth3[i] = mean_ss_smooth;
		mean_norm3[i] = mean_ss;
		mean_truth3[i] = mean_truth;

		width_smooth3[i] = width_ss_smooth;
		width_norm3[i] = width_ss;
		width_truth3[i] = width_truth;

		mean_smooth3Err[i] = mean_ss_smooth_error;
		mean_norm3Err[i] = mean_ss_error;
		mean_truth3Err[i] = mean_truth_error;

		width_smooth3Err[i] = width_ss_smooth_error;
		width_norm3Err[i] = width_ss_error;
		width_truth3Err[i] = width_truth_error;

		//system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots/%s", compare.c_str()));
		c2 -> SaveAs(Form("max_plots/%s/%s_SS.png", compare.c_str(), bkg_names[i].Data()));
	}

	//Delta S
	for(int i = 0; i < bkg_names.size(); i++){
		if(bkg_names[i] == "Dijet") continue;
		//open TFILES
		TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data())); 
		TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names[i].Data()));
		TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names[i].Data()));
		//get histo:
		error = (TH1D*) f1->Get(Form("error_%s", bkg_names[i].Data()));
		error_smooth = (TH1D*) f2->Get(Form("error_%s", bkg_names[i].Data()));
		error_truth = (TH1D*) f3->Get(Form("error_%s", bkg_names[i].Data()));
		//rename
		error -> SetName("error");
        error_smooth -> SetName("error_smooth");
		error_truth -> SetName("error_truth");

		double width_ds;
		double mean_ds;
		double width_ds_smooth;
		double mean_ds_smooth;
		double width_ds_truth;
		double mean_ds_truth;

		double width_ds_error;
		double mean_ds_error;
		double width_ds_smooth_error;
		double mean_ds_smooth_error;
		double width_ds_truth_error;
		double mean_ds_truth_error;

		width_ds = error->GetRMS();
		mean_ds = error->GetMean();
		width_ds_smooth = error_smooth->GetRMS();
		mean_ds_smooth = error_smooth->GetMean();
		width_ds_truth = error_truth->GetRMS();
		mean_ds_truth = error_truth->GetMean();

		width_ds_error = error->GetRMSError();
		mean_ds_error = error->GetMeanError();
		width_ds_smooth_error = error_smooth->GetRMSError();
		mean_ds_smooth_error = error_smooth->GetMeanError();
		width_ds_truth_error = error_truth->GetRMSError();
		mean_ds_truth_error = error_truth->GetMeanError();

		//x axis
		RooRealVar* error_x = new RooRealVar("error_x", "", 10, 16);

		//roo histos and root fits
		RooDataHist* error_data = new RooDataHist("error_data", "Error Data", *error_x, error);

		RooDataHist* error_data_smooth = new RooDataHist("error_data_smooth", "Error Smooth Data", *error_x, error_smooth);

		RooDataHist* error_data_truth = new RooDataHist("error_data_truth", "Error Truth Data", *error_x, error_truth);
		//plot stuff
		RooPlot* errframe = error_x->frame();
		error_data->plotOn(errframe, Name("error_data"));
		error_data_smooth->plotOn(errframe, Name("error_data_smooth"), MarkerColor(kOrange), LineColor(kOrange));
		error_data_truth->plotOn(errframe, Name("error_data_truth"), MarkerColor(kGreen), LineColor(kGreen));

		//create canvas - legend - and save
		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		errframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		errframe->GetXaxis()->SetTitle("Maximum Delta S");
		errframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		errframe->Draw();
 
		auto l = new TLegend(0.6,0.6,0.15,0.9);
   		l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
		l->AddEntry("error_data", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_ds, width_ds_error, mean_ds, mean_ds_error), "LEP");
		l->AddEntry("error_data_smooth", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_ds_smooth, width_ds_smooth_error, mean_ds_smooth, mean_ds_smooth_error), "LEP");
		l->AddEntry("error_data_truth", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_ds_truth, width_ds_truth_error , mean_ds_truth, mean_ds_truth_error), "LEP");
		l->Draw();

		//system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots/%s", compare.c_str()));
		c2 -> SaveAs(Form("max_plots/%s/%s_error.png",compare.c_str(), bkg_names[i].Data()));
        }


		//total error S/DS
	for(int i = 0; i < bkg_names.size(); i++){
		if(bkg_names[i] == "Dijet") continue;
		//open TFILES
		TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names[i].Data())); 
		TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names[i].Data()));
		TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names[i].Data()));
		//get histo: 
		total_error = (TH1D*) f1->Get(Form("total_error_%s", bkg_names[i].Data()));
		total_error_smooth = (TH1D*) f2->Get(Form("total_error_%s", bkg_names[i].Data()));
		total_error_truth = (TH1D*) f3->Get(Form("total_error_%s", bkg_names[i].Data()));
		//rename
                total_error -> SetName("total_error");
                total_error_smooth -> SetName("total_error_smooth");
				total_error_truth -> SetName("total_error_truth");

		double width_err;
		double mean_err;
		double width_err_smooth;
		double mean_err_smooth;
		double width_err_truth;
		double mean_err_truth;

		double width_err_error;
		double mean_err_error;
		double width_err_smooth_error;
		double mean_err_smooth_error;
		double width_err_truth_error;
		double mean_err_truth_error;

		width_err = total_error->GetRMS();
		mean_err = total_error->GetMean();
		width_err_smooth = total_error_smooth->GetRMS();
		mean_err_smooth = total_error_smooth->GetMean();
		width_err_truth = total_error_truth->GetRMS();
		mean_err_truth = total_error_truth->GetMean();

		width_err_error = total_error->GetRMSError();
		mean_err_error = total_error->GetMeanError();
		width_err_smooth_error = total_error_smooth->GetRMSError();
		mean_err_smooth_error = total_error_smooth->GetMeanError();
		width_err_truth_error = total_error_truth->GetRMSError();
		mean_err_truth_error = total_error_truth->GetMeanError();

		RooRealVar* error_x = new RooRealVar("error_x", "", -.4, 1);
		
		RooDataHist* err_tot = new RooDataHist("err_tot", "S/DS Data", *error_x,total_error);

		RooDataHist* err_tot_smooth = new RooDataHist("err_tot_smooth", "S/DS Smooth Data", *error_x,total_error_smooth);
		RooDataHist* err_tot_truth = new RooDataHist("err_tot_truth", "S/DS Truth Data", *error_x,total_error_truth);
		
		RooPlot* spurframe = error_x->frame();
		err_tot->plotOn(spurframe, Name("err_tot"));
		err_tot_smooth->plotOn(spurframe, Name("err_tot_smooth"),MarkerColor(kOrange), LineColor(kOrange));
		err_tot_truth->plotOn(spurframe, Name("err_tot_truth"),MarkerColor(kGreen), LineColor(kGreen));


		TCanvas *c2 = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		spurframe->GetXaxis()->SetTitle("Maximum S/DS");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
        l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.03);
		l->AddEntry("err_tot", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1.c_str(), width_err, width_err_error, mean_err, mean_err_error), "LEP");
        l->AddEntry("err_tot_smooth", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2.c_str(), width_err_smooth, width_err_smooth_error, mean_err_smooth, mean_err_smooth_error), "LEP");
		l->AddEntry("err_tot_truth", Form("Data %s Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3.c_str(), width_err_truth, width_err_truth_error, mean_err_truth, mean_err_truth_error), "LEP");
        l->Draw();

		bias4[i] = abs((mean_err - mean_err_smooth)/mean_err);
		impact4[i] = abs(width_err_smooth/width_err);
		mean_smooth4[i] = mean_err_smooth;
		mean_norm4[i] = mean_err;
		mean_truth4[i] = mean_err_truth;
		width_smooth4[i] = width_err_smooth;
		width_norm4[i] = width_err;
		width_truth4[i] = width_err_truth;

		mean_smooth4Err[i] = mean_err_smooth_error;
		mean_norm4Err[i] = mean_err_error;
		mean_truth4Err[i] = mean_err_truth_error;
		width_smooth4Err[i] = width_err_smooth_error;
		width_norm4Err[i] = width_err_error;
		width_truth4Err[i] = width_err_truth_error;

		//system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots/%s", compare.c_str()));
		c2 -> SaveAs(Form("max_plots/%s/%s_total_err.png", compare.c_str(), bkg_names[i].Data()));
	}


	//----PRINT OUT TABLES----//

	cout << "Spurious Signal Fit: " << endl;
	for(int k = 0; k < size; k++){
		if (mean_val[k] != 125.0) continue;

		cout << "Mean Value: " << mean_val[k] << endl;

		cout << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3.c_str()) << left << setw(20) << Form("Mean %s", data2.c_str()) << left << setw(20) << Form("Mean %s", data1.c_str()) << left << setw(20) << Form("Width %s", data3.c_str()) << left << setw(20) << Form("Width %s", data2.c_str()) << left << setw(15) << Form("Width %s", data1.c_str()) << endl;
	    cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

		//cout << "Mean value of " << mean_val[k] << endl;
		for(int i = 0; i < bkg_names.size(); i++){
			if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(20) <<  bkg_names[i] << left << setw(20) << Form("%.4f ± %.4f", mean_tru[k][i], mean_truErr[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_smooth[k][i], mean_smoothErr[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_norm[k][i], mean_normErr[k][i]) << left << setw(20) << left <<Form("%.4f ± %.4f", width_tru[k][i], width_truErr[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_smooth[k][i], width_smoothErr[k][i]) << left << setw(15) << Form("%.4f ± %.4f", width_norm[k][i], width_normErr[k][i]) << endl;
	    	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	//------- Delta S ------
	cout << "Delta S Fit: " << endl;
	for(int k = 0; k < size; k++){
		if (mean_val[k] != 125.0) continue;

		cout << "Mean Value: " << mean_val[k] << endl;

		cout << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3.c_str()) << left << setw(20) << Form("Mean %s", data2.c_str()) << left << setw(20) << Form("Mean %s", data1.c_str()) << left << setw(20) << Form("Width %s", data3.c_str()) << left << setw(20) << Form("Width %s", data2.c_str()) << left << setw(15) << Form("Width %s", data1.c_str()) << endl;
	    cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

		//cout << "Mean value of " << mean_val[k] << endl;
		for(int i = 0; i < bkg_names.size(); i++){
			if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(20) <<  bkg_names[i] << left << setw(20) << Form("%.4f ± %.4f", mean_tru_ds[k][i], mean_truErr_ds[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_smooth_ds[k][i], mean_smoothErr_ds[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_norm_ds[k][i], mean_normErr_ds[k][i]) << left << setw(20) << left <<Form("%.4f ± %.4f", width_tru_ds[k][i], width_truErr_ds[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_smooth_ds[k][i], width_smoothErr_ds[k][i]) << left << setw(15) << Form("%.4f ± %.4f", width_norm_ds[k][i], width_normErr_ds[k][i]) << endl;
	    	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
	// --------- S / dS ------ 
	cout << "S / Delta S Fit: " << endl;
	for(int k = 0; k < size; k++){
		if (mean_val[k] != 125.0) continue;

		cout << "Mean Value: " << mean_val[k] << endl;

		cout << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3.c_str()) << left << setw(20) << Form("Mean %s", data2.c_str()) << left << setw(20) << Form("Mean %s", data1.c_str()) << left << setw(20) << Form("Width %s", data3.c_str()) << left << setw(20) << Form("Width %s", data2.c_str()) << left << setw(15) << Form("Width %s", data1.c_str()) << endl;
	    cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

		//cout << "Mean value of " << mean_val[k] << endl;
		for(int i = 0; i < bkg_names.size(); i++){
			if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(20) <<  bkg_names[i] << left << setw(20) << Form("%.4f ± %.4f", mean_tru_sds[k][i], mean_truErr_sds[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_smooth_sds[k][i], mean_smoothErr_sds[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_norm_sds[k][i], mean_normErr_sds[k][i]) << left << setw(20) << left <<Form("%.4f ± %.4f", width_tru_sds[k][i], width_truErr_sds[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_smooth_sds[k][i], width_smoothErr_sds[k][i]) << left << setw(15) << Form("%.4f ± %.4f", width_norm_sds[k][i], width_normErr_sds[k][i]) << endl;
	    	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}


	/*cout << "Bias & Impact for Chi Squared Fit: " << endl;
	for(int k = 0; k < size; k++){
		if (mean_val[k] != 125.0) continue;

		cout << "Mean Value: " << mean_val[k] << endl;

		cout << left << setw(15) << "" << left << setw(15) << "Bias" << left << setw(15) << "Impact" << left << setw(15) << "Mean Smooth" << left << setw(15) << "Mean Norm" << left << setw(15) << "Width Smooth" << left << setw(15) << "Width Norm" << endl;
	    cout << "-------------------------------------------------------------------------------------------------------" << endl;

		//cout << "Mean value of " << mean_val[k] << endl;
		for(int i = 0; i < bkg_names.size(); i++){
			if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(15) <<  bkg_names[i] << left << setw(15) << bias2[k][i] << left << setw(15) << impact2[k][i] << left << setw(15) << mean_smooth2[k][i] << left << setw(15) << mean_norm2[k][i] << left << setw(15) << width_smooth2[k][i] << left << setw(15) << width_norm2[k][i] << endl;
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
		}
	}*/

	cout << "Max Spurious Signal Fit: " << endl;
	    cout << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3.c_str()) << left << setw(20) << Form("Mean %s", data2.c_str()) << left << setw(20) << Form("Mean %s", data1.c_str()) << left << setw(20) << Form("Width %s", data3.c_str()) << left << setw(20) << Form("Width %s", data2.c_str()) << left << setw(15) << Form("Width %s", data1.c_str()) << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

		for(int i = 0; i < bkg_names.size(); i++){
			if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(20) <<  bkg_names[i] << left << setw(20) << Form("%.4f ± %.4f", mean_truth3[i], mean_truth3Err[i]) << left << setw(20) << Form("%.4f ± %.4f", mean_smooth3[i], mean_smooth3Err[i]) << left << setw(20) << Form("%.4f ± %.4f", mean_norm3[i], mean_norm3Err[i]) << left << setw(20) << Form("%.4f ± %.4f", width_truth3[i], width_truth3Err[i]) << left << setw(20) << Form("%.4f ± %.4f", width_smooth3[i], width_smooth3Err[i]) << left << setw(20) << Form("%.4f ± %.4f", width_norm3[i], width_norm3Err[i]) << endl;
			cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}

	cout << "Max Spurious Signal Fit over Delta S: " << endl;
	    cout << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3.c_str()) << left << setw(20) << Form("Mean %s", data2.c_str()) << left << setw(20) << Form("Mean %s", data1.c_str()) << left << setw(20) << Form("Width %s", data3.c_str()) << left << setw(20) << Form("Width %s", data2.c_str()) << left << setw(15) << Form("Width %s", data1.c_str()) << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

		//cout << "Mean value of " << mean_val[k] << endl;
		for(int i = 0; i < bkg_names.size(); i++){
			if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(20) <<  bkg_names[i] << left << setw(20) << Form("%.4f ± %.4f", mean_truth4[i], mean_truth4Err[i])  << left << setw(20) << Form("%.4f ± %.4f", mean_smooth4[i], mean_smooth4Err[i]) << left << setw(20) << Form("%.4f ± %.4f", mean_norm4[i], mean_norm4Err[i]) << left << setw(20) << Form("%.4f ± %.4f", width_truth4[i], width_truth4Err[i]) << left << setw(20) << Form("%.4f ± %.4f", width_smooth4[i], width_smooth4Err[i]) << left << setw(20) << Form("%.4f ± %.4f", width_norm4[i], width_norm4Err[i]) << endl;
			cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}

}
