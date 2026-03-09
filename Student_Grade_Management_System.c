#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
     char name[50];
     int grade;
     struct student * next;
};

typedef struct student node;

void addStudent(node **root) { //Çift yıldız kullanarak root'un adresini alıyoruz, böylece fonksiyon içinde root'u değiştirebiliriz.
     node *newStuedent = (node*)malloc(sizeof(node)); //Yeni bir öğrenci düğümü oluşturmak için bellek ayırıyoruz.

     printf("ogrenci adi: "); //Kullanıcıdan öğrenci adını alıyoruz.
     scanf("%s", newStuedent->name); //Adı doğrudan düğümün name alanına kaydediyoruz.
     printf("Notu: "); //Kullanıcıdan öğrenci notunu alıyoruz.
     scanf("%d", &newStuedent->grade);  //Notu doğrudan düğümün grade alanına kaydediyoruz.
     newStuedent->next = NULL; //Bu yeni düğüm listenin sonu olacak. 

     //1. Liste boş mu?
     if (*root == NULL) {
          *root = newStuedent; //Liste boşsa, yeni öğrenci listenin başıdır.
     }

     //2. Liste doluysa sona kadar git.
     else {
          node *temp = *root; //Geçici bir gösterici oluşturuyoruz, başlangıçta root'u gösteriyor.
          while (temp->next != NULL) //Listenin sonuna kadar ilerliyoruz.
          {
           temp = temp->next; //Bir sonraki düğüme geç. 
          }
          temp->next = newStuedent; //Sona ulaştık, yeni öğrenciyi buraya bağla.
     }
}

void saveStudentsToFile(node*root) {
     FILE *fp = fopen("ogrenciler.txt", "w"); //w modu dosyayı sıfırdan oluşturur veya içeriği silip yazar.

     if (fp == NULL) {
          printf("Dosya açilamadi!\n");
          return; //Dosya açılamazsa fonksiyonu sonlandır.
     }

     node *temp = root; //Geçici bir gösterici oluşturuyoruz, başlangıçta root'u gösteriyor.
     while (temp != NULL) {
          //Veriyi dosyaya yazdır.
          fprintf(fp, "%s %d\n", temp->name, temp->grade); //Öğrenci adını ve notunu dosyaya yazıyoruz.
          temp = temp->next; //Bir sonraki düğüme geç.
     }

     fclose(fp); //Dosyayı kapatıyoruz.
     printf("Veriler dosyaya basariyla kaydedildi.\n");
}

void loadStudentsFromFile(node **root) {
     FILE *fp = fopen("ogrenciler.txt", "r"); //r modu dosyayı okumak için açar.
     if (fp == NULL) return; //Dosya açılamazsa fonksiyonu sonlandır.

     char name[50];
     int grade;

     while (fscanf(fp, "%s %d", name, &grade) != EOF) {
          //Yeni bir düğüm oluştur
          node *newNode = (node*)malloc(sizeof(node));
          strcpy(newNode->name, name); //Dosyadan okunan adı düğümün name alanına kopyala.
          newNode->grade = grade; //Dosyadan okunan notu düğümün grade alanına kaydet.
          newNode->next = NULL; //Yeni düğümün next alanını NULL yap.
          
          //Listeye ekle
          if(*root == NULL) {
               *root = newNode;
          }

          else {
               node *temp = *root;
               while (temp->next != NULL ) {
                    temp = temp->next; //Listenin sonuna kadar ilerle.
               }
               temp->next = newNode; //Sona ulaştık, yeni düğümü buraya bağla.
          }
          }
          fclose(fp); //Dosyayı kapatıyoruz.
}

void deleteStudent(node **root, char *name) { 
     node *temp = *root, *prev = NULL; //Geçici bir gösterici oluşturuyoruz, başlangıçta root'u gösteriyor. Ayrıca önceki düğümü takip etmek için prev oluşturuyoruz

     //1.Durum: Silinecek düğüm listenin başındaysa
     if(temp != NULL && strcmp(temp->name, name) == 0) { //Silinecek düğümün adı ile temp'in adı eşleşiyor mu?
          *root = temp->next; //Root'u silinecek düğümün bir sonraki düğümüne güncelle.
          free(temp); //Eski baş düğümü serbest bırak.
          printf("%s silindi.\n", name);
          return; //Fonksiyonu sonlandır.
     }

     //2. Durum: Silinecek düğüm listenin başında değilse, düğümü bulana kadar ilerle.
     while (temp != NULL && strcmp(temp->name, name) != 0) { //Silinecek düğümün adı ile temp'in adı eşleşmiyor mu?
          prev = temp; //prev'i güncelle, temp'i bir sonraki düğüme geçir.
          temp = temp->next; //Bir sonraki düğüme geç.
     }

     //Bulamadıysak.
     if(temp == NULL) {
          printf("Ogrenci bulunamadi.\n");
          return;
     }

     //Bulduk, zinciri kopar ve aradan çıkar.
     prev->next = temp->next; //Önceki düğümün next'ini silinecek düğümün next'ine bağla.
     free(temp); //Silinecek düğümü serbest bırak.
     printf("%s silindi.\n",name);
}

     int main() { 
    node *root = NULL; // Sadece bir kez tanimliyoruz.
    loadStudentsFromFile(&root);
    
    int secim;
    char isim[50];

    printf("1-Ekle, 2-Sil, 3-Cikis: ");
    scanf("%d", &secim);

    if(secim == 1) {
     addStudent(&root); //Öğrenci ekleme fonksiyonunu çağırıyoruz.
     saveStudentsToFile(root); //Değişiklikleri dosyaya kaydediyoruz.
    }
    else if(secim == 2) {
     printf("Silinecek isim: ");
     scanf("%s", isim);
     deleteStudent(&root, isim); //Öğrenci silme fonksiyonunu çağırıyoruz.
     saveStudentsToFile(root); //Değişiklikleri dosyaya kaydediyoruz.
    }
    
    return 0;
}