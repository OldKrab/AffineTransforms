#include "AffineTransforms.h"

Matrix<float>  AffineTransforms::Translate(const Matrix<float>& dots, sf::Vector3f tr)
{
	Matrix<float> t({
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{tr.x, tr.y, tr.z, 1} });
	return dots * t;
}

Matrix<float>  AffineTransforms::Scale(const Matrix<float>& dots, sf::Vector3f sc)
{
	Matrix<float> s({
		{sc.x,0,0,0},
		{0,sc.y,0,0},
		{0,0,sc.z,0},
		{0, 0, 0, 1} });
	return dots * s;
}

Matrix<float> AffineTransforms::Rotate(const Matrix<float>& dots, sf::Vector3f rt)
{
	using std::cosf; using std::sinf;
	Matrix<float> rx({
		{1,	0,				0,			0},
		{0,	cosf(rt.x),		sinf(rt.x),	0},
		{0,	-sinf(rt.x),	cosf(rt.x),	0},
		{0, 0,				0,			1} });
	Matrix<float> ry({
		{cosf(rt.y),	0,	-sinf(rt.y),	0},
		{0,				1,	0,				0},
		{sinf(rt.y),	0,	cosf(rt.y),		0},
		{0,				0,	0,				1} });
	Matrix<float> rz({
		{cosf(rt.z),	sinf(rt.z),	0,	0},
		{-sinf(rt.z),	cosf(rt.z),	0,	0},
		{0,				0,			1,	0},
		{0,				0,			0,	1} });
	return dots * rx * ry * rz;
}

Matrix<float> AffineTransforms::ProjectionOnXY(const Matrix<float>& dots, float angle)
{
	float f = 1.f / 2;
	float alpha = -std::cosf(angle) * f;
	float beta = -std::sinf(angle) * f;
	Matrix<float> p({
		{1,0,0,0},
		{0,1,0,0},
		{alpha,beta,1,0},
		{0, 0, 0, 1} });
	return dots * p;
}
