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
    
    
  TString nomefile = "/var/www/html/SFS/SFSNorth.txt"; //percorso
  TGraph *g = new TGraph(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("Solar Field Strenght North");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
  g->SetName("Solar Field Strenght North");
  g->SetMarkerColor(9); //Markers...
  g->SetMarkerStyle(1);
  g->SetLineColor(2);
  g->SetMarkerColor(2);
  g->SetTitle("Solar Field Strnght North ");
  
  //grafico filtrato Notrh
      
  TString nomefilef = "/var/www/html/SFS/SFSNf.txt"; //percorso
  TGraph *gf = new TGraph(nomefilef);
  gf->GetXaxis()->SetTitle("year");
  gf->GetYaxis()->SetTitle("Solar Field Strenght North 20nhz");
  gf->GetXaxis()->CenterTitle();
  gf->GetYaxis()->CenterTitle();
  gf->SetName("Solar Field Strenght North 20nhz");
  gf->SetMarkerColor(9); //Markers...
  gf->SetMarkerStyle(1);
  gf->SetMarkerColor(2);
  gf->SetLineColor(2); gf->SetLineStyle(2);gf->SetLineWidth(4);
  g->SetTitle("Solar Field Strnght North 20nhz ");
    
     
  TString nomefile2 = "/var/www/html/SFS/SFSSouth.txt"; //percorso
  TGraph *k = new TGraph(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("Solar Field Strenght South");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
  k->SetName("Solar Field Strenght South");
  k->SetMarkerColor(2); //Markers...
  k->SetLineColor(38);
  k->SetMarkerColor(38);
  k->SetMarkerStyle(1);
  k->SetTitle("Solar Field Strenght South");
  //grafico filtrato sud
  TString nomefile2f = "/var/www/html/SFS/SFSSf.txt"; //percorso
  TGraph *kf = new TGraph(nomefile2f);
  kf->GetXaxis()->SetTitle("year");
  kf->GetYaxis()->SetTitle("Solar Field Strenght South 20 nhz");
  kf->GetXaxis()->CenterTitle();
  kf->GetYaxis()->CenterTitle();
  kf->SetName("Solar Field Strenght South 20nhz");
  kf->SetMarkerColor(2); //Markers...
  kf->SetLineColor(38);  kf->SetLineStyle(2);kf->SetLineWidth(4);
  kf->SetMarkerStyle(1);
  kf->SetMarkerColor(38);
  kf->SetTitle("Solar Field Strenght South 20nhz");
    
  TString nomefile3 = "/var/www/html/SFS/SFSAvg.txt"; //percorso
  TGraph *h = new TGraph(nomefile3);
  h->GetXaxis()->SetTitle("year");
  h->GetYaxis()->SetTitle("Solar Field Strenght Avg");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetName("Solar Field Strenght Average");
  h->SetMarkerColor(9); //Markers...
  h->SetLineColor(8);
  h->SetMarkerStyle(1);
  h->SetMarkerColor(8);
  h->SetTitle("Solar Field Strenght Average");
    //fitrato AVg
    
    TString nomefile3f = "/var/www/html/SFS/SFSAvgf.txt"; //percorso
        TGraph *hf = new TGraph(nomefile3f);
        hf->GetXaxis()->SetTitle("year");
        hf->GetYaxis()->SetTitle("Solar Field Strenght Avg 20 nhz");
        hf->GetXaxis()->CenterTitle();
        hf->GetYaxis()->CenterTitle();
        hf->SetName("Solar Field Strenght Average 20 nhz");
        hf->SetMarkerColor(9); //Markers...
        hf->SetLineColor(8);hf->SetLineStyle(2); hf->SetLineWidth(4);
        hf->SetMarkerStyle(1);
       hf->SetMarkerColor(8);
        hf->SetTitle("Solar Field Strenght Average 20 nhz");
    
    //create Multigraph with 3 graphs
    
    cout<<"Loading...."<<endl;
    //Dichiaro Canvas
    c1->cd();
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(h);
    mg->Add(g);
    mg->Add(k);
    mg->Add(hf);
    mg->Add(gf);
    mg->Add(kf);
    mg->SetTitle("Solar Strenght North - Sud - Average");
    mg->Draw("apl");
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->CenterTitle();
    mg->GetXaxis()->SetTitle("year");
    mg->GetYaxis()->SetTitle("Solar Field Strenght");
    mg->SetName("Total Graph");
    
    TLegend *legend = new TLegend(.75,.75,.89,.89);
    legend->SetHeader("","C"); // option "C" allows to center the header
    legend->AddEntry(k,"Solar Field Strenght N ","l");
    legend->AddEntry(g,"Solar Field Strenght S","l");
    legend->AddEntry(h,"Solar Field Strenght Avg ","l");
    legend->AddEntry(kf,"Solar Field Strenght N 20 nhz ","l");
    legend->AddEntry(gf,"Solar Field Strenght S 20 nhz ","l");
    legend->AddEntry(hf,"Solar Field Strenght Avg 20 nhz  ","l");
    legend->SetX1NDC(0.01);
    legend->SetX2NDC(0.9);
    legend->Draw();
      
    //creo file di tipo root dove salvo la canvas contenente il grafico creato
 
    TFile ff("/var/www/html/SFS/ROOT/SFS.root" , "recreate");
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

