# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/GlastSvc/SConscript,v 1.8 2009/01/23 00:07:04 ecephas Exp $
# Authors: T. Burnett <tburnett@u.washington.edu>
# Version: GlastSvc-09-26-01
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('GlastSvcLib', depsOnly = 1)
GlastSvcLib = libEnv.SharedLibrary('GlastSvc',
                                   listFiles(['src/Dll/*.cpp',
                                              'src/GlastDetSvc/*.cxx',
                                              'src/GlastRandomSvc/*.cxx',
                                              'src/Reco/*.cxx',
                                              'src/CurrentEventAlg/*.cxx',
                                              'src/HistorySvc/*.cxx',
                                              'src/EventSelector/*.cpp']))

progEnv.Tool('GlastSvcLib')
test_GlastSvc = progEnv.GaudiProgram('test_GlastSvc',
                                     listFiles(['src/test/*.cxx']), test = 1)

progEnv.Tool('registerTargets', package = 'GlastSvc',
             sharedLibraryCxts = [[GlastSvcLib, libEnv]],
             testAppCxts = [[test_GlastSvc, progEnv]],
             includes = listFiles(['GlastSvc/*'], recursive = True))




