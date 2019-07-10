#!/usr/bin/env python3



import argparse
import os
import platform
import subprocess
import sys
import time



parser = argparse.ArgumentParser(
    formatter_class=argparse.RawDescriptionHelpFormatter,
)

parser.add_argument(
    '--port',
    help = "port use to bind server",
    default = "8080"
)

args = parser.parse_args()



args=[sys.executable, "-m", "http.server", args.port, "--bind", "127.0.0.1"]

if platform.system() == "Windows":
    flags = 0
    flags |= 0x08000000 # CREATE_NO_WINDOW

    server_process = subprocess.Popen(
        args,
        close_fds=True,
        creationflags=flags
    )
else:
    server_process = subprocess.Popen(
        args,
        stdin=subprocess.DEVNULL,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL
    )

time.sleep(0.2)

if server_process.poll() is not None:
    sys.exit("fail to run server")

with open( os.path.join( os.getcwd(), "serve.pid"), "w" ) as pid_file:
    pid_file.write( "{}".format( server_process.pid ) )


with open( os.path.join( os.getcwd(), "serve.pid2"), "w" ) as pid_file:
        pid_file.write( "not end" )

