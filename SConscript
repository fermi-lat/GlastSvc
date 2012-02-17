# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/SConscript,v 1.17.14.1.2.1 2012/01/26 04:13:36 heather Exp $
# Authors: T. Burnett <tburnett@u.washington.edu>
# Version: GlastSvc-09-28-04-gr03
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='GlastSvc', toBuild='component')
#GlastSvcLib = libEnv.SharedLibrary('GlastSvc',
GlastSvcLib = libEnv.ComponentLibrary('GlastSvc',
                                   listFiles(['src/GlastDetSvc/*.cxx',
                                              'src/GlastRandomSvc/*.cxx',
                                              'src/Reco/*.cxx',
                                              'src/CurrentEventAlg/*.cxx',
                                              'src/EventSelector/*.cpp']))

#                                                 #'src/Dll/*.cpp',
#                                                 #'src/HistorySvc/*.cxx',

progEnv.Tool('GlastSvcLib')

test_GlastSvc = progEnv.GaudiProgram('test_GlastSvc',
                                     listFiles(['src/test/*.cxx']), test = 1,
                                     package='GlastSvc')

progEnv.Tool('registerTargets', package = 'GlastSvc',
             libraryCxts = [[GlastSvcLib, libEnv]],
             testAppCxts = [[test_GlastSvc, progEnv]],
             includes = listFiles(['GlastSvc/*/*.h']),
             jo = listFiles(['src/test/*.txt'], recursive = True) )




