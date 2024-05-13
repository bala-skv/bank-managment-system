#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int date,date0;
int month,month0;
int year,year0;


struct Customer {
  char name[50];
  char aadhar[15];
  char birth[15];
  char address[100];
  char ACnumber[15];
  float Balance;
  char password[20];
  int pin;
};

struct transaction {
  char acc[15];
  char Amount[100];
  char type[20];
  char Balance[100];
  char senders_acc[15];
  char transferee[15];
};

struct Customer *customers = NULL;
int numC = 0;
int maxC = 0;
int accountCounter = 10000000;

void readCustomerData();
void saveData();
int authenticateUser(char ACnumber[], char password[], int *index);
int authenticatePin(int pin, int index);
void displayMenu();
void balance(int index);
void withdraw(int index);
void deposit(int index);
void addNewUser();
void th(char *);
void TransferMoney(int index);
void updateDetail(int index);
float simpleinterest(char[]);
float timedifference(float,float,float,float,float,float);
char* getCustomerName(int index);

int main() {
  time_t now=time(NULL);
  //struct tm *gm_time=gmtime(&now);
  char *string_now=ctime(&now);
  maxC = 10;
  customers = malloc(maxC * sizeof(struct Customer));

  readCustomerData();

  int option;
  char ACnumber[15];
  char password[20];
  int index;
  int pin;

  while (1) {

    printf("\n%s",string_now);

    printf("\n======== Sample Bank =======\n");
    printf("===== 1. Login         =====\n");
    printf("===== 2. Add New User  =====\n");
    printf("===== 3. Exit          =====\n");
    printf("============================\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option) {
    case 1:
      printf("Enter Account Number: ");
      scanf("%s", ACnumber);
      printf("Enter Password: ");
      scanf("%s", password);

      if (authenticateUser(ACnumber, password, &index)) {
        while (1) {
        printf("\nHello, %s!\n", getCustomerName(index));

        displayMenu();
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
          balance(index);
          break;
        case 2:
          printf("Enter your PIN: ");
          scanf("%d", &pin);
          if (authenticatePin(pin, index)) {
            updateDetail(index);
          } else {
            break;
          }
          break;
        case 3:
          printf("Enter your PIN: ");
          scanf("%d", &pin);
          if (authenticatePin(pin, index)) {
            withdraw(index);
          } else {
            break;
          }
          break;
        case 4:
          printf("Enter your PIN: ");
          scanf("%d", &pin);
          if (authenticatePin(pin, index)) {
            deposit(index);
          } else {
            break;
          }
          break;
        case 5:
          printf("Enter your PIN : ");
          scanf("%d", &pin);
          if (authenticatePin(pin, index)) {
            TransferMoney(index);
          } else {
            break;
          }
          break;
        case 6:
          printf("Enter your PIN : ");
          scanf("%d", &pin);
          if (authenticatePin(pin, index)) {
            th(customers[index].ACnumber);
          } else {
            break;
          }
          break;
          case 7:
          break;
        default:
          printf("Invalid choice\n");
        }
        if (choice == 7)
        break;
        }
      } else {
        printf("Invalid login credentials\n");
      }
      break;
    case 2:
      addNewUser();
      break;
    case 3:
      saveData();
      free(customers);
      printf("Have a nice day!\n");
      return 0;
    default:
      printf("Invalid choice\n");
    }
  }
}

void readCustomerData() {
  FILE *file = fopen("final.txt", "r");

  while (
      fscanf(file, "%s %s %s %s %s %f %s %d", customers[numC].name,
            customers[numC].aadhar, customers[numC].birth,
            customers[numC].address, customers[numC].ACnumber,
            &customers[numC].Balance, customers[numC].password,
            &customers[numC].pin) == 8) {
    numC++;

    if (numC >= maxC) {
      maxC += 10;
      customers = realloc(customers, maxC * sizeof(struct Customer));
    }
  }

  fclose(file);
}

