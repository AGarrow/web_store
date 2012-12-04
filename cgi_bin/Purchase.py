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
		self.light_price = ""
		self.mid_price = ""
		self.heavy_price = ""
		self.itemspurchased = {}
	
	def parseForm(self, form):
		if form.has_key("username") and form["username"].value != "":
			self.username = form["username"].value.strip()

		if form.has_key("password") and form["password"].value != "":
			self.password = form["password"].value.strip()

		if form.has_key("light-purchase"):
			self.light_quantity = form["light-quantity"].value.strip()
			self.light_price = 20 

		if form.has_key("mid-purchase"):
			self.mid_quantity = form["mid-quantity"].value.strip()
			self.mid_price = 25

		if form.has_key("heavy-purchase"):
			self.heavy_quantity = form["heavy-quantity"].value.strip()
			self.heavy_price = 30

	# We create a tuple to store the information
	#self.temspurchased = {(id1, quantity1,price1), (id2, quantity2,price2), (id3,quantity3,price3), ("username", self.username)}

		self.itemspurchased = [
			("light-purchased", self.light_quantity, self.light_price),
		       ("mid-purchase", self.mid_quantity, self.mid_price),
		       ("heavy-purchase", self.heavy_quantity, self.heavy_price),
		       ("username", self.username)
		]



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

		modified_list = ()
		for line in inventory.readlines():
			entry = line.split(',')
			for items in self.itemspurchased:
				if(items[0] == entry[0]):	

					quantity_in_stock = int(entry[3].strip())
 
					quantity_selected = items[1] 				

					if quantity_selected > quantity_in_stock:
						print "We only have " + quantity_in_stock + " rides left \n"
						print "Please choose another quantity"
						exit()
					else:
						quantity_in_stock = quantity_in_stock - quantity_selected
						#quantity_and_price = (items[1], entry[4])					


			modified_list.append("%s,%s,%s,%s,%s,%s" % (entry[0], entry[1], entry[2], quantity_in_stock, entry[4]))

		inventory.close() 

		# Open file to write modified information
		inventory_modified = open(fn, "w")
	
		for line in modified_list:
			inventory_modified.write(line)
		
		inventory_modified.close()



	def appendLog(self):
		#INPUT: self.itemspurchased from parseForm()

		fn = os.path.abspath('..') + '/databases/Log.csv'
        	log = open(fn, "a") #Make sure that "a" is the correct mode

		for line in log.readlines():
			entry = log.append(self.itemspurchased) # Not sure if python allows this, otherwise, we need to iterate 

		log.close()



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
		print """<div class = "span12">"""
		print """<div class = "alert alert-block alert-error">"""
		print "<h4>Oops!</h4>"
		print "<p>the username and password you entered did not match our 		records</p>"
		print"</div>"
		print"</div>"

	def printBill(self):
		print "Your Bill: \n" 
		# INPUT: self.itemspurchased from editInventory()
		total_before_tax = 0
		for items in self.itemspurchased:
			price = float(items[2].strip())
			quantity_selected = int(items[1].strip())
			total_before_tax = quantity_selected * price
			gst = total_before_tax * 0.05
			pst = gst * 0.095
	
			
			print "Name, Quantity, Price: \n"
			print items[0] + "," + quantity_selected + "," + price
			print "Total before tax = %f \n" %(total_before_tax)
			print "GST = %f \n" %(gst)
			print "PST = %f \n" %(pst)
			print "Total = %f \n" %(total_before_tax + gst + pst)

			# Provide link back to Catalogue and Home
			print """<a href="catalogue.html">Catalogue</a>"""
			print """<a href="home.html">Home</a> """
			
		

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
