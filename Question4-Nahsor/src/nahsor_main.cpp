#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "nahsor/nahsor_detector.hpp"

#include <memory>
#include <iostream>
#include <chrono>

int main()
{
    // 打开视频文件
    cv::VideoCapture cap("../source/nahsor.mp4");
    if (!cap.isOpened())
    {
        printf("nahsor.mp4 not found\n");
        return -1;
    }
    
    // 定义保存的视频文件名
    std::string filename = "output.avi";

    // 获取帧率
    double fps = cap.get(cv::CAP_PROP_FPS);

    // 定义视频文件的大小
    cv::Size size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), 
                  static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    // 初始化VideoWriter对象 
    // 注意: 选择正确的编码器 FOURCC 和文件格式以确保保存成功
    // 这里我们使用DIVX编码器保存为AVI格式。您可能需要根据系统或需求进行调整
    cv::VideoWriter writer(filename, cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size, true);

    if (!writer.isOpened()) {
        std::cerr << "Error initializing video writer" << std::endl;
        return -1;
    }


    // 创建NahsorDetector对象
    std::unique_ptr<nahsor::NahsorDetector> nahsor = std::make_unique<nahsor::NahsorDetector>();

    // 读取视频帧
    while (true)
    {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        // 记录开始时间点
        auto start_time = std::chrono::high_resolution_clock::now();

        nahsor->detect(frame);

        // 记录结束时间点
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "主要运算模块耗时: " << duration.count() << "ms" << std::endl;
        cv::putText(frame, "Time-consuming: " + std::to_string(duration.count()) + "ms", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);

        cv::imshow("nahsor", frame);
        writer.write(frame);

        char key = cv::waitKey(1);
        // 按q退出
        if (key == 'q')
        {
            break;
        }
    }

    // 释放资源
    cap.release();
    writer.release();
    cv::destroyAllWindows();

    return 0;
}