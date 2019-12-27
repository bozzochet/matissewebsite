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
 
  TCanvas *c1 = new TCanvas("TOTAL Graph2","titolo Canvas");
  c1->SetFillColor(0);
    
  //INVK----
  TString nomefile = "/var/www/html/Neutron2/INVK.txt"; //percorso
  TGraph *g = new TGraph(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("NM Rate");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
  g->SetName("INVK");
  g->SetMarkerColor(kAzure); //Markers...
  g->SetMarkerStyle(22);
  g->SetLineColor(kAzure);
  g->SetTitle("INVK Data");
  g->SetMarkerSize(0.7);
  
  //grafico filtrato Notrh
      
  //MOSC----------
  TString nomefilef = "/var/www/html/Neutron2/MOSC.txt"; //percorso
  TGraph *gf = new TGraph(nomefilef);
  gf->GetXaxis()->SetTitle("year");
  gf->GetYaxis()->SetTitle("NM Rate");
  gf->GetXaxis()->CenterTitle();
  gf->GetYaxis()->CenterTitle();
  gf->SetName("MOSC");
  gf->SetMarkerColor(kGreen);//Markers...
  gf->SetLineColor(kGreen);
  gf->SetMarkerStyle(23);
  gf->SetMarkerSize(0.7);
          
  g->SetTitle("MOSC Data");
    
  //KERG -----
  TString nomefile2 = "/var/www/html/Neutron2/KERG.txt"; //percorso
  TGraph *k = new TGraph(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("NM Rate");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
  k->SetName("KERG");
  k->SetMarkerColor(kMagenta); //Markers...
  k->SetLineColor(kMagenta);
  k->SetMarkerStyle(23);
  k->SetMarkerSize(0.7);
  k->SetTitle("KERG Data");
  //grafico filtrato sud
    
    
  // APTY --
  TString nomefile2f = "/var/www/html/Neutron2/APTY.txt"; //percorso
  TGraph *kf = new TGraph(nomefile2f);
  kf->GetXaxis()->SetTitle("year");
  kf->GetYaxis()->SetTitle("NM Rate");
  kf->GetXaxis()->CenterTitle();
  kf->GetYaxis()->CenterTitle();
  kf->SetName("APTY");
  kf->SetMarkerColor(kOrange+7); //Markers...
  kf->SetLineColor(kOrange+7);
  kf->SetMarkerStyle(23);
  kf->SetMarkerSize(0.7);
  kf->SetTitle("APTY Data");
    
        
  //create Multigraph with 3 graphs
    
  cout<<"Loading...."<<endl;
  //Dichiaro Canvas
  c1->cd();
  TMultiGraph *mg = new TMultiGraph();

  mg->Add(g);
  mg->Add(k);

  mg->Add(gf);
  mg->Add(kf);
  mg->Draw("ap");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();
  mg->GetXaxis()->SetTitle("year");
  mg->GetYaxis()->SetTitle("NM Rate (Hz)");
  mg->SetName("Total Graph");
    
  TLegend *legend = new TLegend(.75,.75,.89,.89);
  legend->SetHeader("","C"); // option "C" allows to center the header
  legend->AddEntry(k,"KERG","l");
  legend->AddEntry(kf,"APTY ","l");
  legend->AddEntry(g,"INVK","l");
  legend->AddEntry(gf,"MOSC ","l");

  legend->SetX1NDC(0.01);
  legend->SetX2NDC(0.9);
  legend->Draw();
      
  //creo file di tipo root dove salvo la canvas contenente il grafico creato
 
  TFile ff("/var/www/html/Neutron2/ROOT/Neutron.root" , "recreate");
  ff.cd();
  k->Write();
  g->Write();
  kf->Write();
  gf->Write();
  c1->Write();
  ff.Close();
  return 0;
}
