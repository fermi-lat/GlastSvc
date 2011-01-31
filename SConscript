# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/GlastSvc/SConscript,v 1.17 2010/12/02 00:36:48 jrb Exp $
# Authors: T. Burnett <tburnett@u.washington.edu>
# Version: GlastSvc-10-00-01
import os
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='GlastSvc', toBuild='component')
GlastSvcLib = libEnv.SharedLibrary('GlastSvc',
                                   listFiles(['src/Dll/*.cpp',
                                              'src/GlastDetSvc/*.cxx',
                                              'src/GlastRandomSvc/*.cxx',
                                              'src/Reco/*.cxx',
                                              'src/CurrentEventAlg/*.cxx',
                                              'src/HistorySvc/*.cxx',
                                              'src/EventSelector/*.cpp']))

progEnv.Tool('GlastSvcLib')
##progEnv.AppendUnique(CPPDEFINES = ['PACKAGE_NAME=\\"GlastSvc\\"'])

test_GlastSvc = progEnv.GaudiProgram('test_GlastSvc',
                                     listFiles(['src/test/*.cxx']), test = 1,
                                     package='GlastSvc')

progEnv.Tool('registerTargets', package = 'GlastSvc',
             libraryCxts = [[GlastSvcLib, libEnv]],
             testAppCxts = [[test_GlastSvc, progEnv]],
             includes = listFiles(['GlastSvc/*'], recursive = True),
             jo = listFiles(['src/test/*.txt'], recursive = True) )




