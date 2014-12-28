#! /usr/bin/env python
# encoding: utf-8


option_inc = 'quickfixinc'
option_lib = 'quickfixlib'

checked_include_file = 'Application.h'


from waflib.Configure import conf

def options(opt):
	opt.add_option('--quickfixinc',action='store',default= opt.path.find_dir('SFL/quickfix/include').abspath(), dest= 'quickfixinc')
	opt.add_option('--quickfixlib',action='store',default= opt.path.find_dir('SFL/quickfix/lib').abspath(), dest= 'quickfixlib')

@conf
def load_quickfix(ctx):
	ctx.env.INCLUDES_QUICKFIX = ctx.options.quickfixinc
	if ctx.find_file('Application.h',ctx.env.INCLUDES_QUICKFIX + '/quickfix'):
		ctx.msg('Find quickfix/Application.h', ctx.env.INCLUDES_QUICKFIX)
	else:
		ctx.fatal('quickfixinc is not set and can not find file in default path /usr/local/include')

 	ctx.msg('Checking for the variable quickfixlib', '')
	ctx.env.LIBPATH_QUICKFIX = ctx.options.quickfixlib

	if ctx.find_file('libquickfix.so',ctx.env.LIBPATH_QUICKFIX):
		ctx.msg('Find libquickfix.so', ctx.env.LIBPATH_QUICKFIX)
		ctx.env.LIB_QUICKFIX = ['quickfix']
		ctx.env.RPATH_QUICKFIX = ctx.env.LIBPATH_QUICKFIX
	else:
		ctx.fatal('Can not Find libquickfix.so')

def configure(ctx):
	ctx.load_quickfix()
	
