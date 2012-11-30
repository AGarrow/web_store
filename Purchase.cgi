#!/usr/local/bin/python
import cgi
import os


def checkAccount():
	fn = os.path.join(os.path.dirname(__file__), 'databases/Inventory.csv')
	catalogue = open(fn,'r')
	form = cgi.FieldStorage()
	if form.has_key("username"):
		self.username = form["username"].value
	if form.has_key("password"):
		self.password = form["password"].value

	for line in catalogue.readlines():
		entry = line.split(',')
		if line[0] == username & line[1] == password:
			return true
	return false




print "Content-type: text/html"
print "<html>"
if checkAccount():
	print "hello "+username
else:
	print "username and password do not match"
print "</html>"


	
