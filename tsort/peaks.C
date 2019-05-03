TH1F *h;
void peaks(TH1 *hh, Double_t thres=0.05,int backsub=1)
{
  TString sname=hh->GetName();
  h=(TH1F*)hh->Clone(sname);
  TSpectrum *s=new TSpectrum(500);
  if(backsub) {
   TH1D* hb=(TH1D*)s->Background(h,80,"same");
   sname+="_baksub";
   h->SetName(sname);
   h->Add(h,hb,1,-1);
  }
  Int_t nfound=s->Search(h,2,"",thres);
  TPolyMarker *pm=(TPolyMarker *)
                      h->GetListOfFunctions()->FindObject("TPolyMarker");
  pm->SetMarkerStyle(32);
  pm->SetMarkerColor(kGreen);
  pm->SetMarkerSize(0.4);
  Float_t *xpeaks=s->GetPositionX();
  Float_t *ypeaks=s->GetPositionY();
  for(int j=0;j<nfound;j++) {
   stringstream ss;
   ss<<xpeaks[j];
   TString s1=ss.str();
   TLatex *tex=new TLatex(xpeaks[j],ypeaks[j],s1);
   tex->SetTextFont(13);
   tex->SetTextSize(13);
   tex->SetTextAlign(12);
   tex->SetTextAngle(90);
   tex->SetTextColor(kRed);
   tex->Draw();
  }
}
