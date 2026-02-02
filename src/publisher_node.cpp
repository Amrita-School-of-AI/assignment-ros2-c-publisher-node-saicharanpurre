#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/*
 * TODO: Create a Class named 'PublisherNode' that inherits from rclcpp::Node.
 * Requirements:
 * 1. The constructor should name the node "publisher_node".
 * 2. Create a publisher to topic "/counter" with message type std_msgs::msg::String.
 * 3. Create a timer that triggers every 500ms.
 * 4. The timer callback should:
 * - Increment a counter (starting from 0)
 * - Create a message with format "Count: X" where X is the counter
 * - Publish the message
 * - Log using RCLCPP_INFO: "Publishing: 'Count: X'"
 */

class PublisherNode : public rclcpp::Node
{
public:
    PublisherNode()
        : Node("publisher_node"), count_(0)
    {
        // TODO: Create the publisher here
        publisher_ = this->create_publisher<std_msgs::msg::String>("/counter", 10);

        // TODO: Initialize the timer here
        timer_ = this->create_wall_timer(
            500ms, std::bind(&PublisherNode::timer_callback, this));
    }

private:
    // TODO: Define the timer_callback function here
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Count: " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}