void saveData() {
  FILE *file = fopen("final.txt", "w");

  for (int i = 0; i < numC; i++) {
    fprintf(file, "%s %s %s %s %s %.2f %s %d\n", customers[i].name,
            customers[i].aadhar, customers[i].birth, customers[i].address,
            customers[i].ACnumber, customers[i].Balance, customers[i].password,
            customers[i].pin);
  }

  fclose(file);
}

int authenticateUser(char ACnumber[], char password[], int *index) {
  for (int i = 0; i < numC; i++) {
    if (strcmp(ACnumber, customers[i].ACnumber) == 0 &&
        strcmp(password, customers[i].password) == 0) {
      *index = i;
      return 1;
    }
  }
  return 0;
}

int authenticatePin(int pin, int index) {
    if (pin == customers[index].pin) {
      return 1;
    } else {
      printf(
          "Incorrect Password. You are not authentic. Program has been exited");
      return 0;
    }
  return 0;
}

// char* getCustomerName(int index) {
//   return customers[index].name;
// }

void displayMenu() {
  printf("\n========== SELECT OPTION =========\n");
  printf("===== 1. Balance             =====\n");
  printf("===== 2. Update your details =====\n");
  printf("===== 3. Withdraw            =====\n");
  printf("===== 4. Deposit             =====\n");
  printf("===== 5. Transfer            =====\n");
  printf("===== 6. Transaction History =====\n");
  printf("===== 7. Logout              =====\n");
  printf("==================================\n");
}

void withdraw(int index) {
  float amount;
  printf("Enter withdrawal amount: ");
  scanf("%f", &amount);

  if (amount > 0 && amount <= customers[index].Balance) {
    customers[index].Balance -= amount;
    printf("Withdrawal successful.");
    balance(index);
    saveData();
    time_t now=time(NULL);
    struct tm *gm_time=gmtime(&now);
    date=gm_time->tm_mday;
    month=(gm_time->tm_mon)+1;
    FILE *fp = fopen("Th.txt", "a");
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    int year1 = local_time->tm_year + 1900;
        int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    fprintf(fp, "%s -%.2f (Withdrawn) - %.2f %d %d %d ", customers[index].ACnumber,amount,customers[index].Balance,day,month,year1);
    fclose(fp);
  } else {
    printf("Insufficient funds\n");
  }
}

void deposit(int index) {
  float amount;
  printf("Enter deposit amount: ");
  scanf("%f", &amount);

  if (amount > 0) {
    customers[index].Balance += amount;
    printf("Deposit successful.");
    balance(index);
    saveData();
    time_t now=time(NULL);
    struct tm *gm_time=gmtime(&now);
    date=gm_time->tm_mday;
    month=(gm_time->tm_mon)+1;
    FILE *fp = fopen("Th.txt", "a");
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    int year1 = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    fprintf(fp, "%s +%.2f (Deposited) %.2f - %d %d %d ", customers[index].ACnumber, amount,customers[index].Balance,day,month,year1);
    fclose(fp);
  } else {
    printf("Invalid deposit amount\n");
  }
}

int isAccountNumberUsed(const char *accountNumber) {
    for (int i = 0; i < numC; i++) {
        if (strcmp(accountNumber, customers[i].ACnumber) == 0) {
            return 1;
        }
    }
    return 0;
}

void generateNextAccountNumber(char *accountNumber) {
    int tempCounter = accountCounter++;
    int digitCount = 0;

    while (tempCounter != 0) {
        tempCounter /= 10;
        digitCount++;
    }

    tempCounter = accountCounter;
    for (int i = digitCount - 1; i >= 0; i--) {
        accountNumber[i] = (tempCounter % 10) + '0';
        tempCounter /= 10;
    }

    accountNumber[digitCount] = '\0';
}

