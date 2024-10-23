#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    int result = 0;
    int count = 0;
    unsigned max = HASH_LEN;
    char *in = (char*) malloc(max * sizeof(char));
    // Hash the plaintext
    char *idk = md5(plaintext, strlen(plaintext));

    // Open the hash file
    FILE *hash = fopen(hashFilename, "r");

    // Loop through the hash file, one line at a time.
    while(fgets(in, max, hash) != NULL) //check this
    {
        char *nl = strchr(in, '\n'); //NULL termination use in all string code now plz
        if(nl != NULL)
            *nl = '\0';
        
        // Attempt to match the hash from the file to the
        // hash of the plaintext.
        result = strcmp(idk, in); // need to get string from the hash file
        
        if(result == 0)
        {
            count++;
            free(in);
            return idk;
        }
        // If there is a match, you'll return the hash.
        // If not, return NULL.
    }

    // Before returning, do any needed cleanup:
    //   Close files?
    fclose(hash);
    //   Free memory?

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    // char *found = tryWord("hello", "hashes00.txt");
    // printf("%s\n%s\n", found, "found hello!!");


    // Open the dictionary file for reading.
    FILE *dict = fopen(argv[2], "r");

    
    int count = 0;
    int size = PASS_LEN;
    char *line = (char*) malloc(size * sizeof(char));
    char line2[HASH_LEN];

    if (line == NULL) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }


    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    while(fgets(line, PASS_LEN, dict) != NULL)
    {
        char *nl = strchr(line, '\n');
        if (nl != NULL)
            *nl = '\0';


        char *found = tryWord(line, argv[1]);
        if(found != NULL)
        {
            // If we got a match, display the hash and the word. For example:
            // 5d41402abc4b2a76b9719d911017c592 hello
            printf("%s : %s\n", line, found);
            count++;
        }
    }
        
    // Close the dictionary file.
    fclose(dict);
    // Display the number of hashes that were cracked.
    printf("Total hashes cracked %d\n", count);
    
    // Free up any malloc'd memory?
    free(line);
}

