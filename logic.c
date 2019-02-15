
/* find a node from label, if not found return NULL */

struct node *find_node_rec(char *label, struct node *top) {

	if (top != NULL) {
		if (strcmp(top->label, label) == 0)
			return (top);
		else
			return (find_node_rec(label, top -> next));
	} else
		return (NULL);
}

struct node *find_node(char *label) {

	struct node *res = NULL;
	
	return (find_node_rec(label, current_node));
}


/* find type index from label */

int find_type_index(char *label) {

	int res = -1;
	
	for (int i = 0; (i < TYPES_N) && (res < 0); i++) 
		if (strcmp(type_labels[i], label) == 0)
			res = i;
	
	return (res);
}

 
/* double absolute value */

double dabs(double x) {

	return (x >= 0.0 ? x : -x);
} 
 
 
/* calculate distance and time for single edge */

void calculate_edge(struct edge *edge) {

	double x1 = edge->p1->lon;
	double y1 = edge->p1->lat;
	double x2 = edge->p2->lon;
	double y2 = edge->p2->lat;
	
	double graus_x = dabs(x1 - x2);
	double graus_y = dabs(y1 - y2);
	double d_x = graus_x * r * cos42;
	double d_y = graus_y * r;
	double d = sqrt(d_x * d_x + d_y * d_y);
	double h = dabs(edge -> p1 -> alt - edge -> p2 -> alt);
	
	edge -> d = d;
	edge -> h = h;
	
	int index = find_type_index(edge -> type);
	
	double t1, t2, t1_h, t2_h;
	double cost1, cost2;
	
	if (edge->p1->alt >= edge->p2->alt) {
	    t1_h = d / type_vh_down[index];
	    t2_h = d / type_vh_up[index];
	    t1 = d / type_vh_down[index] + h / type_vv[index];
	    t2 = d / type_vh_up[index] + h / type_vv[index];
	    cost1 = d * type_cost_down[index] * 0.001 * t1 / t1_h;
	    cost2 = d * type_cost_up[index] * 0.001 * t2 / t2_h;
	} else {
	    t1_h = d / type_vh_up[index];
	    t2_h = d / type_vh_down[index];
	    t1 = d / type_vh_up[index] + h / type_vv[index];
	    t2 = d / type_vh_down[index] + h / type_vv[index];
	    cost1 = d * type_cost_up[index] * 0.001 * t1 / t1_h;
	    cost2 = d * type_cost_down[index] * 0.001 * t2 / t2_h;
	}
	edge -> t1 = t1;
	edge -> t2 = t2;
	edge -> cost1 = cost1;
	edge -> cost2 = cost2;
}


/* verify edge coherence, recursive */

int verify_and_calculate_edge(struct edge *edge) {

	int correct;
	
	if (edge == NULL) 
		return (TRUE);
	else {
		
		struct node *node1 = find_node(edge -> end1);
		struct node *node2 = find_node(edge -> end2);
		
		correct = (node1 != NULL) && (node2 != NULL);
		
		if (correct) {
			edge -> p1 = node1;
			edge -> p2 = node2;
			calculate_edge(edge);
		} else
			fprintf (stderr, "Cannot find endpoints for edge %s (%s -> %s) \n", edge -> label, edge -> end1, edge -> end2);
		
		return (verify_and_calculate_edge(edge -> next));
	}
}

/* verify graph coherence */

void verify_graph() {

	if (verify_and_calculate_edge(current_edge))
		printf ("Edges verified OK\n");
	else {
		fprintf (stderr, "Cannot continue, aborting\n");
		exit (2);
	}
}
