#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef enum parking_param_tag {id, occupancy, revenue} parking_param;
typedef enum vehicle_param_tag {parkings_done, amount_paid} vehicle_param;

typedef struct parking_tag
{
    int pspace_id;
    int status;
    float revenue;
    int occupancy;
    struct parking_tag *next;
    struct parking_tag *prev;
}Parking;

typedef struct vehicle_tag
{
    char vehicle_number[20];
    char owner_name[100];
    int date_arr; //ddmmyy
    int time_arr; // hhmm
    int date_dep;
    int time_dep;
    int parking_hours;
    int pspace_alloted; //0 if not alloted
    int membership; //0 for regular(<100hrs), 1 for premium(100hrs< <=200hrs), 2 for gold(>200hrs)
    float amount;
    int parkings_done;
    struct vehicle_tag *next;
}Vehicle;

//Sorting Parking

Parking* merge_parking_id(Parking *head1,Parking *head2){
    Parking *p1=head1;
    Parking *p2=head2;
    Parking *result;
    Parking *tail;

    if(p1->pspace_id < p2->pspace_id){
        result=p1;
        tail=p1;
        p1=p1->next;
    }
    else{
        result=p2;
        tail=p2;
        p2=p2->next;
    }
      
    while(p1!=NULL && p2!=NULL){
          
        if(p1->pspace_id < p2->pspace_id){
            tail->next=p1;
            p1->prev=tail;
            tail=p1;
            p1=p1->next;
        }
        else{
            tail->next=p2;
            p2->prev=tail;
            tail=p2;
            p2=p2->next;
        }
          
    }

    if(p1!=NULL){
        tail->next=p1;
        p1->prev=tail;
    }
    if(p2!=NULL){
        tail->next=p2;
        p2->prev=tail;
    }
    
    return result;   
}

Parking* merge_parking_occupancy(Parking *head1,Parking *head2){
    Parking *p1=head1;
    Parking *p2=head2;
    Parking *result;
    Parking *tail;

    if(p1->occupancy > p2->occupancy){
        result=p1;
        tail=p1;
        p1=p1->next;
    }
    else{
        result=p2;
        tail=p2;
        p2=p2->next;
    }
      
    while(p1!=NULL && p2!=NULL){
          
        if(p1->occupancy > p2->occupancy){
            tail->next=p1;
            p1->prev=tail;
            tail=p1;
            p1=p1->next;
        }
        else{
            tail->next=p2;
            p2->prev=tail;
            tail=p2;
            p2=p2->next;
        }
          
    }

    if(p1!=NULL){
        tail->next=p1;
        p1->prev=tail;
    }
    if(p2!=NULL){
        tail->next=p2;
        p2->prev=tail;
    }
    
    return result;   
}

Parking* merge_parking_revenue(Parking *head1,Parking *head2){
    Parking *p1=head1;
    Parking *p2=head2;
    Parking *result;
    Parking *tail;

    if(p1->revenue > p2->revenue){
        result=p1;
        tail=p1;
        p1=p1->next;
    }
    else{
        result=p2;
        tail=p2;
        p2=p2->next;
    }
      
    while(p1!=NULL && p2!=NULL){
          
        if(p1->revenue > p2->revenue){
            tail->next=p1;
            p1->prev=tail;
            tail=p1;
            p1=p1->next;
        }
        else{
            tail->next=p2;
            p2->prev=tail;
            tail=p2;
            p2=p2->next;
        }
          
    }

    if(p1!=NULL){
        tail->next=p1;
        p1->prev=tail;
    }
    if(p2!=NULL){
        tail->next=p2;
        p2->prev=tail;
    }
    
    return result;   
}

Parking* get_mid_parking(Parking* par_head) {
    
    Parking* slow = par_head;
    Parking* fast = par_head->next->next;

    while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
        }
    }

    Parking* mid = slow->next;
    mid->prev = NULL;
    slow->next = NULL; 
    return mid;
}

