#pragma once
#ifndef CURVE_H
#define CURVE_H

#include <vector>
struct Point {
	float x;
	float y;
};

class Curve{
public:
	Curve() = default;
	const std::vector<float>& deCasteljau(std::vector<float>& ctrl_pts);
	const std::vector<float>& Bspline(std::vector<flaot>& ctrl_pts);
private:
	void deCasteljau_Subroutine(float u);
	void Vector_To_Points(std::vector<float>& ctrl_pts);
	std::vector<float> m_curve;
	std::vector<Point> m_ctrl_pts;
	float m_res = (float)0.001;

	void Gen_Knot_Vector();
	unsigned int Find_Span(int* mid);
	void Basis_Funcs();
	void Bspline_Subroutine();
	std::vector<float> m_bspline_basis_funcs;
	std::vector<float> m_knot_vector;
	int bspline_degree = 3;
};
#endif