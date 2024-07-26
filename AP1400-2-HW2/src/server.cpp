#include "server.h"

Server::Server () {
    this->clients.clear();
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

std::shared_ptr<Client> Server::get_client (std::string id) const {
    for (auto client : this->clients) {
        if ((*client.first).get_id() == id)
            return client.first;
    }
    return nullptr;
}