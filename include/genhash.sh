#/bin/bash
echo "Generating hash for \"$2\""
echo $1 | xxd -r -p - > $2_expected_hash
xxd -i $2_expected_hash > $2_expected_hash.h