Parking* merge_sort_parking(Parking* par_head, parking_param parameter){
    Parking *temp=par_head;
    Parking *retnode;
    if(par_head == NULL || par_head->next==NULL){
        retnode = par_head;
    }
    if (par_head->next!=NULL && par_head!=NULL){
        Parking *mid=get_mid_parking(temp);
        Parking *left= merge_sort_parking(temp,parameter);
        Parking *right=merge_sort_parking(mid,parameter);
        if(parameter == id)
        {
            retnode = merge_parking_id(left,right);
        }
        else if(parameter == occupancy)
        {
            retnode = merge_parking_occupancy(left,right);
        }
        if(parameter == revenue)
        {
            retnode = merge_parking_revenue(left,right);
        }
    }
    return retnode;
}

//Sorting Vehicle

Vehicle*get_mid_Vehicle(Vehicle*veh_temp){
    Vehicle*slow=veh_temp;
    Vehicle*fast=veh_temp->next->next;
    while(fast!=NULL){
        slow=slow->next;
        fast=fast->next;
        if(fast!=NULL){
            fast=fast->next;
        }
    }
    Vehicle*mid=slow->next;
    slow->next=NULL;
    return mid; 
}

Vehicle*merge_vehicle_parkings_done(Vehicle*head1,Vehicle*head2){
    Vehicle*p1=head1;
    Vehicle*p2=head2;
    Vehicle*result;
    Vehicle*tail;
    if(p1->parkings_done > p2->parkings_done){
        result=p1;
        tail=p1;
        p1=p1->next;
    }
    else{
        result=p2;
        tail=p2;
        p2=p2->next;
    }
    while(p1!=NULL && p2!=NULL){
        
        if(p1->parkings_done > p2->parkings_done){
            tail->next=p1;
            tail=p1;
            p1=p1->next;
            
        }
        else{
            tail->next=p2;
            tail=p2;
            p2=p2->next;
        }
        
    }
    if(p1!=NULL){
        tail->next=p1;
    }
    if(p2!=NULL){
        tail->next=p2;
    }
    return result;      
}   

Vehicle*merge_vehicle_amount_paid(Vehicle*head1,Vehicle*head2){
    Vehicle*p1=head1;
    Vehicle*p2=head2;
    Vehicle*result;
    Vehicle*tail;
    if(p1->amount > p2->amount){
        result=p1;
        tail=p1;
        p1=p1->next;
    }
    else{
        result=p2;
        tail=p2;
        p2=p2->next;
    }
    while(p1!=NULL && p2!=NULL){
        
        if(p1->amount > p2->amount){
            tail->next=p1;
            tail=p1;
            p1=p1->next;
            
        }
        else{
            tail->next=p2;
            tail=p2;
            p2=p2->next;
        }
        
    }
    if(p1!=NULL){
        tail->next=p1;
    }
    if(p2!=NULL){
        tail->next=p2;
    }
    return result;       
}

Vehicle*merge_sort_vehicle(Vehicle* veh_head,vehicle_param parameter) {
    
    Vehicle*retnode=NULL;
    Vehicle*temp=veh_head;
    if(veh_head->next==NULL){
        retnode= veh_head;
    }
    else if(veh_head->next!=NULL && veh_head!=NULL){
        Vehicle*mid=get_mid_Vehicle(temp);
        
        Vehicle*left= merge_sort_vehicle(temp,parameter);
        Vehicle*right=merge_sort_vehicle(mid,parameter);
        if(parameter==parkings_done){
            retnode=merge_vehicle_parkings_done(left,right);
        }
        if(parameter==amount_paid){
            retnode=merge_vehicle_amount_paid(left,right);
        }
    }
    return retnode;                    
}  


//Parking database reading and initialisation

