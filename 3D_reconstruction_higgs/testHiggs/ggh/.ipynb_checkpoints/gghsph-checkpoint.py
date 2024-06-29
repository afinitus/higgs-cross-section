import ROOT as r
import math as m
file = r.TFile.Open("ggh.root")
Output = file.output

photon1 = r.TLorentzVector()
photon2 = r.TLorentzVector()
diphoton = r.TLorentzVector()


hist4 = r.TH2F("hist", "photon emissions", 60, 0, 90, 60, -180, 180)
hist1 = r.TH1F("hist", "theta", 60, -180, 180)
hist2 = r.TH1F("hist", "eta", 60, -5, 5)


for entry in Output:
        photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
        photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
        diphoton = photon1 + photon2
        hist4.Fill(diphoton.Theta()*180/m.pi, diphoton.Phi()*180/m.pi, diphoton.E())
	hist1.Fill(diphoton.Theta() * 180/m.pi)
	hist2.Fill(diphoton.Eta())
	

canvas_4 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("colz")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_4.SaveAs("ThetavPhiWeightedcolz.png")

canvas_5 = r.TCanvas("higgs_theta", "higgs_theta")
hist1.SetLineWidth(2)
hist1.SetLineColor(2)
hist1.SetLineStyle(1)
hist1.SetFillColor(2)
hist1.Draw()
hist1.GetXaxis().SetTitle("{#theta}_{#gamma#gamma}")
hist1.GetYaxis().SetTitle("Entries")
canvas_5.SaveAs("Higgs_theta.png")

canvas_51 = r.TCanvas("higgs_eta", "higgs_eta")
hist2.SetLineWidth(2)
hist2.SetLineColor(2)
hist2.SetLineStyle(1)
hist2.SetFillColor(2)
hist2.Draw()
hist2.GetXaxis().SetTitle("{#eta}_{#gamma#gamma}")
hist2.GetYaxis().SetTitle("Entries")
canvas_51.SaveAs("Higgs_eta.png")

canvas_41 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("SURF1 SPH")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_41.SaveAs("ThetavPhiWeightedsurfsph.png")
