#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node
{
    char shop_name[100];
    int serial;//to take the unique regestration number for vendor
    int pass;
    float discount;
    struct node *link;//to connect each vendor to another vendor for linked list
    struct MenuItem *menu;//to keep address of first node of menu for that particular shop
    struct order *system;//to keep address of first node of order for that particular shop
} vendor;

typedef struct MenuItem
{
    int item_id;//to seperate/search food by this id
    char food_name[50];
    int quantity;//quantity of each food of that menu
    float price;
    struct MenuItem *next;//to connect each food item with another
} Menu;

typedef struct order
{
    char c_name[100];//for customer name
    char c_id[200];//mail id of customer
    float t_bill;//total bill of that customer
    char otp[100];//to store unique string for verification from mail id
    int ID[20];//to store all the food item id while ordering
    int order_quantity[20];//how much food happened to order
    int Item_q;
    char update[50];//updation of order(completed/received)
    struct order *queue;
} Order;

vendor *head=NULL,*tail=NULL;
Menu *menu_head=NULL,*menu_tail=NULL;
void del_beg(vendor *ptr,int pos);
void del_end(vendor *ptr,int pos);
void del_fixed(vendor *ptr,int pos);
void add_menu();
void vendor_admin(vendor *ptr);
void deletmenu(vendor *ptr);

void authority_log()
{
    system("cls");
    char username[15], password[6];

    printf("\n\n\t\t\t\tEnter username: ");
    fflush(stdin);
    scanf("%[^\n]s",&username);
    printf("\t\t\t\tEnter Password: ");
    int i=0;
    for(i=0; i<5; i++)
    {
        password[i]=getch();
        printf("%c",'*');
    }
    password[i]='\0';
    while((strcmp(username,"Admin")!=0)||(strcmp(password,"a1234")!=0))
    {
        printf("\n\t\t\tWrong Information!Please try again : \n");
        printf("\t\t\t\tEnter username: ");
        fflush(stdin);
        scanf("%[^\n]s",&username);
        printf("\t\t\t\tEnter Password: ");
        int i=0;
        for(i=0; i<5; i++)
        {
            password[i]=getch();
            printf("%c",'*');
        }
        password[i]='\0';

    }
    printf("\n");
    authority();

}
vendor *add_vendor()
{
    system("cls");
    char ch[50];
    int id,p;
    float dis;
    fflush(stdin);
    printf("\n\tAdd your shop name : ");
    gets(ch);
    printf("\n\tAdd serial number of shop(3 digits) : ");
    scanf("%d",&id);
    printf("\n\tEnter your pass : ");
    scanf("%d",&p);
    printf("\n\tDiscount :");
    scanf("%f",&dis);
    vendor *newnode=NULL;
    newnode = malloc(sizeof(vendor));
    strcpy(newnode->shop_name,ch);
    newnode->serial=id;
    newnode->pass=p;
    newnode->discount=dis;
    newnode->menu=NULL;
    newnode->link=NULL;
    newnode->system=NULL;
    if(head==NULL)
    {
        head=newnode;
        tail=newnode;
    }
    else
    {
        tail->link=newnode;
        tail=newnode;
    }

    printf("\n\tVendor Added Successfully! Congratulations!!\n");
    printf("............................................................\n");

    while(1)
    {
        printf("\n");
        printf("\t1.Wanna add food?\n");
        printf("\t2.Log out? (any digit)\n");
        printf("\t3.Go back to dashboard\n");
        printf("\n");
        printf("\tEnter Your Choose: ");
        int c;
        scanf("%d",&c);
        if(c==1)
        {
            add_menu();
        }
        else if(c==2)
        {
            menu_head=NULL;
            menu_tail=NULL;
            break;
        }
        else if(c==3){
            authority();
        }
    }
    create_files();
}

