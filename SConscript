#HYDRAD Build SConscript
#Will Barnes
#15 December 2015

#Import needed modules
import glob

#Import environment from SConstruct
Import('env')

sources = glob.glob('source/*.cpp')

ot_sources = glob.glob('source/OpticallyThick/*.cpp')

objs = env.Object(sources+ot_sources)

Return('objs')