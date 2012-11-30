#!/usr/local/bin/python
import cgi
import os

username
password

def checkAccount():
	fn = os.path.join(os.path.dirname(__file__), 'databases/Inventory.csv')
	catalogue = open(fn,'r')
	form = cgi.FieldStorage()
	username = form["username"].value
	password = form["password"].value


	for line in catalogue.readlines():
		entry = line.split(',')
		if line[0] == username & line[1] == password
			return true
	return false

print "Content-type: text/html"
print "<html>"
if checkAccount():
	print "hello "+username
else
	print "username and password do not match"
print "</html>"


	
