// working arrays
const int nxmax = 1000, nsmax = 12;
const int ndim = nsmax*nxmax;
double sfit[ndim] = {0};
double dfit[nxmax] = {0};

int nbins = 0;
int nsfit = 0, nxfit = 0;

void xlog(int& np, double* deriv, double& f, double par[], int flag)
{
  double sum = 0;
  for (int ix = 0; ix<nxfit; ++ix) {
    double pred = 0;
    for (int is = 0; is<nsfit; ++is) {
      pred += sfit[is*nxmax+ix]*par[is];
    }
    if (pred>0) sum += pred - dfit[ix]*log(pred); // log likelihood
    //sum += 0.5*pow(pred - dfit[ix],2)/(dfit[ix]>0?dfit[ix]:1); // least squares
  }
  f = 2.*sum;
}

void fill()
{
  nxfit = 20;
  nsfit = 1;

  ifstream fin_template1("templateR.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_template1 >> sfit[i];
  }

  ifstream fin_template2("templateL.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_template2 >> sfit[nxmax + i];
  }

  ifstream fin_data("data.txt");
  for (int i = 0; i<nxfit; ++i) {
    fin_data >> dfit[i];
  }
}

void fit_one()
{
  // load data and templates
  fill();

  // set up minuit
  int npar = nsfit;
  TMinuit* minuit = new TMinuit(npar);
  minuit->SetFCN(xlog);
  for (int i = 0; i<npar; ++i) {
    string sp = "par"; sp+=char(i+'1');
    minuit->DefineParameter(i,sp.c_str(),1.,0.1,0.,10.);
  }

  // do the fit
  minuit->Migrad();

  // draw the 1,2 sigma contours

  TCanvas *c1 = new TCanvas("c1");
  c1->SetGridx();
  c1->SetGridy();
  TH2* hh = new TH2F("hh","",100,0.,2.,100,1.,3.);
  hh->GetXaxis()->SetTitle("p1");
  hh->GetYaxis()->SetTitle("p2");
  hh->Draw("box");

  double p1,p2,ep1,ep2;
  minuit->GetParameter(0,p1,ep1);
  minuit->GetParameter(1,p2,ep2);
  TLine* l1 = new TLine(p1-ep1,p2,p1+ep1,p2);
  TLine* l2 = new TLine(p1,p2-ep2,p1,p2+ep2);
  l1->SetLineWidth(3);
  l2->SetLineWidth(3);
  l1->Draw();
  l2->Draw();

  TLatex* tt = new TLatex();
  tt->SetNDC();
  tt->SetTextFont(42);
  tt->DrawLatex(0.6,0.83,TString::Format("p1 = %5.3f #pm %5.3f",p1,ep1));
  tt->DrawLatex(0.6,0.75,TString::Format("p2 = %5.3f #pm %5.3f",p2,ep2));

  TGraph *gr1 = (TGraph*)minuit->Contour(80,0,1);
  gr1->SetLineColor(2);
  gr1->SetLineWidth(3);
  gr1->Draw("l");
  minuit->SetErrorDef(4); //note 4 and not 2!
  TGraph *gr2 = (TGraph*)minuit->Contour(80,0,1);
  gr2->SetLineColor(4);
  gr2->SetLineWidth(3);
  gr2->Draw("l");
  c1->Modified();
  //c1->Print("contour.pdf");

  delete minuit;
}
