#!/usr/bin/env bash
set -euo pipefail

cd current
./shutdown.sh
cd ..
cd next
./startup.sh
./check.sh
