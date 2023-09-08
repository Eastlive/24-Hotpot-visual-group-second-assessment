#ifndef NAHSOR__NAHSOR_DETECTOR_HPP
#define NAHSOR__NAHSOR_DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace nahsor
{
    class NahsorDetector
    {
    public:
        NahsorDetector()
        {
            rotation_center = cv::Point2f(0, 0);
            old_armor_center = cv::Point2f(0, 0);
            current_armor_center = cv::Point2f(0, 0);
            is_clockwise = 0;
            is_counterclockwise = 0;
        }
        ~NahsorDetector()
        {
        }

        void detect(cv::Mat &frame);

    private:
        cv::Mat preProcess(cv::Mat &frame);
        bool isArmor(std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy, size_t index);
        bool isR(double contourArea, const cv::Vec4i &hierarchy);

        /**
         * @brief 判断旋转方向
         *
         * @param old_armor_center 上一次迭代的装甲板中心
         * @param current_armor_center 当前帧的装甲板中心
         * @param rotation_center 旋转中心
         */
        void direction(cv::Point2f old_armor_center, cv::Point2f current_armor_center, cv::Point2f rotation_center);

        const std::vector<int> low_blue = {150, 0, 0};
        const std::vector<int> up_blue = {255, 130, 130};
        const int core_size = 3;
        const int erode_size = 2;
        const int dilate_size = 3;
        const double MIN_ARMOR_AREA = 1000;
        const double MAX_ARMOR_AREA = 1400;
        const double MAX_PARENT_AREA = 6000;
        const double MIN_R_AREA = 150;
        const double MAX_R_AREA = 250;

        cv::Point2f rotation_center;      // 旋转中心
        cv::Point2f old_armor_center;     // 上一次迭代的装甲板中心
        cv::Point2f current_armor_center; // 当前帧的装甲板中心
        int is_clockwise;                 // 顺时针旋转
        int is_counterclockwise;          // 逆时针旋转
    };
} // namespace nahsor

#endif // NAHSOR__NAHSOR_DETECTOR_HPP