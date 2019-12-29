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
#include <vector>
#include <TPad.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TColor.h>
#include <TVirtualPad.h>
#include <fstream>
#include <sstream>
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
  for (int i=0; i<rate.size(); i++) { cout<<date[i]<<"  "<<rate[i]<<endl;}
}



void GetModulationPotential(int i,vector<double> &phi,vector<double> &rate,  vector< vector <double>> &parameters) //get Phi from NM counts with parameters
{
  double A = parameters[i][0] ;
  double B = parameters[i][1] ;
  double C =  parameters[i][2];
    
  for (int i=0; i<rate.size(); i++) {
    phi.push_back(A + B*rate[i] + C*rate[i]*rate[i]);
  }
}


void SetEIS(double Ekn, vector<double> &EIS, vector<double> &phi ){  //  Ekn -> EIS(t) from phi(t)
  double Z = 1.;
  double A= 1.;
    
  for (int i=0; i<phi.size(); i++) {
    EIS.push_back(Ekn + (Z/A)*(phi[i]*1.e-3));
  }
}


void GetProtonLISvsEkn(vector<double> &JIS, vector<double> &EIS)
{
  //all values of JIS --> JIS(t)
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

//all JMOD value for Ekn fixed -> JMOD(t)
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
    if (phi[i] <= 1.0 ) {
      JMOD.push_back(0);
    }
    else JMOD.push_back(SP * JIS[i]);

  }

}


