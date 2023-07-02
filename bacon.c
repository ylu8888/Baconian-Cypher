#include "bacon.h"

int encrypt(const char *plaintext, char *ciphertext);
int decrypt(const char *ciphertext, char *plaintext);

int encrypt(const char *plaintext, char *ciphertext) {
//bacon code converter
   char letter[100] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
   ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '?'};
    
   char *binary[] = {"000000" , "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001", "001010", "001011", "001100"
    , "001101", "001110", "001111", "010000", "010001", "010010", "010011", "010100", "010101", "010110", "010111", "011000", "011001", "011010", "011011" , "011100", 
    "011101", "011110", "011111", "100000", "100001", "100010", "100011", "100100", "100101", "100110", "100111", "101000", "101001", "101010", "101011", 
    "101100", "101101", "101110", "101111", "110000", "110001", "110010", "110011", "110100" };
   
    int letterCount = 0;
    int encodedChar = 0;
    int ciphSize = (int) strlen(ciphertext);
    int plainSize = (int) strlen(plaintext);
  
     for(int i = 0; i < ciphSize; i++){
        if(isalpha(ciphertext[i])){ 
             letterCount++; // counts how many letters are in ciphertext
        }
        
    }
    
    encodedChar = ((letterCount - 6) / 6) ;
    // case: if the encodedChar is larger than the plaintext size
    if(encodedChar > plainSize){
        encodedChar = plainSize;
    }
    
    //adds the binary numbers of plaintext code into one string

    char binaryComp[200] = "";
   
   int i = 0;
   int j = 0;
   int letterSize = (int)(strlen(letter));

    for(i = 0; i < encodedChar; i++){ //stops traversing through plaintext after reaching # of letters encodable
        for(j = 0; j < letter[i] != '\0'; j++){
            if((toupper(plaintext[i])) == letter[j]){
                strcat(binaryComp, binary[j]);
            }
        }
    }

    strcat(binaryComp, "111111");  //EOM
    int binStrLen = (int) strlen(binaryComp);
    
    //changes cipher text to upper/lower case depending on binary string
    int temp = 0;
    int n = 200;
    
    for(int i = 0; i <= letterCount; i++){
        if(!(isalpha(ciphertext[i]))){
            //shifts binary string array by 1 if it isn't a letter
            temp = binaryComp[n - 1];
            for(int k = n - 1; k > 0; k--){
                binaryComp[k] = binaryComp[k - 1];
            }
            binaryComp[0] = temp;
        }
        else if(isalpha(ciphertext[i])){
            for(int j = 0; j < ciphSize; j++){
                if(binaryComp[i] == '1'){
                ciphertext[i] = toupper(ciphertext[i]);
                }
            
              else if(binaryComp[i] == '0'){
                ciphertext[i] = tolower(ciphertext[i]);
                }
            }
            
        }

    }
    
    //returns how many encoded char there are from ciphertext
   if(ciphSize == 0){
        return -1;
    }
    
    else if(ciphSize <= 6){
        return 0;
    }
    
    else {
        return encodedChar;
    }
    
}


int decrypt(const char *ciphertext, char *plaintext) {
     //bacon code converter
    
    char letter[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '?'};
    
    char *binary[] = {"000000" , "000001", "000010", "000011", "000100", "000101", "000110", "000111", "001000", "001001", "001010", "001011", "001100"
    , "001101", "001110", "001111", "010000", "010001", "010010", "010011", "010100", "010101", "010110", "010111", "011000", "011001", "011010", "011011" , "011100", 
    "011101", "011110", "011111", "100000", "100001", "100010", "100011", "100100", "100101", "100110", "100111", "101000", "101001", "101010", "101011", 
    "101100", "101101", "101110", "101111", "110000", "110001", "110010", "110011", "110100", "111111" };
    
    int letterCount = 0;
    int decodedChar = 0;
    int ciphSize = (int) strlen(ciphertext);
    int plainSize = (int) strlen(plaintext);
  
    for(int i = 0; i < ciphSize; i++){
        if(isalpha(ciphertext[i])){ 
             letterCount++; // counts how many letters are in ciphertext
        }
    }
     
    decodedChar = (letterCount / 6);
    
    char binaryComp[200] = "";
   
    // creates the binary string
    for(int i = 0; i < ciphSize; i++){
        if(isalpha(ciphertext[i])){
            if(isupper(ciphertext[i])){
            strcat(binaryComp, "1");
            }
            else if(islower(ciphertext[i])){
            strcat(binaryComp, "0");
            }
        }
        
    }
    printf("%s\n" , binaryComp);
    
    //checking if an EOM exists
    char sixBitGrp[10] = "";
    int count = 0;
    int eomCheck = 0;
    
    for(int i = 0; i < 6; i++){
        sixBitGrp[i] = binaryComp[i];
    }
    
    for(int i = 0; i < decodedChar; i++){
        for(int j = 0; j < 54; j++){
           if(strcmp(sixBitGrp, binary[53]) == 0){
                eomCheck++;
           }
            
        }

        count++;
        for(int k = 0; k < 6; k++){
        int iterate = count * 6; //jumps 6 positions in binary string
        sixBitGrp[k] = binaryComp[k + iterate];
        }
    }
    
    //if bacon codes are invalid
    count = 0;
    int invalid = 0;
    
    for(int i = 0; i < 6; i++){
        sixBitGrp[i] = binaryComp[i];
    }
    
    for(int i = 0; i < decodedChar; i++){
        for(int j = 0; j < 54; j++){
           if(strcmp(sixBitGrp, binary[j]) == 0){
                invalid++;
           }
            
        }

        count++;
        for(int k = 0; k < 6; k++){
        int iterate = count * 6; //jumps 6 positions in binary string
        sixBitGrp[k] = binaryComp[k + iterate];
        }
    }
    
    //error codes
    if(plainSize == 0){
        return -1;
    }
    else if(eomCheck == 0){
        return -2;
    }
    else if(invalid != count){
        return -3;
    }
    else{
    
    
        
    
    //splits the binary string into groups of 6 bits
    count = 0;
    int plainCount = 0;
    
    for(int i = 0; i < 6; i++){
        sixBitGrp[i] = binaryComp[i];
    }
    
    for(int i = 0; i < decodedChar; i++){
        for(int j = 0; j < 54; j++){
            if(strcmp(sixBitGrp, binary[j]) == 0){
                plaintext[i] = letter[j];
                plainCount++;
            }
            
            if(plainCount == plainSize){
                break;
            }
            
        }
        if(strcmp(sixBitGrp, binary[53]) == 0){
            plaintext[i] = '\0';
            break;
    
        }

        count++;
        for(int k = 0; k < 6; k++){
        int iterate = count * 6; //jumps 6 positions in binary string
        sixBitGrp[k] = binaryComp[k + iterate];
        }
        
    }

    decodedChar = count;
    return decodedChar;
    }
    
}