void add_menu()
{
    system("cls");
    char ch[50];
    int id,q;
    float p;
    printf("\tAdd food name : ");
    fflush(stdin);
    gets(ch);
    printf("\tAdd item number of food : ");
    scanf("%d",&id);
    printf("\tInput quantity : ");
    scanf("%d",&q);
    printf("\tInput the price of food : ");
    scanf("%f",&p);
    Menu *newnode=NULL;
    newnode = malloc(sizeof(vendor));
    strcpy(newnode->food_name,ch);
    newnode->item_id=id;
    newnode->quantity=q;
    newnode->price=p;
    newnode->next=NULL;
    if(menu_head==NULL)
    {
        menu_head=newnode;
        menu_tail=newnode;
    }
    else
    {
        menu_tail->next=newnode;
        menu_tail=newnode;
    }
    tail->menu=menu_head;
    create_files();
    printf("\n\tMenu added successfully!!!!\n");
    printf("....................................................\n");

}

void vendordel_end()
{
    vendor *ptr1=head;
    vendor *temp1=NULL;
    if(ptr1==NULL)
    {
        printf("\tThere is no vendor left to delete\n");
    }
    else if(head->link=NULL)
    {
        free(head);
        head=NULL;
    }
    else
    {
        while(ptr1->link!=NULL)
        {
            temp1=ptr1;
            ptr1=ptr1->link;
        }
        temp1->link=NULL;
        free(ptr1);
        ptr1=NULL;
    }
}

void vendordel_beg()
{

    vendor *temp1=head;
    head=head->link;
    free(temp1);
    temp1=NULL;
}
void vendordel_fixed(vendor *ptr,int pos)
{
    vendor *temp2=ptr;
    for(int i=1; i<=pos-1; i++)
    {
        ptr=temp2;
        temp2=ptr->link;
    }
    ptr->link=temp2->link;
    free(temp2);
    temp2=NULL;
}

void del_vendor()
{
    system("cls");
    printf("\tInput shop serial number to delete : ");
    int number,count=0,count1=0;
    scanf("%d",&number);
    vendor *ptr3=head,*ptr1=head;
    while(ptr3!=NULL)
    {
        count++;//To count total vendor
        ptr3=ptr3->link;
    }
    printf("%d\n",count);
    while(ptr1!=NULL)
    {
        if(ptr1->serial==number)
        {
            count1++;
            if(count1==count)
            {
                vendordel_end();
                break;
            }
            else if(count1==1)
            {
                vendordel_beg();
                break;
            }
            else
            {
                vendordel_fixed(ptr1,count1);
                break;
            }
        }
        else
        {
            count1++;//to calculate the position of deleted vendor
            ptr1=ptr1->link;
        }
    }

    printf("\tSuccessfully deleted\n");
    create_files();
    return main();
}

void authentication()
{
    system("cls");
    int num,p;
    printf("\tEnter shop serial number : ");
    scanf("%d",&num);
    printf("\tEnter pass : ");
    scanf("%d",&p);
    vendor *temp=head;
    while(temp!=NULL)
    {
        if((num==temp->serial)&&(p==temp->pass))
        {
            vendor_admin(temp);
            break;
        }
        else
        {
            temp=temp->link;
        }
    }
}
void add_new(vendor *ptr)
{
    system("cls");
    Menu *temp=ptr->menu;
    char ch[50];
    int id,q;
    float p;
    printf("\tAdd food name : ");
    fflush(stdin);
    gets(ch);
    printf("\tAdd item number of food : ");
    scanf("%d",&id);
    printf("\tInput quantity : ");
    scanf("%d",&q);
    printf("\tInput the price of food : ");
    scanf("%f",&p);
    Menu *newnode=NULL;
    newnode = malloc(sizeof(vendor));
    strcpy(newnode->food_name,ch);
    newnode->item_id=id;
    newnode->quantity=q;
    newnode->price=p;
    newnode->next=NULL;
    if(temp==NULL)
    {
        menu_head=newnode;
        menu_tail=newnode;
        tail->menu=menu_head;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;

    }
    printf("\tNew menu added successfully!!!\n");
    create_files();
}

void add_discount(vendor *ptr)
{
    printf("\tAmount of Discount(in percantage) : ");
    float dis;
    scanf("%f",&dis);
    ptr->discount=dis;
    return vendor_admin(ptr);

}