void addNewUser() {
    maxC += 1;
    customers = realloc(customers, maxC * sizeof(struct Customer));

    do {
        generateNextAccountNumber(customers[numC].ACnumber);
    } while (isAccountNumberUsed(customers[numC].ACnumber));

  printf("Enter user details:\n");
  printf("Name: ");
  scanf(" %[^\n]s", customers[numC].name);
  printf("Aadhar Number: ");
  scanf("%s", customers[numC].aadhar);
  printf("Birth Date: ");
  scanf("%s", customers[numC].birth);
  printf("Address: ");
  scanf("%s", customers[numC].address);
  customers[numC].Balance=0.00;
  printf("Password: ");
  scanf("%s", customers[numC].password);
  printf("PIN: ");
  scanf("%d", &customers[numC].pin);

    numC++;
    saveData();
    printf("=============================================================================================\n");
    printf("Your account has been created successfully, note down the Account Numer for furthur reference\nAccount Number: %s\n", customers[numC - 1].ACnumber);
    printf("=============================================================================================\n");
}
char* getCustomerName(int index) {
  return customers[index].name;
}


void th(char ACN[50]) {
  struct transaction u;
  FILE *fp = fopen("Th.txt", "r");
  int i = 0;
  char d[10],m[10],y[10];
  printf("=========================================================================================================\n\n");
  printf("   Account Number     Amount       Type of Transaction        Balance      Transferee's Account Number      Date");
  while (fscanf(fp, "%s %s %s %s %s %s %s %s", u.acc, u.Amount,u.type , u.Balance ,u.transferee,d,m,y) != EOF) {
    if (strcmp(u.acc, ACN) == 0) {
      if (strcmp(u.type,"(Debited)")== 0){
printf("\n%d.   %s         %s           %s              %s              %s              %s/%s/%s\n", ++i, u.acc, u.Amount,u.type ,u.Balance,
            u.transferee,d,m,y);
      }
      else if (strcmp(u.type,"(Credited)")== 0){
printf("\n%d.   %s         %s           %s             %s              %s              %s/%s/%s\n", ++i, u.acc, u.Amount,u.type ,u.Balance,
            u.transferee,d,m,y);

      }
      else {
      printf("\n%d.   %s         %s           %s            %s              %s              %s/%s/%s\n", ++i, u.acc, u.Amount,u.type ,u.Balance,
            u.transferee,d,m,y);
      }
    }
  }
  if (i == 0){
      printf("\n-         -              -                 -                     -                      -                   -");
      }
  printf("\n=========================================================================================================\n\n");
  fclose(fp);
}

void balance(int index) {
  printf("Your current balance is: %.2f\n", customers[index].Balance+simpleinterest(customers[index].ACnumber));
  printf("The principle amount is: %f\nThe interest is : %f\n",customers[index].Balance,simpleinterest(customers[index].ACnumber));
}

// void TransferMoney(int index) {
//     char targetAccount[15];
//     float amount;
//     int targetIndex;

//     printf("Enter account number in which you want to transfer money: ");
//     scanf("%s",targetAccount);

//     for (targetIndex = 0; targetIndex < numC; targetIndex++) {
//         if (strcmp(targetAccount, customers[targetIndex].ACnumber) == 0) {
//             break;
//         }
//     if (targetIndex==index)
//     {
//       printf("Cannot transfer money to yourself!!!");
//     }
//     else {
//     printf("Enter transfer amount: ");
//     scanf("%f", &amount);

//     if (amount > 0 && amount <= customers[index].Balance) {
//         customers[index].Balance -= amount;
//         customers[targetIndex].Balance += amount;

//         printf("Transfer successful.");
//         balance(index);
//         saveData();
//         time_t now=time(NULL);
//     struct tm *gm_time=gmtime(&now);
//     date=gm_time->tm_mday;
//     month=(gm_time->tm_mon)+1;
//     } else {
//         printf("insufficient funds\n");
//     }
//   FILE *fp = fopen("Th.txt", "a");
//   time_t t = time(NULL);
//     struct tm *local_time = localtime(&t);
//     int year1 = local_time->tm_year + 1900;
//   fprintf(fp, "%s +%f (Credited) %f %s %d %d %d ", customers[targetIndex].ACnumber, amount,customers[targetIndex].Balance,customers[index].ACnumber,date,month,year1);
//   fprintf(fp, "%s -%f (Debited) %f %s %d %d %d ", customers[index].ACnumber, amount,customers[index].Balance,customers[targetIndex].ACnumber,date,month,year1);
//   fclose(fp);
// }
// }
// }

