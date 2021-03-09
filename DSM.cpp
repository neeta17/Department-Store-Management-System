
//                              TO DESIGN AN OPTIMAL APPLICATION FOR DEPARTMENT STORE MANAGEMENT 


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<math.h>
#define pqsize 10
#define qsize 4   //4 bill desks
#define MAX 256
struct Product  //   Structure to store details of a product
{
 int code;
 float price;
 char itemname[20];

};

struct Date     
{
int dd,mm,yy;
};
 
struct Cust_Info         //This stores Customer Information
{
int cust_id,count;
char cust_name[20];
float TA[400];
struct Date D;
};

struct Cust_Que                                   // Structure to store customer information with their respective product list
{
 struct Product pdc[100];                         //Customer Product -pdc
 struct  Cust_Info info;

};


struct Bill_Desk                                   //4 Bill desks are considered
{   struct Cust_Que CQ[pqsize*qsize];              
	int front;
};

int isFull(struct Bill_Desk bd)                         //To check if queue is full
{
	if(bd.front==pqsize*qsize-1)                       
	return 1;
	else
	 return 0;
}

int isEmpty(struct Bill_Desk bd)                        // To check if queue is Empty
{
if(bd.front==-1)
	return 1;
	else
	 return 0;

}

struct Bill_Desk Cust_Enqueue(struct Cust_Que cq,struct Bill_Desk PQ )   //To enqueue customer information in Priority Queue
 {
 int i=PQ.front;

 while(i>-1 && cq.info.count<PQ.CQ[i].info.count)
 {
 PQ.CQ[i+1]=PQ.CQ[i];
 i--;
 }
 PQ.CQ[i+1]=cq;
 PQ.front=PQ.front+1;
 return PQ;
 }


