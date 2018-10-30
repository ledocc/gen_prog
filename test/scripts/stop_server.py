#!/usr/bin/env python3



import os
import signal
import sys

server_pid_file = os.path.join( os.getcwd(), "serve.pid" )

with open( server_pid_file, "r" ) as pid_file:
    pid = pid_file.readline()

os.kill(int(pid), signal.SIGKILL)

os.remove( server_pid_file )
