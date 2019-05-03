#define decay_cxx
#include "decay.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <algorithm>
#include <iostream>

using namespace std;


void decay::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L decay.C
//      Root > decay t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

decay::decay(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../tsmap/sort00335.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../tsmap/sort00335.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

decay::~decay()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t decay::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t decay::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void decay::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mwt", &mwt, &b_mwt);
   fChain->SetBranchAddress("mwe", &mwe, &b_mwe);
   fChain->SetBranchAddress("hit", &hit, &b_hit);
   
  // fChain->SetBranchAddress("yhit", &yhit, &b_yhit);
   fChain->SetBranchAddress("x", x, &b_x);
   fChain->SetBranchAddress("y", y, &b_y);
   fChain->SetBranchAddress("xe", xe, &b_xe);
   fChain->SetBranchAddress("ye", ye, &b_ye);
   fChain->SetBranchAddress("xt", xt, &b_xt);
   fChain->SetBranchAddress("yt", yt, &b_yt);
   fChain->SetBranchAddress("vt", vt, &b_vt);
   fChain->SetBranchAddress("ve", ve, &b_ve);
   fChain->SetBranchAddress("gt", gt, &b_gt);
   fChain->SetBranchAddress("ge", ge, &b_ge);
   
   fChain->SetBranchAddress("npp", npp, &b_npp);
   fChain->SetBranchAddress("ipp", ipp, &b_ipp);
   fChain->SetBranchAddress("trapezoidxE",trapezoidxE,&b_trapezoidxE);
   fChain->SetBranchAddress("trapezoidyE",trapezoidyE,&b_trapezoidyE);
   fChain->SetBranchAddress("chix",chix,&b_chix);
   fChain->SetBranchAddress("chiy",chiy,&b_chiy);
   fChain->SetBranchAddress("slopex",slopex,&b_slopex);
   fChain->SetBranchAddress("slopey",slopey,&b_slopey);
   fChain->SetBranchAddress("eehx",eehx,&b_eehx);
   fChain->SetBranchAddress("eehy",eehy,&b_eehy);  
 
   
   Notify();
}

Bool_t decay::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void decay::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t decay::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void  decay::MappingTs(map<ULong64_t,dssd_> &mts){

  if(fChain==0){
	  cout<<"no input tree!"<<endl;
	  return;
  }
  for(Long64_t i=0;i<fChain->GetEntriesFast();i++){
	fChain->GetEntry(i);
    if(mwe>=2000&&ve[0]<600&&ve[1]<600){
	  if(hit>10||hit>10) continue;
	  if(TMath::Abs(xe[0]-ye[0])>200) continue;
	  dssd_ d;
	  d.IsBeam=true;
	  d.e=xe[0];
	  d.x=x[0];
	  d.y=y[0];
	  d.ts=xt[0];
	  d.np=npp[0];
	  d.ip=ipp[0];
	  d.trapezoidxE=trapezoidxE[0];
	  d.trapezoidyE=trapezoidyE[0];
	  d.chix=chix[0];
	  d.chiy=chiy[0];
	  d.slopex=slopex[0];
	  d.slopey=slopey[0];
	  d.eehx=eehx[0];
	  d.eehy=eehy[0];
          memcpy(d.ge,ge,sizeof(ge));

          mts.insert(pair<ULong64_t,dssd_>(xt[0],d));
	  if(hit>1&&hit<10)
	  for(Int_t i=1;i<hit;i++){
	  if(TMath::Abs(xe[i]-ye[i])>200) continue;
	  d.IsBeam=false;
	  d.e=xe[i];
	  d.x=x[i];
	  d.y=y[i];
	  d.ts=xt[i];
	  d.np=npp[i];
	  d.ip=ipp[i];
	  d.trapezoidxE=trapezoidxE[i];
	  d.trapezoidyE=trapezoidyE[i];
	  d.chix=chix[i];
	  d.chiy=chiy[i];
	  d.slopex=slopex[i];
	  d.slopey=slopey[i];
	  d.eehx=eehx[i];
	  d.eehy=eehy[i];
	  memcpy(d.ge,ge,sizeof(ge));

	  mts.insert(pair<ULong64_t,dssd_>(xt[i],d));
	  }
	}else if (mwe<2000&&ve[0]<600&&ve[1]<600){
	  if(hit>5||hit>5) continue;
	  dssd_ d;
	  for(Int_t i=0;i<hit;i++){
	  if(TMath::Abs(xe[i]-ye[i])>200) continue;
	  d.IsBeam=false;
	  d.e=xe[i];
	  d.x=x[i];
	  d.y=y[i];
	  d.ts=xt[i];
	  d.np=npp[i];
	  d.ip=ipp[i];
	  d.trapezoidxE=trapezoidxE[i];
	  d.trapezoidyE=trapezoidyE[i]; 
	  d.chix=chix[i];
	  d.chiy=chiy[i];
	  d.slopex=slopex[i];
	  d.slopey=slopey[i];
	  d.eehx=eehx[i]; 
	  d.eehy=eehy[i];
	  memcpy(d.ge,ge,sizeof(ge));

	  mts.insert(pair<ULong64_t,dssd_>(xt[i],d));}
	}else continue; // light particle
  }
}

