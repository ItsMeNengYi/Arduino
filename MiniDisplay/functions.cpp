#include "functions.h"
#include "alphabet.h"
 

int* GetArrayOfIndex(String words){
  int ascii_no = 0;
  int words_no = words.length();
  int* array = new int[words_no];
  
  for(int index=0; index<words_no; index++){
    ascii_no = (int)words[index]-65;
    array[index] = ascii_no;
  }
  return array;
}

bool** GetFrame(bool** array, int frame){
  bool** ans = CreateArray(5, 5);
  for (int rows=0;rows<5;rows++){
    for (int cols=frame-1;cols<5+frame-1;cols++){
      ans[rows][cols-frame+1] = array[rows][cols];
    }
  }
  return ans;
}

bool** stringToArray(String words){
  int ascii_no = 0;
  int words_no = words.length();
  bool*** array = new bool**[words_no];
  
  for(int index=0; index<words_no; index++){
    ascii_no = (int)words[index]-65;
    array[index] =  CreateArray(5, 5);

    bool** alphabet = CreateArray(5, 5);
    for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++) {
        alphabet[i][j]= Alphabet[ascii_no][i][j];
      }
    }

    copyArray(array[index], alphabet);
  }


  bool** arr = addWords(array,words_no);
  return arr;
}

bool** addWords(bool*** matrix_array,int word_count) {
 int row,column,spacing = 1;
 bool** final = CreateArray(5, (5+spacing)*word_count);
  for (int letter=0; letter<word_count; letter++){
    row = 5;
    column = 5;
    for (int i=0;i<row;i++){
      for (int j=0;j<column;j++){
        final[i][j+ letter*(5 + spacing)] = matrix_array[letter][i][j];
      }
    }
  }
  return final;
}

// 1D Array
bool* stringToLineArray(String words){
  int ascii_no = 0;
  int words_no = words.length();
  bool*** array = new bool**[words_no];
  
  for(int index=0; index<words_no; index++){
    ascii_no = (int)words[index]-65;
    array[index] =  CreateArray(5, 5);

    bool** alphabet = CreateArray(5, 5);
    for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++) {
        alphabet[i][j]= Alphabet[ascii_no][i][j];
      }
    }

    copyArray(array[index], alphabet);
  }

  int wordRow = 5,wordColumn = 5,spacing = 1;
  bool** textArray = CreateArray(5, (5+spacing)*words_no);
  for (int letter=0; letter<words_no; letter++){
    wordRow = 5;
    wordColumn = 5;
    for (int i=0;i<wordRow;i++){
      for (int j=0;j<wordColumn;j++){
        textArray[i][j+ letter*(5 + spacing)] = array[letter][i][j];
      }
    }
  }
  bool lineArray[words_no*(wordColumn+spacing)*wordRow];
  for (int index;index<words_no*(wordColumn+spacing)*wordRow;index++){
    lineArray[index] = 0;
  }
  bool* finalArr = lineArray;
  for (int i=0;i<wordRow;i++){
    for (int j=0;j<words_no*(wordColumn+spacing);j++){
      lineArray[i*words_no*(wordColumn+spacing)+j] = textArray[i][j];
    }
  }
  
  return finalArr;
}

void DisplayBitWise(bool matrix[],int frame,int word_count){
  for(int x=0; x<5; x++){
    AllLowBitWise();
    for(int y=0; y<5; y++){
      if (matrix[x*word_count*(5+1)+y+frame]){
        HighBitWise(x+1);
        LowBitWise(y+6);
      }
      else{
        HighBitWise(y+6);
      }
    }
    delay(3);
  }
}

void Display(bool** matrix,int frame) {
  for(int x=0; x<5; x++){
    AllLow();
    for(int y=0; y<5; y++){
      if (matrix[x][y+frame]){
        High(x+1);
        Low(y+6);
      }
      else{
        High(y+6);
      }
    }
    delay(3);
  }
}

void copyArray(bool **array1, bool** array2) {
  for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++) {
        array1[i][j] = array2[i][j];
      }
  }
}

bool** CreateArray(int rows, int cols){
  bool** array = new bool*[rows];
  for (int i=0; i<rows; i++) {
    array[i] = new bool[cols];
    for (int j=0; j<cols; j++) {
      array[i][j] = 0;      
    }
  }
  return array;
}

void DisplayBitWise(bool matrix[5][5]) {
  for(int x=0; x<5; x++){
    AllLowBitWise();
    for(int y=0; y<5; y++){
      if (matrix[x][y]){
        HighBitWise(x+1);
        LowBitWise(y+6);
      }
      else{
        HighBitWise(y+6);
      }
    }
    delay(1);
  }
}

void DisplayBitWise(bool** matrix,int frame) {
  for(int x=0; x<5; x++){
    AllLowBitWise();
    for(int y=0; y<5; y++){
      if (matrix[x][y+frame]){
        HighBitWise(x+1);
        LowBitWise(y+6);
      }
      else{
        HighBitWise(y+6);
      }
    }
    delay(3);
  }
}

void AllLow(){
  for(int x=1;x<=10;x++){
    Low(x);
  }
}

void High(int num) {
  digitalWrite(num,HIGH);
}

void Low(int num) {
  digitalWrite(num,LOW);
}

void AllLowBitWise(){
  for(int x=1;x<=10;x++){
    LowBitWise(x);
  }
}

void HighBitWise(int num) {
  if (num<=7){
    // pin 1~7 to High
    PORTD |= (1 << num);
  }else{
    // pin 8~10 to High
    PORTB |= (1 << num-8);
  }

}

void LowBitWise(int num) {
  if (num<=7){
    // pin 1~7 to low
    PORTD &=~(1 << num);
  }else{
    // pin 8~10 to low
    PORTB &=~(1 << num-8);
  }
}

void display_setup(){
  for(int x=1;x<=10;x++){
    pinMode(x, OUTPUT);
  }
}

bool** display_set_word(String text,unsigned long& startTime,int& length){
  startTime = millis();
  length = text.length();
  bool** wordArray = stringToArray(text);
  return wordArray;
}

void Update(bool** wordArray,int length,int& frame_no,unsigned long& startTime,unsigned int interval){
  unsigned long currentTime = millis(); 
  unsigned long elapsedTime = currentTime - startTime; 
  if (elapsedTime>= interval) {
    startTime = millis();
    frame_no++;
  }
  if(frame_no>(length * 6)-5+1){
    frame_no = 1;
  }
  Display(wordArray,frame_no-1);
}

