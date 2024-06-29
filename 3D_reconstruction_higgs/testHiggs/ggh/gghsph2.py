import ROOT as r
import math as m
file = r.TFile.Open("ggh.root")
Output = file.output

photon1 = r.TLorentzVector()
photon2 = r.TLorentzVector()
diphoton = r.TLorentzVector()


hist4 = r.TH2F("hist", "photon emissions", 60, -90, 90, 60, -90, 90)

for entry in Output:
        photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
        photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
        diphoton = photon1 + photon2
        hist4.Fill(diphoton.Theta()*180/m.pi - 90, diphoton.Phi()*180/m.pi, diphoton.E())


canvas_4 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("colz")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_4.SaveAs("thetavphiweightedcolz2.png")

canvas_41 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("SURF1 SPH")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_41.SaveAs("ThetavPhiWeightedsurfsph2.png")

canvas_42 = r.TCanvas("tvpwworldm", "tvpwworldm")
hist4.Draw("mercator")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_42.SaveAs("thetavPhiWeightedworldm.png")

canvas_43 = r.TCanvas("tvpwworlda", "tvpwworlda")
hist4.Draw("aitoff")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_43.SaveAs("thetavPhiWeightedworlda.png")
