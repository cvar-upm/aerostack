#!/usr/bin/env python

# This script maps the output of `gcc -dumpmachine` to supported
# platforms of alchemy (TARGET_ARCH variable).
# `gcc -dumpmachine` is more reliable than `uname -a` inside docker containers
# Refer to the CMakeLists.txt file for more information.

from __future__ import print_function
import subprocess

try:
  arch = subprocess.check_output(["gcc", "-dumpmachine"]).strip().split("-")[0]
  if arch in ["aarch64", "arm64"]:
    o = "aarch64"
  elif arch in ["x86_64", "amd64"]:
    o = "x64"
  elif "arm" in arch:
    o = "arm"
  else:
    o = "x86"
  print(o, end='')
except:
  pass
