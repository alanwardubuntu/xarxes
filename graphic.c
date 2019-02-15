
/* create graphic and write to file
   also run external command 'dot' from
   graphviz package */

void create_graphic(char *graphicfile, char *edgefile) {

    FILE *fp;
    struct node *np;
    struct edge *ep;
    int index;
    int penwidth;
    char *pencolor;
    
    printf ("Writing temp file %s\n", AUX_GRAPHIC_FILE);
    
    fp = fopen(AUX_GRAPHIC_FILE, "wb");
    fprintf (fp, "graph D {\n");
    
    np = current_node;
    while (np != NULL) {
        fprintf( fp, "%s [ label = %s\n pos = \"%lf,%lf!\"\n]\n", np->label, np->label, GRAPHIC_FACTOR*np->lon, GRAPHIC_FACTOR*np->lat);
        np = np->next;
    }
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "type") != 0) {
            index = find_type_index(ep -> type);
            penwidth = type_width[index];
            pencolor = type_color[index];
            
            fprintf (fp, "%s -- %s [label = \"%.1f/%.1f h, %.1lf/%.1lf kg (%s)\", penwidth=%d, color=%s]\n", ep->end1, ep->end2, ep->t1, ep->t2, ep->cost1, ep->cost2, ep->type, penwidth, pencolor);
        }
        
        ep = ep->next; 
    }
    
    fprintf(fp, "fontsize = 14\nlabel = \"%s\"\n", edgefile);
    fprintf(fp, "}\n");
    fclose(fp);
    
    printf ("Converting %s to %s\n", AUX_GRAPHIC_FILE, graphicfile);
    
    char command[1024];
    sprintf(command, "dot -Kfdp -n -Tpdf -o %s %s ", graphicfile, AUX_GRAPHIC_FILE);
    system(command);
    
    //printf ("Removing temp file %s\n", AUX_GRAPHIC_FILE);
    //sprintf(command, "rm -f %s ", AUX_GRAPHIC_FILE);
    //system(command);
}
