#include "server.h"

Server::Server () {
    this->clients.clear();
}

void show_wallets(const Server& server) {
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: server.clients)
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

std::shared_ptr<Client> Server::add_client (std::string id) {
    while (this->get_client(id) != nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distrib(1000, 9999);
        int rand = distrib(gen);
        if (this->get_client(id + std::to_string(rand)) != nullptr) continue;
        id += std::to_string(rand);
    }

    std::shared_ptr<Client> client_ptr = std::make_shared<Client>(id, *this);
    this->clients[client_ptr] = 5;
    return client_ptr;
}

std::shared_ptr<Client> Server::get_client (const std::string id) const {
    for (const auto& client : this->clients) {
        if ((*client.first).get_id() == id)
            return client.first;
    }
    return nullptr;
}

double Server::get_wallet (const std::string id) {
    for (const auto& client : this->clients) {
        if ((*client.first).get_id() == id)
            return client.second;
    }
    return 0;
}