void initialize_parking(Parking** head, Parking** head_gold, Parking** head_premium, Parking** head_regular, int pspace_id, int status, float revenue, int occupancy, int index) {
    Parking* new_node = (Parking*)malloc(sizeof(Parking));
    new_node->pspace_id = pspace_id;
    new_node->status = status;
    new_node->revenue = revenue;
    new_node->occupancy = occupancy;
    new_node->next = NULL;
    new_node->prev = NULL;

    // If the list is empty, set head to new node
    if (*head == NULL) {
        *head = new_node;
    } else {
        Parking* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
        new_node->prev = curr;
    }

    // Handle the special cases for setting head_premium, head_no_membership, and head_gold
    if (index == 0) { // 1st element
        *head_gold = new_node;
    }

    if (index == 10) { // 11th element
        *head_premium = new_node;
    }
    if (index == 20) { // 21st element
        *head_regular = new_node;
    }
    
}

void read_parking_data(const char *filename, Parking** head, Parking** head_gold, Parking** head_premium, Parking** head_regular) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Variables to store parking data temporarily
    int pspace_id, status, occupancy;
    float revenue;

    // Read 50 records from the file and insert them into the doubly linked list
    for (int i = 0; i < 50; i++) {
        // Read data for each parking spot
        if (fscanf(file, "%d %d %f %d", &pspace_id, &status, &revenue, &occupancy) != 4) {
            printf("Error reading data from file\n");
            break; // Stop if there's an issue with reading
        }
        
        // Insert the parking data into the doubly linked list
        initialize_parking(head, head_gold, head_premium, head_regular, pspace_id, status, revenue, occupancy, i);
    }

    fclose(file);
}

void write_parking_data(const char *filename, Parking* head) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    Parking* curr = head;
    while (curr != NULL) {
        fprintf(file, "%d %d %.2f %d\n", curr->pspace_id, curr->status, curr->revenue, curr->occupancy);
        curr = curr->next;
    }

    fclose(file);
    printf("Parking data successfully written to %s\n", filename);
}

void print_parking_list(Parking* start) {

    printf("\n\n");
    printf("====================================================================================================");
    printf("\n\n");
    Parking* curr = start;
    while (curr != NULL) {
        if(curr->pspace_id==1){
            printf("\n\n");
            printf("GOLD LIST \n");
            printf("--x--x--x--x--x--");
            printf("\n\n");
        }
        else if(curr->pspace_id==11){
            printf("\n\n");
            printf("PREMIUM LIST\n");
            printf("--x--x--x--x--x--");
            printf("\n\n");
        }
        else if(curr->pspace_id==21){
            printf("\n\n");
            printf("NO MEMEBERSHIP LIST \n");
            printf("--x--x--x--x--x--");
            printf("\n\n");
        }

        printf("Parking ID: %d, Status: %d, Revenue: %.2f, Occupancy: %d\n",
               curr->pspace_id, curr->status, curr->revenue, curr->occupancy);
        curr = curr->next;
    }
    printf("\n\n");
    printf("====================================================================================================");
    printf("\n\n");
}

void print_parking_node(Parking *node) {
    if (node == NULL) {
        printf("Parking node is NULL.\n");
        return;
    }

    printf("Parking Space ID: %d\n", node->pspace_id);
    printf("Status: %d\n", node->status);
    printf("Revenue: %.2f\n", node->revenue);
    printf("Occupancy: %d\n", node->occupancy);
    printf("\n\n");
}

void print_parking_list_sorted(Parking* start) {

    printf("\n\n");
    printf("====================================================================================================");
    printf("\n\n");
    Parking* curr = start;
    while (curr != NULL){
        printf("Parking ID: %d, Status: %d, Revenue: %.2f, Occupancy: %d\n",
               curr->pspace_id, curr->status, curr->revenue, curr->occupancy);
        curr = curr->next;
    }
    printf("\n\n");
    printf("====================================================================================================");
    printf("\n\n");
}


//Creating Vehicle LL and File Handling