void vendor_admin(vendor *ptr)
{
    system("cls");
    while(1)
    {
        printf("\t\t\t---------------------------\n");
        printf("\t\t\t|                         |\n");
        printf("\t\t\t|          %s         |\n",ptr->shop_name);
        printf("\t\t\t|                         |\n");
        printf("\t\t\t---------------------------\n");
        int num;
        printf("\n\t\t\t1.Add menu\n");
        printf("\t\t\t2.Delete menu\n");
        printf("\t\t\t3.See order\n");
        printf("\t\t\t4.Add Discount\n");
        printf("\t\t\t5.Back\n");
        printf("\n\t\t\tEnter your choice : ");
        scanf("%d",&num);
        switch(num)
        {
        case 1:
        {
            add_new(ptr);
            create_files();
            break;
        }
        case 2:
        {
            deletmenu(ptr);
            create_files();
            break;
        }
        case 3:
        {
update:
            display_order(ptr);
            break;
        }
        case 4:
        {
            add_discount(ptr);
        }
        case 5:
        {
            return main();
            break;
        }
        default:
            printf("\tEnter again\n");
            break;
        }
    }
    //return main();
}

void del_beg(vendor *ptr,int pos)
{
    Menu *ptr1=ptr->menu;
    Menu *temp1=ptr1;
    ptr1=ptr1->next;
    ptr->menu=ptr1;
    free(temp1);
    temp1=NULL;
}

void del_end(vendor *ptr,int pos)
{
    Menu *ptr1=ptr->menu;
    Menu *temp1=NULL;
    if(ptr1==NULL)
    {
        printf("\tThere is no menu left to delete\n");
    }
    else
    {
        while(ptr1->next!=NULL)
        {
            temp1=ptr1;
            ptr1=ptr1->next;
        }
        temp1->next=NULL;
        free(ptr1);
        ptr1=NULL;
    }
}

void del_fixed(vendor *ptr,int pos)
{
    Menu *temp=ptr->menu,*temp2=ptr->menu;
    for(int i=1; i<=pos-1; i++)
    {
        temp=temp2;
        temp2=temp->next;
    }
    temp->next=temp2->next;
    free(temp2);
    temp2=NULL;
}

