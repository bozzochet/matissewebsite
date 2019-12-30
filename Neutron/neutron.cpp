//  lez1.cpp
//  Created by David Pelosi on 02/10/19.
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
#include <string>
#include <sstream>
using namespace std;
//------------------------------------------------------------------------------
int main()
{
    
  TFile ff("/var/www/html/Neutron/ROOT/Neutron.root" , "recreate");
  int color[6] = {416,807,860,616,1,4};
  for (int y = 1; y<3; y++) {  // 2 set di stazioni
    vector<string> stats;
    vector<TString> stations;

    ifstream set;
    stringstream ss;
    ss<<y;
    string s;
    ss>>s;
    string path ="/var/www/html/FFModel/NM_Set" + s + ".txt";
    cout<<path<<endl;
     
    set.open(path);
    string sx;
    while (!set.eof()) {
      set>>sx>>ws;
      stats.push_back(sx);
      stations.push_back(sx);
    }
 
    
    //lita delle stazioni 6
    TCanvas *c = new TCanvas("TOTAL Graph","titolo Canvas");
    TLegend *legend = new TLegend(.75,.75,.89,.89);
    legend->SetHeader("","C");
    legend->SetX1NDC(0.01);
    legend->SetX2NDC(0.9);
    TMultiGraph *mg = new TMultiGraph();

    for (int i=0; i<stats.size(); i++) {
      //i-esima stazione
      ff.cd();
      TString nomefile = stats[i]+".txt"; //percorso
      TGraph *g = new TGraph(nomefile);
      g->GetXaxis()->SetTitle("year");
      g->GetYaxis()->SetTitle("NM Rate");
      g->GetXaxis()->CenterTitle();
      g->GetYaxis()->CenterTitle();
      g->SetName(stations[i]);
      g->SetLineColor(color[i]);
      g->SetMarkerColor(color[i]);
      g->SetLineWidth(2);
      g->SetLineStyle(1);
      g->SetTitle(stations[i] +"Data");
      cout<<"Loading...."<<endl;

      mg->Add(g);legend->AddEntry(g,stations[i],"l");
      g->Write();
    
    }
    c->cd();
    mg->Draw("apl");
    mg->GetXaxis()->CenterTitle();
    mg->GetYaxis()->CenterTitle();
    mg->GetXaxis()->SetTitle("year");
    mg->GetYaxis()->SetTitle(" Rate (Hz)");
    mg->SetName("Total Graph");
    legend->Draw();
    
    ff.cd();
    c->Write();
  }
  
  ff.Close();
  return 0;
}
