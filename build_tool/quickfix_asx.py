#! /usr/bin/env python
# encoding: utf-8


option_inc = 'quickfix_asx_inc'
option_lib = 'quickfix_asx_lib'

checked_include_file = 'Application.h'


from waflib.Configure import conf

def options(opt):
  #opt.add_option('--quickfix_asx_inc',action='store',default= opt.path.find_dir('extern/quickfix/include').abspath(), dest= 'quickfix_asx_inc')
  #opt.add_option('--quickfix_asx_lib',action='store',default= opt.path.find_dir('extern/quickfix/lib').abspath(), dest= 'quickfix_asx_lib')
  pass

@conf
def load_quickfix_asx(ctx):
	if ctx.options.quickfix_asx_inc:
		ctx.env.INCLUDES_QUICKFIXASX = ctx.options.quickfix_asx_inc
	if ctx.find_file('Application.h',ctx.env.INCLUDES_QUICKFIXASX + '/quickfix'):
		ctx.msg('Find Asx quickfix/Application.h', 'OK')
	else:
		ctx.fatal('asx quickfixinc can not find')
	if ctx.options.quickfix_asx_lib:
		ctx.env.LIBPATH_QUICKFIXASX = ctx.options.quickfix_asx_lib
	if ctx.find_file('libquickfix.so',ctx.env.LIBPATH_QUICKFIXASX):
		ctx.msg('Find Asx libquickfix.so', 'OK')
		ctx.env.LIB_QUICKFIXASX = ['quickfix']
	else:
		ctx,fatal('Can not Find Asx libquickfix.so')
	ctx.msg('Finished for the variable Asx quickfix', 'OK')

def configure(ctx):
	#ctx.load_quickfix_asx()
	pass
