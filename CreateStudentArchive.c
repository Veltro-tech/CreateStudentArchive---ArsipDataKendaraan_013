#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    float grade;
}Student;

typedef Student StudentTab[100 + 1];
typedef char String[255];
void copyStudentToArray(String filename, StudentTab Student, int *n);
void printStudent(StudentTab Student, int n);
void ratarata(StudentTab student, int n);

int main(void) {
    //DECLARATION
    Student student;
    FILE *studentFile;
    String filename;
    StudentTab StudentTab;
    int n = 0;

    //ALGORITHM
    strcpy(filename, "students.dat");
    studentFile = fopen("students.dat", "ab");

    if (studentFile == NULL) {
        printf("Error: Tidak bisa Membuat File \n");
        return 1;
    }

    printf("Input Student ID (9999) untuk stop): "); scanf("%d", &student.id);
    while (student.id != 9999) {
        printf("\nName: "); scanf("%s", student.name);
        printf("\nGrade: "); scanf("%f", &student.grade);

        fwrite(&student, sizeof(student), 1, studentFile);
        printf("\n Input Student ID (9999 untuk stop): "); scanf("%d", &student.id);
    }
    fclose(studentFile);
    printf(" \n === Data Berhasil disimpan === \n");

    // Menampilkan Semua Data dalam File
    copyStudentToArray(filename, StudentTab, &n);
    printf("\n --- Lihat Data Mahasiswa --- \n");
    printStudent(StudentTab,n );

    printf("\n --- Menghitung Rata - rata Grade mahasiswa --- \n");
    ratarata(StudentTab, n);
    return 0;
}

void printStudent(StudentTab Student, int n) {
    int i;

    if ( n == 0 ) {
        printf("Tidak ada data mahasiswa \n");
        return;
    }

    for ( i = 1 ; i <= n; i ++) {
        printf("ID  : %d \n", Student[i].id);
        printf("Name : %s\n", Student[i].name);
        printf("Grade : %.2f \n", Student[i].grade); printf("\n");
    }
}

void copyStudentToArray(String filename, StudentTab student, int *n) {
    FILE *studentFile;
    Student studentRec;
    int i = 0;

    studentFile = fopen(filename, "rb");

    if (studentFile == NULL) {
        printf("Error: File student.dat tidak ditemukan\n");
        *n = 0;
        return;
    }

    while ( fread(&studentRec, sizeof(studentRec), 1, studentFile) == 1)  {
        i++;
        student[i] = studentRec;
    }

    fclose (studentFile);
    *n = i;

}

void ratarata(StudentTab student, int n) {
    FILE *studentFile;
    Student studentRec;
    float totalgrade = 0;
    int i;
    float studentss;

    if ( n == 0 ) {
        printf("Tidak ada data mahasiswa \n");
    }

    for (i = 1 ; i <= n; i ++) {
        totalgrade += student[i].grade;
    }

    float average = totalgrade / n;
    printf("Rata-rata grade 3 Mahasiswa adalah: %.2f", average);
}
