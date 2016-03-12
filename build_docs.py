#build_docs.py
#Author: Will Barnes
#Date: 12 March 2016

#Description: Use cldocs to build documentation 

import glob
import subprocess

#Get all headers and sources
sources=glob.glob('source/*.cpp') + glob.glob('source/OpticallyThick/*.cpp')
headers=glob.glob('source/*.h') + glob.glob('source/OpticallyThick/*.h')

#Set build options
build_opts='--report --output html ' + ' '.join(sources) + ' ' + ' '.join(headers)

#Set needed CXX flags
cxx_flags='-I/opt/local/include -I/usr/include/malloc'

#set path to cldoc exec
exec_path='/opt/local/Library/Frameworks/Python.framework/Versions/2.7/bin/cldoc'

#Run command
subprocess.call( exec_path+' generate ' + cxx_flags + ' -- ' + build_opts,shell=True)
