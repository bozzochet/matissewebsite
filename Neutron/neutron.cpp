
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
    
  //JUNG----
  TString nomefile = "/var/www/html/Neutron/Jung.txt"; //percorso
  TGraph *g = new TGraph(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("NM Rate");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
  g->SetName("Jung");
  g->SetMarkerColor(kAzure); //Markers...
  g->SetMarkerStyle(22);
  g->SetLineColor(kAzure);
  g->SetTitle("Jung Data");
  g->SetMarkerSize(0.7);
  
  //grafico filtrato Notrh
      
  //Oulu----------
  TString nomefilef = "/var/www/html/Neutron/Oulu.txt"; //percorso
  TGraph *gf = new TGraph(nomefilef);
  gf->GetXaxis()->SetTitle("year");
  gf->GetYaxis()->SetTitle("NM Rate");
  gf->GetXaxis()->CenterTitle();
  gf->GetYaxis()->CenterTitle();
  gf->SetName("Oulu");
  gf->SetMarkerColor(kGreen);//Markers...
  gf->SetLineColor(kGreen);
  gf->SetMarkerStyle(23);
  gf->SetMarkerSize(0.7);
          
  g->SetTitle("Oulu Data");
    
  //kiel -----
  TString nomefile2 = "/var/www/html/Neutron/Kiel.txt"; //percorso
  TGraph *k = new TGraph(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("NM Rate");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
  k->SetName("Kiel");
  k->SetMarkerColor(kMagenta); //Markers...
  k->SetLineColor(kMagenta);
  k->SetMarkerStyle(23);
  k->SetMarkerSize(0.7);
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
  kf->SetMarkerColor(kOrange+7); //Markers...
  kf->SetLineColor(kOrange+7);
  kf->SetMarkerStyle(23);
  kf->SetMarkerSize(0.7);
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
  mg->SetTitle("Neutron Monitor");
  mg->Draw("ap");
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
      
  //creo file di tipo root dove salvo la canvas contenente il grafico creato
 
  TFile ff("/var/www/html/Neutron/ROOT/Neutron.root" , "recreate");
  ff.cd();
  k->Write();
  g->Write();
  kf->Write();
  gf->Write();
  c1->Write();
  ff.Close();
  return 0;
}