void deletmenu(vendor *ptr)
{
    system("cls");
    printf("\tInput item number of food you want to delete : ");
    int num,count1=0,count=0;
    scanf("%d",&num);
    Menu *ptr1=ptr->menu,*ptr3=ptr->menu,*temp=NULL;
    while(ptr3!=NULL)
    {
        count++;//To count total menu item
        ptr3=ptr3->next;
    }
    if(ptr1==NULL){
        printf("\n\tThere is no food to delete\n");
    printf("\n\tPress 1 to go back : ");
    int option;
    scanf("%d",&option);
    if(option==1){
        return vendor_admin(ptr);
    }
    }
    else{
    while(ptr1!=NULL)
    {
        if(ptr1->item_id==num)
        {
            count1++;
            if(count1==1)
            {
                del_beg(ptr,1);
            }
            else if(count1==count)
            {
                del_end(ptr,count1);
            }

            else
            {
                del_fixed(ptr,count1);
            }
        }
        else
        {
            count1++;//to calculate the position of deleted menu
            ptr1=ptr1->next;
        }
        //  printf("\tSuccessfully deleted\n");
    }
    printf("\n\tSuccessfully deleted\n");
    }
}
void order_customer()
{
    system("cls");
    //display_vendor();
    vendor *ptr=head;
    if(ptr==NULL)
    {
        printf("THere is no vendor yet.");
        main();
    }
    printf("\t\t---------------------------------\n");
    printf("\t\t| Serial No |  Shop Name\t|\n");
    printf("\t\t---------------------------------\n");
    while(ptr!=NULL)
    {
        printf("\t\t   %d    %s   \n",ptr->serial,ptr->shop_name);
        printf("\t\t---------------------------------\n");
        ptr=ptr->link;
    }

    int num;
repeat:

    printf("\n\tChoose Your vendor.Type serial number : ");
    scanf("%d",&num);
    printf("\n");
    ptr=head;
    vendor *temp=NULL;
    while(ptr!=NULL)
    {
        if(ptr->serial==num)
        {
            temp=ptr;
            display_custmenu(temp);
            break;
        }
        else
        {
            ptr=ptr->link;
            if(ptr==NULL)
            {
                printf("\n\t\tThere is no vendor with that serial num. Pls Choose again\n");
                goto repeat;
            }
        }
    }
    if(temp->discount>0)
    {
        printf("\n\t\t%.2f %% Discount in total order!!!!\n",temp->discount);
    }

    int item;
    printf("\n\t\tPlease enter your name and mail ID : \n");
    char name[100];
    char id[200];
    int amount;
    float taka,bill;
    fflush(stdin);
    printf("\n\t\tName : ");
    gets(name);
    printf("\t\tMail ID : ");
    gets(id);
    char king[]="Received";
    int m=0;
    char ch[200];
    while(id[m]!='@')
    {
        ch[m]=id[m];
        m++;
    }
    ch[m]='\0';
    int i=0,count=0,j;
    int temp4[20],temp5[20];
    int choice;
    printf("\tInput quantity of total item number u want to order : ");
    scanf("%d",&choice);
    for(int k=0; k<choice; k++)
    {

choose:
        printf("\tChoose ur food by item no : ");
        scanf("%d",&item);
        Menu *temp1=temp->menu;

        while(temp1!=NULL)
        {
            if(temp1->item_id==item)
            {
                if(temp1->quantity>0)
                {
                    temp4[i]=temp1;
                    printf("\tInput quantity : ");
                    scanf("%d",&amount);
                    if(amount>temp1->quantity)
                    {
                        printf("There is no remaining food of this item.You can order different item\n");
                        goto choose;
                    }
                    taka=temp1->price*amount;
                    bill+=taka;
                    temp5[i]=amount;
                    i++;
                    count++;
                    temp1->quantity-=amount;
                    break;
                }
                else
                {
                    printf("\t\tThere is no food.please choose again\n");
                    goto choose;
                }
            }
            else if(temp1->next==NULL)
            {
                printf("\t\tThe food u have chosen is not in menu.Input again\n");
                goto choose;
            }
            else
            {
                temp1=temp1->next;
            }
        }
    }
    bill=bill-(bill*(temp->discount/100.00));
    Order *newnode=NULL,*rare=temp->system;
    newnode=malloc(sizeof(Order));
    strcpy(newnode->c_id,id);
    strcpy(newnode->otp,ch);
    strcpy(newnode->c_name,name);
    strcpy(newnode->update,king);
    for(j=0; j<=i; j++)
    {
        newnode->ID[j]=temp4[j];
        newnode->order_quantity[j]=temp5[j];
    }
    newnode->t_bill=bill;
    newnode->Item_q=count;
    newnode->queue=NULL;
    if(temp->system==NULL)
    {
        temp->system=newnode;
        rare=newnode;
    }
    else
    {
        while(rare->queue!=NULL)
        {
            rare=rare->queue;
        }
        rare->queue=newnode;
        rare=newnode;

    }
    system("cls");
    printf("\t Your ordered food are in process\n");
    create_files();
    display_custorder(rare,temp);
    // printf("\t\tGo to main menu\n");
    printf("Type 1 to go back to menu : ");
    int x;
    scanf("%d",&x);
    if(x==1)
    {
        main();
    }
}

void paid_order(vendor *ptr)
{
    Order *temp=ptr->system,*temp1=NULL,*temp2=NULL;
    temp1=temp->queue;
    temp2=temp;
    temp=temp1;
    free(temp2);
    temp2=NULL;
    ptr->system=temp;
    printf("\t Removed paid order\n");
    create_files();
    display_order(ptr);
}
void print_orderedfood(Order *temp2)
{
    printf("\n\t------------------------------------------------------------------\n");
    printf("\tNo\tItem Id  Food Name     Quantity    Price\n");
    printf("\n\t------------------------------------------------------------------\n");
    for(int i=0; i<temp2->Item_q; i++)
    {
        Menu *temp3=temp2->ID[i];
        printf("\t%d\t %d \t %s  \t %d    %.2f   \n",i+1,temp3->item_id,temp3->food_name,temp2->order_quantity[i],temp3->price);
        printf("\n\t------------------------------------------------------------------\n");
    }
}

