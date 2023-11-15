set confirm off
set pagination off
target remote host.docker.internal:3333
monitor nrf5 mass_erase 0
detach
quit
