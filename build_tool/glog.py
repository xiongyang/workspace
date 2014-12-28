#! /usr/bin/env python
# encoding: utf-8


from waflib.Configure import conf

def options(opt):
	opt.add_option('--gloginc',action='store',default='/usr/local/include/', dest= 'gloginc')
	opt.add_option('--gloglib',action='store',default='/usr/local/lib/', dest= 'gloglib')

@conf
def load_glog(ctx):
	ctx.msg('Checking for the variable gloginc','')
        if ctx.options.gloginc:
		ctx.env.INCLUDES_GLOG = ctx.options.gloginc
		ctx.msg(ctx.env.INCLUDES_GLOG , 'OK')

	if ctx.find_file('glog/logging.h',ctx.env.INCLUDES_GLOG):
		ctx.msg('Find logging.h', 'OK')
	else:
		ctx.fatal('gloginc is not set and can not find file in default path /usr/local/include')

 	ctx.msg('Checking for the variable gloglib', '')
	if ctx.options.gloglib:
		ctx.env.LIBPATH_GLOG = ctx.options.gloglib
		ctx.msg(ctx.env.LIBPATH_GLOG, 'OK')

	if ctx.find_file('libglog.so',ctx.env.LIBPATH_GLOG):
		ctx.msg('Find libglog.so', 'OK')
		ctx.env.LIB_GLOG = ['glog']
		ctx.env.RPATH_GLOG = ctx.env.LIBPATH_GLOG
	else:
		ctx.fatal('Can not Find libglog.so')

	ctx.msg('Finished for the variable glog', 'OK')

def configure(ctx):
	ctx.load_glog()
