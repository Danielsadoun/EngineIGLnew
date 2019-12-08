#include "Movable.h"

Movable::Movable()
{
	T = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
}

Eigen::Matrix4f Movable::MakeTrans()
{
	return T.matrix();
}

void Movable::MyTranslate(Eigen::Vector3f amt)
{
	T.pretranslate(amt);
	//T.translate(amt);
}
//angle in radians
void Movable::MyRotate(Eigen::Vector3f rotAxis, float angle)
{
	T.rotate(Eigen::AngleAxisf(angle, rotAxis.normalized()));
}

void Movable::MyScale(Eigen::Vector3f amt)
{
	T.scale(amt);
}

/*void Movable::TranslateInSystem(Eigen::Matrix4d Mat, Eigen::Vector3d amt, bool preTranslate) {
	MyTranslate(Mat.block<3, 3>(0, 0).transpose() * amt);
}*/

/*void Movable::RotateInSystem(Eigen::Matrix4d Mat, Eigen::Vector3d rotAxis, double angle) {
	MyRotate(Mat.block<3, 3>(0, 0).transpose() * rotAxis, angle);
}*/

/*void Movable::SetCenterOfRotation(Eigen::Vector3d amt) {
	Tin.translate(-amt);
	Tout.translate(amt);
}*/

/*Eigen::Vector3d Movable::GetCenterOfRotation() {
	return -Tin.translation();
}*/