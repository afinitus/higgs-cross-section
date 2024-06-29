//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 11 12:54:08 2022 by ROOT version 6.20/06
// from TTree Hgg/Hgg
// found on file: ntuple.root
//////////////////////////////////////////////////////////

#ifndef Hgg_h
#define Hgg_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class Hgg {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        mgg;
   Double_t        weight;
   Int_t           is_signal;
   Int_t           is_MC;
   vector<double>  *n_SCThits;

   // List of branches
   TBranch        *b_mgg;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_is_signal;   //!
   TBranch        *b_is_MC;   //!
   TBranch        *b_n_SCThits;   //!

   Hgg(TTree *tree=0);
   virtual ~Hgg();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Hgg_cxx
Hgg::Hgg(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ntuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ntuple.root");
      }
      f->GetObject("Hgg",tree);

   }
   Init(tree);
}

Hgg::~Hgg()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Hgg::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Hgg::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Hgg::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   n_SCThits = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mgg", &mgg, &b_mgg);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("is_signal", &is_signal, &b_is_signal);
   fChain->SetBranchAddress("is_MC", &is_MC, &b_is_MC);
   fChain->SetBranchAddress("n_SCThits", &n_SCThits, &b_n_SCThits);
   Notify();
}

Bool_t Hgg::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Hgg::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Hgg::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Hgg_cxx
