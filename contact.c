#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
//#include "populate.h"

void listContacts(AddressBook *addressBook,int sortCriteria)
{
    // Sort contacts based on the chosen criteria
    int choice;
    int i, j;
    Contact temp;

    printf("Sort by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            for(i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(j = i + 1; j < addressBook->contactCount;j++)
                {
                    if(strcasecmp(addressBook->contacts[i].name,
                              addressBook->contacts[j].name) > 0)
                    {
                        temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            printf("SI.no\tName\t\tPhone Number\tEmail ID\n");
            for(int i=0; i < addressBook -> contactCount; i++)
            {
                printf("  %d\t%s\t\t%s\t%s\n", i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
             case 2:
            for(i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(j = i + 1; j < addressBook->contactCount; j++)
                {
                    if(strcmp(addressBook->contacts[i].phone,
                              addressBook->contacts[j].phone) > 0)
                    {
                        temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            printf("SI.no\tName\t\tPhone Number\tEmail ID\n");
            for(int i=0; i < addressBook -> contactCount; i++)
            {
                printf("  %d\t%s\t\t%s\t%s\n", i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;

        case 3:
            for(i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(j = i + 1; j < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].email,
                              addressBook->contacts[j].email) > 0)
                    {
                        temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            printf("SI.no\tName\t\tPhone Number\tEmail ID\n");
            for(int i=0; i < addressBook -> contactCount; i++)
            {
                printf("  %d\t%s\t\t%s\t%s\n", i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;

        default:
            printf("Invalid input");
            return;
    }

    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nName: %s", addressBook->contacts[i].name);
        printf("\nPhone: %s", addressBook->contacts[i].phone);
        printf("\nEmail: %s\n", addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int i;
      
      while(1)
      {
        int valid=1;
        printf("Enter Name: ");
        scanf("%s",addressBook->contacts[addressBook->contactCount].name);
        
        //Check duplicate name
        for(i=0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[addressBook->contactCount].name,
                addressBook->contacts[i].name) == 0)
                {
                    valid = 0;
                    printf("Re - enter Valid Name, Name already exists\n");
                    break;
                }
        }
        if(valid == 0)
        continue;
       
        //Check name characters
        for(i=0; addressBook->contacts[addressBook->contactCount].name[i]!='\0';i++)
        {
            if(isalnum(addressBook->contacts[addressBook->contactCount].name[i])==0)
            {
                valid = 0;
                printf("Re-enter Valid Name. Name should not contain punctuation\n");
                break;
            }
        }
        
        if(valid == 1)
        {
            break;
        }
    }

    //Phone

      while(1)
      {
        int valid=1;
        printf("Enter Phone: ");
        Phone:
         scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
        
       //Check digits
        for(i = 0; addressBook->contacts[addressBook->contactCount].phone[i] != '\0'; i++)
      {
            if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])==0)
        {
            valid = 0;
            printf("Re-enter valid Phone Number. Only digits 0-9 allowed\n");
            break;
        }
      }

      if(valid == 0)
      continue;

   //Check 10 digits and first digit greater than 5 
        if(strlen(addressBook->contacts[addressBook->contactCount].phone) != 10 ||
           addressBook->contacts[addressBook->contactCount].phone[0] < '6')
        {
            printf("Re-enter Phone Number. It should have 10 digits and start from 6-9!\n");
            continue;
        }

      //Check duplicate phone 
        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[addressBook->contactCount].phone,
                      addressBook->contacts[i].phone) == 0)
            {
                valid = 0;
                printf("Re-enter Valid Phone Number. Number already exists!\n");
                break;
            }
        }

        if(valid == 1)
            break;
    }
     
     //Email

      while(1)
   {
       printf("Enter Email: ");
      Email:
      scanf("%s", addressBook->contacts[addressBook->contactCount].email);
        char *email = addressBook->contacts[addressBook->contactCount].email;

        int at_count = 0;
        int at_pos =-1;
        int valid = 1;
        int len;

        //Check duplicate email
        for(i=0; i < addressBook->contactCount; i++)
        {
            if(strcmp(email, addressBook->contacts[i].email) == 0)
            {
                valid = 0;
                printf("Re-enter Valid Email. Email already exists!\n");
                break;
            }
        }

        if(valid==0)
        continue;

        // Check Lowercase, space and @
        for(i=0; email[i]!='\0'; i++)
        {
            if(isupper(email[i]) || email[i] == ' ')
            {
                valid = 0;
                printf("Re-enter Valid Email. Use lowercase and no spaces\n");
                break;
            }

            if(email[i] == '@')
            {
                at_count++;
                at_pos = i;
            }
        }

        if(valid == 0)
        continue;

        len = strlen(email);

        //Cheak @
        if(at_count  !=1 || at_pos == 0)
        {
            valid = 0;
            printf("Re-enter Valid Email. Only one @ is allowed\n");
        }

        if(valid == 0)
            continue;

        //check .com
        if(len < 4 || strcmp(email + len-4, ".com") !=0)
        {
            valid = 0;
            printf("Re-enter Valid Email. Email must end with .com\n");
        }

        if(valid == 0)
        continue;

        //At least one character btwn @ nd .com
        if(at_pos + 1 >= len-4)
        {
            valid = 0;
            printf("Re-enter Valid Email. Enter a character between @ and .com\n");
        }

        if(valid == 1)
        {
            break;
        }
   }

   addressBook->contactCount++;
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    int i;
    char search[50];

    printf("Search contact using:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter Name: ");
        scanf("%s", search);
    }
    else if(choice == 2)
    {
        printf("Enter Phone: ");
        scanf("%s", search);
    }
    else if(choice == 3)
    {
        printf("Enter Email: ");
        scanf("%s", search);
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(choice == 1)
        {
            if(strstr(addressBook->contacts[i].name, search) != NULL)
            {
                printf("\nName: %s", addressBook->contacts[i].name);
                printf("\nPhone: %s", addressBook->contacts[i].phone);
                printf("\nEmail: %s\n", addressBook->contacts[i].email);
                return;
            }
        }

        else if(choice == 2)
        {
            if(strstr(addressBook->contacts[i].phone, search) != NULL)
            {
                printf("\nName: %s", addressBook->contacts[i].name);
                printf("\nPhone: %s", addressBook->contacts[i].phone);
                printf("\nEmail: %s\n", addressBook->contacts[i].email);
                return;
            }
        }
        else if(choice == 3)
        {
            if(strstr(addressBook->contacts[i].email, search) != NULL)
            {
                printf("\nName: %s", addressBook->contacts[i].name);
                printf("\nPhone: %s", addressBook->contacts[i].phone);
                printf("\nEmail: %s\n", addressBook->contacts[i].email);
                return;
            }
        }
    }

    printf("Contact not found!\n");

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char name[50];
    char phone[20];
    char email[50];
    int i;
    int choice;

    printf("Edit contact using:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {

        printf("Enter Name to edit: ");
        scanf("%s", name);

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].name,name) != NULL)
            {
                printf("\nContact found!\n");
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("Email: %s\n", addressBook->contacts[i].email);

                printf("\nEnter New Name: ");
                scanf("%s", addressBook->contacts[i].name);

                printf("Enter New Phone: ");
                scanf("%s", addressBook->contacts[i].phone);

                printf("Enter New Email: ");
                scanf("%s", addressBook->contacts[i].email);

                printf("Contact updated successfully!\n");
                return;
            }
        }
    }

    else if(choice == 2)
    {
        printf("Enter Phone: ");
        scanf("%s", phone);

        for(i=0; i<addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].phone,phone)!=NULL)
            {
                printf("\nContact found!\n");
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("Email: %s\n", addressBook->contacts[i].email);

                printf("\nEnter New Name: ");
                scanf("%s", addressBook->contacts[i].name);

                printf("Enter New Phone: ");
                scanf("%s", addressBook->contacts[i].phone);

                printf("Enter New Email: ");
                scanf("%s", addressBook->contacts[i].email);

                printf("Contact updated successfully!\n");
                return;

            }
        }
    }

    else if(choice == 3)
    {
        printf("Enter Email: ");
        scanf("%s", email);

        for(i=0; i<addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].email, email) !=NULL)
            {
                printf("\nContact found!\n");
                printf("Name: %s\n", addressBook->contacts[i].name);
                printf("Phone: %s\n", addressBook->contacts[i].phone);
                printf("Email: %s\n", addressBook->contacts[i].email);

                printf("\nEnter New Name: ");
                scanf("%s", addressBook->contacts[i].name);

                printf("Enter New Phone: ");
                scanf("%s", addressBook->contacts[i].phone);

                printf("Enter New Email: ");
                scanf("%s", addressBook->contacts[i].email);

                printf("Contact updated successfully!\n");
                return;
            }
        }
    }

        else
        {
            printf("Invalid choice\n");
            return;
        }
        printf("Contact not found!\n");
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char name[50];
    char phone[20];
    char email[50];
    int choice;
    int i, j;

    printf("Delete contact using:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter Name: ");
        scanf("%s", name);

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].name, name) == 0)
            {
                for(j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] =
                    addressBook->contacts[j + 1];
                }

                addressBook->contactCount--;

                printf("Contact deleted successfully!\n");
                return;
            }
        }
    }

    else if(choice == 2)
    {
        printf("Enter Phone: ");
        scanf("%s", phone);

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                for(j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] =
                    addressBook->contacts[j + 1];
                }

                addressBook->contactCount--;

                printf("Contact deleted successfully!\n");
                return;
            }
        }
    }

    else if(choice == 3)
    {
        printf("Enter Email: ");
        scanf("%s", email);

        for(i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].email, email) == 0)
            {
                for(j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] =
                    addressBook->contacts[j + 1];
                }

                addressBook->contactCount--;

                printf("Contact deleted successfully!\n");
                return;
            }
        }
    }

    else
    {
        printf("Invalid choice!\n");
        return;
    }

    printf("Contact not found!\n");
}
