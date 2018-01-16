#include "stdafx.h"
#include "DVK.h"
#include <fstream>
#include <stdio.h>

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
		*V_Anker = *index[0];
		*N_Anker = *index[Anzahl];

		//Auswahl der Datei [Dateiname -> choice]
		//Auslesen der Datei
		readData(Menu());

		// zur erstellung der Index Liste
		//init();
		// -> verändert und oben bereits passiert

		//sortieren nach MAX-Heap
		HeapSort();

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
		case 1:cout << "Datei.csv ausgewählt" << endl;
			cout << "Lade Datei ..." << endl;
			return "Datei.csv";
			break;
		case 2:cout << "Datei1.csv ausgewählt" << endl;
			cout << "Lade Datei ..." << endl;
			return "Datei1.csv";
			break;
		}

	} while (choice != 1 || choice != 2);
}

// choice erwartet Dateiname
void DVK::readData(string choice) {


	//TEMOPRÄRE vARIABLEN
	double B_S, L_S; // L und B (Sek)
	int B_M, L_M;    // L und B (Min)
	int B_G, L_G;    // L und B (Grad)
	double B, L;      // L und B aus Tabelle   

	double nk_L_Grad, nk_B_Grad; // Nackomma länge und Breite GRAD
	double nk_L_Min, nk_B_Min; // Nackomma länge und Breite MIN




	ifstream f;
	f.open(choice, ios::in);
	char* input;

	int zaehler_zeile = 0;
	while (!f.eof())
	{
		//f.getline(f, input);
		
		f.getline(input, 99);

		//Sekunden einfügen/einelesen
		char* char_array = strtok(input, ","); //Sprung auf ersten eintrag
		B = atof(char_array); // Umwandeln des Wertes in einen Double

		char_array = strtok(input, ","); //Sprung auf zweiten eintrag
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



		// nächste zeile
		zaehler_zeile++;
	}


	f.clear(); 
	f.close();
}

// Aufruf mit : vertausche(index1, index2);
void DVK::vertausche(long First, long Second) {
	// First and Second sind index1 und index2 der zu tauschenden Elemente
	
	// temporäre Variablen für index[First]
	DVKE *V_1, *N_1;
	GEOKO *temp1;

	//zwischenspeichern der index[First Werte]
	temp1 = index[First];
	V_1 = index[First]->GetV;
	N_1 = index[First]->GetN;


	// +++++++++ FIRST +++++++++
		//Zeiger von Objekt (bei Adresse First) -> Second

		// überschreibe First = Second ( V und N)
		index[First]->SetV(index[Second]->GetV);
		index[First]->SetN(index[Second]->GetN);

		// überschreibe eigentliche Adresse
		index[First] = index[Second];

	// +++++++++ SECOND +++++++++
		//Zeiger von Objekt (bei Adresse Second) -> First

		// überschreibe Second = First[aus zwischenspeicher] (V und N)
		index[Second]->SetV(V_1);
		index[Second]->SetN(N_1);

		// überschreibe eigentliche Adresse
		index[Second] = temp1;


	// Fertig Getauscht !
}		