#include <Arduino.h>


int* GetArrayOfIndex(String words);//Method2
bool** GetFrame(bool** array, int frame);
bool** stringToArray(String words);
bool** addWords(bool*** matrix_array,int word_count);
void copyArray(bool **array1, bool** array2);
bool** CreateArray(int rows, int cols);

bool* stringToLineArray(String words);
void DisplayBitWise(bool* matrix,int frame,int word_count);

void Display(bool** matrix,int frame);
void DisplayBitWise(bool** matrix,int frame);
void DisplayBitWise(bool matrix[5][5]);
void AllLow();
void High(int num);
void Low(int num);
void AllLowBitWise();
void HighBitWise(int num);
void LowBitWise(int num);

//bluetooth
void display_setup();
bool** display_set_word(String text,unsigned long& startTime,int& length);
void Update(bool** wordArray,int length,int& frame_no,unsigned long& startTime,unsigned int interval);