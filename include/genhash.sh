#!/bin/bash

if [ "$1" = "self" ]
then
    hash=`cat $2.hash`
else
    hash=$1
fi
echo "Generating hash ($hash) for \"$2\""
echo $hash | xxd -r -p - > $2_expected_hash
xxd -i $2_expected_hash > $2_expected_hash.h
