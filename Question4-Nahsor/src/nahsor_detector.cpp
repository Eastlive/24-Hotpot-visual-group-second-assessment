#include "nahsor/nahsor_detector.hpp"

namespace nahsor
{
    cv::Mat NahsorDetector::preProcess(cv::Mat &frame)
    {
        // 二值化和颜色提取
        cv::Mat binary;
        cv::inRange(frame, low_blue, up_blue, binary); // 蓝色

        // 腐蚀和膨胀
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(core_size, core_size));
        cv::Mat erode_kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(erode_size, erode_size));
        cv::Mat dilate_kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(dilate_size, dilate_size));

        cv::dilate(binary, binary, kernel);
        cv::erode(binary, binary, erode_kernel);
        cv::dilate(binary, binary, dilate_kernel);

        cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, kernel);
        cv::morphologyEx(binary, binary, cv::MORPH_OPEN, kernel);

        return binary;
    }
    void NahsorDetector::detect(cv::Mat &frame)
    {
        cv::Mat binary = preProcess(frame);

        // 轮廓检测
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        // 装甲板和R
        std::vector<cv::RotatedRect> armors;
        std::vector<cv::RotatedRect> rRects;

        // 筛选待击打装甲板
        for (size_t i = 0; i < contours.size(); i++)
        {
            double area = cv::contourArea(contours[i]);
            if (isArmor(contours, hierarchy, i))
            {
                // printf("area: %f\n", area);
                cv::RotatedRect armorRect = cv::minAreaRect(cv::Mat(contours[i]));
                armors.push_back(armorRect);
            }
            if (isR(area, hierarchy[i]))
            {
                // printf("area: %f\n", area);
                cv::RotatedRect armorRect = cv::minAreaRect(cv::Mat(contours[i]));
                rRects.push_back(armorRect);
            }
        }
        old_armor_center = current_armor_center;

        // 绘制装甲板和R
        for (const auto &rect : armors)
        {
            cv::Point2f rect_points[4];
            rect.points(rect_points);
            for (int j = 0; j < 4; j++)
            {
                cv::line(frame, rect_points[j], rect_points[(j + 1) % 4], cv::Scalar(0, 255, 0), 5);
            }
            cv::line(frame, rect_points[0], rect_points[2], cv::Scalar(0, 255, 0), 3);
            cv::line(frame, rect_points[1], rect_points[3], cv::Scalar(0, 255, 0), 3);
            cv::Point2f center = rect.center;
            current_armor_center = center;
            printf("center: %f, %f\n", center.x, center.y);
        }
        for (const auto &rect : rRects)
        {
            // printf("rRects\n");
            cv::Point2f center = rect.center;
            cv::circle(frame, center, 5, cv::Scalar(0, 0, 255), 2);
            rotation_center = center;
        }
        printf("old_armor_center: %f, %f\n", old_armor_center.x, old_armor_center.y);
        printf("current_armor_center: %f, %f\n", current_armor_center.x, current_armor_center.y);
        printf("rotation_center: %f, %f\n", rotation_center.x, rotation_center.y);
        if (old_armor_center.x != 0 && old_armor_center.y != 0 && current_armor_center.x != 0 && current_armor_center.y != 0 && rotation_center.x != 0 && rotation_center.y != 0)
        {
            direction(old_armor_center, current_armor_center, rotation_center);
        }
        cv::putText(frame, (is_clockwise > is_counterclockwise) ? "Clockwise" : "Counterclockwise", cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
    bool NahsorDetector::isArmor(std::vector<std::vector<cv::Point>> &contours, const std::vector<cv::Vec4i> &hierarchy, size_t index)
    {
        // 面积
        double contourArea = cv::contourArea(contours[index]);
        if (contourArea <= MIN_ARMOR_AREA || contourArea >= MAX_ARMOR_AREA)
            return false;

        // 不含子轮廓
        if (hierarchy[index][2] != -1)
            return false;

        // 含父轮廓
        if (hierarchy[index][3] == -1)
            return false;

        // 父轮廓不能再有父轮廓
        cv::Vec4i parent_hierarchy = hierarchy[hierarchy[index][3]];
        if (parent_hierarchy[3] != -1 || cv::contourArea(contours[hierarchy[index][3]]) > MAX_PARENT_AREA)
        {
            return false;
        }

        return true;
    }
    bool NahsorDetector::isR(double contourArea, const cv::Vec4i &hierarchy)
    {
        return contourArea > MIN_R_AREA && contourArea < MAX_R_AREA && hierarchy[3] == -1;
    }
    void NahsorDetector::direction(cv::Point2f old_armor_center, cv::Point2f current_armor_center, cv::Point2f rotation_center)
    {
        cv::Point2f old_vector = old_armor_center - rotation_center;
        cv::Point2f current_vector = current_armor_center - rotation_center;

        float cross_product_z = old_vector.x * current_vector.y - old_vector.y * current_vector.x;

        if (cross_product_z > 0)
        {
            is_clockwise++;
        }
        else
        {
            is_counterclockwise++;
        }
        if (is_clockwise > is_counterclockwise)
        {
            printf("顺时针旋转\n");
        }
        else
        {
            printf("逆时针旋转\n");
        }
    }

} // namespace nahsor