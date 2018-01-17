#include "stdafx.h"
#include "GEONode.h"


GEONode::GEONode(GEOKO in_root, GEOKO in_left, GEOKO in_right, GEOKO in_mid, GEOKO *index_in) {
	*root = in_root;
	*left = in_left;
	*right = in_right;

	*mid = in_mid;
	*index = *index_in;

}


//Sortiert den Knoten
void GEONode::MaxNote() {
	
	if (groesser(*left, *root, *mid)) {
		// wenn left größer root
		vertausche(left->Geta_num, root->Geta_num);
	}

	if (groesser(*right, *root, *mid)) {
		// wenn right größer root
		vertausche(right->Geta_num, root->Geta_num);
	}


}


// gibt true zurück wenn G1 > G2 in bezug auf middle [wenn beide gleich - false]
bool GEONode::groesser(GEOKO G1, GEOKO G2, GEOKO mid) {
	GEOKO G1_fm, G2_fm; // G1, G2 "f"rom "m"iddle -> G1_fm

						// Berechnung des Abstands zur mitte
	G1_fm = abstand_mitte(G1, mid);
	G2_fm = abstand_mitte(G2, mid);



	if (G1_fm.GetBrGr() > G2_fm.GetBrGr()) {
		return true;
	}
	else if (G1_fm.GetBrGr() == G2_fm.GetBrGr()) {

		if (G1_fm.GetBrMin() > G2_fm.GetBrGr()) {
			return true;
		}
		else if (G1_fm.GetBrMin() == G2_fm.GetBrMin()) {

			if (G1_fm.GetBrSec() > G2_fm.GetBrSec()) {
				return true;
			}
			else {
				false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}



}


// gibt den Differenz GEOKO von G zur mitte zurück
GEOKO GEONode::abstand_mitte(GEOKO G, GEOKO mid) {
	GEOKO *ret = new GEOKO();

	ret->SetBrGr((G.GetBrGr() - mid.GetBrGr()));
	ret->SetLaGr((G.GetLaGr() - mid.GetLaGr()));

	ret->SetBrMin((G.GetBrMin() - mid.GetBrMin()));
	ret->SetLaMin((G.GetLaMin() - mid.GetLaMin()));

	ret->SetBrSec((G.GetBrSec() - mid.GetBrSec()));
	ret->SetLaSec((G.GetLaSec() - mid.GetLaSec()));

	return *ret;
}


// Aufruf mit : vertausche(index1, index2); - vertauscht einträge in indexliste + doppelte verkettung
void GEONode::vertausche(long First, long Second) {

	// temporäre gespeichert G1
	GEOKO temp1 = index[First];

	//Elemente komplett getauscht
	index[First] = index[Second];
	index[Second] = temp1;

	// ehemalig First zeiger für DVK korrigiern  
	index[Second].SetV(index[First].GetV());
	index[Second].SetN(index[First].GetN());

	// ehemalig Second zeiger für DVK korrigiern
	index[First].SetV(temp1.GetV());
	index[First].SetN(temp1.GetN());



} 