void photon_pt_distribution_3()
{
//=========Macro generated from canvas: c1_n4/c1_n4
//=========  (Wed Feb  9 21:18:57 2022) by ROOT version 6.20/06
   TCanvas *c1_n4 = new TCanvas("c1_n4", "c1_n4",0,0,700,500);
   c1_n4->Range(-12.5,-13.8,112.5,124.2);
   c1_n4->SetFillColor(0);
   c1_n4->SetBorderMode(0);
   c1_n4->SetBorderSize(2);
   c1_n4->SetFrameBorderMode(0);
   c1_n4->SetFrameBorderMode(0);
   
   TH1F *h_ph_pt__1 = new TH1F("h_ph_pt__1","h_ph_pt",50,0,100);
   h_ph_pt__1->SetBinContent(6,92);
   h_ph_pt__1->SetBinContent(7,36);
   h_ph_pt__1->SetBinContent(8,22);
   h_ph_pt__1->SetBinContent(9,10);
   h_ph_pt__1->SetBinContent(10,15);
   h_ph_pt__1->SetBinContent(11,10);
   h_ph_pt__1->SetBinContent(12,6);
   h_ph_pt__1->SetBinContent(13,7);
   h_ph_pt__1->SetBinContent(14,2);
   h_ph_pt__1->SetBinContent(15,7);
   h_ph_pt__1->SetBinContent(16,3);
   h_ph_pt__1->SetBinContent(17,5);
   h_ph_pt__1->SetBinContent(18,1);
   h_ph_pt__1->SetBinContent(19,2);
   h_ph_pt__1->SetBinContent(20,6);
   h_ph_pt__1->SetBinContent(21,8);
   h_ph_pt__1->SetBinContent(22,4);
   h_ph_pt__1->SetBinContent(23,4);
   h_ph_pt__1->SetBinContent(24,4);
   h_ph_pt__1->SetBinContent(25,3);
   h_ph_pt__1->SetBinContent(26,4);
   h_ph_pt__1->SetBinContent(27,3);
   h_ph_pt__1->SetBinContent(28,2);
   h_ph_pt__1->SetBinContent(29,2);
   h_ph_pt__1->SetBinContent(33,1);
   h_ph_pt__1->SetBinContent(34,2);
   h_ph_pt__1->SetBinContent(35,1);
   h_ph_pt__1->SetBinContent(36,1);
   h_ph_pt__1->SetBinContent(37,1);
   h_ph_pt__1->SetBinContent(39,1);
   h_ph_pt__1->SetBinContent(45,1);
   h_ph_pt__1->SetBinContent(47,1);
   h_ph_pt__1->SetBinContent(48,1);
   h_ph_pt__1->SetBinContent(51,2);
   h_ph_pt__1->SetMinimum(0);
   h_ph_pt__1->SetMaximum(110.4);
   h_ph_pt__1->SetEntries(270);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("h_ph_pt");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 270    ");
   ptstats_LaTex = ptstats->AddText("Mean  =  22.26");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  16.46");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h_ph_pt__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h_ph_pt__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ph_pt__1->SetLineColor(ci);
   h_ph_pt__1->GetXaxis()->SetTitle(" Photon p_{T} [GeV]");
   h_ph_pt__1->GetXaxis()->SetLabelFont(42);
   h_ph_pt__1->GetXaxis()->SetTitleOffset(1);
   h_ph_pt__1->GetXaxis()->SetTitleFont(42);
   h_ph_pt__1->GetYaxis()->SetTitle(" Number of Entries");
   h_ph_pt__1->GetYaxis()->SetLabelFont(42);
   h_ph_pt__1->GetYaxis()->SetTitleFont(42);
   h_ph_pt__1->GetZaxis()->SetLabelFont(42);
   h_ph_pt__1->GetZaxis()->SetTitleOffset(1);
   h_ph_pt__1->GetZaxis()->SetTitleFont(42);
   h_ph_pt__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4231897,0.9339831,0.5768103,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("h_ph_pt");
   pt->Draw();
   c1_n4->Modified();
   c1_n4->cd();
   c1_n4->SetSelected(c1_n4);
}
