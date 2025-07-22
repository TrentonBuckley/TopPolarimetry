void make_data()
{
  //TRandom3 rnd(4343);
  TRandom3 rnd(4347);

  ofstream foutR("templateR.txt");
  ofstream foutL("templateL.txt");
  ofstream foutd("data.txt");

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  const int n = 20;
  TH1* hR_true = new TH1F("hR_true","",n,-1.,1.);
  TH1* hL_true = new TH1F("hL_true","",n,-1.,1.);
  for (int i = 1; i<=n; ++i) hR_true->SetBinContent(i,(i-0.5)/n);
  for (int i = 1; i<=n; ++i) hL_true->SetBinContent(i,1.-(i-0.5)/n);

  int n_events = 100000;
  TH1* hd = new TH1F("hd","",n,-1.,1.);
  TH1* hR = new TH1F("hR","",n,-1.,1.);
  TH1* hL = new TH1F("hL","",n,-1.,1.);
  double threshold = 0.6;
  float observation;
  for (int i = 0; i<n_events; ++i) {
    if (i>(threshold*n_events)) {
      observation=hL_true->GetRandom();
      hd->Fill(observation);
      hL->Fill(observation);
    }
    else {
      observation=hR_true->GetRandom();
      hd->Fill(observation);
      hR->Fill(observation);
    }
  }

  for (int i = 1; i<=n; ++i) foutd << hd->GetBinContent(i) << endl;
  for (int i = 1; i<=n; ++i) foutR << hR->GetBinContent(i) << endl;
  for (int i = 1; i<=n; ++i) foutL << hL->GetBinContent(i) << endl;
}
