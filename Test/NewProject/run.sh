#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/Builds/LinuxMakefile"
make CONFIG=Debug -j"$(nproc)"
exec ./build/NewProject
