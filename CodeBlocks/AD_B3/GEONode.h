#pragma once
#include "GEOKO.h"

class GEONode
{
public:


	GEONode(GEOKO *in_root, GEOKO *in_left, GEOKO *in_right, GEOKO *in_mid, GEOKO *index_in);



	//Operationen

	void MaxNote();
	bool groesser(GEOKO G1, GEOKO G2, GEOKO mid);
	GEOKO abstand_mitte(GEOKO G, GEOKO mid);
	void vertausche(long First, long Second);
	void console_output();

	// Attribute
	GEOKO *root = new GEOKO();	// root 
	GEOKO *left = new GEOKO();	// Left
	GEOKO *right = new GEOKO(); // Right
	GEOKO *mid = new GEOKO(); // mitte

	GEOKO index[];




};

