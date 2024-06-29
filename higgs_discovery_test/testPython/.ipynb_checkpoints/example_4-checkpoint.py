import ROOT

b_mgg = s_mgg = 0

h_s = ROOT.TH1F("h_s","h_s",120,100,160)
h_b = ROOT.TH1F("h_b","h_b",120,100,160)

gRand = ROOT.TRandom(1234)

for i in range(100000):

	s_mgg = gRand.Gaus(125, 2)
	b_mgg = gRand.Exp(500)
	
	signal_weight = 0.01
	
	h_s.Fill(s_mgg, signal_weight)
	h_b.Fill(b_mgg)

canvas_1 = ROOT.TCanvas()

h_s.SetLineWidth(2)
h_s.SetLineColor(2)
h_s.SetLineStyle(1)
h_s.SetFillColor(2)

h_s.Fit("gaus","","", 120, 130)

max_s = 1.5 * h_s.GetMaximum()

h_s.GetXaxis().SetTitle("M_{#gamma#gamma} [GeV]")
h_s.GetYaxis().SetTitle("Entries")

h_s.GetYaxis().SetRangeUser(0,max_s)

h_s.Draw()
h_b.Draw("same")

canvas_1.SaveAs("plot_fit_a_gaus.png")














