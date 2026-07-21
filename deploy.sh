#!/usr/bin/env bash

set -euo pipefail

readonly SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
readonly PI_HOST="192.168.4.1"
readonly PI_USER="pi"
readonly LOCAL_BINARY="${SCRIPT_DIR}/build-artifacts/rpi/HiWonderArm/bin/HiWonderArm"
readonly REMOTE_BINARY="/home/pi/deployment"

if [[ ! -f "${LOCAL_BINARY}" ]]; then
    echo "Raspberry Pi build not found: ${LOCAL_BINARY}" >&2
    echo "Build the rpi target before deploying." >&2
    exit 1
fi

echo "Deploying HiWonderArm to ${PI_USER}@${PI_HOST}:${REMOTE_BINARY}"
scp "${LOCAL_BINARY}" "${PI_USER}@${PI_HOST}:${REMOTE_BINARY}"

echo "Deployment complete."
echo "To log in to the Pi, run: ssh ${PI_USER}@${PI_HOST}"

