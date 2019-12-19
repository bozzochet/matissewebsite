#include <iostream>
#include <iomanip>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
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

  TCanvas *c1 = new TCanvas("Monthly","titolo Canvas");
  c1->SetFillColor(0);
  c1->cd();
  c1->SetLogy();
    
  TString nomefile2 = "/var/www/html/SolarSmoothed/SSN_MonthlyPLOT.txt"; //percorso
  TGraphErrors *k = new TGraphErrors(nomefile2);
  k->GetXaxis()->SetTitle("year");
  k->GetYaxis()->SetTitle("SSN");
  k->GetXaxis()->CenterTitle();
  k->GetYaxis()->CenterTitle();
  k->SetMarkerColor(kAzure+2);
  k->SetLineColor(kAzure+2);
  k->SetMarkerStyle(20);
  k->SetMarkerSize(0.3);
  k->GetYaxis()->SetRangeUser(0.1,1000);
  k->SetTitle("Solar Spot Number Monthly");
  k->Draw("apl");
    
    
    
  TCanvas *c2 = new TCanvas("Smoothed","titolo Canvas");
  c2->SetFillColor(0);
  c2->cd();
  c2->SetLogy();
    
  TString nomefile = "/var/www/html/SolarSmoothed/SSN_13PLOT.txt"; //percorso
  TGraphErrors *g = new TGraphErrors(nomefile);
  g->GetXaxis()->SetTitle("year");
  g->GetYaxis()->SetTitle("SSN");
  g->GetXaxis()->CenterTitle();
  g->GetYaxis()->CenterTitle();
  g->SetFillColor(kMagenta-7);
  g->SetMarkerColor(kOrange+7);
  g->SetFillStyle(3002);
  g->SetLineColor(kPink-6);
  g->SetLineWidth(4);
  g->GetYaxis()->SetRangeUser(0.1,1000);
  g->Draw("a4l");
  g->SetTitle("Solar Spot Number Smoothed ");
    
 
         
  cout<<"Loading...."<<endl;
  //Dichiaro Canvas
  TCanvas *c3 = new TCanvas("Smoothed-Monthly","titolo Canvas");
  c3->SetFillColor(0);
  c3->cd();
  c3->SetLogy();
    
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(k,"pl");
  mg->Add(g,"4l");
  mg->SetTitle("SSN Smoothed vs SSN Monthly");
  mg->Draw("apl");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->SetRangeUser(0.1,1000);
  mg->GetYaxis()->CenterTitle();

  mg->GetYaxis()->SetTitle("SSN");
  mg->GetXaxis()->SetTitle("year");

  TLegend *legend = new TLegend(.75,.75,.89,.89);
  legend->SetHeader("","C"); // option "C" allows to center the header
  legend->AddEntry(g,"Smoothed SSN","l4");
  legend->AddEntry(k," Monthly SSN","lp");
  legend->SetX1NDC(0.01);
  legend->SetX2NDC(0.9);
  legend->Draw();
      

    
    
    
  TCanvas *c4 = new TCanvas("Smoothed-Monthly NOT LOG","titolo Canvas");
  c4->SetFillColor(0);
  c4->cd();

  TMultiGraph *mg2 = new TMultiGraph();
  g->SetLineWidth(1);
  g->SetLineColor(kOrange+7);

  mg2->Add(k,"pl");
  mg2->Add(g,"pl");
  mg2->SetTitle("SSN Smoothed vs SSN Monthly  ");
  mg2->Draw("apl");
  mg2->GetXaxis()->CenterTitle();
  mg2->GetYaxis()->CenterTitle();
  mg2->GetYaxis()->SetTitle("SSN");
  mg2->GetXaxis()->SetTitle("Date");

     
  legend->Draw();
  //creo file di tipo root dove salvo la canvas contenente il grafico creato
  TFile ff("/var/www/html/SolarSmoothed/ROOT/SolarSmoothed.root","recreate");
  ff.cd();
  c3->Write();
  c4->Write();
  c2->Write();
  c1->Write();
    
  ff.Close();
  return 0;
}
                 

