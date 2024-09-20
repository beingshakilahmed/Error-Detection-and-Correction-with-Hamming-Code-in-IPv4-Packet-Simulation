#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum length for input and output data
#define MAX_LENGTH 100

// Function to calculate the number of redundant bits required for Hamming code
int calculateRedundantBits(int dataLength)
{
    int i = 0;
    while ((1 << i) < (dataLength + i + 1))
    {
        i++;
    }
    return i;
}

// Function to generate Hamming code
void generateHammingCode(const char* data, char* hammingCode)
{
    int dataLength = strlen(data);
    int redundantBits = calculateRedundantBits(dataLength);

    // Initialize Hamming code with 0
    memset(hammingCode, '0', dataLength + redundantBits + 1);

    // Copy data bits to Hamming code
    int j = 0;
    for (int i = 1; i <= dataLength + redundantBits; i++)
    {
        if (!((i & (i - 1)) == 0))
        {
            hammingCode[i] = data[j++];
        }
    }

    // Calculate parity bits
    for (int i = 0; i < redundantBits; i++)
    {
        int parityPosition = (1 << i);
        int parity = 0;

        for (int j = parityPosition; j <= dataLength + redundantBits; j += (parityPosition << 1))
        {
            for (int k = 0; k < parityPosition && j + k <= dataLength + redundantBits; k++)
            {
                parity ^= (hammingCode[j + k] - '0');
            }
        }

        hammingCode[parityPosition] = (parity + '0');
    }
}

// Function to introduce a simulated error in Hamming code
void simulateError(char* hammingCode)
{
    int position = rand() % strlen(hammingCode);
    hammingCode[position] = (hammingCode[position] == '0') ? '1' : '0';
}

// Function to correct errors in Hamming code
void correctErrors(char* hammingCode)
{
    int redundantBits = calculateRedundantBits(strlen(hammingCode) - 1);

    for (int i = 0; i < redundantBits; i++)
    {
        int parityPosition = (1 << i);
        int parity = 0;

        for (int j = parityPosition; j <= strlen(hammingCode); j += (parityPosition << 1))
        {
            for (int k = 0; k < parityPosition && j + k <= strlen(hammingCode); k++)
            {
                parity ^= (hammingCode[j + k] - '0');
            }
        }

        if (parity != 0)
        {
            // Flip the incorrect bit
            hammingCode[parityPosition] = (hammingCode[parityPosition] == '0') ? '1' : '0';
        }
    }
}

// Function to perform bit stuffing
void bitStuffing(const char* input, char* stuffedOutput)
{
    int count = 0;
    strcpy(stuffedOutput, ""); // Initialize output string

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '1')
        {
            count++;
        }
        else
        {
            count = 0;
        }

        // Append current bit to output
        strncat(stuffedOutput, &input[i], 1);

        // Perform bit stuffing if count reaches 5
        if (count == 5)
        {
            strcat(stuffedOutput, "0");
            count = 0; // Reset count after stuffing
        }
    }
}

// Function to perform bit destuffing
void bitDestuffing(const char* stuffedInput, char* destuffedOutput)
{
    int count = 0;
    strcpy(destuffedOutput, ""); // Initialize output string

    for (int i = 0; i < strlen(stuffedInput); i++)
    {
        // Append current bit to output
        strncat(destuffedOutput, &stuffedInput[i], 1);

        if (stuffedInput[i] == '1')
        {
            count++;
        }
        else
        {
            count = 0;
        }

        // Skip the stuffed bit (0) after five consecutive 1's
        if (count == 5 && i < strlen(stuffedInput) - 1)
        {
            i++;
        }
    }
}

// Function to perform character stuffing
void charStuffing(const char* input, char* stuffedOutput)
{
    strcpy(stuffedOutput, ""); // Initialize output string

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == 'D')
        {
            strcat(stuffedOutput, "DD");
        }
        else
        {
            strncat(stuffedOutput, &input[i], 1);
        }
    }
}

// Function to perform character destuffing
void charDestuffing(const char* stuffedInput, char* destuffedOutput)
{
    strcpy(destuffedOutput, ""); // Initialize output string

    for (int i = 0; i < strlen(stuffedInput); i++)
    {
        if (stuffedInput[i] == 'D' && stuffedInput[i + 1] == 'D')
        {
            strncat(destuffedOutput, "D", 1);
            i++;
        }
        else
        {
            strncat(destuffedOutput, &stuffedInput[i], 1);
        }
    }
}

