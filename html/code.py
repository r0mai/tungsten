from subprocess import Popen, PIPE, STDOUT
import web
from web import form

render = web.template.render('templates/')

tungsten = '../bin/tungsten --eval '

urls = ('/(.*)', 'index')
app = web.application(urls, globals())

myform = form.Form( 
    form.Textbox("input")
)


class index: 
	def getLog(self): 
		p = Popen("tail log.txt", shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		return p.stdout.read().replace(' ', r'<br>')
	
	def GET(self,name): 
		form = myform()
		cmd = ''
		if name:
			cmd = tungsten + '"' +name.replace('"', r'\"')+ '"'
		p = Popen(cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
		output = p.stdout.read()
		with open("log.txt", "a") as myfile:
			myfile.write(name+'\n')
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
