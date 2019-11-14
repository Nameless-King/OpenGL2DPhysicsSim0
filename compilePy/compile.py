import os
import subprocess
import re
import time

def raise_exception(message):
    raise Exception(message)

def strip_extension(files):
    names = []
    for i in range(len(files)):
        names.append(re.split("[/.(\x07)]",files[i])[-2])
    return names

def compile_files(files,flags,times,last_compiled_time):
    names = strip_extension(files)
    num_errors = 0
    for i in range(len(files)):
        if(last_compiled_time < os.path.getmtime(files[i])):
            current_cmd = "g++ "+flags+" -c -o '../objectFiles/"+names[i]+".o' '"+files[i]+"'"
            print()
            print("[***] Compiling file [->]"+files[i]+"[<-]")
            print("[***] Executing [->]"+current_cmd+"[<-]")
            #could not get os.popen to work with current_cmd
            #cmd_out = os.popen(current_cmd)
            out = subprocess.Popen(["g++",flags,"-c","-o","../objectFiles/"+names[i]+".o",files[i]], stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
            stdout,stderr = out.communicate()
            if stdout != b'' or stderr != None:
                num_errors += 1
                print(stdout)
                print(stderr)
                print("\n[!!!]Fatal error when running command")
                print("\t"+current_cmd)
                input("\n[***]Enter to continue.\n")
            else:
                print("[***]Successfully exectued command.")
            print()
        else:
            print()
            print("[***] File [->]"+files[i]+"[<-]")
            print("[***]\tdoes not need to be recompiled.")
            print()
    print("[***] Compilation finished with [->]"+str(num_errors)+"[<-] errors")
                

def create_dictionary(files):
    last_modified_times = {}
    for file in files:
        if file not in last_modified_times:
            last_modified_times[file] = os.stat(file).st_mtime
        else:
            raise_exception("Duplicate files found! File: " +file)
        
    return last_modified_times

def main():
    compile_list = "CompileList.txt"

    file_input = open(compile_list,"r")
    input_list = file_input.read().split('\n')
    file_input.close()

    reading_flags = False
    flags = ""
    files_to_compile = []
    for item in input_list:
        if(item == "COMPILER_FLAGS") or (item == "COMPILER_FLAGS_END"):
            reading_flags = not reading_flags
            continue

        if(reading_flags):
            flags = item.strip()
        elif item != "":
            files_to_compile.append(item)

    modified_times = create_dictionary(files_to_compile)

    last_compiled = 0
    with open("./cache.txt","r") as f:
        last_compiled = float(f.read())
        if last_compiled == "":
            last_compiled = 0

    compile_files(files_to_compile,flags,modified_times,last_compiled)

    with open("./cache.txt","w") as f:
        f.write(str(time.time()))

if __name__ == '__main__':
    main()
