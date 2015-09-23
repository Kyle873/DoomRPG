#!python2.7

import os, subprocess, sys

# Add Utilities\GDCC to the list of directories to look for GDCC executables
execpaths = os.environ["PATH"].split(os.pathsep)
execpaths.append (os.path.join ("Utilities", "GDCC"))
os.environ["PATH"] = os.pathsep.join (execpaths)

C_COMPILER   = "gdcc-cc"
ASM_COMPILER = "gdcc-as"
LINKER       = "gdcc-ld"

LIBC_SOURCES    = os.path.join ("Utilities", "GDCC", "lib", "src", "libc")
LIBGDCC_SOURCES = os.path.join ("Utilities", "GDCC", "lib", "src", "libGDCC")

ACS_SOURCES  = os.path.join ("DoomRPG", "scripts")
ACS_INCLUDES = os.path.join ("DoomRPG", "scripts", "inc")

# Compile options.
OPTIONS = ['--bc-target=ZDoom']

COMPILEROPTIONS = ['-i', ACS_INCLUDES]
ASSEMBLEROPTIONS = []
LINKEROPTIONS = []

OBJECTDIR = os.path.join ("IR")
OUTPUTDIR = os.path.join ("DoomRPG", "acs")

def compile_objects (path):
    """Compiles a list of all files in <path> into IR objects, then returns the
    objects compiled as a list."""
    if not os.access (OBJECTDIR, os.F_OK):
        os.mkdir (OBJECTDIR)

    linkfiles = []
    compile_failure = False
    for directory, dirnames, filenames in os.walk (path):
        # Compile the files in this directory
        for filename in filenames:
            filepath = os.path.join (directory, filename)
            objectname = filename.rpartition (".")[0] + ".obj"
            objectpath = os.path.join (OBJECTDIR, objectname)
            if filename.endswith (".c"):
                compiler = C_COMPILER
                compileoptions = COMPILEROPTIONS
                
            elif filename.endswith (".asm"):
                compiler = ASM_COMPILER
                compileoptions = ASSEMBLEROPTIONS
                
            else:
                continue # Likely a header

            skip_compiling = False
            if os.access (objectpath, os.F_OK):
                compile_time = os.stat (objectpath).st_mtime
                edit_time = os.stat (filepath).st_mtime

                if compile_time > edit_time:
                    skip_compiling = True

            if not skip_compiling:
                commandline = [compiler]
                commandline += OPTIONS
                commandline += compileoptions
                commandline += [filepath, objectpath]
                print "- Compiling {}...".format (filename)
                try:
                    out = subprocess.check_output (commandline, stderr=subprocess.STDOUT)
                    if out:
                        print "  - Compiler: {}".format (out)
                        
                except subprocess.CalledProcessError, err:
                    print "  - Compile failed: \n    {}".format (err.output.strip())
                    compile_failure = True

            else:
                print "- {} is up to date.".format (filename)
            
            linkfiles.append (objectpath)
        
        # End compiling

    return (compile_failure, linkfiles)

def link_library (objlist, libraryname):
    """Links a list of loose object files into a library."""
    
    commandline = [LINKER]
    commandline += OPTIONS
    commandline += LINKEROPTIONS
    for objectfile in objlist:
        commandline.append (objectfile)

    commandline.append ("-o")
    commandline.append (os.path.join (OUTPUTDIR, libraryname))

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
        final_objects = []
        final_failure = False
        failure, objects = compile_objects (LIBC_SOURCES)
        final_objects += objects
        if failure:
            final_failure = True

        failure, objects = compile_objects (LIBGDCC_SOURCES)
        final_objects += objects
        if failure:
            final_failure = True

        failure, objects = compile_objects (ACS_SOURCES)
        final_objects += objects
        if failure:
            final_failure = True

        if final_failure:
            print "X Errors were detected while attempting to compile."
            print "X Review the errors, and press return to exit."
            raw_input ("")
            raise SystemExit
        
        link_library (objects, "DoomRPG.lib")
        print "* Done! Press return to exit."
        raw_input ("")
        
    except subprocess.CalledProcessError, err:
        print "X An error occurred while attempting to link:"
        print "  {}".format (err.output.strip ())
        print "X Review the error above, and press return to exit."
        raw_input ("")
