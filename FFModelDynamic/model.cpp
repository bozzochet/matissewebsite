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
#include <vector>
#include <TPad.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TColor.h>
#include <TVirtualPad.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
//---------------------------------------------------------dichiaro le funzioni

void SetDataNM(vector<double> &rate, vector<double> &date, string &s)
{
    
  ifstream file;
  file.open(s);
  double dat, hz;
  while (!file.eof( )) {
    file >> dat >> hz;
    rate.push_back(hz);
    date.push_back(dat);
  }
    
  file.close();
  //for (int i=0; i<rate.size(); i++) { cout<<date[i]<<"  "<<rate[i]<<endl;}
}



void GetModulationPotential(int i,vector<double> &phi,vector<double> &rate,  vector< vector <double>> &parameters) //get Phi from NM counts
{
  double A = parameters[i][0] ;
  double B = parameters[i][1] ;
  double C =  parameters[i][2];
  cout<<"A-> "<<A<<endl;
  cout<<"b-> "<<B<<endl;
  cout<<"c-> "<<C<<endl;
  for (int i=0; i<rate.size(); i++) {
    phi.push_back(A + B*rate[i] + C*rate[i]*rate[i]);
  }
}


void SetEIS(double Ekn, vector<double> &EIS, vector<double> &phi ){  // EIS(t) phi(t)
  double Z = 1.;
  double A= 1.;
    
  for (int i=0; i<phi.size(); i++) {
    // PHI in GV [rigidity loss] prima era in MV (il graifico in MV)
    EIS.push_back(Ekn + (Z/A)*(phi[i]*1.e-3));
  }
}


void GetProtonLISvsEkn(vector<double> &JIS, vector<double> &EIS)
{
    
  //per calcore JIS Vector svolgo il calcolo in E si aggiorna E = EIS[i]
  for (int i=0; i<EIS.size(); i++) {
    // --- kinematics ---
    double Z = 1.;
    double A= 1.;
    double pA= 1.;   // mass number
    double pZ= 1.;   // charge number
    double Mp=0.938; // proton mass
    double pM=Mp*pA; // nucleus mass
    double R= (sqrt( (EIS[i]*pA+pM)*(EIS[i]*pA+pM)- (pM*pM)))/pZ; // rigidity R=p/Z
    double LnR= TMath::Log(R); // log-of-rigidity
      
    // --- low-R parameterization ---
    double Norm= 11600;
    double mu= -0.559;
    double sigma= 0.563;
    double G1 = -2.4482;
    double nu= 0.431;
    double LowR= (TMath::Power( 1.+ TMath::Exp(-(LnR-mu)/sigma), -1./nu ))*TMath::Power(R, G1);
      
    // --- high-R parameterization ---
    double Rb1 = 6.2;
    double DG1 = -0.4227;
    double S1  = -0.108;
    double Rb2 = 545.;
    double DG2 = -0.6;
    double S2  = -0.4;
    double HighR= TMath::Power(1.+ TMath::Power(  (R/Rb1)*TMath::Power(1.+ TMath::Power(R/Rb2, DG2/S2), S2) , DG1/S1 ), S1);

    double LIS_RIG =  Norm*LowR*HighR; // rigidity flux J(R) [GV^-1 m^-2 s^-1 sr^-1]
    // --- convert from rigidity to kinetic energy (per nucleon) ---
    // double dEdR = (pZ/pA)*(pZ/pA)*R/sqrt((pZ/pA)*(pZ/pA)*(R*R)+Mp*Mp); // jacobian dE/dR
    double dRdE= (pA/pZ)*(Mp + EIS[i])/sqrt(EIS[i]*EIS[i] + 2.*Mp*EIS[i]); // Jacobian dR/dE
    double LIS_EKN = dRdE*LIS_RIG; // kinetic flux J(E) [(GeV/n)^-1 m^-2 s^-1 sr^-1]

    JIS.push_back(LIS_EKN);
  }
}


