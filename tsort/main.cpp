#include "tsort.h"
#include <iostream>
#include <map>
#include <TH1F.h>

using namespace std;

int main(int argc,char **argv){
  if(argc!=2){
    cout<<"USAGE: "<<argv[0]<< "#[runnum]"<<endl;
	return 0;
  } 

	int runnum=atoi(argv[1]);
	char ipfn[124];
	char opfn[124];
	char file[124];
	sprintf(ipfn,"/home/wangxiang/shans_data/zhli/spulse/spulse%05d.root",runnum);
	sprintf(file,"spulse%05d.root",runnum);
	//sprintf(ipfn,"~/map%05d.root",runnum);
	TFile *ipf=new TFile(ipfn);
	TTree *ipt=(TTree*)ipf->Get("tree");
	if(ipt==0){
	  cout<<"cannot find input tree!"<<endl;
	  return 1;
	}
	sprintf(opfn,"./sort%05d.root",runnum);
	TFile *opf=new TFile(opfn,"RECREATE");

	TTree *opt=new TTree("tree","tree");

	multimap<ULong64_t,dect_> ts;
	multimap<ULong64_t,dect_>::iterator its,jts;
	tsort *sr=new tsort(ipt);
	sr->BranchOpt(opt);
	sr->MappingTs(ts);
	cout<<"ts size:"<<ts.size()<<endl;
	ULong64_t win=500;
	ULong64_t twl,twh;
	Int_t  cnt=0;
	for(its=ts.begin();its!=ts.end();its++){
		sr->ResetOpt();
		if(its->second.det!=2) continue;
		twl=win>its->first?0:its->first-win;
		twh=win+its->first;
		sr->MappingDet(its->second);
		its->second.det=-1;
		sr->tmpt=its->first;
		for(jts=ts.lower_bound(twl);jts->first<twh;jts++){
			if(jts==ts.end()) break;
			if(jts->second.det==-1) continue;//change detector the initial taging changing.
			sr->MappingDet(jts->second);
			jts->second.det=-1;
			//cout<<"hhhh:"<<tmp<<"twl: "<<twl<<"twh: "<<twh<<"its: "<<its->first<<"jts: "<<jts->first<<endl;
					}
		sr->XYcorrection();
		
		//if(sr->xe[0]>0){
		        opt->Fill();
		        cnt++;
		if(cnt%10000==0) cout<<"Processing... "<<cnt<<endl;
		//}
	}
	opt->Write(); 
	opf->Close();
	cout<<file<<"  done!"<<endl;
	return 1;
}