void order_inprocess(vendor *ptr)
{
    Order *temp9=ptr->system;
    char king[]="In Process";
    strcpy(temp9->update,king);
    create_files();
    return display_order(ptr);
}

void order_completed(vendor *ptr)
{
    Order *temp9=ptr->system;
    char king[]="Completed";
    strcpy(temp9->update,king);
    create_files();
    return display_order(ptr);
}
void display_order(vendor *ptr)
{
    system("cls");
    Order *temp=ptr->system;
    while(temp!=NULL)
    {
        printf("\tCustomer Name : %s\n",temp->c_name);
        printf("\tCustomer Mail : %s\n",temp->c_id);
        printf("\tCustomer OTP : %s\n",temp->otp);
        print_orderedfood(temp);
        printf("\tCustomer Bill : %.2f\n",temp->t_bill);
        printf("\t\tUpdate : %s\n\n",temp->update);
        temp=temp->queue;
    }
    int ord;
    printf("\t 1. To delete previous Order\n");
    printf("\t 2. In process\n");
    printf("\t 3. Completed\n");
    printf("\t 4. Back to Admin Menu\n");
    printf("\n\tPlease Enter your choice : ");
    scanf("%d",&ord);
    if(ord==1)
    {
        paid_order(ptr);
    }
    else if(ord==2)
    {
        order_inprocess(ptr);

//goto update;
    }
    else if(ord==3)
    {
        order_completed(ptr);

    }
    else if(ord==4)
    {
        return vendor_admin(ptr);
    }
}
void display_custorder(Order *rare,vendor *ptr)
{
    printf("\tCustomer Name : %s\n",rare->c_name);
    printf("\tCustomer Mail : %s\n",rare->c_id);
    printf("\tCustomer OTP : %s\n",rare->otp);
    print_orderedfood(rare);
    printf("\n\tDiscount : %.2f %%\n",ptr->discount);
    printf("\tCustomer Bill : %.2f\n",rare->t_bill);
    printf("\t\tUpdate : %s\n",rare->update);
    printf("\tTake a snap of your order and show otp to the vendor owner to pay the bill.\n");
    printf("\n");
}
void display_custmenu(vendor *ptr1)
{
    Menu *temp=ptr1->menu;
    int i=1;
    printf("\t---------------------------------------------------------------------------------\n");
    printf("\t| No |\tItem no.\t|\tFOOD\t|\tPRice\t|\tQuantity\t|\n");
    printf("\t---------------------------------------------------------------------------------\n");
    while(temp!=NULL)
    {

        printf("\t  %d  \t%d\t\t    %s     \t%.2f\t\t \t%d\t\t \n",i,temp->item_id,temp->food_name,temp->price,temp->quantity);
        printf("\t---------------------------------------------------------------------------------\n");
        temp=temp->next;
        i++;
    }
}
void display_vendor()
{
    //again:
    system("cls");
    vendor *ptr=head;
    printf("\t\t---------------------------------\n");
    printf("\t\t| Serial No |  Shop Name\t|\n");
    printf("\t\t---------------------------------\n");
    while(ptr!=NULL)
    {
        printf("\t\t   %d\t\t  %s        \n",ptr->serial,ptr->shop_name);
        printf("\t\t-------------------------------------\n");
        ptr=ptr->link;
    }
again:
    printf("\n\t\tPress 1 to go back ");
printf("\n\t\tpress 2 to see menu.\n");
printf("\n\tChoose : ");
    int x;//to take yes or no;
    scanf("%d",&x);
    if(x==1)
    {
        main();
    }
    else if(x==2){
       display_menu();
       goto again;
    }
}
void display_menu()
{
    vendor *ptr=head,*temp1=NULL;
    printf("\tEnter the serial no of shop : ");
    int num;
    scanf("%d",&num);
    while(ptr!=NULL)
    {
        if(ptr->serial==num)
        {
            temp1=ptr;
            break;
        }
        else
        {
            ptr=ptr->link;
        }
    }
    Menu *temp=temp1->menu;
    int i=1;
     printf("\t---------------------------------------------------------------------------------\n");
    printf("\t| No |\tItem no.\t|\tFOOD\t|\tPRice\t|\tQuantity\t|\n");
    printf("\t---------------------------------------------------------------------------------\n");
    while(temp!=NULL)
    {

         printf("\t  %d  \t%d\t\t    %s     \t%.2f\t\t \t%d\t\t \n",i,temp->item_id,temp->food_name,temp->price,temp->quantity);
        printf("\t---------------------------------------------------------------------------------\n");
        temp=temp->next;
        i++;
    }
}

