#!/usr/bin/env python3



import os
import platform
import signal
import sys

server_pid_file = os.path.join( os.getcwd(), "serve.pid" )

with open( server_pid_file, "r" ) as pid_file:
    pid = pid_file.readline()

if platform.system() == "Windows":
    os.kill(int(pid), signal.SIGTERM)
else:
    os.kill(int(pid), signal.SIGKILL)

os.remove( server_pid_file )
