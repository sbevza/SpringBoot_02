#include <stdio.h>
#include <dirent.h>
#include <string.h>

void main_menu(int *dig);
void read_path(char *path_str);
void read_file(char *path_str, FILE **f);

void close_file(FILE *f);
void read_str(char *str);
void write_file(const char *path_str, FILE **f, const char *str);

void read_shift(int *shift);
int main() {
  int dig = 0;
  char path_str[500] = "";
  while (dig != -1) {
    main_menu(&dig);
    FILE *f = NULL;

    if (dig == 1) {
      read_path(path_str);
      read_file(path_str, &f);
      close_file(f);
    } else if (dig == 2) {
      char str[500] = "";
      read_str(str);
      write_file(path_str, &f, str);
      close_file(f);
      read_file(path_str, &f);
      close_file(f);
    } else if (dig == 3) {
      read_path(path_str);
      int shift = 0;
      read_shift(&shift);
      
      
      DIR *dir = opendir(path_str);
      
      if(dir != NULL) {
         struct dirent* ptr_f;
         while ((ptr_f = readdir(dir)) != 0) {
            
            
            char *filename = ptr_f->d_name;
            char type_file[2];
            type_file[0] = filename[strlen(filename) - 2];
            type_file[1] = filename[strlen(filename) - 1];
            char res = 0;
            if (type_file[0] == '.' && (type_file[1] == 'c' || type_file[1] == 'h')){
                res =  type_file[1];
            }

            char* filepath = strcat(path, cur->d_name);
            if (res == 'c') {
                encrypt(filepath, shift);
            } else if (res == 'h') {
                clean_file(filepath);
            }
            free(filepath);
        } 
      } else {
          printf("n/a");
      }
      
      
      
      read_file(path_str, &f);
      close_file(f);
    } else {
      printf("n/a\n");
    }
  }
  return 0;
}

void clean_file(char* filepath) {
    FILE* f = fopen(filepath, "w");
    if(f == NULL) 
        printf("n/a");
    }
    fclose(f);
}

void encrypt(char* filepath, int shift) {
    FILE* f = fopen(filepath, "r+");
    if(f != NULL) {
         char c = fgetc(f);
         while(c != EOF) {
             fputc((c + shift) % 255, f);
             c = fgetc(f);
         }
    } else {
        printf("n/a");
    }
    fclose(f);
}

void write_file(const char *path_str, FILE **f, const char *str) {
  *f = fopen(path_str, "a");
  if (*f != NULL) {
    fprintf(*f, "%s\n", str);
  }
}

void read_str( char *str) {
  printf("Enter string:\n");
  scanf("%s", str);
}

void close_file(FILE *f) {
  if (f != NULL)
    fclose(f);
}

void read_file(char *path_str, FILE **f) {
  *f = fopen(path_str, "r");
  if (*f == NULL) {
    printf("n/a\n");
  } else {
    char c = fgetc(*f);
    if (c == EOF) {
      printf("n/a\n");
    } else {
      printf("%c", c);
    }
    while (!feof(*f)) {
      printf("%c", fgetc(*f));
    }
  }
}

void read_path(char *path_str) {
  printf("Enter path to file:\n");
  scanf("%s", path_str);
}

void main_menu(int *dig) {
  printf("MENU:\n");
  printf("1. Upload file.\n");
  printf("2. Write string to file.\n");
  printf("3. Caesar cipher.\n");
  printf("-1 Exit\n");
  scanf("%d", dig);
}

void read_shift(int *shift) {
  printf("Enter shift:\n");
  scanf("%d", shift);
}






void finder(char *dir_path, int shift) {
    char *ptr1, *ptr2, *cs_in, *clean_in;
    char dir_path_cp[256], dir_path_cp1[256];
    DIR *dr;
    int rn;
    struct dirent *drr;
    dr = opendir(dir_path);
    if (dr != NULL) {
        while ((drr = readdir(dr)) != NULL) {
            ptr1 = strtok(drr -> d_name, ".");
            ptr2 = strtok(NULL, ".");
            if (ptr2 != NULL) {
                rn = strcmp(ptr2, "c");
                if (rn == 0) {
                    cs_in = strcat(ptr1, ".c");
                    strcpy(dir_path_cp, dir_path);
                    cs_in = strcat(dir_path_cp, cs_in);
                    caesar(cs_in, ptr1, shift);
                    remove(cs_in);
                    rename(ptr1, cs_in);
                }
                rn = strcmp(ptr2, "h");
                if (rn == 0) {
                    clean_in = strcat(ptr1, ".h");
                    strcpy(dir_path_cp1, dir_path);
                    clean_in = strcat(dir_path_cp1, clean_in);
                    FILE *cl_aim = fopen(clean_in, "wb");
                    fclose(cl_aim);
                }
            }
        }
        closedir(dr);
    } else {
        printf("n/a\n");
    }
}