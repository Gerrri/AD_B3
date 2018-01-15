using namespace std;

class DVK {
public:
   
   //Nur Heapsort!
   void heapDown(long Anzahl, long Knoten);
   void erzeugeHeap(long Anzahl);
   void vertausche(long First, long Second);
   void init();
    
private:
    //Konstruktor
    DVK(long Anzahl){}; 
    void HeapSort(){};// in DVK Konstruktor
    string Menu(){}; // Menü zur abfrage der der Datei
    void readData(string input){
        
    }
    
    //Varaibalen zu Verankerung / Mitte
    GEOKO *V_Anker;
    GEOKO *N_Anker;
    GEOKO *middle;
    
    // für initialisierung
    GEOKO *index[];
        
    void init();
    
    int anz;
};



