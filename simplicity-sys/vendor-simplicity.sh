#!/usr/bin/env bash
set -e

# Requires (nix-shell with) git, rsync

## 0. Parse command-line options
if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Usage: $0 <path to depend directory> <path to libsimplicity repository root>"
  exit 1
fi

DEPEND_PATH=$(readlink -f "$1")
LIBSIM_PATH=$(readlink -f "$2")
VENDORED_SIM_DIR="$DEPEND_PATH/simplicity"

DEFAULT_VERSION_CODE=$(grep "^version" "$DEPEND_PATH/../Cargo.toml" | sed 's/\./_/g' | sed 's/.*"\(.*\)".*/\1/' | cut -d_ -f1-2)

: "${SIMPLICITY_ALLOC_VERSION_CODE:=$DEFAULT_VERSION_CODE}"

## 1. Sanity check environment.
if ! command -v git > /dev/null; then
    echo "Missing 'git' executable in evironment."
    exit 1
fi
if ! command -v rsync > /dev/null; then
    echo "Missing 'rsync' executable in evironment."
    exit 1
fi

if [ ! -d "$DEPEND_PATH" ]; then
    echo "Depend path '$DEPEND_PATH' does not appear to be a directory."
    exit 1
fi

if [ ! -d "$LIBSIM_PATH" ]; then
    echo "libsimplicity path '$LIBSIM_PATH' does not appear to be a directory."
    exit 1
fi

if [ -d "$VENDORED_SIM_DIR" ]; then
    while true; do
        read -r -p "$VENDORED_SIM_DIR will be deleted [yn]: " yn
        case $yn in
            [Yy]* ) break;;
            [Nn]* ) exit;;
            * ) echo "Please answer y or n.";;
        esac
    done

    rm -rf "$VENDORED_SIM_DIR"
elif [ -e "$VENDORED_SIM_DIR" ]; then
    echo "'simplicity' inside depend directory exists but appears not to be a directory."
    echo "Please move or delete this file."
    exit 1
fi

## 2. Copy files from libsimplicity
pushd "$LIBSIM_PATH/C"

if test -n "$(git status --porcelain)"; then
    echo "WARNING: libsimplicity repo is not clean"
fi

HEAD=$(git rev-parse HEAD)
echo "# This file has been automatically generated." > "$DEPEND_PATH/simplicity-HEAD-revision.txt"
echo "$HEAD" >> "$DEPEND_PATH/simplicity-HEAD-revision.txt"

# Copy C folder to simplicity-sys/depend/simplicity
# Use rsync to copy only files tracked by git
git ls-files | rsync -av --files-from=- . "$VENDORED_SIM_DIR"

popd

## 3. Patch copied files.
find "$DEPEND_PATH/.." -name "*.rs" -type f -exec sed -i "s/rust_[0-9_]*_free/rust_${SIMPLICITY_ALLOC_VERSION_CODE}_free/" {} \;
find "$DEPEND_PATH/.." -name "*.rs" -type f -exec sed -i "s/rust_[0-9_]*_malloc/rust_${SIMPLICITY_ALLOC_VERSION_CODE}_malloc/" {} \;
find "$DEPEND_PATH/.." -name "*.rs" -type f -exec sed -i "s/rust_[0-9_]*_calloc/rust_${SIMPLICITY_ALLOC_VERSION_CODE}_calloc/" {} \;

sed "s/rust_/rust_${SIMPLICITY_ALLOC_VERSION_CODE}_/" \
    < "$DEPEND_PATH/simplicity_alloc.h.patch" \
    | patch "$VENDORED_SIM_DIR/simplicity_alloc.h"

