#!/usr/local/bin/python

import cgi
import os

class Purchase:

	def __init__(self):
		self.username = ""
		self.password = ""
		self.light_price = ""
		self.mid_price = ""
		self.heavy_price = ""
		self.total_before_tax = 0
		self.itemspurchased = {}
	
	def parseForm(self, form):
		if form.has_key("username") and form["username"].value != "":
			self.username = form["username"].value.strip()

		if form.has_key("password") and form["password"].value != "":
			self.password = form["password"].value.strip()
		self.itemspurchased = {"username":self.username}
		if form.has_key("light-purchase"):
			light_quantity = form["light-quantity"].value.strip()
			self.light_price = 20 
			self.itemspurchased["lightweight"] = light_quantity
		if form.has_key("mid-purchase"):
			mid_quantity = form["mid-quantity"].value.strip()
			self.mid_price = 25
			self.itemspurchased["midweight"] = mid_quantity
		if form.has_key("heavy-purchase"):
			heavy_quantity = form["heavy-quantity"].value.strip()
			self.heavy_price = 30
			if heavy_quantity != "0":self.itemspurchased["heavyweight"] = heavy_quantity

	# we create a dict to store the order #["username":username,"lightweight":quantity,"midweight":quantity]

		



	def checkAccount(self):
		fn= os.path.abspath('..')+'/databases/members.csv'
		catalogue = open(fn,'r')
		for line in catalogue.readlines():
			entry = line.split(',')
			if entry[0].strip() == self.username and entry[1].strip() == self.password:
				return True
		return False

	def editInventory(self):

		#INPUT: self.itemspurchased from parseForm()

		#quantity_and_price = {}

		fn = os.path.abspath('..') + '/databases/Inventory.csv'
		inventory = open(fn, "r")
		lines = inventory.readlines()
		inventory.close()
		inventory = open(fn, "w")
		success = True
		modified_list = []
		for line in lines:
			entry = line.split(',')
			if entry[1].strip() in self.itemspurchased:
				stock = int(entry[3])
				purchased = int(self.itemspurchased[entry[1]])
				if stock < purchased:
					inventory.write(line)
					self.printQuantityError(stock)
					success = False
				else:
					newQuantity = stock-purchased
					entry[3] = str(newQuantity)
					inventory.write(','.join(entry))
			else:
				inventory.write(line)
					
		inventory.close()
		return success

	def appendLog(self):
		fn = os.path.abspath('..')+'/databases/Log.csv'
		log = open(fn,'a')

		logEntry = self.itemspurchased["username"]+","+str(self.total_before_tax)+","
		for key,value in self.itemspurchased.items():
			if key != "username": logEntry += key+","+value+","
		logEntry = logEntry[:-1]
		logEntry+="\n"
		log.write(logEntry)
		log.close




	def printHeader(self):
		print """Content-type: text/html\n\n"
		      <html>
		      <head>
			  <link href = "../pages/css/bootstrap.min.css" media="all" rel="stylesheet" type="text/css"/>
			  <link href = "../pages/css/custom.css" media = "all" rel="stylesheet" type="text/css">
		      </head>"""

	def printMenu(self):
		print """<header class ="navbar navbar-fixed-top">
			    <div class = "navbar-inner">
			      <nav>
				 <ul class = "nav pull-left">
				    <li><a href="../home.html">HOME<i class="icon-home"></i></a></li></ul>
				 <ul class = "nav pull-right">
				    <li><a href="../pages/display_catalogue.py">Catalogue</a></li>
				    <li><a href="../pages/login.html" target="_blank">Login</a></li>
				    </ul></nav></div></header>"""

	def printError(self):
		print """<div class = "span12">
			  <div class = "alert alert-block alert-error">
			    <h4>Oops!</h4>
			    <p>the username and password you entered did not match our 		records</p></div></div>"""
	def printQuantityError(self, quantity):
		print """<div class = "span12">
			      <div class = "alert alert-block alert error">
			      <h4> Sorry!</h4>
			      <p>Sorry, but we only have """+str(quantity)+" in stock!</p></div></div>"
	
	def printBill(self):
		print """<div class ="span6 well" style = "float:none; margin:0 auto;">
			     <h2> Your Bill:</h2>
			     <h4>""" +self.username+ """</h4>
			     <table class = "table table-striped">
				  <th>Item</th><th>Quantity:</th><th>Price</th><th>due</th>"""
			  	
		# INPUT: self.itemspurchased from editInventory()
		self.total_before_tax = 0
		if self.itemspurchased.has_key("lightweight"):
			price =int(self.itemspurchased["lightweight"])*self.light_price
			print "<tr><td>lightweight</td><td>"+str(self.itemspurchased["lightweight"])+"</td><td>$"+str(self.light_price)+"</td><td>$"+str(price)+"</td></tr>"
			self.total_before_tax += price
		if self.itemspurchased.has_key("midweight"):
			price =int(self.itemspurchased["midweight"])*self.mid_price
			print "<tr><td>midweight</td><td>"+str(self.itemspurchased["midweight"])+"</td><td>$"+str(self.mid_price)+"</td><td>$"+str(price)+"</td></tr>"
			self.total_before_tax += price
		if self.itemspurchased.has_key("heavyweight"):
			price =int(self.itemspurchased["heavyweight"])*self.heavy_price
			print "<tr><td>heavyweight</td><td>"+str(self.itemspurchased["heavyweight"])+"</td><td>$"+str(self.heavy_price)+"</td><td>$"+str(price)+"</td></tr>"
			self.total_before_tax += price
		gst = self.total_before_tax*0.05
		pst = gst * 0.095
		print "</table><ul>"
		print "<li>GST: $"+str(gst)+"</li>"
		print "<li>PST: $"+str(pst)+"</li>"
		print "<li><strong>TOTAL:$"+str(self.total_before_tax+gst+pst)+"</strong></li><br>"
		print """  <li><a href="../pages/display_catalogue.py">Continue Shopping</a></li>
		      <li><a href="../home.html">return to homepage</a></li>"""
			
		

form = cgi.FieldStorage()
order = Purchase()
order.parseForm(form)
order.printHeader()
print "<body>"
order.printMenu()
if order.checkAccount():
	if order.editInventory():
		order.printBill()
		order.appendLog()
else:
	order.printError()
print "</body>"
print "</html>"
