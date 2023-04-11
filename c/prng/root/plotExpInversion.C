void
plotExpInversion() { 

  TH1F * h_pdf = new TH1F("h_pdf","h_pdf",25,0,5.);
  TH1F * h_cdf = new TH1F("h_cdf","h_cdf",25,0,1.);


  TTree * t = new TTree("t","t"); 
  t->ReadFile("inversion.dat", "index/i:pdf/D:cdf/D");

  TCanvas * c = new TCanvas("c","c",0,0,600,500);
  h_pdf->SetLineColor(kRed);
  t->Draw("pdf>>h_pdf");
  TCanvas * cc = new TCanvas("cc","cc",600,0,600,500);
  h_cdf->SetLineColor(kBlue);  
  t->Draw("cdf>>h_cdf");


}
