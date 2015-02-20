#!/usr/bin/python

import os
import sys
import signal
import threading
import select

sys.path.append(os.path.dirname(__file__))
sys.path.append('../build/html' )
sys.path.append(os.path.join(os.path.dirname(__file__), '../build'))

from subprocess import Popen, PIPE, STDOUT
import web
import string
from django.utils.encoding import smart_str, smart_unicode
from web import form
import libpytungsten
import ctypes
import unicodedata
import uuid



web.config.debug = False
render = web.template.render( os.path.join(os.path.dirname(__file__), 'templates/' ) )
t = libpytungsten.tungsten()

urls = ('/(.*)', 'index')
app = web.application(urls, globals())
curdir = os.path.dirname(__file__)
session = web.session.Session(app, web.session.DiskStore(os.path.join(curdir,'sessions')),)

application = app.wsgifunc()


def terminal():
	areWeUnderExit = False
	while True:
		s = ""
		timeout = 1
		rlist, _, _ = select.select([sys.stdin], [], [], timeout)

		if rlist:
			s = sys.stdin.readline()

			if s == "shutdown\n":
				areWeUnderExit = True

			#sys.stdout.write(s)

			if s == "users\n":
			        t.getUsers()

                        if s == "reload\n":
                                thisFileName = __file__;
                                os.execlp("python", "python", thisFileName, "8081")


		if areWeUnderExit:
			print "Exiting"
			os.kill(os.getpid(), signal.SIGINT)
			break



def myform(val):
	return  form.Form( form.Textarea("input", rows="5", cols="40", placeholder="Input here", value=val) )


class index:
	def getLog(self):
		largeString = ""
		logStringList = (t.getLog().split('\n')[-11:])
		logStringList.reverse()
		for l in logStringList:
			if l:
				if len(l) < 100:
					tmpString = "<a href=\"http://matthiasvegh.dyndns.org/tungsten/"+l+"\">"+l+"</a><br>"
				else:
					tmpString = "<a href=\"http://matthiasvegh.dyndns.org/tungsten/"+l+"\">"+l[:97]+"...</a><br>"
				largeString+=tmpString

		return largeString


	def GET(self,name):
		form = myform(name)
		if name:
			uid = session.session_id
			o = t.evaluate(uid,name.encode('ascii', 'ignore'))
			output = o.getOutputString()
                        if web.ctx.has_key('HTTP_X_FORWARDED_FOR'):
                            ip = web.ctx.env['HTTP_X_FORWARDED_FOR']
                            t.setIp(uid, ip);

			if output == "\\text{Null}":
				output = "\\verb|No Output|"

			errors = o.getErrors()
			input = o.getTeXInputString()
			if not input:
				input = "\\verb~"+name+"~"
				errors = "syntax::syntax" + errors
				output = "\\verb|No Output|"
			svg = o.getSVG()
		else:
			input = name
			output = ""
			errors = ""
			svg = ""
		return render.formtest(form, input, output, svg, errors.replace('\n', r'<br>'), self.getLog())


	def POST(self, name):
		form = myform("")
		if not form.validates() and not name:
			return render.formtest(form, name,'Invalid input', self.getLog())
		else:
			return render.redir(form.d.input)

if __name__=="__main__":
	terminalThread = threading.Thread(None, terminal)
	terminalThread.start()
	app.run()
