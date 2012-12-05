i#!/usr/local/bin/python

import cgi
import os

class Purchase:

	def __init__(self):
		self.username = ""
		self.password = ""
		self.light_price = ""
		self.mid_price = ""
		self.heavy_price = ""
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
<<<<<<< HEAD:cgi_bin/Purchase.py
			heavy_quantity = form["heavy-quantity"].value.strip()
=======
			self.heavy_quantity = form["heavy-quantity"].value.strip()
>>>>>>> 015f212252faff85819526c921dc17f3190357e1:cgi_bin/Purchase.py
			self.heavy_price = 30
			self.itemspurchased["heavyweight"] = heavy_quantity

	# We create a tuple to store the information
	#self.temspurchased = {(id1, quantity1,price1), (id2, quantity2,price2), (id3,quantity3,price3), ("username", self.username)}

		



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

		modified_list = []
		quantity_in_stock = 0
		for line in inventory.readlines():
			entry = line.split(',')
			for items in self.itemspurchased:
				if(items[0] == entry[0]):	

					quantity_in_stock = int(entry[3])
 
					quantity_selected = items[1] 				

					if quantity_selected > quantity_in_stock:
						print "We only have " + quantity_in_stock + " rides left \n"
						print "Please choose another quantity"
						exit()
					else:
						quantity_in_stock = quantity_in_stock - quantity_selected
						#quantity_and_price = (items[1], entry[4])					


			modified_list.append("%s,%s,%s,%s,%s" % (entry[0], entry[1], entry[2], quantity_in_stock, entry[4]))

		inventory.close() 

		# Open file to write modified information
		inventory_modified = open(fn, "w")
	
		for line in modified_list:
			inventory_modified.write(line)
		
		inventory_modified.close()



	def appendLog(self):
		#INPUT: self.itemspurchased from parseForm()

		fn = os.path.abspath('..') + '/databases/Log.csv'
        	log = open(fn, 'a') #Make sure that "a" is the correct mode
		log.write("%s" % self.itemspurchased)

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
		print """<div class ="span6 well" style = "float:none; margin:0 auto;">
			     <h2> Your Bill:</h2>
			     <h4>"""+self.username+ """</h4>
			     <table class = "table table-striped">
				  "<th>Item</th><th>Quantity:</th><th>Price</th><th>due</th>"""
			  	
		# INPUT: self.itemspurchased from editInventory()
		total_before_tax = 0
		if self.itemspurchased.has_key("lightweight"):
			price =int(self.itemspurchased["lightweight"])*self.light_price
			print "<tr><td>lightweight</td><td>"+self.itemspurchased["lightweight"]+"</td><td>$"+self.light_price+"</td><td>"+price+"</td></tr>"
			total_before_tax += price
		if self.itemspurchased.has_key("midweight"):
			price =self.itemspurchased["midweight"].value*self.mid_price
			print "<tr><td>midweight</td><td>"+self.itemspurchased["midweight"]+"</td><td>$"+self.mid_price+"</td><td>"+price+"</td></tr>"
			total_before_tax += price
		if self.itemspurchased.has_key("heavyweight"):
			price =int(self.itemspurchased["heavyweight"])*self.heavy_price
			print "<tr><td>heavyweight</td><td>"+str(self.itemspurchased["heavyweight"])+"</td><td>$"+str(self.heavy_price)+"</td><td>"+str(price)+"</td></tr>"
			total_before_tax += price
		gst = total_before_tax*0.05
		pst = gst * 0.095
		print "</table>"
		print "GST: $"+str(gst)
		print "PST: $"+str(pst)
		print "TOTAL:"+str(total_before_tax+gst+pst)
			
		

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
