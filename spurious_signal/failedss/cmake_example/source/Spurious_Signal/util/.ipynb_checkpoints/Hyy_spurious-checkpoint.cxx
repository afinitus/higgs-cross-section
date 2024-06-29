//NEW HYY CXX 
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include "THStack.h"
#include "TLegend.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooDataHist.h"
#include "RooBernstein.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooAbsPdf.h"
#include "TString.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TKey.h"
#include "RooGenericPdf.h"
#include "RooWorkspace.h"
#include "TMath.h"
#include <iomanip>
#include "TSystem.h"

// STL include(s):
#include <iostream>
#include <sstream>

// ROOT include(s):
#include "TChain.h"
#include "TFile.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"
#include "TH1F.h"

// Local include(s):
//#include "/global/cfs/projectdirs/atlas/juliet/spurious-signal/roofit/HGamma_Package/source/HGamCore/HGamAnalysisFramework/HGamAnalysisFramework/Config.h"
//#include "/global/cfs/projectdirs/atlas/juliet/spurious-signal/roofit/HGamma_Package/source/HGamCore/HGamAnalysisFramework/HGamAnalysisFramework/HGamCommon.h"
#include "/global/cfs/projectdirs/atlas/juliet/spurious-signal/cmake_example/source/Spurious_Signal/inc/RooTwoSidedCBShape.h"

using namespace RooFit;
using namespace std;