void GetProtonMODvsEkn(double Ekn /*[GeV/n]*/, vector<double> &phi, vector<double> &EIS, vector<double> &JIS , vector<double> &JMOD ){
  double Z=1;            // proton charge
  double A=1.;           // proton mass number
  double Mp=0.938;       // proton mass GeV
  
  double E= Ekn;                // GeV/n [kinetic energy (per nucleon) HERE AT EARTH]

  for (int i=0; i<phi.size(); i++) {
    // compute phase space factor PS = P^2/PIS^2 (ratio of the two squared rigidities, or momenta)
    double P2=   (E*A + Mp*A)*(E*A + Mp*A) - (Mp*A)*(Mp*A); // MOM AT EARTH
    double PIS2= (EIS[i]*A + Mp*A)*(EIS[i]*A + Mp*A) - (Mp*A)*(Mp*A); // MOM INTERSTELLAR
    double SP= P2/PIS2; // RATIO OF SQUARED MOMENTA = RATIO OF SQUARED RIGIDITIES
    //  double SP = ( (E + Mp)*(E + Mp) - (Mp*Mp) ) / ( (E + Mp + (Z/A)*PHI)*(E + Mp + (Z/A)*PHI) - (Mp*Mp) ); // EQUIVALENT TO ABOVE
  
    // calc modulated flux at energy E
      
    if (phi[i] <= 1.0 ) {
      JMOD.push_back(0);
    }
    else JMOD.push_back(SP * JIS[i]);
      
  }

}


