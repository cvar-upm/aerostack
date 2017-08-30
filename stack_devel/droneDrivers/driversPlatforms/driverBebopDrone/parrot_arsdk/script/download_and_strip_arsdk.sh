#!/usr/bin/env bash

set -e

ARSDK_MANIFEST_HASH="d7640c80ed7147971995222d9f4655932a904aa8"
ARSDK_VERSION="3_12_6"
PATCH_LEVEL="1"

TMP_WS=`mktemp -d`
CURRENT_DIR=`pwd`
OUTPUT_ARCHIVE=${CURRENT_DIR}/arsdk_${ARSDK_VERSION}_p${PATCH_LEVEL}_stripped.tgz

echo "Temporary workspace: $TMP_WS"
echo "Output: $OUTPUT_ARCHIVE"

cd $TMP_WS
curl -s https://storage.googleapis.com/git-repo-downloads/repo > ./repo
chmod a+x ./repo
echo "y" | ./repo init -u https://github.com/Parrot-Developers/arsdk_manifests.git -b ${ARSDK_MANIFEST_HASH} -m release.xml
./repo sync -c

echo "Applying patches ..."
cd ${TMP_WS}/build/dragon_build && git reset --hard && git apply ${CURRENT_DIR}/patch/dragon_disable_root_check.patch
cd $TMP_WS

mv packages packages.git
mkdir packages

for f in `find ./packages.git -mindepth 1 -maxdepth 1 -type d`; do
  echo "Exporting $f ..."
  git archive --format=tar --prefix=`basename $f`/ --remote $f HEAD | (cd ./packages && tar xf - --exclude='TestBench/*')
done

echo "Applying package patches ..."
git apply ${CURRENT_DIR}/patch/json-c_avoid_so_version.patch

tar cfz $OUTPUT_ARCHIVE ./* --exclude "packages.git"
cd $CURRENT_DIR

echo "Done! Path to the output archive: $OUTPUT_ARCHIVE"

# rm -rf $TMP_WS
