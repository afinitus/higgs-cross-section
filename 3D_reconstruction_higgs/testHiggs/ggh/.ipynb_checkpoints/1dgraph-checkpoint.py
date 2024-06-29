import ROOT as r
from array import array
import math as m
file = r.TFile.Open("ggh.root")
Output = file.output

photon1 = r.TLorentzVector()
photon2 = r.TLorentzVector()
diphoton = r.TLorentzVector()

canvas = r.TCanvas("HIGGS ThetavsEta GGH DATA", "HIGGS ThetavsEta GGH DATA")

x, y = array( 'd' ), array( 'd' )

i = 0
for entry in Output:
	if i == 10000:
		break
	i += 1
	photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
        photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
        diphoton = photon1 + photon2
	x.append(diphoton.Eta())
	y.append(diphoton.Theta() * 180 /m.pi)


graph = r.TGraph(10000, x, y)
graph.Draw("ap")
graph.SetTitle( '#theta_{#gamma#gamma} vs #eta_{#gamma#gamma}' )
graph.GetXaxis().SetTitle( '#eta_{#gamma#gamma}' )
graph.GetYaxis().SetTitle( '#theta_{#gamma#gamma}' )
canvas.SaveAs("ThetavEta.png")

