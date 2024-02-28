#!/usr/bin/env bash
set -euo pipefail

./forte -f *.fboot &
echo "$!" > forte.pid
