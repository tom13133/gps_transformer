# gps_transformer
The package is used to transform GPS information from WGS84 coordinates to local cartesian coordinates.  

## Requirements
1. GeographicLib  

* Installation of GeographicLib: https://hackmd.io/TM7Zv75zTr-RhO0DuQQxKQ  

## Nodes
1. Node **gps_transformer_node**  

## 1. Node gps_transformer_node

### (a) Subscribed Topics
#### (i) rtk_fix (sensor_msgs/NavSatFix)
GPS position fix reported by the device.  

### (b) Published Topics
#### (i) gps_marker (visualization_msgs/Marker)
GPS position in local cartesian coordinates. The origin is set to be the first subscribed GPS position.  

### (c) Getting Started
```
roscore
rosrun gps_transformer gps_transformer_node
```


* Result:  
Red lines: GPS trajectory  
<img src="https://github.com/tom13133/gps_transformer/blob/master/figures/result.png" width="800">
