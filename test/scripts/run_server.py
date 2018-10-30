#!/usr/bin/env python3



import argparse
import os
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


server_process = subprocess.Popen(
    [sys.executable, "-m", "http.server", args.port, "--bind", "127.0.0.1"],
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

