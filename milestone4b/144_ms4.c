// Final Project Milestone 1

// Student defined values tester

// Version 1.0

// Date 2017/03/07

// Author       Vaibhav Moradiya

// Description

// This program test the student implementation of the UI tools

// and Application User Interface for submission.

//

/////////////////////////////////////////////////////////////////


#include <stdio.h>
// tools
#define LINEAR 1

#define STOCK   1
#define CHECKOUT   0
#define MAX_ITEM_NO     500
#define MAX_QTY                 999
#define SKU_MAX                 999
#define SKU_MIN                 100
#define FORM 0
#define DATAFILE "144_fp_items.txt"


const double TAX = 0.13;

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);
int locateItem(const struct Item item[], int record, int sku, int *list);
void listItems(const struct Item item[], int no_Items);
double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
void displayItem(struct Item item, int linear);
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQuantity(struct Item item[], int NoOfRecs, int stock);
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);
void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(const struct Item item[], char fileName[], int NoOfRecs);

// app interface
int yes(void);
void GroceryInventorySystem(void);
int menu();
void GroceryInventorySystem(void) {

	int optn, flag = 0, record;

	struct Item item[MAX_ITEM_NO];

	welcome();

	if (loadItems(item, DATAFILE, &record) == 0)
	{
		printf("Could not read from %s.\n", DATAFILE);
	}
	else
	{
		do
		{
			optn=menu();
			switch (optn)
			{
		case 1:
				//printf("List Items under construction!\n");.
				listItems(item, record);
				pause();
				break;
		case 2:
				//printf("Search Items under construction!\n");.
				search(item, record);
				pause();
				break;
		case 3:
				//printf("Checkout Item under construction!\n");.
				adjustQuantity(item, record, CHECKOUT);
				saveItems(item, DATAFILE, record);
				pause();
				break;
		case 4:
				//printf("Stock Item under construction!\n");.
				adjustQuantity(item, record, STOCK);
				saveItems(item, DATAFILE, record);
				pause();
				break;
		case 5:
				//printf("Add/Update Item under construction!\n");.
				addOrUpdateItem(item, &record);
				saveItems(item, DATAFILE, record);
				pause();
				break;
		case 6:
				printf("Not implemented!\n");
				pause();
				break;
		case 7:
				printf("Not implemented!\n");
				pause();
			     case 0:
				printf("Exit the program? (Y)es/(N)o): ");
				 flag = yes();
				 break;
				       }
				   } while (optn != 0 || flag == 0);




}
}






void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n\n");
};
void printTitle(void) {

	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn");
	printf("\n----+---+--------------------+--------+-----+-----+-----+------------|---");
};


void printFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal>0) {
		printf("                                           Grand Total: |%12.2lf\n", gTotal);
	}
};

void flushKeyboard(void) {
   // getchar();
    while(getchar() != '\n');
};
void pause(void) {
	printf("Press <ENTER> to continue...");
	flushKeyboard();
	//printf("\n");
};
int getInt(void) {
	int ival;
	char NL = 'x';

	do {
		scanf("%d%c", &ival, &NL);
		if (NL != '\n') {
			flushKeyboard();
			printf("Invalid integer, please try again: ");

		}
	} while (NL != '\n');
	return ival;


};

int getIntLimited(int lowerLimit, int upperLimit) {

	int ival;

	do {
		ival = getInt();
		if (ival<lowerLimit || ival>upperLimit) {
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		}


	} while (ival<lowerLimit || ival>upperLimit);
	return ival;
};

double getDouble(void) {
	double dval;
	char NL;

	do {
		scanf("%lf%c", &dval, &NL);


		if (NL != '\n') {
			flushKeyboard();
			printf("Invalid number, please try again: ");
		}
	} while (NL != '\n');
	return dval;
};

double getDoubleLimited(double lowerLimit, double upperLimit) {

	double dval;



	do {
		dval = getDouble();

		if (dval<lowerLimit || dval>upperLimit) {

			printf("Invalid value, %.6lf< value < %.6lf: ", lowerLimit, upperLimit);

		}

	} while (dval<lowerLimit || dval>upperLimit);

	return dval;
};

int yes(void) {
	int flag;

	char choice;
	flag = -1;
	//choice=getchar();
    scanf(" %c",&choice);
	do {
		switch (choice) {
		case 'y':
		case 'Y':
			flag = 1;
			break;
		case 'n':
		case 'N':
			flag = 0;
			break;

		default:
			flushKeyboard();

			printf("Only (Y)es or (N)o are acceptable: ");

			choice=getchar();
			flag = -1;
			break;
		}
	} while (flag == -1);


	return flag;
};


