#!/bin/bash

if [[ "$#" -lt 2 ]]; then
  echo "Usage ./build.sh <dockerfile_dir> <git_url> [<image_name> <gpu_support>]"
  exit 1
fi

scripts_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cwd=$1; shift
git_url=$1; shift
# get inside the dockerfile directory
cd $cwd

args=""

img_name=$1; shift
graphic_support="$#";

if [[ -z $img_name ]]; then
  img_name="$cwd"
fi

args+="-t $img_name "

if [[ $graphic_support -eq 1 ]]; then
  version="$(glxinfo | grep "OpenGL version string" | rev | cut -d" " -f1 | rev)"
  args+="--build-arg GL_VERSION=$version "
fi

args+="--build-arg GIT_URL=$git_url "
args+="."
echo "building image with args... $args"

# copy scripts to docker build context dir
for script in $(ls $scripts_dir/image_scripts/); do
  cp $scripts_dir/image_scripts/$script .
done

sudo docker build $args

# clean
for script in $(ls $scripts_dir/image_scripts/); do
  rm ./$script
done

cd -
