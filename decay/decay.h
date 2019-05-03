//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 24 19:28:05 2016 by ROOT version 5.34/21
// from TTree tree/tree
// found on file: ../tsmap/sort00335.root
//////////////////////////////////////////////////////////

#ifndef decay_h
#define decay_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <map>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

struct dssd_ {
  Bool_t IsBeam;
  Double_t e;
  Int_t  x;
  Int_t  y;
  Int_t ghit;
  Long64_t ts;
  Int_t np;
  Int_t ip;
  Double_t trapezoidxE;
  Double_t trapezoidyE;
  Double_t chix;
  Double_t chiy;
  Double_t slopex;
  Double_t slopey;
  Double_t eehx;
  Double_t eehy;
  Double_t ge[5];
  
};

class decay {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   ULong64_t       mwt;
   Double_t        mwe;

   Int_t           hit;
   //Int_t           yhit;
   Int_t           x[10];   //[xhit]
   Int_t           y[10];   //[xhit]
   Double_t        xe[10];   //[xhit]
   Double_t        ye[10];   //[xhit]
   ULong64_t       xt[10];   //[xhit]
   ULong64_t       yt[10];   //[xhit]
   Double_t        trapezoidxE[10];
   Double_t        trapezoidyE[10];
   Double_t        chix[10];
   Double_t        chiy[10];
   Double_t        slopex[10];
   Double_t        slopey[10];
   
   UShort_t        sample[1500];
   Double_t        eehx[10];
   Double_t        eehy[10];
   
   Int_t             np[10];
   Int_t             ip[10];
   Int_t             bnp;
   Int_t             bip;
   Int_t             npp[10];
   Int_t             ipp[10];

   ULong64_t       vt[3];
   Double_t        ve[3];
   
   ULong64_t       gt[5];
   Double_t        ge[5];

   // List of branches
   TBranch        *b_mwt;   //!
   TBranch        *b_mwe;   //!
   TBranch        *b_hit;   //!
   TBranch        *b_ghit;
   //TBranch        *b_yhit;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_xe;   //!
   TBranch        *b_ye;   //!
   TBranch        *b_xt;   //!
   TBranch        *b_yt;   //!
   TBranch        *b_vt;   //!
   TBranch        *b_ve;   //!
   TBranch        *b_trapezoidxE;
   TBranch        *b_trapezoidyE;
   TBranch        *b_chix;
   TBranch        *b_chiy;
   TBranch        *b_gt;   //!
   TBranch        *b_ge;   //!
   TBranch        *b_npp;
   TBranch        *b_ipp;
   TBranch        *b_slopex;
   TBranch        *b_slopey;
   TBranch        *b_sample;
   TBranch        *b_eehx;
   TBranch        *b_eehy;

   // output variables
   Double_t    be;
   Double_t    bge[5];
   Long64_t    bt;
   Int_t    bx;
   Int_t    by;
   Double_t        btrapezoidE;
   Double_t        bchi2;
   Double_t        bslopex;
   Double_t        bslopey;
   Double_t        beehx;
   Double_t        beehy;


   Int_t    dhit;
   Double_t de[1000];
   Int_t    dx[1000];
   Int_t    dy[1000];
   Long64_t    dt[1000];
   Double_t    dtrapezoidE[1000];
   Double_t    dchi2[1000];
   Double_t    dslopex[1000];
   Double_t    dslopey[1000];
   Double_t    deehx[1000];
   Double_t    deehy[1000];
   Double_t    dge[1000][5];

   decay(TTree *tree=0);
   virtual ~decay();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void   MappingTs(std::map<ULong64_t,dssd_> &mts);
   void   BranchOpt(TTree *opt);
   void   ResetOpt();
   void   GetDecayInfo(dssd_);
   void   GetBeamInfo(dssd_);
};

#endif
