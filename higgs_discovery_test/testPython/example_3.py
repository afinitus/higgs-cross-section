import ROOT
file = ROOT.TFile.Open("ntuple.root")
Hgg = file.Hgg



mgg = weight = is_signal = is_MC = 0
n_SCThits = ROOT.vector('double')()

Hgg.SetBranchAddress( "mgg", mgg )
Hgg.SetBranchAddress( "weight", weight )
Hgg.SetBranchAddress( "is_signal", is_signal )
Hgg.SetBranchAddress( "is_MC", is_MC )

Hgg.SetBranchAddress( "n_SCThits", n_SCThits )

h_s = ROOT.TH1F("h_s","h_s",120,100,160)
h_b = ROOT.TH1F("h_b","h_b",120,100,160)


for entry in Hgg:

	if len(entry.n_SCThits) <= 15:
		continue
	if entry.is_signal == 1:
		h_s.Fill(entry.mgg, entry.weight)	
	else:
		h_b.Fill(entry.mgg, entry.weight)
	
canvas_1 = ROOT.TCanvas()

h_s.SetLineWidth(2)
h_s.SetLineColor(2)
h_s.SetLineStyle(1)
h_s.SetFillColor(2)

h_b.SetLineWidth(2)
h_b.SetLineColor(1)
h_b.SetLineStyle(1)
h_b.SetFillColor(5)

h_b.Draw()
h_s.Add(h_b)
h_s.Draw("same")


h_b.GetXaxis().SetTitle("M_{#gamma#gamma} [GeV]")
h_b.GetYaxis().SetTitle("Entries")

leg_1 = ROOT.TLegend(0.65,0.8,0.85,0.9)
leg_1.AddEntry(h_s,"H #rightarrow #gamma#gamma","FL")
leg_1.AddEntry(h_b,"Background","F")
leg_1.SetLineColor(0)
leg_1.SetTextSize(0.05)
leg_1.SetShadowColor(0)
leg_1.SetFillStyle(0)
leg_1.Draw()

cap_1 = ROOT.TLatex()

cap_1.SetNDC()
cap_1.SetTextColor(1)
cap_1.DrawLatex(0.2,0.25,"#int Ldt = 20.3 fb^{-1} #sqrt{s} = 8 TeV")
cap_1.DrawLatex(0.2,0.35,"ATLAS Internal")

canvas_1.SaveAs("example3_figure_1.png")










