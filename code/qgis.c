
/* dump network data in format suitable for qGIS */

void dump_qgis(struct node *current_node, struct edge *current_edge, char *qgisfile){

    FILE *fp;
    char filename[80];
    struct node *np;
    struct edge *ep;
    
    /* write main file */
    sprintf(filename, "%s.csv", qgisfile);
    printf ("Writing CSV file %s\n", filename);
    
    fp = fopen(filename, "wb");
    fprintf(fp, "long1,lat1,long2,lat2,geom\n");
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "type") != 0) 
            fprintf (fp, "%.3f,%.3f,%.3f,%.3f,\"LINESTRING(%.3f %.3f,%.3f %.3f)\"\n", ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat, ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat);
        
        ep = ep->next; 
    }
    fclose(fp);
    
    
    /* write RMon file */
    sprintf(filename, "%s-mon.csv", qgisfile);
    printf ("Writing CSV file %s\n", filename);
    
    fp = fopen(filename, "wb");
    fprintf(fp, "long1,lat1,long2,lat2,geom\n");
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "RMon") == 0) 
            fprintf (fp, "%.3f,%.3f,%.3f,%.3f,\"LINESTRING(%.3f %.3f,%.3f %.3f)\"\n", ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat, ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat);
        
        ep = ep->next; 
    }
    fclose(fp);
       
    /* write RCam file */
    sprintf(filename, "%s-cam.csv", qgisfile);
    printf ("Writing CSV file %s\n", filename);
    
    fp = fopen(filename, "wb");
    fprintf(fp, "long1,lat1,long2,lat2,geom\n");
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "RCam") == 0) 
            fprintf (fp, "%.3f,%.3f,%.3f,%.3f,\"LINESTRING(%.3f %.3f,%.3f %.3f)\"\n", ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat, ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat);
        
        ep = ep->next; 
    }
    fclose(fp);
       
    /* write RVia file */
    sprintf(filename, "%s-via.csv", qgisfile);
    printf ("Writing CSV file %s\n", filename);
    
    fp = fopen(filename, "wb");
    fprintf(fp, "long1,lat1,long2,lat2,geom\n");
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "RVia") == 0) 
            fprintf (fp, "%.3f,%.3f,%.3f,%.3f,\"LINESTRING(%.3f %.3f,%.3f %.3f)\"\n", ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat, ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat);
        
        ep = ep->next; 
    }
    fclose(fp);
       
    /* write RRiu file */
    sprintf(filename, "%s-riu.csv", qgisfile);
    printf ("Writing CSV file %s\n", filename);
    
    fp = fopen(filename, "wb");
    fprintf(fp, "long1,lat1,long2,lat2,geom\n");
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "RRiu") == 0) 
            fprintf (fp, "%.3f,%.3f,%.3f,%.3f,\"LINESTRING(%.3f %.3f,%.3f %.3f)\"\n", ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat, ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat);
        
        ep = ep->next; 
    }
    fclose(fp);
       
    /* write RMar file */
    sprintf(filename, "%s-mar.csv", qgisfile);
    printf ("Writing CSV file %s\n", filename);
    
    fp = fopen(filename, "wb");
    fprintf(fp, "long1,lat1,long2,lat2,geom\n");
    
    ep = current_edge;
    while (ep != NULL) {
        if (strcmp(ep->type, "RMar") == 0) 
            fprintf (fp, "%.3f,%.3f,%.3f,%.3f,\"LINESTRING(%.3f %.3f,%.3f %.3f)\"\n", ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat, ep->p1->lon, ep->p1->lat, ep->p2->lon, ep->p2->lat);
        
        ep = ep->next; 
    }
    fclose(fp);
}
