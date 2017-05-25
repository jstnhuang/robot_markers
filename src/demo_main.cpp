#include <map>
#include <string>

#include "geometry_msgs/Pose.h"
#include "robot_markers/builder.h"
#include "ros/ros.h"
#include "urdf/model.h"
#include "visualization_msgs/MarkerArray.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "robot_markers_demo");
  ros::NodeHandle nh;
  ros::Publisher marker_arr_pub =
      nh.advertise<visualization_msgs::MarkerArray>("robot", 100);
  ros::Duration(0.5).sleep();

  urdf::Model model;
  model.initParam("robot_description");

  robot_markers::Builder builder(model);
  builder.Init();

  // Robot 1: Default configuration.
  visualization_msgs::MarkerArray robot1;
  builder.SetNamespace("robot");
  builder.SetFrameId("base_link");
  ros::Time now = ros::Time::now();
  builder.SetTime(ros::Time::now());
  builder.Build(&robot1);
  marker_arr_pub.publish(robot1);

  // Robot 2: Different pose and right arm panned slightly outward.
  visualization_msgs::MarkerArray robot2;
  builder.SetNamespace("robot2");

  std::map<std::string, double> joint_positions;
  joint_positions["torso_lift_joint"] = 0.1;
  joint_positions["head_tilt_joint"] = 0.5;
  builder.SetJointPositions(joint_positions);

  geometry_msgs::Pose pose;
  pose.position.y = 1;
  pose.orientation.w = 0.92387953;
  pose.orientation.z = -0.38268343;
  builder.SetPose(pose);
  builder.Build(&robot2);
  marker_arr_pub.publish(robot2);

  ros::Duration(0.5).sleep();

  return 0;
}
