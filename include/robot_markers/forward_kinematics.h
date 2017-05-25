#ifndef _ROBOT_MARKERS_FORWARD_KINEMATICS_H_
#define _ROBOT_MARKERS_FORWARD_KINEMATICS_H_

#include <string>
#include <vector>

#include "geometry_msgs/TransformStamped.h"
#include "kdl/frames.hpp"
#include "kdl/segment.hpp"
#include "kdl/tree.hpp"
#include "urdf/model.h"

namespace robot_markers {
class SegmentPair {
 public:
  SegmentPair(const KDL::Segment& p_segment, const std::string& p_root,
              const std::string& p_tip);

  KDL::Segment segment;
  std::string root, tip;
};

class ForwardKinematics {
 public:
  explicit ForwardKinematics(const urdf::Model& model);
  void Init();
  void GetTransforms(
      const std::map<std::string, double>& joint_positions,
      std::vector<geometry_msgs::TransformStamped>* transforms) const;

 private:
  urdf::Model model_;
  KDL::Tree tree_;
  std::map<std::string, SegmentPair> segments_;
  std::map<std::string, SegmentPair> segments_fixed_;

  void AddChildren(const KDL::SegmentMap::const_iterator segment);
};
}  // namespace robot_markers

#endif  // _ROBOT_MARKERS_FORWARD_KINEMATICS_H_
