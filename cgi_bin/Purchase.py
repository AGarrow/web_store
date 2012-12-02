#!/usr/local/bin/python
import cgi
import os


def checkAccount():
	fn= os.path.abspath('..')+'/databases/Inventory.csv'
	catalogue = open(fn,'r')
	form = cgi.FieldStorage()
	if form.getvalue('light-purchase'):
		print "ordered a lightweight!"
	if form.getvalue('mid-purchase'):
		print "ordered a mid!"
	if form.has_key("username"):
		self.username = form["username"].value
		print "username:"+username
		if form.has_key("password"):
			self.password = form["password"].value

		for line in catalogue.readlines():
			entry = line.split(',')
			if line[0] == username and line[1] == password:
				print "matches!"	
				return True
	return False




print "Content-type: text/html\n\n"
print "<html>\n"
print"<h1>it works! </h1>"
if checkAccount() == True:
	print "hello "+username+"\n"
else:
	print "username and password do not match\n"
	print "Location:../home.html"
print "</html>\n"


	
