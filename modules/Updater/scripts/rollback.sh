#!/usr/bin/env bash
set -euo pipefail

cd next
./shutdown.sh
rm -rf .
cp ../template/* .

cd ..
cd current
./startup.sh