Vehicle* createVehicleNode(char* vehicle_number, char* owner_name, int date_arr, int time_arr, int date_dep, int time_dep, int parking_hours, int pspace_alloted, int membership, float amount, int parkings_done) {
    
    Vehicle* newNode = (Vehicle*)malloc(sizeof(Vehicle));
    
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
    }

    else{
        strcpy(newNode->vehicle_number, vehicle_number);
        strcpy(newNode->owner_name, owner_name);
        newNode->date_arr = date_arr;
        newNode->time_arr = time_arr;
        newNode->date_dep = date_dep;
        newNode->time_dep = time_dep;
        newNode->parking_hours = parking_hours;
        newNode->pspace_alloted = pspace_alloted;
        newNode->membership = membership;
        newNode->amount = amount;
        newNode->parkings_done = parkings_done;
        newNode->next = NULL;
    }
    
    return newNode;
}

void insertVehicleNode(Vehicle** head, Vehicle* newNode) {
    if (*head == NULL) {
        *head = newNode;
    } 
    else {
        newNode->next = *head;
        *head = newNode;
    }
}

Vehicle* readFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return NULL;
    }

    Vehicle* head = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char vehicle_number[20], owner_name[100];
        int date_arr, time_arr, date_dep, time_dep, parking_hours, pspace_alloted, membership, parkings_done;
        float amount;

        // Read tab-separated values from the file
        sscanf(line, "%s %[^\t] %d %d %d %d %d %d %d %f %d",
               vehicle_number, owner_name, &date_arr, &time_arr, &date_dep, &time_dep,
               &parking_hours, &pspace_alloted, &membership, &amount, &parkings_done);

        Vehicle* newNode = createVehicleNode(vehicle_number, owner_name, date_arr, time_arr,
                                             date_dep, time_dep, parking_hours, pspace_alloted,
                                             membership, amount, parkings_done);

        if (newNode) {
            insertVehicleNode(&head, newNode);  // Insert at head
        }
    }

    fclose(file);
    return head;
}

void printVehicles(Vehicle* head) {
    printf("\n\n");
    printf("====================================================================================================");
    printf("\n\n");
    while (head) {
        printf("Vehicle No: %s | Owner: %s | Arr: %02d/%02d/%02d %02d:%02d | Dep: %02d/%02d/%02d %02d:%02d | Hrs: %d | Space: %d | Membership: %d | Amount: %.2f | Parkings: %d\n",
               head->vehicle_number, head->owner_name, 
               (head->date_arr)/10000,((head->date_arr)/100)%100,(head->date_arr)%100, (head->time_arr)/100, (head->time_arr)%100,
               (head->date_dep)/10000, ((head->date_dep)/100)%100, (head->date_dep)%100, (head->time_dep)/100, (head->time_dep)%100,
               head->parking_hours, head->pspace_alloted, head->membership, head->amount, head->parkings_done);
        head = head->next;
    }
    printf("\n");
    printf("====================================================================================================");
    printf("\n\n");
}

void writeToFile(Vehicle* head, const char* filename) {
    FILE* file = fopen(filename, "w"); 
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    while (head) {
        fprintf(file, "%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.2f\t%d\n",
                head->vehicle_number, head->owner_name, head->date_arr, head->time_arr,
                head->date_dep, head->time_dep, head->parking_hours, head->pspace_alloted,
                head->membership, head->amount, head->parkings_done);
        head = head->next;
    }

    fclose(file);
}

void print_Vehicle_Node( Vehicle* veh_node) 
{
    if (veh_node == NULL) {
        printf("No vehicle details available.\n");
        return;
    }

    printf("\nVehicle Details:\n");
    printf("--------------------------------------------------\n");
    printf("Vehicle Number     : %s\n", veh_node->vehicle_number);
    printf("Owner Name         : %s\n", veh_node->owner_name);
    printf("Date of Arrival    : %02d/%02d/%02d (ddmmyy)\n", (veh_node->date_arr)/10000,((veh_node->date_arr)/100)%100,(veh_node->date_arr)%100);
    printf("Time of Arrival    : %02d:%02d (hhmm)\n", (veh_node->time_arr)/100,(veh_node->time_arr)%100);
    printf("Date of Departure  : %02d:%02d/%02d (ddmmyy)\n", (veh_node->date_dep)/10000,((veh_node->date_dep)/100)%100,(veh_node->date_dep)%100);
    printf("Time of Departure  : %02d/%02d (hhmm)\n", (veh_node->time_dep)/100,(veh_node->time_dep)%100);
    printf("Parking Hours Used : %d\n", veh_node->parking_hours);
    printf("Parking Space ID   : %d\n", veh_node->pspace_alloted);
    printf("Membership Type    : %d\n", veh_node->membership);
       
    printf("Total Amount Paid  : %.2f\n", veh_node->amount);
    printf("Total Parkings Done: %d\n", veh_node->parkings_done);
    printf("--------------------------------------------------\n\n");
}

