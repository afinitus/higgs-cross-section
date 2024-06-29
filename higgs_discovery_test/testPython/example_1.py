import ROOT
b_mgg = 0
s_mgg = 0

h_s = ROOT.TH1F("h_s", "h_s", 120, 100, 160)
h_b = ROOT.TH1F("h_b", "h_b", 120, 100, 160)

gRand = ROOT.TRandom3(1234)

signal_weight = 0.01

for i in range(100000):
	s_mgg = gRand.Gaus(125, 2)
	b_mgg = gRand.Exp(500)
	
	h_s.Fill(s_mgg, signal_weight)
	h_b.Fill(b_mgg)

canvas_0 = ROOT.TCanvas()

h_s.Draw()
h_b.Draw("same")

canvas_0.SaveAs("plot_mass_signal_over_background.png")

canvas_1 = ROOT.TCanvas()

h_s.SetLineWidth(2)
h_s.SetLineColor(2)
h_s.SetLineStyle(1)
h_s.SetFillColor(2)

h_b.SetLineWidth(2)
h_b.SetLineColor(1)
h_b.SetLineStyle(1)
h_b.SetFillColor(5)

max_s = 3 * h_s.GetMaximum()

h_s.GetXaxis().SetTitle("M_{#gamma#gamma} [GeV]")
h_s.GetYaxis().SetTitle("Entries")

h_s.GetYaxis().SetRangeUser(0, 1.5 * max_s)

h_s.Draw()
h_b.Draw("same")

canvas_1.SaveAs("plot_mass_signal_over_background_1.png")

canvas_2 = ROOT.TCanvas()

h_s.SetLineWidth(2)
h_s.SetLineColor(2)
h_s.SetLineStyle(1)
h_s.SetFillColor(2)

h_b.SetLineWidth(2)
h_b.SetLineColor(1)
h_b.SetLineStyle(1)
h_b.SetFillColor(5)

stack = ROOT.THStack("sk", "sk")

stack.Add(h_b)
stack.Add(h_s)
max_b = h_b.GetMaximum()
stack.Draw()
stack.GetXaxis().SetTitle("M_{#gamma#gamma} [GeV]")
stack.GetYaxis().SetTitle("Entries")

canvas_2.SaveAs("plot_mass_signal_over_background_2.png")

canvas_3 = ROOT.TCanvas()
h_s.SetLineWidth(2)
h_s.SetLineColor(2)
h_s.SetLineStyle(1)
h_s.SetFillColor(2)

h_b.SetLineWidth(2)
h_b.SetLineColor(1)
h_b.SetLineStyle(1)
h_b.SetFillColor(5)


sk_3 = ROOT.THStack()
sk_3.Add(h_b)
sk_3.Add(h_s)
sk_3.Draw()
sk_3.GetXaxis().SetTitle("M_{#gamma#gamma} [GeV]")
sk_3.GetYaxis().SetTitle("Entries")

leg_3 = ROOT.TLegend(0.65, 0.8, 0.85, 0.9)
leg_3.AddEntry(h_s,"H #rightarrow #gamma#gamma","FL")
leg_3.AddEntry(h_b,"Background","F")
leg_3.SetLineColor(0)
leg_3.SetTextSize(0.05)
leg_3.SetShadowColor(0)
leg_3.SetFillStyle(0)
leg_3.Draw()

cap_3 = ROOT.TLatex()
cap_3.SetNDC()
cap_3.SetTextColor(1)
cap_3.DrawLatex(0.2,0.25,"#int Ldt = 20.3 fb^{-1} #sqrt{s} = 8 TeV")
cap_3.DrawLatex(0.2,0.35,"ATLAS Internal")

canvas_3.SaveAs("plot_mass_signal_over_background_3.png")
















	
