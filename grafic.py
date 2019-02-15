#!/usr/bin/python
# -*- encoding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as mlines

import csv
import sys

filename = "llivia_tort.csv"

if len(sys.argv) > 1:
    filename = sys.argv[1]


# --- read in data from file ---

print ("Reading data from CSV file %s :\n" % filename)

estacions = []
x = []
time = []
stagecost = []
cost = []
alt = []
typ = []
with open(filename) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            print('Reading CSV column names %s ' % row)
            line_count += 1
        else:
            print(row[0])
            estacions.append(row[0])
            x.append(float(row[1].replace(',', '.')))
            time.append(float(row[2].replace(',', '.')))
            stagecost.append(float(row[3].replace(',', '.')))
            cost.append(float(row[4].replace(',', '.')))
            alt.append(float(row[5].replace(',', '.')))
            typ.append(row[6])
            line_count += 1

stagedistance = []
timedistance = []
costdistance = []
for i in range(1, len(x)):
    stagedistance.append(x[i-1])
    stagedistance.append(x[i])
    td = (time[i] - time[i-1]) / (x[i] - x[i-1])
    timedistance.append(td)
    timedistance.append(td)
    cd = (cost[i] - cost[i-1])/ (x[i] - x[i-1])
    costdistance.append(cd)
    costdistance.append(cd)


# plot with various axes scales

fig, ax = plt.subplots(2, 2, sharex=True)


ax[0][0].plot(x, alt, "b")
ax[0][0].set_ylabel("altitud (m)")
ax[0][0].fill_between(x, 0, alt, facecolor='b', alpha=.15)
ax[0][0].grid(True)
ax[0][0].set_title("(a) Perfil")

ax[0][1].plot(x, time, "g")
ax[0][1].set_ylabel("temps acumulat (h)")
ax01b = ax[0][1].twinx()
ax01b.fill_between(stagedistance, 0, timedistance, facecolor='g', alpha=.25)
ax01b.set_ylabel("temps per km (h/km)")
ax[0][1].grid(True)
ax[0][1].set_title("(b) Temps per km i temps acumulat")

ax[1][1].plot(x, cost, "r")
ax[1][1].set_xlabel(u"distància (km)")
ax[1][1].set_ylabel("cost (kg blat)")
ax11b = ax[1][1].twinx()
ax11b.fill_between(stagedistance, 0, costdistance, facecolor='r', alpha=.25)
ax11b.set_ylabel("cost per km (kg blat/km)")
ax[1][1].grid(True)
ax[1][1].set_title("(c) Cost per km i cost accumulat")


#ax[1][0].set_ylabel("cost (mod)")
#ax[1][0].fill_between(x, 0, type, facecolor='r', alpha=.5)


for i in range(0, len(x)):
    ax[1][0].annotate(estacions[i], xy=(x[i], -2.0), rotation='90', va='bottom', size='8')

for i in range(1, len(x)):
    ly, c = 0.0, 'black'
    if (typ[i] == 'RMar'):
        ly, c = 1.0, 'darkblue'
    if (typ[i] == 'RRiu'):
        ly, c = 2.0, 'lightblue'
    if (typ[i] == 'RVia'):
        ly, c = 3.0, 'red'
    if (typ[i] == 'RCam'):
        ly, c = 4.0, 'brown'
    if (typ[i] == 'RMon'):
        ly, c = 5.0, 'black'
    l = mlines.Line2D([x[i-1], x[i]], [ly, ly], color=c)
    ax[1][0].add_line(l)

ax[1][0].grid(False)
ax[1][0].set_title("(d) Tipus de via")
ax[1][0].axis([0.0, max(x), -2.5, 6.0])
ax[1][0].set_xlabel(u"distància (km)")
ax[1][0].get_yaxis().set_visible(False)

#fig.subplots_adjust(hspace=0.3)

#plt.title(filename, size="14")
plt.show()