// Function to convert decimal to binary
void decimalToBinary(int decimal, char binary[])
{
    for (int i = 31; i >= 0; i--)
    {
        binary[31 - i] = (decimal & (1 << i)) ? '1' : '0';
    }
    binary[32] = '\0'; // Null-terminate the string
}

// Function to convert binary to decimal
int binaryToDecimal(const char binary[])
{
    int decimal = 0;
    for (int i = 0; i < 32; i++)
    {
        decimal = (decimal << 1) + (binary[i] - '0');
    }
    return decimal;
}

// Function to perform simple parity check
int parityCheck(const char* input)
{
    int count = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '1')
        {
            count++;
        }
    }
    return (count % 2 == 0) ? 0 : 1; // 0 for even parity, 1 for odd parity
}

int main()
{
    char choice, subChoice;
    char input[MAX_LENGTH], output[MAX_LENGTH * 2];
    char hammingCode[MAX_LENGTH * 2];
    char binaryIPv4[33];
    int decimalIPv4;

    do
    {
        printf("\n****************************************************\n");
        printf("Choose an operation:\n");
        printf("1. Bit Operations\n");
        printf("2. Character Operations\n");
        printf("3. Hamming Code (Error Detection & Correction)\n");
        printf("4. IPv4 Conversion (Decimal to Binary and vice versa)\n");
        printf("5. Parity Checker\n");
        printf("0. Exit\n");
        printf("****************************************************\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            printf("Choose bit operation:\n");
            printf("a. Bit Stuffing\n");
            printf("b. Bit Destuffing\n");
            printf("Enter your choice: ");
            scanf(" %c", &subChoice);

            switch (subChoice)
            {
            case 'a':
                printf("Enter binary data for bit stuffing: ");
                scanf("%s", input);
                bitStuffing(input, output);
                printf("Bit-stuffed data: %s\n", output);
                break;

            case 'b':
                printf("Enter binary data for bit destuffing: ");
                scanf("%s", input);
                bitDestuffing(input, output);
                printf("Bit-destuffed data: %s\n", output);
                break;

            default:
                printf("Invalid choice for bit operation.\n");
                break;
            }
            break;

        case '2':
            printf("Choose character operation:\n");
            printf("a. Character Stuffing\n");
            printf("b. Character Destuffing\n");
            printf("Enter your choice: ");
            scanf(" %c", &subChoice);

            switch (subChoice)
            {
            case 'a':
                printf("Enter data for character stuffing: ");
                scanf("%s", input);
                charStuffing(input, output);
                printf("Character-stuffed data: %s\n", output);
                break;

            case 'b':
                printf("Enter data for character destuffing: ");
                scanf("%s", input);
                charDestuffing(input, output);
                printf("Character-destuffed data: %s\n", output);
                break;

            default:
                printf("Invalid choice for character operation.\n");
                break;
            }
            break;

        case '3':
            printf("Enter binary data for Hamming Code: ");
            scanf("%s", input);
            generateHammingCode(input, hammingCode);
            printf("Hamming Code: %s\n", hammingCode);
            simulateError(hammingCode);
            printf("Simulated error in Hamming Code: %s\n", hammingCode);
            correctErrors(hammingCode);
            printf("Corrected Hamming Code: %s\n", hammingCode);
            break;

        case '4':
            printf("Choose conversion:\n");
            printf("a. Decimal to Binary\n");
            printf("b. Binary to Decimal\n");
            printf("Enter your choice: ");
            scanf(" %c", &subChoice);

            switch (subChoice)
            {
            case 'a':
                printf("Enter IPv4 decimal address: ");
                scanf("%d", &decimalIPv4);
                decimalToBinary(decimalIPv4, binaryIPv4);
                printf("Binary representation: %s\n", binaryIPv4);
                break;

            case 'b':
                printf("Enter IPv4 binary address (32 bits): ");
                scanf("%s", binaryIPv4);
                decimalIPv4 = binaryToDecimal(binaryIPv4);
                printf("Decimal representation: %d\n", decimalIPv4);
                break;

            default:
                printf("Invalid choice for IPv4 conversion.\n");
                break;
            }
            break;

        case '5':
            printf("Enter binary data for parity check: ");
            scanf("%s", input);
            int result = parityCheck(input);
            printf("Parity check result: %s\n", (result == 0) ? "Even Parity" : "Odd Parity");
            break;

        case '0':
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
            break;
        }

        // Consume any remaining characters in the input buffer
        while ((subChoice = getchar()) != '\n' && subChoice != EOF);

    }
    while (choice != '0');

    return 0;
}
