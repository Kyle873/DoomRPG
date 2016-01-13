#!python2.7

import os, subprocess, sys

TERMCAP_BOLD    = ""
TERMCAP_WHITE   = ""
TERMCAP_BLUE    = ""
TERMCAP_RED     = ""
TERMCAP_YELLOW  = ""
TERMCAP_GREEN   = ""
TERMCAP_RESET   = ""

if sys.platform.startswith ("linux"):
    TERMCAP_BOLD    = subprocess.check_output (("tput", "bold"), stderr=subprocess.STDOUT)
    TERMCAP_WHITE   = subprocess.check_output (("tput", "setaf", "7"), stderr=subprocess.STDOUT)
    TERMCAP_BLUE    = subprocess.check_output (("tput", "setaf", "4"), stderr=subprocess.STDOUT)
    TERMCAP_RED     = subprocess.check_output (("tput", "setaf", "1"), stderr=subprocess.STDOUT)
    TERMCAP_YELLOW  = subprocess.check_output (("tput", "setaf", "3"), stderr=subprocess.STDOUT)
    TERMCAP_GREEN   = subprocess.check_output (("tput", "setaf", "2"), stderr=subprocess.STDOUT)
    TERMCAP_RESET   = subprocess.check_output (("tput", "sgr0"), stderr=subprocess.STDOUT)
elif sys.platform.startswith ("win32"):
    subprocess.check_output (("color", "1F"), stderr=subprocess.STDOUT)

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
                errormessage = ""
                status = TERMCAP_BOLD + TERMCAP_GREEN + "OK" + TERMCAP_RESET
                sys.stdout.write ("Compiling " + TERMCAP_BOLD + TERMCAP_BLUE + "{}".format (filename) + TERMCAP_RESET + "...")
                sys.stdout.flush ()
                try:
                    out = subprocess.check_output (commandline, stderr=subprocess.STDOUT).strip()
                    if out:
                        status = TERMCAP_BOLD + TERMCAP_YELLOW + "WARN" + TERMCAP_RESET
                        
                except subprocess.CalledProcessError, err:
                    errormessage = err.output.strip()
                    status = TERMCAP_BOLD + TERMCAP_RED + "FAIL" + TERMCAP_RESET
                    compile_failure = True
                
                finally:
                    sys.stdout.write (status + "\n")
                    sys.stdout.flush ()
                    
                    if out:
                        print TERMCAP_BOLD + TERMCAP_YELLOW + "{}".format (out) + TERMCAP_RESET
                    
                    if errormessage:
                        print TERMCAP_BOLD + TERMCAP_RED + "{}".format (errormessage) + TERMCAP_RESET

            else:
                print TERMCAP_BOLD + TERMCAP_BLUE + "{}".format (filename) + TERMCAP_RESET +  " is up to date."
            
            linkfiles.append (objectpath)
        
        # End compiling

    return (compile_failure, linkfiles)

def link_library (objlist, libraryname):
    """Links a list of loose object files into a library."""
    if not os.access (OUTPUTDIR, os.F_OK):
        os.mkdir (OUTPUTDIR)
    
    errors = False
    
    commandline = [LINKER]
    commandline += OPTIONS
    commandline += LINKEROPTIONS
    for objectfile in objlist:
        commandline.append (objectfile)

    commandline.append ("-o")
    commandline.append (os.path.join (OUTPUTDIR, libraryname))

    status = TERMCAP_BOLD + TERMCAP_GREEN + "OK" + TERMCAP_RESET
    errormessage = ""
    sys.stdout.write ("Linking " + TERMCAP_BOLD + TERMCAP_BLUE + "{}".format (libraryname) + TERMCAP_RESET + "...")
    sys.stdout.flush ()
    try:
        out = subprocess.check_output (commandline, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError, err:
        status = TERMCAP_BOLD + TERMCAP_RED + "FAIL" + TERMCAP_RESET
        out = ""
        errormessage = err.output.strip()
        errors = True
    finally:
        sys.stdout.write (status + "\n")
        sys.stdout.flush ()
        
        if out:
            print TERMCAP_BOLD + TERMCAP_YELLOW + "{}".format (out) + TERMCAP_RESET
        
        if errormessage:
            print TERMCAP_BOLD + TERMCAP_RED + "{}".format (errormessage) + TERMCAP_RESET
    
    return errors

if __name__ == "__main__":
    if "clear" in sys.argv and os.access (OBJECTDIR, os.F_OK):
        print ("Starting a new clean compile")
        for remname in os.listdir (OBJECTDIR):
            try:
                os.remove (os.path.join (OBJECTDIR, remname))
            except OSError: # Windows locked the file, don't caaaaare
                pass
    
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
    
    final_failure = link_library (objects, "DoomRPG.lib")
    if not final_failure:
        print "Done! Press return to exit."
        raw_input ("")
        raise SystemExit
    else:
        print "There were errors.\nPlease review above, then press return to exit."
        raw_input ("")
        raise SystemExit
