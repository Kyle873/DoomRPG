#!python2.7

import subprocess
import urllib2
import sys
import io
import os, shutil

USE_64BIT_BINARIES = (sys.maxsize > 2 ** 32)

def retrievebuild ():
    linksfile = io.open("gdcc_version.txt", "rt")

    link = None
    for linksline in linksfile:
        if not linksline.startswith("GDCC"):
            continue

        if USE_64BIT_BINARIES and linksline.startswith("GDCC32"):
            continue

        version, dummy, link = linksline.partition(": ")
        break

    if link is None:
        raise IOError("Couldn't retrieve GDCC link from gdcc_version.txt")
    
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
