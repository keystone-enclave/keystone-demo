#!/usr/bin/expect

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