//6 bkg_pdfs & 9 steps 
//void Hyy_spurious(string bkgPDF_name){    //double mean_val){ //just this: bkg_PDF){
int main( int argc, char **argv ){

  TString bkgPDF_name = (argv[1]);
  TString rootfile = (argv[2]);
  TString sigFile = (argv[3]);

  cout << "This is the root file print out: " << rootfile << endl;
  
  int min_spur, min_spur_ds, min_spur_sds;
  int max_spur, max_spur_ds, max_spur_sds;
  TString rootName;
  if (rootfile == "smooth.txt" || rootfile == "smooth_gr40.txt" || rootfile == "smooth_le18.txt" || rootfile == "smooth_b1840.txt" || rootfile == "smooth_inc_half.txt" || rootfile == "smooth_pre.txt" || rootfile == "smooth_ori.txt"){
          rootName = "smooth";
          min_spur = -15;
          max_spur = 15;
  }
  else if (rootfile == "unsmooth.txt" || rootfile == "unsmooth_gr40.txt" || rootfile == "unsmooth_le18.txt" || rootfile == "unsmooth_b1840.txt" || rootfile == "unsmooth_inc_half.txt"){
          rootName = "norm";
          min_spur = -15;
          max_spur = 15;
  }
  else if (rootfile == "MC.txt"){ //Monte Carlo method
        rootName = "MC";
  }
  else if (rootfile == "ML.txt"){ //normalizing flow
        rootName = "ML";
  }
  else if (rootfile == "truth.txt"){ //normalizing flow
        rootName = "truth";
  }

  if(rootfile == "truth.txt" || rootfile == "ML.txt" || rootfile == "MC.txt"){
        min_spur = -25;
        max_spur = 25;

        min_spur_ds = 10;
        max_spur_ds = 25;

        min_spur_sds = -5;
        max_spur_sds = 5;
  }

        int spur_center = 50; //was 50 for -20, 20 range
        int ds_bins = 200;
  cout << "This is the root name: " << rootName << endl;

  /*TString sigName;
  if (rootfile == "sig_pt_le100.txt"){
          sigName = "pt_le100";
  }
  else if (rootfile == "sig_pt_gr50.txt"){
          sigName = "pt_gr50";
  }*/

  ifstream infile(rootfile, ios::in);
  string line;
  vector<TString> input_path;
  while (getline(infile, line)){
    input_path.push_back(line);  // can be line.c_str()
  }
  infile.close();

  int input_size = input_path.size();

  cout<<input_path[0]<<endl;

  ifstream infile2(sigFile, ios::in);
  string line2;
  vector<TString> input_path2;
  while (getline(infile2, line2)){
    input_path2.push_back(line2);  // can be line.c_str()
  }
  infile2.close();

  cout<<input_path2[0]<<endl;


	//TIMER
  TStopwatch timer;
  timer.Start();

TFile * f1 = TFile::Open(input_path[0]);

int fileSize = f1->GetListOfKeys()->GetEntries();
cout << "fileSize: " << fileSize << endl;

TIter next(f1->GetListOfKeys()); //key to files
TKey* key;
int count = 0;
string histos[fileSize];
while ((key=(TKey*)next())) {
      histos[count] = key->GetName();
      //cout << "histo " << count + 1 << ": " << histos[count] << endl;
      count += 1;
  
      //printf("key: %s", key->GetName());
      //cout << endl;
      //cout << "Histo " << count << ": " << key->GetName() << endl;
}
int min = 0;

//make roorealvar pointers:
RooRealVar* mass = new RooRealVar("mass", "", 125, 105, 160);
RooRealVar *a0;
RooRealVar *a1;
RooRealVar *a2;
RooRealVar *a3;
RooRealVar *a4;
RooRealVar t("t", "t", 1, 1, 1);
RooAbsPdf *bkg_pdf;
RooPlot* spurframe;

vector<TString> bkg_names;
bkg_names.push_back("Bern3");
bkg_names.push_back("Bern4");
bkg_names.push_back("Bern5");
bkg_names.push_back("ExpPoly2");
bkg_names.push_back("Exponential");
bkg_names.push_back("ExpPoly3");

int bkg_size = bkg_names.size();

int which_pdf;
        
        if (bkgPDF_name == "Bern3"){
                which_pdf = 0;
        }
        else if (bkgPDF_name == "Bern4"){
                which_pdf = 1;
        }
        else if (bkgPDF_name == "Bern5"){
                which_pdf = 2;
        }
        else if (bkgPDF_name == "ExpPoly2"){
                which_pdf = 3;
        }
        else if (bkgPDF_name == "Exponential"){
                which_pdf = 4;
        }
        else if (bkgPDF_name == "ExpPoly3"){
                which_pdf = 5;
        }

int mean_size = 3;
double mean_val[mean_size];
double counting = 1.5;
        for (int j = 0; j < mean_size; j++) {
                mean_val[j] = counting;
                counting = counting + 0.5;
                //couting << "sig" << j << ": " << mean_val[j] << endl;
}

//Histos: 
//2d vector of 1d histos
map<int, map<int, TH1D*>> spur_list_map; 
for (int i=0; i<bkg_size; i++) { 
        for (int k = 0; k < mean_size; k++){
	        spur_list_map[i][k] = new TH1D(Form("spur_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Spurious Signal",spur_center, min_spur, max_spur);
	        //spur_list.push_back(spur);  
        }
}

//2D vector for spurious signal error (ds)
map<int, map<int, TH1D*>> spur_ds_map; 
for (int i=0; i<bkg_size; i++) { 
        for (int k = 0; k < mean_size; k++){
	        spur_ds_map[i][k] = new TH1D(Form("spur_ds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Spurious Signal Error",ds_bins, min_spur_ds, max_spur_ds);
	        //spur_list.push_back(spur);  
        }
}
//2D vector for spurious signal devided by its relative error (S/ds)
map<int, map<int, TH1D*>> spur_sds_map; 
for (int i=0; i<bkg_size; i++) { 
        for (int k = 0; k < mean_size; k++){
	        spur_sds_map[i][k] = new TH1D(Form("spur_sds_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Spurious Signal Total Error",50, min_spur_sds, max_spur_sds);
	        //spur_list.push_back(spur);  
        }
}

map<int, map<int, TH1D*>> chiSq_list_map;
for (int i=0; i<bkg_size; i++) {
        for (int k = 0; k < mean_size; k++){
                chiSq_list_map[i][k] = new TH1D(Form("chiSq_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Chi2",1000, -2, 15); //10,0,2
                //chiSq_list.push_back(chiSq);
        }
}
map<int, map<int, TH1D*>> chiSq_prob_list_map;
for (int i=0; i<bkg_size; i++) {
        for (int k = 0; k < mean_size; k++){
                chiSq_prob_list_map[i][k] = new TH1D(Form("chiSq_prob_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Chi2 Probability",100, 0, 1);  //10,0,2
                //chiSq_prob_list.push_back(chiSq_prob);
        }
}
//max histos 
vector<TH1D*> maxSpur_list; 
for (int i=0; i<bkg_size; i++) { 
        TH1D *maxSpur = new TH1D(Form("maxSpur_%s",bkg_names[i].Data()),"Spurious Signal",50, -15, 15); 
	maxSpur_list.push_back(maxSpur);  
}
vector<TH1D*> maxChiSq_list;
for (int i=0; i<bkg_size; i++) {
        TH1D *maxChiSq = new TH1D(Form("maxChiSq_%s",bkg_names[i].Data()),"Chi2",100, 0, 10); //10,0,2
        maxChiSq_list.push_back(maxChiSq);
}
//delta S vector
vector<TH1D*> error_list;
for (int i=0; i<bkg_size; i++) {
        TH1D *error = new TH1D(Form("error_%s",bkg_names[i].Data()),"Delta S",100, 10, 16); //10,0,2
        error_list.push_back(error);
}
//Error vector
vector<TH1D*> total_error_list;
for (int i=0; i<bkg_size; i++) {
        TH1D *total_error = new TH1D(Form("total_error_%s",bkg_names[i].Data()),"Total Error",100, -1, 3); //10,0,2
        total_error_list.push_back(total_error);
}

//Define SS and error arrays 
double nsignal[bkg_names.size()][fileSize][mean_size];
double deltaS[bkg_names.size()][fileSize][mean_size];
double error[bkg_names.size()][fileSize][mean_size];
double chi2[bkg_names.size()][fileSize][mean_size];
double prob[bkg_names.size()][fileSize][mean_size];

//open signal pdf file:
TFile *f2 = TFile::Open(input_path2[0]);
//TFile *f2 = TFile::Open("DSCB_workspace_mod.root");
RooWorkspace* w = (RooWorkspace*) f2->Get("signalPDF_ws");
//int par[9] = {3, 4, 5, 2, 1, 2};
int par[bkg_names.size()];

//loop through all histos

//only produce 10 myy distributions:
int x = fileSize/10;
int counter10 = 0;
for(int k = 0; k < mean_size; k++){
        if (mean_val[k] != 125.0) continue;
for(int i = which_pdf; i < which_pdf+1; i++){
        cout << "PDF value: " << i << " and " << which_pdf << endl;
	if(bkg_names[i]=="Bern3") {
                a0 = new RooRealVar("a0","a0", 0,-10, 10);
                a1 = new RooRealVar("a1","a1", 0,-10, 10);
                a2 = new RooRealVar("a2","a2", 0,-10, 10);
                bkg_pdf = new RooBernstein("Bern3", "Bern3", *mass, RooArgList(*a0, *a1, *a2, t));
        }
        else if (bkg_names[i] == "Bern4") {
                a0 = new RooRealVar("a0","a0", 0,-10, 10);
                a1 = new RooRealVar("a1","a1", 0,-10, 10);
                a2 = new RooRealVar("a2","a2", 0,-10, 10);
                a3 = new RooRealVar("a3","a3", 0,-10, 10);
                bkg_pdf = new RooBernstein("Bern4", "Bern4", *mass, RooArgList(*a0, *a1, *a2, *a3, t));
        }
        else if (bkg_names[i] == "Bern5") {
                a0 = new RooRealVar("a0","a0", 0,-10, 10);
                a1 = new RooRealVar("a1","a1", 0,-10, 10);
                a2 = new RooRealVar("a2","a2", 0,-10, 10);
                a3 = new RooRealVar("a3","a3", 0,-10, 10);
                a4 = new RooRealVar("a4","a4", 0,-10, 10);
                bkg_pdf = new RooBernstein("Bern5", "Bern5", *mass, RooArgList(*a0, *a1, *a2, *a3, *a4, t));
        }
        else if (bkg_names[i] == "ExpPoly2") { //remove this
                a0 = new RooRealVar("a0","a0", 0,-20, 20);
                a1 = new RooRealVar("a1","a1", 0,-20, 20);
                bkg_pdf = new RooGenericPdf("ExpPoly2", "exp((mass - 100)/100*(a0 + a1*(mass - 100)/100))", RooArgSet(*mass, *a0, *a1));
        }
        else if (bkg_names[i] == "Exponential") {
                a0 = new RooRealVar("a0","a0", 0,-20, 20);
                bkg_pdf = new RooGenericPdf("Exponential", "exp(a0*mass)", RooArgSet(*mass, *a0));
        }
        else if (bkg_names[i] == "ExpPoly3") {
                a0 = new RooRealVar("a0","a0", 0,-20, 20);
                a1 = new RooRealVar("a1","a1", 0,-20, 20);
                a2 = new RooRealVar("a2", "a2", 0, -20,20);
                bkg_pdf = new RooGenericPdf("ExpPoly3", "exp((mass - 100)/100*(a0 + a1*(mass - 100)/100 + a2*(mass - 100)/100*(mass - 100)/100))", RooArgSet(*mass, *a0, *a1, *a2));
        }
	//find the number of parameters
	RooArgSet  m_bkgParameters;
        m_bkgParameters.add(*bkg_pdf->getParameters(RooArgSet()));
        int npars = m_bkgParameters.getSize();
        if(i <= 2){
                par[i] = npars - 2;
        }
        else{
                par[i] = npars - 1;
        }
	//cout << "J Param " << i << ": " << par[i] << endl;	
	
	//--Define parameters for twosided CBShape--
        double mean = 125; //GeV
        double width = mean_val[k]; //w->var("sigwidth")->getVal(); //.5, 1, 2.5, 2, 3
        double ahi = w->var("alphaHi")->getVal();
        double alo = w->var("alphaLo")->getVal();
        double nlo = w->var("nLo")->getVal();
        double nhi = w->var("nHi")->getVal();

        RooRealVar* sigmean = new RooRealVar("sigmean", "mean", mean, mean, mean);
        RooRealVar* sigwidth = new RooRealVar("sigwidth","width",width,width,width) ;
        RooRealVar* alphaLo = new RooRealVar("alphaLo", "alphaLo", alo, alo, alo);
        RooRealVar* alphaHi = new RooRealVar("alphaHi", "alphaHi", ahi, ahi, ahi);
        RooRealVar* nLo = new RooRealVar("nLo", "nLo", nlo, nlo, nlo);
        RooRealVar* nHi = new RooRealVar("nHi", "nHi", nhi, nhi, nhi);
        //--USE original signal PDF
        RooTwoSidedCBShape* signal_PDF = new RooTwoSidedCBShape("signal_PDF", "signal_PDF", *mass,*sigmean,*sigwidth,*alphaLo,*nLo,*alphaHi,*nHi);
        //RooGaussian* signal_PDF = new RooGaussian("signal_PDF", "", *mass, *sigmean, *sigwidth);

        RooRealVar nsig("nsig","#signal events",0, -1000, 1000) ;
        RooRealVar nbkg("nbkg","#background events",10,0,1000000) ;

	// //only produce 10 myy distributions:
        // int x = fileSize/10;
        // int counter10 = 0; 
	for(int j = 0; j < fileSize; j++){

		//if (bkg_names[i] != "Bern3") { continue; }
		//if(j >= 10) continue;
	
		//get each histo and use it
		TH1* histo = (TH1*) f1->Get(Form("%s", histos[j].c_str()));
                RooDataHist *data = new RooDataHist("data","dataset with mes",*mass,histo);

		int nbins = histo->GetNbinsX();
		cout << "Histo bins: " << nbins << endl;

		RooAddPdf sum("sum","bkg_pdf+signal_PDF", RooArgList(*signal_PDF, *bkg_pdf),RooArgList(nsig,nbkg)) ;
		sum.fitTo(*data,Minimizer("Minuit2", "migrad"), Save(), Offset(), Range(105, 160));  //error ~ replace extended with range
		
		nsignal[i][j][k] = nsig.getVal();
		deltaS[i][j][k] = nsig.getError();
		error[i][j][k] = nsig.getVal()/nsig.getError();

		//PLOT STUFF
		RooPlot* massframe = mass->frame() ;
		data->plotOn(massframe);
		sum.plotOn(massframe) ;
		sum.plotOn(massframe,Components(*bkg_pdf),LineStyle(kDashed)) ;

		//--> chi2/dof`
                chi2[i][j][k] = massframe->chiSquare(par[i]);
                cout << "chi2 test: " << chi2[i][j][k] << endl;
                //--> chi2 Probability
                prob[i][j][k] = TMath::Prob(chi2[i][j][k] * (nbins - par[i]), nbins - par[i]);

                cout << "counter10 is equal to " << counter10 << endl;
                if(j == counter10){
                        cout << "Yes I am most def running! " << endl;
                        counter10 += x;

                        string myy_hists = "myy_histos";
                        system(Form("mkdir -vp %s", myy_hists.c_str()));
                        string hist_type = Form("%s_myy_%i_fold", rootName.Data(), fileSize);
                        system(Form("mkdir -vp %s/%s/%s_plots", myy_hists.c_str(),hist_type.c_str(), bkg_names[i].Data()));
                        TCanvas *c = new TCanvas(Form("%s", histos[j].c_str()), Form("%s", histos[j].c_str()), 800, 400);
                        c->Clear();
                        
                        massframe->GetXaxis()->SetTitle("m_{#gamma#gamma} (GeV)");
                        massframe->GetYaxis()->SetTitle("Events");
                        massframe->SetTitle(Form("%s_plot: %s", bkg_names[i].Data(), histos[j].c_str()));
                        massframe->Draw();
                        
                        TLegend* l = new TLegend(0.65,0.73,0.86,0.87);
                        l->SetLineColor(kBlack);
                        l->SetTextSize(0.05);
                        l->SetBorderSize(0);
                        l->AddEntry("", Form("SS: %f", nsignal[i][j][k]), "");
                        l->AddEntry("", Form("Chi2: %f", chi2[i][j][k]), "");
                        l->AddEntry("", Form("Prob(chi2): %f", prob[i][j][k]), "");
                        l->Draw();

		        //save in seperate directories
		        c->SaveAs(Form("%s/%s/%s_plots/%s.png", myy_hists.c_str(), hist_type.c_str(), bkg_names[i].Data(), histos[j].c_str()));	
                }
        }
	for(int s = 0; s < fileSize; s++){
 		spur_list_map[i][k] -> Fill(nsignal[i][s][k]);
                spur_ds_map[i][k] -> Fill(deltaS[i][s][k]);
                spur_sds_map[i][k] -> Fill(error[i][s][k]);
	}
	for(int s = 0; s < fileSize; s++){
		chiSq_list_map[i][k] -> Fill(chi2[i][s][k]);
	}
	for(int s = 0; s < fileSize; s++){
                chiSq_prob_list_map[i][k] -> Fill(prob[i][s][k]);
	}

}       
        
}
for(int i = which_pdf; i < which_pdf+1; i++){
	for(int j = 0; j < fileSize; j++){
                for(int k = 0; k < mean_size; k++){
                        if (j >= 2) break;
                        cout << "mean of: " << mean_val[k] << endl; 
                        cout << nsignal[i][j][k] << " < -- Sig " << endl; 
                        cout << deltaS[i][j][k] << " < -- Symmetric Error " << endl; 
                }
        }
}
//Table:
/*for(int j = 0; j < fileSize ; j++){
        cout << "Histo number: " << j << endl;
        for(int i = which_pdf; i < which_pdf+1; i++){
		cout << right << setw(20) << bkg_names[i] << endl;
		cout << left << setw(10) << "SIGMEAN" << left << setw(10) << "SIG VAL" << left << setw(10) << "Delta_S" << left << setw(10) << "S/DS %" << endl;
	        for(int k = 0; k < mean_size; k++){	
			cout << left << setw(10) << mean_val[k] << left << setw(10) << nsignal[i][j][k] << left << setw(10) << deltaS[i][j][k] << left << setw(10) << error[i][j][k]*100 << "%" << endl;		 
	        }
        }
}*/

//SS VALUES
/*for(int j = 0; j < bkg_names.size(); j++){
	cout << "Background PDF: " << bkg_names[j] << endl;
	cout << "============================" << endl;
	for(int i = 0; i < fileSize; i++){
		cout << histos[i] << " SS: " << nsignal[j][i] << endl;
	}
	cout << "============================" << endl;
}*/

//CHI2 VALUES
/*for(int j = 0; j < bkg_names.size(); j++){
        cout << "Background PDF: " << bkg_names[j] << endl;
        cout << "============================" << endl;
        for(int i = 0; i < fileSize; i++){
                cout << histos[i] << " CHI2: " << chi2[j][i] << endl;
        }
        cout << "============================" << endl;
}*/

//Find Max(S):
/*int ind;
//Find Largest Signal per each Bkg PDF test 
double largest[fileSize];
for(int j = 0; j < fileSize; j++){
        largest[j] = abs(nsignal[0][j]);}
	
int indexLar[6] = {0, 0, 0, 0, 0, 0};
int maxS = nsignal[0][0]; 
for(int i = 0; i < bkg_names.size(); i++){
	for(int j = 0; j < fileSize; j++){
		if(largest[j] < abs(nsignal[i][j])){
                        largest[j] = abs(nsignal[i][j]);
			indexLar[i] = i;
		}
	}
}

int index0 = 0;
string pass[bkg_names.size()];
double smallestLar = largest[0];
for(int r = 0; r < bkg_names.size(); r++){
        ind = indexLar[r];
        if(error[r][ind] > .4){
                pass[r] = "FAIL";
                continue;
        }
        else
        {
                pass[r] = "PASS";
        }
}

int indexPassed[bkg_names.size()];
int counter = 0;
//pick the pdf to use:
for(int i = 0; i < bkg_names.size(); i++){
        if(pass[i] == "PASS"){
                indexPassed[counter] = i;
                counter = counter + 1;
        }
}
int test = 0;
for(int t = 0; t < counter; t++){
        test = indexPassed[t];
        cout << "indexPassed value: " << indexPassed[t] << " and the pdf will be: " << bkg_names[test] << endl;
}

int first = indexPassed[0];
int winner = par[first];
int indexWinner = first;
for(int i = 0; i < counter; i++){
        first = indexPassed[i];
        if(winner > par[first]){
                winner = par[first];
                indexWinner = first;
        }
}

//---FINAL RESULTS TABLE---//
cout << "=== FINAL RESULTS ===" << endl;
cout << left << setw(20) << "Name" << left << setw(20) << "Max(S/deltaS)[%]" << left << setw(20) << "Max(S)" << left << setw(20) << "Chi2/dof" << left << setw(20) << "Prob(chi2)" << left << setw(20) << "nPars" << left << setw(20) << "Result" << endl;
for(int i = 0; i < bkg_names.size(); i++){
        ind = indexLar[i];
        cout << left << setw(20) << bkg_names[i] << left << setw(20) << error[i][ind]*100 << left << setw(20) << largest[i] << left << setw(20) << chi2[i][ind] << left << setw(20) << prob[i][ind] << left << setw(20) << par[i] << left << setw(20) << pass[i] << endl;

}
cout << "The choosen PDF is: " << bkg_names[indexWinner] << endl;*/

//New Filling for highest spurious signal:
//Find Largest Signal per each Bkg PDF test 
cout << "test0" << endl; 
double largest[bkg_size][fileSize];
double largestChi[bkg_size][fileSize];
double largestErr[bkg_size][fileSize];
double largest_tot_err[bkg_size][fileSize];
for (int i = which_pdf; i < which_pdf+1; i ++){
        for(int j = 0; j < fileSize; j++){
	        largest[i][j] = abs(nsignal[i][j][0]);
                largestErr[i][j] = abs(deltaS[i][j][0]);
                largestChi[i][j] = abs(chi2[i][j][0]);
                //cout << "Signal: " << nsignal[i][j][0] << " and error: " << deltaS[i][j][0] << endl;
                largest_tot_err[i][j] = abs(nsignal[i][j][0]/deltaS[i][j][0]);
        }
}
cout << "test1" << endl;

int indexLar[6] = {0, 0, 0, 0, 0, 0};
int indexLarChi[6] = {0, 0, 0, 0, 0, 0};
for(int i = which_pdf; i < which_pdf+1; i++){
	for(int j = 0; j < fileSize; j++){
                for(int k = 0; k < mean_size; k++){
                        if(largest[i][j] < abs(nsignal[i][j][k])){
                                largest[i][j] = abs(nsignal[i][j][k]);
                                largestErr[i][j] = abs(deltaS[i][j][k]);
                                largest_tot_err[i][j] = abs(nsignal[i][j][k]/deltaS[i][j][k]);
                                indexLar[i] = i;
                        }
                        if(largestChi[i][j] < abs(chi2[i][j][k])){
                                largestChi[i][j] = abs(chi2[i][j][k]);
                                indexLarChi[i] = i;
                        }
		}
	}
}
cout << "test2" << endl;
/*for(int i = which_pdf; i < which_pdf+1; i++){
	for(int j = 0; j < fileSize; j++){
                        cout << "Max SS for histo " << j << " at bkg pdf - " << bkg_names[i] << ": " << largest[i][j] << endl;
        }
}*/
for(int i = which_pdf; i < which_pdf+1; i++){
        for(int j = 0; j < fileSize; j++){
                        maxSpur_list[i] -> Fill(largest[i][j]);
        }
        for(int j = 0; j < fileSize; j++){
                        maxChiSq_list[i] -> Fill(largestChi[i][j]);
        }
        //fill delta S - error
        for(int j = 0; j < fileSize; j++){
                         error_list[i] -> Fill(largestErr[i][j]);
        }
        for(int j = 0; j < fileSize; j++){
                         total_error_list[i] -> Fill(largest_tot_err[i][j]);
        }
}  
cout << "test3" << endl;
cout <<"which pdf: " << which_pdf << endl;      

//END OF TIMER
timer.Stop();
timer.Print();
cout << "RealTime : " << timer.RealTime()/60.0 << " minutes" << endl;
cout << "RealTime : " << timer.RealTime() << " seconds" << endl;
cout << "CPUTime  : " << timer.CpuTime()/60.0 << " minutes" << endl;
cout << "Yes DONE" << endl; 

system(Form("mkdir -vp %s_rootFiles", rootName.Data()));

TFile ffile(Form("%s_rootFiles/%s_all_%s.root", rootName.Data(), rootName.Data(), bkgPDF_name.Data()),"RECREATE","Demo ROOT file with histograms & trees");
//TFile ffile(Form("smooth_all_%s.root", bkgPDF_name.c_str()),"RECREATE","Demo ROOT file with histograms & trees");
//TFile ffile(Form("%3.0f_smooth.root", mean_val),"RECREATE","Demo ROOT file with histograms & trees");
//TFile ffile("test.root","RECREATE","Demo ROOT file with histograms & trees"); 


// SS per mean value per bkg PDF
for(int i = which_pdf; i < which_pdf +1; i++){
        for(int k = 0; k < mean_size; k++){
                spur_list_map[i][k]->Clone();
        }
}
// delta S per mean value per bkg PDF
for(int i = which_pdf; i < which_pdf +1; i++){
        for(int k = 0; k < mean_size; k++){
                spur_ds_map[i][k]->Clone();
        }
}
// S/deltaS per mean value per bkg PDF
for(int i = which_pdf; i < which_pdf +1; i++){
        for(int k = 0; k < mean_size; k++){
                spur_sds_map[i][k]->Clone();
        }
}
// Chi2 per mean value per bkg PDF
for(int i = which_pdf; i < which_pdf +1; i++){
        for(int k = 0; k < mean_size; k++){
                chiSq_list_map[i][k]->Clone();
        }
}
//Prob(chi2) per mean value per bkg PDF
for(int i = which_pdf; i < which_pdf +1; i++){
        for(int k = 0; k < mean_size; k++){
                chiSq_prob_list_map[i][k]->Clone();
        }
}
//max SS
for(int i = 0; i < bkg_size; i++){
        maxSpur_list[i]->Clone();
}
for(int i = 0; i < bkg_size; i++){
        maxChiSq_list[i]->Clone();
}
//delta S:
for(int i = 0; i < bkg_size; i++){
        error_list[i]->Clone();
}
//total error
for(int i = 0; i < bkg_size; i++){
        total_error_list[i]->Clone();
}

ffile.Write();
ffile.Close();

return 0;
}