int main() {
 
  //double Ekn = 1.0; //1 GeV
    
    
    
  //Set Parameter
  vector< vector <double>> parameters;
  vector <double> abc;

  abc.push_back(7609.0); abc.push_back(-110.5); abc.push_back( 0.41); parameters.push_back(abc); abc.clear(); //parameter Oulu
  abc.push_back(6907.0); abc.push_back(-103.0); abc.push_back( 0.39); parameters.push_back(abc);abc.clear(); //parameter Newk
  abc.push_back(10668); abc.push_back(-112.7); abc.push_back( 0.31); parameters.push_back(abc);abc.clear();//parameter Jung
  abc.push_back(6580); abc.push_back(-54.5); abc.push_back( 0.11); parameters.push_back(abc);abc.clear();//parameter kiel
  abc.push_back(7979); abc.push_back(-53.9); abc.push_back( 0.09); parameters.push_back(abc);abc.clear();//parameter mosc
  abc.push_back(6849); abc.push_back(-57.9); abc.push_back( 0.12); parameters.push_back(abc);abc.clear();//parameter apty

  //PLOT
  
  //multiplot all phi from different station
  TFile ff("/var/www/html/FFModelDynamic/ForceFielGEV.root" , "recreate");
  ff.cd();
    
  TString stations[6] = {"Oulu","Newk", "Jung","Kiel","MOSC", "APTY"};
  string stats[6] = {"Oulu","Newk", "Jung","Kiel", "MOSC", "APTY"};
  double energy [3] = {1,10,0.1};
  TString strenergy [3] = {"E = 1 [GeV]","E = 10 [GeV]","E = 0.1 [GeV]"};
  // int color[6] = {1,2,4,8,4,8};
    

  int color[6] = {632,416,860,900,860,432};
  vector<double> date;
  vector<double> rate;
  vector<double> phi;
  vector<double> JMOD;
  vector<double> JIS;
  vector<double> EIS;
    
  //multigraph
  TCanvas *c1 = new TCanvas("OULU","titolo Canvas");
  TMultiGraph *mg = new TMultiGraph(); //oulu multigraph
  //------------------------------------------------------------------------------
  TCanvas *c2 = new TCanvas("NEWK","titolo Canvas2");
  TMultiGraph *mg2 = new TMultiGraph();
  //------------------------------------------------------------------------------
  TCanvas *c3 = new TCanvas("JUNG","titolo Canvas2");
  TMultiGraph *mg3 = new TMultiGraph();
  //------------------------------------------------------------------------------
  TCanvas *c4 = new TCanvas("KIEL","titolo Canvas2");
  TMultiGraph *mg4 = new TMultiGraph();
  //------------------------------------------------------------------------------

    
  TLegend *legend = new TLegend(.75,.75,.89,.89);
  legend->SetHeader("","C"); // option "C" allows to center the header
  legend->SetX1NDC(0.01);
  legend->SetX2NDC(0.9);
  TLegend *legend2 = new TLegend(.75,.75,.89,.89);
  legend2->SetHeader("","C"); // option "C" allows to center the header
  legend2->SetX1NDC(0.01);
  legend2->SetX2NDC(0.9);
  TLegend *legend3 = new TLegend(.75,.75,.89,.89);
  legend3->SetHeader("","C"); // option "C" allows to center the header
  legend3->SetX1NDC(0.01);
  legend3->SetX2NDC(0.9);
  TLegend *legend4 = new TLegend(.75,.75,.89,.89);
  legend4->SetHeader("","C"); // option "C" allows to center the header
  legend4->SetX1NDC(0.01);
  legend4->SetX2NDC(0.9);    
for (int j=0; j<4; j++) {
  string s = "/var/www/html/Neutron/" + stats[j]+".txt";
  SetDataNM(rate,date,s); // vector contiene tutti i rate
  GetModulationPotential(j,phi,rate,parameters); // vector phi aggioranato
    
  for (int i=0; i<3; i++) {
    double Ekn = energy[i]; //E GeV
    
    SetEIS(Ekn,EIS, phi );
    GetProtonLISvsEkn(JIS, EIS);
    GetProtonMODvsEkn( Ekn /*[GeV/n]*/, phi, EIS, JIS, JMOD);
    ofstream myfile,myfile2;
    myfile.open("/var/www/html/FFModel/PHI.txt");
    for (int i=0; i<phi.size(); i++) {
      myfile<<date[i]<<" "<<phi[i]<<endl;
    }
    myfile.close();
    myfile2.open ("/var/www/html/FFModel/JMOD.txt");
    for (int i=0; i<phi.size(); i++) {
      myfile2<<date[i]<<" "<<JMOD[i]<<endl;
    }
    myfile2.close();
        
    TGraph *f = new TGraph("/var/www/html/FFModel/JMOD.txt");
    f->GetXaxis()->SetTitle("year");
    f->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
    TString p = "Modulated Flux J " + strenergy[i]+  "GeV) from " + stations[j]+" Data";
    f->SetTitle(p);
    f->GetXaxis()->CenterTitle();
    f->GetYaxis()->CenterTitle();
    f->SetName("J"+stations[j] +" "+ strenergy[i]);
    f->SetMarkerColor(color[i]);//Markers...
    f->SetLineColor(color[i]);
    f->SetLineWidth(2);
    f->SetLineStyle(1);
    f->Write(); //salvo nel file root
        

    switch (j) {
    case 0:
      mg->Add(f);
      legend->AddEntry(f,strenergy[i],"l");
      break;
    case 1:
      mg2->Add(f);
      legend2->AddEntry(f,strenergy[i],"l");
      break;
    case 2:
      mg3->Add(f);
      legend3->AddEntry(f,strenergy[i],"l");
      break;
    case 3:
      mg4->Add(f);
      legend4->AddEntry(f,strenergy[i],"l");
      break;
    default:
      break;
    }

    JMOD.clear();
    JIS.clear();
    EIS.clear();
  }
  date.clear();
  rate.clear();
  phi.clear();

    
 }
    
//inseriamo titoli e legenda
c1->cd();
mg->SetTitle("J(t) OULU");
mg->Draw("apl");
mg->GetXaxis()->CenterTitle();
mg->GetYaxis()->CenterTitle();
mg->GetXaxis()->SetTitle("year");
mg->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
legend->Draw();

    
c2->cd();
mg2->SetTitle("J(t) NEWK");
mg2->Draw("apl");
mg2->GetXaxis()->CenterTitle();
mg2->GetYaxis()->CenterTitle();
mg2->GetXaxis()->SetTitle("year");
mg2->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
legend2->Draw();
    
    
c3->cd();
mg3->SetTitle("J(t) JUNG");
mg3->Draw("apl");
mg3->GetXaxis()->CenterTitle();
mg3->GetYaxis()->CenterTitle();

mg3->GetXaxis()->SetTitle("year");
mg3->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
legend3->Draw();
    
c4->cd();
mg4->SetTitle("J(t) KIEL");
mg4->Draw("apl");
mg4->GetXaxis()->CenterTitle();
mg4->GetYaxis()->CenterTitle();

mg4->GetXaxis()->SetTitle("year");
mg4->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
legend->Draw();
    

ff.cd();
c1->Write();
c2->Write();
c3->Write();
c4->Write();
ff.Close();

}
