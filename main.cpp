#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <string>
using namespace std;

// Luokat

class account
{
	static int last_acno;
	int acno;
	char name[50];
	int deposit;
	char type;
	char currency;

public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
	};

int account ::last_acno = 100 ;

void account::create_account()
{
	acno = ++last_acno

	;
	cout<<"\n\nJasenen nimi: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nAnna jasenyystyyppi - (p = perusjasen, a = alennusjasen, k = kannatysjasen) : ";
	cin>>type;
	type=toupper(type);
	if (type == 'K')
        {cout<<"\n henkilojasen (h), yritysjasen (y) vai muu yhteisojasen (m): ";
        cin>>currency; }
        else {currency = 'h';}

	cout<<"\n Jasenmaksun suuruus - ";
	cout<<"\n Perusjasen 40e, alennusjasen 23e, kannatusjasen min.100e : ";
	cin>>deposit;
	cout<<"\n\n\nJasenen tallennus onnistui ";
}

void account::show_account() const
{
	cout<<"\nJasennumero : "<<acno;
	cout<<"\nJasenen nimi : ";
	cout<<name;
	cout<<"\nJasenyyden tyyppi : "<<type;
	cout<<"\nHenkilo/yritys/muu : "<<currency;
	cout<<"\nMyynnit : "<<deposit;

}


void account::modify()
{
	cout<<"\nOikeiden tietojen osalta, kirjoita jarjestelmassa olemassa oleva tieto";
	cout<<"\nJasennumero : "<<acno;
	cout<<"\nMuokkaa jasenen nimea : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nMuokkaa jasenyyden tyyppia (p/a/k) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nMuokkaa myyntisaldoa, anna uusi saldo: ";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	  cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << setw(10) << " " << currency << endl;
}


int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


// funktiot
void write_account();
void display_sp(int);	//j�sentietojen n�ytt�
void modify_account(int);	//j�sentietojen p�ivitys
void delete_account(int);	//j�senen poisto
void display_all();		//jasenrekisterin n�ytt�
void deposit_withdraw(int, int); // myyntisaldon p�ivitys
void service_info (); // tietoa jasenyyksista ja jarjestelmasta
void intro();	//intro-n�ytt�
// P��funktio

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tALKUVALIKKO";
		cout<<"\n\n\t1. Uusi jasen";
		cout<<"\n\n\t2. Lisaa kannatustuotetilitys";
		cout<<"\n\n\t3. Jasentiedot";
		cout<<"\n\n\t4. Jasenrekisteri";
		cout<<"\n\n\t5. Poista jasentieto";
		cout<<"\n\n\t6. Jasenteidon muokkaus";
		cout<<"\n\n\t7. Tietoa jasenyyksista ja jarjestelmasta";
		cout<<"\n\n\t8. Lopeta";
		cout<<"\n\n\tValitse haluamasi vaihtoehto (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tAnna jasennumero : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tAnna jasennumero : "; cin>>num;
			display_sp(num);
			break;
		case '4':
			display_all();
			break;
		case '5':
			cout<<"\n\n\tAnna jasennumero : "; cin>>num;
			delete_account(num);
			break;
		 case '6':
			cout<<"\n\n\tAnna jasennumero : "; cin>>num;
			modify_account(num);
			break;
        case '7':
            service_info();
			break;
		 case '8':
			cout<<"\n\n\tKiitos kun kaytit jasenyyksien hallintajarjestelmaa!";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}



//tallennus

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//tietyn tilin tiedot

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Tietoja ei voitu avata. Paina enter jatkaaksesi";
		return;
	}
	cout<<"\nMYYNTISALDOTIEDOT\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nJasennumeroa ei ole olemassa";
}


// tietojen muokkaus

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Tietoja ei voitu avata. Paina enter jatkaaksesi";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nAnna uudet tiedot: "<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Tiedot paivitetty";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Tietoja ei loytynyt ";
}

//tietojen deletointi


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Tietoja ei voitu avata. Paina enter jatkaaksesi";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tJasen poistettu";
}

//tilien listaus

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "Tietoja ei voitu avata. Paina enter jatkaaksesi";
        return;
    }

    cout << "\n\n\t\tJASENTEN TIEDOT\n\n";
    cout << "====================================================\n";
    cout << "Jasennumero      Nimi           Tyyppi  Maksettu\n";
    cout << "====================================================\n";

    int totalMembers = 0;
    int totalBalance = 0;

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        ac.report();

        // P�ivit� j�sensm��r� ja saldo
        totalMembers++;
        totalBalance += ac.retdeposit();
    }

    inFile.close();

    //J�senten kokonaism��r� ja saldojen summa
    cout << "\n====================================================\n";
    cout << "Jasenten kokonaismaara: " << totalMembers << "\n";
    cout << "Yhdistyksen varat: " << totalBalance << "\n";
}

// talletus ja nosto

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Tietoja ei voitu avata. Paina enter jatkaaksesi";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tMYYNTITUOTON TILITYS ";
				cout<<"\n\nAnna talletettava summa: ";
				cin>>amt;
				ac.dep(amt);
			}

			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Tiedot paivitetty";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Tietoja ei loytynyt ";
}

void service_info()
{
	std::cout << "JASENYYS- JA JARJESTELMAINFOA\n\n";

	std::cout << "Yhdityksella on 3 jasenyystyyppia: perusjasenyys, alennusjasenyys\n"
                 "tyottomille, opiskelijoille tai muille vahaviraisille seka \n"
                 "kannatusjasenyys niille jotka haluavat tukea yhdistysta \n"
                 "rahallisesti normaalia jasenmaksua enemman. Perusjasenen \n"
                 "jasenmaksu on 40 euroa, alennusjasenen 23 euroa ja \n"
                 "kannatusjasenen vahintaan 100e.\n\n";

    std::cout << "Jarjestelmassa voi lisata, poistaa ja muokata \n"
                 "jasentietoja. Jasenet voivat myos myyda kannatustuotteita \n"
                 "yhdistyksen tukemiseksi ja niiden myyntitulot voidaan \n"
                 "tilittaa jarjestelman kautta.\n";

    std::cout << "Jasenen saldossa nakyy seka jasenen maksama jasenmaksu \n"
                 "etta hanen myymiensa kannatustuotteiden summa yhteen \n"
                 "laskettuna. \n";}

//Intro
void intro()
{
	cout<<"\n\n\n\t  MAAILMANPARANTAJAT RY";
	cout<<"\n\n\t Jasenhallintajarjestelma";
	cout<<"\n\n\t ";
	cout<<"\n\n\n\nTehnyt: Johanna Kesti";
	cout<<"\n\n\n\nPaina Enter aloittaaksesi";

	cin.get();
}