void delete_vehicle_Node(Vehicle**veh_head,Vehicle*node){
    Vehicle *search=*veh_head;
    Vehicle *prev=NULL;
    Vehicle *delete=NULL;
    int found = 0;

    if(*veh_head == NULL){
        printf("Empty List\n");
    }

    else if(*veh_head == node)
    {
        delete = *veh_head;
        (*veh_head)=(*veh_head)->next;
        free(delete);
        printf("Deleted\n");
    }

    else
    {
        prev = search;
        search = search->next;
        while(search != NULL && !found)
        {
            if(search == node)
            {   
                found = 1;
                delete = search;
                prev->next = delete->next;
            }
        }

        if(found){
            free(delete);
            printf("Deleted\n");
        }
        else{
            printf("Node not found\n");
        }
    }
    
}


//Allocation

Vehicle* find_vehicle_node(Vehicle *head, char veh_num[])
{
    Vehicle *search = head;
    Vehicle *retnode = NULL;
    int found = 0;
    while(search!=NULL && found != 1)
    {
        if(strcmp(search->vehicle_number,veh_num)==0)
        {
            found = 1;
            retnode = search;
        }
        search = search->next;
    }
    return retnode;
}

Parking* find_parking_node(Parking *head, Vehicle *vehicle, Parking *head_gold, Parking *head_premium, Parking *head_regular){
    int found=0;
    Parking *retnode = NULL;
    Parking *search = NULL;
    // 0 for reg
    // 1 for premi
    // 2 for gold

    //regular membership
    if(vehicle->membership==0 && !found){
        search = head_regular;
        while(search != NULL && !found){
            if(search->status==0){
                retnode = search;
                found = 1;
            }

            search = search->next;
        }

        if(!found){
            //search in premium membership
            search = head_premium;
            while(search!=head_regular && !found){
                if(search->status==0){
                    found=1;
                    retnode=search;
                }
                search=search->next;
            }
        }

        if(!found){
            //search in gold membership
            search = head_gold;
            while(search!=head_premium && !found){
                if(search->status==0){
                    found=1;
                    retnode=search;
                }
                search=search->next;
            }
        }
    }

    //premium membership
    else if(vehicle->membership==1){
        search=head_premium;
        while(search != head_regular && !found){
            if(search->status == 0){
                retnode = search;
                found = 1;
            }    
            search = search->next; 
        }

        if(!found){
            //search in regular membership
            while(search!=NULL && !found){
                if(search->status==0){
                    found=1;
                    retnode=search;
                }
                search=search->next;
            }
        }

        if(!found){
            //search in gold membership
            search = head_gold;
            while(search!=head_premium && !found){
                if(search->status==0){
                    found=1;
                    retnode=search;
                }
                search=search->next;
            }
        }
        

    }


    //gold membership
    else{
 
        search = head_gold;
        while(search != head_premium && !found){
            if(search->status==0){
                retnode = search;
                found=1;
            }   
            search = search->next;     
        }

        // search in premium
        if(!found){
             while(search != head_regular && !found){
            if(search->status==0){
                retnode=search;
                found=1;
            }    
                
            search = search->next;
            }
        }

        // search in regular
        if(!found){
            while(search!=NULL && !found){
            if(search->status==0){
                retnode = search;
                found=1;
            }

            search = search->next;
            }
        }
    }
    return retnode;
}

