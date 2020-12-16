#include "Curve.h"
#include <iostream>


std::vector<float> Curve::deCasteljau(std::vector<float>& ctrl_pts){
	Vector_To_Points(ctrl_pts);

	if(!m_curve.empty()) m_curve.clear();

	for(float u = 0.; u < 1.; u += m_res){
		deCasteljau_Subroutine(u);
	}

	return m_curve;
}

void Curve::deCasteljau_Subroutine(float u){
	std::vector<Point> tmp_ctrl_pts(m_ctrl_pts);
	for(unsigned int i = 1; i < tmp_ctrl_pts.size(); i++){
		for(unsigned int j = 0; j < tmp_ctrl_pts.size() - i; j++){
			tmp_ctrl_pts[j].x = (1. - u) * tmp_ctrl_pts[j].x + u * tmp_ctrl_pts[j + 1].x;
			tmp_ctrl_pts[j].y = (1. - u) * tmp_ctrl_pts[j].y + u * tmp_ctrl_pts[j + 1].y;
		}
	}

	m_curve.emplace_back(tmp_ctrl_pts[0].x);
	m_curve.emplace_back(tmp_ctrl_pts[0].y);
	m_curve.emplace_back(0.);
}

void Curve::Vector_To_Points(std::vector<float>& vertices){
	if(!m_ctrl_pts.empty()) m_ctrl_pts.clear();

	for(int i = 1; i < vertices.size(); i+=3){
		Point point;
		point.x = vertices.at(i-1);
		point.y = vertices.at(i);
		m_ctrl_pts.emplace_back(point);
	}
}