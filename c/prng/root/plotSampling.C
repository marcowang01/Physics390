void
plotSampling() { 

  TH1F * h_reject = new TH1F();
  TH1F * h_metro  = new TH1F();

  TTree * t = new TTree("t","t"); 
  t->ReadFile("data/sampling.dat", "index/i:reject/D:metro/D");

  t->SetLineColor(kRed);
  t->Draw("metro>>h_metro");
  t->SetLineColor(kBlue);  
  t->Draw("reject>>h_reject","","sames");

}
