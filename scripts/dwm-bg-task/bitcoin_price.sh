#!/bin/bash

LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

price=$(timeout 60 $DIR/bitcoin_price.py)
if [ "$price" != "" ]; then
    echo "₿" $price > /tmp/bitcoin_price.dat
fi
