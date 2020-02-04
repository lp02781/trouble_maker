#!/bin/sh

# check values
if [ -z "$SOURCE_PATH" ]; then
    echo "[ERROR] Plsease set SOURCE_PATH"
    exit 1
fi
if [ -z "$BUILD_PATH" ]; then
    echo "[ERROR] Plsease set BUILD_PATH"
    exit 1
fi

# install package
echo "Please input sudo password for install rviz plugin."
sudo apt install -y ros-kinetic-jsk-rviz-plugins

# PATH settings
FILE_PATH=./files/
DESCRIPTION_PATH=${SOURCE_PATH}/description/
WORLD_PATH=${SOURCE_PATH}/description/media/astrobee_iss/
MODEL_PATH=${SOURCE_PATH}/description/description/urdf/
SIM_CONF_PATH=${SOURCE_PATH}/astrobee/config/simulation/simulation.config
CH_CONF_PATH=${SOURCE_PATH}/astrobee/config/mobility/choreographer.config
ZONES_PATH=${SOURCE_PATH}/astrobee/resources/zones/
RVIZ_PATH=${SOURCE_PATH}/astrobee/resources/rviz/
LAUNCH_PATH=${SOURCE_PATH}/astrobee/launch/

# world files
cp ${FILE_PATH}/meshes/* $WORLD_PATH/meshes/
cp ${FILE_PATH}/media/materials/textures/* $WORLD_PATH/media/materials/textures/
cp ${FILE_PATH}/urdf/model.urdf $WORLD_PATH/urdf/

# models
cp ${FILE_PATH}/urdf/sensor* $MODEL_PATH

# settings
cp ${FILE_PATH}/config/simulation.config $SIM_CONF_PATH
cp ${FILE_PATH}/config/choreographer.config $CH_CONF_PATH

# zones
cp ${FILE_PATH}/zones/iss.bin $ZONES_PATH

# rviz
cp ${FILE_PATH}/rviz/iss.rviz $RVIZ_PATH

# launch
cp ${FILE_PATH}/launch/sim.launch $LAUNCH_PATH/

# simbolic link for gazebo
mkdir -p ~/.gazebo/models/ > /dev/null 2>&1
ln -sf $WORLD_PATH ~/.gazebo/models/

# plugin
cp ${FILE_PATH}/src/gazebo_model_plugin_laser.cc $SOURCE_PATH/simulation/src/gazebo_model_plugin_laser/

# build
echo "Build start"
cd ${BUILD_PATH}
make -j4

exit 0
