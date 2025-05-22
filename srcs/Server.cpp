#include "../include/Server.hpp"

//Orthodox Canonical Form
Server::Server(size_t port, string pass) : portID(port), password(pass){
	isValidPort();
	setAdd();
	createSocket();
	initCommands();
}
Server::~Server(){}

void Server::acceptRequest(){
	int client_fd;
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	// Yeni istemci bağlantısını kabul et
	client_fd = errCheck(-1, accept(server_fd, (struct sockaddr *)&clientAddr, &clientAddrLen), "ERROR | Accept Failed!");

	// İstemci için bir Client nesnesi oluştur
	Client *newClient = new Client();
	newClient->setClientFd(client_fd);  // İstemci dosya tanıtıcısını ayarla
	newClient->setClientAddr(clientAddr);  // İstemci adresini ayarla (isteğe bağlı olarak saklayabilirsiniz)

	// İstemci dosya tanıtıcısını hem okuma hem de yazma için izlemek üzere kevent ayarla
	struct kevent evSet[2];

	// Okuma için kevent yapılandır
	EV_SET(&evSet[0], client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	
	// Yazma için kevent yapılandır
	EV_SET(&evSet[1], client_fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	
	// kevent'ları kqueue'ya ekle
	errCheck(-1, kevent(kq, evSet, 2, NULL, 0, NULL), "ERROR | kevent Add Client Failed!");

	// Yeni istemciyi vektöre ekle
	_clientMap[client_fd] = newClient;

	// İstemci bağlantısı başarıyla kabul edildi ve izleniyor
	cout << BLUE <<"New client connected: " << client_fd << RESET << endl;
}
void Server::disconnectClient(int client_fd) {
	if (_clientMap.find(client_fd) != _clientMap.end()) {		
		// İstemci bulundu, vektörden kaldır
		_clientMap.erase(client_fd);

		// İstemci dosya tanıtıcısını kapat
		errCheck(-1, close(client_fd), "ERROR | Failed to close client socket!");

		cout << "Client disconnected: " << client_fd << endl;
		return; // İşlem tamamlandı, fonksiyondan çık
	}
	// İstemci bulunamadı, hata mesajı ver
	cerr << "ERROR | Client not found: " << client_fd << endl;
}

vector<pair<string, vector<string> > > Server::getParams(const std::string& str)
{
	istringstream ss(str);
	vector<pair<string, vector<string> > > ret;
	string cmd  = "";
	string tmp  = "";
	string tmp2 = "";
	bool   flag;
	vector<string> params;
	
	while (getline(ss, tmp, '\n'))
	{
		istringstream lineStream(tmp);
		if (!(lineStream >> cmd))
			continue; // Eğer komut alınamazsa, sonraki satıra geç
		params.clear();
		flag = false;
		while (lineStream >> tmp)
		{
			if (tmp[0] == ':')
			{
				flag = true;
				tmp2 += tmp + " ";
				while (lineStream >> tmp)
				{
					if (tmp[0] != ':')
						tmp2 += tmp + " ";
					else{
						params.push_back(tmp2);
						tmp2.clear();
						tmp2 += tmp + " ";
					}
				}
				if (!tmp2.empty())
					params.push_back(tmp2);
			}
			if (!flag)
				params.push_back(tmp);
			
		}
		ret.push_back(make_pair(cmd, params));
	}
	return ret;
}
void Server::handleCommand(int client_id)
{
	vector<pair<string, vector<string> > > params = getParams(buffer);

	// cout << "\n --------ALL COMANDS&ARGUMENTS-------- \n";
	// for (size_t j = 0; j < params.size(); ++j) {
	// 	cout << "Command: " << params[j].first << endl;
	// 	cout << "Params: ";
	// 	for (size_t k = 0; k < params[j].second.size(); k++)
	// 		cout << "[" << params[j].second[k] << "]" << " ";
	// 	cout << endl;
	// }
	// cout << "\n --------       FINISH       -------- \n";

	for (size_t j = 0; j < params.size(); ++j) {
		if (_commandMap.find(params[j].first) != _commandMap.end())
			(this->*_commandMap[params[j].first])(params[j].second, *(_clientMap[client_id]));
		else
			cout << RED << "[" << params[j].first << "]" << " COMMAND NOT FOUNT OR ENVER HENÜZ İŞLEMEDİ :)" << RESET << endl;
	}
}
void Server::readEvent(int client_fd) {
	ssize_t bytes_received;

	bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			// Veri hemen mevcut değil, bu normal bir durumdur
			return;
		} 
		else
		{
			cerr << "ERROR | Failed to receive message from client " << client_fd << ": " << strerror(errno) << endl;
			disconnectClient(client_fd);
		}
	}
	else if (bytes_received == 0)
		disconnectClient(client_fd);
	else
	{
		buffer[bytes_received] = '\0';
		handleCommand(client_fd);
	}
}

int Server::getServerfd() const{
	return this->server_fd;
}
void Server::start(){
	kq = errCheck(-1, kqueue(), "ERROR | Kqueue Failed!");
	struct kevent evSet, evList[MAX_EVENTS]; //MAX_EVENTS = 1024

	// Sunucu dosya tanıtıcısını izlemek için kevent ayarla
	EV_SET(&evSet, server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	errCheck(-1, kevent(kq, &evSet, 1, NULL, 0, NULL), "ERROR | kevent Failed!");
	while (true)
	{
		int nev = errCheck(-1, kevent(kq, NULL, 0, evList, MAX_EVENTS, NULL), "ERROR | kevent Failed!");

		for (int i = 0; i < nev; i++)
		{
			if (evList[i].ident == server_fd)
				acceptRequest();
			else if (evList[i].flags & EV_EOF)
				disconnectClient(evList[i].ident);
			else if (evList[i].flags & EVFILT_READ) {
				readEvent(evList[i].ident);
			}
		}
	}
}