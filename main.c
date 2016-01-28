//
//  main.c
//
//  Anthony Kiniyalocts
//
//  CIT-362
//
//  Program Assignment #1:
//
//  This assignment will test you over file I/O character-by-character and the proper use of logic. The user is prompted to input a file name
//  that is comprised of a bizzare code. The program will remove any characters that do not follow the pattern:
//
//  Letters from the file consist of upper and lower case letters, the upper-to-lower-to-upper sequence restarts with each new sentence ,
//  (that is, after any period). Finally, the only upper case letters that should be output in upper case are the first letter of any sentence.
//  All other letters, no matter if they appear in upper or lower case in the input, should be lower cased.
//
//  These letters are appending to a file called output.txt and saved to the file system.
//
//  The program also will output stats, showing the user the name of the input file, name of the output file, number of characters input from the
//  input file, number of characters output, and the percent reduction in the output.
//
//  Due: 1/28/16
//

#include <stdio.h>
#include <ctype.h>

const int true = 1; // convience constant for true

const int false = 0;// convience constant for false

// prototype for printStats method
void printStats(char filename[30], float inputChars, float outputChars);

int main() {
    
    float chars=0, discarded = 0;// counter variables
    
    int needUpper=1, needLower=1, shouldPrintLower=0; // flags for pattern
    
    
    FILE *fp;// file pointer
    FILE *outFile;//output file pointer
    
    char filename[30], current;		// filename and the current character input from the file
    
    printf("Enter the filename to be scanned:  ");	// ask user for filename
    scanf("%s", filename);
    
    fp = fopen(filename, "r");// open the file as read-only
    
    outFile = fopen("output.txt", "a");// open the output file as append
    
    // null check for input file and output file
    if(fp && outFile){
        
        fprintf(outFile, "%s  output: \n\n", filename);
        
        while((current = getc(fp)) != EOF)	// get the next char and as long as it is not the EOF, continue
        {
            
            chars++;
            
            // if we come across a space, print it
            if(isspace(current)){
                fprintf(outFile, "%c", current);
            }
            
            // reset flags once we hit the end of a sentence
            else if(current == '.'){
                //append to our outfile
                fprintf(outFile, "%c", current);

                needUpper = true; // we need an upper case letter next
                needLower = false; // we do not need a lower case letter next
                shouldPrintLower = false; // do not output uppercase as lower case
            }

            
            // we need an upper case letter
            else if(needUpper){
                
                if(isupper(current)){
                    
                    // if its not the beginning of a sentance, we should output the uppercase letter as lowercase
                    if(shouldPrintLower){
                        //append to our outfile in lower case
                        fprintf(outFile, "%c", tolower(current));
                    }
                    
                    // it's the beginning of the sentance, output the upper case letter as is
                    else{
                        // append to our outfile
                        fprintf(outFile, "%c", current);
                    }
                    
                    // we no longer 'need an uppercase letter' set it to false
                    needUpper = false;
                    // we now need a lowercase letter
                    needLower = true;
                }
                
                // char was not lower case when we expected it to be, therefore we must discard the char
                else{
                    discarded++;
                }
            }
            
            //we need a lower case letter
            else if(needLower){
                if(islower(current)){
                    
                    // append to our out file
                    fprintf(outFile, "%c", current);

                    
                    // now we need an upper case letter, set it to true
                    needUpper = true;
                    // discard any lowercase letters
                    needLower = false;
                    // print those upper case letters in lower case since we are not at the beginning of a sentance
                    shouldPrintLower = true;
                }
                // char was not lower case when we expected it to be, therefore we must discard the char
                else{
                    discarded++;
                }
            }
            
            // pick up any remaining chars we don't need
            else{
                discarded++;
            }
            
        }
        
        // call our print stats fuction
        printStats(filename, chars, chars - discarded);
        
        //close the input file
        fclose(fp);
        
        fprintf(outFile, "%s", "\n");
        //close the output file
        fclose(outFile);
        
    }
    
    return (0);
}

// This function takes a filename as a char array, a float of input and output characters.
// This function will print to the console the:
// Input filename
// Output filename
// Number of input characters
// Number of output characters
// Percent reduction in output (num of output chars / num of input chars)
void printStats(char filename[30], float inputChars, float outputChars){
    printf("Input file: %s \n", filename);
    printf("Output file: %s \n", "output.txt");
    printf("Number of input chars: %.f \n", inputChars);
    printf("Number of output chars: %.f \n", outputChars);
    printf("Percent reduction in output: %.2f %% \n", outputChars/inputChars * 100);
}