void allocate_vehicle_parking(Vehicle **veh_head, Parking **par_head, Parking *head_gold, Parking *head_premium, Parking *head_regular){
    
    char veh_num[20];
    printf("Enter vehicle number\n");
    scanf("%s",veh_num);
    
    Vehicle *vehicle = find_vehicle_node(*veh_head, veh_num);

    if(vehicle==NULL)
    {
        printf("New vehicle\n\n");
        
        //GET DETAILS
        char owner_name[100];
        int date_arr; //ddmmyy
        int time_arr; // hhmm
        printf("Enter vehicle owner name\n");
        scanf(" ");
        fgets(owner_name, sizeof(owner_name), stdin);
        owner_name[strcspn(owner_name, "\n")] = '\0';
        int dflag = 0;
        while(dflag==0)
        {
            printf("Enter date of arrival (ddmmyy)\n");
            scanf("%d",&date_arr);
            if(date_arr/10000 > 0 && date_arr/1000000 == 0)
            {
                int dd=(date_arr)/10000;
                int mm= ((date_arr)/100)%100;
                int yy= (date_arr)%100;
                if((dd >0 && dd<=30) && (mm > 0 && mm <= 12) && (yy >0)){
                     dflag = 1; 
                }
                else{
                 printf("Please enter the date in specified format\n");
                }
            }
            else
            {
                printf("Please enter the date in specified format\n");
            }
        }
        int tflag = 0;
        while(tflag==0)
        {
            printf("Enter time of arrival (hhmm 24 hour format)\n");
            scanf("%d",&time_arr);
            if(time_arr/100 > 0 && time_arr/10000 == 0)
            {
                tflag = 1;
            }
            else
            {
                printf("Please enter time in the specified format.\n");
            }
        }

        //GENERATE AN ISOLATED NODE
        vehicle = createVehicleNode(veh_num, owner_name, date_arr, time_arr, 000000, 0000, 0, 0, 0, 0, 0);
        Parking* parking = find_parking_node(*par_head, vehicle, head_gold, head_premium, head_regular); 
        if(parking == NULL)
        {
            printf("No empty parking\n");
        }
        else
        {
            parking->occupancy = parking->occupancy + 1;
            parking->status = 1;
            vehicle->pspace_alloted = parking->pspace_id;
            vehicle->parkings_done = vehicle->parkings_done + 1;
            printf("Vehicle alloted at parking space : %d \n", vehicle->pspace_alloted);
        }
        insertVehicleNode(veh_head,vehicle);
        
    }
    else
    {
        printf("Vehicle found, owned by %s\n\n",vehicle->owner_name);
        int date_arr; //ddmmyy
        int time_arr; // hhmm
        int dflag = 0;
        while(dflag==0)
        {
            printf("Enter date of arrival (ddmmyy)\n");
            scanf("%d",&date_arr);
            if(date_arr/10000 > 0 && date_arr/1000000 == 0)
            {
                int dd=(date_arr)/10000;
                int mm= ((date_arr)/100)%100;
                int yy= (date_arr)%100;
                if((dd >0 && dd<=30) && (mm > 0 && mm <= 12) && (yy >0)){
                     dflag = 1; 
                }
                else{
                 printf("Please enter the date in specified format\n");
                }
            }
            else
            {
                printf("Please enter the date in specified format\n");
            }
        }
        int tflag = 0;
        while(tflag==0)
        {
            printf("Enter time of arrival (hhmm 24 hour format)\n");
            scanf("%d",&time_arr);
            if(time_arr/100 > 0 && time_arr/10000 == 0)
            {
                tflag = 1;
            }
            else
            {
                printf("Please enter time in the specified format.\n");
            }
        }
        vehicle->date_arr = date_arr;
        vehicle->time_arr = time_arr;
        Parking* parking = find_parking_node(*par_head, vehicle, head_gold, head_premium, head_regular); 
        if(parking == NULL)
        {
            printf("No empty parking\n");
        }
        else
        {
            parking->occupancy = parking->occupancy + 1;
            parking->status = 1;
            vehicle->pspace_alloted = parking->pspace_id;
            vehicle->parkings_done = vehicle->parkings_done + 1;
            printf("Vehicle alloted at parking space : %d \n\n", vehicle->pspace_alloted);
        }
    }
}



