#!/usr/bin/env python3

import os
import sys
import subprocess

def run_test(program: str, inp: str, out: str, err: str):
    #print("inp = {0}, out = {1}, err = {2}".format(inp, out, err))
    i = open(inp)
    o = open(out, "w")
    e = open(err, "w")
    p = subprocess.Popen(program,
                         stdin = i,
                         stdout = o,
                         stderr = e)
    p.wait()
    o.flush()
    e.flush()

# Spusti 'diff first_file second_file' a vrati dvojici (navratova hodnota, stdout)
def run_diff(first_file: str, second_file: str) -> tuple:
    #print("first_file = {0}, second_file = {1}".format(first_file, second_file))
    p = subprocess.Popen(["diff", first_file, second_file],
                         stdin = subprocess.DEVNULL,
                         stdout = subprocess.PIPE,
                         stderr = subprocess.STDOUT,
                         universal_newlines = True) # Nutne pro spravne ziskani vystupu jako stringu.
    p.wait()
    out, _ = p.communicate()
    #print("diff = \"{0}\"".format(str(out)))
    return p.returncode, str(out)

def print_usage():
    print("Pouziti: {0} <program> <tests_dir>".format(sys.argv[0]))
    print("   <program>    - cesta k testovanemu spustitelnemu souboru.")
    print("   <tests_dir>  - slozka obsahujici testy a referencni vystupy.")

def dump_tech_info():
    pretty_args = str("{\n")
    for i in range(0, len(sys.argv)):
        pretty_args += "   [{0}]  =>  \"{1}\"\n".format(i, sys.argv[i])
    pretty_args += "}\n"
    dump_lines = [
        "--------  [PYTHON VERSION INFO] --------",
        str(sys.version) + "\n",
        "--------  [DUMP OF PASSED COMMAND-LINE ARGS]  --------",
        str(pretty_args),
    ]
    for line in dump_lines:
        print(line)

def main():
    dump_tech_info()
    if len(sys.argv) != 3:
        print_usage()
        return 1
    program_abspath = os.path.abspath(sys.argv[1])
    tests_dir_abspath = os.path.abspath(sys.argv[2])

    # Test korektnosti command-line parametru:
    if not (os.path.isfile(program_abspath) and os.access(program_abspath, os.X_OK)):
        print("[ERROR]: Soubor \"{0}\" neni spustitelny soubor!".format(program_abspath))
        return 2
    if not (os.path.isdir(tests_dir_abspath)):
        print("[ERROR]: Slozka \"{0}\" neexistuje!".format(tests_dir_abspath))
        return 3

    res = {
        True:   "OK",
        False:  "FAILED!!"
    }
    # Samotne provedeni testu.
    for inp_file in [file for file in os.listdir(tests_dir_abspath) if file.endswith(".in")]:
        inp = os.path.abspath(tests_dir_abspath + "/" + inp_file)
        no_ext, _ = os.path.splitext(inp)
        r_out = no_ext + ".out"
        r_err = no_ext + ".err"
        out = no_ext + ".myout"
        err = no_ext + ".myerr"
        run_test(program_abspath, inp, out, err)
        _, diff_o = run_diff(r_out, out)
        _, diff_e = run_diff(r_err, err)
        print("[TEST][{0}]:  ---  [STDOUT]: {1}  ---  [STDERR]: {2}  ---".format(
                inp_file, res[diff_o == ""], res[diff_e == ""]
            ))

if __name__ == "__main__":
    exit(main())
