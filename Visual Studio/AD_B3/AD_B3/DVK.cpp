#include "stdafx.h"
#include "DVK.h"
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
using namespace std;


// für initialisierung
GEOKO *index[1000000];


DVK::DVK(long Anzahl) {

	// Abfrage ob Anzahl in ordnung
	if (Anzahl <= 1000000) {
		
		anz = Anzahl;
		int const x = Anzahl;

		for (int i = 0; i<Anzahl; i++){

			index[i] = new GEOKO();


			// Zuweisung der Nachfolger bzw Vorgägner
			if (i > 0) {
				//vorgänger = index - 1
				index[i]->SetV(index[i - 1]);

				//(bei vorherigen)nächstes = index (aktuelles)
				index[i - 1]->SetN(index[i]);

				// Beim letzten Element nächster = NULL
				if (i == Anzahl) {index[i]->SetN(0); }

			}
			else {
				// Beim ersten Element vorgänger = NULL
				index[i]->SetV(0);

			}


		}

		// Anker bestücken:
		V_Anker = index[0];
		N_Anker = index[Anzahl-1];

		//Auswahl der Datei [Dateiname -> choice]
		//Auslesen der Datei
		readData(Menu());

		// zur erstellung der Index Liste
		//init();
		// -> verändert und oben bereits passiert

		//sortieren nach MAX-Heap
		//HeapSort();

	}
	else {
		cout << ("Anzahl der gwünschten Objekte zu hoch") << endl;
		cout << ("Maximnal : 1.000.000 Objekte möglich!") << endl;
	}





}

// Ruft Menu zur auswahl einer Datei auf und gibt Datein als Strin "Datei.csv" zurück
string DVK::Menu() {
	int choice;
	do {
		cout << "Bitte Wählen Sie aus den folgenden Dateien: " << endl;
		cout << "(1)  Datei.csv" << endl;
		cout << "(2)  Datei1.csv" << endl;

		cin >> choice;

		switch (choice) {
		case 1:cout << "Daten.csv ausgewählt" << endl;
			cout << "Lade Datei ..." << endl;
			return "Daten.csv";
			break;
		case 2:cout << "Daten1.csv ausgewählt" << endl;
			cout << "Lade Datei ..." << endl;
			return "Daten1.csv";
			break;
		}

	} while (choice != 1 || choice != 2);

	return 0;
}

