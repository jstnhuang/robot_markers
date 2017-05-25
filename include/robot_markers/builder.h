#ifndef _ROBOT_MARKERS_BUILDER_H_
#define _ROBOT_MARKERS_BUILDER_H_

#include <map>
#include <string>

#include "geometry_msgs/Pose.h"
#include "ros/duration.h"
#include "ros/time.h"
#include "std_msgs/ColorRGBA.h"
#include "transform_graph/transform_graph.h"
#include "urdf/model.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"

#include "robot_markers/forward_kinematics.h"

namespace robot_markers {
// Builder creates a visualization of the robot given the URDF model.
//
// You can either get the visualization as a visualization_msgs::MarkerArray or
// as a visualization_msgs::InteractiveMarker.
class Builder {
 public:
  explicit Builder(const urdf::Model& model);

  // Call Init() once before using the builder.
  // This does NOT set any marker parameters (color, pose, etc.).
  void Init();

  void SetJointPositions(const std::map<std::string, double> joint_positions);

  void SetFrameId(const std::string& frame_id);
  void SetTime(const ros::Time& stamp);
  void SetNamespace(const std::string& ns);
  void SetPose(const geometry_msgs::Pose& pose);
  // Set to 0, 0, 0, 0 to use the mesh colors if available.
  void SetColor(float r, float g, float b, float a);
  void SetLifetime(const ros::Duration& lifetime);
  void SetFrameLocked(bool frame_locked);

  // Builds a visualization of the robot model as a marker array.
  void Build(visualization_msgs::MarkerArray* marker_array);

 private:
  // Sets everything in the marker except the pose.
  void BuildMarker(const urdf::Link& link, int id,
                   visualization_msgs::Marker* output);
  std::string NodeName(const std::string& name);

  urdf::Model model_;
  ForwardKinematics fk_;
  transform_graph::Graph tf_graph_;

  std::map<std::string, double> joint_positions_;

  // Marker fields
  std::string frame_id_;
  ros::Time stamp_;
  std::string ns_;
  geometry_msgs::Pose pose_;
  std_msgs::ColorRGBA color_;
  ros::Duration lifetime_;
  bool frame_locked_;
};
}  // namespace robot_markers

#endif  // _ROBOT_MARKERS_BUILDER_H_
