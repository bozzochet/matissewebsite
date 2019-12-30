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
TFile ff("/var/www/html/FFModelDynamic/ForceFieldGEV.root" , "recreate");
ff.cd();
    
TString stations[6] = {"Oulu","Newk", "Jung","Kiel","MOSC", "APTY"};
string stats[6] = {"Oulu","Newk", "Jung","Kiel", "MOSC", "APTY"};
double energy [3] = {1,10,0.1};
TString strenergy [3] = {"E = 1 [GeV]","E = 10 [GeV]","E = 0.1 [GeV]"};
// int color[6] = {1,2,4,8,4,8};
    
/*enum EColor { kWhite =0,   kBlack =1,   kGray=920,
    61               kRed   =632, kGreen =416, kBlue=600, kYellow=400, kMagenta=616, kCyan=432,
    62               kOrange=800, kSpring=820, kTeal=840, kAzure =860, kViolet =880, kPink=900 };*/
int color[6] = {632,416,860,900,860,432};
//Color_t color[6] = {"kGreen","kOrange0","kMagenta","kGreen","kAzure","kOrange" };
vector<double> date;
vector<double> rate;
vector<double> phi;
vector<double> JMOD;
vector<double> JIS;
vector<double> EIS;
    
//multigraph
//multigraph
TCanvas *c[4];
TLegend *legend[4]; // = new TLegend(.75,.75,.89,.89);
TMultiGraph *mg[4];// = new TMultiGraph();
    
      
for (int i = 0; i<4; i++) {
  mg[i]= new TMultiGraph();
  c[i]= new TCanvas();
  legend[i] = new TLegend(.75,.75,.89,.89);
 }
      
for (int i=0; i<4; i++) {
  legend[i]->SetHeader("","C"); // option "C" allows to center the header
  legend[i]->SetX1NDC(0.01);
  legend[i]->SetX2NDC(0.9);
 }

    
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
    mg[j]->Add(f);
    legend[j]->AddEntry(f,strenergy[i],"l");
    break;
  case 1:
    mg[j]->Add(f);
    legend[j]->AddEntry(f,strenergy[i],"l");
    break;
  case 2:
    mg[j]->Add(f);
    legend[j]->AddEntry(f,strenergy[i],"l");
    break;
  case 3:
    mg[j]->Add(f);
    legend[j]->AddEntry(f,strenergy[i],"l");
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
    
for (int i =0; i<4; i++) {
  c[i]->SetName("J(t) "+ stations[i] );
  c[i]->cd();
  mg[i]->SetTitle("J(t) "+ stations[i]);
  mg[i]->Draw("apl");
  mg[i]->GetXaxis()->CenterTitle();
  mg[i]->GetYaxis()->CenterTitle();
  mg[i]->GetXaxis()->SetTitle("year");
  mg[i]->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
  mg[i]->SetName("J TOTAL");
  legend[i]->Draw();
 }
             
    
   

ff.cd();
for (int i=0; i<4; i++) {
  c[i]->Write();
 }

ff.Close();

}
