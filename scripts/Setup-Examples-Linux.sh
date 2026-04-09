#!/usr/bin/env bash
cd "$(dirname "$0")"
cd ..

chmod +x vendor/premake/premake5
vendor/premake/premake5 --file=premake5_examples.lua gmake