//Time and Charges Calculation

float hours_from_ref(int date, int time) {
    // Extract day, month, and year from date
    int day = date / 10000;        // dd
    int month = (date / 100) % 100; // mm
    int year = date % 100;         // yy

    // Extract hour and minute from time
    int hour = time / 100;         // hh
    int minute = time % 100;       // mm

    // Calculate total days since a reference point (e.g., 00/00/xx00)
    // Assuming each month has 30 days for simplicity and leap years are ignored
    int total_days = (year * 365) + (month * 30) + day;
    // Total minutes = total days * 1440 + hours * 60 + minutes
    float time_from_reference = (total_days * 24.0) + hour + (minute/60.0);
    return time_from_reference;
}

float calc_duration(Vehicle*v)
{
    float arrival = hours_from_ref(v->date_arr, v->time_arr);
    float departure = hours_from_ref(v->date_dep, v->time_dep);
    float duration = departure - arrival;
    return duration;
}

float calc_charges(Vehicle*v, float duration)
{
    float base_charge, final_charge;
    
    if (duration <= 3)
    {
        base_charge = 100.0;
    }
    else
    {
        base_charge = 100.0 + (duration - 3)*50.0;
    }

    if(v->membership == 0)
    {
        final_charge = base_charge;
    }
    else
    {
        final_charge = 0.9*base_charge;
    }

    return final_charge;
}



//Unallocation

Parking* find_parking_id_node(Parking*head,int id){
    Parking*retnode=NULL;
    Parking*temp=head;
    int found=0;
    while(temp!=NULL && !found){
        if(temp->pspace_id==id){
            retnode = temp;
            found = 1;
        }
        temp=temp->next;    
    }
    //NULL return mean no id found
    return retnode;
        
}

void unallocate_vehicle_parking(Parking**par_head,Vehicle**veh_head){
    char veh_num[20];
    int vflag = 0;
    while(vflag == 0)
    {
        printf("Enter vechicle number exiting:\n");
        scanf("%s",veh_num);
        Vehicle*vehicle_Node = find_vehicle_node(*veh_head,veh_num);

        //delete_Node(*veh_head,vehicle_Node);

        if(vehicle_Node==NULL)
        {
            printf("Vehicle not found.\n\n");
        }
        else
        {
            //Once found, use its parking space id alloted to navigate the linked list of parking structure
            int id = vehicle_Node->pspace_alloted;
            Parking*parking_id_Node= find_parking_id_node(*par_head,id);

            printf("\n\n");
            printf("Unchanged details:\n");
            //print statements
            print_parking_node(parking_id_Node);
            print_Vehicle_Node(vehicle_Node);
            

            

            //Update date and time of departure to calculate duration parked
            int dflag = 0;
            while(dflag==0)
            {
                printf("Enter date of departure (ddmmyy)\n");
                scanf("%d",&vehicle_Node->date_dep);
                if(vehicle_Node->date_dep/10000 > 0 && vehicle_Node->date_dep/1000000 == 0 )
                {  int dd=(vehicle_Node->date_dep)/10000;
                   int mm= ((vehicle_Node->date_dep)/100)%100;
                   int yy= (vehicle_Node->date_dep)%100;
                   if((dd >0 && dd<=30) && (mm > 0 && mm <= 12) && (yy >0)){
                        dflag = 1; 
                   }
                   else{
                    printf("Please enter the date in specified format\n");
                   }   
                }
                else
                {
                    printf("Please enter the date in specified format\n");
                }
            }
            int tflag = 0;
            while(tflag==0)
            {
                printf("Enter time of departure (hhmm 24 hour format)\n");
                scanf("%d",&vehicle_Node->time_dep);
                if(vehicle_Node->time_dep/100 > 0 && vehicle_Node->time_dep/10000 == 0 )
                {
                    tflag = 1;
                }
                else
                {
                    printf("Please enter time in the specified format.\n");
                }
            }

            //calculate duration parked
            float duration = calc_duration(vehicle_Node);

            if(duration<=0)
            {
                printf("Invalid date or time of exit.\n\n");
            }

            else
            {
                printf("duration:%f\n",duration);

                //update parking hours
                vehicle_Node->parking_hours += duration;
                
                //update membership according to updated parking hours
                if(vehicle_Node->parking_hours<=100)
                {
                    vehicle_Node->membership = 0;
                }
                else if((vehicle_Node->parking_hours>100) && (vehicle_Node->parking_hours<=200))
                {
                    vehicle_Node->membership = 1;
                }
                else
                {
                    vehicle_Node->membership = 2;
                }

                float charges = calc_charges(vehicle_Node,duration);
                printf("charges:%f\n",charges);
                printf("\n\n");

                //update revenue generated by the parking space
                parking_id_Node->revenue = parking_id_Node->revenue + charges;
                parking_id_Node->status = 0;
                vehicle_Node->amount = vehicle_Node->amount + charges;
                vehicle_Node->pspace_alloted = 0;

                printf("Changed details:\n");
                //print statements
                print_parking_node(parking_id_Node);
                print_Vehicle_Node(vehicle_Node);
                printf("\n");
            }
            vflag = 1;
        }
    }

}



