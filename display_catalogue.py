
def feedLines
	import os
	fn = os.path.join(os.path.dirname(__file__), 'databases/Inventory.csv')
	catalogue = open(fn,'r')

	for line in catalogue.readlines():
		entry = line.split(',')

def formatHTML(entry)
	
