#!/usr/bin/env bash
cd "$(dirname "$0")"
cd ..

vendor/premake/premake5 gmake
