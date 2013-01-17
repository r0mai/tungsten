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
    def GET(self,name): 
        form = myform()
        # make sure you create a copy of the form by calling it (line above)
        # Otherwise changes will appear globally
	cmd = ''
        if name:
		cmd = tungsten + name
	p = Popen(cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
	output = p.stdout.read()
	return render.formtest(form, name, output)


    def POST(self, name): 
        form = myform() 
        if not form.validates() and not name: 
            return render.formtest(form, name,'Invalid input')
        else:
            # form.d.boe and form['boe'].value are equivalent ways of
            # extracting the validated arguments from the form.
            cmd = tungsten + form.d.input
            p = Popen(cmd, shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
            output = p.stdout.read()
            return render.formtest(form, name, output)

if __name__=="__main__":
    web.internalerror = web.debugerror
    app.run()
