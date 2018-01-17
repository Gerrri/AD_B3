#pragma once
#include "GEOKO.h"

class GEONote
{
public:
	

	GEONote(GEOKO in_root, GEOKO in_left, GEOKO in_right, GEOKO in_mid, GEOKO *index_in);



	//Operationen

	void Maxheap();
	bool groesser(GEOKO G1, GEOKO G2, GEOKO mid);
	GEOKO abstand_mitte(GEOKO G, GEOKO mid);
	void vertausche(long First, long Second);


	// Attribute
	GEOKO *root = new GEOKO();	// root 
	GEOKO *left = new GEOKO();	// Left
	GEOKO *right = new GEOKO(); // Right

	GEOKO *mid = new GEOKO(); // mitte

	GEOKO index[];


	
};

