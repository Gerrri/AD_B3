#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "windows.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include "DVK.h"
#include "GEOKO.h"
#include "DVKE.h"
using namespace std;
#include <vector>




//initialisierung der Objekte + Indexliste(pointer)



DVK::DVK(long Anzahl){
    // Abfrage ob Anzahl in ordnung
    if(Anzahl <= 1000000){
        
        *index[] = new *index[Anzahl]();
        
        for(int i=0; i<Anzahl; i++){
           *index[i] = new *GEOKO();
        }
    
        //Auswahl der Datei [Dateiname -> choice]
        string choice = Menu();
    
        //Auslesen der Datei
        readData();
        
        // zur erstellung der Index Liste
        //init();
        // -> verändert und oben bereits passiert
        
        //sortieren nach MAX-Heap
        HeapSort();  
        
    }else{
      cout<<("Anzahl der gwünschten Objekte zu hoch")<<endl;
      cout<<("Maximnal : 1.000.000 Objekte möglich!")<< endl;
      return false;
    }
     
    
    
 
    
}

DVK::HeapSort(){

}

void DVK::erzeugeHeap(long Anzahl) {
}

void DVK::heapDown(long Anzahl, long Knoten) {
}

void DVK::vertausche(long First, long Second) {
}


//nicht in benutzung
void DVK::init(){
    // Zuweisung der Referenzen auf Pointer des indexarrays
    for(int i=0;i<1000000;i++){
        index[i] = &obj[i];
    }
}

string DVK::Menu(){
    int choice;
    do{
        cout<<"Bitte Wählen Sie aus den folgenden Dateien: "<<endl;
        cout<<"(1)  Datei.csv"<<endl;
        cout<<"(2)  Datei1.csv"<<endl;
        
        cin>> choice;
        
        switch(choice){
            case 1 :cout<<"Datei.csv ausgewählt"<<endl;
                    cout<<"Lade Datei ..."<<endl;
                    return "Datei.csv";
                    break;
            case 2 :cout<<"Datei1.csv ausgewählt"<<endl;
                    cout<<"Lade Datei ..."<<endl;
                    return "Datei1.csv";
                    break;
        }
        
    }while (choice !=1 || choice !=2);  
}

DVK::readData(string choice){
    
    
    //TEMOPRÄRE vARIABLEN
    double B_S, L_S; // L und B (Sek)
    int B_M, L_M;    // L und B (Min)
    int B_G, L_G;    // L und B (Grad)
    double B,L;      // L und B aus Tabelle   
    
    double nk_L_Grad, nk_B_Grad; // Nackomma länge und Breite GRAD
    double nk_L_Min, nk_B_Min; // Nackomma länge und Breite GRAD
    
    
    ifstream f;
    f.open(choice, ios::in);
    string input;
    
    int zaehler_zeile=0;
    while (!f.eof())
    {
        getline(f, input);
       
        //Sekunden einfügen/einelesen
        char* char_array = strtok(input, ","); //Sprung auf ersten eintrag
        B = (double)input; // Umwandeln des Wertes in einen Double
        
        char_array = strtok(input, ","); //Sprung auf zweiten eintrag
        L = (double)input; 
     
        // Grad = L bzw B / 3600 (nachkomma auslagern) --- L_B = L \ 3600
        // Minuten = (nachkomma von GRAD) *60 (nachkomma auslagern)
        // Sekunden = (nachkomma von Minuten)
        
        //Berechnen des Grads (ohne Nackommastellen)
        B_G = (int) (B / 3600 + 0.5f);
        L_G = (int) (L / 3600 + 0.5f);
        //Nachkommastellen auslesen
        nk_B_Grad = B / 3600 - (int) (B\3600) ;
        nk_L_Grad = L / 3600 - (int) (L\3600) ;
        
        
        //Berechnen der Minuten (ohne Nackommastellen)
        B_M = (int) (nk_B_Grad*60+0.5f);
        L_M = (int) (nk_L_Grad*60+0.5f);
        //Nackommastellen auslesen
        nk_B_Min = nk_B_Grad * 60 -(int) (nk_B_Grad*60);
        nk_L_Min = nk_L_Grad * 60 -(int) (nk_L_Grad*60);
        
        
        //Berechne rest Sekunden
        B_S = nk_B_Min * 60;
        L_S = nk_L_Min * 60;       
        
                
                
                
        //zuweisung Grad
        *index[zaehler_zeile]->SetBrGr(B_G);
        *index[zaehler_zeile]->SetLaGr(L_G); 
        //zuweisung Minuten
        *index[zaehler_zeile]->SetBrMin(B_M);
        *index[zaehler_zeile]->SetLaMin(L_M); 
        //zuweisung Sekunden
        *index[zaehler_zeile]->SetBrSec(B_S);    
        *index[zaehler_zeile]->SetLaSec(L_S);    
            
 
        
        // nächste zeile
        zaehler_zeile++; 
    }
    
    f.close();    
}    

    
    



    
    
    
    
    





