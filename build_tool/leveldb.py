#! /usr/bin/env python
# encoding: utf-8


from waflib.Configure import conf

def options(opt):
  opt.add_option('--leveldbinc',action='store', default= opt.path.find_dir('../extern/leveldb/include'), dest= 'leveldbinc')
  opt.add_option('--leveldblib',action='store', default= opt.path.find_dir('../extern/leveldb'), dest= 'leveldblib')

@conf
def load_leveldb(ctx):
  ctx.env.LIBPATH_LEVELDB = ctx.options.leveldblib
  ctx.env.LIB_LEVELDB = ['leveldb']
  ctx.env.INCLUDES_LEVELDB = ctx.options.leveldbinc
  ctx.env.RPATH_LEVELDB = ctx.env.LIBPATH_LEVELDB
  ctx.msg('leveldb lib path', ctx.env.LIBPATH_LEVELDB)
  ctx.msg('leveldb include ', ctx.env.INCLUDES_LEVELDB)

def configure(ctx):
  ctx.load_leveldb()
