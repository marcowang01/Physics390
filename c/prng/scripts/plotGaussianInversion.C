void
plotGaussianInversion() { 

  TH1F * h_pdf = new TH1F("h_pdf","h_pdf",100,-5.,5.);
  TH1F * h_cdf = new TH1F("h_cdf","h_cdf",100,0,1.);
  TH1F * h_inv = new TH1F("h_inv","h_inv",100,-5.,5.);

  TTree * t = new TTree("t","t"); 
  t->ReadFile("inversion.dat", "index/i:pdf/D:cdf/D:inv/D");

  TCanvas * c = new TCanvas("c","c",0,0,600,500);
  h_pdf->SetLineColor(kRed);
  h_inv->SetLineColor(kBlue);
  t->Draw("pdf>>h_pdf");
  t->Draw("inv>>h_inv","","sames");

  TCanvas * cc = new TCanvas("cc","cc",600,0,600,500);
  t->Draw("cdf>>h_cdf","","goff");
  cc->DrawFrame(0.,0.,1.,1.1*h_cdf->GetMaximum());
  h_cdf->SetLineColor(kBlue);  
  h_cdf->Draw("same");




}
