
class GEOKO : public DVKE {
public:
    GEOKO();
    int GetBrGr() const {return BrGr;}
    int GetLaGr() const {return LaGr;}
    void SetBrGr(int BrGr) {this->BrGr = BrGr;}
    void SetLaGr(int LaGr) {this->LaGr = LaGr;}


    
private:
    int BrGr;
    int LaGr;
    int BrMin;
    int LaMin;
    double BrSec;
    double LaSec;
    
};

