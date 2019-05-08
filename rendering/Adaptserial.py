if(line.find("WSS(MiB)")!=-1):
	currLine = line.split(",")
	wss = 0
	bw = 0
	draw = 0
	for item in currLine:
		if(item.find("WSS(MiB)")!=-1):
			wss = float(item.split(":")[1])
		if(item.find("CumulativeMemoryBandwidth(GiB/s)")!=-1):
			bw = float(item.split(":")[1])
		if(wss>0 and bw>0):
			x[i].append(wss)
			y[i].append(bw)
			draw = 1
