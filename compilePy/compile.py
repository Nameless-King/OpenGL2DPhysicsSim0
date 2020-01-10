import os
import subprocess
import re
import time
import sys

def raise_exception(message):
    raise Exception(message)

def strip_extension(files):
    names = []
    for i in range(len(files)):
        names.append(re.split("[/.(\x07)]",files[i])[-2])
    return names

def execute(command):
    out = subprocess.Popen(command,stdout=subprocess.PIPE)
    for out_line in iter(out.stdout.readline,""):
        yield
    out.stdout.close()
    completion_status = out.wait()
    if completion_status:
        raise subprocess.CalledProcessError(completion_status,command)

def compile_files(files,flags,times,last_compiled_time,compile_type="",prev_terminated=[]):
    terminated_files = []
    names = strip_extension(files)
    num_errors = 0
    num_compiled = 0
    for i in range(len(files)):
        if(compile_type == "--compile-all" or last_compiled_time < os.path.getmtime(files[i]) or files[i] in prev_terminated):
            current_cmd = "g++ "+flags+" -c -o '../objectFiles/"+names[i]+".o' '"+files[i]+"'"
            
            print("[***]Compiling file [->]"+files[i]+"[<-]")
            print("[***]Executing [->]"+current_cmd+"[<-]")
            #could not get os.popen to work with current_cmd
            #cmd_out = os.popen(current_cmd)
            #print(execute(["g++",flags,"-c","-o","../objectFiles/"+names[i]+".o",files[i]]))
            

            
            out = subprocess.Popen(["g++",flags,"-c","-o","../objectFiles/"+names[i]+".o",files[i]], stdout=subprocess.PIPE,stderr=subprocess.STDOUT)

            

            
            stdout,stderr = out.communicate()

            if stdout != b'' or stderr != None:

                num_errors += 1
                terminated_files.append(files[i])
                

                print("\n[!!!]FATAL ERROR[!!!]\n")
                print(str(stdout).replace('\\n','\n'))
                print(str(stderr).replace('\\n','\n'))
                print("\n[!!!]Fatal error when running command")
                print("\t"+current_cmd)
                input("\n[***]Enter to continue.\n")
            else:
                num_compiled += 1
                print("[***]Successfully exectued command.")
                yield "OK\n" 
           
            out.stdout.close()

        else:
            print("[***]File [->]"+files[i]+"[<-]")
            print("[***]\tdoes not need to be recompiled.")
            

        

    print("[***] Compilation finished.")
    print("[***] Errors Raised  [->]"+str(num_errors)+"[<-]")
    print("[***] Files Compiled [->]"+str(num_compiled)+"[<-]")
    return terminated_files
                

def create_dictionary(files):
    last_modified_times = {}
    for file in files:
        if file not in last_modified_times:
            last_modified_times[file] = os.stat(file).st_mtime
        else:
            raise_exception("Duplicate files found! File: " +file)
        
    return last_modified_times

def main():
    compile_type = ""
    if len(sys.argv) > 1:
        compile_type = sys.argv[1]

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
        cache_in = f.read().split(",")
        last_compiled = float(cache_in[0])
        last_terminated = cache_in[1:]
        print("Files to recompile due to previous compiling errors:",last_terminated)
        print()
        #if last_compiled == "":
        #    last_compiled = 0

    print("[***]Compiling Files")
    terminated_files = compile_files(files_to_compile,flags,modified_times,last_compiled,compile_type=compile_type,prev_terminated=last_terminated)

    with open("./cache.txt","w") as f:
        f.write(str(time.time()))
        for file in terminated_files:
            f.write(","+file)
       


if __name__ == '__main__':
    main()
