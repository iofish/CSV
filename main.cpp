#include <stdio.h>
#include "csv.h"
#include <fstream>

using namespace std;

int main() {
    int i =  0;

    Csv csvFile;
    CsvParser *csvparser = csvFile.CsvParser_new("test.csv", ",", 1);   // ��CSV�ļ���','Ϊ�ָ���, ��һ��Ϊͷ��
    CsvRow *row;
    ofstream outfile;
    //string value;
    outfile.open("./outfile.csv");                                      // д��CSV�ļ�

    const CsvRow *header = csvFile.CsvParser_getHeader(csvparser);      // ���ļ�ͷ

    if (header == NULL) {
        printf("%s\n", csvFile.CsvParser_getErrorMessage(csvparser));
        return 1;
    }
    const char **headerFields = csvFile.CsvParser_getFields(header);    // ���ļ�ͷ������
    for (i = 0 ; i < csvFile.CsvParser_getNumFields(header) ; i++) {
        printf("TITLE: %s\n", headerFields[i]);                         // д���ļ�ͷ����
        outfile <<headerFields[i];
        if(i == csvFile.CsvParser_getNumFields(header) -1){
            outfile << ' ';
        }else{
            outfile << ',';
        }
    }
    outfile << '\n';
    while ((row = csvFile.CsvParser_getRow(csvparser)) ) {              // ��ÿһ������
    	printf("==NEW LINE ==\n");
        const char **rowFields = csvFile.CsvParser_getFields(row);
        for (i = 0 ; i < csvFile.CsvParser_getNumFields(row) ; i++) {
            printf("FIELD %d: %s\n", i, rowFields[i]);
            outfile << rowFields[i];
            if(i == csvFile.CsvParser_getNumFields(row) -1){
                outfile << ' ';
            }else{
                outfile << ',';
            }
        }
        outfile << '\n';
		printf("\n");
        csvFile.CsvParser_destroy_row(row);
    }
    csvFile.CsvParser_destroy(csvparser);

    outfile.close();

    return 0;
}
