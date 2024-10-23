ARG TAG=jammy
FROM ubuntu:${TAG}

SHELL ["/bin/bash", "-c"]

ENV DEBIAN_FRONTEND noninteractive

USER root

ARG WORKSPACE_DIR=/opt/noether

# Add ROS2 sources and install ROS infrastructure tools; cache mount to cache downloaded packages
# Bind mount the source directory so as not to unnecessarily copy source code into the docker image
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=bind,target=${WORKSPACE_DIR}/src/noether \
  rm -f /etc/apt/apt.conf.d/docker-clean \
  && apt update -y -qq \
  && apt upgrade -y -qq \
  && apt install -y cmake curl git python3 \
  && curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
  && echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null \
  && apt update -y -qq \
  && apt install -y python3-vcstool python3-colcon-common-extensions python3-rosdep \
  && rosdep init \
  && rosdep update \
  && apt update -y -qq \
  && vcs import ${WORKSPACE_DIR}/src < ${WORKSPACE_DIR}/src/noether/dependencies.repos --shallow \
  && rosdep install \
    --from-paths ${WORKSPACE_DIR}/src \
    -iry \
    --skip-keys libvtk

# Build the repository
# Bind mount the source directory so as not to unnecessarily copy source code into the docker image
RUN --mount=type=bind,target=${WORKSPACE_DIR}/src/noether \
  cd ${WORKSPACE_DIR} \
  && colcon build --cmake-args \
  && rm -rf build log

# Set the entrypoint to source the workspace
COPY docker/entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
