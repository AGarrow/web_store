#!/usr/local/bin/python
import cgi
import os
class Purchase:
	def __init__(self):
		self.username = ""
		self.password = ""
		self.light_quantity = ""
		self.mid_quantity = ""
		self.heavy_quantity = ""
	def parseForm(self,form):
		if form.has_key("username") and form["username"].value != "" :
			self.username = form["username"].value.strip()
		if form.has_key("password") and form["password"].value != "":
			self.password = form["password"].value.strip()
		if form.getvalue("light-purchase"):
			self.light_quantity = form["light-quantity"].value.strip()
		if form.getvalue("mid-purchase"):
			self.mid_quantity = form["mid-quantity"].value.strip()
		if form.getvalue("heavy-purchase"):
			self.heavy_quantity = form["heavy-quantity"].value.strip()


	def checkAccount(self):
		fn= os.path.abspath('..')+'/databases/members.csv'
		catalogue = open(fn,'r')
		for line in catalogue.readlines():
			entry = line.split(',')
			if entry[0].strip() == self.username and entry[1].strip() == self.password:
				return True
		return False

	def editInventory(self):
		print "editing inventory"

	def appendLog(self):
		print "appending log"



	def printHeader(self):
		print "Content-type: text/html\n\n"
		print "<html>\n"
		print "<head>"
		print """<link href = "../pages/css/bootstrap.min.css" media="all" rel="stylesheet" type="text/css"/>"""
		print """<link href = "../pages/css/custom.css" media = "all" rel="stylesheet" type="text/css">"""
		print "</head>"

	def printMenu(self):
		print """<header class ="navbar navbar-fixed-top">"""
		print """<div class = "navbar-inner">"""
		print "<nav>"
		print """<ul class = "nav pull-left">"""
		print """<li><a href="../home.html">HOME<i class="icon-home"></i></a></li>"""
		print "</ul>"
		print """<ul class = "nav pull-right">"""
		print """<li><a href="../pages/catalogue.html">Catalogue</a></li>"""
		print """<li><a href="../pages/login.html" target="_blank">Login</a></li>"""
		print "</ul>"
		print "</nav>"
		print "</div>"
		print "</header>"

	def printError(self):
		print """<div class = "row-fluid">"""
		print "<p>error</p>"
		print"</div>"

	def printBill(self):
		print "bill"
form = cgi.FieldStorage()
order = Purchase()
order.parseForm(form)
order.printHeader()
print "<body>"
order.printMenu()
if order.checkAccount():
	order.editInventory()
	order.appendLog()
	order.printBill()
else:
	order.printError()
print "</body>"
print "</html>"


	
