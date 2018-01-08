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
using namespace std;
#include <vector>




//initialisierung der Objekte + Indexliste(pointer)



DVK::DVK(long Anzahl){
    
    for(int i=0; i<Anzahl; i++){
        obj[i] = new GEOKO();
    }
    
    //Auswahl der Datei [Dateiname -> choice]
    string choice = Menu();
    
    //Auslesen der Datei
    readData();

    
    
    
    
    
    // zur erstellung der Index Liste
    init();
    
    
    HeapSort();
    
}

DVK::HeapSort(){

}

void DVK::erzeugeHeap(long Anzahl) {
}

void DVK::heapDown(long Anzahl, long Knoten) {
}

void DVK::vertausche(long First, long Second) {
}

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
    ifstream f;
    f.open(choice, ios::in);
    string input;
    while (!f.eof())
    {
        getline(f, input);
        char* char_array = strtok(input, ",");
        
        
    }
    f.close();    
}    

    
    



    
    
    
    
    





