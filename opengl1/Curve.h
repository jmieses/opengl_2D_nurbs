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
private:
	void deCasteljau_Subroutine(float u);
	void Vector_To_Points(std::vector<float>& ctrl_pts);
	std::vector<float> m_curve;
	std::vector<Point> m_ctrl_pts;
	float m_res = (float)0.001;
};
#endif