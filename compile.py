#!/usr/bin/env python2

import os, subprocess, sys, re

# [marrub]
def check_in_path(fname):
    for path in os.environ["PATH"].split(os.pathsep):
        pp = path.split(os.sep)
        pp.append(fname)
        pp = os.sep.join(pp)

        if os.path.exists(pp):
            return True

    return False

warning_regex = re.compile("^WARNING:.*$", re.MULTILINE)
error_regex   = re.compile("^ERROR:.*$",   re.MULTILINE)

TERMCAP_BOLD   = ""
TERMCAP_WHITE  = ""
TERMCAP_BLUE   = ""
TERMCAP_RED    = ""
TERMCAP_YELLOW = ""
TERMCAP_GREEN  = ""
TERMCAP_RESET  = ""

if not sys.platform.startswith("win32"):
    op = subprocess.STDOUT
    TERMCAP_BOLD   = subprocess.check_output(("tput", "bold"),       stderr=op)
    TERMCAP_WHITE  = subprocess.check_output(("tput", "setaf", "7"), stderr=op)
    TERMCAP_BLUE   = subprocess.check_output(("tput", "setaf", "4"), stderr=op)
    TERMCAP_RED    = subprocess.check_output(("tput", "setaf", "1"), stderr=op)
    TERMCAP_YELLOW = subprocess.check_output(("tput", "setaf", "3"), stderr=op)
    TERMCAP_GREEN  = subprocess.check_output(("tput", "setaf", "2"), stderr=op)
    TERMCAP_RESET  = subprocess.check_output(("tput", "sgr0"),       stderr=op)
else:
    subprocess.call(("color", "1F"), shell=True)

STD_COMPILER = "gdcc-makelib"
C_COMPILER   = "gdcc-cc"
ASM_COMPILER = "gdcc-as"
LINKER       = "gdcc-ld"

LIB_PATH = os.path.join("Utilities", "GDCC", "lib")

ACS_SOURCES  = os.path.join("DoomRPG", "scripts")
ACS_INCLUDES = os.path.join("DoomRPG", "scripts", "inc")

# Compile options.
OPTIONS = ['--bc-target=ZDoom']

COMPILEROPTIONS = ['-c', '-i', ACS_INCLUDES]
ASSEMBLEROPTIONS = []
LINKEROPTIONS = []

OBJECTDIR = os.path.join("IR")
OUTPUTDIR = os.path.join("DoomRPG", "acs")

# [marrub] If GDCC is not in our system path, add a local copy.
if not check_in_path("gdcc-cc") and not check_in_path("gdcc-cc.exe"):
    COMPILEROPTIONS.append("--lib-path={}".format(LIB_PATH))

# Add Utilities\GDCC to the list of directories to look for GDCC executables
execpaths = os.environ["PATH"].split(os.pathsep)
execpaths.insert(0, os.path.join("Utilities", "GDCC"))
os.environ["PATH"] = os.pathsep.join(execpaths)


