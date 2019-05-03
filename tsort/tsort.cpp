#define tsort_cxx
#include "tsort.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

void tsort::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L tsort.C
//      Root > tsort t
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

tsort::tsort(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../mapping/map00307.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../mapping/map00307.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tsort::~tsort()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tsort::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tsort::LoadTree(Long64_t entry)
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

void tsort::Init(TTree *tree)
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
	
   fChain->SetBranchAddress("det", &det, &b_det);
   fChain->SetBranchAddress("fr", &fr, &b_fr);
   fChain->SetBranchAddress("str", &str, &b_str);
   fChain->SetBranchAddress("ts", &ts, &b_ts);
   fChain->SetBranchAddress("e", &e, &b_e);
   fChain->SetBranchAddress("np", &np, &b_np);
   fChain->SetBranchAddress("ip", &ip, &b_ip);
   fChain->SetBranchAddress("chi",&chi,&b_chi);
   fChain->SetBranchAddress("trapezoidE",&trapezoidE,&b_trapezoidE);
   fChain->SetBranchAddress("slope",&slope,&b_slope);
   fChain->SetBranchAddress("dwave", dwave, &b_dwave);
   fChain->SetBranchAddress("sample", sample, &b_sample);
   fChain->SetBranchAddress("eeh",&eeh, &b_eeh);
   //fChain->SetBranchAddress("bd", &bd, &b_bd);
   //fChain->SetBranchAddress("ch", &ch, &b_ch);
   Notify();
   gammacali();
}

Bool_t tsort::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tsort::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tsort::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void  tsort::MappingTs(multimap<ULong64_t,dect_> &mts){
	fChain->SetBranchStatus("*",0);
	fChain->SetBranchStatus("ts",1);
	fChain->SetBranchStatus("det",1);
	fChain->SetBranchStatus("fr",1);
	fChain->SetBranchStatus("str",1);
	fChain->SetBranchStatus("ts",1);
	fChain->SetBranchStatus("e",1);
	fChain->SetBranchStatus("np",1);
	fChain->SetBranchStatus("ip",1);	
	fChain->SetBranchStatus("chi",1);
	fChain->SetBranchStatus("trapezoidE",1);
	fChain->SetBranchStatus("slope",1);
	fChain->SetBranchStatus("eeh",1);
	for(Long64_t i=0;i<fChain->GetEntriesFast();i++){
	
	  fChain->GetEntry(i);
	  //if(det==4) ts -= 37;
	  
	  dect_ d1;
	  d1.det=det;
	  d1.fr=fr;
	  d1.str=str;
	  d1.ts=ts;
	  
	  if(np==1)
	    d1.e=trapezoidE;
	    else
	      d1.e=e;
	  
	  d1.np=np;
	  d1.ip=ip;
	  d1.chi=chi;
	  d1.trapezoidE=trapezoidE;
	  d1.slope=slope;
	  d1.eeh=eeh;
//	  if(det==2&&fr==1) continue;
	  mts.insert(pair<ULong64_t,dect_>(ts,d1));
	}
}

