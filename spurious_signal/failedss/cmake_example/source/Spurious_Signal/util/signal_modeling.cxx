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

// Local include(s):
//#include "/global/cfs/projectdirs/atlas/juliet/spurious-signal/roofit/HGamma_Package/source/HGamCore/HGamAnalysisFramework/HGamAnalysisFramework/Config.h"
//#include "/global/cfs/projectdirs/atlas/juliet/spurious-signal/roofit/HGamma_Package/source/HGamCore/HGamAnalysisFramework/HGamAnalysisFramework/HGamCommon.h"
#include "/global/cfs/projectdirs/atlas/juliet/spurious-signal/cmake_example/source/Spurious_Signal/inc/RooTwoSidedCBShape.h"

using namespace RooFit;
using namespace std;

//void signal_modeling(){
int main( int argc, char **argv ){

  int option = atof(argv[1]);
  
        // initialize the TTree
        TFile * f1 = TFile::Open("/global/cfs/projectdirs/atlas/hanshuo/Tutorial/HGamma_Package/MxAOD_input/mc16a.PowhegPy8_NNLOPS_ggH125.MxAODDetailedNoSkim.e5607_s3126_r9364_p4180_h027.001.root");
        TTree * t1 = (TTree*) f1->Get("output");
        float m_yy;
        float m_yy_scaled;
	float weightCatCoup_HybridFullRun2;
        float crossSectionBRfilterEff;
        float y1_pt, y1_eta, y1_phi;
        float y2_pt, y2_eta, y2_phi;
	bool isPassed;
	
	float MC_yeild;
        float sum_of_weight = 0;
        int lumi = 139000; //pb or pico barn or inverse pico barn

	t1->SetBranchStatus("*",0);
	t1->SetBranchStatus("HGamEventInfoAuxDyn.crossSectionBRfilterEff", 1);
	t1->SetBranchStatus("HGamEventInfoAuxDyn.weightCatCoup_HybridFullRun2",1);
        t1->SetBranchStatus("HGamEventInfoAuxDyn.m_yy",1);
        t1->SetBranchStatus("HGamEventInfoAuxDyn.isPassed",1);
	
	t1->SetBranchAddress("HGamEventInfoAuxDyn.crossSectionBRfilterEff", &crossSectionBRfilterEff);
	t1->SetBranchAddress("HGamEventInfoAuxDyn.weightCatCoup_HybridFullRun2", &weightCatCoup_HybridFullRun2);
        t1->SetBranchAddress("HGamEventInfoAuxDyn.m_yy", &m_yy);
        t1->SetBranchAddress("HGamEventInfoAuxDyn.isPassed",&isPassed);

        t1->SetBranchStatus("y1_pt", 1);
        t1->SetBranchStatus("y1_eta", 1);
        t1->SetBranchStatus("y1_phi", 1);
        t1->SetBranchStatus("y2_pt", 1);
        t1->SetBranchStatus("y2_eta", 1);
        t1->SetBranchStatus("y2_phi", 1);

        t1->SetBranchAddress("y1_pt", &y1_pt);
        t1->SetBranchAddress("y1_eta", &y1_eta);
        t1->SetBranchAddress("y1_phi", &y1_phi);
 
        t1->SetBranchAddress("y2_pt", &y2_pt);
        t1->SetBranchAddress("y2_eta", &y2_eta);
        t1->SetBranchAddress("y2_phi", &y2_phi);
  
 
       /* //create a txt file to save the mass
        std::ofstream myfile;
        myfile.open("signal.txt", std::ios::app);

        // loop over events in TTree
        int Ntot = t1->GetEntries();
        for(int i = 0; i < Ntot; i++){
          t1->GetEntry(i);
          m_yy_scaled = m_yy / 1000;
          if(isPassed) myfile<<m_yy_scaled<<endl;
        }

        RooRealVar* mass = new RooRealVar("mass", "", 125, 105, 160);
        RooDataSet *data = RooDataSet::read("signal.txt",RooArgList(*mass) );
	*/
	
	//--alternative method which is like 10 times faster--//
	RooRealVar* mass = new RooRealVar("mass", "", 125, 105, 160);
        RooRealVar* weight = new RooRealVar("weight", "", 1, -10, 10);
        RooDataSet *data = new RooDataSet("signal_MC", "", RooArgSet(*mass, *weight), WeightVar(*weight)); //take out RooArgSet

        // loop over events in TTree
	int Ntot = t1->GetEntries();
        //get the sum of weights
	for(int i = 0; i < Ntot; i++){
		t1->GetEntry(i);
		sum_of_weight += weightCatCoup_HybridFullRun2;


	}
        
        TLorentzVector photon1, photon2, diphoton;
        float yy_pt;
        string option_pt;

        //real pt cuts of interests
        if(option == 1){
                option_pt = "pt_gr40";
        }
        else if(option == 2){
                option_pt = "pt_le18";
        }
        else if(option == 3){
                option_pt = "pt_b1840";
        }
        else if (option == 4){
                option_pt = "inclusive_half";
        }
        else if (option == 5){
                option_pt = "normal";
        }

	//diphoton selection
	for(int i = 0; i < Ntot; i++){
          t1->GetEntry(i);

          if (option == 4){
                if(i%2 == 0) continue;
          }

          m_yy_scaled = m_yy / 1000;

          photon1.SetPtEtaPhiM(y1_pt,y1_eta,y1_phi,0);
          photon2.SetPtEtaPhiM(y2_pt,y2_eta,y2_phi,0);
          diphoton = photon1 + photon2;
          yy_pt = diphoton.Pt()/1000; //MeV to GeV

          //real pt values of interest
          if(option == 1){
                if(yy_pt < 40) continue;
          }
          else if(option == 2){
                if(yy_pt > 18) continue;
          }
          else if(option == 3){
                if(yy_pt<18 || yy_pt > 40) continue;
          }

          mass->setVal(m_yy_scaled);
          //weight->setVal(weightCatCoup_HybridFullRun2);
	  MC_yeild = (lumi*weightCatCoup_HybridFullRun2*crossSectionBRfilterEff)/sum_of_weight;	
          weight -> setVal(MC_yeild); 

          if(isPassed) {
            data->add(RooArgSet(*mass, *weight), MC_yeild);
          }
        }



	//---Define Signal---//
	//TFile *f2 = TFile::Open("/global/cfs/projectdirs/atlas/hanshuo/Tutorial/HGamma_Package/input/res_DoubleCB_workspace.root");
        //RooWorkspace* w = (RooWorkspace*) f2->Get("signalWS");
	        RooRealVar mes("mes","m_{#gamma#gamma} (GeV)",105,160);
                double mean = 125.0;
                double width = 1.5;
                double ahi = 1.5;
                double alo = 1.5;
                double nlo = 5.0;
                double nhi = 230.0;
 
                RooRealVar* sigmean = new RooRealVar("sigmean", "mean", mean, mean-5, mean+5);
                RooRealVar* sigwidth = new RooRealVar("sigwidth","width", width, width-5, width+5); //1.63474
                RooRealVar* alphaLo = new RooRealVar("alphaLo", "alphaLo",alo, alo-20, alo+20); //1.77084
                RooRealVar* alphaHi = new RooRealVar("alphaHi", "alphaHi", ahi, ahi-5, ahi+5); //1.44924
                RooRealVar* nLo = new RooRealVar("nLo", "nLo", nlo, nlo-10, nlo+10); //5.36402
                RooRealVar* nHi = new RooRealVar("nHi", "nHi", nhi, nhi-10, nhi+10); //246.466
                //--USE original signal PDF 
                RooTwoSidedCBShape* signal_PDF = new RooTwoSidedCBShape("signal_PDF", "signal_PDF", *mass,*sigmean,*sigwidth,*alphaLo,*nLo,*alphaHi,*nHi);
	
	signal_PDF->fitTo(*data,RooFit::Minimizer("Minuit2", "migrad"), RooFit::Save(), RooFit::Offset(), RooFit::Range(105, 160));

        RooPlot *plot = mass->frame();
        data->plotOn(plot);
        signal_PDF->plotOn(plot);
	plot->Draw();

	// Create a new empty workspace
   	RooWorkspace *signalPDF_ws = new RooWorkspace("signalPDF_ws", "workspace");

	// Import model and all its components into the workspace
	signalPDF_ws->import(*signal_PDF);

	// Import data into the workspace
	signalPDF_ws -> import(*data);
	
	signalPDF_ws -> Print();
	// Save the workspace into a ROOT file
	//signalPDF_ws->writeToFile("DSCB_workspace_test.root");
        signalPDF_ws->writeToFile(Form("sig_PDF_ws/DSCB_ws_%s.root", option_pt.c_str()));

	//root -> Add(ws);
return(0);
}


