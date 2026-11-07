#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
cmake --build build --target sigilsynth -j"$(nproc)"
exec ./build/src/sigilsynth_artefacts/Debug/sigilsynth
