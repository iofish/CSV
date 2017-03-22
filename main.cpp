#include <stdio.h>
#include "csv.h"
#include <fstream>

using namespace std;

int main() {
    int i =  0;

    Csv csvFile;
    CsvParser *csvparser = csvFile.CsvParser_new("test.csv", ",", 1);   // 打开CSV文件，','为分隔符, 第一行为头部
    CsvRow *row;
    ofstream outfile;
    //string value;
    outfile.open("./outfile.csv");                                      // 写入CSV文件

    const CsvRow *header = csvFile.CsvParser_getHeader(csvparser);      // 读文件头

    if (header == NULL) {
        printf("%s\n", csvFile.CsvParser_getErrorMessage(csvparser));
        return 1;
    }
    const char **headerFields = csvFile.CsvParser_getFields(header);    // 读文件头中数据
    for (i = 0 ; i < csvFile.CsvParser_getNumFields(header) ; i++) {
        printf("TITLE: %s\n", headerFields[i]);                         // 写新文件头数据
        outfile <<headerFields[i];
        if(i == csvFile.CsvParser_getNumFields(header) -1){
            outfile << ' ';
        }else{
            outfile << ',';
        }
    }
    outfile << '\n';
    while ((row = csvFile.CsvParser_getRow(csvparser)) ) {              // 读每一行数据
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
