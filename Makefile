
all:
	rm -f xarxa
	gcc xarxa.c -o xarxa -lcsv -lm
#	./xarxa -n xarxa_nodus.csv -e xarxa_camins.csv -g xarxa.png -o La_Seu
	./xarxa -n xarxa_nodus.csv -e xarxa_camins.csv -o Madriu

llivia:
	rm -f xarxa
	gcc xarxa.c -o xarxa -lcsv -lm
	./xarxa -n xarxa_nodus.csv -e xarxa_camins.csv -o Llivia -t Tortosa

graph:
	./xarxa -n xarxa_nodus.csv -e xarxa_camins.csv -g xarxa.pdf

qgis:
	rm -f xarxa
	gcc xarxa.c -o xarxa -lcsv -lm
	./xarxa -q xarxa_qgis -n xarxa_nodus.csv -e xarxa_camins.csv
	cp xarxa_qgis*.csv ~/gis/
	cp xarxa_nodus.csv ~/gis/