void Cust_Dequeue(struct Bill_Desk Q)        // To dequeue Customer from Queue Once their Bill is ready
 {
  Q.front=Q.front-1;

 }

 optimization( struct Bill_Desk Q,int c)        // Function to create bill of customers with increasing order of No.of products purchased.
 {

   int cust_size=c/qsize,i,j,k;
   struct Bill_Desk BQ[qsize];
     for(i=1,j=1;j<=c,i<=c;i++,j++)
     {
	  FILE *fptr=fopen("STOCK.txt","r");
      FILE *fp=fopen("BILL.txt","a");
	  BQ[i].CQ[j]=Q.CQ[j];
	  fprintf(fp,"\nID:%d NAME:%s NO.OF PRODUCTS:%d\n",BQ[i].CQ[j].info.cust_id,BQ[i].CQ[j].info.cust_name,BQ[i].CQ[j].info.count);
	  fprintf(fp,"%d-%d-%d\n",BQ[i].CQ[j].info.D.dd,BQ[i].CQ[j].info.D.mm,BQ[i].CQ[j].info.D.yy);
	  BQ[i].CQ[j].info.TA[j]=0;
      fprintf(fp,"Products purchased are:\n");
      fprintf(fp,"\nProduct Code  Product Name         Price");
     for(k=0;k<Q.CQ[j].info.count;k++)
      	{ fscanf(fptr,"%d%s%f",&BQ[i].CQ[j].pdc[k].code,BQ[i].CQ[j].pdc[k].itemname,&BQ[i].CQ[j].pdc[k].price);
		  fprintf(fp,"\n%d                %s              %.2f",BQ[i].CQ[j].pdc[k].code,BQ[i].CQ[j].pdc[k].itemname,BQ[i].CQ[j].pdc[k].price);
      	  BQ[i].CQ[j].info.TA[j]=BQ[i].CQ[j].info.TA[j]+BQ[i].CQ[j].pdc[k].price;
		}
		 fprintf(fp," \n                         Total Amount =%.2f\n",BQ[i].CQ[j].info.TA[j]);
	    	    fprintf(fp,"\n                Your Bill Is Ready");
                fprintf(fp,"\n                   Visit again");
       fprintf(fp,"\n********THANK YOU*******");
		fprintf(fp,"\n========================================================================");
		

	if(!isEmpty(BQ[i]))
      Cust_Dequeue(BQ[i]);

      fclose(fptr);
	  fclose(fp);
     }
 }




  struct Bill_Desk generate_bill(int c)  //Funtion to store products purchased by a customer in a  Priority Queue
    {
	  int cust_size,DD,MM,YY,i,j,k;
      time_t t;
      srand((unsigned)time(&t));

      float Total_Amount[pqsize*qsize];
      char name[20];
      FILE *fptr;
      fptr=fopen("STOCK.txt","r");
      struct Cust_Que CQ[c];//BD-Bill Desk
      struct Bill_Desk Q;
      Q.front=0;
      printf("\nEnter todays date :");
      scanf("%d %d %d",&DD,&MM,&YY);
	  if(c<=pqsize*pqsize)
      {
	  for(j=0;j<c;j++)
      {
	  CQ[j].info.count=rand()%100;
	  struct Product PD[CQ[j].info.count];

      if(CQ[j].info.count<=100)
      {
	  printf("\nEnter customer Name");
      scanf("%s",name);
      strcpy(CQ[j].info.cust_name,name);
      printf(" Total No.of Products Purchased by %s is %d\n",CQ[j].info.cust_name,CQ[j].info.count);

      CQ[j].info.cust_id=rand();
	  CQ[j].info.D.dd=DD;
      CQ[j].info.D.mm=MM;
      CQ[j].info.D.yy=YY;

     }
           if(!isFull(Q))
         Q=Cust_Enqueue(CQ[j],Q);
	}
	optimization(Q,c);
}
      else
    printf("Bill Desk Queue FULL");
      return Q;
}

 int display_Stock()                      //To create File to store stock of products
 {
 	//create a FILE variable
 	FILE *fptr;

 	//integer variable
 	int i,j;
 	struct Product pds[100];


 	//open the file in write mode
 	fptr=fopen("STOCK.txt","w");

 	if(fptr!= NULL)
 	{
 		printf("File Created Successfully!\n");
	 }
	 else
	 {
	 	printf("Failed to create file!\n");
	 	//exit status for an OS tha an error occured
	 	return -1;
	 }
	 printf("Enter item_code,item_name ,price for 100 products\n");
	 // get item detail

	 for(i=0;i<100;i++)
	 {
	 scanf("%d%s%f",&pds[i].code,pds[i].itemname,&pds[i].price);
	 //write data in file
	 fprintf(fptr,"%d %s %.2f\n",pds[i].code,pds[i].itemname,pds[i].price);
 }

	 //close connection
 fclose(fptr);

	  return 0;

 }

    Delete()                // Function To delete a product from stock
   {
        int ctr = 1,code;
        char ch;
        FILE *fptr1, *fptr2;
		char fname[MAX];
        char str[MAX], temp[] = "temp.txt";
		printf("\n\n Delete a specific line from a file :\n");
		printf("-----------------------------------------\n");
		printf(" Input the file name to be opened : ");
		scanf("%s",fname);
        fptr1 = fopen(fname, "r");
        if (!fptr1)
		{
                printf(" File not found or unable to open the input file!!\n");
                return 0;
        }
        fptr2 = fopen(temp, "w"); // open the temporary file in write mode
        if (!fptr2)
		{
                printf("Unable to open a temporary file to write!!\n");
                fclose(fptr1);
                return 0;
        }
        printf(" Input the Item Code you want to remove : ");
        scanf("%d", &code);
		code++;
        // copy all contents to the temporary file except the specific line
        while (!feof(fptr1))
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            if (!feof(fptr1))
            {
                ctr++;
                /* skip the line at given line number */
                if (ctr != code)
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove(fname);  		// remove the original file
        rename(temp, fname); 	// rename the temporary file to original name
//------ Read the file ----------------/
   fptr2=fopen(temp,"r");
            ch=fgetc(fptr2);
          printf(" Now the content of the file %s is : \n",temp);
          while(ch!=EOF)
            {
                printf("%c",ch);
                 ch=fgetc(fptr1);
            }
        fclose(fptr1);
//------- End of reading ---------------/
        return 0;

  }


int main()
{
   int y,g,o;
   struct Bill_Desk Q;

   printf("                 =================================================================================================");
   printf("\n");
   printf("\n");
   printf("\n");
   printf("                                           WELCOME TO DEPARTMENT MANAGEMENT SYSTEM        ");
   printf("\n");
   printf("\n");
   printf("                 ==================================================================================================\n");
   printf("Enter The Total No.of customers who need bill to be created");
   scanf("%d",&y);
   
   display_Stock();
   
   Q=generate_bill(y);
 
   printf("Want To Delete any Product in Stock\n");
   printf("Enter Choice(0/1)");
   scanf("%d",&o);
   if(o==1)
   Delete();
   return 0;
}
