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
#include <TROOT.h>
#include <iostream>
#include <fstream>
#include <TColor.h>
#include <TVirtualPad.h>
#include <TBufferJSON.h>
#include <THttpServer.h>
#include <fstream>
using namespace std;
//------------------------------------------------------------------------------
int main()
{
    
 
    
  //Dichiaro Canvas
  TCanvas *c1 = new TCanvas("c1","titolo Canvas");
  c1->SetFillColor(19);
  c1->cd();
    
  TString nomefile = "/var/www/html/SSN/SSNPLOT.txt"; //percorso
  TGraphErrors *g = new TGraphErrors(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("SunSpot Number");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
        
  g->SetMarkerColor(9); //Markers...
  g->SetMarkerStyle(1);
  g->SetTitle("Solar Spot Number");
  g->SetName("Graph with Errors");
  g->Draw("ap");

   
  c1->Update();
  c1->Modified();
    
  TCanvas *c2 = new TCanvas("c2","titolo Canvas");
  c2->SetFillColor(19);
  c2->cd();
     
  TString nomefile2 = "/var/www/html/SSN/SSNLINE.txt"; //percorso
  TGraph *k = new TGraph(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("SunSpot Number");
  k->SetName("Graph");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
         
  k->SetMarkerColor(9); //Markers...
  k->SetLineColor(9);
  k->SetMarkerStyle(1);
  k->SetTitle("Solar Spot Number");
  k->Draw("APL");
         
    
  c2->Update();
  c2->Modified();

    
  //creo file di tipo root dove salvo la canvas contenente il grafico creato
  TFile ff("/var/www/html/SSN/ROOT/SSN.root","recreate");
  ff.cd();
  k->Write();
  g->Write();
  ff.Close();
  return 0;
}


