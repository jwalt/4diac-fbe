#!/bin/bash
cd "$(dirname "$0")"

rm -rf A B current next

mkdir -p A
mkdir -p B
ln -s A current
ln -s B next

kill `pgrep forte`
cp ../bin/forte template/
cp template/* current/

(
    cd current
    ./startup.sh
)

exec ./updater "$@"
