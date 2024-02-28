#!/usr/bin/env bash
set -euo pipefail

sleep 5
exec kill -0 $(< forte.pid)
