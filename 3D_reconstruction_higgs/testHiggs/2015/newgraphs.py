import ROOT as r
import math as m
import os

Output = r.TChain("output")

directory = "/global/projecta/projectdirs/atlas/eressegu/Ntuple_h026_0630/data15/data/data15/root"
for filename in os.listdir(directory):
        f = os.path.join(directory, filename)
        if os.path.isfile(f):
                Output.Add(f)

photon1 = r.TLorentzVector()
photon2 = r.TLorentzVector()
diphoton = r.TLorentzVector()

hist4 = r.TH2F("hist", "photon emissions", 60, -180, 180, 60, -90, 90)
hist1 = r.TH1F("hist", "theta", 60, -180, 180)
hist2 = r.TH1F("hist", "eta", 60, -5, 5)


for entry in Output:
        photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
        photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
        diphoton = photon1 + photon2
       	#hist1.Fill(diphoton.Theta() * 180/m.pi)
	angle = diphoton.Pt() / diphoton.Pz()
	actual_angle = m.atan(angle)
	phi = diphoton.Phi() * 180 / m.pi
	#phi2 = 2 * ( diphoton.Phi() * 180 / m.pi - N * 10) + 180
	hist4.Fill(phi ,actual_angle * 180 / m.pi)
	hist1.Fill(actual_angle * 180 / m.pi)
        hist2.Fill(diphoton.Rapidity())


canvas_4 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("colz")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_4.SaveAs("thetavPhiWeightedcolz.png")

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
canvas_41.SaveAs("thetavPhiWeightedsurfsph.png")

canvas_42 = r.TCanvas("tvpwworlda", "tvpwworlda", 800, 800)
hist4.Draw("aitoff")
hist4.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#theta_{#gamma#gamma}")
canvas_42.SaveAs("thetavPhiWeightedworlda.png")

canvas_43 = r.TCanvas("tvpwworldm", "tvpwworldm")
hist4.Draw("mercator")
hist4.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#theta_{#gamma#gamma}")
canvas_43.SaveAs("thetavPhiWeightedworldm.png")