int main()
{
 
  double Ekn = 1.0; //1 GeV
  //Set Parameter
  vector< vector <double>> parameters;
  vector <double> abc;

  abc.push_back(7609.0); abc.push_back(-110.5); abc.push_back( 0.41); parameters.push_back(abc); abc.clear(); //ABCparameters Oulu
  abc.push_back(6907.0); abc.push_back(-103.0); abc.push_back( 0.39); parameters.push_back(abc);abc.clear(); //ABCparameters Newk
  abc.push_back(10668); abc.push_back(-112.7); abc.push_back( 0.31); parameters.push_back(abc);abc.clear();//ABCparameters Jung
  abc.push_back(6580); abc.push_back(-54.5); abc.push_back( 0.11); parameters.push_back(abc);abc.clear();//ABCparameters kiel
  abc.push_back(7979); abc.push_back(-53.9); abc.push_back( 0.09); parameters.push_back(abc);abc.clear();//ABCparameters mosc
  abc.push_back(6849); abc.push_back(-57.9); abc.push_back( 0.12); parameters.push_back(abc);abc.clear();//ABCparameters apty

  //PLOT
  
  //multiplot all phi from different station
  TFile ff("/var/www/html/FFModel/ForceField.root" , "recreate");
  ff.cd();
  TString stations[6] = {"Oulu","Newk", "Jung","Kiel","MOSC", "APTY"};
  string stats[6] = {"Oulu","Newk", "Jung","Kiel", "MOSC", "APTY"};
  int color[6] = {416,807,860,616,4,8};
  vector<double> date;
  vector<double> rate;
  vector<double> phi;
  vector<double> JMOD;
  vector<double> JIS;
  vector<double> EIS;
    
  //multigraph
  TCanvas *c1 = new TCanvas("FF Model PHI_Set1","titolo Canvas");
  TCanvas *c2 = new TCanvas("FF Model J_Set1","titolo Canvas2");
  TMultiGraph *mg = new TMultiGraph();
  TMultiGraph *mg2 = new TMultiGraph();
  TLegend *legend = new TLegend(.75,.75,.89,.89);
  legend->SetHeader("","C"); // option "C" allows to center the header
  legend->SetX1NDC(0.01);
  legend->SetX2NDC(0.9);
  TLegend *legend2 = new TLegend(.75,.75,.89,.89);
  legend2->SetX1NDC(0.01);
  legend2->SetX2NDC(0.9);
  legend2->SetHeader("","C"); // option "C" allows to center the header
    

  TCanvas *c3 = new TCanvas("FF Model PHI_Set2","titolo Canvas");
  TCanvas *c4 = new TCanvas("FF Model J_Set2","titolo Canvas2");
  TMultiGraph *mg3 = new TMultiGraph();
  TMultiGraph *mg4 = new TMultiGraph();
  TLegend *legend3 = new TLegend(.75,.75,.89,.89);
  legend3->SetHeader("","C"); // option "C" allows to center the header
  legend3->SetX1NDC(0.01);
  legend3->SetX2NDC(0.9);
  TLegend *legend4 = new TLegend(.75,.75,.89,.89);
  legend4->SetX1NDC(0.01);
  legend4->SetX2NDC(0.9);
  legend4->SetHeader("","C"); // option "C" allows to center the header
  //end multigraph definition
    
  for (int i=0; i<6; i++) {
    string s = "/var/www/html/Neutron/" + stats[i]+".txt";   //path to -> Rate[Hz] from NM Stations
    SetDataNM(rate,date,s); // vector contiene tutti i rate
    cout<<s<<endl;
    GetModulationPotential(i,phi,rate,parameters); // vector phi aggioranato
    SetEIS(Ekn,EIS, phi );
    GetProtonLISvsEkn(JIS, EIS);
    GetProtonMODvsEkn( Ekn /*[GeV/n]*/, phi, EIS, JIS, JMOD);
    cout<<stats[i]<<endl;
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
    TString p = "Modulated Flux J(E = 1 GeV) from " + stations[i]+" Data";
    f->SetTitle(p);
    f->GetXaxis()->CenterTitle();
    f->GetYaxis()->CenterTitle();
    f->SetName("J"+stations[i]);
    f->SetMarkerColor(color[i]);//Markers...
    f->SetLineColor(color[i]);
    f->SetLineWidth(2);
    f->SetLineStyle(1);
    f->Write();
        

    if (i<4) {
      legend2->AddEntry(f,stations[i],"l");
      mg2->Add(f);
    }
    else {legend4->AddEntry(f,stations[i],"l"); mg4->Add(f);}
        
        
    TGraph *gf = new TGraph("/var/www/html/FFModel/PHI.txt");
    gf->GetXaxis()->SetTitle("year");
    gf->GetYaxis()->SetTitle("#phi [MV]");
    TString p2 = "Modulated Potential #phi from " + stations[i]+" Data";
    gf->SetTitle(p2);
    gf->GetXaxis()->CenterTitle();
    gf->GetYaxis()->CenterTitle();
    gf->SetName("phi"+stations[i]);
    gf->SetMarkerColor(color[i]);//Markers...
    gf->SetLineColor(color[i]);
    gf->SetLineWidth(2);
    gf->SetLineStyle(1);
    gf->Write();
    if (i<4) {
      legend->AddEntry(gf,stations[i],"l");
      mg->Add(gf);
    }
    else {legend3->AddEntry(gf,stations[i],"l"); mg3->Add(gf);}
    
    date.clear();
    rate.clear();
    phi.clear();
    JMOD.clear();
    JIS.clear();
    EIS.clear();
  }
    
  // complete all plots with 2 set of stations. phi(t);J(t)
  // set1 (Oulu, Newk, Kiel, Jung) set2(APTY, Mosc)
  c1->cd();
  mg->SetTitle("#phi Modulated potential");
  mg->Draw("apl");
  mg->GetXaxis()->CenterTitle();
  mg->GetYaxis()->CenterTitle();

  mg->GetXaxis()->SetTitle("year");
  mg->GetYaxis()->SetTitle("#phi [MV]");
  mg->SetName("phi TOTAL");
  legend->Draw();
    
  c3->cd();
  mg3->SetTitle("#phi Modulated potential");
  mg3->Draw("apl");
  mg3->GetXaxis()->CenterTitle();
  mg3->GetYaxis()->CenterTitle();

  mg3->GetXaxis()->SetTitle("year");
  mg3->GetYaxis()->SetTitle("#phi [MV]");
  mg3->SetName("phi TOTAL");
  legend3->Draw();


    
  c2->cd();

  mg2->SetTitle("J(E = 1 GeV) Modulated Flux");
  mg2->Draw("apl");
  mg2->GetXaxis()->CenterTitle();
  mg2->GetYaxis()->CenterTitle();
  mg2->GetXaxis()->SetTitle("year");
  mg2->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
  mg2->SetName("J TOTAL");
  legend2->Draw();
    

    
  c4->cd();

  mg4->SetTitle("J(E = 1 GeV) Modulated Flux");
  mg4->Draw("apl");
  mg4->GetXaxis()->CenterTitle();
  mg4->GetYaxis()->CenterTitle();
  mg4->GetXaxis()->SetTitle("year");
  mg4->GetYaxis()->SetTitle("J [ GeV^{ -1} m^{ -2} s^{ -1} sr^{ -1} ]");
  mg4->SetName("J TOTAL");
  legend4->Draw();
  ff.cd();
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  ff.Close();
}
