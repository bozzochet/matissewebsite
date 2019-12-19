//  lez1.cpp
//  Created by David Pelosi on 02/10/18.
#include <iostream>
#include <iomanip>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TPad.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TColor.h>
#include <TVirtualPad.h>
#include <fstream>
using namespace std;
//------------------------------------------------------------------------------
int main()
{
 
  TCanvas *c1 = new TCanvas("TOTAL Graph","titolo Canvas");
  c1->SetFillColor(0);
    
    
  TString nomefile = "/var/www/html/Tilt/Tilt_R_av.txt"; //percorso
  TGraph *g = new TGraph(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("tilt Angle(deg)");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
  g->SetName("Tilt R_av");
  g->SetMarkerColor(1); //Markers...
  g->SetMarkerStyle(1);
  g->SetLineColor(1);
  g->SetTitle("Tilt Angle ");
  
  //grafico filtrato Notrh
      
  TString nomefilef = "/var/www/html/Tilt/Tilt_R_n.txt"; //percorso
  TGraph *gf = new TGraph(nomefilef);
  gf->GetXaxis()->SetTitle("year");
  gf->GetYaxis()->SetTitle("tilt Angle(deg)");
  gf->GetXaxis()->CenterTitle();
  gf->GetYaxis()->CenterTitle();
  gf->SetName("Tilt R_n");
  gf->SetMarkerColor(2); //Markers...
  gf->SetMarkerStyle(1);
  gf->SetLineColor(2); 
  gf->SetTitle("Tilt Angle");
    
     
  TString nomefile2 = "/var/www/html/Tilt/Tilt_R_s.txt"; //percorso
  TGraph *k = new TGraph(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("tilt Angle (deg)");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
  k->SetName("Tilt R_s");
  k->SetMarkerColor(3); //Markers...
  k->SetLineColor(3);
  k->SetMarkerStyle(1);
  k->SetTitle("Tilt Angle");
  //grafico filtrato sud
  TString nomefile2f = "/var/www/html/Tilt/Tilt_L_av.txt"; //percorso
  TGraph *kf = new TGraph(nomefile2f);
  kf->GetXaxis()->SetTitle("year");
  kf->GetYaxis()->SetTitle("tilt Angle (deg)");
  kf->GetXaxis()->CenterTitle();
  kf->GetYaxis()->CenterTitle();
  kf->SetName("Tilt L_av");
  kf->SetMarkerColor(4); //Markers...
  kf->SetLineColor(4);
  kf->SetMarkerStyle(1);
  kf->SetTitle("Tilt Angle");
    
  TString nomefile3 = "/var/www/html/Tilt/Tilt_L_n.txt"; //percorso
  TGraph *h = new TGraph(nomefile3);
  h->GetXaxis()->SetTitle("year");
  h->GetYaxis()->SetTitle("tilt Angle (deg)");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetName("Tilt L_n");
  h->SetMarkerColor(28); //Markers...
  h->SetLineColor(28);
  h->SetMarkerStyle(1);
  h->SetTitle("Tilt Angle");
  //fitrato AVg
    
  TString nomefile3f = "/var/www/html/Tilt/Tilt_L_s.txt"; //percorso
  TGraph *hf = new TGraph(nomefile3f);
  hf->GetXaxis()->SetTitle("year");
  hf->GetYaxis()->SetTitle("tilt Angle (deg)");
  hf->GetXaxis()->CenterTitle();
  hf->GetYaxis()->CenterTitle();
  hf->SetName("Tilt L_s");
  hf->SetMarkerColor(42); //Markers...
  hf->SetLineColor(42);
  hf->SetMarkerStyle(1);
  hf->SetTitle("Tilt Angle");
    
  //create Multigraph with 3 graphs
    
  cout<<"Loading...."<<endl;
  //Dichiaro Canvas
  c1->cd();
  TMultiGraph *mg = new TMultiGraph();
    
  g->SetLineColor(kOrange+7);
  g->SetMarkerColor(kOrange+7);
  kf->SetLineColor(kAzure);
  kf->SetMarkerColor(kAzure);
  g->SetLineWidth(2);
  g->SetLineStyle(1);
  kf->SetLineWidth(2);
  kf->SetLineStyle(1);
  mg->Add(g);
  mg->Add(kf);
  mg->SetTitle("Tilt Angle");
  mg->Draw("apl");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();
  mg->GetXaxis()->SetTitle("date");
  mg->GetYaxis()->SetTitle("Tilt Angle (deg)");
  mg->SetName("Total Graph");
    
  TLegend *legend = new TLegend(.75,.75,.89,.89);
  legend->SetHeader("","C"); // option "C" allows to center the header
  legend->AddEntry(g,"Tilt Angle R_av","l");
  legend->AddEntry(kf," Tilt Angle L_av","l");
  legend->SetX1NDC(0.01);
  legend->SetX2NDC(0.9);
  legend->Draw();
      
  //creo file di tipo root dove salvo la canvas contenente il grafico creato
 
  TFile ff("/var/www/html/Tilt/ROOT/TILT.root" , "recreate");
  ff.cd();
  k->Write();
  h->Write();
  g->Write();
  kf->Write();
  hf->Write();
  gf->Write();
  c1->Write();
  ff.Close();
  return 0;
}

