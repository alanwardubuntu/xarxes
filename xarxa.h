

#define TRUE (0 == 0)
#define FALSE !TRUE
#define SEPARATOR "-----------------------------------------\n"

/* default file names */

#define DEFAULT_NODE_FILE "nodes.csv"
#define DEFAULT_EDGE_FILE "edges.csv"

#define DEFAULT_GRAPHIC_FILE "output.ps"
#define AUX_GRAPHIC_FILE "output.dot"
#define GRAPHIC_FACTOR 130.0

/* data structures */

typedef struct node {

	char *label;
	double lat, lon, alt;
	double t;
	double cost;
	struct node *next;
} node;

typedef struct edge {

	char *label;
	char *end1, *end2;
	char *type;
	struct node *p1, *p2;
	double d, h, t1, t2, cost1, cost2;
	struct edge *next;
} edge;

typedef struct list {

    char *label;
    char *type;
    double t;
    double cost;
    double acc_cost;
    double d;
    double acc_d;
    double alt;
    double lon, lat;
    
    struct list *next;
} list;


/* route types */

#define TYPES_N 9

char *type_labels[] = {"M", "R", "P", "C", "RMon", "RCam", "RVia", "RRiu", "RMar"};
double type_width[] = {1, 2, 3, 4, 1, 2, 4, 1, 4};
char *type_color[] = {"black", "black", "black", "black", "black", "brown", "red", "blue", "navy"};
double type_vh_down[] = {3000.0, 5000.0, 10000.0, 40000.0, 1000.0, 1600.0, 2000.0, 2510.0, 3700.0};
double type_vh_up[] = {3000.0, 5000.0, 10000.0, 40000.0, 1000.0, 1600.0, 2000.0, 600.0, 3700.0};
double type_vv[] = {500.0, 500.0, 800.0, 1500.0, 500.0, 500.0, 500.0, INFINITY, INFINITY};
double type_cost_up[] = {INFINITY, INFINITY, INFINITY, INFINITY, 4.21, 4.92, 4.92, 0.66, 0.097};
double type_cost_down[] = {INFINITY, INFINITY, INFINITY, INFINITY, 4.21, 4.92, 4.92, 0.33, 0.097};


/* calculation constants */

double r = 6378150.0 / 180.0 * 3.1415926;
double cos42 = 0.743145;


