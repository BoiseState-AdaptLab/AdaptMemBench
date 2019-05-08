#@author Travis Adsitt
#
#This is a python graphing utility for x and y datasets constructed using
#external python modules.

from mpl_toolkits.mplot3d import axes3d
from matplotlib import cm
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
import sys
import random as r
import time
from textwrap import wrap
from inc.conf import Configuration


#This is just a file generation block so that we make a file containing 
#all of the required fields to avoid errors. This generates a graphable
#configuration file.
if(len(sys.argv) > 1 and sys.argv[1] == "--gen_config"):	
	Configuration("").genconf("graph.config")
	sys.exit()

legendColors = ['b','r','g']
legendColors.append(('#5f317f'))
legendColors.append(('#000000'))

legendBW = 0

legendShapes = ["*","P","^","P","s","p","P","*","h","H","+","x","X","D","d","|","_","1","2","3","4","8"]

CONFIG = "graph.config"

if(len(sys.argv) > 1):
	CONFIG = sys.argv[1]

CONFIG = open(CONFIG)

c = Configuration(CONFIG)

#Checks on loaded data
if(c.graphType.upper().find("3D") == -1 and
	c.graphType.upper() != "2D"):
	print("Unrecognized 'GRAPHTYPE' !('3DTRISURF','3DWIRE','2D')")
	sys.exit()

#Build legend items if its needed
if(len(c.legend) < c.numthreads):
	for i in range(c.numthreads - len(c.legend)):
		c.legend.append("Thread " + str(i))


#Draw grid
#Code from:
#https://stackoverflow.com/questions/24943991/change-grid-interval-and-specify-tick-labels-in-matplotlib
fig = plt.figure()
ax = fig.add_subplot(111,projection='3d') if c.graphType.upper().find('3D') != -1 else fig.add_subplot(1,1,1)


major_ticksx = np.arange(0,c.xaxlim,c.maxtickspreadX)
minor_ticksx = np.arange(0,c.xaxlim,c.mintickspreadX)
major_ticksy = np.arange(0,c.yaxlim,c.maxtickspreadY)
minor_ticksy = np.arange(0,c.yaxlim,c.mintickspreadY)

ax.set_xticks(major_ticksx)
ax.set_xticks(minor_ticksx, minor=True)
ax.set_yticks(major_ticksy)
ax.set_yticks(minor_ticksy, minor=True)

ax.grid(which='both')

ax.grid(which='minor', alpha=0.2)
ax.grid(which='major', alpha=0.5)
#End code citation

#Set axis limits
plt.xlim(c.xbase,c.xaxlim)
plt.ylim(c.ybase,c.yaxlim)


#plt.gca().invert_yaxis()
#plt.gca().invert_xaxis()

#Draw Vertical Lines
if c.graphType.upper().find('3D') == -1:
	for cL in range(len(c.lines)):
		linest = '-'
		if(cL<len(c.lineStyles)):
			linest = c.lineStyles[cL]
		if(c.bw.upper() == 'TRUE'):
			plt.axvline(x=float(c.lines[cL]),color=(0.5,0.5,0.5),linestyle=linest)
		else:
			plt.axvline(x=float(c.lines[cL]),color='r',linestyle=linest)
#		plt.text(float(c.lines[cL]), (len(c.lineLabels[cL])*1), c.lineLabels[cL],fontweight='bold', rotation = 90, verticalalignment = 'bottom')
		plt.text(float(c.lines[cL]), 0.1, c.lineLabels[cL],fontweight='bold', rotation = 90, verticalalignment = 'bottom')

cC = 0

#Alright so the following is the coolest part about this graphing script(IMO)
#if there are files available to parse we open them and run the module selected
#for that file... cool right? This seperates the "scraping" script from the
#graphing script.
if c.files[0] != '':
	if c.graphType.upper().find('3D') == -1:
		x = [[]for i in range(c.numthreads)]
		y = [[]for i in range(c.numthreads)]	
		for i in range(0,len(c.files)):
			print("Loading file: " + c.files[i])
			temp = 0
			with open(c.files[i]) as f:
				linenum = 0
				for line in f:
					linenum = linenum + 1
					#Execute the scraping script
					exec(open(c.codeFiles[i if i<len(c.codeFiles) else (len(c.codeFiles)-1)]).read())
		#This is taking the information we stored from the scraping
		#and plotting it using matplotlibs .plot() function.
		for t in range(c.numthreads):	
			#We want RGB to be the primary colors however if there is
			#more data we dont want to leave it out so we select
			#a random color.
			#print("X len: "+str(len(x))+" Y len: "+str(len(y)))
			#print("Current color index: " + str(cC) + " Color Array len: " + str(len(legendColors)))
			if(t>=len(legendColors)):
				time.sleep(1)
				legendColors.append((r.random(),r.random(),r.random()))
			#if(t>=len(legendShapes) and c.bw.upper() == 'TRUE'):
			#	legendShapes.append(t,0,t)
			if(c.graphType.upper() == '2D'):
				if(False):
					colorStep = 100/c.numthreads
					color = ((t * colorStep)%100)/100
					plt.plot(x[t],y[t],'.',color=(0,0,0),marker=legendShapes[t],label=c.legend[t])	
				else:
					plt.plot(x[t],y[t],'.',color=legendColors[t],marker=legendShapes[t],label=c.legend[t])
			cC = cC + 1
	else:
		x = []
		y = []
		z = []
		wire = c.graphType.upper().find('WIRE') != -1
		for i in range(0,len(c.files)):
			print("Loading file: " + c.files[i])
			temp = 0
			with open(c.files[i]) as f:
				for line in f:
					#Execute the scraping script
					exec(open(c.codeFiles[i if i<len(c.codeFiles) else (len(c.codeFiles)-1)]).read())
					if temp == 1 and wire:
						ax.plot_wireframe(x,y,z)
						temp = 0
						x = []
						y = []
						z = []
			#This is taking the information we stored from the scraping
			#and plotting it using matplotlibs .plot() function.
		if c.graphType.upper().find('TRISURF') != -1:
			surf = ax.plot_trisurf(x,y,z,cmap=cm.jet,linewidth=0.2,antialiased=True)

if (c.custLineFiles[0] != '') and (c.graphType.upper() != '2D'):
	for i in range(len(c.custLineFiles)):
		x = []
		y = []
		z = []
		with open(c.custLineFiles[i]) as f:
			for line in f:
				exec(open(c.custLineCodeFiles[i if i<len(c.custLineCodeFiles) else (len(c.custLineCodeFiles)-1)]).read())
		ax.plot(x,y,z)

#We may or may not want a legend displayed, check for that here.
if c.dispLegend.lower() == "true":
	handles, labels = ax.get_legend_handles_labels()
	ax.legend(handles, labels)



#Label axis
plt.ylabel(c.yLabel)
plt.xlabel(c.xLabel)
if c.graphType.upper().find('3D') != -1:
	ax.set_zlabel(c.zLabel)

#Graph title
ax.set_title("\n".join(wrap(c.title,55)))

#Set style 
plt.style.use('ggplot')

#Output saving figure
plt.savefig("graph.png")
#If we specified that we want to see the graph then we do that here. It is 
#important to note that we do this after saving the figure, it was discovered
#that the plot will not save if it has been shown. 
if c.showFig.lower() == "true":
	plt.show()
