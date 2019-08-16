
/* return new empty node */
struct node *new_node() {

	struct node *aux = (struct node *)malloc(sizeof(struct node));
	
	aux -> label = NULL;
	aux -> lat = 0.0;
	aux -> lon = 0.0;
	aux -> alt = 0.0;
	aux -> next = NULL;
	
	return(aux);
}

/* dump nodes, recursively */
void dump_node(struct node *aux) {
	
	if (aux != NULL) {
		printf ("%s, %lf, %lf, %lf\n", aux->label, aux->lat, aux->lon, aux->alt);
		dump_node(aux -> next);
	}
}

/* free a node, recursively */
void free_node(struct node *aux) {

	if (aux != NULL) {
		free_node(aux->next);
		free(aux);
	}
}
