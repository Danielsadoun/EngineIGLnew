#include "Mesh_Data_Struct.h"
#include "igl/circulation.h"
#include <Eigen/LU>

Mesh_Data_Struct::Mesh_Data_Struct(std::string filename, Eigen::MatrixXd& data_F_normals)
{
	igl::read_triangle_mesh(filename, OV, OF);
	V = OV;
	F = OF;
	F_normals = data_F_normals;
	igl::edge_flaps(F, E, EMAP, EF, EI);
	Qit->resize(E.rows());

	C.resize(E.rows(), V.cols());
	Eigen::VectorXd costs(E.rows());
	Q->clear();
	for (int e = 0; e < E.rows(); e++)
	{
		Eigen::Matrix4d QUAD1 = Eigen::Matrix4d::Zero();
		std::vector<int> N1 = igl::circulation(e, false, EMAP, EF, EI);
		for (auto n : N1) {
			Eigen::Vector3d norm = F_normals.row(n).normalized();
			double d = ((-1.0) * V.row(E(e, 0))) * norm;
			Eigen::Vector4d plane(norm[0], norm[1], norm[2], d);
			Eigen::Matrix4d Kp = plane * plane.transpose();
			QUAD1 = QUAD1 + Kp;
		}

		Eigen::Matrix4d QUAD2 = Eigen::Matrix4d::Zero();
		std::vector<int> N2 = igl::circulation(e, true, EMAP, EF, EI);
		for (auto n : N2) {
			Eigen::Vector3d norm = F_normals.row(n).normalized();
			double d = ((-1.0) * V.row(E(e, 1))) * norm;
			Eigen::Vector4d plane(norm[0], norm[1], norm[2], d);
			Eigen::Matrix4d Kp = plane * plane.transpose();
			QUAD2 = QUAD2 + Kp;
		}

		QE.push_back(std::pair<Eigen::MatrixXd, Eigen::MatrixXd>(QUAD1, QUAD2));


		double cost = e;
		Eigen::RowVectorXd p(1, 3);

		Eigen::Matrix4d QUAD3 = QUAD1 + QUAD2;
		Eigen::Matrix4d QUADp = Eigen::Matrix4d::Identity();
		QUADp.block(0, 0, 3, 4) = QUAD3.block(0, 0, 3, 4);
		Eigen::RowVectorXd temp(1,4);
		if (QUADp.fullPivLu().isInvertible()) {
			temp = QUADp.inverse() * (Eigen::Vector4d(0.0, 0.0, 0.0, 1.0));
		}
		else {
			temp = 0.5 * (V.row(E(e, 0)) + V.row(E(e, 1)));
		}

		cost = temp * QUAD3 * temp.transpose();
		p = temp.block(0, 0, 1, 3);

		//igl::shortest_edge_and_midpoint(e, V, F, E, EMAP, EF, EI, cost, p);
		C.row(e) = p;
		(*Qit)[e] = Q->insert(std::pair<double, int>(cost, e)).first;
	}
	num_collapsed = 0;

}

Mesh_Data_Struct:: ~Mesh_Data_Struct() {}

