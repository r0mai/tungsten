from subprocess import Popen, PIPE, STDOUT
import web
import string
from django.utils.encoding import smart_str, smart_unicode
from web import form

render = web.template.render('templates/')

tungsten = '../bin/tungsten --eval '

urls = ('/(.*)', 'index')
app = web.application(urls, globals())

myform = form.Form( 
    form.Textbox("input", size="56", maxlength="128",
    validators = [form.Validator("Only ASCII chars please.", lambda s: all(ord(smart_str(c))<128 for c in s) )])
)


class index: 
	def getLog(self): 
		p = Popen("tail log.txt", shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		return p.stdout.read().replace(' ', r'<br>')
	
	def GET(self,name): 
		form = myform()
		cmd = ''
		if name and (name is not "favicon.ico"):
			cmd = tungsten + '"' +name.replace('"', r'\"')+ '"'
		p = Popen(cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		output = p.stdout.read()
		with open("log.txt", "a") as myfile:
			myfile.write(smart_str(name)+'\n')
		return render.formtest(form, name, output, self.getLog())


	def POST(self, name): 
		form = myform() 
		if not form.validates() and not name: 
			return render.formtest(form, name,'Invalid input', self.getLog())
		else:
			return render.redir(form.d.input)

if __name__=="__main__":
    web.internalerror = web.debugerror
    app.run()
