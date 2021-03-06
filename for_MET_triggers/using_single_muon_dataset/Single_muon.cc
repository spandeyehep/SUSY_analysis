#define Single_muon_cxx
#include "Single_muon.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Please give 3 arguments " << "runList " << " " << "outputFileName" << " " << "dataset" << endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *data          = argv[3];

  Single_muon ana(inputFileList, outFileName, data);
  cout << "dataset " << data << " " << endl;

  ana.EventLoop(data,inputFileList);

  return 0;
}

void Single_muon::EventLoop(const char *data,const char *inputFileList) {
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing dataset " << data << " " << endl;

  Long64_t nbytes = 0, nb = 0;
  int decade = 0;
  // TTree *newtree = fChain->CloneTree(0);

  string s_data=data;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // ==============print number of events done == == == == == == == =
    double progress = 10.0 * jentry / (1.0 * nentries);
    int k = int (progress);
    if (k > decade)
      cout << 10 * k << " %" <<endl;
    decade = k;
    // cout<<"j:"<<jentry<<" fcurrent:"<<fCurrent<<endl;
    // ===============read this entry == == == == == == == == == == == 
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    double wt=1.0;
    h_selectBaselineYields_->Fill(0);
    
    TLorentzVector bestPhoton = getBestPhoton();
    // if(bestPhotonIndxAmongPhotons<0) continue;
    // if( (*Photons_hasPixelSeed)[bestPhotonIndxAmongPhotons] > 0.001 ) continue;

    //    bool passTrg = false, passMETTrg = false;
    bool passTrg=false,passPhoTrg=false,passReqTrg=false,passHTxPhoTrg=false;

    for(int i=0;i<TriggerNames->size();i++){
      TString trgName=(*TriggerNames)[i];
   
      
      if( trgName.Contains("HLT_IsoMu20_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(1); passTrg = true;}
      else if( trgName.Contains("HLT_IsoMu22_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(2); passTrg = true;}
      else if( trgName.Contains("HLT_IsoMu24_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(3); passTrg = true;}
      else if( trgName.Contains("HLT_IsoMu27_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(4); passTrg = true;}
      else if( trgName.Contains("HLT_IsoTkMu22_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(5); passTrg = true;}
      else if( trgName.Contains("HLT_IsoTkMu24_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(6); passTrg = true;}
      else if( trgName.Contains("HLT_Mu50_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(7); passTrg = true;}
      else if( trgName.Contains("HLT_Mu55_v") && (*TriggerPass)[i]==1)         { h_selectBaselineYields_->Fill(8); passTrg = true;}

      // if( trgName.Contains("HLT_PFMET90_PFMHT90_IDTight_v") && (*TriggerPass)[i]==1 )        { h_selectBaselineYields_->Fill(1); passTrg = true;}
      // else if( trgName.Contains("HLT_PFMET100_PFMHT100_IDTight_v") && (*TriggerPass)[i]==1 ) { h_selectBaselineYields_->Fill(2); passTrg = true;}
      // else if( trgName.Contains("HLT_PFMET110_PFMHT110_IDTight_v") && (*TriggerPass)[i]==1 ) { h_selectBaselineYields_->Fill(3); passTrg = true;}
      // else if( trgName.Contains("HLT_PFMET120_PFMHT120_IDTight_v") && (*TriggerPass)[i]==1 ) { h_selectBaselineYields_->Fill(4); passTrg = true;}
      // else if( trgName.Contains("HLT_Photon90_CaloIdL_PFHT600_v") && (*TriggerPass)[i]==1 )  { h_selectBaselineYields_->Fill(5); passTrg = true;}
      // else if( trgName.Contains("HLT_Photon165_HE10_v") && (*TriggerPass)[i]==1 )            { h_selectBaselineYields_->Fill(6); passTrg = true;}

      // else if( trgName.Contains("HLT_Ele15_IsoVVVL_PFHT350_v") && (*TriggerPass)[i]==1 )     { h_selectBaselineYields_->Fill(7); passTrg = true;}
      // else if( trgName.Contains("HLT_Ele32_eta2p1_WPTight_Gsf_v") && (*TriggerPass)[i]==1 )         { h_selectBaselineYields_->Fill(8); passTrg = true;}
      // else if( trgName.Contains("HLT_IsoMu24_v") && (*TriggerPass)[i]==1 )                   { h_selectBaselineYields_->Fill(9); passTrg = true;}
      // else if( trgName.Contains("HLT_Mu15_IsoVVVL_PFHT350_v") && (*TriggerPass)[i]==1 )        { h_selectBaselineYields_->Fill(10); passTrg = true;}

      /*if( trgName.Contains("HLT_PFHT300_v") && (*TriggerPass)[i]==1 )                  { h_selectBaselineYields_->Fill(1); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT350_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(2); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT400_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(3); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT475_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(4); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT600_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(5); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT650_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(6); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT800_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(7); passTrg = true;}
	else if( trgName.Contains("HLT_PFHT900_v") && (*TriggerPass)[i]==1 )             { h_selectBaselineYields_->Fill(8); passTrg = true;}
	else if( trgName.Contains("HLT_Photon90_CaloIdL_PFHT600_v") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(9); passReqTrg = true;}*/
      //else if( trgName.Contains("HLT_Photon165_HE10_v") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(9); passReqTrg = true;}

      //------------------first trial for MET triggers efficiency-------------------------------------------//
      // if( trgName.Contains("HLT_PFMET90_PFMHT90_IDTight_v") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(3); passReqTrg = true;}
      // else if( trgName.Contains("HLT_PFMET100_PFMHT100_IDTight_v") && (*TriggerPass)[i]==1 ) { h_selectBaselineYields_->Fill(4); passReqTrg = true;}
      // else if( trgName.Contains("HLT_PFMET110_PFMHT110_IDTight_v") && (*TriggerPass)[i]==1 ) { h_selectBaselineYields_->Fill(5); passReqTrg = true;}
      // else if( trgName.Contains("HLT_PFMET120_PFMHT120_IDTight_v") && (*TriggerPass)[i]==1 ) { h_selectBaselineYields_->Fill(6); passReqTrg = true;}

      if( trgName.Contains("HLT_PFHT300_PFMET100_v") && (*TriggerPass)[i]==1)      { h_selectBaselineYields_->Fill(9); passReqTrg = true;}
      else if( trgName.Contains("HLT_PFHT300_PFMET110_v") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(10); passHTxPhoTrg = true;}


      // if( trgName.Contains("HLT_PFMET300") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(6); p = true;}


      // if( trgName.Contains("HLT_PFHT300_PFMET100") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(9); passReqTrg = true;}
      // else if( trgName.Contains("HLT_Photon90_CaloIdL_PFHT600_v") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(10); passHTxPhoTrg = true;}
	// else if( trgName.Contains("HLT_Photon90_CaloIdL_PFHT600_v") && (*TriggerPass)[i]==1 )      { h_selectBaselineYields_->Fill(9); passReqTrg = true;}      
      // cout<<(*TriggerNames)[i]<<" "<<(*TriggerPass)[i]<<" "<<(*TriggerPrescales)[i]<<" "<<trgName<<endl;
      
    }
    if(!passTrg) continue;
    //    if(HT<800) continue;
    // if(bestPhoton.Pt()<100) continue;
    bool hadJetID=true;
    //----------------------if we are also using HT X Photon triggers------------------------
    // int minDRindx=-100,photonMatchingJetIndx=-100,nHadJets=0;
    // double minDR=99999,ST=0;
    // vector<TLorentzVector> hadJets;

    // for(int i=0;i<Jets->size();i++){
    //   if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
    // 	double dR=bestPhoton.DeltaR((*Jets)[i]);
    // 	if(dR<minDR){minDR=dR;minDRindx=i;}
    //   }
    // }
    
    // for(int i=0;i<Jets->size();i++){
    //   if( ((*Jets)[i].Pt() > 30.0) && (abs((*Jets)[i].Eta()) <= 2.4) ){
    // 	if( !(minDR < 0.3 && i==minDRindx) ){
    // 	  hadJets.push_back((*Jets)[i]);
    // 	  if(hadJetID) hadJetID=(*Jets_ID)[i];
    // 	}
    //   }
    // }
    // if( minDR<0.3 ) photonMatchingJetIndx=minDRindx;
    // for(int i=0;i<hadJets.size();i++){
    //   if( (abs(hadJets[i].Eta()) < 2.4) ){ST=ST+(hadJets[i].Pt());}
    //   if( (abs(hadJets[i].Eta()) < 2.4) ){nHadJets++;}
    // }
    // if( minDR<0.3 ){
    //   ST=ST+bestPhoton.Pt();
    // }
    // if( !((ST>800 && bestPhoton.Pt()>100) || (bestPhoton.Pt()>190)) )  continue;
    // if(ST < 800) continue;
    // if (MET < 250) continue;
    if(hadJetID){
      // h_ST->Fill(ST,wt);
      h_MET->Fill(MET,wt);
      // h_nHadJets->Fill(nHadJets,wt);
      h_BTags->Fill(BTags,wt);
      h_BestPhotonPt->Fill(bestPhoton.Pt(),wt);
      h_HT->Fill(HT,wt);
      h_MHT->Fill(MHT,wt);
      h_nJets->Fill(NJets,wt);
      h_METvBin->Fill(MET,wt);

      // h_STvBin->Fill(ST,wt);
      h_BestPhotonPt_vBin->Fill(bestPhoton.Pt(),wt);
      h_BestPhotonPt_vBin2->Fill(bestPhoton.Pt(),wt);
      h_HTvBin->Fill(HT,wt);
      // h2_PhoPtST->Fill(bestPhoton.Pt(),ST,wt);

      if(passTrg && passReqTrg){
	//if(passTrg && (passReqTrg || passHTxPhoTrg) ){
	// h_ST_Req->Fill(ST,wt);
	h_MET_Req->Fill(MET,wt);
	h_METvBin_Req->Fill(MET,wt);
	// h_nHadJets_Req->Fill(nHadJets,wt);
	h_BTags_Req->Fill(BTags,wt);
	h_BestPhotonPt_Req->Fill(bestPhoton.Pt(),wt);
	h_HT_Req->Fill(HT,wt);
	h_MHT_Req->Fill(MHT,wt);
	h_nJets_Req->Fill(NJets,wt);

	// h_STvBin_Req->Fill(ST,wt);
	h_BestPhotonPt_vBin_Req->Fill(bestPhoton.Pt(),wt);
	h_BestPhotonPt_vBin2_Req->Fill(bestPhoton.Pt(),wt);
	h_HTvBin_Req->Fill(HT,wt);
	// h2_PhoPtST_Req->Fill(bestPhoton.Pt(),ST,wt);
      }

    }

    //    newtree->Fill();
    
  } // loop over entries
  //  newtree->AutoSave();
}

TLorentzVector Single_muon::getBestPhoton(){
  vector<TLorentzVector> goodPho;
  vector<int> goodPhoIndx;
  for(int iPho=0;iPho<Photons->size();iPho++){
    if( (*Photons_fullID)[iPho] ) {
      goodPho.push_back( (*Photons)[iPho] );
      goodPhoIndx.push_back(iPho);
    }
  }
  
  int highPtIndx=-100;
  for(int i=0;i<goodPho.size();i++){
    if(i==0) highPtIndx=0;
    else if( (goodPho[highPtIndx].Pt()) < (goodPho[i].Pt()) ){highPtIndx=i;}
  }
  
  if(highPtIndx>=0){
    bestPhotonIndxAmongPhotons = goodPhoIndx[highPtIndx];
  }
  else bestPhotonIndxAmongPhotons = -100;
  if(highPtIndx==-100){TLorentzVector v0;return v0;}
  else return goodPho[highPtIndx];
}


/*
  int bestPhoIndx=-100;
  TLorentzVector v1;
  vector<TLorentzVector> goodPho;
  for(int iPhoton=0;iPhoton<Photons->size();iPhoton++){
    if( (*Photons_fullID)[iPhoton] ) goodPho.push_back( (*Photons)[iPhoton] );
  }

  if(goodPho.size()==0) return v1;
  else if(goodPho.size()==1) return goodPho[0];
  else{
    for(int i=0;i<goodPho.size();i++){
      if(i==0) bestPhoIndx=0;
      else if(goodPho[bestPhoIndx].Pt() < goodPho[i].Pt()) bestPhoIndx=i;
    }
    return goodPho[bestPhoIndx];
  }
*/
