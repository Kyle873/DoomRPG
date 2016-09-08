#!/usr/bin/env python2

import subprocess
import urllib2
import sys
import io
import os, shutil

USE_64BIT_BINARIES = (sys.maxsize > 2 ** 32)

def retrievebuild ():
    link = None
    
    if USE_64BIT_BINARIES:
        try:
            link = urllib2.urlopen("https://www.dropbox.com/sh/e4msp35vxp61ztg/AACzzIcbcyFrRhGMamDGcdhMa/gdcc_latest_win64.txt?dl=1").read().strip()
        except Exception:
            pass
    else:
        try:
            link = urllib2.urlopen("https://www.dropbox.com/sh/e4msp35vxp61ztg/AACi9gkSHBKE25Uikv6DUFFUa/gdcc_latest_win32.txt?dl=1").read().strip()
        except Exception:
            pass

    if link is None:
        raise IOError("Couldn't retrieve GDCC link from Dropbox")
    
    link = link.replace("?dl=0", "?dl=1")
    
    destfile = io.open("gdcc.7z", "w+b")
    data = urllib2.urlopen(link.strip())
    
    destfile.write(data.read())
    destfile.close()

def extractbuild ():
    if os.access ("GDCC", os.F_OK):
        shutil.rmtree ("GDCC")
    os.mkdir ("GDCC")

    exename = os.path.join ("7zip", ("64" if USE_64BIT_BINARIES else "32"),
                            "7za.exe")
    arguments = [exename, "x", "-oGDCC", "gdcc.7z"]

    if sys.platform.startswith("linux"):
        try:
            subprocess.call (["wine", "--version"])
        except FileNotFoundError:
            print ("You do not have Wine installed! You won't be able to run GDCC in this manner without it. Try adding it to your system path instead.")
            raise
        
        arguments = ["wine", exename, "x", "-oGDCC", "gdcc.7z"]
    
    subprocess.call (arguments)
    os.remove("gdcc.7z")

if __name__ == "__main__":
    if USE_64BIT_BINARIES:
        print ("Fetching GDCC " + ("64-bit" if USE_64BIT_BINARIES else "32-bit") + "...")
    try:
        retrievebuild ()
    except Exception, e:
        print "There was a problem downloading the compiler:", str(type(e)), str(e)
        raw_input ("Press return to exit.")
        raise SystemExit
        
    print ("Success! Extracting it into the subfolder...")
    try:
        extractbuild ()
    except Exception, e:
        print "There was a problem extracting the compiler:", str(type(e)), str(e)
        raw_input ("Press return to exit.")
        raise SystemExit
        
    print ("Done.")
    raw_input ("Press return to exit.")