int menu() {
	double max = 7, min = 0, l = 0,optn;
	printf("1- List all items\n2- Search by SKU\n3- Checkout an item\n4- Stock an item");
	printf("\n5- Add new item or update item\n6- delete item\n7- Search by name\n0- Exit program\n> ");
	//optn=getLimited(min,max);
	l = getIntLimited(min, max);
	optn = l;
	return optn;
};


double totalAfterTax(struct Item item) {
	double total = item.price * item.quantity;
	if (item.isTaxed == 1) {
	 total = total * (1 + TAX);
	 }
	return total;
	}


int isLowQuantity(struct Item item) {

	if (item.quantity <= item.minQuantity)
		return 1;


	else
		return 0;


}

struct Item itemEntry(int sku) {
	struct Item item;
	item.sku = sku;
	printf("        SKU: %d\n", item.sku);
	printf("       Name: ");
	scanf("%20s[^\n]", item.name);
	flushKeyboard();
	printf("      Price: ");
	item.price = getDoubleLimited(0.01,1000.00);
	printf("   Quantity: ");
	item.quantity = getIntLimited(1,MAX_QTY);
	printf("Minimum Qty: ");
	item.minQuantity = getIntLimited(0,100);
	printf("   Is Taxed: ");
	item.isTaxed = yes();
	flushKeyboard();
	return item;
}

void displayItem(struct Item item, int linear) {
	double price = totalAfterTax(item);
	if (linear == 1)
	{
		if (item.isTaxed == 1)
		{
			printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, item.quantity, item.minQuantity, price);
		}
		else
		{
			printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, item.quantity, item.minQuantity, price);
		}
		if (isLowQuantity(item) == 1)
		{
			printf("***\n");
		}
		else
		{
			printf("\n");
		}

	}

	else
	{
		if (item.quantity<item.minQuantity) {
	    printf("        SKU: %d\n", item.sku);
		printf("       Name: %s\n", item.name);
		printf("      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		printf("   Is Taxed: ");
		if (item.isTaxed == 1){

			printf("Yes\n");
		}else {
			printf("No\n");
		}
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}else{
		printf("        SKU: %d\n", item.sku);
		printf("       Name: %s\n", item.name);
		printf("      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);
		printf("   Is Taxed: ");
		if (item.isTaxed == 1){

			printf("Yes\n");
		}else {
			printf("No\n");
		}
		}
	}
}


void listItems(const struct Item item[], int no_Items)
{
	double grand_total = 0;
	int count;
	printTitle();
	printf("\n");
	for (count = 0; count < no_Items; count++)
	{
		printf("%-4d", count + 1);
		displayItem(item[count], LINEAR);
		grand_total += totalAfterTax(item[count]);
	}
	printFooter(grand_total);
}


int locateItem(const struct Item item[], int record, int sku, int *list) {
	int v;
	int worth = 0;
	for (v = 0; v < record; v++)
	{
		if (sku == item[v].sku)
		{
			worth = 1;
			*list = v;
			break;
		}
	}
	return worth;

}

/*void addItem(struct Item item[], int *NoOfRecs, int sku);
void addItem(struct Item item[], int *NoOfRecs, int sku){
       if(*NoOfRecs==MAX_ITEM_NO)
	    printf("Can not add new item; Storege Full!");
       else{
	    itemEntry(sku);}


};*/

void search(const struct Item item[], int NoOfRecs){
    printf("Please enter the SKU: ");

    int sfu,flag=0,searchIndex=0/*FORM=0*/;//here sfu is sku from an user to search from user
    sfu=getIntLimited(SKU_MIN,SKU_MAX);
    flag=locateItem(item,NoOfRecs,sfu,&searchIndex);

    if(flag==1){
	//here indx is after search getting back index of perticular sku
	 displayItem(item[searchIndex],FORM);}
    else{
	printf("Item not found!\n");
    }
};


void updateItem(struct Item* itemptr){
    int flag;
    printf("Enter new data:\n");//aligned_storage
    struct Item instance;
    instance=*itemptr;

    //printf("%d",instance.sku);
    instance=itemEntry(instance.sku);
    printf("Overwrite old data? (Y)es/(N)o: ");
    flag=yes();
	if(flag==1){
	   *itemptr=instance;

	   printf("--== Updated! ==--\n");

	   }
    else
	printf("-== Aborted! ==--\n");
      getchar();
};


void addItem(struct Item item[], int *NoOfRecs, int sku){
	int flag;
	struct Item k;
	 //printf("\nye bhi dekho%d\n",&NoOfRecs);
	if(*NoOfRecs==MAX_ITEM_NO){
	    printf("Can not add new item; Storage Full!\n");
	}

	else{
	    k=itemEntry(sku);
	    printf("Add Item? (Y)es/(N)o: ");
	    flag=yes();
	    if(flag==1){
		 item[*NoOfRecs]=k;
		*NoOfRecs=*NoOfRecs+1;
		printf("--== Added! ==--\n");
	    }
	    else{
		printf("--== Aborted! ==--\n");
	    }

	}if (item[*NoOfRecs].quantity < item[*NoOfRecs].minQuantity) {
		printf("Quantity is low, please reorder ASAP!!!\n");
	    }
};
void addOrUpdateItem(struct Item item[], int* NoOfRecs){
    int sku,searchIndex=0/*FORM=1*/;
    int yn,flag=0;


    //struct Item k;-just for test in between


    printf("Please enter the SKU: ");
    sku=getIntLimited(SKU_MIN,SKU_MAX);
    flag=locateItem(item,*NoOfRecs,sku,&searchIndex);


    if(flag){

	//printf("\n1%d",searchIndex);
	displayItem(item[searchIndex],FORM);


	printf("Item already exists, Update? (Y)es/(N)o: ");
	yn=yes();
	//printf("%d",yn);
	if(yn==1){

	     updateItem(&item[searchIndex]);
	     //item[serchIndex]=k;
	     //printf("jkbdsjs");

	    }

	else{
	    printf("--== Aborted! ==--\n");
	    //to avoid getting garbage value
	    getchar();}
	}

    else{
	//printf("jkdcbdsj");
	//printf("/ndekho bhai%d/n",&NoOfRecs);
		addItem(item,NoOfRecs,sku);//why like this; my mistake
	getchar();
    }

       //return item;

}



void adjustQuantity(struct Item item[], int NoOfRecs, int stock)        //function to adjust the quantity based on value of STOCK and CHECKOUT
{
    int sku, flag, searchIndex=0, change, newQuantity;
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN, SKU_MAX);
    flag = locateItem(item, NoOfRecs, sku, &searchIndex);
    if (flag == 1) {
	displayItem(item[searchIndex], FORM);
	newQuantity = MAX_QTY - item[searchIndex].quantity;
	printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ",(stock == STOCK) ? "to stock" : "to checkout",(stock == STOCK) ? newQuantity : item[searchIndex].quantity);
	change=getIntLimited(0,(stock == STOCK) ? newQuantity : item[searchIndex].quantity);
	if (change == 0) {
	    printf("--== Aborted! ==--\n");
	} else if (change > 0
		   && change < (stock == STOCK) ? newQuantity : item[searchIndex].quantity) {
	    if (stock == STOCK) {
		item[searchIndex].quantity = item[searchIndex].quantity+change;
		printf("--== Stocked! ==--\n");
	    }
	    else {
		item[searchIndex].quantity = item[searchIndex].quantity -change;
		printf("--== Checked out! ==--\n");
	    }
	    if (item[searchIndex].quantity <= item[searchIndex].minQuantity) {
		printf("Quantity is low, please reorder ASAP!!!\n");
	    }
	}
    } else {
	printf("SKU not found in storage!\n");
    }
}

