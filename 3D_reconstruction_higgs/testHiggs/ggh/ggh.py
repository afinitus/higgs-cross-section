import ROOT as r
import math as m
file = r.TFile.Open("ggh.root")
Output = file.output

photon1 = r.TLorentzVector()
photon2 = r.TLorentzVector()
diphoton = r.TLorentzVector()

hist1 = r.TH2F("hist", "photon emissions", 60, -180, 180, 60, -5, 5)
hist2 = r.TH2F("hist", "photon emissions", 60, -180, 180, 60, -6, 6)
hist3 = r.TH2F("hist", "photon emissions", 60, 0, 180, 60, -180, 180)
hist4 = r.TH2F("hist", "photon emissions", 60, 0, 180, 60, -180, 180)
hist5 = r.TH1F("hist", "higgs mass", 60, 0, 300)
hist6 = r.TH1F("hist", "transverse momentum" , 60, 0, 900)

for entry in Output:
        photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
        photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
        diphoton = photon1 + photon2
        hist1.Fill(diphoton.Phi()*180/m.pi, diphoton.Eta())
        hist2.Fill(diphoton.Phi()*180/m.pi,diphoton.Eta(), diphoton.E())
        hist3.Fill(diphoton.Theta()*180/m.pi, diphoton.Phi()*180/m.pi)
        hist4.Fill(diphoton.Theta()*180/m.pi - 90, diphoton.Phi()*180/m.pi, diphoton.E())
        hist5.Fill(diphoton.M())
        hist6.Fill(diphoton.Pt())

canvas = r.TCanvas("evpu", "evpu")
hist1.Draw("colz")
hist1.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist1.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas.SaveAs("EtavPhiUnweighted.png")

canvas_2 = r.TCanvas("evpw", "evpw")
hist2.Draw("colz")
hist2.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist2.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_2.SaveAs("EtavPhiWeighted.png")

canvas1 = r.TCanvas("evpu", "evpu")
hist2.Draw("surf1cyl")
hist2.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist2.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas1.SaveAs("EtavPhiWeightedsurfcyc.png")

canvas12 = r.TCanvas("evpu", "evpu")
hist2.Draw("col2")
hist2.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist2.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas12.SaveAs("EtavPhiWeightedcol2.png")

canvas13 = r.TCanvas("evpu", "evpu")
hist2.Draw("LEGO2Z")
hist2.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist2.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas13.SaveAs("EtavPhiWeightedlego.png")

canvas14 = r.TCanvas("evpu", "evpu")
hist2.Draw("LEGO1 SPH")
hist2.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist2.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas14.SaveAs("EtavPhiWeightedsphere.png")

canvas15 = r.TCanvas("evpu", "evpu")
hist2.Draw("SURF1 SPH")
hist2.GetYaxis().SetTitle("#eta_{#gamma#gamma}")
hist2.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
canvas15.SaveAs("EtavPhiWeightedspheresurf.png")

canvas_3 = r.TCanvas("tvpu", "tvpu")
hist3.Draw("colz")
hist3.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist3.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_3.SaveAs("ThetavPhiUnweighted.png")

canvas_4 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("colz")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_4.SaveAs("ThetavPhiWeighted.png")

canvas_41 = r.TCanvas("tvpw", "tvpw")
hist4.Draw("SURF1 SPH")
hist4.GetXaxis().SetTitle("#theta_{#gamma#gamma}")
hist4.GetYaxis().SetTitle("#phi_{#gamma#gamma}")
canvas_41.SaveAs("ThetavPhiWeightedsurfsph.png")


canvas_5 = r.TCanvas("higgs_mass", "higgs_mass")
hist5.SetLineWidth(2)
hist5.SetLineColor(2)
hist5.SetLineStyle(1)
hist5.SetFillColor(2)
hist5.Draw()
hist5.GetXaxis().SetTitle("M_{#gamma#gamma} [GeV]")
hist5.GetYaxis().SetTitle("Entries")
canvas_5.SaveAs("Higgs_mass.png")

canvas_6 = r.TCanvas("higgs_pt", "higgs_pt")
hist6.SetLineWidth(2)
hist6.SetLineColor(2)
hist6.SetLineStyle(1)
hist6.SetFillColor(2)
hist6.Draw()
hist6.GetXaxis().SetTitle("Pt_{#gamma#gamma}")
hist6.GetYaxis().SetTitle("Entries")
canvas_6.SaveAs("Higgs_pt.png")