void  tsort::BranchOpt(TTree *opt){
  if(opt==0) return ;
  opt->Branch("mwt",&mwt,"mwt/l");
  opt->Branch("mwe",&mwe,"mwe/D");

  opt->Branch("xhit",&xhit,"xhit/I");
  opt->Branch("yhit",&yhit,"yhit/I");
  opt->Branch("hit",&hit,"hit/I");
  opt->Branch("npp",&npp,"npp[xhit]/I");
  opt->Branch("ipp",&ipp,"ipp[xhit]/I");
  opt->Branch("x",&x,"x[xhit]/I");
  opt->Branch("y",&y,"y[yhit]/I");
  opt->Branch("xe",&xe,"xe[xhit]/D");
  opt->Branch("ye",&ye,"ye[yhit]/D");
  opt->Branch("xt",&xt,"xt[xhit]/l");
  opt->Branch("yt",&yt,"yt[yhit]/l");

  opt->Branch("trapezoidxE",&trapezoidxE,"trapezoidxE[xhit]/D");
  opt->Branch("trapezoidyE",&trapezoidyE,"trapezoidyE[yhit]/D");
  opt->Branch("chix",&chix,"chix[xhit]/D");
  opt->Branch("chiy",&chiy,"chiy[yhit]/D");
  opt->Branch("slopex",&slopex,"slopex[xhit]/D");
  opt->Branch("slopey",&slopey,"slopey[yhit]/D");
  opt->Branch("eehx",&eehx,"eehx[xhit]/D");
  opt->Branch("eehy",&eehy,"eehy[yhit]/D");
  opt->Branch("vt",&vt,"vt[3]/l");
  opt->Branch("ve",&ve,"ve[3]/D");

  opt->Branch("ghit",&ghit,"ghit/I");
  opt->Branch("gt",&gt,"gt[ghit]/l");
  opt->Branch("ge",&ge,"ge[ghit]/D");
  opt->Branch("dt",&dt,"dt[ghit]/I");
  opt->Branch("tsi",&tsi,"tsi[ghit]/l");
}

void tsort::ResetOpt(){
  xhit=0;yhit=0;//hit=0;
  mwt=0;mwe=0;ghit=0;
  //ge=0;gt=0;dt=-10000;
  tmpt=0;
  memset(vt,0,sizeof(vt));
  memset(xt,0,sizeof(ve));
  memset(yt,0,sizeof(yt));
  memset(ve,0,sizeof(ve));
  memset(xe,0,sizeof(xe));
  memset(ye,0,sizeof(ye));
  memset(gt,0,sizeof(gt));
  memset(ge,0,sizeof(ge));
  memset(dt,-10000,sizeof(dt));
  memset(npp,0,sizeof(npp));
  memset(ipp,0,sizeof(ipp));
  memset(tsi,0,sizeof(tsi));
}

void tsort::gammacali(){
  gepar[0][0]=0.2207;
  gepar[0][1]=0.3818;
  gepar[1][0]=0.2198;
  gepar[1][1]=0.3752;
  gepar[2][0]=0.2192;
  gepar[2][1]=0.2356;
  gepar[3][0]=0.2245;
  gepar[3][1]=0.2708;  
  gepar[4][0]=0.0; //
  gepar[4][1]=0.0; //
  }

void  tsort::MappingDet(dect_ &d1){
//if(xhit==1||yhit==1) return;
  if(d1.det==1){
       mwt=d1.ts;
	mwe=d1.e;
  }else if(d1.det==2){
	if(d1.fr==1){
	  
	  yy[yhit]=d1.str;
	  yye[yhit]=d1.e;
	  yyt[yhit]=d1.ts;
	  ytrapezoidyE[yhit]=d1.trapezoidE;
	  ychiy[yhit]=d1.chi;
	  yslopey[yhit]=d1.slope;
	  yeehy[yhit]=d1.eeh;
            
	  yhit++;
	}else {
	  xx[xhit]=d1.str;
	  xxe[xhit]=d1.e;
	  xxt[xhit]=d1.ts;
	  npp[xhit]=d1.np;
	  ipp[xhit]=d1.ip;
	  xslopex[xhit]=d1.slope;
	  xtrapezoidxE[xhit]=d1.trapezoidE;
	  xchix[xhit]=d1.chi;
	  xeehx[xhit]=d1.eeh;
	  
	  //  if(npp[xhit]==2)cout<<npp[xhit]<<" "<<ipp[xhit]<<endl; 
	  xhit++;
	}
  }else if(d1.det==3){
	if(d1.str<0||d1.str>=3) return;
        ve[d1.str]=d1.e;
	vt[d1.str]=d1.ts;
  }else if(d1.det==4){
        
        if(d1.str<0||d1.str>5) return;
        // ge[d1.str]=d1.e*gepar[d1.str][0]-gepar[d1.str][1];
	// gt[d1.str]=d1.ts;
	gt[ghit]=d1.ts;
        
	dt[ghit]=tmpt-d1.ts;
	tsi[ghit]=tmpt;
	ge[ghit]=d1.e*gepar[d1.str][0]-gepar[d1.str][1];//ge==0 mean the str==4;
	
	/*if(gt-tmpt>200||gt-tmpt<0){
	gt=0;
	ge=0;
	}*/
	
	ghit++;
  }
}


