#include "Curve.h"
#include <numeric>
const std::vector<float>& Curve::deCasteljau(std::vector<float>& ctrl_pts){
	Vector_To_Points(ctrl_pts);

	if(!m_curve.empty()) m_curve.clear();

	for(float u = 0.0f; u < 1.0f; u += m_res){
		deCasteljau_Subroutine(u);
	}

	return m_curve;
}

void Curve::deCasteljau_Subroutine(float u){
	std::vector<Point> tmp_ctrl_pts(m_ctrl_pts);
	for(unsigned int i = 1; i < tmp_ctrl_pts.size(); i++){
		for(unsigned int j = 0; j < tmp_ctrl_pts.size() - i; j++){
			tmp_ctrl_pts[j].x = ((float)1. - u) * tmp_ctrl_pts[j].x + u * (tmp_ctrl_pts[j + 1].x);
			tmp_ctrl_pts[j].y = ((float)1. - u) * tmp_ctrl_pts[j].y + u * (tmp_ctrl_pts[j + 1].y);
		}
	}

	m_curve.emplace_back(tmp_ctrl_pts[0].x);
	m_curve.emplace_back(tmp_ctrl_pts[0].y);
	m_curve.emplace_back(0.0f);
}

const std::vector<float>& Curve::Bspline(std::vector<float>& ctrl_pts){
	Vector_To_Points(ctrl_pts);

	if(!m_curve.empty()) m_curve.clear();
	if(m_knot_vector.empty()) Gen_Knot_Vector();

	for(float u = 0.0f; u <= 1.0f; u += m_res){
		int span = this->Find_Span(u);
		Basis_Funcs(span, u);
		float x = 0.0f, y = 0.0f;
		for(int i = 0; i < degree + 1; i++){
			x = x + m_bspline_basis_funcs[i] * m_ctrl_pts[span - degree + i].x;
			y = y + m_bspline_basis_funcs[i] * m_ctrl_pts[span - degree + i].y;
		}
		m_curve.emplace_back(x);
		m_curve.emplace_back(y);
		m_curve.emplace_back(0.);
	}

	return m_curve;
}

void Curve::Gen_Knot_Vector(){
	int n = m_ctrl_pts.size();

	if(!m_knot_vector.empty()) m_knot_vector.clear();
	
	for (int i = 0; i < degree + 1; ++i)   { m_knot_vector.emplace_back(0.0f); }

	for (int i = 1; i < (n - degree); ++i)
	{
		m_knot_vector.emplace_back((float)i / (float)(n - degree + 1));
	}

	for (int i = 0; i < degree + 1; ++i)   { m_knot_vector.emplace_back(1.); }
}

int Curve::Find_Span(float& u){
	int n = m_knot_vector.size() - 1;

	if(u == m_knot_vector.back()) return n;

	int low = degree, high = n + 1;

	int mid = (low + high) / 2;

	while ( u < m_knot_vector[mid] || u >= m_knot_vector[mid + 1]){
		if (u < m_knot_vector[mid]) high = mid;
		else 						low = mid;
		mid = (low + high) / 2;
	}
	return mid;
}

void Curve::Basis_Funcs(const int& span,const float& knot){
	if(!m_bspline_basis_funcs.empty()) m_bspline_basis_funcs.clear();

	m_bspline_basis_funcs.emplace_back(1.0f);

	std::vector<float> left(degree + 1, 1);
	std::vector<float> right(degree + 1, 1);

	for(int j = 1; j < degree + 1; j++){
		left[j] = knot - m_knot_vector[span + 1 - j];
		right[j] = m_knot_vector[span + j] - knot;
		float saved = 0.0f;   
		for(int r = 0; r < j; r++){
			float temp = m_bspline_basis_funcs[r] / (right[r+1] + left[j-r]);
			m_bspline_basis_funcs[r] = saved + right[r+1] * temp;
			saved = left[j-r] * temp;
		}
	m_bspline_basis_funcs.emplace_back(saved);
	}
}

void Curve::Vector_To_Points(std::vector<float>& vertices){
	if(!m_ctrl_pts.empty()) m_ctrl_pts.clear();

	for(int i = 1; i < vertices.size(); i += 3){
		Point point;
		point.x = vertices.at(i-1);
		point.y = vertices.at(i);
		m_ctrl_pts.emplace_back(point);
	}
}

const std::vector<float>& Curve::NURBS(std::vector<float>& ctrl_pts){
	Vector_To_Points(ctrl_pts);

	// create weights vector
	if(!m_weight_vector.empty()) m_weight_vector.clear();

	for(int i = 0; i < m_ctrl_pts.size(); i++) m_weight_vector.emplace_back(10.0f);

	Scale_Points();

	return NURBS_Subroutine();

	// auto& will always work in this case. auto&& resolves issue with std::vector<bool> proxy refernece, which is not the case here.
	// Check https://devblogs.microsoft.com/cppblog/details-about-some-of-the-new-c-language-features/ for reference
	// for(auto& p : m_curve){
	// 	p = p / (float)(N * w) ;
	// }
}

// inline void Curve::Scale_Points(std::vector<Point>* ctrl_pts, std::vector<float>& weight){

// 	for(int i = 0; i < ctrl_pts.size(); i++){
// 		ctrl_pts[i]->x = weight[i] * ctrl_pts[i]->x;
// 		ctrl_pts[i]->y = weight[i] * ctrl_pts[i]->y;
// 	}
// }

inline void Curve::Scale_Points(){

	for(int i = 0; i < m_ctrl_pts.size(); i++){
		m_ctrl_pts[i].x = m_ctrl_pts[i].x * m_weight_vector[i];
		m_ctrl_pts[i].y = m_ctrl_pts[i].y * m_weight_vector[i];
	}
}

const std::vector<float>& Curve::NURBS_Subroutine(){
	

	if(!m_curve.empty()) m_curve.clear();
	if(m_knot_vector.empty()) Gen_Knot_Vector();

	for(float u = 0.0f; u <= 1.0f; u += m_res){
		int span = this->Find_Span(u);
		Basis_Funcs(span, u);

		float basis_weight = 0.f;

		for(unsigned int i =0; i < degree + 1; i++){
			basis_weight += m_bspline_basis_funcs[i] * m_weight_vector[span - degree + i];
		}

		float x = 0.0f, y = 0.0f;
		for(int i = 0; i < degree + 1; i++){
			x += (m_bspline_basis_funcs[i] * m_ctrl_pts[span - degree + i].x);
			y += (m_bspline_basis_funcs[i] * m_ctrl_pts[span - degree + i].y);
		}
		m_curve.emplace_back(x / basis_weight);
		m_curve.emplace_back(y / basis_weight);
		m_curve.emplace_back(0.);
	}

	return m_curve;
}