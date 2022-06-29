    else if(publisherProxy->topicType == "control_msgs/JointControllerState")
    {
        control_msgs::JointControllerState msg;
        read__control_msgs__JointControllerState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "control_msgs/JointTolerance")
    {
        control_msgs::JointTolerance msg;
        read__control_msgs__JointTolerance(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "diagnostic_msgs/DiagnosticArray")
    {
        diagnostic_msgs::DiagnosticArray msg;
        read__diagnostic_msgs__DiagnosticArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "diagnostic_msgs/DiagnosticStatus")
    {
        diagnostic_msgs::DiagnosticStatus msg;
        read__diagnostic_msgs__DiagnosticStatus(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "diagnostic_msgs/KeyValue")
    {
        diagnostic_msgs::KeyValue msg;
        read__diagnostic_msgs__KeyValue(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/BoolParameter")
    {
        dynamic_reconfigure::BoolParameter msg;
        read__dynamic_reconfigure__BoolParameter(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/Config")
    {
        dynamic_reconfigure::Config msg;
        read__dynamic_reconfigure__Config(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/ConfigDescription")
    {
        dynamic_reconfigure::ConfigDescription msg;
        read__dynamic_reconfigure__ConfigDescription(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/DoubleParameter")
    {
        dynamic_reconfigure::DoubleParameter msg;
        read__dynamic_reconfigure__DoubleParameter(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/Group")
    {
        dynamic_reconfigure::Group msg;
        read__dynamic_reconfigure__Group(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/GroupState")
    {
        dynamic_reconfigure::GroupState msg;
        read__dynamic_reconfigure__GroupState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/IntParameter")
    {
        dynamic_reconfigure::IntParameter msg;
        read__dynamic_reconfigure__IntParameter(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/ParamDescription")
    {
        dynamic_reconfigure::ParamDescription msg;
        read__dynamic_reconfigure__ParamDescription(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/SensorLevels")
    {
        dynamic_reconfigure::SensorLevels msg;
        read__dynamic_reconfigure__SensorLevels(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "dynamic_reconfigure/StrParameter")
    {
        dynamic_reconfigure::StrParameter msg;
        read__dynamic_reconfigure__StrParameter(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/ContactState")
    {
        gazebo_msgs::ContactState msg;
        read__gazebo_msgs__ContactState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/ContactsState")
    {
        gazebo_msgs::ContactsState msg;
        read__gazebo_msgs__ContactsState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/LinkState")
    {
        gazebo_msgs::LinkState msg;
        read__gazebo_msgs__LinkState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/LinkStates")
    {
        gazebo_msgs::LinkStates msg;
        read__gazebo_msgs__LinkStates(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/ModelState")
    {
        gazebo_msgs::ModelState msg;
        read__gazebo_msgs__ModelState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/ModelStates")
    {
        gazebo_msgs::ModelStates msg;
        read__gazebo_msgs__ModelStates(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/ODEJointProperties")
    {
        gazebo_msgs::ODEJointProperties msg;
        read__gazebo_msgs__ODEJointProperties(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/ODEPhysics")
    {
        gazebo_msgs::ODEPhysics msg;
        read__gazebo_msgs__ODEPhysics(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "gazebo_msgs/WorldState")
    {
        gazebo_msgs::WorldState msg;
        read__gazebo_msgs__WorldState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Accel")
    {
        geometry_msgs::Accel msg;
        read__geometry_msgs__Accel(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/AccelStamped")
    {
        geometry_msgs::AccelStamped msg;
        read__geometry_msgs__AccelStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/AccelWithCovariance")
    {
        geometry_msgs::AccelWithCovariance msg;
        read__geometry_msgs__AccelWithCovariance(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/AccelWithCovarianceStamped")
    {
        geometry_msgs::AccelWithCovarianceStamped msg;
        read__geometry_msgs__AccelWithCovarianceStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Inertia")
    {
        geometry_msgs::Inertia msg;
        read__geometry_msgs__Inertia(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/InertiaStamped")
    {
        geometry_msgs::InertiaStamped msg;
        read__geometry_msgs__InertiaStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Point")
    {
        geometry_msgs::Point msg;
        read__geometry_msgs__Point(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Point32")
    {
        geometry_msgs::Point32 msg;
        read__geometry_msgs__Point32(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/PointStamped")
    {
        geometry_msgs::PointStamped msg;
        read__geometry_msgs__PointStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Polygon")
    {
        geometry_msgs::Polygon msg;
        read__geometry_msgs__Polygon(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/PolygonStamped")
    {
        geometry_msgs::PolygonStamped msg;
        read__geometry_msgs__PolygonStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Pose")
    {
        geometry_msgs::Pose msg;
        read__geometry_msgs__Pose(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Pose2D")
    {
        geometry_msgs::Pose2D msg;
        read__geometry_msgs__Pose2D(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/PoseArray")
    {
        geometry_msgs::PoseArray msg;
        read__geometry_msgs__PoseArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/PoseStamped")
    {
        geometry_msgs::PoseStamped msg;
        read__geometry_msgs__PoseStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/PoseWithCovariance")
    {
        geometry_msgs::PoseWithCovariance msg;
        read__geometry_msgs__PoseWithCovariance(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/PoseWithCovarianceStamped")
    {
        geometry_msgs::PoseWithCovarianceStamped msg;
        read__geometry_msgs__PoseWithCovarianceStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Quaternion")
    {
        geometry_msgs::Quaternion msg;
        read__geometry_msgs__Quaternion(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/QuaternionStamped")
    {
        geometry_msgs::QuaternionStamped msg;
        read__geometry_msgs__QuaternionStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Transform")
    {
        geometry_msgs::Transform msg;
        read__geometry_msgs__Transform(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/TransformStamped")
    {
        geometry_msgs::TransformStamped msg;
        read__geometry_msgs__TransformStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Twist")
    {
        geometry_msgs::Twist msg;
        read__geometry_msgs__Twist(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/TwistStamped")
    {
        geometry_msgs::TwistStamped msg;
        read__geometry_msgs__TwistStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/TwistWithCovariance")
    {
        geometry_msgs::TwistWithCovariance msg;
        read__geometry_msgs__TwistWithCovariance(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/TwistWithCovarianceStamped")
    {
        geometry_msgs::TwistWithCovarianceStamped msg;
        read__geometry_msgs__TwistWithCovarianceStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Vector3")
    {
        geometry_msgs::Vector3 msg;
        read__geometry_msgs__Vector3(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Vector3Stamped")
    {
        geometry_msgs::Vector3Stamped msg;
        read__geometry_msgs__Vector3Stamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/Wrench")
    {
        geometry_msgs::Wrench msg;
        read__geometry_msgs__Wrench(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "geometry_msgs/WrenchStamped")
    {
        geometry_msgs::WrenchStamped msg;
        read__geometry_msgs__WrenchStamped(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "map_msgs/OccupancyGridUpdate")
    {
        map_msgs::OccupancyGridUpdate msg;
        read__map_msgs__OccupancyGridUpdate(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "map_msgs/PointCloud2Update")
    {
        map_msgs::PointCloud2Update msg;
        read__map_msgs__PointCloud2Update(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "map_msgs/ProjectedMap")
    {
        map_msgs::ProjectedMap msg;
        read__map_msgs__ProjectedMap(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "map_msgs/ProjectedMapInfo")
    {
        map_msgs::ProjectedMapInfo msg;
        read__map_msgs__ProjectedMapInfo(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "nav_msgs/GridCells")
    {
        nav_msgs::GridCells msg;
        read__nav_msgs__GridCells(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "nav_msgs/MapMetaData")
    {
        nav_msgs::MapMetaData msg;
        read__nav_msgs__MapMetaData(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "nav_msgs/OccupancyGrid")
    {
        nav_msgs::OccupancyGrid msg;
        read__nav_msgs__OccupancyGrid(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "nav_msgs/Odometry")
    {
        nav_msgs::Odometry msg;
        read__nav_msgs__Odometry(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "nav_msgs/Path")
    {
        nav_msgs::Path msg;
        read__nav_msgs__Path(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "roscpp/Logger")
    {
        roscpp::Logger msg;
        read__roscpp__Logger(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "rosgraph_msgs/Clock")
    {
        rosgraph_msgs::Clock msg;
        read__rosgraph_msgs__Clock(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "rosgraph_msgs/Log")
    {
        rosgraph_msgs::Log msg;
        read__rosgraph_msgs__Log(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "rosgraph_msgs/TopicStatistics")
    {
        rosgraph_msgs::TopicStatistics msg;
        read__rosgraph_msgs__TopicStatistics(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/CameraInfo")
    {
        sensor_msgs::CameraInfo msg;
        read__sensor_msgs__CameraInfo(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/ChannelFloat32")
    {
        sensor_msgs::ChannelFloat32 msg;
        read__sensor_msgs__ChannelFloat32(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/CompressedImage")
    {
        sensor_msgs::CompressedImage msg;
        read__sensor_msgs__CompressedImage(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/FluidPressure")
    {
        sensor_msgs::FluidPressure msg;
        read__sensor_msgs__FluidPressure(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/Illuminance")
    {
        sensor_msgs::Illuminance msg;
        read__sensor_msgs__Illuminance(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/Image")
    {
        sensor_msgs::Image msg;
        read__sensor_msgs__Image(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/Imu")
    {
        sensor_msgs::Imu msg;
        read__sensor_msgs__Imu(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/JointState")
    {
        sensor_msgs::JointState msg;
        read__sensor_msgs__JointState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/Joy")
    {
        sensor_msgs::Joy msg;
        read__sensor_msgs__Joy(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/JoyFeedback")
    {
        sensor_msgs::JoyFeedback msg;
        read__sensor_msgs__JoyFeedback(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/JoyFeedbackArray")
    {
        sensor_msgs::JoyFeedbackArray msg;
        read__sensor_msgs__JoyFeedbackArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/LaserEcho")
    {
        sensor_msgs::LaserEcho msg;
        read__sensor_msgs__LaserEcho(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/LaserScan")
    {
        sensor_msgs::LaserScan msg;
        read__sensor_msgs__LaserScan(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/MagneticField")
    {
        sensor_msgs::MagneticField msg;
        read__sensor_msgs__MagneticField(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/MultiDOFJointState")
    {
        sensor_msgs::MultiDOFJointState msg;
        read__sensor_msgs__MultiDOFJointState(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/MultiEchoLaserScan")
    {
        sensor_msgs::MultiEchoLaserScan msg;
        read__sensor_msgs__MultiEchoLaserScan(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/NavSatFix")
    {
        sensor_msgs::NavSatFix msg;
        read__sensor_msgs__NavSatFix(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/NavSatStatus")
    {
        sensor_msgs::NavSatStatus msg;
        read__sensor_msgs__NavSatStatus(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/PointCloud")
    {
        sensor_msgs::PointCloud msg;
        read__sensor_msgs__PointCloud(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/PointCloud2")
    {
        sensor_msgs::PointCloud2 msg;
        read__sensor_msgs__PointCloud2(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/PointField")
    {
        sensor_msgs::PointField msg;
        read__sensor_msgs__PointField(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/Range")
    {
        sensor_msgs::Range msg;
        read__sensor_msgs__Range(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/RegionOfInterest")
    {
        sensor_msgs::RegionOfInterest msg;
        read__sensor_msgs__RegionOfInterest(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/RelativeHumidity")
    {
        sensor_msgs::RelativeHumidity msg;
        read__sensor_msgs__RelativeHumidity(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/Temperature")
    {
        sensor_msgs::Temperature msg;
        read__sensor_msgs__Temperature(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "sensor_msgs/TimeReference")
    {
        sensor_msgs::TimeReference msg;
        read__sensor_msgs__TimeReference(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "shape_msgs/Mesh")
    {
        shape_msgs::Mesh msg;
        read__shape_msgs__Mesh(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "shape_msgs/MeshTriangle")
    {
        shape_msgs::MeshTriangle msg;
        read__shape_msgs__MeshTriangle(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "shape_msgs/Plane")
    {
        shape_msgs::Plane msg;
        read__shape_msgs__Plane(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "shape_msgs/SolidPrimitive")
    {
        shape_msgs::SolidPrimitive msg;
        read__shape_msgs__SolidPrimitive(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "smach_msgs/SmachContainerInitialStatusCmd")
    {
        smach_msgs::SmachContainerInitialStatusCmd msg;
        read__smach_msgs__SmachContainerInitialStatusCmd(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "smach_msgs/SmachContainerStatus")
    {
        smach_msgs::SmachContainerStatus msg;
        read__smach_msgs__SmachContainerStatus(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "smach_msgs/SmachContainerStructure")
    {
        smach_msgs::SmachContainerStructure msg;
        read__smach_msgs__SmachContainerStructure(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Bool")
    {
        std_msgs::Bool msg;
        read__std_msgs__Bool(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Byte")
    {
        std_msgs::Byte msg;
        read__std_msgs__Byte(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/ByteMultiArray")
    {
        std_msgs::ByteMultiArray msg;
        read__std_msgs__ByteMultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Char")
    {
        std_msgs::Char msg;
        read__std_msgs__Char(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/ColorRGBA")
    {
        std_msgs::ColorRGBA msg;
        read__std_msgs__ColorRGBA(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Duration")
    {
        std_msgs::Duration msg;
        read__std_msgs__Duration(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Empty")
    {
        std_msgs::Empty msg;
        read__std_msgs__Empty(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Float32")
    {
        std_msgs::Float32 msg;
        read__std_msgs__Float32(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Float32MultiArray")
    {
        std_msgs::Float32MultiArray msg;
        read__std_msgs__Float32MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Float64")
    {
        std_msgs::Float64 msg;
        read__std_msgs__Float64(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Float64MultiArray")
    {
        std_msgs::Float64MultiArray msg;
        read__std_msgs__Float64MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Header")
    {
        std_msgs::Header msg;
        read__std_msgs__Header(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int16")
    {
        std_msgs::Int16 msg;
        read__std_msgs__Int16(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int16MultiArray")
    {
        std_msgs::Int16MultiArray msg;
        read__std_msgs__Int16MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int32")
    {
        std_msgs::Int32 msg;
        read__std_msgs__Int32(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int32MultiArray")
    {
        std_msgs::Int32MultiArray msg;
        read__std_msgs__Int32MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int64")
    {
        std_msgs::Int64 msg;
        read__std_msgs__Int64(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int64MultiArray")
    {
        std_msgs::Int64MultiArray msg;
        read__std_msgs__Int64MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int8")
    {
        std_msgs::Int8 msg;
        read__std_msgs__Int8(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Int8MultiArray")
    {
        std_msgs::Int8MultiArray msg;
        read__std_msgs__Int8MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/MultiArrayDimension")
    {
        std_msgs::MultiArrayDimension msg;
        read__std_msgs__MultiArrayDimension(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/MultiArrayLayout")
    {
        std_msgs::MultiArrayLayout msg;
        read__std_msgs__MultiArrayLayout(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/String")
    {
        std_msgs::String msg;
        read__std_msgs__String(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/Time")
    {
        std_msgs::Time msg;
        read__std_msgs__Time(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt16")
    {
        std_msgs::UInt16 msg;
        read__std_msgs__UInt16(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt16MultiArray")
    {
        std_msgs::UInt16MultiArray msg;
        read__std_msgs__UInt16MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt32")
    {
        std_msgs::UInt32 msg;
        read__std_msgs__UInt32(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt32MultiArray")
    {
        std_msgs::UInt32MultiArray msg;
        read__std_msgs__UInt32MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt64")
    {
        std_msgs::UInt64 msg;
        read__std_msgs__UInt64(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt64MultiArray")
    {
        std_msgs::UInt64MultiArray msg;
        read__std_msgs__UInt64MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt8")
    {
        std_msgs::UInt8 msg;
        read__std_msgs__UInt8(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "std_msgs/UInt8MultiArray")
    {
        std_msgs::UInt8MultiArray msg;
        read__std_msgs__UInt8MultiArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "tf/tfMessage")
    {
        tf::tfMessage msg;
        read__tf__tfMessage(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "tf2_msgs/TF2Error")
    {
        tf2_msgs::TF2Error msg;
        read__tf2_msgs__TF2Error(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "tf2_msgs/TFMessage")
    {
        tf2_msgs::TFMessage msg;
        read__tf2_msgs__TFMessage(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "trajectory_msgs/JointTrajectory")
    {
        trajectory_msgs::JointTrajectory msg;
        read__trajectory_msgs__JointTrajectory(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "trajectory_msgs/JointTrajectoryPoint")
    {
        trajectory_msgs::JointTrajectoryPoint msg;
        read__trajectory_msgs__JointTrajectoryPoint(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "trajectory_msgs/MultiDOFJointTrajectory")
    {
        trajectory_msgs::MultiDOFJointTrajectory msg;
        read__trajectory_msgs__MultiDOFJointTrajectory(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "trajectory_msgs/MultiDOFJointTrajectoryPoint")
    {
        trajectory_msgs::MultiDOFJointTrajectoryPoint msg;
        read__trajectory_msgs__MultiDOFJointTrajectoryPoint(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/ImageMarker")
    {
        visualization_msgs::ImageMarker msg;
        read__visualization_msgs__ImageMarker(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/InteractiveMarker")
    {
        visualization_msgs::InteractiveMarker msg;
        read__visualization_msgs__InteractiveMarker(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/InteractiveMarkerControl")
    {
        visualization_msgs::InteractiveMarkerControl msg;
        read__visualization_msgs__InteractiveMarkerControl(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/InteractiveMarkerFeedback")
    {
        visualization_msgs::InteractiveMarkerFeedback msg;
        read__visualization_msgs__InteractiveMarkerFeedback(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/InteractiveMarkerInit")
    {
        visualization_msgs::InteractiveMarkerInit msg;
        read__visualization_msgs__InteractiveMarkerInit(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/InteractiveMarkerPose")
    {
        visualization_msgs::InteractiveMarkerPose msg;
        read__visualization_msgs__InteractiveMarkerPose(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/InteractiveMarkerUpdate")
    {
        visualization_msgs::InteractiveMarkerUpdate msg;
        read__visualization_msgs__InteractiveMarkerUpdate(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/Marker")
    {
        visualization_msgs::Marker msg;
        read__visualization_msgs__Marker(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/MarkerArray")
    {
        visualization_msgs::MarkerArray msg;
        read__visualization_msgs__MarkerArray(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
    else if(publisherProxy->topicType == "visualization_msgs/MenuEntry")
    {
        visualization_msgs::MenuEntry msg;
        read__visualization_msgs__MenuEntry(in->_.stackID, &msg, &(publisherProxy->rd_opt));
        publisherProxy->publisher.publish(msg);
    }
