#!/bin/bash

# build_files_dir=$1
output_path=$1

# if [ "${build_files_dir}xxx" = "xxx" ]; then
#     echo You must set the output path!;
#     exit
# fi
if [ "${output_path}xxx" = "xxx" ]; then
    echo You must set the directory which will hold the build files to copy over!;
    exit
fi
if [ -z "$KEYSTONE_SDK_DIR" -a "${KEYSTONE_SDK_DIR+xxx}" = "xxx" ]; then
    echo You MUST set KEYSTONE_SDK_DIR.;
    exit
fi
if [ -z "$KEYSTONE_DIR" -a "${KEYSTONE_DIR+xxx}" = "xxx" ]; then
    echo You MUST set KEYSTONE_DIR.;
    exit
fi

copysdk () {
    curdir="$(ls -1)"

    cp -u $build_files_dir $KEYSTONE_SDK_DIR/bin/

	cd $KEYSTONE_DIR
    make hifive
	cd $curdir
}

genhash () {
    echo "Generating hash ($2) for \"$1\""
    echo $2 | xxd -r -p - > $1_expected_hash
    xxd -i $1_expected_hash > $1_expected_hash.h
}

extracthash () {
    # Generalize me!
    expect_commands='
    set timeout 60
    cd $::env(KEYSTONE_DIR)
    spawn ./scripts/run-hifive-qemu.sh
    expect "*?ogin" { send "root\r" }
    expect "*?assword" { send "sifive\r" }

    expect "# " { send "insmod keystone-driver.ko\r" }


    expect "# " { send "ifdown lo && ifup lo #>/dev/null 2>/dev/null\r" }
    expect "# " { send "chmod +x enclave-host.riscv trusted_client.riscv\r" }
    expect "# " { send "./enclave-host.riscv & #>sout.log 2>serr.log\r" }
    expect "# " { send "echo q | ./trusted_client.riscv 127.0.0.1 --ingnore-valid #>cout.log 2>cerr.log\r" }


    expect "# " { send "poweroff\r" }
    expect eof
    '
    expect -c "${expect_commands//
/;}"
}


extracthash | tee extract_hash.log
SM_HASH=$(awk '/=== Security Monitor ===/,/=== Enclave Application ===/' extract_hash.log  | grep "Hash: " | cut -c 7-)
EAPP_HASH=$(awk '/=== Enclave Application ===/,/-- Device pubkey --/' extract_hash.log  | grep "Hash: " | cut -c 7-)
rm -f extract_hash.log
cd $output_path
ls
genhash sm $SM_HASH
genhash enclave $EAPP_HASH