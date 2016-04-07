#build_docs.py
#Author: Will Barnes
#Date: 12 March 2016

#Description: Use cldocs to build documentation
#TODO: makefile or scons instead of scripts?
#TODO: trigger doc builds at every commit on github
#TODO: docs page on github

import glob
import os
import subprocess

#Get all headers and sources
sources=glob.glob('source/*.cpp') + glob.glob('source/OpticallyThick/*.cpp')
headers=glob.glob('source/*.h') + glob.glob('source/OpticallyThick/*.h')

#check for travis
on_travis = os.environ.get('TRAVIS',None).lower()=='true'

#Set build options
if on_travis:
    build_opts = '--report --merge docs/ext --output docs/html '
else:
    build_opts = '--static --report --merge docs/ext --output docs/html '
build_opts += ' '.join(sources) + ' ' + ' '.join(headers)

#Set needed CXX flags
cxx_flags='-I/opt/local/include -I/usr/include/malloc'

#set path to cldoc exec (if not already in path)
exec_path='cldoc'

#Run command
subprocess.call( exec_path+' generate ' + cxx_flags + ' -- ' + build_opts,shell=True)
