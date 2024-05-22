#include "linearList.h"
#include <limits.h>
#include <malloc.h>

/********** BODY SUB PROGRAM ***********/
/**** Predikat untuk test keadaan LIST  ****/
boolean ListEmpty(List L)
/* Mengirim true jika List Kosong */
{
	return (First(L) == Nil);
}

/**** Konstruktor/Kreator List Kosong ****/
void CreateList(List *L)
/* IS : L sembarang */
/* FS : Terbentuk List Kosong */
{
	First(*L) = Nil;
}

/**** Manajemen Memory ****/
addressP Alokasi(infotypeP X)
/* Mengirimkan addressP hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressP != Nil, 	   */
/*	dan misalnya menghasilkan P, maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	/* Kamus Lokal */
	addressP P;
	/* Algoritma */
	P = (addressP)malloc(sizeof(ElmtList));
	if (P != Nil) /* Alokasi berhasil */
	{
		Info(P) = X;
		Next(P) = Nil;
	}
	return (P);
}

void DeAlokasi(addressP P)
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian addressP P ke system */
{
	if (P != Nil)
	{
		free(P);
	}
}

/**** Pencarian sebuah elemen List ****/
addressP Search(List L, infotypeP X)
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan addressP elemen tsb. */
/* Jika tidak ada, mengirimkan Nil */
/* Menggunakan variabel bertype boolean */
{
	/* Kamus Lokal */
	addressP P;
	boolean found = false;
	/* algoritma */
	P = First(L);
	while ((P != Nil) && (!found))
	{
		if (Info(P) == X)
		{
			found = true;
		}
		else
		{
			P = Next(P);
		}
	} /* P = Nil atau Ketemu */
	return (P);
}

boolean FSearch(List L, addressP P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	/* Kamus Lokal */
	boolean found = false;
	addressP PSearch;
	/* Algortima */
	PSearch = First(L);
	while ((PSearch != Nil) && (!found))
	{
		if (PSearch == P)
		{
			found = true;
		}
		else
		{
			PSearch = Next(PSearch);
		}
	} /* PSearch = Nil atau Ketemu */
	return (found);
}

addressP SearchPrec(List L, infotypeP X)
/* Mengirimkan addressP elemen sebelum elemen yang nilainya = X */
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan addressP Prec, dengan Next(Prec) = P dan Info(P) = X */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec = Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
	/* Kamus Lokal */
	addressP Prec, P;
	boolean found = false;
	/* Algoritma */
	Prec = Nil;
	P = First(L);
	while ((P != Nil) && (!found))
	{
		if (Info(P) == X)
		{
			found = true;
		}
		else
		{
			Prec = P;
			P = Next(P);
		}
	} /* P = Nil atau Ketemu */
	if (found)
	{
		return (Prec);
	}
	else
	{
		return (Nil);
	}
}

/**** PRIMITIF BERDASARKAN NILAI ****/
/**** Penambahan Elemen ****/
void InsVFirst(List *L, infotypeP X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	/* Kamus Lokal */
	addressP P;
	/* Aloritma */
	P = Alokasi(X);
	if (P != Nil)
	{
		InsertFirst(&(*L), P);
	}
}

