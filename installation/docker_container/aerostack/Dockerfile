FROM ros:kinetic
MAINTAINER gblanco

RUN export TERM=xterm
RUN export ROS_DISTRO="kinetic"

# setup keys
# gazebo
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys D2486D2DD83DB69272AFE98867170598AF249743
# ros
RUN apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
# setup sources.list
RUN . /etc/os-release \
  && . /etc/lsb-release \
  && echo "deb http://packages.osrfoundation.org/gazebo/$ID-stable $DISTRIB_CODENAME main" > /etc/apt/sources.list.d/gazebo-latest.list \
  && echo "deb http://packages.ros.org/ros/ubuntu $DISTRIB_CODENAME main" > /etc/apt/sources.list.d/ros-latest.list
# dependencies
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y \
            vim ros-$ROS_DISTRO-ros-tutorials apt-utils sudo \
            gnome-terminal \
            libncurses5 \
            ncurses-bin \
            ncurses-dev \
            libboost-dev \
            expect \
            liblapack3 \
            liblapack-dev \
            libblas3 \
            libblas-dev \
            libf2c2 \
            libf2c2-dev \
            libsdl2-dev \
            libavahi-core-dev \
            libavahi-client-dev \
            libswscale-dev \
            libavformat-dev \
            libavcodec-dev \
            ros-$ROS_DISTRO-rqt \
            ros-$ROS_DISTRO-rqt-common-plugins \
            ros-$ROS_DISTRO-rqt-image-view \
            ros-$ROS_DISTRO-rqt-plot \
            ros-$ROS_DISTRO-hector-slam \
            ros-$ROS_DISTRO-parrot-arsdk \
            ros-$ROS_DISTRO-amcl \
            ros-$ROS_DISTRO-move-base \
            ros-$ROS_DISTRO-mavros-msgs \
            ros-$ROS_DISTRO-audio-common \
            ros-$ROS_DISTRO-rviz \
            ros-$ROS_DISTRO-image-proc \
            ros-$ROS_DISTRO-zeroconf-avahi \
            ros-$ROS_DISTRO-zeroconf-avahi-demos \
            ros-$ROS_DISTRO-zeroconf-avahi-suite \
            protobuf-compiler \
            build-essential python-rosdep python-catkin-tools \
            libsdl1.2-dev libudev-dev libiw-dev \
            libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev \
            festlex-cmu \
            python-gst0.10 python-pyinotify  \
            net-tools xfce4-terminal iputils-ping \
            libgl1-mesa-glx libgl1-mesa-dri mesa-utils \
            binutils module-init-tools \
            libprotobuf-dev libprotoc-dev libeigen3-dev libgazebo7-dev genromfs \
            zip unzip less tree \
            zsh wget

RUN apt-cache search festvox && \
    apt-get update && \
    apt-get install -y \
            festvox-rablpc16k festvox-kallpc16k festvox-ellpc11k \
            libqwt-headers libqwt-qt5-dev libzbar-dev

# vim, zsh, bash setup
RUN git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim && \
    mkdir -p ~/.vim/swap ~/.vim/backup ~/.vim/undo && \
    chsh -s /usr/bin/zsh && \
    git clone --depth=1 https://github.com/robbyrussell/oh-my-zsh.git /root/.oh-my-zsh && \
    git clone https://github.com/zsh-users/zsh-autosuggestions /root/.oh-my-zsh/custom/plugins/zsh-autosuggestions

# Nvidia Driver
ARG GL_VERSION=-1
ENV GL_VERSION $GL_VERSION
# project url
ARG GIT_URL=""

# scripts
# graphic card support
COPY gl_setup.sh /root/gl_setup.sh
RUN chmod +x /root/gl_setup.sh
RUN /root/gl_setup.sh

# aerostack setup
COPY setup.sh /root/setup.sh
RUN chmod +x /root/setup.sh
RUN /root/setup.sh $GIT_URL

# pixhawk sitl
COPY install_sitl.sh /root/install_sitl.sh
RUN chmod +x /root/install_sitl.sh 
RUN /root/install_sitl.sh

# rc files
COPY zshrc /root/.zshrc
COPY bashrc /root/.bashrc
COPY vimrc /root/.vimrc

# utility scripts
COPY post_install.sh /root/post_install.sh
RUN chmod +x /root/post_install.sh
COPY ros_entrypoint.sh /ros_entrypoint.sh
RUN chmod +x /ros_entrypoint.sh
COPY launch_sitl.sh /root/launch_sitl.sh
RUN chmod +x /root/launch_sitl.sh

# ENV SHELL="/usr/bin/zsh"

# Launch /root/post_install.sh with
# https://[<user>:<pass>@]github.com/Vision4UAV/aerostack
CMD ["zsh"]
