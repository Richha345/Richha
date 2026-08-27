#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
//#include "populate.h"


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------//


void display(AddressBook *addressBook)
{
    printf("\n-------------------------------------------------------------------------------------");
    printf("\nSl.no\tName\t\tPhone Number\tEmail ID\n");
    printf("-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("  %d\t%s\t\t%s\t%s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("-------------------------------------------------------------------------------------\n");
}

void sortby_name(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            if (strcasecmp(addressBook->contacts[i].name,
                           addressBook->contacts[j].name) > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    display(addressBook);
}

void sortby_phone(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            if (strcmp(addressBook->contacts[i].phone,
                       addressBook->contacts[j].phone) > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    display(addressBook);
}

void sortby_email(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            if (strcmp(addressBook->contacts[i].email,
                       addressBook->contacts[j].email) > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    display(addressBook);
}


//-----------------------------------------------------------------display contacts---------------------------------------------------------------------------------//


void listContacts(AddressBook *addressBook)
{
    // Sort contacts based on the chosen criteria
    int choice;

    while (1)
    {
        printf("\nDisplay contacts by:\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                sortby_name(addressBook);
                continue;

            case 2:
                sortby_phone(addressBook);
                continue;

            case 3:
                sortby_email(addressBook);
                continue;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
                continue;
        }

        break;
    }

}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int name_validation(char *name, AddressBook *addressBook, int index)
{
    int i;

    // Check whether the name already exists
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (i != index)
        {
            if (strcasecmp(name, addressBook->contacts[i].name) == 0)
            {
                printf("Name already exists. Enter another name: ");
                return 0;
            }
        }
    }

    // Check whether name contains only alphabets and numbers
    i = 0;

    while (name[i] != '\0')
    {
        if (isalnum(name[i]) == 0)
        {
            printf("Name should not contain special characters: ");
            return 0;
        }

        i++;
    }

    return 1;
}

int phone_validation(char *phone, AddressBook *addressBook, int index)
{
    int i;

    // Check whether phone contains only digits
    i = 0;
    while (phone[i] != '\0')
    {
        if (isdigit(phone[i]) == 0)
        {
            printf("Phone number should contain only digits: ");
            return 0;
        }
        i++;
    }

    // Check phone number length and starting digit
    if (strlen(phone) != 10 || phone[0] < '6')
    {
        printf("Phone number should contain 10 digits and start from 6-9: ");
        return 0;
    }

    // Check whether phone number already exists
    i = 0;
    while (i < addressBook->contactCount)
    {
        if (i != index)
        {
            if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                printf("Phone number already exists. Enter another number: ");
                return 0;
            }
        }

        i++;
    }

    return 1;
}

int email_validation(char *email, AddressBook *addressBook, int index)
{
    int i;
    int at_count = 0;
    int at_position = -1;
    int length;

    // Check for duplicate email
    i = 0;
    while (i < addressBook->contactCount)
    {
        if (i != index)
        {
            if (strcmp(email, addressBook->contacts[i].email) == 0)
            {
                printf("Email already exists. Enter another email: ");
                return 0;
            }
        }

        i++;
    }

    // Check uppercase letters, spaces and count @ symbol
    i = 0;
    while (email[i] != '\0')
    {
        if (isupper(email[i]) != 0 || email[i] == ' ')
        {
            printf("Email should be lowercase and should not contain spaces: ");
            return 0;
        }

        if (email[i] == '@')
        {
            at_count++;
            at_position = i;
        }

        i++;
    }

    length = strlen(email);

    // Check @ symbol and characters before .com
    if (email[0] == '@' ||
        at_count != 1 ||
        at_position > length - 6)
    {
        printf("Invalid email format: ");
        return 0;
    }

    // Check whether email ends with .com
    if (length < 4 || strcmp(email + length - 4, ".com") != 0)
    {
        printf("Email should end with .com: ");
        return 0;
    }

    return 1;
}


//-----------------------------------------------------------------create contacts---------------------------------------------------------------------------------//


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    // Get name
    printf("Enter Name: ");
    scanf("%s", addressBook->contacts[addressBook->contactCount].name);

    while (name_validation(addressBook->contacts[addressBook->contactCount].name,
                            addressBook, -1) == 0)
    {
        scanf("%s", addressBook->contacts[addressBook->contactCount].name);
    }

    // Get phone number
    printf("Enter Phone Number: ");
    scanf("%s", addressBook->contacts[addressBook->contactCount].phone);

    while (phone_validation(addressBook->contacts[addressBook->contactCount].phone,
                            addressBook, -1) == 0)
    {
        scanf("%s", addressBook->contacts[addressBook->contactCount].phone);
    }

    // Get email
    printf("Enter Email ID: ");
    scanf("%s", addressBook->contacts[addressBook->contactCount].email);

    while (email_validation(addressBook->contacts[addressBook->contactCount].email,
                             addressBook, -1) == 0)
    {
        scanf("%s", addressBook->contacts[addressBook->contactCount].email);
    }

    addressBook->contactCount++;

    printf("Contact added successfully.\n");

}

void search_display_name(AddressBook *addressBook, char *search)
{
    int i;
    int flag = 0;

    // Search contact by name
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].name, search))
        {
            // Print heading only once
            if (flag == 0)
            {
                printf("\n-------------------------------------------------------------------------------------\n");
                printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
                 printf("-------------------------------------------------------------------------------------\n");
                flag = 1;
            }

            // Display matching contact
            printf("  %d\t%s\t\t%s\t%s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
        }
    }
 printf("-------------------------------------------------------------------------------------\n");
    // Display message if no contact is found
    if (flag == 0)
    {
        printf("Contact not found.\n");
    }
}