void  decay::BranchOpt(TTree *opt){
  if(opt==0) return;
  opt->Branch("be",&be,"be/D");
  opt->Branch("bge",bge,"bge[5]/D");
  opt->Branch("bslopex",&bslopex,"bslopex/D");
  opt->Branch("bslopey",&bslopey,"bslopey/D");
  opt->Branch("bt",&bt,"bt/L");
  opt->Branch("bx",&bx,"bx/I");
  opt->Branch("by",&by,"by/I");
  opt->Branch("bnp",&bnp,"bnp/I");
  opt->Branch("bip",&bip,"bip/I");  
  opt->Branch("btrapezoidE",&btrapezoidE,"btrapezoidE/D");
  opt->Branch("bchi2",&bchi2,"bchi2/D");
  opt->Branch("beehx",&beehx,"beehx/D");
  opt->Branch("beehy",&beehy,"beehy/D");
  
  opt->Branch("dhit",&dhit,"dhit/I");
  opt->Branch("de",&de,"de[dhit]/D");
  opt->Branch("dge",dge,"dge[dhit][5]/D");
  opt->Branch("dslopex",&dslopex,"dslopex[dhit]/D");
  opt->Branch("dslopey",&dslopey,"dslopey[dhit]/D");
  opt->Branch("dx",&dx,"dx[dhit]/I");
  opt->Branch("dy",&dy,"dy[dhit]/I");
  opt->Branch("dt",&dt,"dt[dhit]/L");
  opt->Branch("np",&np,"np[dhit]/I");
  opt->Branch("ip",&ip,"ip[dhit]/I");
  opt->Branch("deehx",&deehx,"deehx[dhit]/D");
  opt->Branch("deehy",&deehy,"deehy[dhit]/D");
  
  opt->Branch("dtrapezoidE",&dtrapezoidE,"dtrapezoidE[dhit]/D");
  opt->Branch("dchi2",&dchi2,"dchi2[dhit]/D");
}

void decay::ResetOpt(){
  dhit=0;
  be=0;
  bt=0;
  bx=-1;
  by=-1;
  memset(np,0,sizeof(np));
  memset(ip,0,sizeof(ip));
}

void decay::GetDecayInfo(dssd_ d1){
	if(dhit>=1000) return;
	de[dhit]=d1.e;
	dx[dhit]=d1.x;
	dy[dhit]=d1.y;
	dt[dhit]=d1.ts;
	np[dhit]=d1.np;
	ip[dhit]=d1.ip;
	dtrapezoidE[dhit]=d1.trapezoidxE;
	dchi2[dhit]=d1.chix;
	dslopex[dhit]=d1.slopex;
	dslopey[dhit]=d1.slopey;
	deehx[dhit]=d1.eehx;
	deehy[dhit]=d1.eehy;
	memcpy(dge[dhit],d1.ge,sizeof(d1.ge));
	dhit++;
	
}

void decay::GetBeamInfo(dssd_ d1){
        be=d1.e;
        bx=d1.x;
        by=d1.y;
        bt=d1.ts;
        bnp=d1.np;
        bip=d1.ip;
	btrapezoidE=d1.trapezoidxE;
	bchi2=d1.chix;
	bslopex=d1.slopex;
	bslopey=d1.slopey;
	beehx=d1.eehx;
	beehy=d1.eehy;
	memcpy(bge,d1.ge,sizeof(d1.ge));

}
