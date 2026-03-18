#!/bin/sh

HOST=`ip route show | head --lines 1 | awk '{print $9}'`
cat $BASE_DIR/../custom-scripts/network-config | sed 's/\[IP-DO-HOST\]/'"$HOST"'/g' > $BASE_DIR/../custom-scripts/S41network-config
cp $BASE_DIR/../custom-scripts/S41network-config $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S41network-config
cp $BASE_DIR/../apps/hello $BASE_DIR/target/usr/bin
cp $BASE_DIR/../custom-scripts/hello $BASE_DIR/target/etc/init.d/S50hello
chmod +x $BASE_DIR/target/etc/init.d/S50hello