void tsort::XYcorrection()
{
   int hit1=0;
  /* hit=0;
   for(int i=0;i<xhit;i++)
     for(int j=0;j<yhit;j++) {
        //if(xxe[i]>0&&yye[j]>0&&TMath::Abs(xxe[i]-yye[j])>200) continue;
        xe[i]=xxe[i];
        x[i]=xx[i];
        xt[i]=xxt[i];
        slopex[i]=xslopex[i];
        trapezoidxE[i]=xtrapezoidxE[i];
        chix[i]=xchix[i];
        //npp[i]=npp[i];
        //ipp[i]=ipp[i];
        ye[j]=yye[j];
        y[j]=yy[j];
        yt[j]=yyt[j];
        slopey[j]=yslopey[j];
        trapezoidyE[j]=ytrapezoidyE[j];
        chiy[j]=ychiy[j];
        eehx[j]=xeehx[j];
        eehy[j]=yeehy[j];
        hit++;

      }*/
    
   
    for(int i=0;i<xhit;i++){
        xe[i]=xxe[i];
        x[i]=xx[i];
        xt[i]=xxt[i];
        slopex[i]=xslopex[i];
        trapezoidxE[i]=xtrapezoidxE[i];
        chix[i]=xchix[i];
        npp[i]=npp[i];
        ipp[i]=ipp[i];
    }
    
    for(int j=0;j<yhit;j++){
        ye[j]=yye[j];
        y[j]=yy[j];
        yt[j]=yyt[j];
        slopey[j]=yslopey[j];
        trapezoidyE[j]=ytrapezoidyE[j];
        chiy[j]=ychiy[j];
        eehx[j]=xeehx[j];
        eehy[j]=yeehy[j];
    }
    
    /*
    for(int i=0;i<hit1;i++) {
        for(int j=0;j<hit1-i-1;j++) {
            if(xt[j]>xt[j+1])
            {
              swap(xt[j],xt[j+1]);
              swap(yt[j],yt[j+1]);
              swap(xe[j],xe[j+1]);
              swap(ye[j],ye[j+1]);
              swap(x[j],x[j+1]);
              swap(y[j],y[j+1]);
              swap(trapezoidxE[j], trapezoidxE[j+1]);
              swap(trapezoidyE[j], trapezoidyE[j+1]);
              swap(chix[j], chix[j+1]);
              swap(chiy[j], chiy[j+1]);  
              swap(slopex[j],slopex[j+1]);
              swap(slopey[j],slopey[j+1]);  
              swap(eehx[j],eehx[j+1]);
              swap(eehy[j],eehy[j+1]);
            }
        }
    }
   hit=hit1;
   
//correct for the time stamp when hit events have the same time stamp;
    hit=0;
    for(int i=0;i<hit1;i++) {
      int dh=0;
      for(int j=0;j<hit1;j++) if(xt[i]==xt[j]) dh++;
      if(dh>1) continue;
      xt[hit]=xt[i];    
      yt[hit]=yt[i];
      xe[hit]=xe[i];    
      ye[hit]=ye[i]; 
      x[hit]=x[i];
      y[hit]=y[i];
      trapezoidxE[hit]=trapezoidxE[i];
      trapezoidyE[hit]=trapezoidyE[i];
      chix[hit]=chix[i];
      chiy[hit]=chiy[i];
      slopex[hit]=slopex[i];
      slopey[hit]=slopey[i];
      eehx[hit]=eehx[i];
      eehy[hit]=eehy[i];
      
      hit++;      
     }*/

 }
