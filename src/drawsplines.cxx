void drawsplines(string InputFile){
  using namespace std;
  
  Int_t MAX_VERTEX=1;
  
  TClonesArray* SF_toLFGTwkDialGraph;
  TSpline3 **SF_toLFGTwkDialSpline = new TSpline3 *[MAX_VERTEX];

  TClonesArray* MAQEGraph;
  TSpline3 **MAQESpline = new TSpline3 *[MAX_VERTEX];
  
  TChain* fChain = new TChain("sample_sum");


  std::cout << "OK" << std::endl;
  fChain->AddFile(InputFile.c_str());

  MAQEGraph = new TClonesArray("TGraph", 0);
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
  TBranch *b_MAQEGraph;       //!  


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
  fChain->SetBranchAddress("MAQEGraph", &MAQEGraph, &b_MAQEGraph);  

  for(int ientry = 0; ientry < 100; ientry++){
  //for(int ientry = 830; ientry < 831; ientry++){
  //for(int ientry = 1492; ientry < 1501; ientry++){      

    fChain->GetEntry(ientry); 
    TGraph *cast_SF_toLFGTwkDialGraph = (TGraph *)(SF_toLFGTwkDialGraph->At(0));
    TGraph *cast_MAQEGraph = (TGraph *)(MAQEGraph->At(0));    
    SF_toLFGTwkDialSpline[0] = new TSpline3("SF_toLFGTwkDialSpline", cast_SF_toLFGTwkDialGraph);
    MAQESpline[0] = new TSpline3("MAQESpline", cast_MAQEGraph);    

  /*  cast_SF_toLFGTwkDialGraph->SetMarkerStyle(31);
    cast_SF_toLFGTwkDialGraph->SetMarkerColor(kRed);
    cast_SF_toLFGTwkDialGraph->SetTitle(Form("SF_toLFG_TwkDial entry # = %d",ientry));    
    cast_SF_toLFGTwkDialGraph->GetYaxis()->SetRangeUser(-1.2,2.4);              

    SF_toLFGTwkDialSpline[0]->SetLineColor(kBlue);

    TLegend *leg = new TLegend(0.8, 0.4, 0.99, 0.6);
    leg->AddEntry(cast_SF_toLFGTwkDialGraph, "cast_SF_toLFGTwkDialGraph","p");
    leg->AddEntry(SF_toLFGTwkDialSpline[0] , "SF_toLFGTwkDialSpline","l");  
    leg->SetFillColor(0);
    TCanvas *c1 = new TCanvas("c1","c1", 800, 800);
    c1->cd();
    cast_SF_toLFGTwkDialGraph->Draw("AP");
    SF_toLFGTwkDialSpline[0]->Draw("samel");        
    
    leg->Draw();  */

    cast_MAQEGraph->SetMarkerStyle(31);
    cast_MAQEGraph->SetMarkerColor(kRed);
    cast_MAQEGraph->SetTitle(Form("MAQE entry # = %d",ientry));    
    cast_MAQEGraph->GetYaxis()->SetRangeUser(-1.2,2.4);              

    MAQESpline[0]->SetLineColor(kBlue);

    TLegend *leg = new TLegend(0.8, 0.4, 0.99, 0.6);
    leg->AddEntry(cast_MAQEGraph, "cast_MAQEGraph","p");
    leg->AddEntry(MAQESpline[0] , "MAQESpline","l");  
    leg->SetFillColor(0);
    TCanvas *c1 = new TCanvas("c1","c1", 800, 800);
    c1->cd();
    cast_MAQEGraph->Draw("AP");
    MAQESpline[0]->Draw("samel");        
    
    leg->Draw();      

//  TCanvas *c2 = new TCanvas("c1","c1");
  //c2->cd();
 // PionFSI_QEHighMomProbGraph->Draw("A*");

  //std::cout << "Value " << << " " << << std::endl;
    //c1->SaveAs(Form("WeightGraph_%d.pdf",ientry));
    c1->SaveAs(Form("MAQEGraph_%d.pdf",ientry));    
  }

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
      std::cout << "# of points = " << cast_SF_toLFGTwkDialGraph->GetN() << std::endl;
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
