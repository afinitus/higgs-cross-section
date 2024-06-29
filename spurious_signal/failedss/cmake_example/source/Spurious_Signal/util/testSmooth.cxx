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
#include "TLorentzVector.h"
#include "TTree.h"
#include "TFile.h"

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
//#include "TMVA/PDF.h"
//#include "TMVA/KDEKernel.h"
//#include "TMVA/MsgLogger.h"
//#include "TMVA/Types.h"
//#include "TMVA/Tools.h"
//#include "TMVA/TSpline1.h"
//#include "TMVA/TSpline2.h"
//#include "TMVA/Version.h"
#include <TMVA/Tools.h>
#include <TMVA/Factory.h>
#include <TMVA/Reader.h>
#include <TMVA/MethodCuts.h>

using namespace std;

//void Smooth_v2(){
int main( int argc, char **argv ){

  TString unsmooth_rootfile = argv[1];
  int which_file = atof(argv[2]);

  ifstream infile(unsmooth_rootfile, ios::in);
  string line;
  vector<TString> input_path;
  while (getline(infile, line)){
    input_path.push_back(line);  // can be line.c_str()
  }
  infile.close();

  map<int, TH1F*> input_hists;
  map<int, TH1F*> output_hists;
  //TFile *f1 = TFile::Open("hist_yy_random1000_split_105160.root");
  //TFile *f1 = TFile::Open("/global/cfs/projectdirs/atlas/hanshuo/Tutorial/HGamma_Package/input/hist_yy_random1000_split_100165.root");

  double fine = 0.01;

  string name;
  //real pt cuts of interests
  if(which_file == 1){
    name = "pt_gr40";
  }
  else if(which_file == 2){
    name = "pt_le18";
  }
  else if(which_file == 3){
    name = "pt_b1840";
  }
  else if(which_file == 4){
    name = "inclusive_half";
  }
  else if (which_file == 5){
    name = Form("inclusive_%.1f_FF", fine*100);
    //name = "inclusive_smallFF";
  }

  TFile *f1 = TFile::Open(input_path[which_file - 1]);

  for(int j = 0; j < 1000; j++){

    // read the histogram
    TH1F *input = (TH1F*) f1->Get(Form("hmgg_c%d", j));
    //input->Draw();

    // create empty histogram with the same bins
    input_hists[j] = (TH1F*) input->Clone(Form("hmgg_c%d_smooth_v0", j));
    input_hists[j]->Reset();

    // smooth
    float finefactor = fine;
    TMVA::PDF * pdf = new TMVA::PDF(Form("pdf_%d", j), input, TMVA::KDEKernel::kGauss,TMVA::KDEKernel::kAdaptiveKDE,TMVA::KDEKernel::kSampleMirror,finefactor,false);
    //TMVA::PDF * pdf = new TMVA::PDF(Form("pdf_%d", j), input, TMVA::KDEKernel::kGauss,TMVA::KDEKernel::kNonadaptiveKDE,TMVA::KDEKernel::kSampleMirror,finefactor,false);
    //TMVA::PDF * pdf = new TMVA::PDF(Form("pdf_%d", j), input, TMVA::KDEKernel::kNone,TMVA::KDEKernel::kNonadaptiveKDE,TMVA::KDEKernel::kSampleMirror,finefactor,false);
    // smoothed PDF -> smoothed histogram, but there are 10000 bins 
    input_hists[j] = (TH1F*) pdf->GetPDFHist();
    int numbin = input_hists[j]->GetNbinsX();
    int residual = numbin%(input->GetNbinsX());
    int deficit = 2*(input->GetNbinsX()) - residual;

    TH1F* output = new TH1F(Form("hmgg_c%d_smooth_v1", j), "", numbin+deficit, 100, 165);
    for(int i = 0; i < output->GetNbinsX(); i++){
      int curr_bin = input_hists[j]->FindBin(output->GetBinCenter(i+1));
      output->SetBinContent(i+1, input_hists[j]->GetBinContent(curr_bin));
      output->SetBinError(i+1, input_hists[j]->GetBinError(curr_bin));
    }
    output->Scale(input->Integral()/output->Integral());
    output->Rebin((int) (numbin+deficit)/(input->GetNbinsX()));
    cout<<numbin+deficit<< " "<<input->GetNbinsX()<<endl;
    output->SetName(Form("hmgg_c%d_smooth_v2", j));    

    //output->SetLineColor(2);    
    //output->Draw("histsame");
    //output->Print("all");

    // redefine the histogram in 105-160
    output_hists[j] = new TH1F (Form("hmgg_c%d_smooth", j), "", 220, 105, 160);
    for(int i = 0; i < output_hists[j]->GetNbinsX(); i++){
      int curr_bin = output->FindBin(output_hists[j]->GetBinCenter(i+1));
      output_hists[j]->SetBinContent(i+1, output->GetBinContent(curr_bin));
      output_hists[j]->SetBinError(i+1, output->GetBinError(curr_bin));
    }

    // copy the error band from input
    for(int i = 0; i < output_hists[j]->GetNbinsX(); i++){
      int curr_bin = input->FindBin(output_hists[j]->GetBinCenter(i+1));
      output_hists[j]->SetBinError(i+1, input->GetBinError(curr_bin));
    }


  }

  TFile ffile(Form("smooth_rootHistos/hist_yy_smooth1000_%s.root", name.c_str()),"RECREATE","Demo ROOT file with histograms & trees");
  for(int j = 0; j < 1000; j++){
    output_hists[j]->Clone();
  }
  ffile.Write();
  ffile.Close();
}