void create_files()
{
    vendor *ptr=head;
    int number=0;
    FILE *fc;
    char vendor_name[100];
    while(ptr!=NULL)
    {
        int i=1;
        strcpy(vendor_name,ptr->shop_name);
        char filename[100];
        sprintf(filename, "%s.txt", vendor_name);
        fc=fopen(filename,"w");
        Menu *temp=ptr->menu;
        fprintf(fc,"\t--------------------------------------------------------\n");
        fprintf(fc,"\t| No |Item no  |  FOOD\t|  Price\t|  Quantity\t|\n");
        fprintf(fc,"\t--------------------------------------------------------\n");
        while(temp!=NULL)
        {
            fprintf(fc,"\t %d     %d \t  %s    %.2f \t   %d\t\n",i,temp->item_id,temp->food_name,temp->price,temp->quantity);
            fprintf(fc,"\t--------------------------------------------------------\n");
            temp=temp->next;
            i++;
        }
        fprintf(fc,"\n\t\tDiscount : %.2f %%\n",ptr->discount);
        fprintf(fc,"\n\tOrdered List : \n");
        Order *temp1=ptr->system;
        while(temp1!=NULL)
        {
            fprintf(fc,"\tCustomer Name : %s\n",temp1->c_name);
            fprintf(fc,"\tCustomer Mail : %s\n",temp1->c_id);
            fprintf(fc,"\tCustomer OTP : %s\n",temp1->otp);
            fprintf(fc,"\n\t---------------------------------------------------------------\n");
            fprintf(fc,"\tNo\t  Food Name     Quantity    Price\n");
            fprintf(fc,"\t---------------------------------------------------------------\n");
            for(int i=0; i<temp1->Item_q; i++)
            {
                Menu *temp3=temp1->ID[i];
                //printf("\t%d\t %d \t %s  \t %d    %.2f   \n",i+1,temp3->item_id,temp3->food_name,temp2->order_quantity[i],temp3->price);
                fprintf(fc,"\t%d\t %s \t  %d \t %.2f\n",i+1,temp3->food_name,temp1->order_quantity[i],temp3->price);
                fprintf(fc,"\t---------------------------------------------------------------\n");
            }
            fprintf(fc,"\tCustomer Bill : %.2f (Tk)\n",temp1->t_bill);
            fprintf(fc,"\t\tUpdate : %s\n\n",temp1->update);
            temp1=temp1->queue;
        }
        fclose(fc);
        ptr=ptr->link;
    }
}

void see_update()
{
    system("cls");
    vendor *ptr=head;
    printf("\t\tPlease input your OTP : ");
    fflush(stdin);
    char verification[100];
    gets(verification);
    int count6=0;//to cancel the loop;
    while(ptr!=NULL)
    {
        Order *temp=ptr->system;
        while(temp!=NULL)
        {
            if(strcmp(verification,temp->otp)==0)
            {
                display_custorder(temp,ptr);
                count6++;
                break;
            }
            else
            {
                temp=temp->queue;
            }
        }
        if(count6==1)
        {
            break;
        }
        else
        {
            ptr=ptr->link;
        }
    }
    if(count6==0)
    {
        printf("\tYou have no ordered food\n");
    }
    printf("\t\tGo back??\n");
    printf("\t\t1.Yes\n");
    int x;//to take yes or no;
    scanf("%d",&x);
    if(x==1)
    {
        main();
    }
}

