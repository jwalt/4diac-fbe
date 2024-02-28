#!/usr/bin/env bash
set -euo pipefail

mv next tmp
mv current next
mv tmp current

cd next
rm -rf .
cp ../template/* .
