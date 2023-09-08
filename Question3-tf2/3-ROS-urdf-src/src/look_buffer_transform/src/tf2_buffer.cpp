#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"


class BufferLooker : public rclcpp::Node
{
public:
  BufferLooker() : Node("buffer_looker")
  {
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    init_point_stamped();

    timer_ = create_wall_timer(std::chrono::milliseconds(500), std::bind(&BufferLooker::timer_callback, this));
  }

private:
  void init_point_stamped()
  {
    point_stamped_.header.frame_id = "camera_optical_link";
    point_stamped_.header.stamp = get_clock()->now();
    point_stamped_.point.x = 3.0;
    point_stamped_.point.y = 4.0;
    point_stamped_.point.z = 5.0;
  }
  void timer_callback()
  {
    geometry_msgs::msg::PointStamped point_1, piont_2;
    try
    {
        tf_buffer_->transform(point_stamped_, point_1, "gimbal_odom");
        tf_buffer_->transform(point_1, piont_2, "camera_optical_link");
    }
    catch (tf2::TransformException& ex)
    {
      RCLCPP_WARN(this->get_logger(), "%s", ex.what());
      return;
    }

    RCLCPP_INFO(this->get_logger(), "x: %f, y: %f, z: %f", piont_2.point.x,
                piont_2.point.y, piont_2.point.z);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  geometry_msgs::msg::PointStamped point_stamped_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BufferLooker>());
  rclcpp::shutdown();
  return 0;
}
