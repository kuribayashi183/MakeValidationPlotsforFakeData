void calculate_Weight(string InputFile){
  using namespace std;
  
  Int_t MAX_VERTEX=1;
  
  TClonesArray* SF_toLFGTwkDialGraph;
  TSpline3 **SF_toLFGTwkDialSpline = new TSpline3 *[MAX_VERTEX];
  
  TChain* fChain = new TChain("sample_sum");


  std::cout << "OK" << std::endl;
  fChain->AddFile(InputFile.c_str());

  SF_toLFGTwkDialGraph = new TClonesArray("TGraph", 0);
  TClonesArray* PionFSI_QEHighMomProbGraph = new TClonesArray("TGraph", 0);  
  
   //Tree entries common to 2013 and 2014.
  Int_t    NSamples;
  Double_t *Enu;
  Double_t *Pmu;
  Double_t *CosThetamu;
  Int_t    *ReactionCode;
  Int_t    *NeutrinoCode;
  Double_t *FluxWeight;
  Double_t DetNomWeight;
  //Kendall's coherent tuning weight
  Double_t *CohTuningWeight;

  Double_t *TruePmu;
  Double_t *TrueCosThetamu;
  Double_t TruePostFSIPiMom;
  Int_t    TruePostFSIPiPDG;
  Int_t    *TrueLepPDG;
  Double_t *Q2;
  Double_t *FFweight; //form factor fake data weights array
  Double_t *Q2QE;
  Char_t   *HaveTruth;
  Int_t    *TgtMat;
  Int_t    *NuParent;
  Int_t    Run;
  Int_t    *TruthVtx;

  TBranch *b_Enu;          //!
  TBranch *b_Pmu;          //!
  TBranch *b_CosThetamu;   //!
  TBranch *b_ReactionCode; //!
  TBranch *b_NeutrinoCode; //!
  TBranch *b_FluxWeight;   //!
  TBranch *b_DetNomWeight; //!
  //Kendall CCCoh weight
  TBranch *b_CohTuningWeight; //!
  TBranch *b_TruePmu;         //!
  TBranch *b_TrueLepPDG;      //!
  TBranch *b_TrueCosThetamu;  //!
  TBranch *b_TruePostFSIPiMom;
  TBranch *b_TruePostFSIPiPDG;
  TBranch *b_Q2;             //!
  TBranch *b_FFweight;       //!
  TBranch *b_Q2QE;           //!
  TBranch *b_HaveTruth;      //!
  TBranch *b_TgtMat;         //!
  TBranch *b_NuParent;       //!
  TBranch *b_Run;            //!
  TBranch *b_TruthVtx;       //!

  TBranch *b_PionFSI_QEHighMomProbGraph;
  TBranch *b_SF_toLFGTwkDialGraph;       //!


  Enu             = new Double_t[MAX_VERTEX];
  Pmu             = new Double_t[MAX_VERTEX];
  CosThetamu      = new Double_t[MAX_VERTEX];
  ReactionCode    = new Int_t[MAX_VERTEX];
  NeutrinoCode    = new Int_t[MAX_VERTEX];
  FluxWeight      = new Double_t[MAX_VERTEX];
  // Kendall CCCoh tuning
  CohTuningWeight = new Double_t[MAX_VERTEX];
  TruePmu         = new Double_t[MAX_VERTEX];
  TrueLepPDG      = new Int_t[MAX_VERTEX];
  TrueCosThetamu  = new Double_t[MAX_VERTEX];
  Q2              = new Double_t[MAX_VERTEX];
  Q2QE            = new Double_t[MAX_VERTEX];
  HaveTruth       = new Char_t[MAX_VERTEX];
  TgtMat          = new Int_t[MAX_VERTEX];
  NuParent        = new Int_t[MAX_VERTEX];
  TruthVtx        = new Int_t[MAX_VERTEX];

  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("CosThetamu", CosThetamu, &b_CosThetamu);
  fChain->SetBranchAddress("ReactionCode", ReactionCode, &b_ReactionCode);
  fChain->SetBranchAddress("NeutrinoCode", NeutrinoCode, &b_NeutrinoCode);
  fChain->SetBranchAddress("FluxWeight", FluxWeight, &b_FluxWeight);
  fChain->SetBranchAddress("DetNomWeight", &DetNomWeight, &b_DetNomWeight);
  fChain->SetBranchAddress("TruePmu", TruePmu, &b_TruePmu);
  fChain->SetBranchAddress("TrueLepPDG", TrueLepPDG, &b_TrueLepPDG);
  fChain->SetBranchAddress("TrueCosThetamu", TrueCosThetamu, &b_TrueCosThetamu);
  fChain->SetBranchAddress("TruePostFSIPiMom", &TruePostFSIPiMom, &b_TruePostFSIPiMom);
  fChain->SetBranchAddress("TruePostFSIPiPDG", &TruePostFSIPiPDG, &b_TruePostFSIPiPDG);
  fChain->SetBranchAddress("Q2", Q2, &b_Q2);
 // fChain->SetBranchAddress("FFweight", FFweight, &b_FFweight);
  fChain->SetBranchAddress("Q2QE", Q2QE, &b_Q2QE);
  fChain->SetBranchAddress("HaveTruth", HaveTruth, &b_HaveTruth);
  fChain->SetBranchAddress("TgtMat", TgtMat, &b_TgtMat);
  fChain->SetBranchAddress("NuParent", NuParent, &b_NuParent);
  fChain->SetBranchAddress("Run", &Run, &b_Run);
  fChain->SetBranchAddress("TruthVtx", TruthVtx, &b_TruthVtx);

  fChain->SetBranchAddress("PionFSI_QEHighMomProbGraph", &PionFSI_QEHighMomProbGraph, &b_PionFSI_QEHighMomProbGraph);
  fChain->SetBranchAddress("SF_toLFGTwkDialGraph", &SF_toLFGTwkDialGraph, &b_SF_toLFGTwkDialGraph);

  Double_t Weight_SF_toLFGTwk;
  //Double_t Q2;
  //Double_t Q2;
  //TTree *SF_toLFGTwkDialTree = new TTree("SF_toLFGTwkDialTree","SF_toLFGTwkDialTree");
  //SF_toLFGTwkDialTree->Branch("DialValue_SF_toLFGTwk", &DialValue_SF_toLFGTwk);
  //SF_toLFGTwkDialTree->Branch("Weight_SF_toLFGTwk", &Weight_SF_toLFGTwk);
  TH1D *hQ2 = new TH1D("hQ2","hQ2",80,0,2);  
  TH1D *hQ2_FD = new TH1D("hQ2_FD","hQ2_FD",80,0,2);  
  TH1D *hQ2_ratio = new TH1D("hQ2_ratio","hQ2_ratio",80,0,2);    

  TH1D *hrecE = new TH1D("hrecE","hrecE",80,0,2);  
  TH1D *hrecE_FD = new TH1D("hrecE_FD","hrecE_FD",80,0,2);  
  TH1D *hrecE_ratio = new TH1D("hrecE_ratio","hrecE_ratio",80,0,2);    


  Double_t Weight_FD = 1;
  Double_t Weight_Nom = 1;

  for(int ientry = 0; ientry < fChain->GetEntries(); ientry++){

    fChain->GetEntry(ientry); 

    TGraph *cast_SF_toLFGTwkDialGraph = (TGraph *)(SF_toLFGTwkDialGraph->At(0));
    if(ReactionCode[0]==-1){
      if(cast_SF_toLFGTwkDialGraph->GetN()==1){
        Weight_FD = 1;
        Weight_Nom = 1;
      }else{
        SF_toLFGTwkDialSpline[0] = new TSpline3("SF_toLFGTwkDialSpline", cast_SF_toLFGTwkDialGraph);
        Weight_FD = SF_toLFGTwkDialSpline[0]->Eval(1);    
        Weight_Nom = SF_toLFGTwkDialSpline[0]->Eval(0);

        //Double_t Weight_Nom = 1;
      }
      //to select CCQE events
      std::cout << "ientry : Weight Nom : FD " << ientry << " " << Weight_Nom << " "<< Weight_FD << endl;
      hQ2->Fill(Q2[0], Weight_Nom);
      hQ2_FD->Fill(Q2[0], Weight_FD); 
      hrecE->Fill(Q2[0], Weight_Nom);
      hrecE_FD->Fill(Q2[0], Weight_FD);       
    }
  }
  //if(ReactionCode[0]==-1){
  for(int i = 0; i< 80;i++){
    if(hQ2->GetBinContent(i+1)== 0){
      hQ2_ratio->SetBinContent(i+1, 1);   
    }else{
      hQ2_ratio->SetBinContent(i+1, hrecE_FD->GetBinContent(i+1)/hrecE->GetBinContent(i+1));   
    } 
    if(hrecE->GetBinContent(i+1)== 0){
      hrecE_ratio->SetBinContent(i+1, 1);         
    }else{
      hrecE_ratio->SetBinContent(i+1, hrecE_FD->GetBinContent(i+1)/hrecE->GetBinContent(i+1));             
    }
  }
  //}

  gStyle->SetOptStat(0);
  
  hQ2->SetTitle("Q2(SF_LFGTwkDial); Q^{2}(GeV^{2}); Total weight");
  hQ2_ratio->SetTitle(";Q^{2}(GeV^{2});Ratio");
  hQ2->SetLineColor(kBlack);
  hQ2_FD->SetLineColor(kBlue);  
  hQ2_ratio->SetLineColor(kBlue);    

  hrecE->SetTitle("recE(SF_LFGTwkDial); recE(GeV); Total weight");
  hrecE_ratio->SetTitle(";recE(GeV);Ratio");
  hrecE->SetLineColor(kBlack);
  hrecE_FD->SetLineColor(kBlue);  
  hrecE_ratio->SetLineColor(kBlue);      

  TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
  leg->AddEntry(hQ2, "SF","l");
  leg->AddEntry(hQ2_FD , "SFtoLFGTwk dial value = 1","l");  
  leg->SetFillColor(0);

  TLegend *legrecE = new TLegend(0.6, 0.7, 0.9, 0.9);
  legrecE->AddEntry(hrecE, "SF","l");
  legrecE->AddEntry(hrecE_FD , "SFtoLFGTwk dial value = 1","l");  
  legrecE->SetFillColor(0);  

  TCanvas *c1 = new TCanvas("c1","c1");  
  c1->cd();
  TPad *pad1 = new TPad("pad1","pad1",0.,0.3,1.0,1.0,21);
  TPad *pad2 = new TPad("pad2","pad2",0.,0.0,1.0,0.3,22);  
  pad1->SetFillColor(0);  
  pad2->SetFillColor(0);  
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  hQ2->Draw("");
  hQ2_FD->Draw("same");  
  leg->Draw();
  pad2->cd();
  hQ2_ratio->Draw("");
  c1->SaveAs("test_Q2_CCQE.pdf");

  TCanvas *c2 = new TCanvas("c2","c2");  
  c2->cd();
  TPad *pad1 = new TPad("pad1","pad1",0.,0.3,1.0,1.0,21);
  TPad *pad2 = new TPad("pad2","pad2",0.,0.0,1.0,0.3,22);  
  pad1->SetFillColor(0);  
  pad2->SetFillColor(0);  
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  hrecE->Draw("");
  hrecE_FD->Draw("same");  
  legrecE->Draw();
  pad2->cd();
  hrecE_ratio->Draw("");
  c1->SaveAs("test_recE_CCQE.pdf");  
  /*std::vector<Double_t> Weight_SF_toLFGTwk;
  std::vector<Double_t> DialValue_SF_toLFGTwk;  
  TTree *SF_toLFGTwkDialTree = new TTree("SF_toLFGTwkDialTree","SF_toLFGTwkDialTree");
  SF_toLFGTwkDialTree->Branch("DialValue_SF_toLFGTwk", &DialValue_SF_toLFGTwk);
  SF_toLFGTwkDialTree->Branch("Weight_SF_toLFGTwk", &Weight_SF_toLFGTwk);

  for(int i = 0; i< fChain->GetEntries(); i++) {
    fChain->GetEntry(i);
    for(int j=0; j< cast_SF_toLFGTwkDialGraph->GetN(); j++){
      double dial_value = cast_SF_toLFGTwkDialGraph ->GetPointX(j);
      double weight_dail = cast_SF_toLFGTwkDialGraph->GetPointY(j);
      std::cout << "# of points = " << cast_SF_toLFGTwkDialGr
      aph->GetN() << std::endl;
      std::cout << "dial value =  " << dial_value << std::endl;
      std::cout << "weight value = " << weight_dail << std::endl;    
      DialValue_SF_toLFGTwk.push_back(dial_value);
      Weight_SF_toLFGTwk.push_back(weight_dail);    
    }
    SF_toLFGTwkDialTree->Fill();  
  }
  //std::string OutputFile = Form("%s_output.root");
  std::string OutputFile = "test_output.root";

  TFile *ofile = new TFile(OutputFile.c_str(),"recreate");
  ofile->cd();
  SF_toLFGTwkDialTree->Write();*/

  }