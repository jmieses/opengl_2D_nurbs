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
	const std::vector<float>& Bspline(std::vector<float>& ctrl_pts);
	const std::vector<float>& NURBS(std::vector<float>& ctrl_pts);
private:
	void deCasteljau_Subroutine(float u);
	void Vector_To_Points(std::vector<float>& ctrl_pts);
	std::vector<float> m_curve;
	std::vector<Point> m_ctrl_pts;
	float m_res = 0.001f;

	void Gen_Knot_Vector();
	int Find_Span(float&);
	void Basis_Funcs(const int&, const float&);
	void Bspline_Subroutine();
	int degree = 3;
	std::vector<float> m_bspline_basis_funcs;
	std::vector<float> m_knot_vector;
	std::vector<float> m_weight_vector;
	
	inline void Scale_Points();
	const std::vector<float>& NURBS_Subroutine();
	float m_weight_sum;
	float m_bspline_basis_funcs_sum;
};
#endif