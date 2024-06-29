#include "TGraph.h"

using namespace RooFit;
using namespace std;

void text(){
	cout << "Hello i am using a function in ROOT!" << endl;
}

void process_data(int min, int max, string compare_dummy, vector<TString> eq_dummy, vector<TString> bkg_names_dummy, int bkg_names_size, double mean_arr[], int mean_size, string data1_dummy, string data2_dummy, string data3_dummy, string type, string plot_name, string spur_type, string rootName1, string rootName2, string rootName3, int fold){
	double width, mean, width_error, mean_error; //MC
	double width1, mean1, width_error1, mean_error1; //ML
	double width2, mean2, width_error2, mean_error2;  //Truth

	double mean_0[mean_size][bkg_names_size];
	double mean_1[mean_size][bkg_names_size];
	double mean_2[mean_size][bkg_names_size];
	double width_0[mean_size][bkg_names_size];
	double width_1[mean_size][bkg_names_size];
	double width_2[mean_size][bkg_names_size];

	double mean_Err0[mean_size][bkg_names_size];
	double mean_Err1[mean_size][bkg_names_size];
	double mean_Err2[mean_size][bkg_names_size];
	double width_Err0[mean_size][bkg_names_size];
	double width_Err1[mean_size][bkg_names_size];
	double width_Err2[mean_size][bkg_names_size];

	double mean_mc[bkg_names_size];
	double mean_nf[bkg_names_size];
	double mean_truth[bkg_names_size];
	double mean_error_mc[bkg_names_size];
	double mean_error_nf[bkg_names_size];
	double mean_error_truth[bkg_names_size];

	double width_mc[bkg_names_size];
	double width_nf[bkg_names_size];
	double width_truth[bkg_names_size];
	double width_error_mc[bkg_names_size];
	double width_error_nf[bkg_names_size];
	double width_error_truth[bkg_names_size];

	TH1D* spur1;
	TH1D* spur2;
	TH1D* spur3;
	TH1D* fixHist1;
	TH1D* fixHist2;
	TH1D* fixHist3;

	for(int k = 0; k < mean_size; k++){
    	if(mean_arr[k] != 125) continue; 
		for(int i = 0; i < bkg_names_size; i++){
        //if(bkg_names[i] != "Exponential") continue;

		TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names_dummy[i].Data()));
		TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names_dummy[i].Data()));
		TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names_dummy[i].Data()));

		//get histo: 
		spur1 = (TH1D*) f1->Get(Form("%s_%s_%3.0f",spur_type.c_str(), bkg_names_dummy[i].Data(), mean_arr[k]));
		spur2 = (TH1D*) f2->Get(Form("%s_%s_%3.0f",spur_type.c_str(), bkg_names_dummy[i].Data(), mean_arr[k]));
		spur3 = (TH1D*) f3->Get(Form("%s_%s_%3.0f",spur_type.c_str(), bkg_names_dummy[i].Data(), mean_arr[k]));
		
		//rename
				spur1 -> SetName("spur1");
				spur2 -> SetName("spur2");
				spur3 -> SetName("spur3");
		
			double RMS_v0, Mean_v0, RMS_v1, Mean_v1, RMS_v2, Mean_v2; 
			double bin_x1, bin_x2, bin_y1, bin_y2, bin_z1, bin_z2, x1, x2, y1, y2, z1, z2;
			int num_range = 5;

			RMS_v0 = spur1->GetRMS();
			Mean_v0 = spur1->GetMean();
			RMS_v1 = spur2->GetRMS();
			Mean_v1 = spur2->GetMean();
			RMS_v2 = spur3->GetRMS();
			Mean_v2 = spur3->GetMean();
			cout << "Mean V0: " << Mean_v0 << " RMS v0: " << RMS_v0 << endl;

			x1 = Mean_v0-num_range*RMS_v0;
			x2 = Mean_v0+num_range*RMS_v0;
			y1 = Mean_v1-num_range*RMS_v1;
			y2 = Mean_v1+num_range*RMS_v1;
			z1 = Mean_v2-num_range*RMS_v2;
			z2 = Mean_v2+num_range*RMS_v2;

			bin_x1 = spur1->FindBin(Mean_v0-num_range*RMS_v0);
			bin_x2 = spur1->FindBin(Mean_v0+num_range*RMS_v0);
			bin_y1 = spur2->FindBin(Mean_v1-num_range*RMS_v1);
			bin_y2 = spur2->FindBin(Mean_v1+num_range*RMS_v1);
			bin_z1 = spur3->FindBin(Mean_v2-num_range*RMS_v2);
			bin_z2 = spur3->FindBin(Mean_v2+num_range*RMS_v2);
			//cout << "Bin x1: " << bin_x1 << " Bin x2: " << bin_x2 << endl;

			//define new (second) histogram:
				fixHist1 = new TH1D("spur_new_histogram MC (1)","New MC",bin_x2-bin_x1+1, x1, x2);
				fixHist2 = new TH1D("spur_new_histogram ML (1)","New ML",bin_y2-bin_y1+1, y1, y2);
				fixHist3 = new TH1D("spur_new_histogram Truth (2)","New Truth",bin_z2-bin_z1+1, z1, z2);

			//loop over the bins in the 1st histogram, copy the bin content and bin error at the same X-axis position to the 2nd histogram
			for(int j = bin_x1 ; j <= bin_x2 ; j++){
				// if (spur1->GetBinContent(j) != 0)
				// cout<<spur1->GetBinContent(j)<< " at bin: " << j << endl;

				double x=spur1->GetBinCenter(j);  
				double bin_y = fixHist1->FindBin(x) ;  
				fixHist1->SetBinContent(bin_y, spur1->GetBinContent(j));

				fixHist1->SetBinError(bin_y, spur1->GetBinError(j));
			} 

			for(int j = bin_y1 ; j <= bin_y2 ; j++){
				// if (spur2->GetBinContent(j) != 0)
				// cout<<spur2->GetBinContent(j)<< " at bin: " << j << endl;

				double x=spur2->GetBinCenter(j);  
				double bin_y = fixHist2->FindBin(x) ;  
				fixHist2->SetBinContent(bin_y, spur2->GetBinContent(j));

				fixHist2->SetBinError(bin_y, spur2->GetBinError(j));
			} 

			for(int j = bin_z1 ; j <= bin_z2 ; j++){
				// if (spur3->GetBinContent(j) != 0)
				// cout<<spur3->GetBinContent(j)<< " at bin: " << j << endl;

				double x=spur3->GetBinCenter(j);  
				double bin_y = fixHist3->FindBin(x) ;  
				fixHist3->SetBinContent(bin_y, spur3->GetBinContent(j));

				fixHist3->SetBinError(bin_y, spur3->GetBinError(j));
			} 

			//number of folds? 
			double integral; 
			integral = fixHist1 -> Integral();

				width = fixHist1->GetRMS();
				mean = fixHist1->GetMean();
				width_error = fixHist1->GetRMSError();
				mean_error = fixHist1->GetMeanError();

				width1 = fixHist2->GetRMS();
				mean1 = fixHist2->GetMean();
				width_error1 = fixHist2->GetRMSError();
				mean_error1 = fixHist2->GetMeanError();

				width2 = fixHist3->GetRMS();
				mean2 = fixHist3->GetMean();
				width_error2 = fixHist3->GetRMSError();
				mean_error2 = fixHist3->GetMeanError();

				RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min, max);

				RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,fixHist1);  //one small addition
				RooDataHist* ss1 = new RooDataHist("ss1", "Spurious Signal Data", *spurious_signal,fixHist2);
				RooDataHist* ss2 = new RooDataHist("ss2", "Spurious Signal Data", *spurious_signal,fixHist3);

				RooPlot* spurframe = spurious_signal->frame();
				ss->plotOn(spurframe, Name("ss"));
				ss1->plotOn(spurframe, Name("ss1"),MarkerColor(46), LineColor(46)); //ML //soft red
				ss2->plotOn(spurframe, Name("ss2"), MarkerColor(8), LineColor(8)); //Truth //soft green

				TCanvas *c = new TCanvas(Form("%s", bkg_names_dummy[i].Data()), Form("%s", bkg_names_dummy[i].Data()), 800, 400);
				spurframe->SetTitle(Form("%s plot & Mean Val: %3.0f", bkg_names_dummy[i].Data(), mean_arr[k]));
				spurframe->GetXaxis()->SetTitle(Form("%s", plot_name.c_str()));
				spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
				spurframe->Draw();

				TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
				l->SetHeader(Form("PDF =  %s", eq_dummy[i].Data()),"C");
				l->SetLineColor(kWhite);
				l->SetTextSize(0.03);
				l->AddEntry("ss", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1_dummy.c_str(), width, width_error, mean, mean_error), "LEP");
				l->AddEntry("ss1", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2_dummy.c_str(), width1, width_error1, mean1, mean_error1), "LEP");
				l->AddEntry("ss2", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3_dummy.c_str(), width2, width_error2, mean2, mean_error2), "LEP");
				l->AddEntry("histogram_fold", Form("Integral Value: %.0f", integral), "");
				l->Draw();

				mean_0[k][i] = mean;
				mean_1[k][i] = mean1;
				mean_2[k][i] = mean2;
				width_0[k][i] = width;
				width_1[k][i] = width1;
				width_2[k][i] = width2;

				mean_Err0[k][i] = mean_error;
				mean_Err1[k][i] = mean_error1;
				mean_Err2[k][i] = mean_error2;
				width_Err0[k][i] = width_error;
				width_Err1[k][i] = width_error1;
				width_Err2[k][i] = width_error2;

				system(Form("mkdir -vp distributions/%s", compare_dummy.c_str()));
				system(Form("mkdir -vp distributions/%s/%s", compare_dummy.c_str(), type.c_str()));
				c -> SaveAs(Form("distributions/%s/%s/%s_%s_%3.0f.png", compare_dummy.c_str(), type.c_str(), bkg_names_dummy[i].Data(), type.c_str(), mean_arr[k]));
		}
	}	

	//-------SCATTER PLOTS--------//
	for(int i = 0; i < bkg_names_size; i++){
		//mean
		mean_mc[i] = mean_2[4][i];
		mean_error_mc[i] = mean_Err2[4][i];

		mean_nf[i] = mean_1[4][i];
		mean_error_nf[i] = mean_Err1[4][i];

		mean_truth[i] = mean_0[4][i];
		mean_error_truth[i] = mean_Err0[4][i];

		//width

		width_mc[i] = width_2[4][i];
		width_error_mc[i] = width_Err2[4][i];

		width_nf[i] = width_1[4][i];
		width_error_nf[i] = width_Err1[4][i];

		width_truth[i] = width_0[4][i];
		width_error_truth[i] = width_Err0[4][i];
	}

	//PLOT SCATTER
   TCanvas *c1 = new TCanvas("c1","Exclusion graphs examples",200,10,600,400);
   c1->SetGrid();
 
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle("Width vs. Mean For All Background PDFs");
   mg->GetXaxis()->SetTitle("Mean");
   mg->GetYaxis()->SetTitle("Width");
 
   const Int_t n = bkg_names_size;
 
   TGraph *gr1 = new TGraphErrors(n,mean_truth, width_truth, mean_error_truth, width_error_truth);
   gr1->SetMarkerColor(4);
   gr1->SetMarkerSize(1.0);
   gr1->SetMarkerStyle(21);
   gr1 -> SetName("gr1");
   
 
   TGraph *gr2 = new TGraphErrors(n,mean_nf, width_nf, mean_error_nf, width_error_nf);
   gr2->SetMarkerColor(2);
   gr2->SetMarkerSize(1.0);
   gr2->SetMarkerStyle(20);
   gr2 -> SetName("gr2");
   
   TGraph *gr3 = new TGraphErrors(n,mean_mc, width_mc, mean_error_mc, width_error_mc);
   gr3->SetMarkerColor(8);
   gr3->SetMarkerSize(1.0);
   gr3->SetMarkerStyle(22);
   gr3 -> SetName("gr3");
 
   mg->Add(gr1);
   mg->Add(gr2);
   mg->Add(gr3);
   mg->Draw("AP");

   //legend
    TLegend *l1 = new TLegend(0.1,0.7,0.5,0.90);
	l1->SetLineColor(kWhite);
	l1->SetTextSize(0.03);

	l1->AddEntry("gr1", "Truth", "lp");
	l1->AddEntry("gr2", "Normalizing Flow", "lp");
	l1->AddEntry("gr3", "Monte Carlo", "lp");
	l1->Draw();
 
   c1 -> SaveAs(Form("distributions/%s/%s_scatter.png", compare_dummy.c_str(), type.c_str()));

	//plots as shuo suggested

	double ml, mr, wl, wr;
	if (type == "SS"){
		wl = 2.8;
		wr = 4;
		ml = -3;
		mr = .5;
	}
	else if (type == "dS"){
		wl = .1;
		wr = .2;
		ml = 11.4;
		mr = 15;
	}
	else if (type == "SdS"){
		wl = .2;
		wr = .3;
		ml = -.25;
		mr = .15;
	}

	TCanvas *c2 = new TCanvas("c2","Plotting Data Tables",200,10,600,400);

	 TH1 *h1 = new TH1F("h1", "", 6,0,6);
	 TH1 *h3 = new TH1F("h3", "", 6,0,6);
	 TH1 *h5 = new TH1F("h5", "", 6,0,6);

	vector<TString> xlabels = {"Bern3", "Bern4", "Bern5", "Exp", "ExpPoly2", "ExpPoly3"};
	//vector<float> values = {-0.2233, -0.1635, -0.3884, -2.6487, -0.0120, -0.2304};
	//vector<float> errors = {0.1037, 0.1034, 0.1173, 0.0944, 0.1020, 0.1029};
	for(int j = 0; j < xlabels.size(); j++){
		h1->Fill(xlabels[j], mean_truth[j]);
		h1->SetBinError(j+1, mean_error_truth[j]);

		h3->Fill(xlabels[j], mean_mc[j]);
		h3->SetBinError(j+1, mean_error_mc[j]);

		h5->Fill(xlabels[j], mean_nf[j]);
		h5->SetBinError(j+1, mean_error_nf[j]);
	}
	h1->SetStats(0);
	h3->SetStats(0);
	h5->SetStats(0);
	h1->GetYaxis()->SetRangeUser(-1, 1);

	h1->SetTitle(Form("Mean Data %i Fold, %s", fold, type.c_str()));
    h1->GetXaxis()->SetTitle("Mean Test");
    h1->GetYaxis()->SetTitle("Events");

	h1->SetMarkerColor(4);
	h1->SetLineColor(4);
    h1->SetMarkerSize(1.0);
    h1->SetMarkerStyle(21);
    h1 -> SetName("Mean Truth");

	h3->SetMarkerColor(2);
	h3->SetLineColor(2);
    h3->SetMarkerSize(1.0);
    h3->SetMarkerStyle(20);
    h3 -> SetName("Mean MC");

	h5->SetMarkerColor(8);
	h5->SetLineColor(8);
    h5->SetMarkerSize(1.0);
    h5->SetMarkerStyle(22);
    h5 -> SetName("Mean ML");

	h1->Draw("SAME");
	h3->Draw("SAME");
	h5->Draw("SAME");

	TLegend *l2 = new TLegend(0.87,0.7,.99,0.9);
	l2->SetLineColor(kWhite);
	l2->SetTextSize(0.03);

	l2->AddEntry("Mean Truth", "Mean Truth", "lp");
	l2->AddEntry("Mean MC", "Mean MC", "lp");
	l2->AddEntry("Mean ML", "Mean ML", "lp");
	l2->Draw();

	c2-> SaveAs(Form("distributions/%s/%s_mean_scatter.png", compare_dummy.c_str(), type.c_str()));
	
	TCanvas *c3 = new TCanvas("c3","Width",200,10,600,400);
	
	TH1 *h2 = new TH1F("h1", "", 6,0,6);
	TH1 *h4 = new TH1F("h3", "", 6,0,6);
	TH1 *h6 = new TH1F("h6", "", 6,0,6);

	for(int j = 0; j < xlabels.size(); j++){
		h2->Fill(xlabels[j], width_truth[j]);
		h2->SetBinError(j+1, width_error_truth[j]);

		h4->Fill(xlabels[j], width_mc[j]);
		h4->SetBinError(j+1, width_error_mc[j]);

		h6->Fill(xlabels[j], width_nf[j]);
		h6->SetBinError(j+1, width_error_nf[j]);
	}

	h2->SetStats(0);
	h4->SetStats(0);
	h6->SetStats(0);
	h2->GetYaxis()->SetRangeUser(wl, 5);

	h2->SetTitle(Form("Width Data %i Fold, %s", fold, type.c_str()));
    h2->GetXaxis()->SetTitle("Mean Test");
    h2->GetYaxis()->SetTitle("Events");
	h4->GetXaxis();
	h4->GetYaxis();
	h6->GetXaxis();
	h6->GetYaxis();

	h2->SetMarkerColor(4);
	h2->SetLineColor(4);
    h2->SetMarkerSize(1.0);
    h2->SetMarkerStyle(21);
    h2 -> SetName("Width Truth");

	h4->SetMarkerColor(2);
	h4->SetLineColor(2);
    h4->SetMarkerSize(1.0);
    h4->SetMarkerStyle(20);
    h4 -> SetName("Width MC");

	h6->SetMarkerColor(8);
	h6->SetLineColor(8);
    h6->SetMarkerSize(1.0);
    h6->SetMarkerStyle(22);
    h6 -> SetName("Width ML");

	h2->Draw("SAME");
	h4->Draw("SAME");
	h6->Draw("SAME");

	TLegend *l3 = new TLegend(0.87,0.7,.99,0.9);
	l3->SetLineColor(kWhite);
	l3->SetTextSize(0.03);

	l3->AddEntry("Width Truth", "Width Truth", "lp");
	l3->AddEntry("Width MC", "Width MC", "lp");
	l3->AddEntry("Width ML", "Width ML", "lp");
	l3->Draw();

	c3-> SaveAs(Form("distributions/%s/%s_width_scatter.png", compare_dummy.c_str(), type.c_str()));




		//----PRINT OUT TABLES----//

	// Create and open a text file
  	ofstream MyFile(Form("distributions/%s/%s_mean.txt", compare_dummy.c_str(),type.c_str()));
	ofstream MyFile2(Form("distributions/%s/%s_width.txt", compare_dummy.c_str(),type.c_str()));

	cout << "" << endl;

		MyFile << Form("%s Fit: ", plot_name.c_str()) << endl;
		for(int k = 0; k < mean_size; k++){
			if (mean_arr[k] != 125.0) continue;

			MyFile << "Mean Value: " << mean_arr[k] << endl;

			MyFile << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3_dummy.c_str()) << left << setw(20) << Form("Mean %s", data2_dummy.c_str()) << left << setw(20) << Form("Mean %s", data1_dummy.c_str()) << endl;
			MyFile << "--------------------------------------------------------------------------" << endl;

			//cout << "Mean value of " << mean_val[k] << endl;
			for(int i = 0; i < bkg_names_size; i++){
				//if (bkg_names[i] == "Dijet") continue;
				MyFile << left << setw(20) <<  bkg_names_dummy[i] << left << setw(20) << Form("%.4f ± %.4f", mean_2[k][i], mean_Err2[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_1[k][i], mean_Err1[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_0[k][i], mean_Err0[k][i]) << endl;
				MyFile << "--------------------------------------------------------------------------" << endl;
			}
		}

	// Close the file
  	MyFile.close();
  
	cout << "" << endl;
	MyFile2 << Form("%s Fit: ", plot_name.c_str()) << endl;
		for(int k = 0; k < mean_size; k++){
			if (mean_arr[k] != 125.0) continue;

			MyFile2 << "Mean Value: " << mean_arr[k] << endl;

			MyFile2 << left << setw(20) << "" << left << setw(20) << Form("Width %s", data3_dummy.c_str()) << left << setw(20) << Form("Width %s", data2_dummy.c_str()) << left << setw(15) << Form("Width %s", data1_dummy.c_str()) << endl;
			MyFile2 << "--------------------------------------------------------------------------" << endl;

			//cout << "Mean value of " << mean_val[k] << endl;
			for(int i = 0; i < bkg_names_size; i++){
				//if (bkg_names[i] == "Dijet") continue;
				MyFile2 << left << setw(20) <<  bkg_names_dummy[i] << left << setw(20) << Form("%.4f ± %.4f", width_2[k][i], width_Err2[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_1[k][i], width_Err1[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_0[k][i], width_Err0[k][i]) << endl;
				MyFile2 << "--------------------------------------------------------------------------" << endl;
			}
		}
	// Close the file
  	MyFile2.close();	

}

//------------------------------------For a Guassian Fit: -----------------------------------------//
void process_data_gauss(int min, int max, string compare_dummy, vector<TString> eq_dummy, vector<TString> bkg_names_dummy, int bkg_names_size, double mean_arr[], int mean_size, string data1_dummy, string data2_dummy, string data3_dummy, string type, string plot_name, string spur_type, string rootName1, string rootName2, string rootName3, int fold){
	double width, mean, width_error, mean_error; //MC
	double width1, mean1, width_error1, mean_error1; //ML
	double width2, mean2, width_error2, mean_error2;  //Truth

	double mean_0[mean_size][bkg_names_size];
	double mean_1[mean_size][bkg_names_size];
	double mean_2[mean_size][bkg_names_size];
	double width_0[mean_size][bkg_names_size];
	double width_1[mean_size][bkg_names_size];
	double width_2[mean_size][bkg_names_size];

	double mean_Err0[mean_size][bkg_names_size];
	double mean_Err1[mean_size][bkg_names_size];
	double mean_Err2[mean_size][bkg_names_size];
	double width_Err0[mean_size][bkg_names_size];
	double width_Err1[mean_size][bkg_names_size];
	double width_Err2[mean_size][bkg_names_size];

	double mean_mc[bkg_names_size];
	double mean_nf[bkg_names_size];
	double mean_truth[bkg_names_size];
	double mean_error_mc[bkg_names_size];
	double mean_error_nf[bkg_names_size];
	double mean_error_truth[bkg_names_size];

	double width_mc[bkg_names_size];
	double width_nf[bkg_names_size];
	double width_truth[bkg_names_size];
	double width_error_mc[bkg_names_size];
	double width_error_nf[bkg_names_size];
	double width_error_truth[bkg_names_size];

	TH1D* spur1;
	TH1D* spur2;
	TH1D* spur3;
	TH1D* fixHist1;
	TH1D* fixHist2;
	TH1D* fixHist3;

	for(int k = 0; k < mean_size; k++){
    	if(mean_arr[k] != 125) continue; 
		for(int i = 0; i < bkg_names_size; i++){
        //if(bkg_names[i] != "Exponential") continue;

		TFile* f1 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName1.c_str(), rootName1.c_str(), bkg_names_dummy[i].Data()));
		TFile* f2 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName2.c_str(), rootName2.c_str(), bkg_names_dummy[i].Data()));
		TFile* f3 = TFile::Open(Form("%s_rootFiles/%s_all_%s.root", rootName3.c_str(), rootName3.c_str(), bkg_names_dummy[i].Data()));

		//get histo: 
		spur1 = (TH1D*) f1->Get(Form("%s_%s_%3.0f",spur_type.c_str(), bkg_names_dummy[i].Data(), mean_arr[k]));
		spur2 = (TH1D*) f2->Get(Form("%s_%s_%3.0f",spur_type.c_str(), bkg_names_dummy[i].Data(), mean_arr[k]));
		spur3 = (TH1D*) f3->Get(Form("%s_%s_%3.0f",spur_type.c_str(), bkg_names_dummy[i].Data(), mean_arr[k]));
		
		//rename
				spur1 -> SetName("spur1");
				spur2 -> SetName("spur2");
				spur3 -> SetName("spur3");
		
			double RMS_v0, Mean_v0, RMS_v1, Mean_v1, RMS_v2, Mean_v2; 
			double bin_x1, bin_x2, bin_y1, bin_y2, bin_z1, bin_z2, x1, x2, y1, y2, z1, z2;
			int num_range = 5;

			RMS_v0 = spur1->GetRMS();
			Mean_v0 = spur1->GetMean();
			RMS_v1 = spur2->GetRMS();
			Mean_v1 = spur2->GetMean();
			RMS_v2 = spur3->GetRMS();
			Mean_v2 = spur3->GetMean();
			cout << "Mean V0: " << Mean_v0 << " RMS v0: " << RMS_v0 << endl;

			x1 = Mean_v0-num_range*RMS_v0;
			x2 = Mean_v0+num_range*RMS_v0;
			y1 = Mean_v1-num_range*RMS_v1;
			y2 = Mean_v1+num_range*RMS_v1;
			z1 = Mean_v2-num_range*RMS_v2;
			z2 = Mean_v2+num_range*RMS_v2;

			bin_x1 = spur1->FindBin(Mean_v0-num_range*RMS_v0);
			bin_x2 = spur1->FindBin(Mean_v0+num_range*RMS_v0);
			bin_y1 = spur2->FindBin(Mean_v1-num_range*RMS_v1);
			bin_y2 = spur2->FindBin(Mean_v1+num_range*RMS_v1);
			bin_z1 = spur3->FindBin(Mean_v2-num_range*RMS_v2);
			bin_z2 = spur3->FindBin(Mean_v2+num_range*RMS_v2);
			//cout << "Bin x1: " << bin_x1 << " Bin x2: " << bin_x2 << endl;

			//define new (second) histogram:
				fixHist1 = new TH1D("spur_new_histogram MC (1)","New MC",bin_x2-bin_x1+1, x1, x2);
				fixHist2 = new TH1D("spur_new_histogram ML (1)","New ML",bin_y2-bin_y1+1, y1, y2);
				fixHist3 = new TH1D("spur_new_histogram Truth (2)","New Truth",bin_z2-bin_z1+1, z1, z2);

			//loop over the bins in the 1st histogram, copy the bin content and bin error at the same X-axis position to the 2nd histogram
			for(int j = bin_x1 ; j <= bin_x2 ; j++){
				// if (spur1->GetBinContent(j) != 0)
				// cout<<spur1->GetBinContent(j)<< " at bin: " << j << endl;

				double x=spur1->GetBinCenter(j);  
				double bin_y = fixHist1->FindBin(x) ;  
				fixHist1->SetBinContent(bin_y, spur1->GetBinContent(j));

				fixHist1->SetBinError(bin_y, spur1->GetBinError(j));
			} 

			for(int j = bin_y1 ; j <= bin_y2 ; j++){
				// if (spur2->GetBinContent(j) != 0)
				// cout<<spur2->GetBinContent(j)<< " at bin: " << j << endl;

				double x=spur2->GetBinCenter(j);  
				double bin_y = fixHist2->FindBin(x) ;  
				fixHist2->SetBinContent(bin_y, spur2->GetBinContent(j));

				fixHist2->SetBinError(bin_y, spur2->GetBinError(j));
			} 

			for(int j = bin_z1 ; j <= bin_z2 ; j++){
				// if (spur3->GetBinContent(j) != 0)
				// cout<<spur3->GetBinContent(j)<< " at bin: " << j << endl;

				double x=spur3->GetBinCenter(j);  
				double bin_y = fixHist3->FindBin(x) ;  
				fixHist3->SetBinContent(bin_y, spur3->GetBinContent(j));

				fixHist3->SetBinError(bin_y, spur3->GetBinError(j));
			} 

			//number of folds? 
			double integral; 
			integral = fixHist1 -> Integral();

				width = fixHist1->GetRMS();
				mean = fixHist1->GetMean();
				width_error = fixHist1->GetRMSError();
				mean_error = fixHist1->GetMeanError();

				width1 = fixHist2->GetRMS();
				mean1 = fixHist2->GetMean();
				width_error1 = fixHist2->GetRMSError();
				mean_error1 = fixHist2->GetMeanError();

				width2 = fixHist3->GetRMS();
				mean2 = fixHist3->GetMean();
				width_error2 = fixHist3->GetRMSError();
				mean_error2 = fixHist3->GetMeanError();

				RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min, max);

				//Gaussian Definitions:
				RooRealVar mean_ss("mean_ss", "", -1, -10, 10);
				RooRealVar width_ss("width_ss", "", 5, 0, 10);
				RooGaussian gauss_ss("gauss_SS","gauss", *spurious_signal,mean_ss,width_ss);

				RooRealVar mean_ss1("mean_ss1", "", -1, -10, 10);
				RooRealVar width_ss1("width_ss1", "", 5, 0, 10);
				RooGaussian gauss_ss1("gauss_ss1","gauss", *spurious_signal,mean_ss1,width_ss1);

				RooRealVar mean_ss2("mean_ss2", "", -1, -10, 10);
				RooRealVar width_ss2("width_ss2", "", 5, 0, 10);
				RooGaussian gauss_ss2("gauss_ss2","gauss", *spurious_signal,mean_ss2,width_ss2);

				RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,fixHist1);  //one small addition
				gauss_ss.fitTo(*ss);

				RooDataHist* ss1 = new RooDataHist("ss1", "Spurious Signal Data", *spurious_signal,fixHist2);
				gauss_ss1.fitTo(*ss1);

				RooDataHist* ss2 = new RooDataHist("ss2", "Spurious Signal Data", *spurious_signal,fixHist3);
				gauss_ss2.fitTo(*ss2);

				RooPlot* spurframe = spurious_signal->frame();
				ss->plotOn(spurframe, Name("ss"));
				ss1->plotOn(spurframe, Name("ss1"),MarkerColor(46), LineColor(46)); //ML //soft red
				ss2->plotOn(spurframe, Name("ss2"), MarkerColor(8), LineColor(8)); //Truth //soft green
				gauss_ss.plotOn(spurframe, Name("gauss_ss"));
				gauss_ss1.plotOn(spurframe, Name("gauss_ss1"), LineColor(6));  //pink 
				gauss_ss2.plotOn(spurframe, Name("gauss_ss2"), LineColor(kYellow)); 

				TCanvas *c = new TCanvas(Form("%s", bkg_names_dummy[i].Data()), Form("%s", bkg_names_dummy[i].Data()), 800, 400);
				spurframe->SetTitle(Form("%s plot & Mean Val: %3.0f", bkg_names_dummy[i].Data(), mean_arr[k]));
				spurframe->GetXaxis()->SetTitle(Form("%s", plot_name.c_str()));
				spurframe->GetYaxis()->SetTitle("N_Samples");  //Form("%d_samples", (spur->GetEntries())/bkg_names.size() ));
				spurframe->Draw();

				TLegend *l = new TLegend(0.6,0.5,0.99,0.95);
				l->SetHeader(Form("PDF =  %s", eq_dummy[i].Data()),"C");
				l->SetLineColor(kWhite);
				l->SetTextSize(0.03);

				l->AddEntry("gauss_ss", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1_dummy.c_str(), width_ss.getVal(), width_ss.getError(), mean_ss.getVal(), mean_ss.getError()), "L");
				l->AddEntry("gauss_ss1", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2_dummy.c_str(), width_ss1.getVal(), width_ss1.getError(), mean_ss1.getVal(), mean_ss1.getError()), "L");
				l->AddEntry("gauss_ss2", Form("Fit %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3_dummy.c_str(), width_ss2.getVal(), width_ss2.getError(), mean_ss2.getVal(), mean_ss2.getError()), "L");
				
				l->AddEntry("ss", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data1_dummy.c_str(), width, width_error, mean, mean_error), "LEP");
				l->AddEntry("ss1", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data2_dummy.c_str(), width1, width_error1, mean1, mean_error1), "LEP");
				l->AddEntry("ss2", Form("Data %s, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", data3_dummy.c_str(), width2, width_error2, mean2, mean_error2), "LEP");

				l->AddEntry("histogram_fold", Form("Integral Value: %.0f", integral), "");
				l->Draw();

				mean_0[k][i] = mean_ss.getVal();
				mean_1[k][i] = mean_ss1.getVal();
				mean_2[k][i] = mean_ss2.getVal();
				width_0[k][i] = width_ss.getVal();
				width_1[k][i] = width_ss1.getVal();
				width_2[k][i] = width_ss2.getVal();

				mean_Err0[k][i] = mean_ss.getError();
				mean_Err1[k][i] = mean_ss1.getError();
				mean_Err2[k][i] = mean_ss2.getError();
				width_Err0[k][i] = width_ss.getError();
				width_Err1[k][i] = width_ss1.getError();
				width_Err2[k][i] = width_ss2.getError();

				system(Form("mkdir -vp distributions/%s", compare_dummy.c_str()));
				system(Form("mkdir -vp distributions/%s/%s", compare_dummy.c_str(), type.c_str()));
				c -> SaveAs(Form("distributions/%s/%s/%s_%s_%3.0f.png", compare_dummy.c_str(), type.c_str(), bkg_names_dummy[i].Data(), type.c_str(), mean_arr[k]));
		}
	}	

	for(int i = 0; i < bkg_names_size; i++){
		//mean
		mean_mc[i] = mean_2[4][i];
		mean_error_mc[i] = mean_Err2[4][i];

		mean_nf[i] = mean_1[4][i];
		mean_error_nf[i] = mean_Err1[4][i];

		mean_truth[i] = mean_0[4][i];
		mean_error_truth[i] = mean_Err0[4][i];

		//width

		width_mc[i] = width_2[4][i];
		width_error_mc[i] = width_Err2[4][i];

		width_nf[i] = width_1[4][i];
		width_error_nf[i] = width_Err1[4][i];

		width_truth[i] = width_0[4][i];
		width_error_truth[i] = width_Err0[4][i];
	}

	//PLOT SCATTER
   TCanvas *c1 = new TCanvas("c1","Exclusion graphs examples",200,10,600,400);
   c1->SetGrid();
 
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle("Width vs. Mean For All Background PDFs");
   mg->GetXaxis()->SetTitle("Mean");
   mg->GetYaxis()->SetTitle("Width");
 
   const Int_t n = bkg_names_size;
 
   TGraph *gr1 = new TGraphErrors(n,mean_truth, width_truth, mean_error_truth, width_error_truth);
   gr1->SetMarkerColor(4);
   gr1->SetMarkerSize(1.0);
   gr1->SetMarkerStyle(21);
   gr1 -> SetName("gr1");
   
 
   TGraph *gr2 = new TGraphErrors(n,mean_nf, width_nf, mean_error_nf, width_error_nf);
   gr2->SetMarkerColor(2);
   gr2->SetMarkerSize(1.0);
   gr2->SetMarkerStyle(20);
   gr2 -> SetName("gr2");
   
   TGraph *gr3 = new TGraphErrors(n,mean_mc, width_mc, mean_error_mc, width_error_mc);
   gr3->SetMarkerColor(8);
   gr3->SetMarkerSize(1.0);
   gr3->SetMarkerStyle(22);
   gr3 -> SetName("gr3");
 
   mg->Add(gr1);
   mg->Add(gr2);
   mg->Add(gr3);
   mg->Draw("AP");

   //legend
    TLegend *l1 = new TLegend(0.1,0.7,0.5,0.90);
	l1->SetLineColor(kWhite);
	l1->SetTextSize(0.03);

	l1->AddEntry("gr1", "Truth", "lp");
	l1->AddEntry("gr2", "Normalizing Flow", "lp");
	l1->AddEntry("gr3", "Monte Carlo", "lp");
	l1->Draw();
 
   c1 -> SaveAs(Form("distributions/%s/%s_scatter.png", compare_dummy.c_str(), type.c_str()));

	//plots as shuo suggested

	double ml, mr, wl, wr;
	if (type == "SS"){
		wl = 2.8;
		wr = 4;
		ml = -3;
		mr = .5;
	}
	else if (type == "dS"){
		wl = .1;
		wr = .2;
		ml = 11.4;
		mr = 15;
	}
	else if (type == "SdS"){
		wl = .2;
		wr = .3;
		ml = -.25;
		mr = .15;
	}

	TCanvas *c2 = new TCanvas("c2","Plotting Data Tables",200,10,600,400);

	 TH1 *h1 = new TH1F("h1", "", 6,0,6);
	 TH1 *h3 = new TH1F("h3", "", 6,0,6);
	 TH1 *h5 = new TH1F("h5", "", 6,0,6);

	vector<TString> xlabels = {"Bern3", "Bern4", "Bern5", "Exp", "ExpPoly2", "ExpPoly3"};
	//vector<float> values = {-0.2233, -0.1635, -0.3884, -2.6487, -0.0120, -0.2304};
	//vector<float> errors = {0.1037, 0.1034, 0.1173, 0.0944, 0.1020, 0.1029};
	for(int j = 0; j < xlabels.size(); j++){
		h1->Fill(xlabels[j], mean_truth[j]);
		h1->SetBinError(j+1, mean_error_truth[j]);

		h3->Fill(xlabels[j], mean_mc[j]);
		h3->SetBinError(j+1, mean_error_mc[j]);

		h5->Fill(xlabels[j], mean_nf[j]);
		h5->SetBinError(j+1, mean_error_nf[j]);
	}
	h1->SetStats(0);
	h3->SetStats(0);
	h5->SetStats(0);
	h1->GetYaxis()->SetRangeUser(-5, 1);

	h1->SetTitle(Form("Mean Data %i Fold, %s", fold, type.c_str()));
    h1->GetXaxis()->SetTitle("Mean Test");
    h1->GetYaxis()->SetTitle("Events");

	h1->SetMarkerColor(4);
	h1->SetLineColor(4);
    h1->SetMarkerSize(1.0);
    h1->SetMarkerStyle(21);
    h1 -> SetName("Mean Truth");

	h3->SetMarkerColor(2);
	h3->SetLineColor(2);
    h3->SetMarkerSize(1.0);
    h3->SetMarkerStyle(20);
    h3 -> SetName("Mean MC");

	h5->SetMarkerColor(8);
	h5->SetLineColor(8);
    h5->SetMarkerSize(1.0);
    h5->SetMarkerStyle(22);
    h5 -> SetName("Mean ML");

	h1->Draw("SAME");
	h3->Draw("SAME");
	h5->Draw("SAME");

	TLegend *l2 = new TLegend(0.87,0.7,.99,0.9);
	l2->SetLineColor(kWhite);
	l2->SetTextSize(0.03);

	l2->AddEntry("Mean Truth", "Mean Truth", "lp");
	l2->AddEntry("Mean MC", "Mean MC", "lp");
	l2->AddEntry("Mean ML", "Mean ML", "lp");
	l2->Draw();

	c2-> SaveAs(Form("distributions/%s/%s_mean_scatter.png", compare_dummy.c_str(), type.c_str()));
	
	TCanvas *c3 = new TCanvas("c3","Width",200,10,600,400);
	
	TH1 *h2 = new TH1F("h1", "", 6,0,6);
	TH1 *h4 = new TH1F("h3", "", 6,0,6);
	TH1 *h6 = new TH1F("h6", "", 6,0,6);

	for(int j = 0; j < xlabels.size(); j++){
		h2->Fill(xlabels[j], width_truth[j]);
		h2->SetBinError(j+1, width_error_truth[j]);

		h4->Fill(xlabels[j], width_mc[j]);
		h4->SetBinError(j+1, width_error_mc[j]);

		h6->Fill(xlabels[j], width_nf[j]);
		h6->SetBinError(j+1, width_error_nf[j]);
	}

	h2->SetStats(0);
	h4->SetStats(0);
	h6->SetStats(0);
	h2->GetYaxis()->SetRangeUser(2.8, 5);

	h2->SetTitle(Form("Width Data %i Fold, %s", fold, type.c_str()));
    h2->GetXaxis()->SetTitle("Mean Test");
    h2->GetYaxis()->SetTitle("Events");
	h4->GetXaxis();
	h4->GetYaxis();
	h6->GetXaxis();
	h6->GetYaxis();

	h2->SetMarkerColor(4);
	h2->SetLineColor(4);
    h2->SetMarkerSize(1.0);
    h2->SetMarkerStyle(21);
    h2 -> SetName("Width Truth");

	h4->SetMarkerColor(2);
	h4->SetLineColor(2);
    h4->SetMarkerSize(1.0);
    h4->SetMarkerStyle(20);
    h4 -> SetName("Width MC");

	h6->SetMarkerColor(8);
	h6->SetLineColor(8);
    h6->SetMarkerSize(1.0);
    h6->SetMarkerStyle(22);
    h6 -> SetName("Width ML");

	h2->Draw("SAME");
	h4->Draw("SAME");
	h6->Draw("SAME");

	TLegend *l3 = new TLegend(0.87,0.7,.99,0.9);
	l3->SetLineColor(kWhite);
	l3->SetTextSize(0.03);

	l3->AddEntry("Width Truth", "Width Truth", "lp");
	l3->AddEntry("Width MC", "Width MC", "lp");
	l3->AddEntry("Width ML", "Width ML", "lp");
	l3->Draw();

	c3-> SaveAs(Form("distributions/%s/%s_width_scatter.png", compare_dummy.c_str(), type.c_str()));



		//----PRINT OUT TABLES----//
  	ofstream MyFile(Form("distributions/%s/%s_mean.txt", compare_dummy.c_str(),type.c_str()));
	ofstream MyFile2(Form("distributions/%s/%s_width.txt", compare_dummy.c_str(),type.c_str()));

	cout << "" << endl;

		MyFile << Form("%s Fit: ", plot_name.c_str()) << endl;
		for(int k = 0; k < mean_size; k++){
			if (mean_arr[k] != 125.0) continue;

			MyFile << "Mean Value: " << mean_arr[k] << endl;

			MyFile << left << setw(20) << "" << left << setw(20) << Form("Mean %s", data3_dummy.c_str()) << left << setw(20) << Form("Mean %s", data2_dummy.c_str()) << left << setw(20) << Form("Mean %s", data1_dummy.c_str()) << endl;
			MyFile << "--------------------------------------------------------------------------" << endl;

			//cout << "Mean value of " << mean_val[k] << endl;
			for(int i = 0; i < bkg_names_size; i++){
				//if (bkg_names[i] == "Dijet") continue;
				MyFile << left << setw(20) <<  bkg_names_dummy[i] << left << setw(20) << Form("%.4f ± %.4f", mean_2[k][i], mean_Err2[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_1[k][i], mean_Err1[k][i]) << left << setw(20) << Form("%.4f ± %.4f", mean_0[k][i], mean_Err0[k][i]) << endl;
				MyFile << "--------------------------------------------------------------------------" << endl;
			}
		}
	// Close the file
  	MyFile.close();
  
	cout << "" << endl;
	MyFile2 << Form("%s Fit: ", plot_name.c_str()) << endl;
		for(int k = 0; k < mean_size; k++){
			if (mean_arr[k] != 125.0) continue;

			MyFile2 << "Mean Value: " << mean_arr[k] << endl;

			MyFile2 << left << setw(20) << "" << left << setw(20) << Form("Width %s", data3_dummy.c_str()) << left << setw(20) << Form("Width %s", data2_dummy.c_str()) << left << setw(15) << Form("Width %s", data1_dummy.c_str()) << endl;
			MyFile2 << "--------------------------------------------------------------------------" << endl;

			//cout << "Mean value of " << mean_val[k] << endl;
			for(int i = 0; i < bkg_names_size; i++){
				//if (bkg_names[i] == "Dijet") continue;
				MyFile2 << left << setw(20) <<  bkg_names_dummy[i] << left << setw(20) << Form("%.4f ± %.4f", width_2[k][i], width_Err2[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_1[k][i], width_Err1[k][i]) << left << setw(20) << Form("%.4f ± %.4f", width_0[k][i], width_Err0[k][i]) << endl;
				MyFile2 << "--------------------------------------------------------------------------" << endl;
			}
		}
	// Close the file
  	MyFile2.close();	

}

void spuriousPlots(float value, int fold_value){
  text();

  float which_study = value;
  int fold = fold_value;

  string rootName1, rootName2, rootName3, compare, data1, data2, data3, fit1, fit2;

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
		compare = Form("MCvMLvTruth_%iFold", fold);
		data1 = "MC";
		data2 = "ML";
		data3 = "truth";
		min_spur = -20;
        max_spur = 20;
		min_ds = 10;
		max_ds = 25;
		min_sds = -2;
		max_sds = 2;
  }

    //define bkg names
	vector<TString> bkg_names;
	bkg_names.push_back("Bern3");
	bkg_names.push_back("Bern4");
	bkg_names.push_back("Bern5");
	bkg_names.push_back("Exponential");
	bkg_names.push_back("ExpPoly2");
	bkg_names.push_back("ExpPoly3");

	//equations used:
	vector<TString> eq;
	eq.push_back("N#sum^{3}_{i=0}a_{i}B_{in}");
	eq.push_back("N#sum^{4}_{i=0}a_{i}B_{in}");
	eq.push_back("N#sum^{5}_{i=0}a_{i}B_{in}");
	eq.push_back("e^{a_{0}mass}");
	eq.push_back("exp#left(a_{0}#left(#frac{x-100}{100}#right) + a_{1}#left(#frac{x-100}{100}#right)^{2}#right)");
	eq.push_back("exp#left(a_{0}#left(#frac{x-100}{100}#right) + a_{1}#left(#frac{x-100}{100}#right)^{2} + a_{2}#left(#frac{x-100}{100}#right)^{3}#right)");
  
//open TFILES
int size = 9;
double mean_val[size];
double count = 121.0;
for (int j = 0; j < size; j++) {
	mean_val[j] = count;
    count = count + 1;
}

string plot_type_spur = "SS";
string plottingName_spur = "Spurious Signal";
string spur0 = "spur";

string plot_type_ds = "dS";
string plottingName_ds = "Delta S";
string spur_ds = "spur_ds";

string plot_type_sds = "SdS";
string plottingName_sds = "S/deltaS";
string spur_sds = "spur_sds";

process_data(min_ds, max_ds, compare, eq, bkg_names, bkg_names.size(), mean_val, size, data1, data2, data3, plot_type_ds, plottingName_ds, spur_ds, rootName1, rootName2, rootName3, fold);

process_data_gauss(min_sds, max_sds, compare, eq, bkg_names, bkg_names.size(), mean_val, size, data1, data2, data3, plot_type_sds, plottingName_sds, spur_sds, rootName1, rootName2, rootName3, fold);

//For spurious signal with gaussian fit:

process_data_gauss(min_spur, max_spur, compare, eq, bkg_names, bkg_names.size(), mean_val, size, data1, data2, data3, plot_type_spur, plottingName_spur, spur0, rootName1, rootName2, rootName3, fold);



  return 0;
}
