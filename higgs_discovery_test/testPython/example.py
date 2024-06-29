import ROOT 
def example(seed, SorB):
	Output = ROOT.TTree("Hgg", "Hgg")
	File = ROOT.TFile("ntuple.root", "recreate")
	print("Seed", seed, " S or B ", SorB)

	mgg = 0

	Output.Branch("mgg", mgg, "mgg/D")
	
	gRand = ROOT.TRandom3(seed)
	
	i = 0
	while i < 1:
		if SorB == 1:
			mgg = gRand.Gaus(125, 2)
		else:
			mgg = 100 + gRand.Exp(50)   
		print("the generated mass value", mgg)
		Output.Fill()
	Output.Write()
	File.Close()


