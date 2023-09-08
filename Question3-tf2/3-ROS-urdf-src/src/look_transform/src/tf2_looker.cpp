#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

class Looker : public rclcpp::Node
{
public:
  Looker() : Node("looker")
  {
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    timer_ = create_wall_timer(std::chrono::milliseconds(500), std::bind(&Looker::timer_callback, this));
  }

private:
  void timer_callback()
  {
    geometry_msgs::msg::TransformStamped transform_stamped;
    try
    {
      transform_stamped = tf_buffer_->lookupTransform("camera_optical_link", "gimbal_odom", tf2::TimePointZero);
    }
    catch (tf2::TransformException& ex)
    {
      RCLCPP_WARN(this->get_logger(), "%s", ex.what());
      return;
    }

    RCLCPP_INFO(this->get_logger(), "x: %f, y: %f, z: %f", transform_stamped.transform.translation.x,
                transform_stamped.transform.translation.y, transform_stamped.transform.translation.z);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Looker>());
  rclcpp::shutdown();
  return 0;
}
