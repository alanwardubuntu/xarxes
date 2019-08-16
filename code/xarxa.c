
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <csv.h>
#include <string.h>
#include <math.h>


#include "xarxa.h"
#include "nodes.c"
#include "edges.c"
#include "csv.c"
#include "qgis.c"
#include "logic.c"
#include "graphic.c"
#include "times.c"


/* print usage and quit */
void do_usage() {

	fprintf(stderr, "Usage\n\txarxa [-y] [-n <node CSV file>] [-e <edge CSV file>] [-g graphic PNG file>] [-o <origin node> [-t <destination node>] ]\n\n");
	fprintf(stderr, "\t-y List route types\n"); 
	fprintf(stderr, "\t-d Dump nodes and edges on screen\n"); 
	fprintf(stderr, "\t-q Dump nodes and edges in format for qGIS\n"); 
	fprintf(stderr, "\tIf the -q option is set, an output CSV file must be specified\n");
	fprintf(stderr, "\tIf the -n option is not set, node file name defaults to '%s'\n", DEFAULT_NODE_FILE);
	fprintf(stderr, "\tIf the -e option is not set, edge file name defaults to '%s'\n", DEFAULT_EDGE_FILE);
	fprintf(stderr, "\tIf the -g option is set, an output PNG file must be specified\n");
	fprintf(stderr, "\tIf the -o option is set, a node for the origin of distance calculations must be specified\n");
	fprintf(stderr, "\tIf the -t option is set, a node for the target of distance calculations must be specified\n");
	fprintf(stderr, "\n");
	
	exit(0);
}

/* dump route types */
void do_print_types() {

	int i;
	
	printf ("Route types supported in xarxa:\n");
	for (i = 0; i < TYPES_N; i++)
		printf ("-> %s: vh=%.2lf/%.2lf  vv=%.2lf  \n", type_labels[i], type_vh_up[i], type_vh_down[i], type_vv[i]);
	
	printf ("\n");
	printf (SEPARATOR);
}

/* main program */
int main(int argc, char *argv[]) {
	
	printf ("xarxa\n");
	
	// parse arguments and output files
	char *qgisfile = NULL;
	char *nodefile = DEFAULT_NODE_FILE;
	char *edgefile = DEFAULT_EDGE_FILE;
    char *graphicfile = DEFAULT_GRAPHIC_FILE;
    char *originnode = NULL;
    char *targetnode = NULL;
    
	int flag_dump_types = FALSE;
	int flag_dump_qgis = FALSE;
	int flag_dump_data = FALSE;
    int flag_output_graphic = FALSE;
    int flag_calculate_times = FALSE;
    int flag_calculate_route = FALSE;
    
	int c;
	
	
	opterr = 0;
	while ((c = getopt(argc, argv, "ydhq:n:e:g:o:t:")) != -1)
		switch (c) {
			case 'y':
				flag_dump_types = TRUE; break;
			case 'd':
				flag_dump_data = TRUE; break;
			case 'h':
				do_usage(); break;
			case 'q':
				flag_dump_qgis = TRUE;
				qgisfile = optarg; break;
			case 'n':
				nodefile = optarg; break;
			case 'e':
				edgefile = optarg; break;
			case 'g':
                flag_output_graphic = TRUE;
				graphicfile = optarg; break;
			case 'o':
                flag_calculate_times = TRUE;
                originnode = optarg; break;
			case 't':
                flag_calculate_times = TRUE;
                flag_calculate_route = TRUE;
                targetnode = optarg; break;
			default:
				do_usage();
		}
	
	printf (SEPARATOR);
	
	if (flag_dump_types) 
		do_print_types();
	
	printf ("-> node file = %s\n", nodefile);
	printf ("-> edge file = %s\n", edgefile);

    if (flag_output_graphic)
    	printf ("-> output graphic file = %s\n", graphicfile);
	
	read_nodes(nodefile);
	read_edges(edgefile);
	
	if (flag_dump_data) {
    	printf (SEPARATOR);
		dump_node(current_node);
		dump_edge(current_edge);
	}
		
	printf (SEPARATOR);
	
	verify_graph();
	
    if (flag_dump_qgis) {
        printf (SEPARATOR);
    	printf ("-> output qGIS file = %s\n", qgisfile);
    	dump_qgis(current_node, current_edge, qgisfile);
    }

	if (flag_dump_data) {
	    printf (SEPARATOR);
		dump_edge_data(current_edge);
	}	

    if (flag_output_graphic) 
        create_graphic(graphicfile, edgefile);
	
	if (flag_calculate_times) {
	    printf (SEPARATOR);
	    if (originnode != NULL) {
    	    calculate_times(originnode, current_node, current_edge);
    	    if (flag_calculate_route)
    	        if (targetnode != NULL)
    	            calculate_route(originnode, targetnode, current_node, current_edge);
    	        else
    	            fprintf(stderr,"Target node not specified, cannot calculate route\n");
    	} else
    	    fprintf(stderr,"Origin node not specified, cannot calculate times\n");
	}
	
	printf (SEPARATOR);
	
	return(0);
}
