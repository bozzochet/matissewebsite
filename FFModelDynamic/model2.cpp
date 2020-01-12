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

//global struct
typedef struct NeutronMonitor {
  string name;
  double A;
  double B;
  double C;
    
} NeutronMonitor;


NeutronMonitor NM[8]; // global array



void SetDataNM(vector<double> &rate, vector<double> &date, string &s) {
    
  ifstream file;
  file.open(s);
  double dat, hz;
while (!file.eof( )) {
  file >> dat >> hz;
  if(dat > 1965.000) {
    rate.push_back(hz);
    date.push_back(dat);
  }
 }
  file.close();
 }



void GetModulationPotential(string &stat,vector<double> &phi,vector<double> &rate)
{
  NM[0].name = "OULU"; NM[0].A =7609.16; NM[0].B = -110.498; NM[0].C = 0.414333;
  NM[1].name = "NEWK"; NM[1].A =6907.31; NM[1].B =  -102.973; NM[1].C =0.385457;
  NM[2].name = "JUNG"; NM[2].A =10668.1; NM[2].B = -112.679; NM[2].C =0.309376;
  NM[3].name = "KIEL"; NM[3].A =6579.55; NM[3].B = -54.5371; NM[3].C = 0.11357;
  NM[4].name = "MOSC"; NM[4].A = 7978.88; NM[4].B = -53.9157; NM[4].C = 0.0936969;
  NM[5].name = "APTY"; NM[5].A =6848.52; NM[5].B = -57.9011; NM[5].C =0.124626;
  NM[6].name = "ROME"; NM[6].A =13516.2; NM[6].B =  -197.111; NM[6].C =0.716388;
  NM[7].name = "MXCO"; NM[7].A =13572.7; NM[7].B = -105.231; NM[7].C =0.209658;
  double A;
  double B;
  double C;
    
  for (int i =0; i<8; i++) {  // 8 numero di stazioni definite
    if (NM[i].name == stat) {
      A = NM[i].A;B = NM[i].B; C = NM[i].C;
      cout<<"A-> "<<A<<endl;
      cout<<"b-> "<<B<<endl;
      cout<<"c-> "<<C<<endl;
      for (int i=0; i<rate.size(); i++) {
	phi.push_back(A + B*rate[i] + C*rate[i]*rate[i]);
      }
    }
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


int main()
{
  int color[6] = {632,416,860,900,860,432};
  vector<double> date;
  vector<double> rate;
  vector<double> phi;
  vector<double> JMOD;
  vector<double> JIS;
  vector<double> EIS;

  TFile ff("/var/www/html/FFModelDynamic/ForceFieldGEV.root" , "recreate");
  ff.cd();
    
  // importare la lista dei NM
  for (int y = 1 ; y<2; y++) {
    vector<string> stats;
    vector<TString> stations;
    //TString stations[6] = {"Oulu","Newk", "Jung",/*inizio set2*/"Kiel","MOSC", "APTY"};
    //string stats[6] = {"Oulu","Newk", "Jung","Kiel", "MOSC", "APTY"};
    ifstream set;
    stringstream ss;
    ss<<y;
    string s;
    ss>>s;
    string path ="/var/www/html/FFModelDynamic/NM_Set" + s + ".txt";
    cout<<path<<endl;
     
    set.open(path);
    string sx;
    while (!set.eof()) {
      set>>sx>>ws;
      stats.push_back(sx);
      stations.push_back(sx);
    }
    
    
    
    double energy [3] = {1,10,0.1};
    TString strenergy [3] = {"E = 1 [GeV]","E = 10 [GeV]","E = 0.1 [GeV]"};

            
    for (int j=0; j<stats.size(); j++) {
      ff.cd();
 string s = "/var/www/html/Neutron/"+
   stats[j]+".txt";
 SetDataNM(rate,date,s); // vector contiene tutti i rate
 GetModulationPotential(stats[j],phi,rate); // vector phi aggiornato

 TCanvas *c = new TCanvas("TOTAL Graph","titolo Canvas");
 TLegend *legend = new TLegend(.75,.75,.89,.89);
 legend->SetHeader("","C");
 legend->SetX1NDC(0.01);
 legend->SetX2NDC(0.9);
 TMultiGraph *mg = new TMultiGraph();
    
 //for sulle energie
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
   TString p = "Modulated Flux J " + strenergy[i]+  " from " + stations[j]+" Data";
   f->SetTitle(p);
   f->GetXaxis()->CenterTitle();
   f->GetYaxis()->CenterTitle();
   f->SetName("J"+stations[j] +" "+ strenergy[i]);
   f->SetMarkerColor(color[i]);//Markers...
   f->SetLineColor(color[i]);
   f->SetLineWidth(2);
   f->SetLineStyle(1);
   f->Write(); //salvo nel file root
         
   mg->Add(f);
   legend->AddEntry(f,strenergy[i],"l");
   
   JMOD.clear();
   JIS.clear();
   EIS.clear();
 }
        
 c->SetName("J(t) "+ stations[j] );
 c->SetTitle("J(t) "+ stations[j] );
 c->cd();
 mg->SetTitle("J(t) "+stations[j] );
 mg->Draw("apl");
 mg->GetXaxis()->CenterTitle();
 mg->GetYaxis()->CenterTitle();
 mg->GetXaxis()->SetTitle("year");
 mg->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
 mg->SetName("J TOTAL");
 legend->Draw();

 ff.cd();
 c->Write();
    
 date.clear();
 rate.clear();
 phi.clear();

    }
    
    
  }
  ff.Close();
  return 0;
}
