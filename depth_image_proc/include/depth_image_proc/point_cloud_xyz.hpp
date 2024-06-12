// Copyright (c) 2008, Willow Garage, Inc.
// All rights reserved.
//
// Software License Agreement (BSD License 2.0)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//  * Neither the name of the Willow Garage nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
#ifndef DEPTH_IMAGE_PROC__POINT_CLOUD_XYZ_HPP_
#define DEPTH_IMAGE_PROC__POINT_CLOUD_XYZ_HPP_

#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <image_geometry/pinhole_camera_model.h>
#include <depth_image_proc/conversions.hpp>
#include <depth_image_proc/visibility.h>
#include <rcl_interfaces/msg/set_parameters_result.hpp>

#include <sensor_msgs/point_cloud2_iterator.hpp>
#include <memory>

namespace depth_image_proc
{

namespace enc = sensor_msgs::image_encodings;

class PointCloudXyzNode : public rclcpp::Node
{
public:
  DEPTH_IMAGE_PROC_PUBLIC PointCloudXyzNode(const rclcpp::NodeOptions & options);

private:
  using PointCloud2 = sensor_msgs::msg::PointCloud2;
  using Image = sensor_msgs::msg::Image;
  using CameraInfo = sensor_msgs::msg::CameraInfo;

  // Subscriptions
  image_transport::CameraSubscriber sub_depth_;
  int queue_size_;
  bool stream_pointcloud_;
  double clip_distance_;
  int min_x_;
  int max_x_;
  int min_y_;
  int max_y_;

  // Publications
  rclcpp::Publisher<PointCloud2>::SharedPtr pub_point_cloud_;
  OnSetParametersCallbackHandle::SharedPtr callback_handle_;

  image_geometry::PinholeCameraModel model_;

  rcl_interfaces::msg::SetParametersResult parametersCallback(const std::vector<rclcpp::Parameter> &);

  void enable_streaming();
  void disable_streaming();

  void depthCb(
    const Image::ConstSharedPtr & depth_msg,
    const CameraInfo::ConstSharedPtr & info_msg);

  rclcpp::Logger logger_ = rclcpp::get_logger("PointCloudXyzNode");
};

}  // namespace depth_image_proc

#endif  // DEPTH_IMAGE_PROC__POINT_CLOUD_XYZ_HPP_
