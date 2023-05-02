#include <vector>
#include "TF1.h"
#include "include/vegas_constants.hh"


//
// plots contributions to the integral from each event for the first 
// and last iterations of a given trial.  
//
// The first iteration corresponds to uniform binning in x, so most 
// events will be away from the gaussian peaks and their contributions
// are small, giving a peak in the I distribution near zero.  The integral 
// value (ie: the sum of all contributions) is driven by the events in 
// the tails of the I distribution, which are near the peaks of the gaussians
//
// The last iteration corresponds to converged importance remapping.  Now 
// more events are located near the gaussian peaks, giving a peak in the 
// I distribution at higher values 
//


void plotOptTarget(Int_t Niter, Int_t Nevt, const char* ipath, const char* opath) { 

  char fname[512];
  sprintf(fname, "%s/xhist__Niter_%d_Nevt_%d.dat", ipath, Niter, Nevt);
  
  TTree * t = new TTree("t","t");
  t->ReadFile(fname, "it/I:bin/I:xbound/F:occ/F:avgJF/F:avgJ2F2/F");


  int n;
  n = t->Draw("bin:occ","it==0","goff");
  TGraph * g_occ_first = new TGraph( n, t->GetV1(), t->GetV2());
  n = t->Draw("bin:avgJF","it==0","goff");
  TGraph * g_avgJF_first = new TGraph( n, t->GetV1(), t->GetV2());
  n = t->Draw("bin:avgJ2F2","it==0","goff");
  TGraph * g_avgJ2F2_first = new TGraph( n, t->GetV1(), t->GetV2());
  n = t->Draw("bin:occ","it==19","goff");
  TGraph * g_occ_last = new TGraph( n, t->GetV1(), t->GetV2());
  n = t->Draw("bin:avgJF","it==19","goff");
  TGraph * g_avgJF_last = new TGraph( n, t->GetV1(), t->GetV2());
  n = t->Draw("bin:avgJ2F2","it==19","goff");
  TGraph * g_avgJ2F2_last = new TGraph( n, t->GetV1(), t->GetV2());

  g_occ_first->Print();
  g_occ_last->Print();

  char pngstr[512];

  TCanvas * c1 = new TCanvas("c1","c1",0,0,600,500);
  double max_occ = 1.1*TMath::Max(TMath::MaxElement(n,g_occ_first->GetY()),TMath::MaxElement(n,g_occ_last->GetY()));
  cout << "max_occ: " << max_occ << endl;
  //TH1F * f1 = (TH1F*)(c1->DrawFrame(-VEGAS_HIGH_RANGE,0.1,VEGAS_HIGH_RANGE,max_occ));
  TH1F * f1 = (TH1F*)(c1->DrawFrame(0,0.1,50,max_occ));
  g_occ_first->SetLineColor(kRed);
  g_occ_first->SetLineWidth(2);
  g_occ_first->SetMarkerColor(kRed);
  g_occ_first->SetMarkerStyle(20);
  g_occ_first->SetMarkerSize(1.2);
  g_occ_last->SetLineColor(kBlue);
  g_occ_last->SetLineWidth(2);
  g_occ_last->SetMarkerColor(kBlue);
  g_occ_last->SetMarkerStyle(20);
  g_occ_last->SetMarkerSize(1.2);
  g_occ_first->Draw("pl");
  g_occ_last->Draw("pl");
  sprintf(pngstr,"%s/xOccupany_Nevts_%d.png", opath,Nevt);
  c1->Print(pngstr);


  TCanvas * c2 = new TCanvas("c2","c2",600,0,600,500);
  double max_JF = 1.1*TMath::Max(TMath::MaxElement(n,g_avgJF_first->GetY()),TMath::MaxElement(n,g_avgJF_last->GetY()));
  cout << "max_JF: " << max_JF << endl;
  //TH1F * f2 = (TH1F*)(c2->DrawFrame(-VEGAS_HIGH_RANGE,0.1,VEGAS_HIGH_RANGE,max_JF));
  TH1F * f2 = (TH1F*)(c2->DrawFrame(0,0.1,50,max_JF));
  g_avgJF_first->SetLineColor(kRed);
  g_avgJF_first->SetLineWidth(2);
  g_avgJF_first->SetMarkerColor(kRed);
  g_avgJF_first->SetMarkerStyle(20);
  g_avgJF_first->SetMarkerSize(1.2);
  g_avgJF_last->SetLineColor(kBlue);
  g_avgJF_last->SetLineWidth(2);
  g_avgJF_last->SetMarkerColor(kBlue);
  g_avgJF_last->SetMarkerStyle(20);
  g_avgJF_last->SetMarkerSize(1.2);
  g_avgJF_first->Draw("pl");
  g_avgJF_last->Draw("pl");
  sprintf(pngstr,"%s/xavgJF_Nevts_%d.png", opath,Nevt);
  c2->Print(pngstr);


  TCanvas * c3 = new TCanvas("c3","c3",1200,0,600,500);
  double max_J2F2 = 1.1*TMath::Max(TMath::MaxElement(n,g_avgJ2F2_first->GetY()),TMath::MaxElement(n,g_avgJ2F2_last->GetY()));
  cout << "max_J2F2: " << max_J2F2 << endl;
  //TH1F * f3 = (TH1F*)(c3->DrawFrame(-VEGAS_HIGH_RANGE,0.1,VEGAS_HIGH_RANGE,max_J2F2));
  TH1F * f3 = (TH1F*)(c3->DrawFrame(0,0.1,50,max_J2F2));
  g_avgJ2F2_first->SetLineColor(kRed);
  g_avgJ2F2_first->SetLineWidth(2);
  g_avgJ2F2_first->SetMarkerColor(kRed);
  g_avgJ2F2_first->SetMarkerStyle(20);
  g_avgJ2F2_first->SetMarkerSize(1.2);
  g_avgJ2F2_last->SetLineColor(kBlue);
  g_avgJ2F2_last->SetLineWidth(2);
  g_avgJ2F2_last->SetMarkerColor(kBlue);
  g_avgJ2F2_last->SetMarkerStyle(20);
  g_avgJ2F2_last->SetMarkerSize(1.2);
  g_avgJ2F2_first->Draw("pl");
  g_avgJ2F2_last->Draw("pl");
  sprintf(pngstr,"%s/xavgJ2F2_Nevts_%d.png", opath,Nevt);
  c3->Print(pngstr);

}

