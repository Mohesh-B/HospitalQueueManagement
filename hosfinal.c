#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
int doc_id=1;
int pat_tok=1;
int pat_id=1;
int no_of_doctors;
int pass_admin;
void readadminpass()
{
    FILE *ptr;
    ptr=fopen("adminpass.txt","r");
    fscanf(ptr,"%d",&pass_admin);
    fclose(ptr);
}
void update_admin_pass()
{
    FILE *ptr;
    ptr=fopen("adminpass.txt","w");
    fprintf(ptr,"%d",pass_admin);
    fclose(ptr);
}
struct docnode
{
    int d_id;
    char docName[50];
    int password;
    char speciality[50];
    struct Patientnode *pat1;
    struct docnode *nextdoc;
};
struct docnode *dhead;
struct Patientnode
{
    
    char diagnosis[1000];
    char issue[50];
    char name[100];
    int age;
    char address[100];
    int phone;
    char bloodgroup[100];
    int Criticality;
    struct Patientnode *next;
};
void rewrite()
{
    FILE *p;
    p=fopen("doctors.txt","w");
    struct docnode *temp;
    temp=dhead;
    while(temp!=NULL)
    {
        fprintf(p,"%d %s %s %d\n",temp->d_id,temp->docName,temp->speciality,temp->password);
        temp=temp->nextdoc;
    }
    fclose(p);
}
void insert_Newdoc_file()
{
    
    FILE *fptr;
    fptr=fopen("doctors.txt","r");
    if(fptr==NULL)
    {
        puts("Cannot open the file!!");
        exit(1);
    }
    int id,pw;
    char name[100];
    char spec[100];
    while( fscanf(fptr,"%d %s %s %d",&id,name,spec,&pw)!=EOF)
    {
        struct docnode *ptr;
    ptr=(struct docnode*)malloc(sizeof(struct docnode));
    ptr->d_id=id;
    ptr->password=pw;
    memcpy(ptr->docName, name, strlen(name));
    memcpy(ptr->speciality, spec, strlen(spec));
        ptr->nextdoc=NULL;
        if(dhead==NULL)
        {
        dhead=ptr;
        }
        else
        {
            struct docnode *temp;
            temp=dhead;
            while(temp->nextdoc!=NULL)
            {
                temp=temp->nextdoc;
            }
            temp->nextdoc=ptr;
            temp=ptr;
            
        }
        no_of_doctors++;
       
    }
    fclose(fptr);
}
void insert_Newdoc()
{
    no_of_doctors++;
   struct docnode *ptr;
    char docname[100];
    char* address[100];
    ptr=(struct docnode*)malloc(sizeof(struct docnode));
    FILE *fp;
    fp=fopen("doctors.txt","a+");
    ptr->d_id=no_of_doctors;
    printf("Enter Doctor Name:");
    getchar();
    scanf("%[^\n]s",ptr->docName);
    getchar();
    printf("Enter Doctor's Speciality:");
    scanf(" %s",ptr->speciality);
    printf("SET Doctor's Password:");
    scanf(" %d",&ptr->password);
    fprintf(fp,"\n%d %s %s %d",ptr->d_id,ptr->docName,ptr->speciality,ptr->password);
    fclose(fp);
    ptr->nextdoc=NULL;
        if(dhead==NULL)
        {
        dhead=ptr;
        }
        else
        {
            struct docnode *temp;
            temp=dhead;
            while(temp->nextdoc!=NULL)
            {
                temp=temp->nextdoc;
            }
            temp->nextdoc=ptr;
            temp=ptr;
            
        }
        no_of_doctors++;
        printf("%s is added to the doctor list\nThe doctor id is :%d",ptr->docName,ptr->d_id);
}

