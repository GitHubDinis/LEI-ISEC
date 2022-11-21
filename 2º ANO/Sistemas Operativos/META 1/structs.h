#define TAM 20

typedef struct user user;
struct user{
	char *username;
	char *password;
	int saldo;
};

typedef struct item item;
struct item{
	int iditem, valor_atual, valor_comprar, duracao;
	char nome[TAM], categoria[TAM], userVende[TAM], userLicita[TAM];
};


