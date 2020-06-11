#include <iostream>
#include <sstream>
#include <string>
#include <gps_transformer.hpp>
#include <ros/package.h>
#include <ros/ros.h>

double lat_origin, lon_origin, alt_origin;
bool first_frame = true;;
GeographicLib::Geocentric earth(GeographicLib::Constants::WGS84_a(),
                                GeographicLib::Constants::WGS84_f());
GeographicLib::LocalCartesian proj_geo;

ros::Publisher pub_marker;
visualization_msgs::Marker line_strip;

void gnss_callback(const sensor_msgs::NavSatFixConstPtr &msg) {
  if (first_frame) {
    lat_origin = msg->latitude;
    lon_origin = msg->longitude;
    alt_origin = msg->altitude;
    proj_geo = GeographicLib::LocalCartesian(lat_origin,
                                             lon_origin,
                                             alt_origin,
                                             earth);
    first_frame = false;
  }

  double x, y, z;
  // Warning: if the measurement of altitude is wrong,
  // then the result of projection will be wrong.
  proj_geo.Forward(msg->latitude, msg->longitude, msg->altitude, x, y, z);

  geometry_msgs::Point p;
  p.x = x;
  p.y = y;
  p.z = z;

  std::cout << "Status: " << static_cast<int>(msg->status.status) << std::endl;
  std::cout << "(latitude, longitude, altitude)(deg, m) => (x, y, z)(m) = ("
            << std::to_string(msg->latitude) << ", "
            << std::to_string(msg->longitude) << ", "
            << std::to_string(msg->altitude) << ") => ("
            << x << ", "
            << y << ", "
            << z << ")" << std::endl;

  line_strip.points.push_back(p);
  if (line_strip.points.size() > 10000)
    line_strip.points.clear();

  pub_marker.publish(line_strip);

  return;
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "gps_transformer_node");
  ros::NodeHandle nh;

  ros::Subscriber gnss_sub = nh.subscribe("rtk_fix", 100000, gnss_callback);
  pub_marker = nh.advertise<visualization_msgs::Marker>("/gps_marker", 1, true);

  line_strip.header.frame_id = "/map";
  line_strip.ns = "linestrip";
  line_strip.action = visualization_msgs::Marker::ADD;
  line_strip.pose.orientation.w = 1.0;
  line_strip.id = 1;
  line_strip.type = visualization_msgs::Marker::LINE_STRIP;

  line_strip.scale.x = 0.5;
  line_strip.color.r = 1.0;
  line_strip.color.a = 1.0;


  ros::spin();
}
