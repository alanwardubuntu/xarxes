

int current_field;
struct node *current_node; 
struct edge *current_edge;

/* callback functions */

static int is_space(unsigned char c) {
  if (c == CSV_SPACE || c == CSV_TAB || c == CSV_QUOTE) return 1;
  return 0;
}

static int is_term(unsigned char c) {
  if (c == CSV_CR || c == CSV_LF) return 1;
  return 0;
}


void cb1n (void *s, size_t len, void *data) { 
	
	char aux[100];
	
	strncpy(aux, s, len);
	aux[len] = '\0';
	if ((len > 0) && (aux[len -1] == CSV_QUOTE))
		aux[len - 1] = '\0';

	switch (current_field) {
	case 0:
		current_node -> label = (char *)malloc(strlen(aux) + 1);
		strcpy(current_node -> label, aux);
		break;
	case 1:
		current_node -> lat = atof(aux);
		break;
	case 2:
		current_node -> lon = atof(aux);
		break;
	case 3:
		current_node -> alt = atof(aux);
		break;
	default:
		fprintf(stderr, "Error reading CSV file, at token '%s'\n", (char *)s);
		exit(2);
	}
	
	current_field = (current_field + 1) % 4;
}

void cb2n (int c, void *data) { 

	struct node *aux;
	
	if ((current_node -> lat != 0.0) &&
		(current_node -> lon != 0.0) &&
		(current_node -> alt != 0.0)) {
		
		aux = new_node();
		aux -> next = current_node;
		current_node = aux;
	}
}


void cb1e (void *s, size_t len, void *data) { 
	
	char aux[100];
	
	strncpy(aux, s, len);
	aux[len] = '\0';
	if ((len > 0) && (aux[len -1] == CSV_QUOTE))
		aux[len - 1] = '\0';

	switch (current_field) {
	case 0:
		current_edge -> label = (char *)malloc(strlen(aux) + 1);
		strcpy(current_edge -> label, aux);
		break;
	case 1:
		current_edge -> end1 = (char *)malloc(strlen(aux) + 1);
		strcpy(current_edge -> end1, aux);
		break;
	case 2:
		current_edge -> end2 = (char *)malloc(strlen(aux) + 1);
		strcpy(current_edge -> end2, aux);
		break;
	case 3:
		current_edge -> type = (char *)malloc(strlen(aux) + 1);
		strcpy(current_edge -> type, aux);
		break;

	default:
		fprintf(stderr, "Error reading CSV file, at token '%s'\n", (char *)s);
		exit(2);
	}
	
	current_field = (current_field + 1) % 4;
}

void cb2e (int c, void *data) { 

	struct edge *aux;
	
	if (strcmp(current_edge -> type, "type") != 0) {
		
		aux = new_edge();
		aux -> next = current_edge;
		current_edge = aux;
	}
}

/* read in data from each csv file */


void read_nodes(char *filename) {
	
	FILE *fp;
	struct csv_parser p;
	char buf[1024];
	size_t bytes_read;
	

	current_node = new_node();
	current_field = 0;
	
  if (csv_init(&p, 0) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(1);
	}

	csv_set_space_func(&p, is_space);
	csv_set_term_func(&p, is_term);
	
	fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "xarxa cannot open file %s, aborting.\n", filename);
		exit (1);
	}
	
  while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
    if (csv_parse(&p, buf, bytes_read, cb1n, cb2n, NULL) != bytes_read) {
      fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
    }
	}
	
	csv_fini(&p, cb1n, cb2n, NULL);
  fclose(fp);
	csv_free(&p);
	
	struct node *aux = current_node -> next;
	current_node -> next = NULL;
	free_node(current_node);
	current_node = aux;
} 


void read_edges(char *filename) {
	
	FILE *fp;
	struct csv_parser p;
	char buf[1024];
	size_t bytes_read;
	

	current_edge = new_edge();
	current_field = 0;
	
  if (csv_init(&p, 0) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(1);
	}

	csv_set_space_func(&p, is_space);
	csv_set_term_func(&p, is_term);
	
	fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "xarxa cannot open file %s, aborting.\n", filename);
		exit (1);
	}
	
  while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
    if (csv_parse(&p, buf, bytes_read, cb1e, cb2e, NULL) != bytes_read) {
      fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
    }
	}
	
	csv_fini(&p, cb1e, cb2e, NULL);
  fclose(fp);
	csv_free(&p);
	
	struct edge *aux = current_edge -> next;
	current_edge -> next = NULL;
	free_edge(current_edge);
	current_edge = aux;
} 

