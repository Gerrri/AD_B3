
class DVKE {
public:
    // Konstruktor
    DVKE(DVKE* V, DVKE* N);
    DVKE();
    
    // Getter
    DVKE* GetN() const {return N;}
    DVKE* GetV() const {return V;}
    
    // Setter
    void SetN(DVKE* N) {this->N = N;}
    void SetV(DVKE* V) {this->V = V;}

    
private:
    DVKE *V; // Element daVOR
    DVKE *N; // Element daNACH
};


