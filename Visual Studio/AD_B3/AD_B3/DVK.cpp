#include "stdafx.h"
#include "DVK.h"
#include "DVKE.h"
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
using namespace std;


// für initialisierung
static GEOKO *index[1000000];
string choice;

//Konstruktor DVK
DVK::DVK(long Anzahl) {

	// Abfrage ob Anzahl in ordnung
	if (Anzahl <= 1000000) {
		
		anz = Anzahl;
		anz_uns = Anzahl;
		//int const x = Anzahl;

		for (int i = 0; i<Anzahl; i++){

			index[i] = new GEOKO();
			index[i]->Seta_num(i); // code leiche


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
				index[i]->SetV(nullptr);

			}


		}

		// Anker bestücken:
		V_Anker = index[0];
		N_Anker = index[Anzahl-1];

		//Auswahl der Datei [Dateiname -> choice]
		//Auslesen der Datei
		choice = Menu();
		readData(choice);

		//Ausgabe Middle
		cout << "" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Mittelpunkt der Daten liegt bei :" << endl;
		middle->console_output();
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "" << endl;
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

// Ruft Menu zur auswahl einer Datei auf und gibt den Dateiname als String "Datei.csv" zurück
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

// choice erwartet Dateiname als String
void DVK::readData(string choice) {


	//TEMOPRÄRE vARIABLEN
	double B_S, L_S; // L und B (Sek)
	int B_M, L_M;    // L und B (Min)
	int B_G, L_G;    // L und B (Grad)
	double B=0, L=0; // L und B aus Tabelle   

	double nk_L_Grad, nk_B_Grad;	// Nackomma länge und Breite GRAD
	double nk_L_Min, nk_B_Min;		// Nackomma länge und Breite MIN

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
		B_G = (int)(B / 3600);
		L_G = (int)(L / 3600);

		//Nachkommastellen auslesen
		nk_B_Grad = B / 3600 - (int)(B/3600);
		nk_L_Grad = L / 3600 - (int)(L/3600);


		//Berechnen der Minuten (ohne Nackommastellen)
		B_M = (int)(nk_B_Grad * 60);
		L_M = (int)(nk_L_Grad * 60);

		//Nackommastellen auslesen
		nk_B_Min = nk_B_Grad * 60 - (int)(nk_B_Grad * 60);
		nk_L_Min = nk_L_Grad * 60 - (int)(nk_L_Grad * 60);


		//Berechne rest Sekunden
		B_S = nk_B_Min * 60;
		L_S = nk_L_Min * 60;



		//zuweisung inhalt liste
		index[zaehler_zeile]->Setaus_csvB(B);
		index[zaehler_zeile]->Setaus_csvL(L);
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



	//zuweisung inhalt liste
	middle->Setaus_csvB(B);
	middle->Setaus_csvL(L);
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


void DVK::HeapSort() {

	//Knoten = index
	//Knoten 1 -> 2,3 || Knoten 2 -> 4,5 || Knoten 3 -> 6,7
	//Knotenindex + (Knotenindex +1) = Anfang der Kinder
	//+-----------------+------------------+
	//|    Kind 1       |      Kind 2      |
	//+-----------------|------------------|
	//| Knotenindex *2  | Kind1.index +1   |
	//+-----------------+------------------+
	
	// Gegeben
	// Anzahl der Objekte im Array "anz"
	// Anzahl der noch zu sortierenden Objekte "anz_uns"
	// sortierte anz - unsoriterte


	int AktNode; // Aktueler Knoten
	// Schleife für runterzäglen von knoten
	double temp_ver, d_p1, d_p2;
	
	anz_uns = anz;


	for (int i=anz_uns; i > 1; i--) {
		AktNode = (int)(anz_uns / 2); // bei 7 elementen anfang bei 7/2 = 3.5 -> Knoten(index) 3
		AktNode = AktNode - 1;

		///*root */ index[AktNode];
		///*left */ index[AktNode * 2 ];
		///*right*/ index[AktNode * 2 + 1];

			
		
			
			// left > root
			// temp Debug zwecke
			



			//d_p1 = index[AktNode] - middle;
			//d_p2 = index[AktNode * 2 + 1] - middle;
			d_p1 = index[AktNode]->abstand(*middle);
			d_p2 = index[AktNode * 2 + 1]->abstand(*middle);

			temp_ver = (d_p1) - (d_p2);


			
			if ( temp_ver > 0.0001){
				//vertausche root und left
				vertausche(AktNode, (AktNode * 2 + 1)); // +1  = korrektur dex index
			}

			if ((anz_uns+1) == AktNode * 2 + 2) {
				temp_ver = (index[AktNode] - middle) - (index[AktNode * 2 + 2] - middle);
				if (temp_ver < 0.0001) {
					vertausche(AktNode, (AktNode * 2 + 2)); // +2  = korrektur dex index
				}
			}

			// wenn Anzahl unsortierte elem. = AktNode * 2 + 2
			//temp = AktNode * 2 + 2;
			//if (anz_uns == temp) {
				// right > root
			//	if ((index[AktNode] - middle) - (index[AktNode * 2 + 2] - middle) > 0, 0001) {
					// vertausche root und right
			//		vertausche(AktNode, (AktNode * 2 + 2));
			//	}
			anz_uns--;
		}

		
			


	}


// Verwaltung für GEONote



void DVK::vertausche(long First, long Second) {

	// temporäre gespeichert G1
	//	GEOKO *temp1 = index[First];

	DVKE *t_V, *t_N;

	GEOKO *temp1 = new GEOKO;
	temp1 = index[First];
	t_V = index[First]->GetV();
	t_N = index[First]->GetN();
	


	index[First]->SetN(index[Second]->GetN());
	index[First]->SetV(index[Second]->GetV());



	//Elemente komplett getauscht
	index[First] = index[Second];
	index[Second] = temp1;



	index[Second]->SetN(temp1->GetN());
	index[Second]->SetV(temp1->GetV());

	// ehemalig First zeiger für DVK korrigiern  
	//index[Second]->SetV(index[First]->GetV());
	//index[Second]->SetN(index[First]->GetN());

	// ehemalig Second zeiger für DVK korrigiern
	//index[First]->SetV(temp1->GetV());
	//index[First]->SetN(temp1->GetN());
}

//ACHTUNG !!! Gibt ALLE Elemente der Lise aus !
void DVK::console_output_list() {
	for (int i = 0; i<anz; i++) {
		index[i]->console_output();
	}
}

//Achtung alle datensätze werden in das File geschrieben
void DVK::create_File(string choice){
	ofstream file;
	file.open(choice, std::ofstream::out | std::ofstream::trunc);
	string temp;
	string sec_L_s, sec_B_s;

	double sec_B, sec_L;

	if (file.is_open()) {
		file.clear();
		//file << " [Format: (LängenGrad/BreitenGrad) || (LängenMinute/BreitenMinute) || (LängenSekunde/BreitenSekunde])" << endl;
		for (int i = 0; i < anz; i++) {

			

			
			sec_L = (index[i]->GetLaGr() * 3600) + (index[i]->GetLaMin() * 60) + index[i]->GetLaSec();
			sec_B = (index[i]->GetBrGr() * 3600) + (index[i]->GetBrMin() * 60) + index[i]->GetBrSec();
			
			sec_L_s = to_string(sec_L);
			sec_B_s = to_string(sec_B);

			file << sec_B_s << ", " << sec_L_s << ";" <<endl;


		}

		file.close();
	}
	else {
		cout << "Datei konnte nicht geöffnet werden!" << endl;
	}

}




