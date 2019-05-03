//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 24 14:11:09 2016 by ROOT version 5.34/21
// from TTree tree/tree
// found on file: ../mapping/map00307.root
//////////////////////////////////////////////////////////

#ifndef tsort_h
#define tsort_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <map>

using namespace std;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

struct  dect_ {
  Int_t det;
  Int_t fr;
  Int_t str;
  ULong64_t ts;
  Double_t e;
  Int_t np;
  Int_t ip;
  Double_t chi;
  Double_t trapezoidE;
  Double_t slope;
  Double_t eeh;
};

class tsort {      
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           det;
   Int_t           fr;
   Int_t           str;
   ULong64_t       ts;
   Double_t        e;
   Int_t           np;
   Int_t           ip;
   Double_t        ep[10];
   ULong64_t       tsp[10];
   Double_t        chi;
   Double_t        trapezoidE;
   Double_t        slope;
   Double_t        dwave[1500];
   UShort_t        sample[1500];
   Int_t           bd;
   UChar_t         ch;
   Double_t        eeh;
   // Ge calibration
   Double_t gepar[5][2];

   // List of branches
   TBranch        *b_det;   //!
   TBranch        *b_fr;   //!
   TBranch        *b_str;   //!
   TBranch        *b_ts;   //!
   TBranch        *b_e;   //!
   TBranch        *b_dwave;   //!
   TBranch        *b_sample;   //!
   TBranch        *b_bd;   //!
   TBranch        *b_ch;   //!
   TBranch        *b_np;
   TBranch        *b_ip;
   TBranch        *b_ep;
   TBranch        *b_tsp;
   TBranch        *b_chi;
   TBranch        *b_trapezoidE;
   TBranch        *b_slope;
   TBranch        *b_eh;
   TBranch        *b_eeh;

   ULong64_t         mwt;
   Double_t          mwe;

   Int_t             xhit;
   Int_t             yhit;
   Int_t             hit;
   Int_t             x[200];
   Int_t             y[200];
   Double_t          xe[200];
   Double_t          ye[200];
   ULong64_t         xt[200];
   ULong64_t         yt[200];
   Int_t             xx[100];
   Int_t             yy[100];
   Double_t          xxe[100];
   Double_t          yye[100];
   ULong64_t         xxt[100];
   ULong64_t         yyt[100];
   Int_t             npp[100];
   Int_t             ipp[100];
   Double_t        xtrapezoidxE[100];
   Double_t        ytrapezoidyE[100];
   Double_t        xslopex[100];
   Double_t        yslopey[100];
   Double_t         xwavex[100][1500];
   Double_t         ywavey[100][1500];
   Double_t         xeehx[100];
   Double_t         yeehy[100];
   Double_t         wavex[100][1500];
   Double_t         wavey[100][1500];
   Double_t         eehx[100];
   Double_t         eehy[100];

   Double_t        xchix[100];
   Double_t        ychiy[100];
   Double_t        trapezoidxE[100];
   Double_t        trapezoidyE[100];
   Double_t        chix[100];
   Double_t        chiy[100];
   Double_t        slopex[100];
   Double_t        slopey[100];
   ULong64_t         vt[3];
   Double_t          ve[3];

   ULong64_t         gt[100];
   Double_t          ge[100];
   Int_t             ghit;
   Int_t             dt[100];
   ULong64_t         tsi[100];
   ULong64_t         tmpt;

   tsort(TTree *tree=0);
   virtual ~tsort();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void  MappingTs(multimap<ULong64_t,dect_> &mts);
   void  BranchOpt(TTree *opt);
   void  ResetOpt();
   void  MappingDet(dect_&);
   void  XYcorrection();
   void  gammacali();
};

#endif
