from subprocess import Popen, PIPE, STDOUT
import web
import string
from django.utils.encoding import smart_str, smart_unicode
from web import form
import pytungsten
import ctypes
import unicodedata
import uuid

web.config.debug = False
render = web.template.render('templates/')
t = pytungsten.tungsten()

urls = ('/(.*)', 'index')
app = web.application(urls, globals())
session = web.session.Session(app, web.session.DiskStore('sessions'))

myform = form.Form( 
    form.Textbox("input", size="56", maxlength="128",
    validators = [form.Validator("Only ASCII chars please.", lambda s: all(ord(smart_str(c))<128 for c in s) )])
)


class index: 
	def getLog(self): 
		p = Popen("tail log.txt", shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		return p.stdout.read().replace('\n', r'<br>')
	
	def GET(self,name): 
		form = myform
		if name:
			uid = long(session.session_id[0:7], 16) # hopefully this should be enough.
			output = t.evaluate(uid,name.encode('ascii', 'ignore')).getOutputString()
		else:
			output = ""
		with open("log.txt", "a") as myfile:
			if not (name == 'favicon.ico'): 
				myfile.write(smart_str(name)+'\n')
		return render.formtest(form, name, output, self.getLog())


	def POST(self, name): 
		form = myform() 
		if not form.validates() and not name: 
			return render.formtest(form, name,'Invalid input', self.getLog())
		else:
			return render.redir(form.d.input)

if __name__=="__main__":
    app.run()