void TransferMoney(int index) {
    char targetAccount[15];
    float amount;
    int targetIndex;

    printf("Enter account number in which you want to transfer money: ");
    scanf("%s", targetAccount);

    for (targetIndex = 0; targetIndex < numC; targetIndex++) {
        if (strcmp(targetAccount, customers[targetIndex].ACnumber) == 0) {
            break;
        }
    }

    if (targetIndex == numC) {
        printf("Error: The target account does not exist.\n");
        return;
    }

    printf("Enter transfer amount: ");
    scanf("%f", &amount);

    if (amount > 0 && amount <= customers[index].Balance) {
        customers[index].Balance -= amount;
        customers[targetIndex].Balance += amount;

        printf("Transfer successful. New balance: %.2f\n", customers[index].Balance);
        saveData();
    } else {
        printf("Insufficient funds or invalid transfer amount.\n");
    }
  FILE *fp = fopen("Th.txt", "a");
  time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    int year1 = local_time->tm_year + 1900;
        int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
  fprintf(fp, "%s +%.2f (Credited) %.2f %s %d %d %d ", customers[targetIndex].ACnumber, amount,customers[targetIndex].Balance,customers[index].ACnumber,day,month,year1);
  fprintf(fp, "%s -%.2f (Debited) %.2f %s %d %d %d ", customers[index].ACnumber, amount,customers[index].Balance,customers[targetIndex].ACnumber,day,month,year1);
  fclose(fp);
}

void updateDetail(int index) {
    int value;
    printf("\n=========== Menu ===========\n");
    printf("===== 1. Name          =====\n");
    printf("===== 2. Aadhar Number =====\n");
    printf("===== 3. Birth Date    =====\n");
    printf("===== 4. Address       =====\n");
    printf("===== 5. Password      =====\n");
    printf("===== 6. PIN           =====\n");
    printf("Which detail do you want to update:\n");
    scanf("%d",&value);
    switch(value) {
    case 1:
    printf("New Name: ");
    scanf(" %[^\n]s", customers[index].name);
    break;
    case 2:
    printf("New Aadhar Number: ");
    scanf("%s", customers[index].aadhar);
    break;
    case 3:
    printf("New Birth Date: ");
    scanf("%s", customers[index].birth);
    break;
    case 4:
    printf("New Address: ");
    scanf("%s", customers[index].address);
    break;
    case 5:
    printf("New Password: ");
    scanf("%s", customers[index].password);
    break;
    case 6:
    printf("New PIN: ");
    scanf("%d", &customers[index].pin);
    break;
    }

    saveData();
    printf("User information updated successfully\n");
}
float timedifference(float d,float d0,float m,float m0,float y,float y0){
float timediff=(((d-d0)/365)+ ((m-m0)/12)+ (y-y0));
return timediff;}
float simpleinterest(char ACN[50]) {
  char acc[20],sendersacc[20],hypen[10],balance[40];
  float amount;
  FILE *fp = fopen("Th.txt", "r");
  int i = 1;
  float principle=0;
  float time=0;
  float interest=0;
  float rate=0.08;
  while (fscanf(fp, "%s %f %s %s %s %d %d %d",acc,&amount,sendersacc,hypen,balance,&date,&month,&year) != EOF){
    if (strcmp(acc, ACN) == 0) {
    if(i>1){
      time=timedifference(date,date0,month,month0,year,year0);
      interest=interest+principle*rate*time;
      }
    principle=principle+amount;
    date0=date;
    month0=month;
    year0=year;
    i++;
    }
  }
  printf("\n=========================\n\n");
  fclose(fp);
  return interest;
}
