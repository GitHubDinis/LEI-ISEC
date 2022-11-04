// Servidor.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERV_UDP_PORT 6000

#define BUFFERSIZE 4096

void Abort(char* msg);

/*________________________________ main ________________________________________
*/

int main(int argc, char* argv[])
{
	SOCKET sockfd;
	int iResult, nbytes;
	int length_addr;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFFERSIZE];
	WSADATA wsaData;

	/*=============== INICIA OS WINSOCKS ==============*/

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		getchar();
		exit(1);
	}

	/*============ CRIA O SOCKET PARA RECEPCAO/ENVIO DE DATAGRAMAS UDP ============*/

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		Abort("Impossibilidade de abrir socket");

	/*=============== ASSOCIA O SOCKET AO  ENDERECO DE ESCUTA ===============*/

	/*Define que pretende receber datagramas vindos de qualquer interface de
	rede, no porto pretendido*/

	memset((char*)&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; /*Address Family: Internet*/
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /*Host TO Network Long*/
	serv_addr.sin_port = htons(SERV_UDP_PORT);  /*Host TO Network Short*/

	/*Associa o socket ao porto pretendido*/

	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		Abort("Impossibilidade de registar-se para escuta");

	/*================ PASSA A ATENDER CLIENTES INTERACTIVAMENTE =============*/

	while (1) {

		fprintf(stderr, "<SER1>Esperando datagram...\n");

		length_addr = sizeof(cli_addr);
		nbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cli_addr, &length_addr);

		if (nbytes == SOCKET_ERROR)
			Abort("Erro na recepcao de datagrams");

		buffer[nbytes] = '\0'; /*Termina a cadeia de caracteres recebidos com '\0'*/

		printf("\n<SER1>Mensagem recebida {%s}\n", buffer);


		//Enviar mensagem de volta ao cliente
		printf("\n<SER1>Vou reenviar a mensagem ao cliente\n");
		nbytes = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
		if (nbytes == SOCKET_ERROR) {
			printf("\n<SER1>Erro ao reenviar a mensagem ao cliente\n");
		}

	}

}

void Abort(char* msg)
{
	fprintf(stderr, "<SERV>Erro fatal: <%s> (%d)\n", msg, WSAGetLastError());
	exit(EXIT_FAILURE);
}
// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
