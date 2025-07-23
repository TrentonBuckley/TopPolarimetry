void cos_theta_differences()
{
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  const int n = 1000;
  TH1* h1 = new TH1F("h1","",n,-1.,1.);
  for (int i = 1; i<=n; ++i) h1->SetBinContent(i,(i-0.5)/n);
  TH1* h2 = new TH1F("h2","",n,-1.,1.);
  for (int i = 1; i<=n; ++i) h2->SetBinContent(i,1.-(i-0.5)/n);
  TH1* hs = new TH1F("hs","",64,-3.2,3.2);
  TH1* ho = new TH1F("ho","",64,-3.2,3.2);
  for (int i = 0; i<10000; ++i) {
    double theta11 = acos(h1->GetRandom());
    double theta12 = acos(h1->GetRandom());
    double theta21 = acos(h2->GetRandom());
    double theta22 = acos(h2->GetRandom());
    hs->Fill(theta11-theta12);
    hs->Fill(theta21-theta22);
    ho->Fill(theta11-theta21);
    ho->Fill(theta22-theta12);
  }
  hs->GetXaxis()->SetTitle("#theta*_{1}-#theta*_{2}");
  hs->GetYaxis()->SetTitle("Arbitrary units");
  hs->Draw();
  ho->SetLineColor(2);
  ho->Draw("same");

  TLegend* l = new TLegend(0.20,0.75,0.45,0.85);
  l->SetMargin(0.2);
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  l->AddEntry(hs,"L-L, R-R","l");
  l->AddEntry(ho,"L-R, R-L","l");
  l->Draw();

}
