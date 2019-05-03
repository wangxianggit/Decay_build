#include "decay.h"
#include <iostream>
#include <map>

using namespace std;

int main(int argc,char **argv){
  if(argc!=2){
    cout<<"USAGE: "<<argv[0]<< "#[runnum]"<<endl;
	return 0;
  }

	int runnum=atoi(argv[1]);
	char ipfn[124];
	char opfn[124];
	sprintf(ipfn,"../tsort/sort%05d.root",runnum);
	TFile *ipf=new TFile(ipfn);
	TTree *ipt=(TTree*)ipf->Get("tree");
	if(ipt==0){
	  cout<<"cannot find input tree!"<<endl;
	  return 1;
	}
	sprintf(opfn,"./decay%05d.root",runnum);
	TFile *opf=new TFile(opfn,"RECREATE");

	TTree *opt=new TTree("tree","tree");

	map<ULong64_t,dssd_> ts;
	map<ULong64_t,dssd_>::iterator its,jts;

	decay *dc=new decay(ipt);
	dc->BranchOpt(opt);
	dc->MappingTs(ts);
	cout<<"ts size:"<<ts.size()<<endl;
	Long64_t lwin=0000ll;
	Long64_t lhig=1000000000ll;
	Long64_t twl,twh;
	Int_t  cnt=0;
	for(its=ts.begin();its!=ts.end();its++){
		if(!its->second.IsBeam) continue;
		dc->ResetOpt();
		
		twl=its->first+lwin;
		twh=its->first+lhig;
		dssd_ beam = its->second;
		dc->GetBeamInfo(beam);
		for(jts=ts.lower_bound(twl);jts->first<(ULong64_t)twh;jts++){
			if(jts==ts.end()) break;
			dssd_ d1=jts->second;
			if(d1.IsBeam) continue;
			if(TMath::Abs(d1.x-beam.x)>0||TMath::Abs(d1.y-beam.y)>0) continue;
			dc->GetDecayInfo(jts->second);
			//cout<<"hhhh:"<<tmp<<"twl: "<<twl<<"twh: "<<twh<<"its: "<<its->first<<"jts: "<<jts->first<<endl;
		}
		opt->Fill();
		cnt++;
		if(cnt%10000==0) cout<<"Processing... "<<cnt<<endl;
	}
	cout<<"**********"<<endl;
	opt->Write();
	opf->Close();

	return 1;
}
