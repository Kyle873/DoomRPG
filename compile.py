#!python2.7

import os, subprocess

C_COMPILER   = os.path.join ("Utilities", "GDCC", "gdcc-cc.exe")
ASM_COMPILER = os.path.join ("Utilities", "GDCC", "gdcc-as.exe")
LINKER       = os.path.join ("Utilities", "GDCC", "gdcc-ld.exe")

LIBC_SOURCES    = os.path.join ("Utilities", "GDCC", "lib", "src", "libc")
LIBGDCC_SOURCES = os.path.join ("Utilities", "GDCC", "lib", "src", "libGDCC")

ACS_SOURCES  = os.path.join ("DoomRPG", "scripts")
ACS_INCLUDES = os.path.join ("DoomRPG", "scripts", "inc")

# Compile options.
OPTIONS = ['--bc-target=ZDoom']

COMPILEROPTIONS = ['-i', ACS_INCLUDES]
ASSEMBLEROPTIONS = []
LINKEROPTIONS = []

OBJECTDIR = os.path.join ("DoomRPG", "acs")

def compile_objects (path):
    """Compiles a list of all files in <path> into IR objects, then returns the
    objects compiled as a list."""
    linkfiles = []
    for directory, dirnames, filenames in os.walk (path):
        # Compile the files in this directory
        for filename in filenames:
            objectname = filename.rpartition (".")[0] + ".obj"
            if filename.endswith (".c"):
                compiler = C_COMPILER
                compileoptions = COMPILEROPTIONS

            elif filename.endswith (".asm"):
                compiler = ASM_COMPILER
                compileoptions = ASSEMBLEROPTIONS

            else:
                continue # Likely a header

            commandline = [compiler]
            commandline += OPTIONS
            commandline += compileoptions
            commandline += [os.path.join (directory, filename), os.path.join (OBJECTDIR, objectname)]
            print "- Compiling {}...".format (filename)
            try:
                out = subprocess.check_output (commandline, stderr=subprocess.STDOUT)
                if out:
                    print "  - Compiler: {}".format (out)

            except subprocess.CalledProcessError:
                print "  - Compile failed!"
                raise

            linkfiles.append (os.path.join (OBJECTDIR, objectname))

        # End compiling

    return linkfiles

def link_library (objlist, libraryname):
    """Links a list of loose object files into a library."""

    commandline = [LINKER]
    commandline += OPTIONS
    commandline += LINKEROPTIONS
    for objectfile in objlist:
        commandline.append (objectfile)

    commandline.append ("-o")
    commandline.append (os.path.join (OBJECTDIR, libraryname))

    print "+ Linking {}...".format (libraryname)
    try:
        out = subprocess.check_output (commandline, stderr=subprocess.STDOUT)
        if out:
            print "  - Linker: {}".format (out)

    except subprocess.CalledProcessError:
        print "  - Link failed!"
        raise

if __name__ == "__main__":
    try:
        objects = compile_objects (LIBC_SOURCES)
        objects += compile_objects (LIBGDCC_SOURCES)
        objects += compile_objects (ACS_SOURCES)

        link_library (objects, "DoomRPG.lib")
        print "> Cleaning up files..."
        for filename in objects:
            os.remove (filename)

        print "* Done! Press return to exit."
        raw_input ("")

    except subprocess.CalledProcessError, err:
        print "X An error occurred while attempting to compile/link:"
        print "  {}".format (err.output.strip ())
        print "X Review the error above, and press return to exit."
        raw_input ("")
