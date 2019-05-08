

class Configuration:
	def __init__(self, fileO):
		valid = True
		
		
		conitems = {'KEY':'VALUE'}
		
		#This is going through the config file and loading in any options 
		#that are stored there # signify a comment, and = signify there
		#is an option on the line
		if valid:
			for line in fileO:
				if line.find("#") == -1 and line.find("$") != -1:
					line = line.split("$")
					conitems[line[0]] = line[1]
			
			#Loading in all of the relevant dictionary items included inthe dictionary
			self.lines = conitems['VERTLINES'].split(",")
			self.lineLabels = conitems['VERTLINELABELS'].split(",")
			self.lineStyles = conitems['VERTLINESTYLES'].split(",") if ('GRAPHTYPE' in conitems) else []
			self.custLineFiles = conitems['CUSTOMLINEFILES'].split(",") if ('CUSTOMLINEFILES' in conitems) else []
			self.custLineCodeFiles = conitems['CUSTOMLINECODEFILES'].split(",") if ('CUSTOMLINECODEFILES' in conitems) else []
			self.graphType = conitems['GRAPHTYPE'] if ('GRAPHTYPE' in conitems) else ""
			self.files = conitems['FILELIST'].split(",")
			self.codeFiles = conitems['CODE'].split(",")
			self.xaxlim = float(conitems['XLIM'])
			self.yaxlim = float(conitems['YLIM'])
			self.zaxlim = float(conitems['ZLIM']) if ('ZLIM' in conitems) else 0
			self.xbase = float(conitems['XBASE'])
			self.ybase = float(conitems['YBASE'])
			self.zbase = float(conitems['ZBASE']) if ('ZBASE' in conitems) else 0
			self.maxtickspreadX = float(conitems['MAJORTICKX'])
			self.mintickspreadX = float(conitems['MINORTICKX'])
			self.maxtickspreadY = float(conitems['MAJORTICKY'])
			self.mintickspreadY = float(conitems['MINORTICKY'])
			self.maxtickspreadZ = float(conitems['MAJORTICKZ']) if ('MAJORTICKZ' in conitems) else 0
			self.mintickspreadZ = float(conitems['MINORTICKZ']) if ('MINORTICKZ' in conitems) else 0
			self.numthreads = int(conitems['NUMTHREADS'])
			self.dispLegend = conitems['DISPLAYLEGEND']
			self.legend = conitems['LEGENDNAMES'].split(",")
			self.bw = conitems['BW'] if ('BW' in conitems) else 'False'
			self.title = conitems['TITLE']
			self.yinv = conitems['XINV']
			self.xinv = conitems['YINV']
			self.yLabel = conitems['YAXLABEL']
			self.xLabel = conitems['XAXLABEL']
			self.zLabel = conitems['ZAXLABEL'] if ('ZAXLABEL' in conitems) else 'Default Z Label'
			self.showFig = conitems['SHOWFIG']
	def printConf():
		#Announce to the user what they have selected
		print("X axis limit set to " + str(self.xaxlim))
		
		print("Y axis limit set to " + str(self.yaxlim))
		
		print("Number of code files counted: " + str(len(self.codeFiles)))
		
		for i in self.codeFiles:
			print("     File: " + i)
		print("Number of data files counted: " + str(len(self.files)))
		
		for i in self.files:
			print("     File: " + i)
		
		if(len(self.codeFiles)<len(self.files)):
			print("Fewer code files than data files, all remaining data files\nwill be run using the codefile last on the list!")
		
		if(self.dispLegend.lower =="true"):
			print("Legend is going to be displayed!")
			print("Number of legend items counted: " + str(len(self.legend)))
		
		if(self.graphType.upper()=='2D'):
			print("Graphtype set to 2D!")
			print("     2 data arrays(x[] y[]) expected to be loaded, and sizes should be equal!")
		if(self.graphType.upper().find('3D') != -1):
			print("Graphtype set to 3D!")
			print("     3 data arrays(x[] y[] z[]) expected to be loaded, and sizes should be equal!")
	def genconf(filename):
		f = open(filename,"w+")
		
		f.write("TITLE=Default Title=\n")
		f.write("DISPLAYLEGEND=True=\n")
		f.write("LEGENDNAMES=Legend 1,Legend 2=\n")
		f.write("FILELIST==\n")
		f.write("CODE==\n")
		f.write("GRAPHTYPE=2D=\n")
		f.write("BW=False=\n")
		f.write("NUMTHREADS=0=\n")
		f.write("XAXLABEL=Default X Axis Label=\n")
		f.write("YAXLABEL=Default Y Axis Label=\n")
		f.write("ZAXLABEL=Default Z Axis Label=\n")
		f.write("XBASE=0=\n")
		f.write("XLIM=5=\n")
		f.write("YBASE=0=\n")
		f.write("YLIM=5=\n")
		f.write("XINV=False=\n")
		f.write("YINV=False=\n")
		f.write("ZINV=False=\n")
		f.write("MAJORTICKX=1=\n")
		f.write("MINORTICKX=0.5=\n")
		f.write("MAJORTICKY=1=\n")
		f.write("MINORTICKY=0.5=\n")
		f.write("CUSTOMLINEFILES==\n")
		f.write("CUSTOMLINECODEFILES==\n")
		f.write("VERTLINES=1,2,3=\n")
		f.write("VERTLINESTYLES=--,-,-.")
		f.write("VERTLINELABELS=Vert Line 1,Vert Line 2,Vert Line 3=\n")
		f.write("SHOWFIG=True=\n")
		
		f.close()
		
		print("graph.config created!")
		sys.exit()







