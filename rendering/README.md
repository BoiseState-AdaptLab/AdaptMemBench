# AdaptLabs Graphing Utility (AGU)

AGU is a python script that utilizes matplotlib to graph custom datasets.

### Requirements

AGU uses python along with [matplotlib] to graph your data

### Usage

First, assuming we have nothing except for the script file, we need to generate a configuration file as such:

```sh
$ python graphing.py --gen_config
```

This will generate for us a graph.config file that has all of the required feilds included in it. From there we can go ahead and graph the default config file like this:

```sh
$ python graphing.py 
```

or (for the purposes of automation or config file specification)

```sh
$ python graphing.py graph.config
```
### Configuration File Contents

The configuration file is pretty self explanatory but the following is an explenation of each of the variables. Also, I would like to point out that there are two equal signs for each parameter, this is to allow white space at the end of each string (all options must be placed inside of the = e.g. =here=).

|Field|Description|
|:----:|:----:|
|TITLE|Title of the graph|
|DISPLAYLEGEND|Show legend on the graph (true or false)|
LEGENDNAMES|Specify the names of the data on the legend|
FILELIST|List the files to be scraped
GRAPHTYPE|Used to set the graph type, 2D, 3DTRISURF, 3DWIRE
CODE|Where are the scraping files located?
NUMTHREADS|How many different sets of data are you planning to graph
SEMILOGX|Log scale for x-axis (setting both x and y to true will result in a loglog graph)
SEMILOGY|Log scale for y-axis (setting both x and y to true will result in a loglog graph)
XAXLABEL|Label for the x-axis
YAXLABEL|Label for the y-axis
XBASE|Minimum value to display for the x-axis
XLIM|Maximum value to display for the x-axis
YBASE|Minimum value to display for the y-axis
YLIM|Maximum value to display for the y-axis
MAJORTICKX|The distance between the bolder and also labeled grid lines on the x-axis
MINORTICKX|The distance between the lighter and unlabeled grid lines on the x-axis
MAJORTICKY|The distance between the bolder and also labeled grid lines on the y-axis
MINORTICKY|The distance between the lighter and unlabeled grid lines on the y-axis
VERTLINES|These are kind of special purpose, used to draw a red vertical line on the graph (usually used for showing where expected values will be)
VERTLINELABELS|Labels for the vertical lines
SHOWFIG|This is used if you want to preview your graph after it has been generated (disable if automating)


**Libraries**

   [matplotlib]: <https://matplotlib.org/>
