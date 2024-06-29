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
  TString rootfileMC = (argv[2]);
  TString rootfileML = (argv[3]);
  TString rootfileT = (argv[4]);
  TString sigFile = (argv[5]);
  
  int min_spur;
  int max_spur;
  TString rootNameML, rootNameMC, rootNameT;

  if (rootfileMC == "MC.txt"){ //Monte Carlo method
        rootNameMC = "MC";
        min_spur = -2;
        max_spur = 11;
  }
  else if (rootfileML == "ML.txt"){ //normalizing flow
        rootNameML = "ML";
        min_spur = -2;
        max_spur = 11;
  }
  else if (rootfileT == "truth.txt"){ //normalizing flow
        rootNameT = "T";
        min_spur = -2;
        max_spur = 11;
  }

  ifstream infile(rootfileMC, ios::in);
  string line;
  vector<TString> input_path;
  while (getline(infile, line)){
    input_path.push_back(line);  // can be line.c_str()
  }
  infile.close();
   
  int input_size = input_path.size();

  ifstream infile3(rootfileML, ios::in);
  string line3;
  vector<TString> input_path3;
  while (getline(infile3, line3)){
    input_path3.push_back(line3);  // can be line.c_str()
  }
  infile3.close();
  cout<<input_path3[0]<<endl;

  ifstream infile4(rootfileT, ios::in);
  string line4;
  vector<TString> input_path4;
  while (getline(infile4, line4)){
    input_path4.push_back(line4);  // can be line.c_str()
  }
  infile4.close();

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
TFile * f3 = TFile::Open(input_path3[0]);
TFile * f4 = TFile::Open(input_path4[0]);

int fileSize = f1->GetListOfKeys()->GetEntries();
cout << "fileSize: " << fileSize << endl;

int fileSize2 = f3->GetListOfKeys()->GetEntries();
cout << "fileSize2: " << fileSize2 << endl;

int fileSize3 = f4->GetListOfKeys()->GetEntries();

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

TIter next2(f3->GetListOfKeys()); //key to files
TKey* key2;
int count_2 = 0;
string histos2[fileSize2];
while ((key2=(TKey*)next2())) {
      histos2[count_2] = key2->GetName();
      count_2 += 1;
}

TIter next3(f4->GetListOfKeys()); //key to files
TKey* key3;
int count_3 = 0;
string histos3[fileSize3];
while ((key3=(TKey*)next3())) {
      histos3[count_3] = key3->GetName();
      count_3 += 1;
}

cout << "test1" << endl;
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

vector<TString> eq;
	eq.push_back("N#sum^{3}_{i=0}a_{i}B_{in}");
	eq.push_back("N#sum^{4}_{i=0}a_{i}B_{in}");
	eq.push_back("N#sum^{5}_{i=0}a_{i}B_{in}");
	eq.push_back("exp#left(a_{0}#left(#frac{x-100}{100}#right) + a_{1}#left(#frac{x-100}{100}#right)^{2}#right)");
	eq.push_back("e^{a_{0}mass}");
	eq.push_back("exp#left(a_{0}#left(#frac{x-100}{100}#right) + a_{1}#left(#frac{x-100}{100}#right)^{2} + a_{2}#left(#frac{x-100}{100}#right)^{3}#right)");

int bkg_size = bkg_names.size();
cout << "test2" << endl;
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

int mean_size = 9;
double mean_val[mean_size];
double counting = 121.0;
        for (int j = 0; j < mean_size; j++) {
                mean_val[j] = counting;
                counting = counting + 1;
                //couting << "sig" << j << ": " << mean_val[j] << endl;
}

int min_spur_pull = -10;
int max_spur_pull = 10;

