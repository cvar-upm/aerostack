## How to update the version of Parrot ARSDK

- Get the release hash ID of the SDK from https://github.com/Parrot-Developers/arsdk_manifests/releases
- Update `script/download_and_strip_arsdk.sh` according to the hash obtained from step 1. For the version, convert dots (`.`) to underscores (`_`). For example for version `3.11.0` use `3_11_0`. If you are releasing a new SDK set the patch level to `0`. Increase that number anytime you apply a new patch to the SDK.

```
ARSDK_MANIFEST_HASH="<hash>"
ARSDK_VERSION="<version>"
PATCH_LEVEL="0"
```

- Run `script/download_and_strip_arsdk.sh` (you need to be connected to the Internet)

    $ ./`script/download_and_strip_arsdk.sh`


This script, downloads all `parrot_arsdk` packages at your specified version, remove all the unnecessary files (i.e. test files), then re-package everything into a single gzipped tarball (e.g. `arsdk_3_11_0_p0_stripped.tgz`) which can be compiled offline.

- Move the generated archive into the `sdk` folder. 

- Update `CMakeLists.txt` to use this new file. Also update the MD5 hash variable:

```
# 3.11.0 patch 0
set(ARSDK_ARCHIVE arsdk_3_11_0_p0_stripped.tgz)
set(ARSDK_ARCHIVE_MD5 c6e04174ffdf736378c79ef6fd921265)
```

- Build the package as a normal `catkin` package.