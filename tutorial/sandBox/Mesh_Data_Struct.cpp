#include "Mesh_Data_Struct.h"


Mesh_Data_Struct::Mesh_Data_Struct(std::string filename)
{
	igl::read_triangle_mesh(filename, OV, OF);
	V = OV;
	F = OF;
	igl::edge_flaps(F, E, EMAP, EF, EI);
	Qit->resize(E.rows());

	C.resize(E.rows(), V.cols());
	Eigen::VectorXd costs(E.rows());
	Q->clear();
	for (int e = 0; e < E.rows(); e++)
	{
		double cost = e;
		Eigen::RowVectorXd p(1, 3);
		igl::shortest_edge_and_midpoint(e, V, F, E, EMAP, EF, EI, cost, p);
		C.row(e) = p;
		(*Qit)[e] = Q->insert(std::pair<double, int>(cost, e)).first;
	}
	num_collapsed = 0;

}

Mesh_Data_Struct:: ~Mesh_Data_Struct() {}