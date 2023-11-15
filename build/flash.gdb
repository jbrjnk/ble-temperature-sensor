set confirm off
set pagination off
target remote host.docker.internal:3333
monitor reset
load
monitor reset
detach
quit
