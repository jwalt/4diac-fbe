#!/usr/bin/env bash
set -euo pipefail

kill -9 $(cat forte.pid)