void InsVLast(List *L, infotypeP X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir (elemen terakhir adalah yang baru) */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal IS = FS */
{
	/* Kamus Lokal */
	addressP P;
	/* Algoritma */
	P = Alokasi(X);
	if (P != Nil)
	{
		InsertLast(&(*L), P);
	}
}

/**** PRIMITIF BERDASARKAN ALAMAT ****/
/**** Penambahan elemen berdasarkan alamat ****/
void InsertFirst(List *L, addressP P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : menambahkan elemen ber-addressP P sebagai elemen pertama */
{
	Next(P) = First(*L);
	First(*L) = P;
}

void InsertAfter(List *L, addressP P, addressP Prec)
/* IS : Prec pastilah elemen List dan bukan elemen terakhir */
/*	P sudah dialokasi */
/* FS : Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P) = Next(Prec);
	Next(Prec) = P;
}

void InsertLast(List *L, addressP P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : P ditambahkan sebagai elemen terakhir yang baru */
{
	/* Kamus Lokal */
	addressP Last;
	/* Algoritma */
	if (First(*L) != Nil)
	{
		Last = First(*L);
		while (Next(Last) != Nil)
		{
			Last = Next(Last);
		}
		Next(Last) = P;
	}
	else
	{
		First(*L) = P;
	}
}

/**** Penghapusan Elemen ****/
void DelVFirst(List *L, infotypeP *X)
/* IS : L TIDAK Kosong */
/* FS : Elemen pertama List dihapus, nilai info disimpan ke X */
/* 	dan alamat elemen pertama di dealokasi */
{
	if (First(*L) == Nil)
	{
		// Underflow
		printf("List Kosong .... \n");
	}
	else
	{
		/* Kamus Lokal */
		addressP P;
		/* Algoritma */
		// P = First(*L);
		// First(*L) = Next(First(*L));
		DelFirst(L, &P);
		*X = Info(P);
		DeAlokasi(P);
	}
}

void DelVLast(List *L, infotypeP *X)
/* IS : L TIDAK Kosong */
/* FS : Elemen terakhir list dihapus : nilai info disimpan pada X */
/* 	dan alamat elemen terakhir di dealokasi */
{
	if (First(*L) == Nil)
	{
		// Underflow
		printf("List Kosong .... \n");
	}
	else
	{
		/* Kamus Lokal */
		addressP PDel;
		/* Algoritma */
		PDel = First(*L);
		DelLast(&(*L), &PDel);
		(*X) = Info(PDel);
		DeAlokasi(PDel);
	}
}

/**** Penghapusan sebuah elemen ****/
void DelFirst(List *L, addressP *P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen pertama list sebelum penghapusan */
/*	elemen list berkurang satu (mungkin menjadi kosong) */
/* First elemen yang baru adalah suksessor elemen pertama yang lama */
{
	*P = First(*L);
	First(*L) = Next(First(*L));
}

void DelLast(List *L, addressP *P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen terakhir list sebelum penghapusan */
/*	Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last elemen baru adalah predesessor elemen terakhir yang lama, jika ada */
{
	/* Kamus Lokal */
	addressP Prec;
	/* Algoritma */
	*P = First(*L);
	Prec = Nil;
	while (Next(*P) != Nil)
	{
		Prec = *P;
		*P = Next(*P);
	}

	if (Prec == Nil) /* Hanya 1 elemen */
	{
		First(*L) = Nil;
	}
	else /* List Lebih dari 1 elemen */
	{
		Next(Prec) = Nil;
	}
}

void DelP(List *L, infotypeP X)
/* IS : L sembarang */
/* FS : Jika ada elemen list beraddressP P, dengan Info(P) = X */
/* 	Maka P dihapus dari list dan di dealokasi */
/* Jika tidak ada elemen list dengan Info(P) = X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	/* Kamus Lokal */
	addressP P, Prec;
	boolean found = false;
	/* Algoritma */
	Prec = Nil;
	P = First(*L);
	while ((P != Nil) && (!found))
	{
		if (Info(P) == X)
		{
			found = true;
		}
		else
		{
			Prec = P;
			P = Next(P);
		}
	} /* P = Nil Atau Ketemu */

	if (found)
	{
		if (Prec == Nil && Next(P) == Nil) /* Hanya 1 elemen */
		{
			First(*L) = Nil;
		}
		else if (Prec == Nil) /* Ketemu di elemen 1*/
		{
			First(*L) = Next(P);
		}
		else /* Ketemu di elemen list yang ditengah/akhir */
		{
			Next(Prec) = Next(P);
		}
		Next(P) = Nil;
		DeAlokasi(P);
	}
}

void DelAfter(List *L, addressP *Pdel, addressP Prec)
/* IS : L TIDAK Kosong, Prec adalah anggota List */
/* FS : menghapus Next(Prec): Pdel adalah alamat elemen list yang dihapus */
{
	*Pdel = Next(Prec);
	if (Pdel != Nil)
	{
		Next(Prec) = Next(*Pdel);
		Next(*Pdel) = Nil;
	}
}

void DelAll(List *L)
/* Delete semua elemen list dan alamat elemen di dealokasi */
{
	/* Kamus Lokal */
	addressP PDel;
	/* Algoritma */
	PDel = First(*L);
	while (PDel != Nil)
	{
		DelFirst(&(*L), &PDel);
		DeAlokasi(PDel);
		PDel = First(*L);
	}
}

// Challenge v2 (Mengubah list dengan sort)
void SortList(List *L)
{
	addressP P, Q;
	infotypeP temp;
	P = First(*L);
	while (Next(P) != Nil)
	{
		Q = Next(P);
		while (Q != Nil)
		{
			if (Info(P) > Info(Q))
			{
				temp = Info(P);
				Info(P) = Info(Q);
				Info(Q) = temp;
			}
			Q = Next(Q);
		}
		P = Next(P);
	}
}