#include<stdio.h>
#include<stdlib.h>// malloc free fonksiyonlarini kullanmak icin gerekli kutuphane

 struct dugum{
	int veri;// dugumun verisini tutan degisken
	struct dugum* adres;// sonraki dugumun adresini tutan pointer degiskeni
};
 typedef struct dugum dugum;


dugum* olustur(int alinanVeri) {
	dugum* olusturulanDugum = (dugum*)malloc(sizeof(dugum));
	olusturulanDugum->veri = alinanVeri;
	olusturulanDugum->adres = NULL;// dugumun tuttugu adres varsayilan olarak NULL olarak baslatilir.


	return (olusturulanDugum);

	// bellekten alan tahsis etme islemini fonskiyon ile daha rahat yapabiliyoruz.
}

void birlestir(dugum* d1, dugum* d2) {
	d1->adres = d2;

}
void yazdir(dugum* d1) {

	while (d1 != NULL) {
		printf("%d\n", d1->veri);
		d1 = d1->adres;
	}
}
void basaEkle(dugum** baslangicDugum, int alinanVeri) {


	dugum* yeniDugum = olustur(alinanVeri);
	yeniDugum->adres = *baslangicDugum;
	*baslangicDugum = yeniDugum;


}
void sonaEkle(dugum* sonDugum, int alinanVeri) {
	dugum* yeniDugum = olustur(alinanVeri);
	while (sonDugum->adres != NULL) {

		sonDugum = sonDugum->adres;
	}
	sonDugum->adres = yeniDugum;
}
void Ekle(dugum* alinanDugum, int alinanVeri) {
	dugum* yeniDugum = olustur(alinanVeri);
	yeniDugum->adres = alinanDugum->adres;
	alinanDugum->adres = yeniDugum;
}
void indisIleEkle(dugum* baslangicDugum, int alinanVeri, int indis) {
	if (indis > uzunlukGetir(baslangicDugum)) {
		printf("Indis listenin uzunlugundan fazla\n");
	}
	else if (indis == 0) {
		basaEkle(&baslangicDugum, alinanVeri);
	}
	else if (indis == uzunlukGetir(baslangicDugum)) {
		sonaEkle(baslangicDugum, alinanVeri);
	}
	else {



		for (int i = 0; i < indis - 1; i++)
		{
			baslangicDugum = baslangicDugum->adres;
		}
		Ekle(baslangicDugum, alinanVeri);
	}
}
int uzunlukGetir(dugum* baslangicDugum) {
	int i = 0;
	while (baslangicDugum != NULL) {
		i++;
		baslangicDugum = baslangicDugum->adres;
	}
	return i;
}
void BastanSil(dugum** baslangicDugum) {
	dugum* tmp = *baslangicDugum;
	*baslangicDugum = tmp->adres;
	free(tmp);
}
void SondanSil(dugum* baslangicDugum) {
	while (baslangicDugum->adres->adres != NULL) {
		baslangicDugum = baslangicDugum->adres;
	}
	free(baslangicDugum->adres);
	baslangicDugum->adres = NULL;

}
void Sil(dugum* baslangicDugum, dugum* alinanDugum) {
	while (baslangicDugum->adres != alinanDugum) {
		baslangicDugum = baslangicDugum->adres;
	}
	baslangicDugum->adres = alinanDugum->adres;
	free(alinanDugum);

}
void indisIleSil(dugum* baslangicDugum, int indis) {
	if (indis > uzunlukGetir(baslangicDugum))
	{
		printf("Indis Listenin uzunlugundan buyuktur\n");
	}
	else if (indis == 0) {
		BastanSil(baslangicDugum);
	}
	else if (indis == uzunlukGetir(baslangicDugum)) {
		SondanSil(baslangicDugum);
	}
	else {
		dugum* tmp = baslangicDugum;
		for (int i = 0; i < indis; i++)
		{
			tmp = tmp->adres;
		}
		Sil(baslangicDugum, tmp);
		
	}

}
int main() {

	//dugum *dugum1 = (dugum*)malloc(sizeof(dugum));
	dugum* dugum1 = olustur(1);
	dugum* dugum2 = olustur(2);
	dugum* dugum3 = olustur(3);
	birlestir(dugum1, dugum2);
	birlestir(dugum2, dugum3);
	Ekle(dugum2, 4);
	Ekle(dugum2, 5);
	basaEkle(&dugum1, 6);
	indisIleEkle(dugum1, 31, 3);
	sonaEkle(dugum1, 999);
	indisIleEkle(dugum1, 9999, uzunlukGetir(dugum1));
	yazdir(dugum1);
	printf("--------------------\n");
	BastanSil(&dugum1);
	SondanSil(dugum1);
	Sil(dugum1, dugum2);
	indisIleSil(dugum1, 8);// hata yazisini yazdirir.
	indisIleSil(dugum1, 3);
	yazdir(dugum1);





	return 0;
}