void search()
{
    system("cls");
repeat:
    printf("\t\tPlease enter the food you want to find : ");
    int joke=0;
    char food[100],test[100];
    fflush(stdin);
    gets(food);
    vendor *temp=head;
    while(temp!=NULL)
    {
        Menu *temporary=temp->menu;
        while(temporary!=NULL)
        {
            strcpy(test,temporary->food_name);
            if(strcmp(test,food)==0)
            {

                printf("\t---------------------------------------------------------------------------\n");
                printf("\t%d | %d | %s | %s | %.2f | %d |\n",temp->serial,temporary->item_id,temp->shop_name,test,temporary->price,temporary->quantity);
                printf("\t---------------------------------------------------------------------------\n");
                joke++;
                break;
            }
            else
            {
                temporary=temporary->next;
            }
        }
        temp=temp->link;
        if(temp==NULL&&joke==0)
        {
            printf("\tThere is no food on this name!! Try Again.\n");
            goto repeat;
        }
    }
    printf("\tDo you want to go back??\n");
    printf("\t1. YEs\n");
    printf("\t2. No OR \n");
    printf("\n\t3Order food\n");

    int choice;
    printf("\tchoose :");
    scanf("%d",&choice);
    if(choice==1)
    {
        return main();
    }
    else if(choice==2)
    {
        goto repeat;
    }
    else if(choice==3)
    {
        order_customer();
    }


}


void authority()
{
    system("cls");
again:
    printf("\t\t\t---------------------------\n");
    printf("\t\t\t|                         |\n");
    printf("\t\t\t|          Admin          |\n");
    printf("\t\t\t|                         |\n");
    printf("\t\t\t---------------------------\n");
    printf("\t\t\t1.Add Vendor\n");
    printf("\t\t\t2.Delete Vendor\n");
    printf("\t\t\t0.LOG out\n");
    int num;
    printf("\t\t\tPlease choose from the option : ");
    scanf("%d",&num);
    if(num==1)
    {
        add_vendor();
    }
    else if(num==2)
    {
        del_vendor();
    }
    else if(num==0)
    {
        return main();
    }
    else
    {
        printf("\tYou choose the wrong option.Please try again\n");
        goto again;
    }
    printf("\tDo you want to log out\n");
    printf("\t\t1.Yes\n");
    int x;//to take yes or no;
    scanf("%d",&x);
    if(x==1)
    {
        main();
    }
}
int main()
{
    system("cls");
    while(1)
    {
        int num;
        printf("\t\t\t\t\t------------------\n");
        printf("\t\t\t\t\t|                |\n");
        printf("\t\t\t\t\t| UNI FOOD COURT |\n");
        printf("\t\t\t\t\t|                |\n");
        printf("\t\t\t\t\t------------------\n\n\n");
        printf("\t\t\t\t\t1.Authority\n");
        printf("\t\t\t\t\t2.See shop and menu\n");
        printf("\t\t\t\t\t3.Admin vendor\n");
        printf("\t\t\t\t\t4.Order food\n");
        printf("\t\t\t\t\t5.Track Your Order\n");
        printf("\t\t\t\t\t6.Search food\n");
        printf("\t\t\t\t\t0.Exit\n\n\n");
        printf("\t\t\t\t\tEnter your choice : ");
        scanf("%d",&num);
        switch(num)
        {
        case 1:
            authority_log();
            break;
        case 2:
            display_vendor();
            break;
        case 3:
            authentication();
            break;
        case 4:
            order_customer();
            break;
        case 5:
            see_update();
        case 6:
            search();
        case 0:
            exit(0);
        default:
            printf("enter again");
            break;
        }

    }
}

