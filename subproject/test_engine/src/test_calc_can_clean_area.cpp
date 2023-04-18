#include <iostream>
#include <string>
#include <stack>
#include "Eigen/Core"
#include "Eigen/SparseCore"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>


#define ROBOT_R 0.175//m

using namespace std;
using namespace cv;

class DeviceObserver
{
public:
	// m / pixels
	void set_meter_pixels(float m)
	{
		m_meter_pixels = m;
	}
	void set_refer_pose(const Eigen::Vector2i &v)
	{
		m_refer_pose = v;
	}

	bool find_clear_point_in_mat(const Mat &_mat, cv::Point &_p)
	{
		int width = _mat.cols;
		int height = _mat.rows;
		_p = cv::Point(m_refer_pose[0], m_refer_pose[1]);
		if (_mat.at<uchar>(_p.y, _p.x) == 255)
		{
			return true;
		}
		stack<cv::Point> stack_p;
		stack_p.push(_p);
		while (!stack_p.empty())
		{
			cv::Point cur = stack_p.top();
			stack_p.pop();
			if (_mat.at<uchar>(cur.y, cur.x + 1) == 255)
			{
				_p = cv::Point(cur.x + 1, cur.y);
				return 1;
			}
			if (_mat.at<uchar>(cur.y, cur.x - 1) == 255)
			{
				_p = cv::Point(cur.x + 1, cur.y);
				return 1;
			}
			if (_mat.at<uchar>(cur.y + 1, cur.x) == 255)
			{
				_p = cv::Point(cur.x, cur.y + 1);
				return 1;
			}
			if (_mat.at<uchar>(cur.y - 1, cur.x) == 255)
			{
				_p = cv::Point(cur.x, cur.y - 1);
				return 1;
			}
			stack_p.push(cv::Point(cur.x + 1, cur.y));
			stack_p.push(cv::Point(cur.x - 1, cur.y));
			stack_p.push(cv::Point(cur.x, cur.y + 1));
			stack_p.push(cv::Point(cur.x, cur.y - 1));
		}
		return 0;
	}

	void cal_can_clean_area(string filename)
	{
		std::cout << "cal can clean area start" << std::endl;
		Mat origin = cv::imread(filename, IMREAD_COLOR);
		Mat origin_clone = origin.clone();
		Mat mat_color[3];
		split(origin_clone, mat_color);

		Mat b = mat_color[0];
		Mat g = mat_color[1];
		Mat r = mat_color[2];

		Mat origin_refer = r.clone();
		Mat origin_robot = origin.clone();
		origin_refer.setTo(0);
		threshold(r, origin_refer, 128, 255, THRESH_BINARY);
		vector<vector<cv::Point>> contour_refer;
		findContours(origin_refer, contour_refer, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		cv::RotatedRect r_rect = minAreaRect(contour_refer[0]);
		cv::Rect refer_rect = r_rect.boundingRect();
		// refer_rect.width.pixels * pixel_size =refer_rect.height.pixels * pixel_size=1m in actual
		// pixel_size : m/pixels
		float pixel_size = (1.f / (float)refer_rect.width + 1.f / (float)refer_rect.height) / 2.f;
		set_meter_pixels(pixel_size);
		set_refer_pose(Eigen::Vector2i(r_rect.center.x, r_rect.center.y));
		origin_clone = g.clone();
		threshold(origin_clone, origin_clone, 140, 255, THRESH_BINARY);

		int dilate_size = (int)(ROBOT_R / pixel_size);
		dilate(origin_clone, origin_clone, cv::getStructuringElement(MORPH_RECT, cv::Size(dilate_size * 2, dilate_size * 2)));
		erode(origin_clone, origin_clone, cv::getStructuringElement(MORPH_RECT, cv::Size(dilate_size * 2, dilate_size * 2)));

		cv::Mat mat_fill = origin_clone;
		mat_fill = ~mat_fill;
		cv::Point p_clear;
		bool is_find = find_clear_point_in_mat(mat_fill, p_clear);
		if (!is_find)
		{
			cout << "can not find clear point!";
			return;
		}
		floodFill(mat_fill, p_clear, 200);
		cv::Mat mat_fill_outer = mat_fill.clone();
		threshold(mat_fill_outer, mat_fill_outer, 201, 255, CV_THRESH_BINARY);
		mat_fill = mat_fill - mat_fill_outer;
		int count = countNonZero(mat_fill);
		float area = count * pixel_size * pixel_size;
		m_can_clean_area = area;
		m_can_clean_mat = mat_fill.clone();
		m_cleaned_mat = mat_fill.clone();
		m_explored_mat = mat_fill.clone();

		std::cout << "cal can clean area start" << std::endl;
	}

private:
	Eigen::Vector2i m_refer_pose;
	float m_meter_pixels;
	float m_can_clean_area;
	Mat m_can_clean_mat;
	Mat m_cleaned_mat;
	Mat m_explored_mat;
};


int main(int argc, char const *argv[])
{
	DeviceObserver deviceObserver;
	deviceObserver.cal_can_clean_area(argv[1]);
	return 0;
}