void show_patient_queue()
{
    struct docnode *temp;
    struct Patientnode *ptr;
    printf("Enter the id of the doctor you want to Check:");
    int val0;
    scanf("%d",&val0);
    temp=dhead;
    while(temp->nextdoc!=NULL&&temp->d_id!=val0)
    {
        temp=temp->nextdoc;
    }
    if(temp->pat1==NULL)
    printf("No patient waiting at the moment!!");
    else{
    ptr=temp->pat1;
    if(ptr==NULL)
    printf("No patient waiting at the moment!!");
    while(ptr!=NULL)
    {
        char name1[100];
       // name1=ptr->name;
        printf("\n\n\n---------------------------------------------------\n");
                printf("The name of patient is:%s\n",ptr->name);
                printf("The age of patient is:%d\n",ptr->age);
                printf("The address of patient is : %s\n",ptr->address);
                printf("Phone Number:%d\n",ptr->phone);
                printf("The blood group of patient is:%s\n",ptr->bloodgroup);
                printf("Criticality:%d\n",ptr->Criticality);
                printf("---------------------------------------------------\n\n\n");
                ptr=ptr->next;
    }
    }
}
int patient_count(int val0)
{
    struct docnode *temp;
    struct Patientnode *ptr;
    int ct=0;
    temp=dhead;
    while(temp->nextdoc!=NULL&&temp->d_id!=val0)
    {
        temp=temp->nextdoc;
    }
    if(temp->pat1==NULL)
    return ct;
    else{
    ptr=temp->pat1;
    }
    while(ptr!=NULL)
    {
        ct++;
        ptr=ptr->next;
    }
    return ct;
}
void display_doc()
{
    struct docnode *temp;
    temp=dhead;
    while(temp!=NULL)
    {
        int count;
        int doc_id;
        doc_id=temp->d_id;
        count=patient_count(doc_id);
        printf("\n\n\n_______________________________________________________________________________________________\n");
        printf("Doctor_ID:%d\tNAME:%s\tDEPARTMENT:%s\t\nNumber of patients currently waiting:%d\n",temp->d_id,temp->docName,temp->speciality,count);
        printf("\n________________________________________________________________________________________________\n\n\n");  
        temp=temp->nextdoc;
    }
}
void diagnose(int id)
{
   
    struct docnode *temp;
    temp=dhead;
    while(temp->nextdoc!=NULL&&temp->d_id!=id)
    {
        temp=temp->nextdoc;
    }
    if(temp->pat1==NULL)
    printf("You don't have any patients yet!!");
    else{
        getchar();
        printf("Enter your Diagnosis:");
        scanf("%s",temp->pat1->diagnosis);
        printf("Diagnosis Entered!!");
        FILE *pat;
        pat=fopen("patientlog.txt","a");
        fprintf(pat,"Doctor_id:%d Doctor_name:%s Patient_name:%s Patient_issue:%s Patient_diagnosis:%s",temp->d_id,temp->docName,temp->pat1->name,temp->pat1->issue,temp->pat1->diagnosis);
        fclose(pat);
}
}
void current_patient_details(int id)
{
    struct docnode *temp;
    temp=dhead;
    while(temp->nextdoc!=NULL&&temp->d_id!=id)
    {
        temp=temp->nextdoc;
    }
    struct Patientnode *ptr;
    ptr=temp->pat1;
    if(ptr==NULL)
    printf("No patients yet!!");
    else{
                printf("\n\n\n---------------------------------------------------\n");
                printf("The name of patient is:%s\n",ptr->name);
                printf("The age of patient is:%d\n",ptr->age);
                printf("The address of patient is : %s\n",ptr->address);
                printf("Phone Number:%d\n",ptr->phone);
                printf("The blood group of patient is:%s\n",ptr->bloodgroup);
                printf("Criticality:%d\n",ptr->Criticality);
                printf("Issue:%s\n",ptr->issue);
                printf("---------------------------------------------------\n\n\n");
    
}}
void nextpatient(int id)
{
    struct docnode *temp;
    temp=dhead;
    while(temp->nextdoc!=NULL&&temp->d_id!=id)
    {
        temp=temp->nextdoc;
    }
    struct Patientnode *ptr;
    struct Patientnode *ptr1;
    ptr=temp->pat1;
        if(ptr==NULL)
    {
        printf("No Patient available!");
    }
    else{
        temp->pat1=ptr->next;
        free(ptr);

    printf("Next Patient Has Arrived!!");}
}
void show_patients(int id)
{
    struct docnode *temp;
    temp=dhead;
    
    while(temp->nextdoc!=NULL&&temp->d_id!=id)
    {
        temp=temp->nextdoc;
    }
    struct Patientnode *ptr;
    ptr=temp->pat1;
    if(ptr==NULL)
    {
        printf("No Patients!!");
        return ;
    }
    while(ptr!=NULL){
     printf("\n\n\n---------------------------------------------------\n");
                printf("The name of patient is:%s\n",ptr->name);
                printf("The age of patient is:%d\n",ptr->age);
                printf("The address of patient is : %s\n",ptr->address);
                printf("Phone Number:%d\n",ptr->phone);
                printf("The blood group of patient is:%s\n",ptr->bloodgroup);
                printf("Criticality:%d\n",ptr->Criticality);
                printf("Issue:%s\n",ptr->issue);
                printf("---------------------------------------------------\n\n\n");
    ptr=ptr->next;
    }
    
}
void change_doc_pass(int id)
{
    struct docnode *temp;
    temp=dhead;
    int old_pass;
    int new_pass;
    while(temp->nextdoc!=NULL&&temp->d_id!=id)
    {
        temp=temp->nextdoc;
    }
    printf("Enter your Old password:");
    scanf("%d",&old_pass);
    if(temp->password==old_pass)
    {
        printf("Enter you New password:");
        scanf("%d",&new_pass);
        printf("Password Updated");
        temp->password=new_pass;
        rewrite();
    }
    else
    {
        printf("Wrong Password");
    }
}
struct Patientnode *start= NULL;
struct Patientnode *insert();