int main() {
    Parking* par_head = NULL;    
    Parking* head_premium = NULL;
    Parking* head_regular = NULL; 
    Parking* head_gold = NULL;        

    read_parking_data("parking_data.txt", &par_head, &head_gold, &head_premium, &head_regular);
    Vehicle* vehicle_list = readFromFile("vehicles.txt");

    int exit = 0;
    int action;
    while(exit == 0)
    {
        printf("What operation do you want to perform?\n");
        printf("1) Allocate Parking\n");
        printf("2) Ullocate Parking\n");
        printf("3) Sort parkings based on occupancy\n");
        printf("4) Sort parkings based on revenue generated\n");
        printf("5) Sort vehicles based on parkings done\n");
        printf("6) Sort vehicles based on total amount paid\n");
        printf("0) Exit\n");
        scanf("%d",&action);
        printf("\n\n");
       


    switch(action)
        {
            case 1:
                par_head=merge_sort_parking(par_head,id);
                printVehicles(vehicle_list);
                allocate_vehicle_parking(&vehicle_list,&par_head,head_gold,head_premium,head_regular);
                print_parking_list(par_head);
                printVehicles(vehicle_list);
                break;
            
            case 2:
                par_head=merge_sort_parking(par_head,id);
                printVehicles(vehicle_list);
                unallocate_vehicle_parking(&par_head,&vehicle_list);
                print_parking_list(par_head);
                printVehicles(vehicle_list);
                break;

            case 3:
                par_head=merge_sort_parking(par_head,occupancy);
                print_parking_list_sorted(par_head);
                break;
            
            case 4:
                par_head=merge_sort_parking(par_head,revenue);
                print_parking_list_sorted(par_head);
                break;
            
            case 5:
                vehicle_list=merge_sort_vehicle(vehicle_list,parkings_done);
                printVehicles(vehicle_list);
                break;
            
            case 6:
                vehicle_list=merge_sort_vehicle(vehicle_list, amount_paid);
                printVehicles(vehicle_list);
                break;
            
            case 0:
                par_head=merge_sort_parking(par_head,id);
                writeToFile(vehicle_list, "vehicles.txt");
                write_parking_data("parking_data.txt", par_head);
                exit = 1;
                break;

            default:
                printf("Invalid action\n\n");
        }
    }
    
    return 0;
}