void saveItem(struct Item item, FILE* dataFile){

    fprintf(dataFile,"%d,%d,%d,%.2f,%d,%s\n",item.sku,item.quantity,item.minQuantity,item.price,item.isTaxed,item.name);

}

int loadItem(struct Item* item, FILE* dataFile){
    int fv=0;
    /*float ttl;
     ttl=totalAfterTax(item);*/
     fv=fscanf(dataFile,"%d,%d,%d,%lf,%d,%[^\n]",&(*item).sku,&(*item).quantity,&(*item).minQuantity,&(*item).price,&(*item).isTaxed,(*item).name);
     return fv;
};

int saveItems(const struct Item item[], char fileName[], int NoOfRecs){
  //FILE *fp=fileName;
  int i=0;
  FILE *fp=NULL;
  fp=fopen(fileName,"w+");
  if(fp==NULL){
     return 0;
     }
  else{
    for(i=0;i<NoOfRecs;i++){
	//printf("%d",item[i].sku);
	saveItem(item[i],fp);
    }
    fclose(fp);
    return 1;
  }

};

int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr){
   FILE *fp;
   int j=0;
   fp=fopen(fileName,"r+");
   if(fp==NULL){
    return 0;
   }
   else{
   while(loadItem(&item[j],fp)==6){
     j++;
   }
   *NoOfRecsPtr=j;
   fclose(fp);
   return 1;
   }
};

int main(void) {
   GroceryInventorySystem();
   return 0;
}

