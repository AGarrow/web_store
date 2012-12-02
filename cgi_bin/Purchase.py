#!/usr/local/bin/python
import cgi
import os


def parseForm():
	if form.has_key("username") and form["username"].value != "":
		self.username = form["username"].value
	if form.has_key("password") and form["password"].value != "":
		self.password = form["password"].value
	if form.getvalue("light-purchase"):
		self.light_quantity = form["light-quantity"].value
	if form.getvalue("mid-purchase"):
		self.mid_quantity = form["mid-quantity"].value
	if form.getvalue("heavy-purchase"):
		self.heavy_quantity = form["heavy-quantity"].value


def checkAccount():
	fn= os.path.abspath('..')+'/databases/Inventory.csv'
	catalogue = open(fn,'r')
	for line in catalogue.readlines():
		entry = line.split(',')
		if line[0] == username & line[1] == password:
			return True
	return False

def editInventory():
	
def appendLog():



def printHeader():
	print "Content-type: text/html\n\n"
	print "<html>\n"
	print "<head>"
	print """<link href = "./css/bootstrap.min.css" media="all" rel="stylesheet" type="text/css"/>"""
	print """<link href = "./css/custom.css" media = "all" rel="stylesheet" type="text/css">"""
	print "</head>"

def printMenu():
	print """<header class ="navbar navbar-fixed-top">"""
	print """<div class = "navbar-inner">"""
	print "<nav>"
	print """<ul class = "nav pull-left">"""
	print """<li><a href="../home.html">HOME<i class="icon-home"></i></a></li>"""
	print "</ul>"
	print """<ul class = "nav pull-right">"""
	print """<li><a href="catalogue.html">Catalogue</a></li>"""
	print """<li><a href="login.html" target="_blank">Login</a></li>"""
	print "</ul>"
	print "</nav>"
	print "</div>"
	print "</header>"

def printError():


def printBill():

parseForm()
printHeader()
print "<body>"
printMenu()
if checkAccount():
	editInventory():
	appendLog():
	printBill():
else:
	printError():
print "</body>"



	
