#include "stdafx.h"
#include "DVK.h"
#include <fstream>




DVK::DVK(long Anzahl) {

	// Abfrage ob Anzahl in ordnung
	if (Anzahl <= 1000000) {
		
		anz = Anzahl;
		int const x = Anzahl;

		GEOKO *index[5];

		for (int i = 0; i<Anzahl; i++) {
			*index[i] = *(new GEOKO());

			// Zuweisung der Nachfolger bzw Vorg�gner
			if (i > 0) {
				//vorg�nger = index - 1
				index[i]->SetV(index[i - 1]);

				//(bei vorherigen)n�chstes = index (aktuelles)
				index[i - 1]->SetN(index[i]);

				// Beim letzten Element n�chster = NULL
				if (i == Anzahl) {index[i]->SetN(0); }

			}
			else {
				// Beim ersten Element vorg�nger = NULL
				index[i]->SetV(0);

			}


		}

		// Anker best�cken:
		*V_Anker = *index[0];
		*N_Anker = *index[Anzahl];

		//Auswahl der Datei [Dateiname -> choice]
		//Auslesen der Datei
		readData(Menu());

		// zur erstellung der Index Liste
		//init();
		// -> ver�ndert und oben bereits passiert

		//sortieren nach MAX-Heap
		HeapSort();

	}
	else {
		cout << ("Anzahl der gw�nschten Objekte zu hoch") << endl;
		cout << ("Maximnal : 1.000.000 Objekte m�glich!") << endl;
	}





}

string DVK::Menu() {
	int choice;
	do {
		cout << "Bitte W�hlen Sie aus den folgenden Dateien: " << endl;
		cout << "(1)  Datei.csv" << endl;
		cout << "(2)  Datei1.csv" << endl;

		cin >> choice;

		switch (choice) {
		case 1:cout << "Datei.csv ausgew�hlt" << endl;
			cout << "Lade Datei ..." << endl;
			return "Datei.csv";
			break;
		case 2:cout << "Datei1.csv ausgew�hlt" << endl;
			cout << "Lade Datei ..." << endl;
			return "Datei1.csv";
			break;
		}

	} while (choice != 1 || choice != 2);
}

void DVK::readData(string choice) {


	//TEMOPR�RE vARIABLEN
	double B_S, L_S; // L und B (Sek)
	int B_M, L_M;    // L und B (Min)
	int B_G, L_G;    // L und B (Grad)
	double B, L;      // L und B aus Tabelle   

	double nk_L_Grad, nk_B_Grad; // Nackomma l�nge und Breite GRAD
	double nk_L_Min, nk_B_Min; // Nackomma l�nge und Breite MIN




	ifstream f;
	f.open(choice, ios::in);
	char* input;

	int zaehler_zeile = 0;
	while (!f.eof())
	{
		getline(f, input);
	

		//Sekunden einf�gen/einelesen
		char* char_array = strtok(input, ","); //Sprung auf ersten eintrag
		string a = char_array;
		B = Double.parseDouble(a); // Umwandeln des Wertes in einen Double

		char_array = strtok(input, ","); //Sprung auf zweiten eintrag
		L = input;

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



		// n�chste zeile
		zaehler_zeile++;
	}

	f.close();
}