struct Patientnode *insert()
{
    int val2,val4,val6,pri,val0;
    char val1,val3,val5;
    struct Patientnode *ptr,*p;
    char* name[100];
    char* address[100];
    ptr=(struct Patientnode*)malloc(sizeof(struct Patientnode));
    printf("Enter patient Name:");
    scanf(" %[^\n]s",ptr-> name);
    printf("Enter the patient's age:");
    scanf("%d",&val2);
    printf("Enter your home address:");
    scanf(" %[^\n]s",ptr->address);
    printf("Enter your phone number:");
    scanf("%d",&val4);
    printf("Enter the blood group of Patient:");
    scanf(" %[^\n]s",ptr->bloodgroup);
    printf("Enter the issue:");
    getchar();
    scanf("%[^\n]s",ptr->issue);
    printf("Enter the patient's criticality\n(REMEMBER THIS POINT SHOULD BE EVALUATED \nBASED ON THE SITUATION OF THE PATIENT AT THE MOMENT)\n");
    scanf("%d",&pri);
    printf("Enter doctor the patient wants to see(If patient doesnot have a choice then \nsend him to the respective department based on his injury):");
    scanf("%d",&val0);
    //ptr->name=name;
    ptr->age=val2;
    //ptr->address=address;
    ptr->phone=val4;
   //ptr->reg=val6;
    ptr->Criticality=pri;
    struct docnode *temp;
    temp=dhead;
    while(temp->nextdoc!=NULL)
    {
        if(temp->d_id==val0)
        {
            break;
        }
        else
        {
            temp=temp->nextdoc;
        }
    }
    int ct=1;
    if((temp->pat1==NULL)||pri<temp->pat1->Criticality)
    {
        ptr->next=temp->pat1;
        temp->pat1=ptr;
        printf("The doctor is free now you can send the patient in");
    }
    else
        {
            p=temp->pat1;
            while(p->next!=NULL && p->next->Criticality <=pri)
            
            {
                ct++;
                p=p->next;
            }
            printf("You can Send the patient after %d patients",--ct);
            ptr->next=p->next;
            p->next=ptr;
        }
        return temp->pat1;
}
void delete_update(int de_id)
{
    FILE *fpd,*fpt;
    fpd=fopen("doctors.txt","r");
    fpt=fopen("temp.txt","w");
      int id,pw;
    char name[100];
    char spec[100];
    while( fscanf(fpd,"%d %s %s %d",&id,name,spec,&pw)!=EOF)
    {
        fprintf(fpt,"%d %s %s %d\n",id,name,spec,pw);
    }
    fclose(fpd);
    fclose(fpt);
    FILE *fpdr;
    fpdr=fopen("doctors.txt","w");
    fpt=fopen("temp.txt","r");
     while( fscanf(fpt,"%d %s %s %d",&id,name,spec,&pw)!=EOF)
    {
        if(id!=de_id)
        fprintf(fpdr,"%d %s %s %d\n",id,name,spec,pw);
    }
    fclose(fpd);
    fclose(fpdr);
}

