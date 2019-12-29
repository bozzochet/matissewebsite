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
 
  TCanvas *c1 = new TCanvas("TOTAL GraphSet1","titolo Canvas");
  c1->SetFillColor(0);
    
  //JUNG----
  TString nomefile = "/var/www/html/Neutron/Jung.txt"; //percorso
  TGraph *g = new TGraph(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("NM Rate");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
  g->SetName("Jung");
  g->SetLineColor(kAzure);
  g->SetLineWidth(2);
  g->SetLineStyle(1);
  g->SetMarkerColor(kAzure);//Markers...
  g->SetTitle("Jung Data");

  
       
  //Oulu----------
  TString nomefilef = "/var/www/html/Neutron/Oulu.txt"; //percorso
  TGraph *gf = new TGraph(nomefilef);
  gf->GetXaxis()->SetTitle("year");
  gf->GetYaxis()->SetTitle("NM Rate");
  gf->GetXaxis()->CenterTitle();
  gf->GetYaxis()->CenterTitle();
  gf->SetName("Oulu");
  gf->SetLineColor(kGreen);
  gf->SetLineWidth(2);
  gf->SetLineStyle(1);
  gf->SetMarkerColor(kGreen);//Markers...
          
  g->SetTitle("Oulu Data");
    
  //kiel -----
  TString nomefile2 = "/var/www/html/Neutron/Kiel.txt"; //percorso
  TGraph *k = new TGraph(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("NM Rate");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
  k->SetName("Kiel");
  k->SetLineColor(kMagenta);
  k->SetLineWidth(2);
  k->SetLineStyle(1);
  k->SetMarkerColor(kMagenta);//Markers...
  k->SetTitle("Kiel Data");
  //grafico filtrato sud
    
    
  // Newk --
  TString nomefile2f = "/var/www/html/Neutron/Newk.txt"; //percorso
  TGraph *kf = new TGraph(nomefile2f);
  kf->GetXaxis()->SetTitle("year");
  kf->GetYaxis()->SetTitle("NM Rate");
  kf->GetXaxis()->CenterTitle();
  kf->GetYaxis()->CenterTitle();
  kf->SetName("Newk");
  kf->SetLineColor(kOrange+7);
  kf->SetLineWidth(2);
  kf->SetLineStyle(1);
  kf->SetMarkerColor(kOrange+7);//Markers...
  kf->SetTitle("Newk Data");
    
        
  //create Multigraph with 3 graphs
    
  cout<<"Loading...."<<endl;
  //Dichiaro Canvas
  c1->cd();
  TMultiGraph *mg = new TMultiGraph();

  mg->Add(g);
  mg->Add(k);

  mg->Add(gf);
  mg->Add(kf);
  mg->Draw("apl");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();
  mg->GetXaxis()->SetTitle("year");
  mg->GetYaxis()->SetTitle("NM Rate (Hz)");
  mg->SetName("Total Graph");
    
  TLegend *legend = new TLegend(.75,.75,.89,.89);
  legend->SetHeader("","C"); // option "C" allows to center the header
  legend->AddEntry(k,"Kiel","l");
  legend->AddEntry(kf,"Newk ","l");
  legend->AddEntry(g,"Jung","l");
  legend->AddEntry(gf,"Oulu ","l");

  legend->SetX1NDC(0.01);
  legend->SetX2NDC(0.9);
  legend->Draw();
  TFile ff("/var/www/html/Neutron/ROOT/Neutron.root" , "recreate");
  ff.cd();
  k->Write();
  g->Write();
  kf->Write();
  gf->Write();
  c1->Write();
  //creo file di tipo root dove salvo la canvas contenente il grafico creato
    
  //altro set di STAZIONI
  TCanvas *c2 = new TCanvas("TOTAL GraphSet2","titolo Canvas");
  c2->SetFillColor(0);
           
  //MOSC----------
  TString nomefilef2 = "/var/www/html/Neutron/MOSC.txt"; //percorso
  TGraph *gf2 = new TGraph(nomefilef);
  gf2->GetXaxis()->SetTitle("year");
  gf2->GetYaxis()->SetTitle("NM Rate");
  gf2->GetXaxis()->CenterTitle();
  gf2->GetYaxis()->CenterTitle();
  gf2->SetName("MOSC");
  gf2->SetLineColor(kAzure);
  gf2->SetLineWidth(2);
  gf2->SetLineStyle(1);
  gf2->SetMarkerColor(kAzure);//Markers...
  gf2->SetTitle("MOSC Data");
      
      
      
  // APTY --
  TString nomefile2f2 = "/var/www/html/Neutron/APTY.txt"; //percorso
  TGraph *kf2 = new TGraph(nomefile2f2);
  kf2->GetXaxis()->SetTitle("year");
  kf2->GetYaxis()->SetTitle("NM Rate");
  kf2->GetXaxis()->CenterTitle();
  kf2->GetYaxis()->CenterTitle();
  kf2->SetName("APTY");
  kf2->SetLineColor(kGreen);
  kf2->SetLineWidth(2);
  kf2->SetLineStyle(1);
  kf2->SetMarkerColor(kGreen);//Markers...
  kf2->SetTitle("APTY Data");
      
          
  //create Multigraph with 3 graphs
      
  cout<<"Loading...."<<endl;
  //Dichiaro Canvas
  c2->cd();
  TMultiGraph *mg2 = new TMultiGraph();

  mg2->Add(gf2);
  mg2->Add(kf2);
  mg2->Draw("apl");
  mg2->GetXaxis()->CenterTitle();
  mg2->GetYaxis()->CenterTitle();
  mg2->GetXaxis()->SetTitle("year");
  mg2->GetYaxis()->SetTitle("NM Rate (Hz)");
  mg2->SetName("Total Graph");
      
  TLegend *legend2 = new TLegend(.75,.75,.89,.89);
  legend2->SetHeader("","C"); // option "C" allows to center the header
  legend2->AddEntry(kf2,"APTY ","l");
  legend2->AddEntry(gf2,"MOSC ","l");

  legend2->SetX1NDC(0.01);
  legend2->SetX2NDC(0.9);
  legend2->Draw();
    
  ff.cd();
  kf2->Write();
  gf2->Write();
  c2->Write();
    
  ff.Close();
  return 0;
}