def run_command_status(commandline):
    status = TERMCAP_BOLD + TERMCAP_GREEN + "OK" + TERMCAP_RESET
    errors = False
    output = ""

    try:
        output = subprocess.check_output(commandline, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError, err:
        output = err.output
        output = output + "\nERROR: Program quit with error code {}".format(err.returncode)

    warningoutput = warning_regex.findall(output)
    if warningoutput:
        status = TERMCAP_BOLD + TERMCAP_YELLOW + "WARN" + TERMCAP_RESET

    erroroutput = error_regex.findall(output)
    if erroroutput:
        status = TERMCAP_BOLD + TERMCAP_RED + "FAIL" + TERMCAP_RESET
        errors = True

    sys.stdout.write(status + "\n")
    sys.stdout.flush()

    # Write the warnings first since they're not as important
    for warning in warningoutput:
        sys.stdout.write(TERMCAP_BOLD + TERMCAP_YELLOW + warning + TERMCAP_RESET + "\n")

    for error in erroroutput:
        sys.stdout.write(TERMCAP_BOLD + TERMCAP_RED + error + TERMCAP_RESET + "\n")

    sys.stdout.flush()

    return errors

def compile_objects(path):
    """Compiles a list of all files in <path> into IR objects, then returns the
    objects compiled as a list."""
    if not os.access(OBJECTDIR, os.F_OK):
        os.mkdir(OBJECTDIR)

    linkfiles = []
    compile_failure = False
    for directory, dirnames, filenames in os.walk(path):
        # Compile the files in this directory
        for filename in filenames:
            filepath = os.path.join(directory, filename)
            objectname = filename.rpartition(".")[0] + ".obj"
            objectpath = os.path.join(OBJECTDIR, objectname)
            if filename.endswith(".c"):
                compiler = C_COMPILER
                compileoptions = COMPILEROPTIONS

            elif filename.endswith(".asm"):
                compiler = ASM_COMPILER
                compileoptions = ASSEMBLEROPTIONS

            else:
                continue # Likely a header

            skip_compiling = False
            if os.access(objectpath, os.F_OK):
                compile_time = os.stat(objectpath).st_mtime
                edit_time = os.stat(filepath).st_mtime

                if compile_time > edit_time:
                    skip_compiling = True

            if not skip_compiling:
                commandline = [compiler]
                commandline += OPTIONS
                commandline += compileoptions
                commandline += [filepath, objectpath]

                sys.stdout.write("Compiling " + TERMCAP_BOLD + TERMCAP_BLUE + "{}".format(filename) + TERMCAP_RESET + "...")
                sys.stdout.flush()

                compile_failure = run_command_status(commandline)

            else:
                print(TERMCAP_BOLD + TERMCAP_BLUE + "{}".format(filename) +
                        TERMCAP_RESET +  " is up to date.")

            linkfiles.append(objectpath)

        # End compiling

    return(compile_failure, linkfiles)

def link_library(objlist, libraryname):
    """Links a list of loose object files into a library."""
    if not os.access(OUTPUTDIR, os.F_OK):
        os.mkdir(OUTPUTDIR)

    errors = False

    commandline = [LINKER]
    commandline += OPTIONS
    commandline += LINKEROPTIONS
    for objectfile in objlist:
        commandline.append(objectfile)

    commandline.append("-o")
    commandline.append(os.path.join(OUTPUTDIR, libraryname))

    sys.stdout.write("Linking " + TERMCAP_BOLD + TERMCAP_BLUE + "{}".format(libraryname) + TERMCAP_RESET + "...")
    sys.stdout.flush()

    errors = run_command_status(commandline)
    if errors:
        try:
            os.remove(os.path.join(OUTPUTDIR, libraryname)) # Don't leave behind a partially-built library
        except OSError:
            pass

    return errors

def pause_if_necessary():
    if sys.platform.startswith("win32"):
        subprocess.call(("pause",), shell=True)

if __name__ == "__main__":
    failure = False
    objects = []

    if "noclear" not in sys.argv and os.access(OBJECTDIR, os.F_OK):
        print("Starting a new clean compile")
        for remname in os.listdir(OBJECTDIR):
            try:
                if not remname.endswith("dummy.file"):
                    os.remove(os.path.join(OBJECTDIR, remname))
            except OSError: # Windows locked the file, I DON'T CAAARE
                pass

    sys.stdout.write("Compiling " + TERMCAP_BOLD + TERMCAP_BLUE + "C libraries" + TERMCAP_RESET + "...")
    failure = run_command_status([STD_COMPILER] + COMPILEROPTIONS + OPTIONS + ["-o", os.path.join(OBJECTDIR, "libc.obj"), "libc"])

    if not failure:
        objects.append(os.path.join("IR", "libc.obj"))
        sys.stdout.write("Compiling " + TERMCAP_BOLD + TERMCAP_BLUE + "GDCC libraries" + TERMCAP_RESET + "...")
        failure = run_command_status([STD_COMPILER] + COMPILEROPTIONS + OPTIONS + ["-o", os.path.join(OBJECTDIR, "libGDCC.obj"), "libGDCC"])

    if not failure:
        objects.append(os.path.join("IR", "libGDCC.obj"))
        failure, tempobjs = compile_objects(ACS_SOURCES)

    if not failure:
        objects += tempobjs
        failure = link_library(objects, "DoomRPG.lib")

    if not failure:
        print(TERMCAP_BOLD + TERMCAP_GREEN + "Finished compiling." +
                TERMCAP_RESET)
    else:
        print(TERMCAP_BOLD + TERMCAP_RED + "There were errors. Please review the messages above." + TERMCAP_RESET)

    pause_if_necessary()
    
    if failure:
        sys.exit(1)
