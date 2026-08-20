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
                for(j = i + 1; j < addressBook->contactCount; j++)
                {
                    if(strcmp(addressBook->contacts[i].name,
                              addressBook->contacts[j].name) > 0)
                    {
                        temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
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
            break;

        case 3:
            for(i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(j = i + 1; j < addressBook->contactCount; j++)
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
            break;

        default:
            printf("Invalid choice!\n");
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
      printf("Enter Name: ");
      name:
      scanf("%s",addressBook->contacts[addressBook->contactCount].name);
      for(i=0; addressBook->contacts[addressBook->contactCount].name[i]!='\0';i++)
      {
        if(isalnum(addressBook->contacts[addressBook->contactCount].name[i])==0)
        {
            printf("Re-enter Valid Name which should not contains panctuation Characters like !,@,#,$,%%,&,*.....");
            goto name;
        }

      }
       printf("Enter Phone: ");
       Phone:
      scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
      for(i = 0; addressBook->contacts[addressBook->contactCount].phone[i] != '\0'; i++)
      {
        if(isdigit(addressBook->contacts[addressBook->contactCount].phone[i])==0)
        {
            printf("Re-enter Valid Phone\n");
            goto Phone;
        }
      }
     

       printf("Enter Email: ");
       Email:
      scanf("%s", addressBook->contacts[addressBook->contactCount].email);
      for(i=0; addressBook->contacts[addressBook->contactCount].email[i]!='\0';i++)
      {
        if(!isalnum(addressBook->contacts[addressBook->contactCount].email[i]) && 
            addressBook->contacts[addressBook->contactCount].email[i] != '@' &&
       addressBook->contacts[addressBook->contactCount].email[i] != '.') 
        {
            printf("Re-enter Valid Email\n");
            goto Email;
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
    int i;

    printf("Enter Name to edit: ");
    scanf("%s", name);

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strstr(addressBook->contacts[i].name,name))
        {
            printf("Enter New Name: ");
            scanf("%s", addressBook->contacts[i].name);

            printf("Enter New Phone: ");
            scanf("%s", addressBook->contacts[i].phone);

            printf("Enter New Email: ");
            scanf("%s", addressBook->contacts[i].email);

            printf("Contact edited successfully!\n");
            return;
        }
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
