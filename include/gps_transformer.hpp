#ifndef INCLUDE_GPS_TRANSFORMER_HPP_
#define INCLUDE_GPS_TRANSFORMER_HPP_

#include <iostream>
#include <string>
#include <sensor_msgs/NavSatFix.h>
#include <visualization_msgs/Marker.h>

// GeographicLib
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>

void gnss_callback(const sensor_msgs::NavSatFixConstPtr &msg);

#endif  // INCLUDE_GPS_TRANSFORMER_HPP_
