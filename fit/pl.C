void pl()
{
  bool print = false;

  int nxfit = 20;
  TH1F* h1 = new TH1F("h1","",nxfit,-1.,1.);
  TH1F* h2 = new TH1F("h2","",nxfit,-1.,1.);
  TH1F* hd = new TH1F("hd","",nxfit,-1.,1.);

  double d;
  ifstream fin_template1("templateR.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_template1 >> d;
    h1->SetBinContent(i+1,d);
  }

  ifstream fin_template2("templateL.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_template2 >> d;
    h2->SetBinContent(i+1,d);
  }

  ifstream fin_data("data.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_data >> d;
    hd->SetBinContent(i+1,d);
  }

  TH1* h1a = (TH1*)h1->Clone();
  TH1* h2a = (TH1*)h2->Clone();

  TCanvas* c1 = new TCanvas("c1","c1");
  h1a->SetLineWidth(3);
  h1a->SetLineColor(2);
  h2a->SetLineWidth(3);
  h2a->SetLineColor(3);
  h2a->GetXaxis()->SetTitle("Time [s]");
  h2a->SetMinimum(0);
  h1a->Draw();
  h2a->Draw("same");
  c1->Modified();
  if (print) c1->Print("fit_data.pdf");

  TCanvas* c2 = new TCanvas("c2","c2");
  THStack* ths = new THStack();
  h1->SetFillColor(2);
  ths->Add(h1);
  h2->SetFillColor(3);
  ths->Add(h2);
  ths->Draw("hist");
  //h1->Draw("hist");
  //h2->Draw("hist");
  //ths->SetMaximum(35);
  ths->GetXaxis()->SetTitle("Time [s]");
  ths->GetYaxis()->SetTitle("Events / 1 s");
  hd->SetMarkerStyle(8);
  hd->SetMarkerSize(1.2);
  hd->Draw("e0same");
  c2->Modified();
  if (print) c2->Print("fit_sum.pdf");
}
