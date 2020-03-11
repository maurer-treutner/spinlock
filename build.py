#!/usr/bin/python3
#
import argparse
import os
import shutil
import sys
import subprocess
#import os.path

class Builder:
    def __init__(self,path,srcDir,buildDir,prefixDir):
        self.rootPath = os.path.abspath(path)
        self.srcPath = self.rootPath
        if srcDir:
            self.srcPath += '/' + srcDir
        self.buildPath = self.rootPath + '/' + buildDir
        self.prefixPath = self.rootPath + '/' + prefixDir
        self.findCMakeFile()

    def findCMakeFile(self):
        if not os.path.exists(self.srcPath + '/CMakeLists.txt'):
            if os.path.exists(self.srcPath + 'src/CMakeLists.txt'):
                self.srcPath += '/src'
            if os.path.exists(self.srcPath + 'dev/CMakeLists.txt'):
                self.srcPath += '/dev'
            if os.path.exists(self.srcPath + 'source/CMakeLists.txt'):
                self.srcPath += '/source'
            else:
                sys.exit("Could not find CMakeLists.txt in " + self.srcPath + " or its subdirs")

    def prepareBuild(self):
        if (not os.path.exists(self.buildPath)):
            os.mkdir(self.buildPath)
        if (not os.path.exists(self.prefixPath)):
            os.mkdir(self.prefixPath) 
        os.chdir(self.buildPath)
        subprocess.run(['cmake','-DCMAKE_INSTALL_PREFIX='+self.prefixPath,self.srcPath])         

    def doBuild(self):
        os.chdir(self.buildPath)
        subprocess.run(['cmake','--build','.'])
        subprocess.run(['cmake','--build','.','--','install'])

    def doTest(self):
        os.chdir(self.buildPath)
        subprocess.run(['ctest','.'])

    def doClean(self):
        if (os.path.exists(self.buildPath)):
            os.chdir(self.buildPath)
            subprocess.run(['cmake','--build','.','--','clean'])

    def doPurge(self):
        if (os.path.exists(self.prefixPath)):
            shutil.rmtree(self.prefixPath)
        if (os.path.exists(self.buildPath)):
            shutil.rmtree(self.buildPath)


def def_args():
    p = argparse.ArgumentParser(description='build a CMake project')
    p.add_argument('--command',choices=['full','test','build','prepare','clean','purge'],default='full',help='define build action')
    p.add_argument('targetPath')
    return p

parser = def_args()
args = parser.parse_args()
print(args.command)
builder = Builder(args.targetPath,"","build","prefix")
if args.command in ['full','test','build','prepare']:
    builder.prepareBuild()
if args.command in ['full','build','test']:
    builder.doBuild()
if args.command == 'test':
    builder.doTest()
if args.command == 'clean':
    builder.doClean()
if args.command == 'purge':
    builder.doPurge()
