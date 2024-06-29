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


hist4 = r.TH2F("hist", "photon emissions", 60,-180, 180, 60, -180, 180)
hist5 = r.TH1F("hist", "higgs phi", 60, -6, 6)
hist6 = r.TH1F("hist", "higgs rapidity" , 60, -6, 6)


for entry in Output:
    photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
    photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
    diphoton = photon1 + photon2
    angle = diphoton.Pt() / diphoton.Pz()
    actual_angle = m.atan(angle)
    phi = diphoton.Phi() * 180 / m.pi
    rapidity = diphoton.Rapidity()
    hist5.Fill(phi)
    hist6.Fill(rapidity)
    hist4.Fill(phi ,actual_angle * 180 / m.pi)

canvas_4 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("colz")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_4.SaveAs("ThetavPhiRaw.png")

canvas_5 = r.TCanvas("higgs_phi", "higgs_phi")
hist5.SetLineWidth(2)
hist5.SetLineColor(2)
hist5.SetLineStyle(1)
hist5.SetFillColor(2)
hist5.Draw()
hist5.GetXaxis().SetTitle("Phi_{#gamma#gamma} [GeV]")
hist5.GetYaxis().SetTitle("Entries")
canvas_5.SaveAs("Higgs_Phi.png")

canvas_6 = r.TCanvas("higgs_rapidity", "higgs_rapidity")
hist6.SetLineWidth(2)
hist6.SetLineColor(2)
hist6.SetLineStyle(1)
hist6.SetFillColor(2)
hist6.Draw()
hist6.GetXaxis().SetTitle("Rapidity_{#gamma#gamma}")
hist6.GetYaxis().SetTitle("Entries")
canvas_6.SaveAs("Higgs_Rapidity.png")