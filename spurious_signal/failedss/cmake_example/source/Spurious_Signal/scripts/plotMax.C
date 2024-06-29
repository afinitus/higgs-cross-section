#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace RooFit;
using namespace std;

void plotMax(){
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
	
	//directory to save plots into:
	//string compare = "max_10P_newSmoothing";

	string compare = "max_distributions";

	TH1D* spur;
	TH1D* chiSq;
	TH1D* error;
	TH1D* total_error;

	TH1D* spur_smooth;
        TH1D* chiSq_smooth;
        TH1D* error_smooth;
		TH1D* total_error_smooth;


	//array to hold bias, impact for max SS
	double bias[bkg_names.size()];
	double impact[bkg_names.size()];
	double mean_smooth[bkg_names.size()];
	double mean_norm[bkg_names.size()];
	double width_smooth[bkg_names.size()];
	double width_norm[bkg_names.size()];

	// arrays for max s/ds
    	double bias2[bkg_names.size()];
	double impact2[bkg_names.size()];
	double mean_smooth2[bkg_names.size()];
	double mean_norm2[bkg_names.size()];
	double width_smooth2[bkg_names.size()];
	double width_norm2[bkg_names.size()];


	for(int i = 0; i < bkg_names.size(); i++){

	///if(bkg_names[i] == "Dijet") continue;
	//open TFILES
	//TFile* f1 = TFile::Open("normal_all.root");
	TFile* f1 = TFile::Open(Form("norm_rootFiles/norm_all_%s.root", bkg_names[i].Data())); 

	//TFile* f2 = TFile::Open("smooth_all.root");
	TFile* f2 = TFile::Open(Form("smooth_rootFiles/smooth_all_%s.root", bkg_names[i].Data()));

	//Define RooReal Var + Gaussian for SS distrubution (SMOOTH & NON-SMOOTH)
	//for(int i = 0; i < bkg_names.size(); i++){
		//get histo: 
		spur = (TH1D*) f1->Get(Form("maxSpur_%s", bkg_names[i].Data()));
		spur_smooth = (TH1D*) f2->Get(Form("maxSpur_%s", bkg_names[i].Data()));
		//rename
                spur -> SetName("spur");
                spur_smooth -> SetName("spur_smooth");

		double width_ss;
		double mean_ss;
		double width_ss_smooth;
		double mean_ss_smooth;

		width_ss = spur->GetRMS();
		mean_ss = spur->GetMean();
		width_ss_smooth = spur_smooth->GetRMS();
		mean_ss_smooth = spur_smooth->GetMean();

		//RooRealVar mean_ss("mean_ss", "", -1, -10, 10);
		//RooRealVar width_ss("width_ss", "", 5, 0, 10);
		RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", -5, 30);
		//RooGaussian gauss_SS("gauss_SS","gauss", *spurious_signal,mean_ss,width_ss);
		
		RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,spur);
		//gauss_SS.fitTo(*ss);
		
		//ss->SetLineColor(kBlue);

		/*RooRealVar mean_ss_smooth("mean_ss_smooth", "", -1, -10, 10);
		RooRealVar width_ss_smooth("width_ss_smooth", "", 5, 0, 10);
		RooGaussian gauss_SS_smooth("gauss_SS_smooth","gauss", *spurious_signal,mean_ss_smooth,width_ss_smooth);
		*/
		RooDataHist* ss_smooth = new RooDataHist("ss_smooth", "Spurious Signal Smooth Data", *spurious_signal,spur_smooth);
		//gauss_SS_smooth.fitTo(*ss_smooth);
		
		RooPlot* spurframe = spurious_signal->frame();
		ss->plotOn(spurframe, Name("ss"));
		ss_smooth->plotOn(spurframe, Name("ss_smooth"),MarkerColor(kOrange), LineColor(kOrange));

		//gauss_SS.plotOn(spurframe, Name("gauss_SS"));
		//gauss_SS_smooth.plotOn(spurframe, Name("gauss_SS_smooth"), LineColor(kRed));
		
		//gauss_SS_smooth.SetLineColor(kRed);

		TCanvas *c2 = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		spurframe->GetXaxis()->SetTitle("Maximum Spurious Signal");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
                l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.04);
		l->AddEntry("ss", Form("Data Normal, Width: %.2f, Mean: %.2f", width_ss, mean_ss), "LEP");
        l->AddEntry("ss_smooth", Form("Data Smooth Width: %.2f, Mean: %.2f", width_ss_smooth, mean_ss_smooth), "LEP");
        //l->AddEntry("gauss_SS", Form("Fit Normal, Width: %.2f, Mean: %.2f", width_ss.getVal(),mean_ss.getVal()), "L");
    	//l->AddEntry("gauss_SS_smooth", Form("Fit Smooth, Width: %.2f, Mean: %.2f",width_ss_smooth.getVal(),mean_ss_smooth.getVal()), "L");
		l->Draw();

		bias[i] = abs((mean_ss - mean_ss_smooth)/mean_ss);
		impact[i] = abs(width_ss_smooth/width_ss);
		mean_smooth[i] = mean_ss_smooth;
		mean_norm[i] = mean_ss;
		width_smooth[i] = width_ss_smooth;
		width_norm[i] = width_ss;

		system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots"));
		c2 -> SaveAs(Form("max_plots/%s/%s_SS.png", compare.c_str(), bkg_names[i].Data()));
	}
	//for(int i = 0; i < bkg_names.size(); i++){
		//get histo:
		/*chiSq = (TH1D*) f1->Get(Form("maxChiSq_%s", bkg_names[i].Data()));
		chiSq_smooth = (TH1D*) f2->Get(Form("maxChiSq_%s", bkg_names[i].Data()));
		//rename
		chiSq -> SetName("chiSq");
        chiSq_smooth -> SetName("chiSq_smooth");

		//regular vars
		RooRealVar mean_chi("mean_chi", "",  5, -1, 3);
		RooRealVar width_chi("width_chi", "", 5, -1, 3);
		//smooth vars
		RooRealVar mean_chi_smooth("mean_chi_smooth", "", 5, -1, 3);
		RooRealVar width_chi_smooth("width_chi_smooth", "", 5, -1, 3);
		//x axis
		RooRealVar* chi_squared = new RooRealVar("chi_squared", "", 0, 10);

		//gaussians
		RooGaussian gauss_chi2("gauss_chi2","gauss", *chi_squared,mean_chi,width_chi);
		RooGaussian gauss_chi2_smooth("gauss_chi2_smooth","gauss", *chi_squared,mean_chi_smooth,width_chi_smooth);

		//roo histos and root fits
		RooDataHist* chi2 = new RooDataHist("chi2", "Chi-Squared", *chi_squared,chiSq);
		gauss_chi2.fitTo(*chi2);

		RooDataHist* chi2_smooth = new RooDataHist("chi2_smooth", "Chi-Squared Smooth Data", *chi_squared, chiSq_smooth);
		gauss_chi2_smooth.fitTo(*chi2_smooth);

		//plot stuff
		RooPlot* chiframe = chi_squared->frame();
		chi2->plotOn(chiframe, Name("chi2"));
		chi2_smooth->plotOn(chiframe, Name("chi2_smooth"), MarkerColor(kOrange), LineColor(kOrange));
		gauss_chi2.plotOn(chiframe, Name("gauss_chi2"));
		gauss_chi2_smooth.plotOn(chiframe, Name("gauss_chi2_smooth"),LineColor(kRed));
		
		//create canvas - legend - and save
		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		chiframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		chiframe->GetXaxis()->SetTitle("Maximum Chi-Squared");
		chiframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		chiframe->Draw();
 
		auto l = new TLegend(0.6,0.6,0.99,0.99);
   		l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.04);
		l->AddEntry("chi2", "Data Normal", "LEP");
		l->AddEntry("chi2_smooth", "Data Smooth", "LEP");
		l->AddEntry("gauss_chi2", Form("Fit Normal, Width: %.2f, Mean: %.2f", width_chi.getVal(), mean_chi.getVal()), "L");
        l->AddEntry("gauss_chi2_smooth", Form("Fit Smooth, Width: %.2f, Mean: %.2f", width_chi_smooth.getVal(), mean_chi_smooth.getVal()), "L");
		l->Draw();

		system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots"));
		c2 -> SaveAs(Form("max_plots/%s/%s_chi2.png",compare.c_str(), bkg_names[i].Data()));
        //}*/


		//Delta S
	for(int i = 0; i < bkg_names.size(); i++){
		//if(bkg_names[i] == "Dijet") continue;
		//open TFILES
		//TFile* f1 = TFile::Open("normal_all.root");
		TFile* f1 = TFile::Open(Form("norm_rootFiles/norm_all_%s.root", bkg_names[i].Data())); 

		//TFile* f2 = TFile::Open("smooth_all.root");
		TFile* f2 = TFile::Open(Form("smooth_rootFiles/smooth_all_%s.root", bkg_names[i].Data()));
		//get histo:
		error = (TH1D*) f1->Get(Form("error_%s", bkg_names[i].Data()));
		error_smooth = (TH1D*) f2->Get(Form("error_%s", bkg_names[i].Data()));
		//rename
		error -> SetName("error");
        error_smooth -> SetName("error_smooth");

		double width_ds;
		double mean_ds;
		double width_ds_smooth;
		double mean_ds_smooth;

		width_ds = error->GetRMS();
		mean_ds = error->GetMean();
		width_ds_smooth = error_smooth->GetRMS();
		mean_ds_smooth = error_smooth->GetMean();

		//x axis
		RooRealVar* error_x = new RooRealVar("error_x", "", 10, 16);

		//roo histos and root fits
		RooDataHist* error_data = new RooDataHist("error_data", "Error Data", *error_x, error);

		RooDataHist* error_data_smooth = new RooDataHist("error_data_smooth", "Error Smooth Data", *error_x, error_smooth);

		//plot stuff
		RooPlot* errframe = error_x->frame();
		error_data->plotOn(errframe, Name("error_data"));
		error_data_smooth->plotOn(errframe, Name("error_data_smooth"), MarkerColor(kOrange), LineColor(kOrange));

		//create canvas - legend - and save
		TCanvas *c2 = new TCanvas(Form("%s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		errframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		errframe->GetXaxis()->SetTitle("Maximum Delta S");
		errframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		errframe->Draw();
 
		auto l = new TLegend(0.6,0.6,0.15,0.9);
   		l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.04);
		l->AddEntry("error_data", Form("Data Normal Width: %.2f, Mean: %.2f", width_ds, mean_ds), "LEP");
		l->AddEntry("error_data_smooth", Form("Data Smooth Width: %.2f, Mean: %.2f", width_ds_smooth, mean_ds_smooth), "LEP");
		l->Draw();

		system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots"));
		c2 -> SaveAs(Form("max_plots/%s/%s_error.png",compare.c_str(), bkg_names[i].Data()));
        }


		//total error S/DS
	for(int i = 0; i < bkg_names.size(); i++){
		//if(bkg_names[i] == "Dijet") continue;
		//open TFILES
		//TFile* f1 = TFile::Open("normal_all.root");
		TFile* f1 = TFile::Open(Form("norm_rootFiles/norm_all_%s.root", bkg_names[i].Data())); 

		//TFile* f2 = TFile::Open("smooth_all.root");
		TFile* f2 = TFile::Open(Form("smooth_rootFiles/smooth_all_%s.root", bkg_names[i].Data()));
		//get histo: 
		total_error = (TH1D*) f1->Get(Form("total_error_%s", bkg_names[i].Data()));
		total_error_smooth = (TH1D*) f2->Get(Form("total_error_%s", bkg_names[i].Data()));
		//rename
                total_error -> SetName("total_error");
                total_error_smooth -> SetName("total_error_smooth");

		double width_err;
		double mean_err;
		double width_err_smooth;
		double mean_err_smooth;

		width_err = total_error->GetRMS();
		mean_err = total_error->GetMean();
		width_err_smooth = total_error_smooth->GetRMS();
		mean_err_smooth = total_error_smooth->GetMean();

		RooRealVar* error_x = new RooRealVar("error_x", "", -.4, 1);
		
		RooDataHist* err_tot = new RooDataHist("err_tot", "S/DS Data", *error_x,total_error);

		RooDataHist* err_tot_smooth = new RooDataHist("err_tot_smooth", "S/DS Smooth Data", *error_x,total_error_smooth);
		
		RooPlot* spurframe = error_x->frame();
		err_tot->plotOn(spurframe, Name("err_tot"));
		err_tot_smooth->plotOn(spurframe, Name("err_tot_smooth"),MarkerColor(kOrange), LineColor(kOrange));


		TCanvas *c2 = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
		spurframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
		spurframe->GetXaxis()->SetTitle("Maximum S/DS");
		spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
		spurframe->Draw();

		TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
                l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
		l->SetLineColor(kWhite);
		l->SetTextSize(0.04);
		l->AddEntry("err_tot", Form("Data Normal, Width: %.2f, Mean: %.2f", width_err, mean_err), "LEP");
        l->AddEntry("err_tot_smooth", Form("Data Smooth Width: %.2f, Mean: %.2f", width_err_smooth, mean_err_smooth), "LEP");
        l->Draw();

		bias2[i] = abs((mean_err - mean_err_smooth)/mean_err);
		impact2[i] = abs(width_err_smooth/width_err);
		mean_smooth2[i] = mean_err_smooth;
		mean_norm2[i] = mean_err;
		width_smooth2[i] = width_err_smooth;
		width_norm2[i] = width_err;

		system(Form("mkdir -vp %s", compare.c_str()));
		system(Form("mkdir -vp max_plots"));
		c2 -> SaveAs(Form("max_plots/%s/%s_total_err.png", compare.c_str(), bkg_names[i].Data()));
	//}
	}

	cout << "Bias & Impact for Max Spurious Signal Fit: " << endl;
		cout << left << setw(15) << "" << left << setw(15) << "Bias" << left << setw(15) << "Impact" << left << setw(15) << "Mean Smooth" << left << setw(15) << "Mean Norm" << left << setw(15) << "Width Smooth" << left << setw(15) << "Width Norm" << endl;
	    cout << "-------------------------------------------------------------------------------------------------------" << endl;

		for(int i = 0; i < bkg_names.size(); i++){
			//if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(15) <<  bkg_names[i] << left << setw(15) << bias[i] << left << setw(15) << impact[i] << left << setw(15) << mean_smooth[i] << left << setw(15) << mean_norm[i] << left << setw(15) << width_smooth[i] << left << setw(15) << width_norm[i] << endl;
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
		}

	cout << "Bias & Impact for Max Spurious Signal Fit over Delta S: " << endl;
		cout << left << setw(15) << "" << left << setw(15) << "Bias" << left << setw(15) << "Impact" << left << setw(15) << "Mean Smooth" << left << setw(15) << "Mean Norm" << left << setw(15) << "Width Smooth" << left << setw(15) << "Width Norm" << endl;
	    cout << "-------------------------------------------------------------------------------------------------------" << endl;

		//cout << "Mean value of " << mean_val[k] << endl;
		for(int i = 0; i < bkg_names.size(); i++){
			//if (bkg_names[i] == "Dijet") continue;
			cout << left << setw(15) <<  bkg_names[i] << left << setw(15) << bias2[i] << left << setw(15) << impact2[i] << left << setw(15) << mean_smooth2[i] << left << setw(15) << mean_norm2[i] << left << setw(15) << width_smooth2[i] << left << setw(15) << width_norm2[i] << endl;
			cout << "-------------------------------------------------------------------------------------------------------" << endl;
		}

}
