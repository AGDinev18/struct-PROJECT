#pragma once

bool checkIncorrectDate(DATE start, DATE end);

void calcSpecTime(int& start, int& end, int& dur);

bool tryReadInt(int& result, int min, int max);

bool isLeap(int year);

bool isValidDate(int d, int m, int y);

void enterDate(int& year, int& month, int& day);

int enterInt(int min, int max, string text);

void enterTime(int& hour, int& min);

void printSeperator();
