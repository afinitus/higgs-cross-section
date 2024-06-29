import ROOT as r
file = r.TFile.Open("testfile.root")
Output = file.output

ph_eta1 = 0
ph_phi1 = 0
is_passed = 0

hist = r.TH2F("hist", "photon emissions", 150, -2.4, 2.4, 150, -3.2, 3.2)
hist.SetFillColor(46)

for entry in Output:
	if entry.isPassed:
		hist.Fill(entry.ph_eta1, entry.ph_phi1)
	
canvas = r.TCanvas()

hist.Draw("colz")

hist.GetXaxis().SetTitle("ph_eta1")
hist.GetYaxis().SetTitle("ph_phi1")

canvas.SaveAs("Higgs.png")

