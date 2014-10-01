#!/bin/bash


REPO_BRANCH=$1
REPO_URL=$2
MODULE_PATH=$3

#Do the command
git submodule add -b $REPO_BRANCH $REPO_URL $MODULE_PATH  > /dev/null