void delete_doc()
{
    int id;
    printf("Enter the doctor id to be deleted:");
    scanf("%d",&id);
    struct docnode *temp;
     struct docnode *temp1;
    temp=dhead;
    if(temp->d_id==id)
    {
        free(temp);
        printf("The doctor has been fired!!");
        return ;
    }
    while(temp->nextdoc!=NULL&&temp->d_id!=id)
    {
        temp1=temp;
        temp=temp->nextdoc;
    }
    if(temp->pat1==NULL){
    temp1->nextdoc=temp->nextdoc;
    free(temp);
    delete_update(id);
    }
    else
    {
        printf("This doctor currently has patients waiting for him..");
    }
    
}
int main()
{
    //textcolor(3);
    int pass_old;
        int pass_new;
        readadminpass();
   /* insert_Newdoc();
    insert_Newdoc();
    insert_Newdoc();
    show_doc_list();*/
    insert_Newdoc_file();
    int option;
    int entry;
    do{
    printf("\n\t\t\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t WELCOME TO MOHESH HOSPITAL!\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t  LOGIN\n");
        printf("\n\t\t\t\t\t\t\t1)I am front door-Admin!\n");
        printf("\t\t\t\t\t\t\t2)I am a Doctor!\n");
        printf("\t\t\t\t\t\t\t3)Exit\n");
        printf("\t\t\t\t\t\t\tChoice:");
        scanf("%d",&entry);
        if(entry==1)
       {
         int pass;
        printf("\n\t\t\t\t\t\t\tEnter password:");
        scanf("%d",&pass);
        if(pass==pass_admin)
        {
    do{
         printf("\n\n\t\t\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t WELCOME TO MOHESH HOSPITAL!\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t\t\t1.APPOINT A PATIENT\n");
        printf("\t\t\t\t\t\t\t2.ADD A DOCTOR\n");
        printf("\t\t\t\t\t\t\t3.DISPLAY APPOINTMENTS\n");
        printf("\t\t\t\t\t\t\t4.DISPLAY DOCTORS\n");
        printf("\t\t\t\t\t\t\t5.FIRE A DOCTOR\n");
        printf("\t\t\t\t\t\t\t6.Change Password\n");
        printf("\t\t\t\t\t\t\t7.Exit\n");
        printf("\t\t\t\t\t\t\tEnter your choice:");
        scanf("%d",&option);
    switch(option)
    {
    case 1:
        insert();
        getchar();
        //system("cls");
        break;
    case 2:
        
        insert_Newdoc();
        getchar();
        break;
        case 3:
        show_patient_queue();
        getchar();
       // system("cls");
        break;
        case 4:
        display_doc();
        break;
        case 5:
        delete_doc();
        break;
    case 6:
        printf("\t\t\t\t\t\t\t;Enter old Password:");
        scanf("%d",&pass_old);
        if(pass_old==pass_admin)
        {
            printf("\t\t\t\t\t\t\tEnter new Password:");
            scanf("%d",&pass_new);
            pass_admin=pass_new;
            printf("\t\t\t\t\t\t\tPassword Changed!!");
            update_admin_pass();
        }
        else
        {
            printf("\t\t\t\t\t\tIncorrect Password\n");
        }
        break;
        case 7:
        break;
    }
    }while(option!=7);
        }
          else
        {
            printf("\t\t\t\t\t\t\t\tIncorrect Password");
        }
       }
    else if(entry==2)
    {
        int option1;
         int id;
        printf("\n\t\t\t\t\t\t\tEnter Doctor_ID:");
        scanf("%d",&id);
        if(id>no_of_doctors)
        {
            printf("\t\t\t\t\t\t\tINVALID DOCTOR ID\n");
        }
        else
        {
        struct docnode * ptr;
        ptr=dhead;
        while(ptr!=NULL&&ptr->d_id!=id)
        {
            ptr=ptr->nextdoc;
        }
        int pass;
        printf("Enter Your Password:");
        scanf("%d",&pass);
        if(pass==ptr->password)
        {
    do{
        
         printf("\n\n\t\t\t\t\t\t\t------------------------------\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t WELCOME TO MOHESH HOSPITAL!\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t\t\t1.ENTER/UPDATE DIAGOSIS\n");
        printf("\t\t\t\t\t\t\t2.CURRENT PATIENT DETAILS\n");
        printf("\t\t\t\t\t\t\t3.NEXT PATIENT\n");
        printf("\t\t\t\t\t\t\t4.DISPLAY PATIENT QUEUE\n");
        printf("\t\t\t\t\t\t\t5.CHANGE PASSWORD\n");
        printf("\t\t\t\t\t\t\t6.Exit\n");
        printf("\t\t\t\t\t\t\tEnter your choice:");
        scanf("%d",&option1);
    switch(option1)
    {
        case 1:
        diagnose(id);
        break;
        case 2:
        current_patient_details(id);
        break;
        case 3:
        nextpatient(id);
        break;
        case 4:
        show_patients(id);
        break;
        case 5:
        change_doc_pass(id);
        break;
        case 6:
        break;
    }
    }while(option1!=6);
}
        else
        {
            printf("Incorrect Password");
        }
    }}}while(entry!=3);
        }
        

