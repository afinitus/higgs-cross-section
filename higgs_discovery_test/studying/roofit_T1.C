#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TMath.h"
#include "TF1.h"
#include "Math/DistFunc.h"
#include "RooTFnBinding.h"
 
using namespace RooFit;

void roofit_T1(){
	
    // --- Observable ---
    RooRealVar mes("mes","m_{ES} (GeV)",5.20,5.30) ;
    // --- Build Gaussian signal PDF ---
    RooRealVar sigmean("sigmean","B^{#pm} mass",5.28,5.20,5.30) ;
    RooRealVar sigwidth("sigwidth","B^{#pm} width",0.0027,0.001,1.) ;
    RooGaussian gauss("gauss","gaussian PDF",mes,sigmean,sigwidth) ;
    // --- Build Argus background PDF ---
    RooRealVar argpar("argpar","argus shape parameter",-20.0,-100.,-1.) ;
    RooArgusBG argus("argus","Argus PDF",mes,RooConst(5.291),argpar) ;
    // --- Construct signal+background PDF ---
    RooRealVar nsig("nsig","#signal events",200,0.,10000) ;
    RooRealVar nbkg("nbkg","#background events",800,0.,10000) ;
    RooAddPdf sum("sum","g+a",RooArgList(gauss,argus),RooArgList(nsig,nbkg)) ;
    // --- Generate a toyMC sample from composite PDF ---
    RooDataSet *data = sum.generate(mes,2000) ;
    // --- Perform extended ML fit of composite PDF to toy data ---
    sum.fitTo(*data,Extended()) ;
    // --- Plot toy data and composite PDF overlaid ---
    RooPlot* mesframe = mes.frame() ;
    data->plotOn(mesframe) ;
    sum.plotOn(mesframe) ;
    sum.plotOn(mesframe,Components(argus),LineStyle(kDashed)) ;

    //draw the plot:
    mesframe->Draw();

    //save the mesframe as a pdf
    mesframe->SaveAs("fitted_plot_T1");

}