// choice erwartet Dateiname
void DVK::readData(string choice) {


	//TEMOPRÄRE vARIABLEN
	double B_S, L_S; // L und B (Sek)
	int B_M, L_M;    // L und B (Min)
	int B_G, L_G;    // L und B (Grad)
	double B=0, L=0;      // L und B aus Tabelle   

	double nk_L_Grad, nk_B_Grad; // Nackomma länge und Breite GRAD
	double nk_L_Min, nk_B_Min; // Nackomma länge und Breite MIN

	// für middle Berechnung
	double ges_B_S=0;
	double ges_L_S=0;



	ifstream f(choice) ;
	//f.open(choice, ios::in);
	string input;
	int zaehler_zeile = 0;
	
	

	//while (!f.eof()){
	while(getline(f, input) && zaehler_zeile < anz){
		
		//cout << input << endl;
		char in_arr[100];
		#pragma warning(suppress : 4996)
		strcpy(in_arr, input.c_str());



		//Sekunden einfügen/einelesen
		#pragma warning(suppress : 4996)	
		char* char_array = strtok(in_arr, ","); //Sprung auf ersten eintrag
		B = atof(char_array); // Umwandeln des Wertes in einen Double

		#pragma warning(suppress : 4996)		
		char_array = strtok(NULL, ","); //Sprung auf zweiten eintrag
		L = atof(char_array); // Umwandeln des Wertes in einen Double

		// Grad = L bzw B / 3600 (nachkomma auslagern) --- L_B = L \ 3600
		// Minuten = (nachkomma von GRAD) *60 (nachkomma auslagern)
		// Sekunden = (nachkomma von Minuten)

		//Berechnen des Grads (ohne Nackommastellen)
		B_G = (int)(B / 3600 + 0.5f);
		L_G = (int)(L / 3600 + 0.5f);

		//Nachkommastellen auslesen
		nk_B_Grad = B / 3600 - (int)(B/3600);
		nk_L_Grad = L / 3600 - (int)(L/3600);


		//Berechnen der Minuten (ohne Nackommastellen)
		B_M = (int)(nk_B_Grad * 60 + 0.5f);
		L_M = (int)(nk_L_Grad * 60 + 0.5f);
		//Nackommastellen auslesen
		nk_B_Min = nk_B_Grad * 60 - (int)(nk_B_Grad * 60);
		nk_L_Min = nk_L_Grad * 60 - (int)(nk_L_Grad * 60);


		//Berechne rest Sekunden
		B_S = nk_B_Min * 60;
		L_S = nk_L_Min * 60;




		//zuweisung Grad
		index[zaehler_zeile]->SetBrGr(B_G);
		index[zaehler_zeile]->SetLaGr(L_G);
		//zuweisung Minuten
		index[zaehler_zeile]->SetBrMin(B_M);
		index[zaehler_zeile]->SetLaMin(L_M);
		//zuweisung Sekunden
		index[zaehler_zeile]->SetBrSec(B_S);
		index[zaehler_zeile]->SetLaSec(L_S);



		//Gesamt L und B für Berechnung von middle
		ges_B_S = ges_B_S + B;
		ges_L_S = ges_L_S + L;



		// nächste zeile
		zaehler_zeile++;
	}

	//Berechnung middle [Quick and Dirty - Sorry]
	//initialisierung
	middle = new GEOKO();
	
	B = ges_B_S / anz;
	L = ges_L_S / anz;



	//Berechnen des Grads (ohne Nackommastellen)
	B_G = (int)(B / 3600 + 0.5f);
	L_G = (int)(L / 3600 + 0.5f);

	//Nachkommastellen auslesen
	nk_B_Grad = B / 3600 - (int)(B / 3600);
	nk_L_Grad = L / 3600 - (int)(L / 3600);


	//Berechnen der Minuten (ohne Nackommastellen)
	B_M = (int)(nk_B_Grad * 60 + 0.5f);
	L_M = (int)(nk_L_Grad * 60 + 0.5f);
	//Nackommastellen auslesen
	nk_B_Min = nk_B_Grad * 60 - (int)(nk_B_Grad * 60);
	nk_L_Min = nk_L_Grad * 60 - (int)(nk_L_Grad * 60);


	//Berechne rest Sekunden
	B_S = nk_B_Min * 60;
	L_S = nk_L_Min * 60;


	//zuweisung Grad
	middle->SetBrGr(B_G);
	middle->SetLaGr(L_G);
	//zuweisung Minuten
	middle->SetBrMin(B_M);
	middle->SetLaMin(L_M);
	//zuweisung Sekunden
	middle->SetBrSec(B_S);
	middle->SetLaSec(L_S);




	f.clear(); 
	f.close();
}

// Aufruf mit : vertausche(index1, index2);
void DVK::vertausche(long First, long Second) {
	// First and Second sind index1 und index2 der zu tauschenden Elemente
	
	// temporäre Variablen für index[First]
	DVKE *V_1 = new DVKE();
	DVKE *N_1 = new DVKE();
	GEOKO *temp1;

	// temporäre Variablen für index[First]
	DVKE *V_2 = new DVKE();
	DVKE *N_2 = new DVKE();
	GEOKO *temp2;


	//zwischenspeichern der index[First Werte]
	temp1 = index[First];
	V_1->SetV(index[First]->GetV());
	N_1->SetN(index[First]->GetN());


	//zwischenspeichern der index[First Werte]
	temp2 = index[Second];
	V_2->SetV(index[Second]->GetV());
	N_2->SetN(index[Second]->GetN());


	// +++++++++ FIRST +++++++++
		//Zeiger von Objekt (bei Adresse First) -> Second

		// überschreibe First = Second ( V und N)
		index[First]->SetV(index[Second]->GetV());
		index[First]->SetN(index[Second]->GetN());

		// überschreibe eigentliche Adresse
		index[First] = index[Second];

	// +++++++++ SECOND +++++++++
		//Zeiger von Objekt (bei Adresse Second) -> First

		// überschreibe Second = First[aus zwischenspeicher] (V und N)
		index[Second]->SetV(V_1);
		index[Second]->SetN(N_1);
#

		// überschreibe eigentliche Adresse
		index[Second] = temp1;


	// Fertig Getauscht !
}		