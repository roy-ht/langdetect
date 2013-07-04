# -*- coding: utf-8 -*-

out = '__build'


def options(opt):
        opt.load('compiler_cxx')
        opt.recurse('src')


def configure(conf):
        conf.load('compiler_cxx')
        conf.env.CXXFLAGS = ['-Wall', '-O3', '--std=c++0x']
        # conf.env.CXXFLAGS = ['-Wall', '-O2', '-g', '--std=c++0x']
        if 'clang++' in conf.env.CXX:
            conf.env.append_value('CXXFLAGS', '-stdlib=libc++')
        conf.recurse('src')


def build(bld):
    bld.recurse('src')
