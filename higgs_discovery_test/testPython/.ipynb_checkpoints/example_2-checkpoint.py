import ROOT
from array import array
Tree = ROOT.TTree("Hgg", "Hgg")
File = ROOT.TFile("ntuple.root", "recreate")

mgg = array('d', [ 0 ])
weight = array('d', [ 0 ])
is_signal = array('i', [ 0 ]) 
is_MC = array('i', [ 0 ])

n_SCThits = ROOT.vector('double')()

Tree.Branch("mgg",mgg,"mgg/D")
Tree.Branch("weight",weight,"weight/D")
Tree.Branch("is_signal",is_signal,"is_signal/I")
Tree.Branch("is_MC",is_MC,"is_MC/I")
Tree.Branch("n_SCThits",n_SCThits)

gRand = ROOT.TRandom(1234)

for i in range(100000):
	n_SCThits.clear()
	mgg[0] = gRand.Gaus(125, 2)
	weight[0] = .01
	is_signal[0] = 1
	is_MC[0] = 1

	n_trk = gRand.Poisson(25)
	nscthits = 0
	for j in range(n_trk):
		nscthits = gRand.Poisson(14)
		n_SCThits.push_back(nscthits)

	Tree.Fill()	


for i in range(150000):
      	n_SCThits.clear()
        mgg[0] = gRand.Exp(500)
        weight[0] = 1
        is_signal[0] = 0
        is_MC[0] = 1

        n_trk = gRand.Poisson(35)
        nscthits = 0
        for j in range(n_trk):
                nscthits = gRand.Poisson(8)
              	n_SCThits.push_back(nscthits)
        Tree.Fill()

Tree.Write()
File.Close()
 