void search_display_phone(AddressBook *addressBook, char *search)
{
    int i;
    int flag = 0;

    // Search contact using phone number
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].phone, search))
        {
            // Print heading when first match is found
            if (flag == 0)
            {
                printf("\n-------------------------------------------------------------------------------------\n");
                printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
                 printf("-------------------------------------------------------------------------------------\n");
                flag = 1;
            }

            // Display matching contact
            printf("  %d\t%s\t\t%s\t%s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
        }
    }
 printf("-------------------------------------------------------------------------------------\n");
    // Display message if no contact is found
    if (flag == 0)
    {
        printf("Contact not found.\n");
    }
}

void search_display_email(AddressBook *addressBook, char *search)
{
    int i;
    int flag = 0;

    // Search contact using email
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].email, search))
        {
            // Print heading when first match is found
            if (flag == 0)
            {
                printf("\n-------------------------------------------------------------------------------------\n");
                printf("Sl.no\tName\t\tPhone Number\tEmail ID\n");
                 printf("-------------------------------------------------------------------------------------\n");
                flag = 1;
            }

            // Display matching contact
            printf("  %d\t%s\t\t%s\t%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    printf("-------------------------------------------------------------------------------------\n");

    // Display message if no contact is found
    if (flag == 0)
    {
        printf("Contact not found.\n");
    }
}


//-----------------------------------------------------------------search contacts---------------------------------------------------------------------------------//


void searchContact(AddressBook *addressBook)
{
    int choice;
    char search[30];

    while (1)
    {
        printf("\nSearch contact by:\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting...\n");
            return;
        }

        printf("Enter what you wants to search : ");
        scanf("%s", search);

        switch (choice)
        {
            case 1:
                search_display_name(addressBook, search);
                break;

            case 2:
                search_display_phone(addressBook, search);
                break;

            case 3:
                search_display_email(addressBook, search);
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
}

void read_index(int *index, AddressBook *addressBook)
{
    // Read the index
    scanf("%d", index);

    // Check whether index is valid
    while (*index <= 0 || *index > addressBook->contactCount)
    {
        printf("Invalid index. Enter again: ");
        scanf("%d", index);
    }
}


//-----------------------------------------------------------------edit contacts---------------------------------------------------------------------------------//


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice, index;
    char search[30];

    while (1)
    {
        printf("\nEdit contact by:\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting...\n");
            return;
        }

        printf("Enter search value: ");
        scanf("%s", search);

        switch (choice)
        {
            case 1:
                // Search contact by name
                search_display_name(addressBook, search);

                printf("Enter contact index to edit: ");
                read_index(&index, addressBook);

                printf("Enter new name: ");
                scanf("%s", addressBook->contacts[index - 1].name);

                // Validate new name
                while (name_validation(addressBook->contacts[index - 1].name,
                                        addressBook, index - 1) == 0)
                {
                    scanf("%s", addressBook->contacts[index - 1].name);
                }

                printf("Contact edited successfully.\n");
                break;

            case 2:
                // Search contact by phone
                search_display_phone(addressBook, search);

                printf("Enter contact index to edit: ");
                read_index(&index, addressBook);

                printf("Enter new phone number: ");
                scanf("%s", addressBook->contacts[index - 1].phone);

                // Validate new phone number
                while (phone_validation(addressBook->contacts[index - 1].phone,
                                         addressBook, index - 1) == 0)
                {
                    scanf("%s", addressBook->contacts[index - 1].phone);
                }

                printf("Contact edited successfully.\n");
                break;

            case 3:
                // Search contact by email
                search_display_email(addressBook, search);

                printf("Enter contact index to edit: ");
                read_index(&index, addressBook);

                printf("Enter new email: ");
                scanf("%s", addressBook->contacts[index - 1].email);

                // Validate new email
                while (email_validation(addressBook->contacts[index - 1].email,
                                         addressBook, index - 1) == 0)
                {
                    scanf("%s", addressBook->contacts[index - 1].email);
                }

                printf("Contact edited successfully.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
}

void delete_contact(AddressBook *addressBook, int index)
{
	/* Define the logic for deletecontact */
    int i;

    // Shift contacts to the left
    i = index;

    while (i < addressBook->contactCount - 1)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
        i++;
    }

    // Decrease contact count
    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}


//-----------------------------------------------------------------delete contacts---------------------------------------------------------------------------------//


void deleteContact(AddressBook *addressBook)
{
    int choice;
    int index;
    char search[30];

    while (1)
    {
        printf("\nDelete contact by:\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email ID\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                // Search by name
                printf("Enter search value: ");
                scanf("%s", search);

                search_display_name(addressBook, search);

                printf("Enter contact index to delete: ");
                read_index(&index, addressBook);

                delete_contact(addressBook, index - 1);
                break;

            case 2:
                // Search by phone number
                printf("Enter search value: ");
                scanf("%s", search);

                search_display_phone(addressBook, search);

                printf("Enter contact index to delete: ");
                read_index(&index, addressBook);

                delete_contact(addressBook, index - 1);
                break;

            case 3:
                // Search by email
                printf("Enter search value: ");
                scanf("%s", search);

                search_display_email(addressBook, search);

                printf("Enter contact index to delete: ");
                read_index(&index, addressBook);

                delete_contact(addressBook, index - 1);
                break;

            case 4:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}
