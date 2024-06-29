from array import array
import ROOT

myFile = ROOT.TFile.Open("file.root", "RECREATE")
tree = ROOT.TTree("tree", "The Tree Title")

# Provide a one-element array, so ROOT can read data from this memory.
var = array('d', [ 0 ])
tree.Branch("branch0", var, "leafname/D");

r = ROOT.TRandom3(1234)

for iEntry in range(10):
   var[0] = r.Gaus(125, 2)
   # Fill the current value of `var` into `branch0`
   tree.Fill()

# Now write the header
tree.Write()
