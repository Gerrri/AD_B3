#include "stdafx.h"
#include "DVK.h"
#include "DVKE.h"
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
using namespace std;


// für initialisierung
static GEOKO *index[1000000];
string name;

//Konstruktor DVK
DVK::DVK(long Anzahl) {

	// Abfrage ob Anzahl in ordnung
	if (Anzahl <= 1000000) {
		
		anz = Anzahl;
		int anz_uns = Anzahl;
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
		name = Menu();
		readData(name);

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
			name = "Daten";
			return name+".csv";
			break;
		case 2:cout << "Daten1.csv ausgewählt" << endl;
			cout << "Lade Datei ..." << endl;
			name = "Daten1";
			return (name+".csv");
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


	// Schleife zur Berechnung der Abstände zum Mittelpunkt + Zuweisung
	
	for (int i = 0; i < anz; i++) {
		double temp;
		temp = abs(index[i]->abstand(*middle));

		index[i]->Setdist(temp);
	}
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
	//
	// Gegeben
	// Anzahl der Objekte im Array "anz"
	// Anzahl der noch zu sortierenden Objekte "anz_uns"
	// sortierte anz - unsoriterte
	//


	
	double temp_ver, d_p1, d_p2;
	int node; // Aktueller Knoten
	int anz_uns = anz;
	int j; // zähler;



	//#####################################################################################
	//--------------------------   Aktueller Code   ---------------------------------------
	//#####################################################################################

	//Maxheap aufstellen
	initMaxheap();

	for (int i = 0; i < anz; i++) {

		//if (anz_uns < 1) { break; }

		//vertausche erstes mit letzten Element
		vertausche(0, anz_uns - 1);
		//anzahl der unsortierten dekrementieren
		anz_uns--;

		//versickern des obersten elements
		heapDown(anz_uns);

	}


	//#####################################################################################
	//#####################################################################################


	



	/*
	for(int i=0; i<anz_uns; i++){
		if (anz_uns >= 2) {
			node = (anz_uns / 2) - 1;
		}
		else {
			node = 0;
		}
		j = anz_uns;


		for (int i = node; i >= 0; i--) {
			
			if ((index[i]->Getdist()) < (index[(i * 2) + 1]->Getdist())) {
				vertausche(i, ((i * 2) + 1));
			}

			if ((((i * 2) + 2) != j && anz_uns != 1) && (index[i]->Getdist()) < (index[(i * 2) + 2]->Getdist())) {
				{
					vertausche(i, ((i * 2) + 2));
				}
			}

			j--;
			
		}
		*/


		//erstes mit letzten tauschen
		//vertausche((0), (anz_uns - 1));
		// anz_uns decrementieren
		
		//anz_uns--;


		//
		// Abstände init
		//double root_middle, left_middle, right_middle;
		//
		// Indizes init
		//int root, left, right;
	
	
/*
	while (anz_uns != 0) {
		if (anz_uns >= 2) {
			node = (anz_uns / 2) - 1;
		}
		else {
			node = 0;
		}
		j = anz_uns;


		for (int i = node; i >= 0; i--) {

			//indizes Aktualisieren
			root = i;
			left = (i * 2) + 1;
			right = (i * 2) + 2;
			//Knoten werte Aktualisieren
			root_middle = abs(index[root]->Getdist());
			left_middle = abs(index[left]->Getdist());
			if (right != j) {
				right_middle = abs(index[right]->Getdist());
			}



			if (root_middle < left_middle) {
				vertausche(root, left);

				//Knoten werte Aktualisieren
				root_middle = abs(index[root]->Getdist());
				left_middle = abs(index[left]->Getdist());
				if (right != j) {
					right_middle = abs(index[right]->Getdist());
				}

			}

			if (right != j && anz_uns != 1) {
				if (root_middle < right_middle)
				{

					vertausche(root, right);

				}
			}

			j--;
		}

		//erstes mit letzten tauschen
		vertausche((0), (anz_uns - 1));
		// anz_uns decrementieren
		anz_uns--;

	}
*/


	//korrektur
	//vertausche(0, 1);

	}

// Verwaltung für GEONote
void DVK::heapDown(int anz_uns) {
	int node=0;
	int j = anz;

	for (int i = 0; i < anz; i++) {
		
		
		/*
		root = node;
		left = (node * 2) + 1;
		right = (node * 2) + 2;
		*/

		if (node*2 <= anz_uns && anz_uns >=1) {
			
			// if Right+Left Available
			if (index[(node * 2) + 2] != nullptr) {
						// if			left				   >				right               &&					left			   >	      root	         && (left.index noch zu sortieren?)
						if ((index[(node * 2) + 1]->Getdist()) > (index[(node * 2) + 2]->Getdist()) && ((index[(node * 2) + 1]->Getdist()) > index[node]->Getdist()) && ((node * 2 + 1) < anz_uns)) {

							//vertausche root mit left
							vertausche(node, ((node * 2) + 1));

							//index auf knoten left setzten
							node = node * 2 + 1;
						}

						//else if       right					   >			root		    && (right.index noch zu sortieren?)
						else if (((index[(node * 2) + 2]->Getdist()) >= index[node]->Getdist()) && ((node * 2 + 2) < anz_uns)) {
							//vertausche root mit right
							vertausche(node, ((node * 2) + 2));

							//index auf knoten right setzten
							node = node * 2 + 2;
						}

						// else right == root 
						else {
							//versickern Fertig
							break;
						}

			}
			// if Left Available
			else if (index[(node * 2) + 1] != nullptr) {
						// if			   	left			    >			root		  &&      (left.index noch zu sortieren?)
						if (((index[(node * 2) + 1]->Getdist()) > index[node]->Getdist()) && ((node * 2 + 1) != anz_uns)) {

							//vertausche root mit left
							vertausche(node, ((node * 2) + 1));

							//index auf knoten left setzten
							node = node * 2 + 1;
						}
						else {
							//versickern Fertig
							break;
						}

			}

		}
		else { 
			//versickern Fertig
			break; 
		}
	}
		
		
		
		
		
	}

void DVK::initMaxheap() {
	int anz_uns = anz;
	int j = anz_uns;
	int node;
	
	if (anz_uns >= 2) {
		node = (anz_uns / 2) - 1;
	}
	else {
		node = 0;
	}


		for (int i = node; i >= 0; i--) {

			if ((index[i]->Getdist()) < (index[(i * 2) + 1]->Getdist())) {
				vertausche(i, ((i * 2) + 1));
			}

			if ((((i * 2) + 2) != j && anz_uns != 1) && (index[i]->Getdist()) < (index[(i * 2) + 2]->Getdist())) {
					vertausche(i, ((i * 2) + 2));
			}
			

			j--;

		}
	}

// vertauscht index First mit Index Second und behält doppelte verkettung bei
void DVK::vertausche(long ii, long jj) {

	
	GEOKO * i = index[ii];
	GEOKO * j = index[jj];
	
	DVKE * iN = i->GetN();
	DVKE * iV = i->GetV();
	DVKE * jN = j->GetN();
	DVKE * jV = j->GetV();

	if (iN) iN->SetV(j);
	if (iV) iV->SetN(j);
	if (jN) jN->SetV(i);
	if (jV) jV->SetN(i);

	j->SetV(iV);
	i->SetN(jN);

	if ((ii + 1) == jj) {
		i->SetV(j);
		j->SetN(i);
	}
	else {
		i->SetV(jV);
		j->SetN(iN);
	}

	index[ii] = j;
	index[jj] = i;
	




	
	// temporäre gespeichert G1
	//	GEOKO *temp1 = index[First];
	/*
	DVKE *t_V, *t_N;

	GEOKO *temp1 = new GEOKO;
	GEOKO *temp2 = new GEOKO;

	// werte von First zwischenspeichern in temp1 Pointer
	copy(temp1, index[First]);

	// index[First] POinter = Index[Second]
	copy(index[First], index[Second]);

	//index[Second] Pointer = Index[First]
	copy(index[Second], temp1);


	//index[First]->SetN(index[Second]->GetN());
	//index[First]->SetV(index[Second]->GetV());

	*/
	
}

// Kopiert alle Attribute (ausgenommen Zeiger) von E2 nach E1 [Codeleiche]
void DVK::copy(GEOKO* E1, GEOKO *E2) {

	E1->SetN(E2->GetN());
	E1->SetV(E2->GetV());
	
	/*
	E1->Setaus_csvB(E2->Getaus_csvB());
	E1->Setaus_csvL(E2->Getaus_csvL());

	E1->SetBrGr(E2->GetBrGr());
	E1->SetLaGr(E2->GetLaGr());

	E1->SetBrMin(E2->GetBrMin());
	E1->SetLaMin(E2->GetLaMin());

	E1->SetBrSec(E2->GetBrSec());
	E1->SetLaSec(E2->GetLaSec());
	*/
}

//ACHTUNG !!! Gibt ALLE Elemente der Lise aus !
void DVK::console_output_list() {
	for (int i = 0; i<anz; i++) {
		index[i]->console_output();
	}
}

//Achtung alle datensätze werden in das File geschrieben
void DVK::create_File() {
	string choice = name + "_S.txt";
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





//################################################################################
//MergeSort
void DVK::MergeSort() {

	//Kopie der Index-Liste erstellen
	GEOKO **Liste = copy2(index, anz);

	sortieren(Liste, this->anz);

	//Schreiben der Datei mit erneuter Umrechnung der Gradangaben in Gradsekunden
	ofstream datei;
	datei.open(name+".cvs");
	for (int i = 0; i < anz; i++) {
		double br_temp = ((Liste[i]->GetBrSec() / 60 + Liste[i]->GetBrMin()) / 60 + Liste[i]->GetBrGr()) * 3600;
		double la_temp = ((Liste[i]->GetLaSec() / 60 + Liste[i]->GetLaMin()) / 60 + Liste[i]->GetLaGr()) * 3600;
		datei << "   " << std::fixed << std::setprecision(2) << br_temp << ",   " << std::fixed << std::setprecision(2) << la_temp << ";\n";
	}
	datei.close();


}

void DVK::sortieren(GEOKO *Liste[], int länge) {


	if (länge > 1) {
		//Teilen der Liste in zwei Hälften
		GEOKO **Links = new GEOKO*[länge / 2];
		GEOKO **Rechts = new GEOKO*[(länge + 1) / 2];

		for (int i = 0; i < länge / 2; ++i) {
			Links[i] = Liste[i];
		}
		for (int i = länge / 2; i < länge; ++i) {
			Rechts[i - länge / 2] = Liste[i];
		}

		//Rekursiver Aufruf, um die Liste weiter in Einzelteile zu teilen
		sortieren(Links, länge / 2);
		sortieren(Rechts, (länge + 1) / 2);


		GEOKO **pos1 = &Links[0];
		GEOKO **pos2 = &Rechts[0];

		//Zusammenfügen
		//Falls pos1 näher am Mittelpunkt als pos2 liegt, wird das Element an der entsprechenden Position in die neue Liste eingefügt
		for (int i = 0; i < länge; ++i) {
			if ((*this->middle - **pos2) - (*this->middle - **pos1) > 0.0001) {
				Liste[i] = *pos1;
				if (pos1 != &Rechts[(länge + 1) / 2 - 1]) { // pos1 nicht verändern, wenn der größte Wert mehrmals vorkommt
					if (pos1 == &Links[länge / 2 - 1]) {
						pos1 = &Rechts[(länge + 1) / 2 - 1];
					}
					else {
						++pos1;
					}
				}
			}
			//Ansonsten umgekehrt
			else {
				Liste[i] = *pos2;
				if (pos2 == &Rechts[(länge + 1) / 2 - 1]) {
					pos2 = &Links[länge / 2 - 1];
				}
				else {
					++pos2;
				}
			}
		}
	}
}

GEOKO** DVK::copy2(GEOKO *Liste[], int anz) {
	GEOKO **kopie = new GEOKO*[anz];

	for (int i = 0; i < anz; i++) {
		kopie[i] = Liste[i];
	}
	return kopie;
}


