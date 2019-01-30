#!/bin/sh

echo "downloading nvidia driver... $GL_VERSION"
if test "$GL_VERSION" != "-1"; then
  curl http://us.download.nvidia.com/XFree86/Linux-x86_64/"$GL_VERSION"/NVIDIA-Linux-x86_64-"$GL_VERSION".run -o /tmp/NVIDIA-DRIVER.run
  sh /tmp/NVIDIA-DRIVER.run -a -N --ui=none --no-kernel-module
  rm /tmp/NVIDIA-DRIVER.run
fi