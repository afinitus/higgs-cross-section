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


for N in range(19):
	hist4 = r.TH2F("hist", "photon emissions", 60, -180, 180, 60, -90, 90)
	for entry in Output:
        	photon1.SetPtEtaPhiE(entry.ph_pt1, entry.ph_eta1, entry.ph_phi1, entry.ph_E1)
        	photon2.SetPtEtaPhiE(entry.ph_pt2, entry.ph_eta2, entry.ph_phi2, entry.ph_E2)
        	diphoton = photon1 + photon2
        	#hist1.Fill(diphoton.Theta() * 180/m.pi)
        	angle = diphoton.Pt() / diphoton.Pz()
        	actual_angle = m.atan(angle)
        	phi = 2 * ( diphoton.Phi() * 180 / m.pi - N * 10) + 180
        	hist4.Fill(phi ,actual_angle * 180 / m.pi, diphoton.E())
	canvas_42 = r.TCanvas("tvpwworlda", "tvpwworlda", 800, 800)
	hist4.Draw("aitoff")
	hist4.GetXaxis().SetTitle("#phi_{#gamma#gamma}")
	hist4.GetYaxis().SetTitle("#theta_{#gamma#gamma}")
	canvas_42.SaveAs("thetavphiweightedaitoff" + str(N) + ".png")
	hist4.Reset()
	hist4.ResetStats()


