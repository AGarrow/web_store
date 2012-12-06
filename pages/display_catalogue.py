#!/usr/local/bin/python
import cgi
import os
def printHeader():
		print "Content-type: text/html\n\n"
		print "<html>\n"
		print "<head>"
		print """<link href = "../pages/css/bootstrap.min.css" media="all" rel="stylesheet" type="text/css"/>"""
		print """<link href = "../pages/css/custom.css" media = "all" rel="stylesheet" type="text/css">"""
		print "</head>"

def printMenu():
	print """<header class ="navbar navbar-fixed-top">"""
	print """<div class = "navbar-inner">"""
	print "<nav>"
	print """<ul class = "nav pull-left">"""
	print """<li><a href="../home.html">HOME<i class="icon-home"></i></a></li>"""
	print "</ul>"
	print """<ul class = "nav pull-right">"""
	print """<li><a href="../pages/display_catalogue.py">Catalogue</a></li>"""
	print """<li><a href="../pages/login.html" target="_blank">Login</a></li>"""
	print "</ul>"
	print "</nav>"
	print "</div>"
	print "</header>"
def printTableHead():
	print """<div class = "well text-align: left">"""
	print """<form method = "POST" action = "../cgi_bin/Purchase.py">"""
	print "<h1>Catalogue</h1>"

def printTableTail():
	print """<input type = "text" name = "username" placeholder = "username" >"""
	print """<input type = "text" name = "password" placeholder = "password" >"""
	print """<input type = "submit" class = "btn btn-primary">"""
	print "</form>"
	print "</div>"		

def printItem(entry):
	img = ""
	checkName = ""
	quantName = ""
	pid = entry[0].strip()
	name = entry[1].strip()
	description = entry[2].strip()
	quantity = entry[3].strip()
	price = entry[4].strip()
	if pid == "01":
		img = """"./images/nerd.jpg" """
		checkName =""" "light-purchase" """
		quantName = """ "light-quantity" """
	if pid == "02":
		img = """ "./images/student.jpg" """
		checkName = """ "mid-purchase" """
		quantName = """ "mid-quantity" """
	if pid == "03":
		img = """ "./images/athlete.jpg" """
		checkName =""" "heavy-purchase" """
		quantName =""" "heavy-quantity" """
	print """<div class = "table table-bordered">"""
	print """	<div class = "row-fluid">"""
	print """		<div class = "span2 pull-left">"""
	print "			<img src="+img+">"
	print "			</div>"
	print """		<div class = "span8">"""
	print "			<br/><h3>"+name+"</h3><br/>"
	print "			<p>"+description+"</p>"
	print "		</div>"
	print """	<div class = "span2"><br/>"""
	print "<h3>$"+price+"/ride</h3>"
	print "<h4>"+quantity+" remaining</h4>"
	print """			<label class = "checkbox">Purchase?	"""				
	print """				<input type = "checkbox" name ="""+checkName+"></label>"
	print "			<label>Rides:</label>"				
	print """			<input type = "text" name = """+quantName+"""class = "input-small" value = "0">"""
	print "</div></div></div>"




fn= os.path.abspath('..')+'/databases/Inventory.csv'
catalogue = open(fn,'r')
printHeader()
printMenu()
print "<body>"
printTableHead()
for line in catalogue.readlines():
	entry = line.split(',')
	if int(entry[3]) != 0:
		printItem(entry)
printTableTail()
print "</body>"

