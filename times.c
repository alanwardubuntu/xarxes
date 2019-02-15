
/* calculate minimum times from origin node to all other nodes */

void calculate_times (char *originnode, 
    struct node *current_node,
    struct edge *current_edge) {

    printf ("-> Calculating times from: %s\n", originnode);
    
    struct node *origin = find_node(originnode);
    struct node *auxn;
    struct edge *auxe;
    int changes;
    
    if (origin != NULL) {
        auxn = current_node;
        while (auxn != NULL) {
            if (auxn == origin)
                auxn -> t  = 0.0;
            else
                auxn -> t = INFINITY;
            
            auxn = auxn -> next;  
        }
        
        changes = 1;
        while (changes > 0) {
            changes = 0;
            
            auxe = current_edge;
            while (auxe != NULL) {
                if (auxe -> p1 -> t + auxe -> t1 < auxe -> p2 -> t) {
                    auxe -> p2 -> t = auxe -> p1 -> t + auxe -> t1;
                    changes++;
                }
                
                if (auxe -> p2 -> t + auxe -> t2 < auxe -> p1 -> t) {
                    auxe -> p1 -> t = auxe -> p2 -> t + auxe -> t2;
                    changes++;
                }
                
                auxe = auxe -> next;
            }
        }
        
        auxn = current_node;
        while (auxn != NULL) {
            if (auxn == origin)
                auxn -> cost  = 0.0;
            else
                auxn -> cost = INFINITY;
            
            auxn = auxn -> next;  
        }
        
        changes = 1;
        while (changes > 0) {
            changes = 0;
            
            auxe = current_edge;
            while (auxe != NULL) {
                if (auxe -> p1 -> cost + auxe -> cost1 < auxe -> p2 -> cost) {
                    auxe -> p2 -> cost = auxe -> p1 -> cost + auxe -> cost1;
                    changes++;
                }
                
                if (auxe -> p2 -> cost + auxe -> cost2 < auxe -> p1 -> cost) {
                    auxe -> p1 -> cost = auxe -> p2 -> cost + auxe -> cost2;
                    changes++;
                }
                
                auxe = auxe -> next;
            }
        }
        
        printf ("Node, Long, Lat, Time(hrs), Cost(kg)\n");
        auxn = current_node;
        while (auxn != NULL) {
            printf ("%s,%.1lf,%.1lf,%.1lf,%.1lf\n", auxn -> label, auxn->lon, auxn->lat, auxn -> t, auxn -> cost);
            
            auxn = auxn -> next;
        }
    } else
        fprintf (stderr, "Cannot find origin node labeled: %s\n", originnode);
}


/* calculate minimum route from origin node to target node */

void calculate_route (char *originnode, char *targetnode,
    struct node *current_node,
    struct edge *current_edge) {
    
    printf (SEPARATOR);
    printf ("Best route from %s to %s:\n", originnode, targetnode);
    
    struct node *origin = find_node(originnode);
    struct node *target = find_node(targetnode);
    struct node *auxn = target;
    struct edge *auxe, *chosene;
    
    struct list *list_head, *list_aux;
    
    list_head = NULL;
    while (auxn != origin) {
       
        chosene = NULL;
        auxe = current_edge;

        while (auxe != NULL) {
            if ((auxe->p1 == auxn) && (auxe->t2 + auxe->p2->t == auxn->t)) {
                chosene = auxe;
            }
            if ((auxe->p2 == auxn) && (auxe->t1 + auxe->p1->t == auxn->t)) {
                chosene = auxe;
            }
            auxe = auxe -> next;
        }
        
        if (chosene == NULL) {
            fprintf(stderr, "Cannot find previous node for %s, aborting\n", auxn->label);
            exit (1);
        } else {
        
            list_aux = (struct list *)malloc(sizeof(struct list));
            list_aux -> label = auxn -> label;
            list_aux -> t = auxn -> t;
            list_aux -> lon = auxn -> lon;
            list_aux -> lat = auxn -> lat;
              
            if ((chosene->p1 == auxn) && (chosene->t2 + chosene->p2->t == auxn->t)) {
                auxn = chosene->p2;
                list_aux -> cost = chosene -> cost2; //cost1;
                list_aux -> type = chosene -> type;
                list_aux -> alt = chosene -> p2 -> alt;
                list_aux -> d = chosene -> d * 0.001;
            }
            else if ((chosene->p2 == auxn) && (chosene->t1 + chosene->p1->t == auxn->t)) {
                auxn = chosene->p1;
                list_aux -> cost = chosene -> cost1; //cost2;
                list_aux -> type = chosene -> type;
                list_aux -> alt = chosene -> p1 -> alt;
                list_aux -> d = chosene -> d * 0.001;
            }
            
            list_aux -> acc_cost = 0.0;
            list_aux -> acc_d = 0.0;
            list_aux -> next = list_head;
            list_head = list_aux;
        }
    }


    list_aux = (struct list *)malloc(sizeof(struct list));
    list_aux -> label = origin -> label;
    list_aux -> type = "None";
    list_aux -> t = 0.0;
    list_aux -> cost = 0.0;
    list_aux -> acc_cost = 0.0;
    list_aux -> alt = origin -> alt;    
    list_aux -> d = 0.0;
    list_aux -> acc_d = 0.0;
    list_aux -> lon = origin -> lon;
    list_aux -> lat = origin -> lat;
    list_aux -> next = list_head;
    list_head = list_aux;

    
    double acc_cost = list_head->acc_cost;
    double acc_d = list_head->acc_d;

    printf ("Stage,Distance,Time,StageCost,Cost,Alt,Type,Long,Lat\n");
    while (list_aux != NULL) {
        acc_cost += list_aux -> cost;
        list_aux -> acc_cost = acc_cost;
        acc_d += list_aux -> d;
        list_aux -> acc_d = acc_d;
        printf ("%s,%.1lf,%.1lf,%.1lf,%.1lf,%.1lf,%s,%.3lf,%.3lf\n", list_aux->label ,list_aux->acc_d, list_aux->t, list_aux->cost, list_aux->acc_cost, list_aux->alt, list_aux->type, list_aux->lon, list_aux->lat);
        list_aux = list_aux -> next;
    }
}
