#!/usr/bin/env python3

# I will try to achieve batch simulations with Cmdenv.
# 2024.07.07, Weilu

"""
Runs Veins simulation in current directory
"""

from __future__ import print_function
import os
import argparse
import subprocess
import tempfile

# v-- contents of out/config.py go here
run_libs = ['../src/libveins.dll']
run_neds = ['../src/veins', '../examples/veins']
run_imgs = ['images']
# ^-- contents of out/config.py go here

def relpath(s):
    veins_root = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')
    return os.path.relpath(os.path.join(veins_root, s), '.')

def modify_ini_parameter(file_path, parameter, value, temp_file_path):
    # Read original file
    with open(file_path, "r", encoding='utf-8') as file:
        lines = file.readlines()
    # Modify parameters and write into the temp file
    with open(temp_file_path, "w", encoding='utf-8') as file:
        parameter_found = False
        for line in lines:
            if line.startswith(parameter):
                file.write(f"{parameter} = {value}s\n")
                parameter_found = True
            else:
                file.write(line)
        if not parameter_found:
            file.write(f"{parameter} = {value}s\n")

# This function is used for extracting the vector data from the vec file
# module:node[...] or rsu[...]
# name: e.g., posx
def extract_attribute_from_csv_output(output, module, name):
    attr_values = []
    for line in output.splitlines():
        if module in line and name in line:
            parts = line.split()
            try:
                delay = float(parts[-1])
                attr_values.append(delay)
            except ValueError:
                pass
    return attr_values

run_libs = [relpath(s) for s in run_libs]
run_neds = [relpath(s) for s in run_neds] + ['.']
run_imgs = [relpath(s) for s in run_imgs]

opp_run = 'opp_run'

lib_flags = ['-l%s' % s for s in run_libs]
ned_flags = ['-n' + ';'.join(run_neds)]
img_flags = ['--image-path=' + ';'.join(run_imgs)]

cmdline = [opp_run, '-u', 'Cmdenv'] + lib_flags + ned_flags + img_flags

print(cmdline)

#Main command here
# if os.name == 'nt':
#     subprocess.call(['env'] + cmdline)
# else:
#     os.execvp('env', ['env'] + cmdline)

# batch simulation for multiple ini files
parameter_name = "*.node[*].appl.beaconInterval"
parameter_values = [5,10]
omnetpp_ini_path = 'omnetpp.ini'
for value in parameter_values:
    print(f"Running simulation with {parameter_name} = {value}s")
    # Build a temp file that will be deleted finally
    fd, temp_ini_path = tempfile.mkstemp(dir='.', suffix='.ini')
    os.close(fd)  
    try:
        modify_ini_parameter(omnetpp_ini_path, parameter_name, value, temp_ini_path)
        temp_cmdline = cmdline + ['-f', temp_ini_path] + ['-c', 'WithBeaconing']
        if os.name == 'nt':
            subprocess.call(['env'] + temp_cmdline)
        else:
            os.execvp('env', ['env'] + temp_cmdline)
        vec_file_path = './results/WithBeaconing-#0.vec'
        
        # run opp_vec2longcsv.sh
        result = subprocess.run(['sh', './results/opp_vec2longcsv.sh', vec_file_path], capture_output=True, text=True)
        output = result.stdout
        
        # Herein we provide an example for extracting I2VDelay
        I2VDelay_values = extract_attribute_from_csv_output(output, 'rsu[0]', 'I2VDelay')
        print('------------------------------output begin------------------------------\n')
        print(f'The size of I2VDelay for {value} is: ',len(I2VDelay_values),'\n')
        print('------------------------------output end--------------------------------\n')
                
    finally:
        os.remove(temp_ini_path)