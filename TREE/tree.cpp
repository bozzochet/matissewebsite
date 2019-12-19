#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TChain.h>
#include <TNtuple.h>
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
#include <TTree.h>
#include <TRandom.h>
using namespace std;

int main(int argc, char * argv[])  {
   cout<<"Creazione del SSN Tree"<<endl;
    
   TFile *f1 =  new TFile("ROOT/SSNTree.root","RECREATE");
   TTree *t1 = new TTree ("SSN Data","ex 1");
   //creo un tree t1(nome del tree) dal titolo "example tree"
   struct dato {
       float  x;
       float y;
   };
   
   dato dx; //  punto sul grafico SSN vs Date
   t1->Branch("SSN",&dx,"date/F:value");
   //2 leaf uguali conta l'ordine il primo valore che assume dx va su valore

   fstream g;

   g.open("/var/www/html/SSN/SSNLINE.txt",ios::in);
   while (!g.eof()) {
       g>>dx.x>>dx.y>>ws;
       t1->Fill();  }
   
   g.close();
   t1->Print();
   f1->Write();
   f1->Close();
   cout<<"Solar Tree Data Created"<<endl;
    
    //-----------------------------------------------------------------------------------------------------

    
    dato dN,dS,dAvg,dNf,dSf,dAvgf;
    
    //----------SFS Tree------
    cout<<"Creazione del Solar Field Stenght N-S-Avg Tree"<<endl;
    //creazione di un tree SSn
    TFile *f2 =  new TFile("/var/www/html/TREE/ROOT/SFSTree.root","RECREATE");
    TTree *t2 = new TTree ("SFS Data","ex 1");
    //creo un tree t1(nome del tree) dal titolo "example tree"

    t2->Branch("SFS_N",&dN,"date/F:value");
    t2->Branch("SFS_S",&dS,"date/F:value");
    t2->Branch("SFS_Avg",&dAvg,"date/F:value");
    t2->Branch("SFS_N20nhz",&dNf,"date/F:value");
    t2->Branch("SFS_S20nhz",&dSf,"date/F:value");
    t2->Branch("SFS_Avg20nhz",&dAvgf,"date/F:value");
    
    //2 leaf uguali conta l'ordine il primo valore che assume dx va su valore

    fstream ff1;
    ff1.open("/var/www/html/TREE/SFS/SFSNorth.txt",ios::in);
    fstream ff2;
     ff2.open("/var/www/html/TREE/SFS/SFSSouth.txt",ios::in);
    fstream ff3;
     ff3.open("/var/www/html/TREE/SFS/SFSAvg.txt",ios::in);
    fstream ff4;
     ff4.open("/var/www/html/TREE/SFS/SFSNf.txt",ios::in);
    fstream ff5;
     ff5.open("/var/www/html/TREE/SFS/SFSSf.txt",ios::in);
    fstream ff6;
     ff6.open("/var/www/html/TREE/SFS/SFSAvgf.txt",ios::in);
    while (!ff1.eof()) {
        ff1>>dN.x>>dN.y>>ws;ff2>>dS.x>>dS.y>>ws;ff3>>dAvg.x>>dAvg.y>>ws;
        ff4>>dNf.x>>dNf.y>>ws;ff5>>dSf.x>>dSf.y>>ws;ff6>>dAvgf.x>>dAvgf.y>>ws;
        cout<<setprecision(7)<<dNf.x<<"    "<<dNf.y<<endl;
        t2->Fill();
        
    }
    
    ff1.close();   ff2.close();   ff3.close();   ff4.close();   ff5.close();   ff6.close();
    t2->Print();
    f2->Write();
    f2->Close();
    cout<<"Solar Filed Strenght Tree Data Created"<<endl;
     
    
    
//---------------------------------------Tilt Tree----------------------------------------------------
    
    dato dNt,dSt,dAvgt,dNft,dSft,dAvgft;
    
    
    cout<<"Creazione del tILT ANGLE Tree"<<endl;
    //creazione di un tree SSn
    TFile *f3 =  new TFile("/var/www/html/TREE/ROOT/TiltTree.root","RECREATE");
    TTree *t3 = new TTree ("Tilt Data","ex 1");
    //creo un tree t1(nome del tree) dal titolo "example tree"

    t3->Branch("R_av",&dNt,"date/F:value");
    //t3->Branch("R_n",&dSt,"date/F:value");
    //t3->Branch("R_s",&dAvgt,"date/F:value");
    t3->Branch("L_av",&dNft,"date/F:value");
    //t3->Branch("L_n",&dSft,"date/F:value");
   // t3->Branch("L_s",&dAvgft,"date/F:value");
    
    //2 leaf uguali conta l'ordine il primo valore che assume dx va su valore

    fstream f1t;
    f1t.open("/var/www/html/Tilt/Tilt_R_av.txt",ios::in);
    fstream f2t;
     f2t.open("/var/www/html/Tilt/Tilt_R_n.txt",ios::in);
    fstream f3t;
     f3t.open("/var/www/html/Tilt/Tilt_R_s.txt",ios::in);
    fstream f4t;
     f4t.open("/var/www/html/Tilt/Tilt_L_av.txt",ios::in);
    fstream f5t;
     f5t.open("/var/www/html/Tilt/Tilt_L_n.txt",ios::in);
    fstream f6t;
     f6t.open("/var/www/html/Tilt/Tilt_L_s.txt",ios::in);
    while (!f1t.eof()) {
        f1t>>dNt.x>>dNt.y>>ws;f2t>>dSt.x>>dSt.y>>ws;f3t>>dAvgt.x>>dAvgt.y>>ws;
        f4t>>dNft.x>>dNft.y>>ws;f5t>>dSft.x>>dSft.y>>ws;f6t>>dAvgft.x>>dAvgft.y>>ws;
        cout<<setprecision(7)<<dNft.x<<"    "<<dNft.y<<endl;
        t3->Fill();
        
    }
    
    f1t.close();f2t.close();f3t.close();f4t.close();f5t.close();f6t.close();
    t3->Print();
    f3->Write();
    f3->Close();
    cout<<"SSN Tilt Angle tree created"<<endl;
    
    
  //--------------------------------------TREE SSN SMOOTHED
    


    dato dSmoothed;
    float errory;
    float errorx;
    
    
    cout<<"Creazione del SSN Smoothed Tree"<<endl;
    //creazione di un tree SSn
    TFile *f4 =  new TFile("/var/www/html/TREE/ROOT/SmoothedTree.root","RECREATE");
    TTree *t4 = new TTree ("Smoothed","ex 1");
    //creo un tree t1(nome del tree) dal titolo "example tree"
    t4->Branch("Smmothed",&dSmoothed,"date/F:value");
    t4->Branch("SmmothedError",&errory,"error/F");


    
    //2 leaf uguali conta l'ordine il primo valore che assume dx va su valore

    fstream fSmoothed;
    fSmoothed.open("/var/www/html/SolarSmoothed/SSN_13PLOT.txt",ios::in);

    while (!fSmoothed.eof()) {
        fSmoothed>>dSmoothed.x>>dSmoothed.y>>errorx>>errory>>ws;
        t4->Fill();
        
    }
    
    
    
    fSmoothed.close();
    t4->Print();
    f4->Write();
    f4->Close();
    cout<<"SSN Smoothed tree created"<<endl;
    
    //---------------TREE SSN MONTHLY
    
    
    dato dMonthly;
    cout<<"Creazione del SSN Monthly Tree"<<endl;
    //creazione di un tree SSn
   
   TFile *f5 =  new TFile("/var/www/html/TREE/ROOT/MonthlyTree.root","RECREATE");
    
    TTree *t5 = new TTree ("Monthly","ex 1");
    //creo un tree t1(nome del tree) dal titolo "example tree"
    t5->Branch("Monthly",&dMonthly,"date/F:value");
     t5->Branch("Error",&errory,"error/F");
    
    //2 leaf uguali conta l'ordine il primo valore che assume dx va su valore

  
    fstream fMonthly;
     fMonthly.open("/var/www/html/SolarSmoothed/SSN_MonthlyPLOT.txt",ios::in);

    while (!fMonthly.eof()) {
        fMonthly>>dMonthly.x>>dMonthly.y>>errorx>>errory>>ws;
        t5->Fill();
    }
    
    fMonthly.close();
    t5->Print();
    f5->Write();
    f5->Close();
   

        //---------------TREE Neutron---------------------------------------------------------------
        
    dato dJung,dNewk,dOulu,dKiel;
        
        
        cout<<"Creazione del Neutron Tree"<<endl;
        //creazione di un tree SSn
        TFile *fTotal =  new TFile("/var/www/html/TREE/ROOT/NeutronTree.root","RECREATE");
        TTree *t6 = new TTree ("Jung","ex 1");

      t6->Branch("Jung",&dJung,"date/F:value");
    
        fstream Jung;
    Jung.open("/var/www/html/Neutron/Jung.txt",ios::in);

        while (!Jung.eof()) {
            Jung>>dJung.x>>dJung.y>>ws;
            t6->Fill();

            
        }

    cout<<"Jung tree created"<<endl;
    
    //--------------------------------KIEL TREE--

        TTree *t7 = new TTree ("Kiel","ex 1");
        t7->Branch("Kiel",&dKiel,"date/F:value");
    
    
        fstream Kiel;
    Kiel.open("/var/www/html/Neutron/Kiel.txt",ios::in);

        while (!Kiel.eof()) {
            Kiel>>dKiel.x>>dKiel.y>>ws;
            t7->Fill();
        }
    Kiel.close();
    t7->Print();

    cout<<"Kiel tree created"<<endl;
    
    //----------------Oulu-----------------------------------------------------

    TTree *t8 = new TTree ("Oulu","ex 1");
    t8->Branch("Oulu",&dOulu,"date/F:value");

    fstream Oulu;
    Oulu.open("/var/www/html/Neutron/Oulu.txt",ios::in);

        while (!Oulu.eof()) {
            Oulu>>dOulu.x>>dOulu.y>>ws;
            t8->Fill();
            
        }
    
    Oulu.close();
    t8->Print();

    cout<<"Oulu tree created"<<endl;
    
    
    //------------NEWK TREE-----

    TTree *t9 = new TTree ("Newk","ex 1");
    t9->Branch("Newk",&dNewk,"date/F:value");

    
    fstream Newk;
    Newk.open("/var/www/html/Neutron/Newk.txt",ios::in);

        while (!Newk.eof()) {
            Newk>>dNewk.x>>dNewk.y>>ws;
            t9->Fill();
            
        }
    
    t9->Print();
    Newk.close();


    fTotal->Write();
    fTotal->Close();
    cout<<"Neutron tree created"<<endl;
    

    return 0;

    
}
