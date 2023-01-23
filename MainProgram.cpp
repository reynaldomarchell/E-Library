#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <conio.h>

#define llu unsigned long long
#define ll long long
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

int token = 0;
char player_real[102];

typedef struct user{
	char username[102]="\0";
	char password[102]="\0";
}user;

typedef struct pinjam_buku{
	char kode[12]="\0";
	char nama[102]="\0";
	char ketersediaan[10]="\0";
}pinjam;

typedef struct kembali_buku{
	char p_username[102]="\0";
	char nama_buku[102]="\0";
	char kode_buku[12]="\0";
	long int tanggal1={};
	long int tanggal2={};
}kembalikan;

void design();
void list_buku();
void ngilang();
void design_admin();


void credit(){
//  Credit member of Group 1 from LB75 Class.
	printf("\033[0;36m");
	usleep(1000);  
  	printf("Thank you for using our program. See you again another time! ^_^\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("Our Member : \n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("1. 2602096306 - Deli Irawan\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("2. 2602138214 - Reynaldo Marchell\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("3. 2602065950 - Ravel Jonathan\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("4. 2602086753 - Samuel Alfonsus\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("5. 2602080005 - Charis Tedjasukma\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	printf("6. 2602153373 - Muhammad Daffa\n");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
  	puts("");
  	usleep(1000); 
	printf("\033[0m");

}

void payment(int kredit){
	while(1){
		// melakukan pembayaran
		design();
		printf("\nJumlah Pembayaran: ");

		int harga;scanf("%d",&harga);

		system("cls");

		int sisa=kredit-harga;

		if(sisa==0){
			printf("Lunas. Terimakasih atas kerjasamanya\n\n");
			ngilang();
			return;
		}
		else if(sisa>0){
			printf("Belum lunas. Mohon lakukan pembayaran kembali\n");
			kredit=sisa;
			printf("Sisa pembayaran : %d\n",kredit);
		}
		else if(sisa<0){
			sisa=sisa*(-1);
			printf("Lunas. Kembalian anda adalah : %d. Terimakasih atas kerjasamanya\n",sisa);
			puts("");
			return;
		}
	}
}

void mengembalikan(char player[]){
	// get data from list
	char line[100000];
	kembalikan balik[1000];
	FILE *reading=fopen("data_buku_pinjam.dat","r");
	int i=0;

	while(fgets(line,100000,reading)){
		strcpy(balik[i].p_username,strtok(line,"#"));
		char pemindah[100];

		strcpy(pemindah,strtok(NULL,"#"));
		balik[i].tanggal1=atol(pemindah);

		strcpy(balik[i].nama_buku,strtok(NULL,"#"));
		strcpy(balik[i].kode_buku,strtok(NULL,"#"));
		strcpy(pemindah,strtok(NULL,"\n"));

		balik[i].tanggal2=atol(pemindah);
		i++;
	}

	fclose(reading);
	int jumlah=i;
	
	// get user data
	int nilai=1;
	int arr[5];

	design();
	
	int penghenti2=0;
	for(i=0;i<jumlah;i++){
		if(strcmp(balik[i].p_username,player)==0){
			printf("Data buku pinjaman ke-%d :\n",nilai);
			printf("Username peminjam : %s\n",balik[i].p_username);
			printf("Nama Buku : %s\n",balik[i].nama_buku);
			printf("Kode Buku : %s\n",balik[i].kode_buku);
			
			time_t pukul1=balik[i].tanggal1;
			struct tm *lok1=localtime(&pukul1);
			char *but=asctime(lok1);

			printf("Tanggal Meminjam : %s",but);
			time_t pukul2=balik[i].tanggal2;
			struct tm *lok2=localtime(&pukul2);
			char *then=asctime(lok2);

			printf("Tanggal kembalikan : %s\n\n",then);

			arr[nilai]=i;
			nilai++;
			penghenti2=1;
		}
	}
	
	// return the borrowed book
	int data;

	if(penghenti2==0){
		printf("\nTidak ada buku yang perlu dikembalikan\n\n");
		ngilang();
		return;
	}
	
	time_t pukul3=time(NULL);
	struct tm *lok3=localtime(&pukul3);
	char *now=asctime(lok3);
	long int penyimpan=pukul3; 

	printf("Tanggal saat ini : %s\n",now);

	printf("Data buku ke berapa yang ingin dikembalikan?: ");
	scanf("%d",&data);

	if(data > jumlah || data <= 0){
			system("cls");
			return ;
	}

	system("cls");
	
	
	if(balik[arr[data]].tanggal2-penyimpan>=0){
		printf("Buku telah dikembalikan. Terima Kasih sudah meminjam.\n\n");
		ngilang();
	}else{
		// listing for consequence
		printf("\033[0;31m");
		printf("ANDA TELAT\n\n");
		printf("\033[0m");
		int waktu_terlambat=(penyimpan-balik[arr[data]].tanggal2+3600)/3600;
		printf("Total waktu ketelatan = %d jam\n\n",waktu_terlambat);
		printf("Konsekuensi jika telat: \n");
		printf("- 1 jam = denda 5.000\n");
		printf("- 1 hari = denda 100.000\n");
		printf("- 30 hari = denda 5.000.000\n");
		printf("- Lebih dari 2 bulan = Anda di blacklist\n\n");
		int total;
		
		// JUDGEMENT TIME
		if(waktu_terlambat>1440){
			printf("Anda di blacklist\n");
			// write the username into blacklist
			FILE *blacklist=fopen("data_blacklist.dat","a");
			fprintf(blacklist,"%s\n",balik[arr[data]].p_username);
			fclose(blacklist);
		}else if(waktu_terlambat<1440 && waktu_terlambat>720){
			int sisa=waktu_terlambat-720;
			int sisah=sisa/24;
			sisa-=(sisah*24);
			total=(sisah*100000)+(sisa*5000)+5000000;
			printf("Total denda : %d\n",total);
			payment(total);
		}else if(waktu_terlambat<720 && waktu_terlambat>24){
			int sisa=waktu_terlambat/24;
			int sisaj=waktu_terlambat-(sisa*24);
			total=((waktu_terlambat/24)*100000)+(sisaj*5000);
			printf("Total denda : %d\n",total);
			payment(total);
		}else if(waktu_terlambat<24){
			total=waktu_terlambat*5000;
			printf("Total denda : %d\n",total);
			payment(total);
		}
	}
	
	// deleting the user data
		FILE *rewrite=fopen("data_buku_pinjam.dat","w");
		for(i=0;i<jumlah;i++){
			if(i==arr[data]){
				continue;
			}
			fprintf(rewrite,"%s#%lld#%s#%s#%lld\n",balik[i].p_username,balik[i].tanggal1,balik[i].nama_buku,balik[i].kode_buku,balik[i].tanggal2);
		}
		fclose(rewrite);
	
	// read the list of book data
		FILE *data_buku_baca=fopen("data_buku.dat","r");
		pinjam datbuk[1000];
		int jumlah2=0;

		for(i=0;fgets(line,100000,data_buku_baca);i++){
			strcpy(datbuk[i].nama,strtok(line,"#"));
			strcpy(datbuk[i].kode,strtok(NULL,"#"));
			strcpy(datbuk[i].ketersediaan,strtok(NULL,"\n"));
			jumlah2++;
		}

		fclose(data_buku_baca);

		for(i=0;i<jumlah2;i++){
			if(strcmp(balik[arr[data]].nama_buku,datbuk[i].nama)==0){
				int pengubah=atoi(datbuk[i].ketersediaan);
				pengubah++;

				sprintf(datbuk[i].ketersediaan,"%d",pengubah);
				break;
			}
		}

		// rewriting the book data
		FILE *renew=fopen("data_buku.dat","w");
		for(i=0;i<jumlah2;i++){
			fprintf(renew,"%s#%s#%s\n",datbuk[i].nama,datbuk[i].kode,datbuk[i].ketersediaan);
		}
		fclose(renew);
		
	return;
}

void meminjam2(char kode_buku[],char nama_buku[],char player[]){
	//list the time
	time_t waktu=time(NULL);
	struct tm *lokal=localtime(&waktu);
	char *now=asctime(lokal);

	puts("");
	printf("Waktu peminjaman : %s",now);
	printf("Nama buku : %s\n",nama_buku);
	printf("Kode buku : %s\n",kode_buku);

	lokal->tm_mday=lokal->tm_mday+7;

	char *then=asctime(lokal);

	printf("Waktu pengembalian : %s",then);
	puts("");
	printf("Buku berhasil dipinjam.\n");
	puts("");

	ngilang();
	
	//write down the borrower data
	FILE *data_buku_pinjam=fopen("data_buku_pinjam.dat","a");
	fprintf(data_buku_pinjam,"%s#%lld#%s#%s#%lld\n",player,waktu,nama_buku,kode_buku,waktu+604800);
	fclose(data_buku_pinjam);

	return;
}

void meminjam(char player[]){
	//do some listing
	FILE *data_buku_baca=fopen("data_buku.dat","r");
	pinjam datbuk[1000];
	char line[100000];
	int jumlah=0;
	
	for(int i=0;fgets(line,100000,data_buku_baca);i++){
		strcpy(datbuk[i].nama,strtok(line,"#"));
		strcpy(datbuk[i].kode,strtok(NULL,"#"));
		strcpy(datbuk[i].ketersediaan,strtok(NULL,"\n"));
		jumlah++;
	}
	fclose(data_buku_baca);
	
	//do some searching
	phase1:
	design();
	list_buku();
	printf("\nMasukan nama/inisial buku yang diinginkan atau masukan 0 (nol) jika ingin kembali ke menu: ");
	
	char ss[100];
	
	getchar();
	scanf("%[^\n]",ss);
	system("cls");

	if(ss[0]=='0') return;

	int penghenti=0;

	design();

	for(int i=0;i<jumlah;i++){
		if(strstr(datbuk[i].nama,ss)!=NULL || strstr(datbuk[i].kode,ss)!=NULL){
			printf("Nama Buku : %s\n",datbuk[i].nama);
			printf("Kode Buku : %s\n",datbuk[i].kode);
			printf("Ketersediaan Buku : %s\n\n",datbuk[i].ketersediaan);
			puts("");
			penghenti=1;
		}
		else if(i==jumlah-1 && penghenti==0){
			printf("Maaf buku yang anda cari tidak ada. Silahkan input kembali\n");
			sleep(2);
			goto phase1;
		}
	}
	
	// asking for some borrowing
	phase2:
	char jawaban;

	printf("Ingin Pinjam? (Y/N): ");
	getchar();
	scanf("%c",&jawaban);
	
	if(jawaban=='N' || jawaban=='n'){
		goto phase1;
	}
	else if(jawaban=='Y' || jawaban=='y'){
		printf("\nMasukan nama atau kode buku yang ingin dipinjam (yang lengkap): ");
		
		char sss[100];
		
		getchar();
		
		scanf("%[^\n]",sss);
		system("cls");
		
		for(int i=0;i<jumlah;i++){
			if(strcmp(datbuk[i].nama,sss)==0 || strcmp(datbuk[i].kode,sss)==0){
				if(datbuk[i].ketersediaan[0]=='0'){
					printf("Maaf buku yang anda ingin pinjam sudah habis. Silahkan pilih yang lain\n");
					sleep(2);
					goto phase1;
				}

				meminjam2(datbuk[i].kode,datbuk[i].nama,player);
				int sisa=atoi(datbuk[i].ketersediaan);
				sisa--;
				sprintf(datbuk[i].ketersediaan,"%d",sisa);
			}
			
			//rewriting the book list
			FILE *data_buku_tulis=fopen("data_buku.dat","w");

			for(int i=0;i<jumlah;i++){
				fprintf(data_buku_tulis,"%s#%s#%s\n",datbuk[i].nama,datbuk[i].kode,datbuk[i].ketersediaan);
			}
			fclose(data_buku_tulis);
		}
	}
	else{
		printf("Input salah. Silahkan masukan kembali\n");
		goto phase2;
	}
}

// List Function
void swap(char a[], char b[]){
    char temp[100];
    strcpy(temp, b);
    strcpy(b, a);
    strcpy(a, temp);
}

void list_buku(){
    //show the list
    FILE *reading=fopen("data_buku.dat","r");
    char line[100000];
    pinjam datbuk[1000];
    int jumlah = 0;
    
    for(int i=0;fgets(line,1000,reading);i++){
        strcpy(datbuk[i].nama,strtok(line,"#"));
        strcpy(datbuk[i].kode,strtok(NULL,"#"));
        strcpy(datbuk[i].ketersediaan,strtok(NULL,"\n"));
        jumlah++;
    }

    // Sort struct datbuk
  for(int i = 0; i < jumlah - 1; i++){
    for(int j = 0; j < jumlah - 1 - i; j++){
      if(strcmp(datbuk[j].nama, datbuk[j + 1].nama) > 0){
        swap(datbuk[j].nama, datbuk[j+1].nama);
        swap(datbuk[j].kode, datbuk[j+1].kode);
        swap(datbuk[j].ketersediaan, datbuk[j+1].ketersediaan);
      }
    }
  }

    for(int i=0;i<jumlah;i++){
        printf("Data Buku ke %d\n",i+1);
        printf("Nama buku : %s\n",datbuk[i].nama);
        printf("Kode buku : %s\n",datbuk[i].kode);
        printf("Ketersediaan buku : %s\n\n",datbuk[i].ketersediaan);
    }
    fclose(reading);
}

char* welcome();

char* login(){
   // Get data from user list 
   char username[100],password[100];
   user user[1000];
   char line[100000];
   int total_data=0;
   FILE *fpu = fopen("user.dat", "r");

   for(int i=0;fgets(line,100000,fpu);i++){
 		strcpy(user[i].username,strtok(line,"#"));
 		strcpy(user[i].password,strtok(NULL,"\n"));
 		total_data++;
   }
   fclose(fpu);
  
  	// input to login
  	test:
	design();

    printf("\nMasukkan username yang telah didaftarkan:\n");
    scanf("%s", username);
    printf("\nMasukkan password yang telah didaftarkan:\n");
    scanf("%s", password);
    system("cls");
    
    for(int i=0;i<total_data;i++){
    	if(strcmp(username,user[i].username) == 0 && strcmp(password,user[i].password) == 0){
        	printf("");
        	token=1;
       		return username;
      	}
 	}

 	wrong:
	design();
    printf("Log in Failed.\n\n");
    printf("Ingin mencoba kembali? \n");
    printf("1. Ya     2. Tidak\n");
    printf("\nJawaban: ");
	
   	int jawaban;
	scanf("%d",&jawaban);
	getchar();

   	system("cls");
    if(jawaban==1){
      	goto test;
	}
	else if(jawaban==2){
		welcome();
	}
	else{
		printf("Maaf inputan anda salah. Silahkan masukan kembali\n");
		goto wrong;
	}
}

void signin(){
  char username[100], password[100];
  FILE *fpu = fopen("user.dat", "a");
  
  //crate username and input to userlist
  design();

  printf("Masukkan username untuk didaftarkan:\n");
  getchar();
  scanf("%[^\n]", username);
  getchar();

  user user[1000];
  char line[100000];
  FILE *fpop=fopen("user.dat","r");

  for(int i=0;fgets(line,100000,fpop);i++){
		strcpy(user[i].username,strtok(line,"#"));
		strcpy(user[i].password,strtok(NULL,"\n"));

		if(strcmp(user[i].username,username)==0){
			printf("\nUsername anda sudah ada yang menggunakannya\n");
			sleep(2);
			system("cls");
			welcome();
		}
  }
  fclose(fpop);
  fprintf(fpu, "%s", username);
  
  //create password and input to userlist
  sandi:
  printf("\nPassword minimal terdapat 8 karakter alfanumerik serta terdapat minimal 1 simbol \"@\"\n");
  printf("Password tak boleh terdapat simbol lain selain \"@\"\n");
  printf("\nMasukkan password untuk didaftarkan:\n");

  scanf("%[^\n]", password);getchar();
  system("cls");

  int panjang= strlen(password);
 
  if(panjang<8){
  	printf("Maaf, password terlalu pendek. Silahkan input kembali\n ");
		sleep(2);
  	system("cls");
		goto sandi;
  }else{
  	for(int i=0;i<panjang;i++){
  		if(password[i]>=65 && password[i]<=90){
  			password[i]+=32;
		  }
	}
	if(strrchr(password,'@')==NULL){
  			printf("Maaf, password harus terdapat simbol \"@\" min 1. Silahkan input kembali\n ");
				sleep(2);
				system("cls");
				goto sandi;
	}
  	for(int i=0;i<panjang;i++){
  		if((password[i]<'a' || password[i]>'z') && (password[i]<'0' || password[i]>'9') && password[i]!='@' && password!='\0'){
  			printf("Password tak boleh terdapat simbol lain selain \"@\". Silahkan Input kembali\n");
  			sleep(2);
				system("cls");
				goto sandi;
		  }
	}
  }

  fprintf(fpu, "#%s\n", password);
  fclose(fpu);
  
  //checking if username already listed
  fpop=fopen("user.dat","r");

	for(int i=0;fgets(line,100000,fpop);i++){
		strcpy(user[i].username,strtok(line,"#"));
		strcpy(user[i].password,strtok(NULL,"\n"));

		if(strcmp(user[i].username,username)==0 && strcmp(user[i].password,password)==0){
			printf("Username telah terdaftar. Silahkan melakukan login\n");
			login();
		}
	}
	fclose(fpop);
}

char* welcome(){
	int ac;

	design();

	printf("\nApakah anda sudah memiliki Akun?\n1. Sudah -> Log in\n2. Belum -> Sign in\n");
    printf("\nPILIHAN: ");
	scanf("%d", &ac);
    system("cls");
    
	char player[100];

    if(ac == 1)
    	strcpy(player,login());
    else if(ac == 2)
    	signin();
    else{
    	printf("Maaf input anda salah, silahkan masukan kembali\n");
    	welcome();
	}
    return player;
}

void loading(){
	for(int i=1; i<=5; i++){
		system("cls");
		printf("\033[0;35m");
		printf("\n         %d%%          ", 20*i);
		printf("\033[0m");
		sleep(1);
	}
}

/* FUNCTION FOR ADMIN START HERE */
// Function for admin main menu
void menu_admin(){
	design_admin();
	printf("\nPilih menu:\n");
	printf("1. Edit data buku\n");
	printf("2. Buku yang dipinjam\n");
	printf("3. Remove blacklist\n");
	printf("4. Exit\n");
	printf("\nPILIHAN : ");
}

// Function for editing book
void setor_baru(){
	system("cls");
	design_admin();

	FILE *fp=fopen("data_buku.dat","a");
	char kode[100], judul[100], qty[100];

	getchar();
	printf("\nMasukkan judul buku:\n");
	scanf("%[^\n]", judul);	getchar();
	printf("Masukkan kode buku:\n");
	scanf("%[^\n]", kode); getchar();
	printf("Masukkan jumlah buku:\n");
	scanf("%[^\n]", qty);	getchar();

	fprintf(fp, "%s#%s#%s\n", judul, kode, qty);
	fclose(fp);
	
	return;
}

void edit_buku(){
	FILE *reading=fopen("data_buku.dat","r");
	char line[100000];
	pinjam datbuk[1000];
	int jumlah = 0;
	
	for(int i=0;fgets(line,1000,reading);i++){
		strcpy(datbuk[i].nama,strtok(line,"#"));
		strcpy(datbuk[i].kode,strtok(NULL,"#"));
		strcpy(datbuk[i].ketersediaan,strtok(NULL,"\n"));
		jumlah++;
	}

	// Sort struct datbuk
  for(int i = 0; i < jumlah - 1; i++){
    for(int j = 0; j < jumlah - 1 - i; j++){
      if(strcmp(datbuk[j].nama, datbuk[j + 1].nama) > 0){
        swap(datbuk[j].nama, datbuk[j+1].nama);
        swap(datbuk[j].kode, datbuk[j+1].kode);
        swap(datbuk[j].ketersediaan, datbuk[j+1].ketersediaan);
      }
    }
  }

	book_list:
	system("cls");
	design_admin();
	printf("\n");
	for(int i=0;i<jumlah;i++){
		printf("Data Buku ke %d\n",i+1);
		printf("Nama buku : %s\n",datbuk[i].nama);
		printf("Kode buku : %s\n",datbuk[i].kode);
		printf("Ketersediaan buku : %s\n\n",datbuk[i].ketersediaan);
	}
	fclose(reading);

	printf("\nPilih menu:\n1. Add\n2. Remove\n3. Back\n");
	printf("\nPILIHAN : ");
	int jawaban;
	scanf("%d",&jawaban); getchar();
	

	char nama_buku[100];
	if(jawaban==1){
		printf("\nMasukkan nama buku:\n");
		scanf("%[^\n]", nama_buku);

		FILE *writing1=fopen("data_buku.dat","w");
		int flag=0;
		for(int i=0; i<jumlah; i++){
			if(strcmp(nama_buku, datbuk[i].nama)==0){
				char temp[100];
				int num;

				flag=1;

				strcpy(temp, datbuk[i].ketersediaan);
				num=atoi(temp);
				num++;
				sprintf(temp, "%d", num);
				strcpy(datbuk[i].ketersediaan, temp);
			}
			fprintf(writing1,"%s#%s#%s\n", datbuk[i].nama, datbuk[i].kode, datbuk[i].ketersediaan);
		}
		fclose(writing1);

		if(flag==0){
			printf("\nBuku tersebut belum tersedia, silakan daftarkan buku!\n");
			sleep(2);
			setor_baru();
		}
		else{
			printf("\nBuku berhasil ditambahkan!\n");
			sleep(2);
		}
	}
	else if(jawaban==2){
		printf("\nMasukkan nama buku:\n");
		scanf("%[^\n]", nama_buku);

		FILE *writing2=fopen("data_buku.dat","w");
		for(int i=0; i<jumlah; i++){
			if(strcmp(nama_buku, datbuk[i].nama)==0){
				char temp[100];
				int num;

				strcpy(temp, datbuk[i].ketersediaan);
				num=atoi(temp);
				num--;
				sprintf(temp, "%d", num);
				strcpy(datbuk[i].ketersediaan, temp);
			}
			fprintf(writing2,"%s#%s#%s\n", datbuk[i].nama, datbuk[i].kode, datbuk[i].ketersediaan);
		}
		fclose(writing2);

		printf("\nBuku berhasil diremove!\n");
		sleep(2);
	}
	else if(jawaban==3) return;
	else{
		printf("Input Salah!\n");
		sleep(1);
		system("cls");
		goto book_list;
	}
}

// Function for edit blacklist
void edit_blacklist(){
	char data_blacklist[1000][100];
	char line[100000]="\0";

	int jumlah = 0;
	
	FILE *blacklist=fopen("data_blacklist.dat","r");
	for(int i=0;fgets(line,100000,blacklist);i++){
		strcpy(data_blacklist[i],strtok(line,"\n"));
		jumlah++;
	}
	fclose(blacklist);

	lagi:
	system("cls");
	design_admin();

	printf("\nNama akun yang terblokir\n\n");
	for(int i=0; i<jumlah; i++){
		printf("%d. %s\n", i+1, data_blacklist[i]);
	}

	char user_name[100];
	printf("\nMasukkan nama yang ingin diremove ('0' untuk kembali):\n");
	scanf("%[^\n]", user_name);
	getchar();

	if(strcmp(user_name, "0")==0) return;
	
	int flag=0;

	FILE *write=fopen("data_blacklist.dat","w");
	for(int i=0; i<jumlah; i++){
		if(strcmp(user_name, data_blacklist[i])==0){
			flag=1;
			continue;
		}
		fprintf(write,"%s\n", data_blacklist[i]);
	}
	fclose(blacklist);

	if(flag==0){
		printf("Nama tidak ditemukan!\n");
		sleep(2);
		goto lagi;
	}
	else
		printf("\nAkun yang terblokir berhasil diremove!\n");
	
	sleep(2);
}

// Function for see book borrowed detail
void buku_dipinjam(){
	kembalikan st[1000];
	char line[100000];
	int jumlah = 0;

	FILE *fp=fopen("data_buku_pinjam.dat", "r");
	for(int i=0; fgets(line,100000,fp); i++){
		char temp_char[100000]="\0";
		long int temp_int=0;

		strcpy(st[i].p_username,strtok(line,"#"));

		strcpy(temp_char,strtok(NULL,"#"));
		temp_int=atoi(temp_char);
		st[i].tanggal1 = temp_int;

		strcpy(st[i].nama_buku,strtok(NULL,"#"));

		strcpy(st[i].kode_buku,strtok(NULL,"#"));

		strcpy(temp_char,strtok(NULL,"\n"));
		temp_int=atoi(temp_char);
		st[i].tanggal2 = temp_int;

		jumlah++;
	}
	fclose(fp);
	
	again:
	system("cls");
	design_admin();
	printf("\nData buku yang dipinjam\n");
	for(int i=0; i<jumlah; i++){
		printf("\nNama Peminjam: %s\n", st[i].p_username);

		printf("Nama Buku: %s\n", st[i].nama_buku);

		printf("Kode Buku: %s\n", st[i].kode_buku);

		time_t waktu1=st[i].tanggal1;
		struct tm *local1=localtime(&waktu1);
		char *date1=asctime(local1);
		printf("Tanggal Meminjam: %s", date1);

		time_t waktu2=st[i].tanggal2;
		struct tm *local2=localtime(&waktu2);
		char *date2=asctime(local2);
		printf("Tanggal Pengembalian: %s", date2);
	}
	
	int op;
	printf("\nMasukkan '0' untuk kembali\n");
	scanf("%d", &op);

	if(op==0) return;
	else goto again;
}

// Admin main function
void admin(){
	int op;

	while(1){
		system("cls");
		menu_admin();
		scanf("%d", &op); getchar();

		switch(op){
			case 1:{
				edit_buku();
				break;
			}
			case 2:{
				buku_dipinjam();
				break;
			}
			case 3:{
				edit_blacklist();
				break;
			}
			case 4:{
				system("cls");
				credit();
				return;
			}
			default:{
				printf("Input salah!\n");
				sleep(1);
			}
		}
	}
}
/* FUNCTION FOR ADMIN END HERE */

void ngilang(){
// Buat jeda
	int i;
	for(i=3;i>=1;i--){
		printf("This text will close in %d...\n", i);
		sleep(1);
	}
	system("cls");
}

void design(){
// Function for design E-Library
	printf("\033[0;32m");
printf(
  "......................................................\n"
  "|  ______      _      _ _                            |\t\n"
  "| |  ____|    | |    (_) |                           |\t\n"
  "| | |__ ______| |     _| |__  _ __ __ _ _ __ _   _   |\t\n"
  "| |  __|______| |    | | '_ \\| '__/ _` | '__| | | |  |\t\n"
  "| | |____     | |____| | |_) | | | (_| | |  | |_| |  |\t\n"
  "| |______|    |______|_|_.__/|_|  \\__,_|_|   \\__, |  |\t\n"
  "|                                             __/ |  |\t\n"
  "|                                            |___/   |\t\n"\
  "|....................................................|\n"
    );
	printf("\033[0m");

	printf("\033[0;34m");
	printf(COLOR_BOLD"This program was made by Group 1.\n\n\n"COLOR_OFF);
	printf("\033[0m");
}

void design_admin(){
	printf(
		"              _           _       	 \n"
			"     /\\      | |         (_)       \n"
			"    /  \\   __| |_ __ ___  _ _ __  \n"
			"   / /\\ \\ / _` | '_ ` _ \\| | '_ \\ \n"
			"  / ____ \\ (_| | | | | | | | | | | \n"
			" /_/    \\_\\__,_|_| |_| |_|_|_| |_| \n"

	);
}

// Main Function
int main(){
	int op, ac;

	system ("cls");
	sleep(1);
	loading();
	system ("cls");

	start:
	design();
	printf("Ingin log-in sebagai apa?\n1. Admin\n2. User\n");
	printf("\nPILIHAN : ");
	scanf("%d", &ac);

	if(ac==1){
		char player_real2[102];
		strcpy(player_real2, login());
		if(strcmp(player_real2, "admin")==0){
			admin();	
		}
		else{
			printf("ANDA BUKAN ADMIN!!!\n");
			ngilang();
			token = 0;
			goto start;
		}
	}

	else if(ac==2){
		system("cls");
		if(token == 1){
			menu:
			design();

			printf("\n\nMENU\n");
			printf("1. List Buku\n");
			printf("2. Meminjam buku\n");
			printf("3. Mengembalikan buku\n");
			printf("4. Exit\n\n");
			printf("PILIHAN : ");

			scanf("%d",&op);

			system("cls");

			switch(op){
				case 1: 
					list_buku();
					goto menu;
				case 2:
					meminjam(player_real);
					goto menu;
				case 3:
					mengembalikan(player_real);
					goto menu;
				case 4:
					credit();
					return 0;
				default:
					goto menu;
			}
		}
		else{
		strcpy(player_real,welcome());

		char data_blacklist[1000][100];
		char line[100000];
		FILE *blacklist=fopen("data_blacklist.dat","r");

		for(int i=0;fgets(line,100000,blacklist);i++){
			strcpy(data_blacklist[i],strtok(line,"\n"));

			if(strcmp(data_blacklist[i],player_real)==0){
				design();
				printf("\nMaaf akun anda sudah terblokir. Silahkan Hubungi pihak admin untuk informasi lebih lanjut\n");
				exit(0);
			}
		}
		fclose(blacklist);
		goto menu;
		}
	}
	else{
		printf("Input salah!");
		sleep(1);
		system("cls");

		goto start;
	}
}