//Histos: 
//2d vector of 1d histos
map<int, map<int, TH1D*>> spur_map; 
for (int i=0; i<bkg_size; i++) { 
        for (int k = 0; k < mean_size; k++){
	        spur_map[i][k] = new TH1D(Form("spur_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Spurious Signal",50, min_spur_pull, max_spur_pull);
	        //spur_list.push_back(spur);  
        }
}

map<int, map<int, TH1D*>> spur_map2; 
for (int i=0; i<bkg_size; i++) { 
        for (int k = 0; k < mean_size; k++){
	        spur_map2[i][k] = new TH1D(Form("spur2_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Spurious Signal",50, min_spur_pull, max_spur_pull);
	        //spur_list.push_back(spur);  
        }
}

map<int, map<int, TH1D*>> spur_map3; 
for (int i=0; i<bkg_size; i++) { 
        for (int k = 0; k < mean_size; k++){
	        spur_map3[i][k] = new TH1D(Form("spur3_%s_%3.0f",bkg_names[i].Data(), mean_val[k]),"Spurious Signal",50, min_spur_pull, max_spur_pull);
	        //spur_list.push_back(spur);  
        }
}

//Define SS and error arrays 
double nsignal[bkg_size][fileSize][mean_size];
double deltaS[bkg_size][fileSize][mean_size];
double error[bkg_size][fileSize][mean_size];
double chi2[bkg_size][fileSize][mean_size];
double prob[bkg_size][fileSize][mean_size];

double nsignal2[bkg_size][fileSize][mean_size];
double nsignal3[bkg_size][fileSize][mean_size];
/*double nsignal_2[bkg_size][fileSize][mean_size];
double deltaS_2[bkg_size][fileSize][mean_size];
double error_2[bkg_size][fileSize][mean_size];
double chi2_2[bkg_size][fileSize][mean_size];
double prob_2[bkg_size][fileSize][mean_size];*/

//for plotting:
RooPlot* massframe = mass->frame() ;
RooDataHist *data2, *data, *data3;
RooAddPdf sum, sum2, sum3;

//open signal pdf file:
TFile *f2 = TFile::Open(input_path2[0]);
RooWorkspace* w = (RooWorkspace*) f2->Get("signalPDF_ws");
int par[bkg_names.size()];
//loop through all histos
for(int k = 0; k < mean_size; k++){
        if (mean_val[k] != 125.0) continue;
        cout << "test3.1" << endl;
  for(int i = which_pdf; i < which_pdf+1; i++){
        cout << "test3.2" << endl;
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
	      RooArgSet  m_bkgParameters;
        m_bkgParameters.add(*bkg_pdf->getParameters(RooArgSet()));
        int npars = m_bkgParameters.getSize();
        if(i <= 2){
                par[i] = npars - 2;
        }
        else{
                par[i] = npars - 1;
        }
	
	      //--Define parameters for twosided CBShape--
        double mean = mean_val[k]; //GeV
        double width = w->var("sigwidth")->getVal();
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
  
        for(int j = 0; j < fileSize; j++){

        //if (bkg_names[i] != "Bern3") { continue; }
        //if(j >= 10) continue;
      
        //get each histo and use it
        TH1* histo = (TH1*) f1->Get(Form("%s", histos[j].c_str()));
        data = new RooDataHist("data","dataset with mes",*mass,histo);

        int nbins = histo->GetNbinsX();
        cout << "Histo bins: " << nbins << endl;

        RooAddPdf sum("sum","bkg_pdf+signal_PDF", RooArgList(*signal_PDF, *bkg_pdf),RooArgList(nsig,nbkg)) ;
        sum.fitTo(*data,Minimizer("Minuit2", "migrad"), Save(), Offset(), Range(105, 160));  //error ~ replace extended with range
        
        nsignal[i][j][k] = nsig.getVal();
        deltaS[i][j][k] = nsig.getError();
        error[i][j][k] = abs(nsig.getVal()/nsig.getError());

        cout << "nsignal MC: " << nsignal[i][j][k] << endl;

        //PLOT STUFF
        data->plotOn(massframe, Name("data"));
        //sum.plotOn(massframe, Name("sum")) ;
        //sum.plotOn(massframe,Components(*bkg_pdf),LineStyle(kDashed)) ;

        //--> chi2/dof`
                chi2[i][j][k] = massframe->chiSquare(par[i]);
                cout << "chi2 test: " << chi2[i][j][k] << endl;
                //--> chi2 Probability
                prob[i][j][k] = TMath::Prob(chi2[i][j][k] * (nbins - par[i]), nbins - par[i]);
        }
        for(int j = 0; j < fileSize2; j++){

        //if (bkg_names[i] != "Bern3") { continue; }
        //if(j >= 10) continue;
      
        //get each histo and use it
        TH1* histo = (TH1*) f3->Get(Form("%s", histos2[j].c_str()));
        data2 = new RooDataHist("data","dataset with mes",*mass,histo);

        int nbins = histo->GetNbinsX();
        cout << "Histo bins: " << nbins << endl;

        RooAddPdf sum2("sum","bkg_pdf+signal_PDF", RooArgList(*signal_PDF, *bkg_pdf),RooArgList(nsig,nbkg)) ;
        sum2.fitTo(*data2,Minimizer("Minuit2", "migrad"), Save(), Offset(), Range(105, 160));  //error ~ replace extended with range
        
        nsignal2[i][j][k] = nsig.getVal();

        data2->plotOn(massframe, Name("data2"), MarkerColor(kOrange), LineColor(kRed));
        //sum2.plotOn(massframe, Name("sum2"), LineColor(kRed)) ;
        //sum2.plotOn(massframe,Components(*bkg_pdf),LineStyle(kDashed), LineColor(kRed)) ;
        //deltaS[i][j][k] = nsig.getError();
        //error[i][j][k] = abs(nsig.getVal()/nsig.getError());
        }
        for(int j = 0; j < fileSize3; j++){

        //if (bkg_names[i] != "Bern3") { continue; }
        //if(j >= 10) continue;
      
        //get each histo and use it
        TH1* histo = (TH1*) f4->Get(Form("%s", histos3[j].c_str()));
        data3 = new RooDataHist("data3","dataset with mes",*mass,histo);

        int nbins = histo->GetNbinsX();
        cout << "Histo bins: " << nbins << endl;

        RooAddPdf sum3("sum","bkg_pdf+signal_PDF", RooArgList(*signal_PDF, *bkg_pdf),RooArgList(nsig,nbkg)) ;
        sum3.fitTo(*data3,Minimizer("Minuit2", "migrad"), Save(), Offset(), Range(105, 160));  //error ~ replace extended with range
        
        nsignal3[i][j][k] = nsig.getVal();

        data3->plotOn(massframe, Name("data3"), MarkerColor(kGreen), LineColor(kGreen));
        //sum3.plotOn(massframe, Name("sum2"), LineColor(kYellow)) ;
        //sum3.plotOn(massframe,Components(*bkg_pdf),LineStyle(kDashed), LineColor(kYellow)) ;
        //deltaS[i][j][k] = nsig.getError();
        //error[i][j][k] = abs(nsig.getVal()/nsig.getError());
        }
    }    
      
}

//save plots: 
if(fileSize2 == 1){
  for(int i = which_pdf; i < which_pdf+1; i++){
    for(int j = 0; j < fileSize; j++){
      for(int k = 0; k < mean_size; k++){
        if (mean_val[k] != 125.0) continue;

        string myy_hists = "myy_histos";
        system(Form("mkdir -vp %s", myy_hists.c_str()));
        string hist_type = "together";
        system(Form("mkdir -vp %s/%s/%s_plots", myy_hists.c_str(),hist_type.c_str(), bkg_names[i].Data()));
        TCanvas *c = new TCanvas(Form("%s", histos[j].c_str()), Form("%s", histos[j].c_str()), 800, 400);
        c->Clear();
        
        massframe->GetXaxis()->SetTitle("m_{#gamma#gamma} (GeV)");
        massframe->GetYaxis()->SetTitle("Events");
        massframe->SetTitle(Form("%s_plot: %s", bkg_names[i].Data(), histos[j].c_str()));
        massframe->Draw();
        
        TLegend* l = new TLegend(0.6,0.6,0.99,0.99);
        l->SetLineColor(kBlack);
        l->SetTextSize(0.04);
        l->SetBorderSize(0);
        l->AddEntry("", Form("SS_MC: %f", nsignal[i][j][k]), "");
        l->AddEntry("", Form("SS_ML: %f", nsignal2[i][j][k]), "");
        l->AddEntry("", Form("SS_T: %f", nsignal3[i][j][k]), "");
        l->AddEntry("data2","Data ML", "LEP");
        l->AddEntry("data","Data MC", "LEP");
        //l->AddEntry("data3","Data T", "LEP");
        //l->AddEntry("sum2","Sig + Bkg PDF ML", "L");
        //l->AddEntry("sum","Sig + Bkg PDF MC", "L");
        l->Draw();

        //save in seperate directories
        c->SaveAs(Form("%s/%s/%s_plots/%s.png", myy_hists.c_str(), hist_type.c_str(), bkg_names[i].Data(), histos[j].c_str()));
      }
    }
  }
}

//============ Find difference between signal MC and signal ML  - PULL PLOTS - ==================//
//nsignal[i][j][k] & nsignal2[i][j][k]
cout << "test4" << endl;
double diff[bkg_size][fileSize][mean_size];

for(int i = which_pdf; i < which_pdf+1; i++){
  for(int j = 0; j < fileSize; j++){
    for(int k = 0; k < mean_size; k++){
      diff[i][j][k] = nsignal[i][j][k] - nsignal2[i][j][k]; //MC - ML
      spur_map[i][k] -> Fill(diff[i][j][k]);
    }
  }
}
cout << "test4.1" << endl;

int num_range = 4;
TH1D* fixHist;
//--------- PULL PLOTS ----------//
for(int i = which_pdf; i < which_pdf+1; i++){
    for(int k = 0; k < mean_size; k++){
      if (mean_val[k] != 125.0) continue;

      //define new histogram to get true RMS value

      double width_ss_v0 = spur_map[i][k]->GetRMS();
      double mean_ss_v0 = spur_map[i][k]->GetMean();

      double x1 = mean_ss_v0-num_range*width_ss_v0;
			double x2 = mean_ss_v0+num_range*width_ss_v0;
      double bin_x1 = spur_map[i][k]->FindBin(mean_ss_v0-num_range*width_ss_v0);
			double bin_x2 = spur_map[i][k]->FindBin(mean_ss_v0+num_range*width_ss_v0);

      //define new (second) histogram:
			fixHist = new TH1D("Histo 2","fixHist",bin_x2-bin_x1+1, x1, x2);

      for(int j = bin_x1 ; j <= bin_x2 ; j++){
				double x=spur_map[i][k]->GetBinCenter(j);  
				double bin_y = fixHist->FindBin(x) ;  
				fixHist->SetBinContent(bin_y, spur_map[i][k]->GetBinContent(j));

				fixHist->SetBinError(bin_y, spur_map[i][k]->GetBinError(j));
			} 

      //Plot real values

      double width_ss = fixHist->GetRMS();
      double mean_ss = fixHist->GetMean();
     
      double width_ss_error = fixHist->GetRMSError();
      double mean_ss_error = fixHist->GetMeanError();
        cout << "test4.1.1" << endl;
      RooRealVar* spurious_signal = new RooRealVar("spurious_signal", "", min_spur_pull, max_spur_pull);
      RooDataHist* ss = new RooDataHist("ss", "Spurious Signal Data", *spurious_signal,fixHist);

      RooPlot* spurframe = spurious_signal->frame();
      ss->plotOn(spurframe, Name("ss"));
      cout << "test4.1.2" << endl;
      TCanvas *c = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
      spurframe->SetTitle(Form("%s_plot", bkg_names[i].Data()));
      spurframe->GetXaxis()->SetTitle("(SS_MC - SS_NF) Spurious Signal");
      spurframe->GetYaxis()->SetTitle("N_Samples");  
      spurframe->Draw();
      cout << "test4.1.3" << endl;
      TLegend *l = new TLegend(0.6,0.6,0.99,0.99);
      l->SetLineColor(kWhite);
      l->SetTextSize(0.033);
      l->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
      l->AddEntry("ss", "(MC - NF) Pull Plot Histogram", "LEP");
      l-> AddEntry("ss", Form("Data, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", width_ss, width_ss_error, mean_ss, mean_ss_error), "");
      l->Draw();
    
      string compare = "diff_MC_NF";
  
      system(Form("mkdir -vp %s", compare.c_str()));
      c -> SaveAs(Form("%s/%s_%iSS.png", compare.c_str(), bkg_names[i].Data(), fileSize));
    }
    cout << "test4.1.8" << endl;
}
cout << "test4.2" << endl;

//-------PULL PlOTS FOR MC - TRUTH ----- --------------------------------------------------// 
double diff2[bkg_size][fileSize][mean_size];

for(int i = which_pdf; i < which_pdf+1; i++){
  for(int j = 0; j < fileSize; j++){
    for(int k = 0; k < mean_size; k++){
      diff2[i][j][k] = nsignal[i][j][k] - nsignal3[i][j][k]; // MC - Truth 
      spur_map2[i][k] -> Fill(diff2[i][j][k]);
    }
  }
}
cout << "test4.3" << endl;

//--------- PULL PLOTS ----------//
for(int i = which_pdf; i < which_pdf+1; i++){
    for(int k = 0; k < mean_size; k++){
      if (mean_val[k] != 125.0) continue;

      //define new histogram to get true RMS value

      double width_ss_v0 = spur_map2[i][k]->GetRMS();
      double mean_ss_v0 = spur_map2[i][k]->GetMean();

      double x1 = mean_ss_v0-num_range*width_ss_v0;
			double x2 = mean_ss_v0+num_range*width_ss_v0;
      double bin_x1 = spur_map2[i][k]->FindBin(mean_ss_v0-num_range*width_ss_v0);
			double bin_x2 = spur_map2[i][k]->FindBin(mean_ss_v0+num_range*width_ss_v0);

      //define new (second) histogram:
			fixHist = new TH1D("Histo 2","fixHist",bin_x2-bin_x1+1, x1, x2);

      for(int j = bin_x1 ; j <= bin_x2 ; j++){
				double x=spur_map2[i][k]->GetBinCenter(j);  
				double bin_y = fixHist->FindBin(x) ;  
				fixHist->SetBinContent(bin_y, spur_map2[i][k]->GetBinContent(j));

				fixHist->SetBinError(bin_y, spur_map2[i][k]->GetBinError(j));
			} 

      //Plot real values

      double width_ss2 = fixHist->GetRMS();
      double mean_ss2 = fixHist->GetMean();

      double width_ss_error2 = fixHist->GetRMSError();
      double mean_ss_error2 = fixHist->GetMeanError();

      RooRealVar* spurious_signal2 = new RooRealVar("spurious_signal2", "", min_spur_pull, max_spur_pull);
      RooDataHist* ss2 = new RooDataHist("ss2", "Spurious Signal Data", *spurious_signal2,fixHist);

      RooPlot* spurframe2 = spurious_signal2->frame();
      ss2->plotOn(spurframe2, Name("ss2"));

      TCanvas *c2 = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
      spurframe2->SetTitle(Form("%s_plot", bkg_names[i].Data()));
      spurframe2->GetXaxis()->SetTitle("(SS_MC - SS_Truth) Spurious Signal");
      spurframe2->GetYaxis()->SetTitle("N_Samples");  
      spurframe2->Draw();

      TLegend *l2 = new TLegend(0.6,0.6,0.99,0.99); //, Form("PDF =  %s", eq[i].Data()), "brNDC");
      l2->SetLineColor(kWhite);
      l2 -> SetTextSize(0.033);
      l2->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
      l2->AddEntry("ss2", "(MC - Truth) Pull Plot Histogram", "LEP");
      l2 -> AddEntry("ss2", Form("Data: Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", width_ss2, width_ss_error2, mean_ss2, mean_ss_error2), "");
      l2->Draw();

      string compare2 = "diff_MC_Truth";

      system(Form("mkdir -vp %s", compare2.c_str()));
      c2 -> SaveAs(Form("%s/%s_%iSS.png", compare2.c_str(), bkg_names[i].Data(), fileSize));
    }
}
cout << "test4.4" << endl;
//------PULL PLOTS for NF - Truth -------------------------------------------------------//
double diff3[bkg_size][fileSize][mean_size];

for(int i = which_pdf; i < which_pdf+1; i++){
  for(int j = 0; j < fileSize; j++){
    for(int k = 0; k < mean_size; k++){
      diff3[i][j][k] = nsignal2[i][j][k] - nsignal3[i][j][k]; //NF - Truth
      spur_map3[i][k] -> Fill(diff3[i][j][k]);
    }
  }
}
cout << "test4.5" << endl;

//--------- PULL PLOTS ----------//
for(int i = which_pdf; i < which_pdf+1; i++){
    for(int k = 0; k < mean_size; k++){
      if (mean_val[k] != 125.0) continue;

      //define new histogram to get true RMS value

      double width_ss_v0 = spur_map3[i][k]->GetRMS();
      double mean_ss_v0 = spur_map3[i][k]->GetMean();

      double x1 = mean_ss_v0-num_range*width_ss_v0;
			double x2 = mean_ss_v0+num_range*width_ss_v0;
      double bin_x1 = spur_map3[i][k]->FindBin(mean_ss_v0-num_range*width_ss_v0);
			double bin_x2 = spur_map3[i][k]->FindBin(mean_ss_v0+num_range*width_ss_v0);

      //define new (second) histogram:
			fixHist = new TH1D("Histo 2","fixHist",bin_x2-bin_x1+1, x1, x2);

      for(int j = bin_x1 ; j <= bin_x2 ; j++){
				double x=spur_map3[i][k]->GetBinCenter(j);  
				double bin_y = fixHist->FindBin(x) ;  
				fixHist->SetBinContent(bin_y, spur_map3[i][k]->GetBinContent(j));

				fixHist->SetBinError(bin_y, spur_map3[i][k]->GetBinError(j));
			} 

      //Plot real values

      double width_ss3 = fixHist->GetRMS();
      double mean_ss3 = fixHist->GetMean();

      double width_ss_error3 = fixHist->GetRMSError();
      double mean_ss_error3 = fixHist->GetMeanError();

      RooRealVar* spurious_signal3 = new RooRealVar("spurious_signal3", "", min_spur_pull, max_spur_pull);
      RooDataHist* ss3 = new RooDataHist("ss3", "Spurious Signal Data", *spurious_signal3, fixHist);

      RooPlot* spurframe3 = spurious_signal3->frame();
      ss3->plotOn(spurframe3, Name("ss3"));

      TCanvas *c3 = new TCanvas(Form("Max %s", bkg_names[i].Data()), Form("%s", bkg_names[i].Data()), 800, 400);
      spurframe3->SetTitle(Form("%s_plot", bkg_names[i].Data()));
      spurframe3->GetXaxis()->SetTitle("(SS_NF - SS_Truth) Spurious Signal");
      spurframe3->GetYaxis()->SetTitle("N_Samples");  
      spurframe3->Draw();

      TLegend *l3 = new TLegend(0.6,0.6,0.99,0.99);
      l3->SetLineColor(kWhite);
      l3->SetTextSize(0.033);
      l3->SetHeader(Form("PDF =  %s", eq[i].Data()),"C");
      l3->AddEntry("ss3", "(NF - Truth) Pull Plot Histogram", "LEP");
      l3 -> AddEntry("ss3", Form("Data, Width: %.2f #pm %.2f, Mean: %.2f #pm %.2f", width_ss3, width_ss_error3, mean_ss3, mean_ss_error3), "");
      l3->Draw();

      string compare3 = "diff_NF_Truth";

      system(Form("mkdir -vp %s", compare3.c_str()));
      c3 -> SaveAs(Form("%s/%s_%iSS.png", compare3.c_str(), bkg_names[i].Data(), fileSize));
    }
}
cout << "test4.6" << endl;


cout << "test_final" << endl;

//END OF TIMER
timer.Stop();
timer.Print();
cout << "RealTime : " << timer.RealTime()/60.0 << " minutes" << endl;
cout << "RealTime : " << timer.RealTime() << " seconds" << endl;
cout << "CPUTime  : " << timer.CpuTime()/60.0 << " minutes" << endl;
cout << "Yes DONE" << endl; 

return 0;
}
