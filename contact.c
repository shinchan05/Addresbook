// ================================================================
// AddressBook System - Core Functions
// Handles create, edit, search, delete, and save of contacts
// Includes duplicate checking and input validation
// ================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int isDuplicate(AddressBook *addressBook, char *phone, char *email) 
{
     // Loop through all contacts in the address book
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Compare phone or email to detect duplicates
        if (strcmp(addressBook->contacts[i].phone, phone) == 0 ||
            strcmp(addressBook->contacts[i].email, email) == 0) {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicates
}
// Display all contacts in a formatted table
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
     printf("%-3s %-20s %-15s %-30s\n", "No", "Name", "Phone", "Email");
printf("---------------------------------------------------------------\n");
  for(int i=0;i<addressBook->contactCount;i++)
  {
    printf("%-3d %-20s %-15s %-30s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

  }

}
// Initialize address book and load existing contacts from file
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Save all contacts and exit program
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
// Function to create and add a new contact with validation

void createContact(AddressBook *addressBook)
{
    // Temporary structure to hold input
	/* Define the logic to create a Contacts */
    struct contact
    {
        char name[120];
        char phone[14];
        char email[100];
    };
    struct contact s1;
    
    nameloop:
    printf("Enter the Name\n");
    getchar();
    scanf("%[^\n]",s1.name);
    // Validate name (only alphabets allowed)
    for(int i=0;s1.name[i]!='\0';i++)
    {
      
        if((s1.name[i]>='A' && s1.name[i]<='Z')||(s1.name[i]>='a' && s1.name[i]<='z'))
        {
          printf("entered Name is  %s",s1.name); 
          break;
        }
        else 
        {
            printf("Enter valid name ");
            goto nameloop;
        }

    } 
    
    phoneloop:
    printf("\nenter the phone number : \n");
    scanf("%s",s1.phone);
    int len=strlen(s1.phone);
    if(len<10||len>10)
    {
        printf("enter valid number");
        goto phoneloop;
    }
    else{
          // Validate that all characters are digits
    for(int i=0;s1.phone[i]!='\0';i++)
    {
        if((s1.phone[i]>='0' && s1.phone[i]<='9'))
        {
          printf("entered phone number  %s",s1.phone); 
          break;
        }
        else 
        {
            printf("Enter valid phone number");
            goto phoneloop;
        }

    } 
    emailloop:
    printf("\nEnter the email\n");
    char s2[50]={"@gmail.com"};
    scanf("%s",s1.email);
    // Validate email format
    char *ptr;
    (ptr=strstr(s1.email,s2));
      
    if(s1.email[0]!='@')
    {
      if((ptr!=NULL)&&((strcmp(ptr,s2)==0)&& strlen(ptr) == strlen(s2)))
      {
        
    for(int i=0;s1.email[i]!='\0';i++)
    {
        if((s1.email[i]>='A' && s1.email[i]<='Z')||(s1.email[i]==' '))
        {
          printf("email: must not contain uppercase letters or spaces."); 
          goto emailloop;
          break;
        }
        else 
        {
            printf("entered email is %s\n",s1.email);
            break;

        }

    } 
    }
    else 
    {
        printf("enter a valid gmail ending with @gmail.com");
        goto emailloop;
    }
    if (isDuplicate(addressBook, s1.phone, s1.email))
            {
                printf("\n Duplicate contact found! (same phone/email)\n");
                printf("\nReenter the phone number and email");
                goto phoneloop;
            }

    //addressBook->contactCount++;
    strcpy(addressBook->contacts[addressBook->contactCount].name,s1.name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,s1.phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,s1.email);
    //addressBook->contactCount++;
    printf("\nContact created");
    printf("\n%s\t\t%s\t\t%s\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email);
    addressBook->contactCount++;
}
else
{
    printf("email should not start with @");
    goto emailloop;
}
}

}

// Function to search contacts by name, phone, or email
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int n;
    printf("select which you need to search \n1=name\n2=phone\n3=email\n");
    scanf("%d",&n);
   
    switch (n)
    {
        case 1:
        char name[50];
        int i;
        printf("Enter the name\n");\
        getchar();
        scanf("%[^\n]",name);
        int count=0;
        for( i=0;i<addressBook->contactCount;i++)
        {
            if(strcasestr(addressBook->contacts[i].name,name)!=NULL)
            {
                count=1;
                printf("%-3d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);    
            }   
        }
        if(count==0)
        {
            printf("not found");
        }
        break ;
        case 2:
        char phone[50];
        int j;
        printf("Enter the phone number \n");
        scanf("%s",phone);
        int flag=0;
        for( j=0;j<addressBook->contactCount;j++)
        {
            if(strstr(addressBook->contacts[j].phone,phone)!=NULL)
            {
                flag=1;
                //printf("found");
               printf("%s\t\t%s\t\t%s\n",addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
                //break;   
            }   
        }
        if(flag==0)
        {
            printf("not found");
        }

        break;
        case 3:
        char email[50];
        int k;
        printf("Enter the email\n");
        scanf("%s",email);
        int sta=0;
        for( k=0;k<addressBook->contactCount;k++)
        {
            if(strstr(addressBook->contacts[k].email,email)!=NULL)
            {
                sta=1;
               
                printf("%s\t\t%s\t\t%s\n",addressBook->contacts[k].name,addressBook->contacts[k].phone,addressBook->contacts[k].email);
                //break;   
            }   
        }
       // break;
        if(sta==0)
        {
            printf("not found");
        }
        break;
    
        default:
        printf("Inavalid: enter valid option\n");
    }
}
// Edit an existing contact's name, phone, or email
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
   int n;
    printf("select which you need to edit \n1=name\n2=phone\n3=email\n");
    scanf("%d",&n);
   
    switch (n)
    {
        case 1:
        char name[50];
        int i;
        printf("Enter the name to serach\n");
        scanf("%s",name);
        printf("enter the name to replace\n");
        char name1[100];
        getchar();
        scanf("%[^\n]",name1);
        int count=0;
        for( i=0;i<addressBook->contactCount;i++)
        {
            if(strcasestr(addressBook->contacts[i].name,name)!=NULL)
            {
                count=1;
               printf("%s\t\t%s\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
             strcpy(addressBook->contacts[i].name,name1); 
            printf("%s\t\t%s\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
              break;   
            } 

        }
         
        if(count==0)
        {
            printf("not found");
        }
        break ;
        case 2:
        char phone[50];
        int j;
        printf("Enter the phone number \n");
        scanf("%s",phone);
        phoneloop:
        printf("enter the phone number to replace\n");
        char phone1[100];
        scanf("%s",phone1);
        int len=strlen(phone1);
    if(len<10||len>10)
    {
        printf("enter valid number\n");
        goto phoneloop;
    }
    else
    {
        int flag=0;
        if (isDuplicate(addressBook, phone1, ""))
    {
                printf("\n Duplicate contact found! (same phone/email)\n");
                printf("\n Reenter the phone number\n");
                goto phoneloop;
    }   
        for( j=0;j<addressBook->contactCount;j++)
        {
            if(strstr(addressBook->contacts[j].phone,phone)!=NULL)
            {
                flag=1;
               printf("%s\t\t%s\t\t%s\n",addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
               strcpy(addressBook->contacts[j].phone,phone1); 
                printf("%s\t\t%s\t\t%s\n",addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
                break;   
            }   
        }
        if(flag==0)
        {
            printf("not found");
        }
    }
    break;
    case 3:
        char email[50];
        int k;
        printf("Enter the previous email\n");
        scanf("%s",email);
        getchar();
    emailloop1:
        printf("enter the email to replace\n");
        char email1[100];
        scanf("%s",email1);
        char s2[50]={"@gmail.com"};
        char *ptr;
        int sta=0;
        (ptr=strstr(email1,s2));
      
    if(email1[0]!='@')
    {
      if((ptr!=NULL)&&(strcmp(ptr,s2)==0&& strlen(ptr) == strlen(s2)))
      {
        
    for(int i=0;email1[i]!='\0';i++)
    {
        if((email1[i]>='A' && email1[i]<='Z')||(email1[i]==' '))
        {
          printf("Invalid email: contains capital letters or spaces\n"); 
          goto emailloop1;
          break;
        }
        else 
        {
            printf("\nentered email is %s\n",email1);
            break;
        }

    } 
    }
    else 
    {
        printf("enter a valid gmail ending with @gmail.com");
        goto emailloop1;
    }
    if (isDuplicate(addressBook,"", email1))
    {
                printf("\n Duplicate contact found! (same phone)\n");
                printf("\n Reenter the phone  email");
                goto emailloop1;
    }        
        for( k=0;k<addressBook->contactCount;k++)
        {
            if(strcasestr(addressBook->contacts[k].email,email)!=NULL)
            {
                sta=1;
                printf("%s\t\t%s\t\t%s\n",addressBook->contacts[k].name,addressBook->contacts[k].phone,addressBook->contacts[k].email);
                strcpy(addressBook->contacts[k].email,email1); 
                printf("%s\t\t%s\t\t%s\n",addressBook->contacts[k].name,addressBook->contacts[k].phone,addressBook->contacts[k].email);
                break;   

            }   
        }
      
        if(sta==0)
        {
            printf("not found");
        }   
    }
    else
    {
        printf("gmail should not start with @");
    } 
    break;
    }
}
// Delete a contact by name, phone, or email
void deleteContact(AddressBook *addressBook)
{
    {
	/* Define the logic for deletecontact */
      int n;
    
    printf("select which you need to delete \n1=name\n2=phone\n3=email\n");
    scanf("%d",&n);
    switch (n)
    {
        case 1:
       // int n;
    name:   
     int foundindexes[100];
     int foundcount=0;
        char name[50];
        int i;
        printf("Enter the name\n");
        scanf("%s",name);
        int count=0;
        for( i=0;i<addressBook->contactCount;i++)
        {
            if(strcasestr(addressBook->contacts[i].name,name) != NULL)
            {
                
                printf("%d %s\t\t%s\t\t%s\n",foundcount+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                foundindexes[foundcount++] = i; 
            } 
            
        }
        if(foundcount==0)
        {
            printf("not found");
            break;
        }
           int choice;
          printf("Enter the number of the contact to delete (1-%d): ", foundcount);
             scanf("%d", &choice);

            if (choice < 1 || choice > foundcount)
                {
                printf("Invalid choice.\n");
                 
                }
    printf("Do you really want to delete(y/n)\n");
    char ch;
    getchar();
    scanf("%c",&ch);
    if(ch=='y')
    {
    int indexToDelete = foundindexes[choice - 1];
    for(int j=indexToDelete;j<addressBook->contactCount;j++)
                {
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                }
                (addressBook->contactCount--);
                printf("sucessfully deleted\n");
    }
    else 
    {
        goto name;
    }
        break ;

    case 2:
   // int m;
     int foundindexes1[100];
     int foundcount1=0;
        char phone[50];
        int j;
        printf("Enter the phone number\n");
        scanf("%s",phone);
        //int count=0;
        for( j=0;j<addressBook->contactCount;j++)
        {
            if(strstr(addressBook->contacts[j].phone,phone) != NULL)
            {
                
                printf("%d %s\t\t%s\t\t%s\n",foundcount1+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email);
                foundindexes1[foundcount1++] = j; 
            }   
        }
        if(foundcount1==0)
        {
            printf("not found");
            break;
        }
           int choice1;
          printf("Enter the number of the contact to delete (1-%d): ", foundcount1);
             scanf("%d", &choice1);

            if (choice1 < 1 || choice1 > foundcount1)
                {
                printf("Invalid choice.\n");
                 //return 0;
                }

    int indexToDelete1 = foundindexes1[choice1 - 1];
    for(int j=indexToDelete1;j<addressBook->contactCount;j++)
                {
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                }
                (addressBook->contactCount--);
                printf("sucessfully deleted");
    break ;
       case 3:
   // int m;
     int foundindexes2[100];
     int foundcount2=0;
        char email[50];
        int k;
        printf("Enter the email\n");
        scanf("%s",email);
        //int count=0;
        for( k=0;k<addressBook->contactCount;k++)
        {
            if(strstr(addressBook->contacts[k].email,email) != NULL)
            {
                
                printf("%d %s\t\t%s\t\t%s\n",foundcount2+1,addressBook->contacts[k].name,addressBook->contacts[k].phone,addressBook->contacts[k].email);
                foundindexes2[foundcount2++] = k; 
            }   
        }
        if(foundcount2==0)
        {
            printf("not found");
            break;
        }
           int choice2;
          printf("Enter the number of the contact to delete (1-%d): ", foundcount2);
             scanf("%d", &choice2);

            if (choice2 < 1 || choice2 > foundcount2)
                {
                printf("Invalid choice.\n");
                 //return 0;
                }

    int indexToDelete2 = foundindexes2[choice2 - 1];
    for(int j=indexToDelete2;j<addressBook->contactCount;j++)
                {
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                }
                (addressBook->contactCount--);
                printf("sucessfully deleted");
    break ;
    }
    }
} 



